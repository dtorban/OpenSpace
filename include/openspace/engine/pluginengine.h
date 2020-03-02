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

#ifndef __OPENSPACE_CORE___PLUGINENGINE___H__
#define __OPENSPACE_CORE___PLUGINENGINE___H__

#include <vector>
#include <openspace/util/openspacemodule.h>
#include <openspace/engine/sharedlibrary.h>

namespace openspace {

class PluginEngine {
public:
	PluginEngine(const std::vector<std::string>& folders);
	~PluginEngine();

	std::vector<OpenSpaceModule*> getModules() { return modules; }
private:
	std::vector<std::string> listDirectory(const std::string& path, bool directories, std::string extension = "");
	void loadPlugins(const std::string& pluginDir);
	void loadPlugin(const std::string& filePath);

	std::vector<SharedLibrary*> libraries;
	std::vector<OpenSpaceModule*> modules;
};

} // namespace openspace

#endif