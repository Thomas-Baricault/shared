/*
 * Copyright (c) 2026-present Thomas Baricault
 *
 * SPDX-License-Identifier: MIT
 */


#pragma once


#include <string>

#ifdef _WIN32
#include <windows.h>
#else
#include <dlfcn.h>
#endif


namespace tbaricault::shared
{

    /**
     * @brief Wrapper around a dynamically loaded shared library
     * 
     * Provides a platform-independent interface for loading shared libraries and retrieving exported symbols.
     */
    class Lib
    {

        public:

            /**
             * @brief Constructs an invalid library handle
             */
            Lib() noexcept = default;

            /**
             * @brief Copy construction is disabled
             */
            Lib(const Lib&) = delete;

            /**
             * @brief Move constructor
             * 
             * @param other Library handle to move
             */
            Lib(Lib&& other) noexcept;

            /**
             * @brief Loads a shared library
             * 
             * @param path Path to the shared library
             */
            Lib(const std::string& path);

            /**
             * @brief Destructor
             */
            virtual ~Lib() noexcept;

            /**
             * @brief Copy assignment is disabled
             */
            Lib& operator=(const Lib&) = delete;

            /**
             * @brief Move assignement operator
             * 
             * @param other Library handle to move
             * 
             * @return Reference to this library handle
             */
            Lib& operator=(Lib&& other) noexcept;

            /**
             * @brief Returns whether the library handle is in a valid state
             */
            explicit operator bool() const noexcept;

            /**
             * @brief Checks whether the object represents the current process
             * 
             * @return `true` if symbols are resolved from the current executable instead of an external shared library, `false` otherwise
             */
            bool isSelf() const noexcept;

            /**
             * @brief Returns the library path
             * 
             * @return Path of the loaded library
             */
            const std::string& getPath() const noexcept;

            /**
             * @brief Retrieves an exported symbol
             * 
             * @tparam T Symbol type
             * 
             * @param name Exported symbol name
             * 
             * @return The requested symbol cast to `T*`
             */
            template<typename T>
            T getSymbol(const std::string& name) const noexcept;


        private:

            /**
             * @brief Whether the library handle represents the current process
             */
            bool _self = false;

#ifdef _WIN32
            /**
             * @brief Library handle
             */
            HMODULE _handle = nullptr;
#else
            /**
             * @brief Library handle
             */
            void* _handle = nullptr;
#endif

            /**
             * @brief Library path
             */
            std::string _path;

    };

}


#include "Lib.tpp"
