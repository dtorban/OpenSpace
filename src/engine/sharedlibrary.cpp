/*****************************************************************************************
 *                                                                                       *
 * OpenSpace                                                                             *
 *                                                                                       *
 * Copyright (c) 2014-2020                                                               *
 *                                                                                       *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this  *
 * software and associated documentation files (the "Software"), to deal in the Software *
 * without restriction, including without limitation the rights to use, copy, modify,    *
 * merge, publish, distribute, sublicense, and/or sell copies of the Software, and to    *
 * permit persons to whom the Software is furnished to do so, subject to the following   *
 * conditions:                                                                           *
 *                                                                                       *
 * The above copyright notice and this permission notice shall be included in all copies *
 * or substantial portions of the Software.                                              *
 *                                                                                       *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,   *
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A         *
 * PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT    *
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF  *
 * CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE  *
 * OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                                         *
 ****************************************************************************************/

#include <iostream>
#include <openspace/engine/sharedlibrary.h>

namespace openspace {

SharedLibrary::SharedLibrary(const std::string &filePath, bool autoLoad) : _filePath(filePath), _isLoaded(false) {
    if (autoLoad)
    {
        load();
    }
}

SharedLibrary::~SharedLibrary() {
    unload();
}

void SharedLibrary::load() {
    if (!_isLoaded)
    {
        const char* error;
#if defined(WIN32)
        _lib = LoadLibraryA(_filePath.c_str());
#else
        dlerror();
        _lib = dlopen(_filePath.c_str(), RTLD_NOW);//RTLD_LAZY);
        error = dlerror();
#endif

        if (!_lib) {
            //MinVR::Logger::getInstance().assertMessage(false, "Could not load library: " + _filePath + " - " + error);
            return;
        }

        _isLoaded = true;
    }
}

void SharedLibrary::unload() {
    if (_isLoaded)
    {
        const char* error;
#if defined(WIN32)
        BOOL result = FreeLibrary(_lib);
#else
        dlerror();
        int result = dlclose(_lib);
        error = dlerror();
#endif
        if(result != 0) {
            //MinVR::Logger::getInstance().assertMessage(false, "Could not unload library: " + _filePath + " - " + error);
            return;
        }

        _isLoaded = false;
    }
}

void* SharedLibrary::loadSymbolInternal(const std::string &functionName) {
    if (_isLoaded)
    {
#if defined(WIN32)
        FARPROC symbol =GetProcAddress(_lib, functionName.c_str());
        if (!symbol) {
            //MinVR::Logger::getInstance().assertMessage(false, "Cannot load symbol: " + functionName + " - " + "");
            std::cout << "Cannot load symbol: " + functionName + " - " + "" << std::endl;

            return NULL;
        }

        return symbol;
#else
        void* symbol = (void*) dlsym(_lib, functionName.c_str());
        const char* dlsym_error = dlerror();
        if (dlsym_error) {
            std::cout << "Cannot load symbol: " + functionName + " - " + dlsym_error << std::endl;
            //MinVR::Logger::getInstance().assertMessage(false, "Cannot load symbol: " + functionName + " - " + dlsym_error);
            dlerror();

            return NULL;
        }

        return symbol;
#endif

    }

    return NULL;
}


} // namespace openspace
