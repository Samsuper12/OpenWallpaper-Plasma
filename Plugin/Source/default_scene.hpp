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

#ifndef DEFAULT_SCENE_HPP
#define DEFAULT_SCENE_HPP

#include <QOpenGLContext>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>

#include "abstract_render.hpp"

class DefaultScene : public openWallpaper::ogl::QtRender
{
public:
    DefaultScene();
    ~DefaultScene();

    void init(const std::string& dir, const std::vector<std::string>& params) override;
    void data(bool focus, bool music, float volume, const std::vector<std::string>& params) override;
    void draw() override;
    void onPause() override;
    void onResume() override;

private:
    QOpenGLFunctions* functions;
};

#endif // DEFAULT_SCENE_HPP
