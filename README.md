
# OpenWallpaper Plasma - Plugin for [KDE Plasma][kde_link]

This is the complete source code and builds instructions for the OpenWallpaper Plasma. We recommend you to use the [OpenWallpaper Manager][wallpaper_manager_link] to have the best user experience. Video demonstration: [YouTube][youtube_plasma]

## Description

OpenWallpaper Plasma is a plugin for [KDE Plasma][kde_link] providing additional possibilities for desktop wallpaper.

Available options:

* Play [QtOpenGL][qt_opengl] scene with mouse events and music
* Play GIFs with music 
* Play Video

The main feature of each package is that each wallpaper contains information about the package itself, about the author and a brief description. Each package will work on different computers with the same plugin version. At the moment, the KDE Plasma support is implemented only, other DEs and operating systems will become available in future updates.

## Examples

There are several demonstration packages available now. You can create your own and publish it on [reddit][reddit_link] community page.

* [Blink][blink] - QtOpenGL wallpaper
* [Winter][winter] - GIF with the music
* [Sunset][sunset] - Video

## Roadmap

* [Lua][lua_wiki] scene engine
* Cross platforming
* OpenWallpaper in different DEs
* HTML wallpaper type

If you have any suggestions or feedback, feel free to email us.

## Build instructions

The following packages must be installed from the official repositories for all distributives:

* [GCC][gcc_link]
* [CMake 3.10][cmake]
* [Gstreamer][gst_install]
* [Extra-cmake-modules][ecm]

The following are the most popular distributives and the name of the packages that you need to install. If you are a user of a little-known distributive, that is not listed below, we recommend you to find and install analogs of these packages.

ATTENTION: Your system should be updated to the last release.
 
First you need download develop dependencies:
 
### Ubuntu

```console
# sudo apt install build-essential libkf5plasma-dev qtdeclarative5-dev
```
### Fedora

```console
# sudo dnf install kf5-plasma-devel qt5-qtdeclarative-devel
```
### Arch

```console
# sudo pacman -S kdeclarative
```

### Build and installing

Now when all the necessary packages are installed, you can proceed with the compilation and installation.

Go to the Open Wallpaper Plasma project directory and run the terminal. Now you should create a folder and enter it.

```console
# mkdir build && cd build
```
Run CMake with the following parameters:

```console
# cmake -D CMALE_INSTALL_PREFIX=/usr ..
```
CMake can show an error if the system doesn’t have the necessary dependencies.

Start building the project:

```console
# cmake --build . 
```
if you have more than 2 CPU cores or threads you can write `-- -jХ` where X will be a number of cores/threads. Example: `cmake --build. -- -j4` 

Read CMake output and if the compilation was successful, you can install a plugin in the system directory with the following command:

```console
# sudo make install
```

Success! Now you can run a plugin in Plasma Desktop Settings. Attention: the plugin doesn’t have any packages included. See the Examples above.

## System requirements

### RAM
At that moment, the QML widgets have some bugs with deleting unnecessary data. Don't worry: that not more than 1 GB of RAM. We don't know why (Maybe Plasma do not ready for [Qt Multimedia][qt_miltimedia]). Fix in future updates.

### CPU
The processor can allocate 2-5 percent for a plugin. The value might be different on old or new processors.

### GPU
We detect some leaks of RAM in the Nvidia cards with an open driver. We recommend to use only proprietary drivers version 390xx or greater. On AMD GPU all fine without any problems. Send review if you use intel integrated graphics. 

### QtOpenGL
The current OpenGL version is 3.1. Need more testing information with different hardware and drivers.

Attention: QtOpenGL isn't regular OpenGL, because of using the QOpenGLShaderProgram for grabbing and compiling shaders. But different not so critical.

About QtOpenGL read in [Qt documentation][qt_opengl].

## Third-party

* [CMake 3.10+][cmake]
* Qt 5.10+ ([LGPL](http://doc.qt.io/qt-5/lgpl.html))

Also in the project uses materials and ideas of that projects:

* [CPP-Dynamic-Class-Loading][cpp_dcl] - dll_loader.cpp/hpp.
* [Smart Video Wallpaper ][svw] - great idea of a double player.

## Support

Any help in the current moment will be very helpful. If you want to help, you can pick something of proposed options:

* Involvement with the project development
* Creating the wiki pages with needed (as you think) information for users
* Send an email with your idea
* Share information about that project
* Material help. [Donation Alerts][donate_link] and [Patreon][patreon_link]. Also, you can send hardware for testing, we'll be so thankful to you

## Acknowledgments

* Andrew Origin - help with README
* [Arch linux][telegram_arch_ru] comminity on Telegram - good advices about Linux
* [KDE Plasma][telegram_kde_ru] community on Telegram - ideas
* [Bogdan Kachura][telegram_bogdan] - help with reddit

## Authors

* [Michael Skorohkodov][michael_gh_link] - bakaprogramm@gmail.com, [twitter][michael_twitter]
* [Felix Lewandowski][felix_gh_link] - acidicmercury8@gmail.com


[//]: # (LINKS)
[cmake]: https://cmake.org/
[ecm]: https://api.kde.org/ecm/manual/ecm.7.html#
[wallpaper_manager_link]: https://github.com/Samsuper12/OpenWallpaper-Manager
[kde_link]: https://kde.org/plasma-desktop
[qt]: https://www.qt.io/
[qt_opengl]: https://doc.qt.io/qt-5/qopenglfunctions.html
[gst_install]: https://gstreamer.freedesktop.org/documentation/installing/on-linux.html?gi-language=c
[gcc_link]: https://gcc.gnu.org/
[qt_miltimedia]: https://doc.qt.io/qt-5/qtmultimedia-qmlmodule.html
[license]: LICENSE

[blink]: https://github.com/Samsuper12/Blink
[winter]: https://github.com/Samsuper12/Winter
[sunset]: https://github.com/Samsuper12/Sunset
[lua_wiki]: https://en.wikipedia.org/wiki/Lua_(programming_language)
[cpp_dcl]: https://github.com/knusbaum/CPP-Dynamic-Class-Loading
[svw]: https://store.kde.org/p/1316299/
[donate_link]: https://www.donationalerts.com/r/redbakas
[patreon_link]: https://www.patreon.com/Samsuris
[michael_twitter]: https://twitter.com/Samsuris4
[michael_gh_link]: https://github.com/ADD_LINK
[felix_gh_link]: https://github.com/acidicMercury8
[reddit_link]: https://www.reddit.com/r/OpenWallpaper/
[telegram_arch_ru]: https://t.me/ArchLinuxChatRU
[telegram_kde_ru]: https://t.me/kde_ru
[telegram_bogdan]: https://t.me/desu_pair
[youtube_plasma]: https://youtu.be/W6t2PojD7X4


