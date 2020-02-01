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

#include "render_manager.hpp"

RenderManager::RenderManager(QObject *parent) 
    : QObject(parent)
    , libRef(nullptr)
{
    renderObject = std::make_shared<DefaultScene>();
}

RenderManager::~RenderManager()
{
    if (libRef != nullptr) {
        delete libRef;
        libRef = nullptr;
    }
}

void RenderManager::set(const QString& sourcePath, const QString& packageDir)
{
    if (sourcePath == lastPackage) {
        LOG("This is same package!")
        return;
    }

    this->lastPackage = sourcePath;

    setDefault();

    libRef = new DllLoader<QtRender>(sourcePath.toStdString());
    std::shared_ptr<QtRender> BufferRef = libRef->loadClass();

    if (BufferRef.get() == nullptr) {
        LOG("OpenGL package was not loaded.")
        return;
    }

    //useless now. created for future
    std::vector<std::string> vec;

    BufferRef->init(packageDir.toStdString(),vec);
    renderObject = std::move(BufferRef);
}

void RenderManager::setDefault()
{
    if (libRef != nullptr) {
        delete libRef;
        libRef = nullptr;
    }

    //useless now. created for future
    std::vector<std::string> vec;

    lastPackage.clear();
    renderObject = std::make_shared<DefaultScene>();
    renderObject->init(std::string(), vec);
}

void RenderManager::resume() const
{
    renderObject->onResume();
}

void RenderManager::pause() const
{
    renderObject->onPause();
}

