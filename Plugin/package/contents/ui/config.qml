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
import QtQuick.Dialogs 1.3 as QQD
import QtQuick.Layouts 1.12 as QQL

import org.kde.kquickcontrols 2.0 as KQC2
import org.kde.plasma.core 2.0 as PlasmaCore
import org.kde.kirigami 2.5 as Kirigami

Kirigami.FormLayout {
    id: root
    twinFormLayouts: parentLayout
    
    property string cfg_Package;
    property real cfg_Volume;
    
    QQC2.TextField{
        id: filePath
        Kirigami.FormData.label: i18ndc("plasma_wallpaper_org.openwallpaper.plasma","@label:chooser", "Path: ")
        readOnly: true;
        
        MouseArea {
            anchors.fill: parent;
            
            onClicked: {
                fileDialog.open();
            }
        }
    }
    
    QQC2.Slider {
        id: volumeSlider
        Kirigami.FormData.label: i18ndc("plasma_wallpaper_org.openwallpaper.plasma","@label:chooser", "Volume: ")
        width: 15;
        from: 0.0
        to: 1.0
        
        onValueChanged: {
            cfg_Volume = value;
        }
    }
    
    QQC2.Button {
        id: colorButton
        Kirigami.FormData.label: i18ndc("plasma_wallpaper_org.openwallpaper.plasma","@label:chooser", "Information: ")
        text: qsTr("Show");
        
        onClicked:{
            popupInfo.open();
        }
    }
    
    QQD.FileDialog {
        id: fileDialog
        title: "Please choose a wallapper file"
        folder: shortcuts.home
        nameFilters: ["Wallpaper init file (*.ini)"]
        
        onAccepted: {
            filePath.text = fileDialog.fileUrl.toString().replace("file://", "");
            cfg_Package = filePath.text;
        }
        width: parent.width
    }
    
    QQC2.Popup {
        id: popupInfo
        height: parent.height /1.3;
        width: 475
        x:  (parent.width /2) - (width/2);
        y: (parent.height /2) - (height/2);

        modal: true
        closePolicy: QQC2.Popup.CloseOnPressOutside
        
        Flickable {
            id: configPopupContent
            anchors.fill:parent
        
            clip: true
            contentWidth: 450
            contentHeight: 370
            QQC2.ScrollBar.vertical: QQC2.ScrollBar { }
        
            Rectangle {
                anchors.fill: parent;
                
                QQC2.Label {
                    id: nameLabel;
                    x: (parent.width /2) - (width /2)
                    anchors.top: parent.top
                    anchors.topMargin: 30;
                    text: qsTr("OpenWallpaper Plasma");
                    font.pixelSize: 20;
                }
                
                QQC2.Label{
                    id: useLabel;
                    anchors.top: nameLabel.bottom
                    anchors.left: parent.left;
                    anchors.topMargin: 20;
                    anchors.leftMargin: 15;
                    
                    text: qsTr("<b>How to use it?</b>");
                    font.pixelSize: 14;
                }
                
                Text {
                    id: ans1Label;
                    anchors.top: useLabel.bottom
                    anchors.left: parent.left;
                    anchors.right: parent.right;
                    anchors.topMargin: 5;
                    anchors.leftMargin: 15;
                    anchors.rightMargin: 15;

                    text: qsTr("Wallpaper plugin use packages with needed information for playing content on your desktop. Just downloads package what you like and select path to 'wallpaper.ini' file in package folder.");
                    wrapMode: Text.WordWrap;
                    font.pixelSize: 12;
                }
                
                QQC2.Label {
                    id: useManagerLabel;
                    anchors.top: ans1Label.top
                    anchors.left: parent.left;
                    anchors.topMargin: 60;
                    anchors.leftMargin: 15;
                    
                    text: qsTr("<b>Manager</b>");
                    font.pixelSize: 14;
                }
                
                Text {
                    id: ans2Label;
                    anchors.top: useManagerLabel.bottom
                    anchors.left: parent.left;
                    anchors.right: parent.right;
                    anchors.topMargin: 5;
                    anchors.leftMargin: 15;
                    anchors.rightMargin: 15;

                    text: qsTr("With the OpenWallpaper Manager you can very quickly and comfortably add/delete/play wallpaper packages. Also, manager have settings for better customizing playing process. Download, install and enjoy.");
                    wrapMode: Text.WordWrap;
                    font.pixelSize: 12;
                }
                
                QQC2.Label {
                    id: whatNextLabel;
                    anchors.top: ans2Label.top
                    anchors.left: parent.left;
                    anchors.topMargin: 60;
                    anchors.leftMargin: 15;
                    
                    text: qsTr("<b>What next?</b>");
                    font.pixelSize: 14;
                }
                
                Text {
                    id: ans3Label;
                    anchors.top: whatNextLabel.bottom
                    anchors.left: parent.left;
                    anchors.right: parent.right;
                    anchors.topMargin: 5;
                    anchors.leftMargin: 15;
                    anchors.rightMargin: 15;

                    text: qsTr("Cross platforming and more flexibility. Send email, if you have good idea or interesting proposal.");
                    wrapMode: Text.WordWrap;
                    font.pixelSize: 12;
                }
                
                QQC2.Label {
                    id: moreInfoLabel;
                    x: (parent.width /2) - (width /2)
                    anchors.top: ans3Label.bottom
                    anchors.topMargin: 30;
                    text: qsTr("<a href='https://github.com/Samsuper12/OpenWallpaper-Plasma'>More information on GitHub</a>");
                    onLinkActivated: Qt.openUrlExternally("https://github.com/Samsuper12/OpenWallpaper-Plasma")
                    font.pixelSize: 13;
                }
            }
        }
    }
}
