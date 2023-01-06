cmake_minimum_required(VERSION 3.10)
project(emailServer)
SET(INC_BASE ../../include)
include_directories(${INC_BASE}/thirdparty/asio/)
include_directories(${INC_BASE}/thirdparty/)
include_directories(${INC_BASE}/thirdparty/json11/)
include_directories(${INC_BASE}/common/)
include_directories(${INC_BASE}/common/config/)
include_directories(${INC_BASE}/common/util/)
include_directories(${INC_BASE}/proto/)
include_directories(${INC_BASE}/proto/code/)
include_directories(${INC_BASE}/proto/smtp/)
include_directories(${INC_BASE}/proto/pop3/)
include_directories(${INC_BASE}/proto/imap/)
include_directories(${INC_BASE}/database/)
include_directories(.)
include_directories(./served/)
include_directories(${INC_BASE}/network/)
include_directories(${INC_BASE}/network/tcpClient/)
include_directories(./handler/)
SET(SERVED_BUILD_STATIC 1)
add_subdirectory(./served/)
if(WIN32)
else()
link_libraries(pthread)
endif()
SET(EMAIL_SERVER CEmailServer.h CEmailServer.cpp 
                 CTcpServer.h
                 CHttpMailServer.h  CHttpMailServer.cpp
                 ./handler/CSmtpServerHandler.h  
                 ./handler/CSmtpServerHandler.cpp
                 ./handler/CImapServerHandler.h  
                 ./handler/CImapServerHandler.cpp
                 ./handler/CPop3ServerHandler.h  
                 ./handler/CPop3ServerHandler.cpp

                 ${INC_BASE}/network/tcpClient/CTcpClient.h
                 ${INC_BASE}/network/tcpClient/CTcpClient.cpp
                 ${INC_BASE}/proto/smtp/CClientSmtpProto.h  
                 ${INC_BASE}/proto/smtp/CClientSmtpProto.cpp
                 ${INC_BASE}/proto/smtp/CServerSmtpProto.h  
                 ${INC_BASE}/proto/smtp/CServerSmtpProto.cpp
                 ${INC_BASE}/proto/pop3/CPop3ServerProto.h  
                 ${INC_BASE}/proto/pop3/CPop3ServerProto.cpp
                 ${INC_BASE}/proto/imap/CServerImapProto.h  
                 ${INC_BASE}/proto/imap/CServerImapProto.cpp
                 ${INC_BASE}/proto/imap/CImapProtoCmd.h  
                 ${INC_BASE}/proto/imap/CImapProtoCmd.cpp
                 ${INC_BASE}/proto/pop3/CPop3ProtoCmd.h  
                 ${INC_BASE}/proto/pop3/CPop3ProtoCmd.cpp
                 ${INC_BASE}/proto/smtp/CProtoCmd.h  
                 ${INC_BASE}/proto/smtp/CProtoCmd.cpp
                 ${INC_BASE}/common/util/ProtoUtil.h  
                 ${INC_BASE}/common/util/ProtoUtil.cpp
                 ${INC_BASE}/common/config/user_info.cpp
                 # DataBase
                 ${INC_BASE}/database/DataBaseInterface.h
                 ${INC_BASE}/database/CMemDataBase.h
                 ${INC_BASE}/database/CMemDataBase.cpp
                 )
             
link_directories(./lib/)
SET(SOURCE_FILE ${EMAIL_SERVER} main.cpp )
link_libraries(httplib)
add_executable(emailServer ${SOURCE_FILE})
add_dependencies(emailServer httplib)
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/../../bin) 