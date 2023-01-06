# Copyright (C) 2014 MediaSift Ltd.
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

#
# Process ragel files
#
cmake_minimum_required(VERSION 3.10)
project(httplib)
if(WIN32)
	add_compile_options("/std:c++14")
else()
	add_compile_options("-std=c++14")
	add_compile_options(-Wno-implicit-fallthrough)
endif()

#
# Locate project sources
#
FILE (GLOB_RECURSE served_SRCS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp)
FILE (GLOB_RECURSE served_HDRS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp)

#
# Locate test sources and remove from project sources
#
FILE (GLOB_RECURSE test_SRCS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/*.test.cpp)
LIST (REMOVE_ITEM served_SRCS ${test_SRCS})

#
# Configure common project settings
#
SET (served_LIBS ${Boost_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
SET (served_BIN ${PROJECT_NAME})

IF (NOT DEFINED SERVED_BUILD_SHARED)
	IF (CMAKE_CROSSCOMPILING)
		SET(SERVED_BUILD_SHARED 0)
	ELSE (CMAKE_CROSSCOMPILING)
		SET(SERVED_BUILD_SHARED 1)
	ENDIF (CMAKE_CROSSCOMPILING)
ENDIF (NOT DEFINED SERVED_BUILD_SHARED)

IF (NOT DEFINED SERVED_BUILD_STATIC)
	SET(SERVED_BUILD_STATIC 1)
ENDIF (NOT DEFINED SERVED_BUILD_STATIC)

#
# Static lib build rules
#
IF (SERVED_BUILD_STATIC)
	ADD_LIBRARY (httplib STATIC ${served_SRCS} ${served_RLSOURCES})
	TARGET_LINK_LIBRARIES (httplib ${served_LIBS})
	SET_TARGET_PROPERTIES (httplib PROPERTIES VERSION "${APPLICATION_VERSION_MAJOR}.${APPLICATION_VERSION_MINOR}" OUTPUT_NAME ${served_BIN} CLEAN_DIRECT_OUTPUT 1)
	INSTALL (TARGETS httplib DESTINATION lib)
ENDIF (SERVED_BUILD_STATIC)

#
# Shared object build rules
#
#IF (SERVED_BUILD_SHARED)
#	ADD_LIBRARY (${PROJECT_NAME} SHARED ${served_SRCS} ${served_RLSOURCES})
#	TARGET_LINK_LIBRARIES (${PROJECT_NAME} ${served_LIBS})
#	SET_TARGET_PROPERTIES (${PROJECT_NAME} PROPERTIES VERSION "${APPLICATION_VERSION_MAJOR}.${APPLICATION_VERSION_MINOR}" OUTPUT_NAME ${served_BIN} CLEAN_DIRECT_OUTPUT 1)
#	INSTALL (TARGETS ${PROJECT_NAME} DESTINATION lib)
#ENDIF (SERVED_BUILD_SHARED)

#
# Configure common test settings
#
SET (test_LIBS ${Boost_LIBRARIES} ${PROJECT_NAME})
SET (test_HDRS "../test/catch.cpp")

#
# Test build rules
#
IF (SERVED_BUILD_TESTS)
	IF (NOT CMAKE_CROSSCOMPILING)
		LINK_DIRECTORIES (${MAINFOLDER}/lib)
		FOREACH (T_FILE ${test_SRCS})
			GET_FILENAME_COMPONENT (T_NAME ${T_FILE} NAME_WE)
			SET (T_NAME "${T_NAME}_test")
			ADD_EXECUTABLE (${T_NAME} ${T_FILE} ${test_HDRS})
			TARGET_LINK_LIBRARIES (${T_NAME} ${test_LIBS})
			ADD_TEST (${T_NAME} ${MAINFOLDER}/bin/${T_NAME})
		ENDFOREACH (T_FILE ${test_SRCS})
	ENDIF (NOT CMAKE_CROSSCOMPILING)
ENDIF (SERVED_BUILD_TESTS)

#
# Install target
#
FOREACH (H_FILE ${served_HDRS})
	SET (H_INSTALL_DIR "served")
	STRING (REGEX MATCH "(.*)[/\\]" DIR ${H_FILE})
	INSTALL (FILES ${H_FILE} DESTINATION include/${H_INSTALL_DIR}/${DIR})
ENDFOREACH (H_FILE ${served_HDRS})
