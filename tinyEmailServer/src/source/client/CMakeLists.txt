cmake_minimum_required(VERSION 3.10)
project(EmailClient)
SET(INC_BASE ../../include)
include_directories(${INC_BASE}/thirdparty/asio/)
include_directories(${INC_BASE}/thirdparty/)
include_directories(${INC_BASE}/thirdparty/json11/)
include_directories(${INC_BASE}/common/)
include_directories(${INC_BASE}/common/util/)
include_directories(${INC_BASE}/proto/)
include_directories(${INC_BASE}/proto/code/)
include_directories(${INC_BASE}/proto/imap/)
include_directories(${INC_BASE}/proto/pop3/)
include_directories(${INC_BASE}/proto/smtp/)
include_directories(${INC_BASE}/network/)
include_directories(${INC_BASE}/network/tcpClient/)
include_directories(${INC_BASE}/database/)
if(WIN32)
else()
link_libraries(pthread)
endif()
SET(C_TCP_CLIENT ${INC_BASE}/network/tcpClient/CTcpClient.h ${INC_BASE}/network/tcpClient/CTcpClient.cpp)
SET(C_EMAIL    CEmailClient.h CEmailClient.cpp)

SET(PROTO_FILE 
${INC_BASE}/common/util/ProtoUtil.cpp
${INC_BASE}/proto/code/CProtoCode.h
${INC_BASE}/common/util/ProtoUtil.h
${INC_BASE}/proto/smtp/CProtoCmd.h ${INC_BASE}/proto/smtp/CProtoCmd.cpp
${INC_BASE}/proto/smtp/CClientSmtpProto.h ${INC_BASE}/proto/smtp/CClientSmtpProto.cpp
${INC_BASE}/proto/pop3/CPop3Proto.h ${INC_BASE}/proto/pop3/CPop3Proto.cpp
${INC_BASE}/proto/pop3/CPop3ProtoCmd.h ${INC_BASE}/proto/pop3/CPop3ProtoCmd.cpp

${INC_BASE}/proto/imap/CClientImapProto.h ${INC_BASE}/proto/imap/CClientImapProto.cpp
${INC_BASE}/proto/imap/CImapProtoCmd.h ${INC_BASE}/proto/imap/CImapProtoCmd.cpp
${INC_BASE}/common/CEmailProtoInterface.h
               )
SET(SOURCE_FILE main.cpp ${C_TCP_CLIENT} ${C_EMAIL} ${PROTO_FILE})
add_executable(EmailClient ${SOURCE_FILE})
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/../../bin)
