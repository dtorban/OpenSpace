/*****************************************************************************************
 *                                                                                       *
 * OpenSpace                                                                             *
 *                                                                                       *
 * Copyright (c) 2014                                                                    *
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

#ifndef __OPENSPACEENGINE_H__
#define __OPENSPACEENGINE_H__

#include "interaction/interactionhandler.h"
#include "rendering/renderengine.h"
#include <ghoul/misc/configurationmanager.h>

namespace openspace {

class ScriptEngine;

class OpenSpaceEngine {
public:
    static void create(int argc, char** argv, int& newArgc, char**& newArgv);
    static void destroy();
    static OpenSpaceEngine& ref();

    bool initialize();

    ghoul::ConfigurationManager& configurationManager();
    InteractionHandler& interactionHandler();
    RenderEngine& renderEngine();

    // SGCT callbacks
    bool initializeGL();
    void preSynchronization();
    void postSynchronizationPreDraw();
    void render();
    void postDraw();
    void keyboardCallback(int key, int action);
    void mouseButtonCallback(int key, int action);
    void mousePositionCallback(int x, int y);
    void mouseScrollWheelCallback(int pos);

private:
    OpenSpaceEngine();
    ~OpenSpaceEngine();

    static OpenSpaceEngine* _engine;

    ghoul::ConfigurationManager* _configurationManager;
    InteractionHandler* _interactionHandler;
    RenderEngine* _renderEngine;
    ScriptEngine* _scriptEngine;
};

#define OsEng (openspace::OpenSpaceEngine::ref())

} // namespace openspace

#endif // __OPENSPACEENGINE_H__
