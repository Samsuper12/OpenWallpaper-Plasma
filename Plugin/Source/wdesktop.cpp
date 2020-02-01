/*
 * This file is part of OpenWallpaper Plasma.
 * 
 * OpenWallpaper Plasma is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * OpenWallpaper Plasma is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * Full license: https://github.com/Samsuper12/OpenWallpaper-Plasma/blob/master/LICENSE
 * Copyright (C) 2020- by Michael Skorokhodov bakaprogramm29@gmail.com
 */

#include "wdesktop.hpp"

#include <QQuickWindow>
#include <QOpenGLFramebufferObject>
#include <QOpenGLFramebufferObjectFormat>

class ObjectRenderer : public QQuickFramebufferObject::Renderer
{

public:
    ObjectRenderer() {
        lastTime = std::time(nullptr);
        rendManager = new RenderManager();
    }
    
    virtual ~ObjectRenderer() {
        delete rendManager;
    }

    void synchronize(QQuickFramebufferObject *item) override {
        plasmaDesktop = item->window();

        WDesktop *wdesk = static_cast<WDesktop *>(item);

        switch (wdesk->renderStatus) {

        case renderState::change:
            rendManager->set(wdesk->getSourcePath(), wdesk->getDir());
            play = true;
            break;

        case renderState::play:
            play = true;
            rendManager->resume();
            break;

        case renderState::pause:
            play = false;
            rendManager->pause();
            break;

        case renderState::stop:
            play = false;
            rendManager->setDefault();
            break;

        default:
            break;
        }

        if (play) {
            focus = wdesk->getFocus();
            musicVolume = wdesk->mainCfg->lastVolume;
            music = wdesk->musicPlay;
        }

        wdesk->renderStatus = renderState::nullCommand;
    }

    void render() override {
        if (play) {
            
            rendManager->renderObject->data(focus, music, musicVolume, vec);
            rendManager->renderObject->draw();
            
            update();
            plasmaDesktop->resetOpenGLState();
            //fps();
        }
    }

    QOpenGLFramebufferObject *createFramebufferObject(const QSize &size) override {
        QOpenGLFramebufferObjectFormat format;
        format.setSamples(4);
        format.setAttachment(QOpenGLFramebufferObject::CombinedDepthStencil);
        return new QOpenGLFramebufferObject(size, format);
    }

    inline void fps() {
        currentTime = std::time(nullptr);
        frame++;
        if ((currentTime - lastTime) > 1) {
            LOG_CONSOLE(frame)
            frame = 0;
            //lastTime++;
            lastTime = currentTime;
        }
    }

private:
    QQuickWindow* plasmaDesktop;
    RenderManager* rendManager;

    //useless now. created for future
    std::vector<std::string> vec;

    bool play = true;
    bool focus = false;
    bool music = false;
    float musicVolume;

    int frame = 0;
    std::time_t currentTime = 0;
    std::time_t lastTime = 0;
};


WDesktop::WDesktop(QQuickItem *parent)
    : QQuickFramebufferObject(parent)
    , renderStatus(renderState::nullCommand)
    , mainCfg(new MainConfig)
    , currentConfig(nullptr)
    , renderer(renderType::ogl)
{
    setupConfigs();

    connect(this, &WDesktop::playingSignalC, this, &WDesktop::playingSignalQ);
    connect(this, &WDesktop::disableSignalC, this, &WDesktop::disableSignalQ);
    connect(this, &WDesktop::enableSignalC, this, &WDesktop::enableSignalQ);
    connect(this, &WDesktop::debugSignalC, this, &WDesktop::debugSignalQ);
    connect(&dBus, &DBusManager::changeConfigSignal, this, &WDesktop::changeMainCfg);
    connect(&dBus, &DBusManager::changePackageSignal, this, &WDesktop::setPackage);
    connect(&dBus, &DBusManager::playSignal, this, &WDesktop::setPlaying);
    connect(&dBus, &DBusManager::debugSignal, this, &WDesktop::testSlot);

    connect(&dBus, &DBusManager::volumeSignal, this, [&](double volume) {
        setMusicVolume(volume);
    });

    connect(&dBus, &DBusManager::volumeRequestSignal, [&]() {
        emit dBus.volumeToManagerSignal(mainCfg->lastVolume);
    });

    connect(&dBus, &DBusManager::lastPackageRequestSignal, [&]() {
        emit dBus.lastPackageSignal(mainCfg->lastPackage);
    });

    connect(&dBus, &DBusManager::restoreConfigSignal, this, [&]() {
        restoreConfig(QDir::homePath().toStdString() +
                      '/' + WP_DIR+ '/' + WP_MAIN_FILE, WP_DEFAULT_CFG);
    });

    renderMap["OGL"] = renderType::ogl;
    renderMap["Video"] = renderType::video;
    renderMap["Gif"] = renderType::gif;
    renderMap["QML"] = renderType::qml; // later
}

