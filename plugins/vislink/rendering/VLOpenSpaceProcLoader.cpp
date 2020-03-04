#include "rendering/VLOpenSpaceProcLoader.h"
#include <openspace/engine/windowdelegate.h>
#include "vislinkmodule.h"

namespace openspace {

	vislink::VLProc VLOpenSpaceProcLoader::getProc(const char* name) {
		WindowDelegate& windowDelegate = *static_cast<WindowDelegate*>((static_cast<VisLinkModule*>(module)->getPluginInfo().windowDelegate));
		std::cout << "Using windows delegate" << std::endl;
		return windowDelegate.openGLProcedureAddress(name);
	}

}