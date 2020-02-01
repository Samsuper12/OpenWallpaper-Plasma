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

#ifndef DEBUG_HPP
#define DEBUG_HPP

#include <fstream>
#include <QDebug>
#include <QDir>

#define LOG_PATH QDir::homePath().toStdString() \
    + '/' + ".openWallpaper"  \
    + '/' + "log"

#define LOG_CONSOLE(comment) \
    qDebug() << comment;

#define LOG(comment) { \
    std::ofstream file(LOG_PATH, std::ios::app | std::ios::out); \
    file << __TIME__ \
    << " [" \
    << __FILE__ \
    << ": " \
    << __LINE__ \
    << "] " \
    << comment \
    << '\n' \
    << std::flush; \
    file.close(); } \
    LOG_CONSOLE(comment)


#endif // DEBUG_HPP