WDesktop::~WDesktop()
{
    mainCfgParser.replace("LastVolume", std::to_string(mainCfg->lastVolume));
    mainCfgParser.replace("LastPackage", mainCfg->lastPackage.toStdString());
    mainCfgParser.replace("AlwaysInFocus", (mainCfg->alwaysInFocus) ? "True" : "False");
    mainCfgParser.replace("MusicCycle", (mainCfg->musicCycle) ? "True" : "False");

    delete mainCfg;
}

QQuickFramebufferObject::Renderer *WDesktop::createRenderer() const
{
    return new ObjectRenderer;
}

int WDesktop::getFillMode() const
{

    if (currentConfig->fillmode == "PreserveAspectCrop") {
        return 2; // VideoOutput.PreserveAspectCrop
    }
    else if (currentConfig->fillmode == "PreserveAspectFit") {
        return 1; // VideoOutput.PreserveAspectFit
    }
    else {
        return 0; // VideoOutput.Stretch // std
    }
}

void WDesktop::setOglPlaying(const int state)
{
    switch (state) {
    case 0:
        renderStatus = renderState::stop;
        break;
    case 1:
        renderStatus = renderState::play;
        break;
    case 2:
        renderStatus = renderState::pause;
        break;
    default:
        break;
    }

    update();
}

void WDesktop::setMusicVolume(double volume)
{
    emit musicVolumeSignalQ(volume);
    mainCfg->lastVolume = volume;
    update();
}

void WDesktop::checkFocus(QModelIndex task)
{
    if (mainCfg->alwaysInFocus) {
        return;
    }

    // desktop always have -1 position
    // also we can check focus with TaskModel.count
    // if count == 0 (zero windows open), then we look at desktop

    if(task.row() == -1) {
        this->focus = true;
    } else {
        this->focus = false;
    }

    emit focusChanged(focus);
    update();
}

void WDesktop::checkLastPackage()
{
    if (mainCfg->lastPackage != "null" && !mainCfg->lastPackage.isNull()) {
        setPackage(mainCfg->lastPackage);
    }
    // else - default OGL scene
}

bool WDesktop::getFocus() const
{
    if (mainCfg->alwaysInFocus) {
        return true;
    }
    return focus;
}

void WDesktop::restoreConfig(const std::string& path, const std::string& text)
{
    QDir dir(QDir::home());

    if (!dir.exists(WP_DIR)) {
        dir.mkdir(WP_DIR);
    }

    //set default main config;
    delete mainCfg;
    mainCfg = new MainConfig;

    // and replace main.ini
    ConfigParser::createFile(path, text);

    // emit signal to manager
    dBus.restoreSuccessfulSlot();
}

void WDesktop::hideRenderer(renderType type)
{
    if (type == renderer) {
        return;
    }

    switch (renderer) {

    case renderType::ogl:
        emit disableSignalC(static_cast<int>(renderer));
        update();
        break;

    case renderType::video:
        emit disableSignalC(static_cast<int>(renderer));
        break;

    case renderType::gif:
        emit disableSignalC(static_cast<int>(renderer));
        break;

    case renderType::qml:
        break;

    default: break;
    }
}

