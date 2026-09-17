/*
 * Copyright (c) 2026-present Thomas Baricault
 *
 * SPDX-License-Identifier: MIT
 */


#include "shared/Lib.hpp"


namespace tbaricault::shared
{

    Lib::Lib(const std::string& path)
    {
        const char* ptr = path.c_str();
        if (path.empty())
        {
            this->_self = true;
            ptr = nullptr;
        }
        else
        {
#ifdef _WIN32
            this->_handle = LoadLibraryA(ptr);
#else
            this->_handle = dlopen(ptr, RTLD_NOW);
#endif
            this->_path = path;
        }
        return;
    }

    Lib::Lib(Lib&& other) noexcept
        : _self(other._self)
        , _handle(other._handle)
        , _path(std::move(other._path))
    {
        other._self = false;
        other._handle = nullptr;
    }

    Lib::~Lib() noexcept
    {
#ifdef _WIN32
        FreeLibrary(this->_handle);
#else
        dlclose(this->_handle);
#endif
        return;
    }

    Lib& Lib::operator=(Lib&& other) noexcept
    {
        if (&other == this)
            return (*this);
        if (!this->_self && this->_handle)
        {
#ifdef _WIN32
            FreeLibrary(this->_handle);
#else
            dlclose(this->_handle);
#endif
        }
        this->_self = other._self;
        this->_handle = other._handle;
        this->_path = std::move(other._path);
        other._self = false;
        other._handle = nullptr;
        return (*this);
    }

    Lib::operator bool() const noexcept
    {
        return (this->_self || this->_handle != nullptr);
    }

    bool Lib::isSelf() const noexcept
    {
        return (this->_self);
    }

    const std::string& Lib::getPath() const noexcept
    {
        return (this->_path);
    }

}
