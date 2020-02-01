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
 * Copyright (C) 2014-2020 by Kyle Nusbaum KyleJNusbaum@gmail.com 
 * Copyright (C) 2020- by Michael Skorokhodov bakaprogramm29@gmail.com
 */

#ifndef DLL_LOADER_HPP
#define DLL_LOADER_HPP

// Author: https://github.com/knusbaum/CPP-Dynamic-Class-Loading
// also check https://www.linuxjournal.com/article/3687

#include <memory>
#include <string>
#include <dlfcn.h>

#include "debug.hpp"

template<class T>
class DllLoader
{
public:
    DllLoader(const std::string& path);
    ~DllLoader();
    
    std::shared_ptr<T> loadClass();
   
private:
    struct Object{
        typename T::create_t* create = nullptr;
        typename T::destroy_t* destroy = nullptr;
        
        ~Object();
        void* handle = nullptr;
        
        bool open(const std::string& path);
        void close();
        
    };
private:
    std::string libPath;
    std::shared_ptr<Object> libClass;
};

#include "dll_loader.cpp"

#endif // DLL_LOADER_HPP
