##########################################################################################
#                                                                                        #
# OpenSpace                                                                              #
#                                                                                        #
# Copyright (c) 2014-2018                                                                #
#                                                                                        #
# Permission is hereby granted, free of charge, to any person obtaining a copy of this   #
# software and associated documentation files (the "Software"), to deal in the Software  #
# without restriction, including without limitation the rights to use, copy, modify,     #
# merge, publish, distribute, sublicense, and/or sell copies of the Software, and to     #
# permit persons to whom the Software is furnished to do so, subject to the following    #
# conditions:                                                                            #
#                                                                                        #
# The above copyright notice and this permission notice shall be included in all copies  #
# or substantial portions of the Software.                                               #
#                                                                                        #
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,    #
# INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A          #
# PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT     #
# HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF   #
# CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE   #
# OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                                          #
##########################################################################################

set(CMAKE_FRAMEWORK_DIR ${CMAKE_SOURCE_DIR}/support/cmake/framework)

if(NOT EXISTS ${CMAKE_FRAMEWORK_DIR})
execute_process(
		#COMMAND git clone ${PROJECT_SOURCE_DIR}/.. ${CMAKE_FRAMEWORK_DIR}
		COMMAND git clone https://github.com/dtorban/cmake_fw.git ${CMAKE_FRAMEWORK_DIR}
)
endif()

include(${OPENSPACE_CMAKE_EXT_DIR}/module_definition.cmake)

set(HEADER_FILES
  ${CMAKE_CURRENT_SOURCE_DIR}/vislinkmodule.h
  ${CMAKE_CURRENT_SOURCE_DIR}/rendering/renderabletest.h
)
source_group("Header Files" FILES ${HEADER_FILES})

set(SOURCE_FILES
  ${CMAKE_CURRENT_SOURCE_DIR}/vislinkmodule.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/rendering/renderabletest.cpp
)
source_group("Source Files" FILES ${SOURCE_FILES})

include_directories(.)

# --------------------- Dependencies -----------------------
include(${CMAKE_FRAMEWORK_DIR}/project/project.cmake)

add_external(VisLinkLib
	GIT_REPOSITORY https://github.com/dtorban/VisLink.git
	LIB_NAME VisLink
)

set(DEP_LINK_DIRS ${DEP_LINK_DIRS} ${external_dir}/VisLinkLib/install/lib)
message(${external_dir}/VisLinkLib/install/lib)

include(${external_dir}/OpenGL/OpenGL.cmake)
useOpenGL()
useGLEW()

# --------------------- Executable -----------------------

link_directories(${DEP_LINK_DIRS})

create_new_plugin(
  "VisLink"
  vislink_module
  SHARED
  ${HEADER_FILES} ${SOURCE_FILES} ${DEP_SOURCEFILES}
)

set(PROJECT_NAME openspace-module-vislink)

addStandardInfo(PRIVATE)
