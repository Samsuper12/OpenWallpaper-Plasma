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
 * 
 */

template<class T>
DllLoader<T>::DllLoader(const std::string& path) 
    : libPath(path)
{
    libClass = std::make_shared<Object>();
}

template<class T>
DllLoader<T>::~DllLoader()
{
}

template<class T>
bool DllLoader<T>::Object::open(const std::string& path)
{
    handle = dlopen(path.c_str(), RTLD_NOW);
    if (!handle) {
        LOG(dlerror())
        return false;
    }
    
    dlerror();
    
    create = (typename T::create_t*) dlsym(handle, "create");
    if (!create) {
        LOG(dlerror())
        return false;
    }
    
    dlerror();
    
    destroy = (typename T::destroy_t*) dlsym(handle, "destroy");
    if (!destroy) {
        LOG(dlerror())
        return false;
    }
    
    return true;
}


template<class T>
void DllLoader<T>::Object::close()
{
    dlclose(handle);
    create = nullptr;
    destroy = nullptr;
}

template<class T>
std::shared_ptr<T> DllLoader<T>::loadClass()
{
    if (!libClass->create || !libClass->destroy) {
        if (!libClass->open(libPath)) {
            return std::shared_ptr<T>(nullptr);
        }
    }

    std::shared_ptr<Object> ref = libClass;
    return std::shared_ptr<T>(libClass->create(), [ref] (T*t) {
        ref->destroy(t);
    });    
}

template<class T>
DllLoader<T>::Object::~Object()
{
    close();
}
