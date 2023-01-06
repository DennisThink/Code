cmake_minimum_required(VERSION 3.10)
project(serverTest)

SET(INC_BASE ../../include)

include_directories(${INC_BASE}/thirdparty/doctest/)
include_directories(${INC_BASE}/common/)
include_directories(${INC_BASE}/common/util/)

SET(LOCAL_SOURCE_FILE 
${INC_BASE}/common/util/ProtoUtil.h
${INC_BASE}/common/util/ProtoUtil.cpp
LocalServerTest.cpp)

SET(NET_SOURCE_FILE 
${INC_BASE}/common/util/ProtoUtil.h
${INC_BASE}/common/util/ProtoUtil.cpp
                NetServerTest.cpp)

SET(NO_NET_SOURCE_FILE 
${INC_BASE}/common/util/ProtoUtil.h
${INC_BASE}/common/util/ProtoUtil.cpp
                noNetTest.cpp)


link_libraries(ssl crypto)
add_executable(localServerTest ${LOCAL_SOURCE_FILE})
add_executable(netServerTest ${NET_SOURCE_FILE})
add_executable(noNetTest ${NO_NET_SOURCE_FILE})

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/../../bin)  