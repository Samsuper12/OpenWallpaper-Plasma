set(CMAKE_AUTOMOC ON)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE}  -O2 -ftree-vectorize -pipe -fPIC -ldl")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -Og -Wall -Wextra -pipe -fPIC -ldl")

set(DBUS_SOURCE
    Source/dbus_manager.cpp
    Source/dbus_manager.hpp
)

qt5_add_dbus_adaptor(DBUS_SOURCE DBus/dbus_manager.xml Source/dbus_manager.hpp DBusManager dbus_manager_adaptor)

add_subdirectory(Simple_parser)

add_library(${PROJECT_NAME} SHARED)

target_sources(${PROJECT_NAME}

PRIVATE
    Source/default_scene.cpp
    Source/openwallpaperplasma_plugin.cpp
    Source/render_manager.cpp
    Source/wdesktop.cpp
    
    Source/dll_loader.hpp
    Source/openwallpaperplasma_plugin.h
    Source/wdesktop.hpp
    Source/debug.hpp
    Source/default_scene.hpp
    Source/render_manager.hpp
    Source/abstract_render.hpp
    
    ${DBUS_SOURCE}
)

target_link_libraries(${PROJECT_NAME}
PRIVATE
    Qt5::Core
    Qt5::DBus
    Qt5::Quick
    Qt5::Qml
    OpenW::Parser
)

target_include_directories(${PROJECT_NAME}
PRIVATE
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
)

set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)

#don't forget about -D CMAKE_INSTALL_PREFIX=/usr
install(TARGETS ${PROJECT_NAME} DESTINATION ${KDE_INSTALL_QMLDIR}/OpenWallpaper/Plasma)
install(FILES Source/qmldir DESTINATION ${KDE_INSTALL_QMLDIR}/OpenWallpaper/Plasma)
install(FILES Source/abstract_render.hpp DESTINATION ${INCLUDE_INSTALL_DIR}/OpenWallpaper/QtOpenGL)

plasma_install_package(package org.openwallpaper.plasma wallpapers wallpaper) 
