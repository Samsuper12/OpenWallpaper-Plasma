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

#ifndef RENDERMANAGER_H
#define RENDERMANAGER_H

#include <QObject>
#include <memory>

#include "debug.hpp"
#include "dll_loader.hpp"
#include "default_scene.hpp"

using QtRender = openWallpaper::ogl::QtRender;

class RenderManager : public QObject
{
    Q_OBJECT

public:
    explicit RenderManager(QObject *parent = nullptr);
    ~RenderManager();

    void set(const QString& sourcePath, const QString& packageDir);
    void setDefault();

    void resume() const;
    void pause() const;

    std::shared_ptr<QtRender> renderObject;

private:
    QString lastPackage;
    DllLoader<QtRender>* libRef;
};

#endif // RENDERMANAGER_H
