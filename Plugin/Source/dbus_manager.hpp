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

#ifndef DBUS_MANAGER_HPP
#define DBUS_MANAGER_HPP

#include <QObject>
#include <QtDBus>

#include "debug.hpp"

class DBusManager : public QObject
{
    Q_OBJECT

public:
    explicit DBusManager(QObject *parent = nullptr);
    ~DBusManager();

public slots:
    void setPlaySlot(int arg);
    void setVolumeSlot(double volume);
    void setPackageSlot(QString package);
    void debugSlot(QString Arg);
    void changeConfigSlot(int param, QString value);
    void restoreConfigSlot();
    void restoreSuccessfulSlot();

    void getLastPackageRequestSlot();

    void getVolumeRequestSlot();

signals:
    void playSignal(int arg);
    void volumeSignal(double volume);
    void changePackageSignal(QString package);
    void debugSignal(QString arg);
    void changeConfigSignal(int param, QString value);
    void restoreConfigSignal();
    void restoreSuccessfulSignal();

    void lastPackageRequestSignal();
    void lastPackageSignal(QString path);

    void volumeRequestSignal();
    void volumeToManagerSignal(double value);
};


#endif // DBUS_MANAGER_HPP
