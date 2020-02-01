cmake_minimum_required(VERSION 3.10)

project(OpenWallpaperPlasmaPlugin
        LANGUAGES CXX
        VERSION 0.1
)

find_package(ECM 5.66 REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH})

find_package(KF5Plasma REQUIRED)

find_package(Qt5 CONFIG REQUIRED 
    Core  
    DBus
    Quick
    Qml
)

add_subdirectory(Plugin)
