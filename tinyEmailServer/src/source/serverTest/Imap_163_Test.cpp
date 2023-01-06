#ifndef _IMAP_163_TEST_CPP_
#define _IMAP_163_TEST_CPP_
#include "ServerTest.h"
const std::string strImapRecvOnConnect="* OK Coremail System IMap Server Ready(163com[10774b260cc7a37d26d71b52404dcf5c])\r\n";

const std::string strImapRecvCapability="* CAPABILITY IMAP4rev1 XLIST SPECIAL-USE ID LITERAL+ STARTTLS XAPPLEPUSHSERVICE UIDPLUS X-CM-EXT-1\r\n \
C1 OK CAPABILITY completed\r\n";

const std::string strImapRecvLoginSucceed="C3 OK LOGIN completed\r\n";
//Send
const std::string strImapSendC1_CAPABILITY="C1 CAPABILITY\r\n";
const std::string strImapSendLogin="C3 LOGIN dennismi srpPr9MXwp285Su\r\n";
const std::string strImapSendSelect="C4 SELECT inbox\r\n";
const std::string strImapExamine="C5 examine inbox\r\n";
const std::string strImapCreate="C6 create testbox\r\n";
const std::string strImapRename="C7 rename testbox testbox2\r\n";
const std::string strImapDelete="C8 delete testbox2\r\n";
const std::string strImapSubscribe="C9 subscribe inbox\r\n";
const std::string strImapLsub="C10 LSUB \"\" *\r\n";
const std::string strImapUnSubscribe="C11 unsubscribe inbox\r\n";
const std::string strImapList="C12 list \"\" *\r\n";
const std::string strImapFetch="C13 fetch 1 all\r\n";
const std::string strImapLogout="C18 LOGOUT\r\n";
//IMAP END
TEST_CASE("IMAP_163_BASE_TEST") {
    int sockFd = Open("123.125.50.47",143);
    CHECK(sockFd > 0);
    std::string strMsg;
    CHECK(Recv(sockFd,strMsg));
    CHECK_EQ(strMsg,strImapRecvOnConnect);
    
    CHECK(Send(sockFd,strImapSendC1_CAPABILITY));

    strMsg.clear();
    CHECK(Recv(sockFd,strMsg));
    CHECK(strMsg.find("C1 OK CAPABILITY")!=std::string::npos);

    CHECK(Send(sockFd,strImapSendLogin));
    strMsg.clear();
    CHECK(Recv(sockFd,strMsg));
    CHECK_EQ(strMsg,strImapRecvLoginSucceed);

    CHECK(Send(sockFd,strImapSendSelect));
    strMsg.clear();
    CHECK(Recv(sockFd,strMsg));
    CHECK(strMsg.find("C4 OK ")!=std::string::npos);

    CHECK(Send(sockFd,strImapExamine));
    strMsg.clear();
    CHECK(Recv(sockFd,strMsg));
    CHECK(strMsg.find("C5 OK ")!=std::string::npos);


    CHECK(Send(sockFd,strImapCreate));
    strMsg.clear();
    CHECK(Recv(sockFd,strMsg));
    CHECK(strMsg.find("C6 OK ")!=std::string::npos);

    CHECK(Send(sockFd,strImapRename));
    strMsg.clear();
    CHECK(Recv(sockFd,strMsg));
    CHECK(strMsg.find("C7 OK ")!=std::string::npos);

    CHECK(Send(sockFd,strImapDelete));
    strMsg.clear();
    CHECK(Recv(sockFd,strMsg));
    CHECK(strMsg.find("C8 OK ")!=std::string::npos);

    CHECK(Send(sockFd,strImapSubscribe));
    strMsg.clear();
    CHECK(Recv(sockFd,strMsg));
    std::cout<<strMsg<<std::endl;
    CHECK(strMsg.find("C9 OK ")!=std::string::npos);

    CHECK(Send(sockFd,strImapLsub));
    strMsg.clear();
    CHECK(Recv(sockFd,strMsg));
    std::cout<<strMsg<<std::endl;
    CHECK(strMsg.find("C10 OK")!=std::string::npos);

    CHECK(Send(sockFd,strImapUnSubscribe));
    strMsg.clear();
    CHECK(Recv(sockFd,strMsg));
    CHECK(strMsg.find("C11 OK")!=std::string::npos);

    CHECK(Send(sockFd,strImapList));
    strMsg.clear();
    CHECK(Recv(sockFd,strMsg));
    CHECK(strMsg.find("C12 OK")!=std::string::npos);

    CHECK(Send(sockFd,strImapFetch));
    strMsg.clear();
    CHECK(Recv(sockFd,strMsg));
    CHECK(strMsg.find("C13 OK")!=std::string::npos);

    CHECK(Send(sockFd,strImapLogout));
    strMsg.clear();
    CHECK(Recv(sockFd,strMsg));
    CHECK(strMsg.find("C18 OK")!=std::string::npos);
}

#endif