void WDesktop::setupConfigs()
{
    QDir dir(QDir::home());
    std::string cfgPath;

    if(!dir.cd(WP_DIR)) {
        restoreConfig(QDir::homePath().toStdString() + '/' + WP_DIR+ '/' + WP_MAIN_FILE, WP_DEFAULT_CFG);
        dir.cd(WP_DIR);
    }

    cfgPath = dir.path().toStdString() + '/' + WP_MAIN_FILE;

    QStringList files = dir.entryList(QDir::Files | QDir::NoDotAndDotDot);

    if (!files.contains(WP_MAIN_FILE)) {
        restoreConfig(cfgPath, WP_DEFAULT_CFG);
    }

    packageParser.findValue("Type",
                      "Source",
                      "MusicSource",
                      "Music",
                      "StartVolume",
                      "FillMode");

    mainCfgParser.findValue("IgnoreDefaultVolume",
                               "AlwaysInFocus",
                               "LastVolume",
                               "LastPackage",
                               "MusicCycle");

    if (!mainCfgParser.open(cfgPath)) {
        LOG("Main config not open.")
        restoreConfig(cfgPath, WP_DEFAULT_CFG);
    }

    try {
        mainCfg->alwaysInFocus = (mainCfgParser["AlwaysInFocus"] == "True") ? true : false;
        mainCfg->ignoreDefaultVolume = (mainCfgParser["IgnoreDefaultVolume"] == "True") ? true : false;
        mainCfg->lastVolume = std::stod(mainCfgParser["LastVolume"]);
        mainCfg->lastPackage = QString(mainCfgParser["LastPackage"].c_str());
        mainCfg->musicCycle = (mainCfgParser["MusicCycle"] == "True") ? true : false;

    } catch (const std::exception& e) {
        LOG(e.what())
        restoreConfig(cfgPath, WP_DEFAULT_CFG);

        //manager.sendError (or maybe later...)
    }
}
void WDesktop::setMusicCycle(bool value)
{
    mainCfg->musicCycle = value;
    emit musicCycleChanged(value);
}

bool WDesktop::getMusicCycle() const
{
    return mainCfg->musicCycle;
}

void WDesktop::changeMainCfg(int param, QString value)
{
    switch (param) {

    case receivedValue::alwaysInFocus:
        mainCfg->alwaysInFocus =
                (value == "True") ? true : false;
        break;

    case receivedValue::ignoreDefaultVolume:
        mainCfg->ignoreDefaultVolume =
                (value == "True") ? true : false;
        break;

    case receivedValue::musicCycle:
        setMusicCycle((value == "True") ? true : false);
        break;

    default:
        break;
    }

    this->update();
}

void WDesktop::setPackage(QString path)
{
    std::unique_ptr<PackageConfig> guard;
    QString pathBuf = path;

    packageParser.clear();

    if (!packageParser.open(path.toStdString())) {
        LOG("Package was not open")
        return;
    }

    if(currentConfig != nullptr) {
        guard = std::move(currentConfig);
    }

    path.remove(WP_PACKAGE_FILE);

    currentConfig = std::make_unique<PackageConfig>();

    try {
        currentConfig->type = renderMap[packageParser["Type"]];
        currentConfig->sourcePath = path + QString(packageParser["Source"].c_str());
        currentConfig->musicPath = path + QString(packageParser["MusicSource"].c_str());
        currentConfig->haveMusic = (packageParser["Music"] == "True") ? true: false;
        currentConfig->fillmode = QString(packageParser["FillMode"].c_str());
        currentConfig->dir = path;

        if (!mainCfg->ignoreDefaultVolume) {
            const std::string sref = packageParser["StartVolume"];

            if (!sref.empty()) {
                currentConfig->startVolume = std::stod(sref);
                mainCfg->lastVolume = currentConfig->startVolume;

                emit dBus.volumeToManagerSignal(mainCfg->lastVolume);
            }

        } else {
            currentConfig->startVolume = mainCfg->lastVolume;
        }

        if (currentConfig->startVolume > 0.0) {
            musicPlay = true;
        }

        if (currentConfig->type == renderType::unknownRender ||
           currentConfig->sourcePath == path) {
            LOG("Incorrect source path or unknown render type")
            return;
        }

    } catch (const std::exception& e) {
        currentConfig = std::move(guard);
        LOG(e.what())
        return;
    }

    mainCfg->lastPackage = pathBuf;
    hideRenderer(currentConfig->type);
    renderer = currentConfig->type;

    if (currentConfig->type == renderType::ogl) {
        renderStatus = renderState::change;
    }

    emit enableSignalC(renderer);
    update();
}

void WDesktop::setPlaying(int value)
{
    if (value > 0) {
        emit playingSignalC(renderer, true);
        musicPlay = true;
        update();
        return;
    }

    emit playingSignalC(renderer, false);
    musicPlay = false;
    update();
}

void WDesktop::testSlot()
{
}
