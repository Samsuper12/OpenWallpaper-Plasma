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

#include "default_scene.hpp"

DefaultScene::DefaultScene()
{
    functions = QOpenGLContext::currentContext()->functions();
    functions->glClearColor(0.0, 0.0, 0.0, 1.0);
}

DefaultScene::~DefaultScene()
{
}

void DefaultScene::init(const std::string& dir, const std::vector<std::string>& params)
{
    Q_UNUSED(dir)
    Q_UNUSED(params)
}

void DefaultScene::data(bool focus, bool music, float volume, const std::vector<std::string> &params)
{
    Q_UNUSED(focus)
    Q_UNUSED(music)
    Q_UNUSED(volume)
    Q_UNUSED(params)
}

void DefaultScene::draw()
{
    functions->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    functions->glEnable(GL_DEPTH_TEST);
}

void DefaultScene::onPause()
{
}

void DefaultScene::onResume()
{
}
