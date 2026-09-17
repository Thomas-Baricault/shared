/*
 * Copyright (c) 2026-present Thomas Baricault
 *
 * SPDX-License-Identifier: MIT
 */


#pragma once


#ifdef _WIN32
    #define EXPORT extern "C" __declspec(dllexport)
    #define IMPORT extern "C" __declspec(dllimport)
#else
    #define EXPORT extern "C" __attribute__((visibility("default")))
    #define IMPORT EXPORT
#endif
