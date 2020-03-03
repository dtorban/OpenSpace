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

#include <openspace/engine/pluginengine.h>
#include <openspace/util/plugininfo.h>

#if defined(WIN32)
#include <Windows.h>
#else
#include <dirent.h> 
#endif

namespace openspace {

PluginEngine::PluginEngine(const std::vector<std::string>& folders) {

	for (int f = 0; f < folders.size(); f++) {
		std::vector<std::string> pluginDirs = listDirectory(folders[f], true);

		for (int i = 0; i < pluginDirs.size(); i++) {
			//if (pluginDirs[f].find(".plugin") != std::string::npos) {
				std::string pluginDir = folders[f] + "/" + pluginDirs[i];

				loadPlugins(pluginDir);
			//}
		}
	}

	//exit(0);
}

PluginEngine::~PluginEngine() {
	for (int f = 0; f < libraries.size(); f++) {
		delete libraries[f];
	}
}

void PluginEngine::loadPlugins(const std::string& pluginDir) {

	//std::string dir = "/lib/";
	std::string dir = "";

#if defined(WIN32)
	//dir = "/bin/";
	std::string ext = ".dll";
#elif defined(__APPLE__)
	std::string ext = ".dylib";
#else
	std::string ext = ".so";
#endif

	std::string libDir = pluginDir + dir;

	std::vector<std::string> libs = listDirectory(libDir, false, ext);
	for (int i = 0; i < libs.size(); i++) {
		loadPlugin(libDir, libs[i]);
	}


}

void PluginEngine::loadPlugin(const std::string& path, const std::string& name) {

	SharedLibrary* lib = new SharedLibrary(path + "/" + name, true);
	if (lib->isLoaded())
	{
		typedef OpenSpaceModule* load_t(PluginInfo);
		load_t* createModule = lib->loadSymbol<load_t>("createOpenSpaceModule");
		if (createModule == NULL)
		{
			delete lib;
			return;
		}

		PluginInfo pluginInfo;
		pluginInfo.factoryManager = &FactoryManager::ref();
		pluginInfo.path = path;

		OpenSpaceModule* pluginModule = createModule(pluginInfo);
		int countRegistered = 0;
		if (pluginModule != NULL) {
			countRegistered++;
		}

		if (countRegistered > 0) {
			modules.push_back(pluginModule);
			libraries.push_back(lib);
		}
		else {
			delete lib;
		}
	}
	else {
		delete lib;
	}
}

std::vector<std::string> PluginEngine::listDirectory(const std::string& path, bool directories, std::string extension) {
	std::vector<std::string> files;

	std::string searchString = std::string("*") + extension;

#if defined(WIN32)
	char search_path[300];
	if (path[path.size() - 1] == '/') {
		sprintf(search_path, "%s%s", path.c_str(), searchString.c_str());
	}
	else {
		sprintf(search_path, "%s/%s", path.c_str(), searchString.c_str());
	}
	WIN32_FIND_DATA fd;
	HANDLE hFind = ::FindFirstFile(search_path, &fd);
	if (hFind != INVALID_HANDLE_VALUE) {
		do {
			if (directories && (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
				files.push_back(fd.cFileName);
			}
			else if (((fd.dwFileAttributes & FILE_ATTRIBUTE_NORMAL) || (fd.dwFileAttributes & FILE_ATTRIBUTE_ARCHIVE)))
			{
				files.push_back(fd.cFileName);
			}
		} while (::FindNextFile(hFind, &fd));
		::FindClose(hFind);
	}
	else {
		/* could not open directory */
		//perror ("");
	}
#else
	DIR *dir;
	struct dirent *ent;
	if ((dir = opendir(path.c_str())) != NULL) {
		/* print all the files and directories within directory */
		while ((ent = readdir(dir)) != NULL) {
			if (directories && ent->d_type == DT_DIR)
			{
				files.push_back(ent->d_name);
			}
			else if (ent->d_type == DT_REG)
			{
				std::string fileName = ent->d_name;
				if (searchString == "*" || fileName.find(extension) != std::string::npos) {
					files.push_back(ent->d_name);
				}
			}
		}
		closedir(dir);
	}
	else {
		/* could not open directory */
		//perror ("");
	}
#endif

	return files;
}


} // namespace openspace
