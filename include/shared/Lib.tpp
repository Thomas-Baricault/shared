/*
 * Copyright (c) 2026-present Thomas Baricault
 *
 * SPDX-License-Identifier: MIT
 */


#pragma once


#include "Lib.hpp"


namespace tbaricault::shared
{

    template<typename T>
    T Lib::getSymbol(const std::string& name) const noexcept
    {
#ifdef _WIN32
        return (reinterpret_cast<T>(GetProcAddress(
            this->_handle,
            name.c_str()
        )));
#else
        return (reinterpret_cast<T>(dlsym(
            this->_handle,
            name.c_str()
        )));
#endif
    }

}
