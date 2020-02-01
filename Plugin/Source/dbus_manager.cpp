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

#include "dbus_manager.hpp"
#include "dbus_manager_adaptor.h"

DBusManager::DBusManager(QObject *parent)
    : QObject(parent)
{
#ifdef DEBUG
    LOG_CONSOLE("DBus adaptor has been created.")
#endif
    new DBusManagerAdaptor(this);

    QDBusConnection connection = QDBusConnection::sessionBus();
    connection.registerObject("/DBusManager", this);
    connection.registerService("org.OpenWallpaper.DBusManager");
}

DBusManager::~DBusManager()
{
}

void DBusManager::setPlaySlot(int arg)
{
#ifdef DEBUG
    LOG_CONSOLE("setPlaySlot.")
#endif
    emit playSignal(arg);
}

void DBusManager::setVolumeSlot(double volume)
{
#ifdef DEBUG
    LOG_CONSOLE("setVolumeSlot.")
#endif
    emit volumeSignal(volume);
}

void DBusManager::setPackageSlot(QString package)
{
#ifdef DEBUG
    LOG_CONSOLE("setPackageSlot.")
#endif
    emit changePackageSignal(package);
}

void DBusManager::debugSlot(QString arg)
{
#ifdef DEBUG
    LOG_CONSOLE("debugSlot.")
#endif
    emit debugSignal(arg);
}

void DBusManager::changeConfigSlot(int param, QString value)
{
#ifdef DEBUG
    LOG_CONSOLE("changeConfigSlot.")
#endif
    emit changeConfigSignal(param, value);
}

void DBusManager::restoreConfigSlot()
{
#ifdef DEBUG
    LOG_CONSOLE("restoreConfigSlot.")
#endif
    emit restoreConfigSignal();
}

void DBusManager::restoreSuccessfulSlot()
{
#ifdef DEBUG
    LOG_CONSOLE("restoreSuccessfulSlot.")
#endif
    emit restoreSuccessfulSignal();
}

void DBusManager::getLastPackageRequestSlot()
{
#ifdef DEBUG
    LOG_CONSOLE("getLastPackageRequestSlot.")
#endif
    emit lastPackageRequestSignal();
}

void DBusManager::getVolumeRequestSlot()
{
#ifdef DEBUG
    LOG_CONSOLE("getVolumeRequestSlot.")
#endif
    emit volumeRequestSignal();
}
