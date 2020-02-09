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
import QtQuick.Controls 2.12 as QQC2
import QtMultimedia 5.12 as QM

import org.kde.plasma.core 2.0
import org.kde.taskmanager 0.1 as TaskManager

import OpenWallpaper.Plasma 0.1

Item {
    id: root

    // OGL is dafault
    property int currentType: 1; 
    property bool haveMusicQml: false;
    
    property real volumeFromPlasma: wallpaper.configuration.Volume;
    property string packageFromPlasma: wallpaper.configuration.Package;
    
    onVolumeFromPlasmaChanged:      { wClass.volume = volumeFromPlasma;    }
    onPackageFromPlasmaChanged:     { wClass.setPackage(packageFromPlasma);       }
    
    
    Rectangle {
        id: oglWallpaper
        visible: true;
        anchors.fill: parent;
        
        WDesktop {
            id: wClass
            anchors.fill: parent;
        
            SequentialAnimation {
                id: wAnim
            }
        }
    }
    
    // idea of "double player" - https://store.kde.org/p/1316299
    // i don't know why QML classes are so... unfinished.
    
    VideoWallpaper {
        id: videoWallpaper;
        anchors.fill: parent;
        
        visible: false;
    }
    
    AnimatedImage {
        id: gifWallpaper;
        anchors.fill: parent;
        
        playing : true;
        visible: false;
        
        Component.onDestruction: {
            source = "";
        }
    }
    
    QM.Audio {
        id:audioPlayer;
        
        autoPlay: false;
        
        Component.onDestruction: {
            source = "";
        }
    }
    
    //https://api.kde.org/4.x-api/apidox-kde-4.x/apidox-kde-4.x/workspace-apidocs/plasma-workspace/html/tasksmodel_8h.html
    TaskManager.TasksModel {

		onActiveTaskChanged: {
             wClass.checkFocus(activeTask);
		}
    }
    
    Connections {
        target: wClass;
        
        onPackageChanged:       {   enableRender();               }
        onPackageStopped:       {   disableRender();              }
        onPlayingChanged:       {   renderPlaying(wClass.playing) }
        onVolumeChanged:        {   setVolume();                  }  // TODO change. Must take argument 
        onFocusChanged:         {}
        onMusicCycleChanged: {  
            if (currentType == 2) { //Video
                //videoWallpaper.loop(value); // in next release
                return;
            }
            audioPlayer.loops = value ? QM.Audio.Infinite : 1
        }
    }
    
    Component.onCompleted: {
        wClass.checkLastPackage();
    }
    
    function renderPlaying(val) { 
        switch (currentType) {
            case 1: 
                wClass.glState = val ? 2 : 3;
                break;
            case 2:
                val ? videoWallpaper.play() : videoWallpaper.pause();
                break;
            case 3: gifWallpaper.paused = !val;
                break;
                    
            default: break;
        }
        
        if (haveMusicQml) {
            val ? audioPlayer.play() : audioPlayer.pause();
        }
    }
    
    function enableRender() {
         switch (wClass.type) {
            case 1: 
                oglWallpaper.visible = true;
                break;
            case 2:
                videoWallpaper.clean();
                videoWallpaper.open("file://" + wClass.sourcePath);
                videoWallpaper.fillMode(wClass.fillMode);
                videoWallpaper.visible = true;
                videoWallpaper.setVolume(wClass.startVolume);
                //videoWallpaper.loop(wClass.musicCycle);
                break;
            case 3:
                gifWallpaper.source = "file://" + wClass.sourcePath;
                gifWallpaper.playing = true;
                gifWallpaper.visible = true;
                break;
                    
            default: break;
        }
        
        currentType = wClass.type;
        
        if (wClass.haveMusic) {
            haveMusicQml = true;
            audioPlayer.source = "file://" + wClass.musicPath;
            setVolume();
            audioPlayer.loops = wClass.musicCycle ? QM.Audio.Infinite : 1;
            audioPlayer.play();
        }
    }
    
    function disableRender() {
        switch (currentType) {
            case 1:  //ogl
                oglWallpaper.visible = false;
                wClass.glState = 4; // 4 - Stop;
                break;
            case 2: //video
                videoWallpaper.stop();
                videoWallpaper.visible = false;
                videoWallpaper.fillMode(0); // to default
                videoWallpaper.clean();
                
                break;
            case 3: // gif
                gifWallpaper.playing = false;
                gifWallpaper.visible = false;
                gifWallpaper.source = "";
                break;
                    
            default: break;
        }
        
        currentType = 0; // null render
        
        haveMusicQml = false;
        audioPlayer.stop();
        audioPlayer.source = "";
    }
    
    function setVolume(vol) {
        if (currentType == 2) {   //Video
            videoWallpaper.setVolume(wClass.volume);
            return;
        }
        audioPlayer.volume = wClass.volume;
    }
}
