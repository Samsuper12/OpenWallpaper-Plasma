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

import QtQuick 2.12
import QtMultimedia 5.12 as QM

// idea of "double player" - https://store.kde.org/p/1316299
// i don't know why QML classes are so... unfinished.

Rectangle {

    QM.Video {
        id: vBelow;
        anchors.fill: parent;
            
        autoPlay: false;
        muted: true;
        loops: QM.MediaPlayer.Infinite;
    }
        
    QM.Video {
        id: vAbove;
        anchors.fill: parent;
            
        autoPlay: false;
        loops: QM.MediaPlayer.Infinite;
    }
        
    function loop(value) {
        vAbove.loops = value ? QM.MediaPlayer.Infinite : 1;
    }
        
    function pause() {
        vAbove.pause();
    }
        
    function stop() {
        vBelow.stop();
        vAbove.stop();
    }
        
    function play() {
        vAbove.play();
    }
        
    function open(src) {
        vBelow.source = src;
        vAbove.source = src;
            
        vBelow.play();
        vBelow.seek(0);
        vBelow.pause();
        vAbove.play();
    }
        
    function setVolume(vol) {
        vAbove.volume = vol;
    }
        
    function fillMode(mode) {
        vBelow.fillMode = mode;
        vAbove.fillMode = mode;
    }
        
    function clean() {
        vBelow.source = "";
        vAbove.source = "";
    }
        
    Component.onDestruction: {
        clean();
    }
} 
