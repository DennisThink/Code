cmake_minimum_required(VERSION 3.10)
project(mimeParse)

SET(INC_BASE ../../include)

include_directories(${INC_BASE}/thirdparty/doctest/)
include_directories(${INC_BASE}/common/)
include_directories(${INC_BASE}/mime/)
include_directories(${INC_BASE}/common/util/)


SET(MIME_SOURCE MimeParseMain.cpp)
link_libraries(ssl crypto)
add_executable(mimeParse ${MIME_SOURCE})


SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/../../bin)  