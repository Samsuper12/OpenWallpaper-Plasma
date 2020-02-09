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

#ifndef WDESKTOP_HPP
#define WDESKTOP_HPP

#include <QQuickFramebufferObject>
#include <QStringList>
#include <QModelIndex>

#include "debug.hpp"
#include "dbus_manager.hpp"
#include "render_manager.hpp"
#include "config_parser.hpp"

class WDesktop;
class ObjectRenderer;

struct PackageConfig;
struct StartConfig;

enum renderType : int;
enum receivedValue : int;

enum renderState {
    nullCommand = 0,
    change,
    play,
    pause,
    stop
};

class WDesktop : public QQuickFramebufferObject
{
    Q_OBJECT
    Q_DISABLE_COPY(WDesktop)

    
    Q_PROPERTY(QString sourcePath READ getSourcePath NOTIFY packageChanged)
    Q_PROPERTY(QString musicPath READ getMusicSourcePath NOTIFY packageChanged) // TODO: clear value, if package without music
    Q_PROPERTY(QString dirPath READ getDir NOTIFY packageChanged) 
    
    Q_PROPERTY(double volume READ getMusicVolume WRITE setMusicVolume NOTIFY volumeChanged)
    
    Q_PROPERTY(float startVolume READ getStartVolume NOTIFY packageChanged) // TODO maybe change type to double
    
    Q_PROPERTY(int type READ getPackageType NOTIFY packageChanged)
    Q_PROPERTY(int fillMode READ getFillMode NOTIFY packageChanged) 
    Q_PROPERTY(bool haveMusic READ getHaveMusic NOTIFY packageChanged)
    Q_PROPERTY(bool focus READ getFocus NOTIFY focusChanged)
    Q_PROPERTY(bool musicCycle READ getMusicCycle WRITE setMusicCycle NOTIFY musicCycleChanged)
    
    const char* WP_DIR = ".openWallpaper";
    const char* WP_PACKAGE_FILE = "wallpaper.ini";
    const char* WP_MAIN_FILE = "main.ini";
    const char* WP_DEFAULT_CFG = "[PluginSettings]\n"
                                 "AlwaysInFocus=False\n"
                                 "IgnoreDefaultVolume=False\n"
                                 "LastVolume=0.0\n"
                                 "LastPackage=null\n"
                                 "MusicCycle=True\n"
                                 "\n"
                                 "[ManagerSettings]\n"
                                 "CopyToHiddenPlace=True\n";

    enum renderType : int {
        unknownRender = 0,
        ogl,
        video,
        gif,
        qml
    };

    enum receivedValue : int {
        alwaysInFocus = 0,
        ignoreDefaultVolume,
        musicCycle
    };

    struct MainConfig
    {
       bool alwaysInFocus = false;
       bool ignoreDefaultVolume = false;
       double lastVolume = 0.0;
       QString lastPackage = "null";
       bool musicCycle = true;
    };

    struct PackageConfig
    {
        renderType type = renderType::unknownRender;
        QString sourcePath;
        bool haveMusic = false;
        double startVolume = 0.0;
        QString musicPath;
        QString fillmode;
        QString dir;
    };

public:
    explicit WDesktop(QQuickItem *parent = nullptr);
    ~WDesktop() override;
    Renderer *createRenderer() const Q_DECL_OVERRIDE;

    Q_INVOKABLE QString getSourcePath() const           {return currentConfig->sourcePath;  }
    Q_INVOKABLE QString getDir() const                  {return currentConfig->dir;         }
        
    Q_INVOKABLE void setOglPlaying(const int state); // TODO: change
    Q_INVOKABLE void checkFocus(QModelIndex task);
    Q_INVOKABLE void checkLastPackage();

    bool getFocus() const;

private:
    
    QString getMusicSourcePath() const      {return currentConfig->musicPath;   }
    double getMusicVolume() const           {return mainCfg->lastVolume;        }
    float getStartVolume() const            {return (float)currentConfig->startVolume; } // FIXME
    int getPackageType() const              {return currentConfig->type;        }
    bool getHaveMusic() const               {return currentConfig->haveMusic;   }
    int getFillMode() const;
    void setMusicVolume(double volume); // TODO: change
    
    void restoreConfig(const std::string& path, const std::string& text);
    void hideRenderer(renderType type);
    void setupConfigs();

    void setMusicCycle(bool value);
    bool getMusicCycle() const;

public slots:
    void changeMainCfg(int param, QString value);
    void setPackage(QString path);
    void setPlaying(int value);

    void testSlot();

signals:
   //Postfix C - local C++ signal;
   //Postfix Q - emited signal from C to QML layer;
    
   void playingSignalC(int render, bool mode); 
   void playingSignalQ(int Render, bool Mode); 

   //void musicVolumeSignalQ(float Volume);

   void packageChanged();
   void packageStopped();
   
   void debugSignalC();
   void debugSignalQ();

   void musicCycleChanged(bool value) const;
   void focusChanged(bool focus) const;
   void volumeChanged() const;
   
public:
   renderState renderStatus;
   MainConfig* mainCfg;

   // only for OpenGL Renderer
   bool musicPlay = false;

private:
   std::unique_ptr<PackageConfig> currentConfig;
   std::map<std::string, renderType> renderMap;

   ConfigParser packageParser;
   ConfigParser mainCfgParser;

   // only for OpenGL Renderer
   renderType renderer;

   DBusManager dBus;

   bool focus = false;
};

#endif // WDESKTOP_HPP
