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

#ifndef __OPENSPACE_CORE___SHAREDLIBRARY___H__
#define __OPENSPACE_CORE___SHAREDLIBRARY___H__

#include <string>
#if defined(WIN32)
	#include <Windows.h>
	typedef HMODULE LibHandleType;
#else
	#include <dlfcn.h>
	typedef void * LibHandleType;
#endif

namespace openspace {

class SharedLibrary {
public:
	SharedLibrary(const std::string &filePath, bool autoLoad = true);
	virtual ~SharedLibrary();

	void load();
	void unload();

	bool isLoaded() {
		return _isLoaded;
	}

	template<typename TSig>
	TSig * loadSymbol(const std::string &functionName)
	{
		return reinterpret_cast<TSig *>(loadSymbolInternal(functionName));
	}

protected:
	void* loadSymbolInternal(const std::string &functionName);


private:
	std::string _filePath;
	bool _isLoaded;
	LibHandleType _lib;
};

} // namespace openspace

#endif