/*****************************************************************************************
 *                                                                                       *
 * OpenSpace                                                                             *
 *                                                                                       *
 * Copyright (c) 2014-2019                                                               *
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


#include<iostream>
#include "testpluginmodule.h"

namespace openspace {

TestPluginModule::TestPluginModule(const std::string& path) : OpenSpaceModule(Name), path(path) {}

void TestPluginModule::internalInitialize(const ghoul::Dictionary&) {
	std::cout << "Initialize test plugin" << std::endl;
	//exit(0);
    //auto fRenderable = FactoryManager::ref().factory<Renderable>();
    //ghoul_assert(fRenderable, "No renderable factory existed");
    //fRenderable->registerClass<RenderableToyVolume>("RenderableToyVolume");
}

} // namespace openspace

#if defined(WIN32)
#define OPENSPACE_API __declspec(dllexport)
#else
#define OPENSPACE_API
#endif

extern "C" {

OPENSPACE_API openspace::OpenSpaceModule* createOpenSpaceModule(const char* modulePath) {
	std::cout << "Does it work?" << std::endl;
	//exit(0);
	std::string path(modulePath);
	return new openspace::TestPluginModule(path);
}

}