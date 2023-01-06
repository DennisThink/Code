#ifndef _IMAP_SERVER_TEST_CPP_
#define _IMAP_SERVER_TEST_CPP_
#include "ServerTest.h"
//IMAP BEGIN
//RECV
const std::string strImapRecvOnConnect="* OK Coremail System IMap Server Ready(cppemail[1.0])\r\n";

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

TEST_CASE("IMAP_CPP_EMAIL_BASE_TEST") {
    int sockFd = Open("127.0.0.1",143);
    CHECK(sockFd > 0);
    std::string strMsg;
    CHECK(Recv(sockFd,strMsg));
    CHECK_EQ(strMsg,strImapRecvOnConnect);
    
    CHECK(Send(sockFd,strImapSendC1_CAPABILITY));

    strMsg.clear();
    CHECK(Recv(sockFd,strMsg));
    CHECK(strMsg.find("C1 OK CAPABILITY")!=std::string::npos);
    {
        std::vector<std::string> strArray;
        strArray = cpp_email::CProtoUtil::SplitStringByLine(strMsg);
        CHECK_EQ(strArray.size(),2);
        if(strArray.size() >= 2)
        {
            CHECK_EQ(strArray[1],"C1 OK CAPABILITY completed (cpp email)\r\n");
        }
    }

    CHECK(Send(sockFd,"C3 LOGIN sender@cppemail.com sender\r\n"));
    strMsg.clear();
    CHECK(Recv(sockFd,strMsg));
    CHECK_EQ(strMsg,"C3 OK LOGIN completed (cpp email)\r\n");

    CHECK(Send(sockFd,strImapSendSelect));
    strMsg.clear();
    CHECK(Recv(sockFd,strMsg));
    /*CHECK(strMsg.find("C4 OK ")!=std::string::npos);
    {
        std::vector<std::string> strArray;
        strArray = cpp_email::CProtoUtil::SplitStringByLine(strMsg);
        CHECK_EQ(strArray.size(),6);
        if(strArray.size() >= 6)
        {
            CHECK_EQ(strArray[0],"* 0 EXISTS\r\n");
            CHECK_EQ(strArray[1],"* 0 RECENT\r\n");
            CHECK_EQ(strArray[2],"* OK [UIDVALIDITY 1] UIDs valid\r\n");
            CHECK_EQ(strArray[3],"* FLAGS (\\Answered \\Seen \\Deleted \\Draft \\Flagged)\r\n");
            CHECK_EQ(strArray[4],"* OK [PERMANENTFLAGS (\\Answered \\Seen \\Deleted \\Draft \\Flagged)] Limited\r\n");
            CHECK_EQ(strArray[5],"C4 OK [READ-WRITE] SELECT completed\r\n");
        }
    }*/

    CHECK(Send(sockFd,strImapExamine));
    strMsg.clear();
    CHECK(Recv(sockFd,strMsg));
    /*CHECK(strMsg.find("C5 OK ")!=std::string::npos);
    {
        std::vector<std::string> strArray;
        strArray = cpp_email::CProtoUtil::SplitStringByLine(strMsg);
        CHECK_EQ(strArray.size(),6);
        if(strArray.size() >= 6)
        {
            CHECK_EQ(strArray[0],"* 0 EXISTS\r\n");
            CHECK_EQ(strArray[1],"* 0 RECENT\r\n");
            CHECK_EQ(strArray[2],"* OK [UIDVALIDITY 1] UIDs valid\r\n");
            CHECK_EQ(strArray[3],"* FLAGS (\\Answered \\Seen \\Deleted \\Draft \\Flagged)\r\n");
            CHECK_EQ(strArray[4],"* OK [PERMANENTFLAGS (\\Answered \\Seen \\Deleted \\Draft \\Flagged)] Limited\r\n");
            CHECK_EQ(strArray[5],"C5 OK [READ-WRITE] EXAMINE completed\r\n");
        }
    }*/ 


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
    {
        {
        std::vector<std::string> strArray;
        strArray = cpp_email::CProtoUtil::SplitStringByLine(strMsg);
        CHECK_EQ(strArray.size(),2);
        if(strArray.size() >= 2)
        {
            CHECK(strArray[0].find("* LSUB () ")!=std::string::npos);
            CHECK_EQ(strArray[1],"C10 OK LSUB Completed\r\n");
        }
        } 
    }
    std::cout<<strMsg<<std::endl;
    CHECK(strMsg.find("C10 OK")!=std::string::npos);

    CHECK(Send(sockFd,strImapUnSubscribe));
    strMsg.clear();
    CHECK(Recv(sockFd,strMsg));
    CHECK(strMsg.find("C11 OK")!=std::string::npos);

    CHECK(Send(sockFd,strImapList));
    strMsg.clear();
    CHECK(Recv(sockFd,strMsg));
    {
        std::vector<std::string> strArray;
        strArray = cpp_email::CProtoUtil::SplitStringByLine(strMsg);
        CHECK_EQ(strArray.size(), 8);
        if (strArray.size() >= 8)
        {
            CHECK(strArray[0].find("* LIST () ") != std::string::npos);
            CHECK(strArray[1].find("* LIST (\\Drafts) ") != std::string::npos);
            CHECK(strArray[2].find("* LIST (\\Sent) ") != std::string::npos);
            CHECK(strArray[3].find("* LIST (\\Trash) ") != std::string::npos);
            CHECK(strArray[4].find("* LIST (\\Junk) ") != std::string::npos);
            CHECK(strArray[5].find("* LIST () ") != std::string::npos);
            CHECK_EQ(strArray[7], "C12 OK LIST Completed\r\n");
        }
    }
    CHECK(strMsg.find("C12 OK")!=std::string::npos);

    CHECK(Send(sockFd,strImapFetch));
    strMsg.clear();
    CHECK(Recv(sockFd,strMsg));
    CHECK(strMsg.find("C13 OK")!=std::string::npos);

    CHECK(Send(sockFd,strImapLogout));
    strMsg.clear();
    CHECK(Recv(sockFd,strMsg));
    CHECK(strMsg.find("C18 OK")!=std::string::npos);

    Close(sockFd);
}


TEST_CASE("IMAP_CPP_EMAIL_BAD_CMD") {
    int sockFd = Open("127.0.0.1",143);
    CHECK(sockFd > 0);
    std::string strMsg;
    CHECK(Recv(sockFd,strMsg));
    CHECK_EQ(strMsg,strImapRecvOnConnect);
    
    CHECK(Send(sockFd,"C1 CAPABIL\r\n"));
    strMsg.clear();
    CHECK(Recv(sockFd,strMsg));
    CHECK_EQ(strMsg,"C1 BAD Parse command error (cpp email)\r\n");
    Close(sockFd);
}

TEST_CASE("IMAP_CPP_EMAIL_LOGIN_FAILED") {
    int sockFd = Open("127.0.0.1",143);
    CHECK(sockFd > 0);
    std::string strMsg;
    CHECK(Recv(sockFd,strMsg));
    CHECK_EQ(strMsg,strImapRecvOnConnect);
    
    CHECK(Send(sockFd,"C1 LOGIN dennis dennis\r\n"));
    strMsg.clear();
    CHECK(Recv(sockFd,strMsg));
    CHECK_EQ(strMsg,"C1 NO LOGIN Login error password error (cpp email)\r\n");
    Close(sockFd);
}
#endif