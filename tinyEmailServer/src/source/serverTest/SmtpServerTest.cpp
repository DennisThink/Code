#ifndef _SMTP_SERVER_TEST_CPP_
#define _SMTP_SERVER_TEST_CPP_
#include "ServerTest.h"
//RECV
const std::string strOnConnected = "220 cppemail.com Anti-spam GT for Coremail System\r\n";
const std::string strEhloRsp[] ={
    "250-mail\r\n",
    "250-AUTH LOGIN PLAIN\r\n",
    "250-AUTH=LOGIN PLAIN\r\n",
    "250 8BITMIME\r\n",
};

const std::string strRecvName="334 VXNlck5hbWU=\r\n";
const std::string strRecvPassword="334 UGFzc3dvcmQ=\r\n";
const std::string strRecvAuthSuccess="235 auth successfully\r\n";
const std::string strRecvMailFrom="250 MAIL FROM Succeed\r\n";
const std::string strRecvRcptTo="250 RCPT TO Succeed\r\n";
const std::string strRecvData="354 Enter mail, end with \".\" on a line by itself\r\n";
const std::string strRecvQuit="221 Bye\r\n";

//SEND
const std::string strEHLO="EHLO smtp.cppemail.com\r\n";
const std::string strAUTH_LOGIN="AUTH LOGIN\r\n";
const std::string strSendUserName="c2VuZGVyQGNwcGVtYWlsLmNvbQ==\r\n";
const std::string strSendPassword="c2VuZGVy\r\n";
const std::string strSendMailFrom="MAIL FROM:\"\"<sender@cppemail.com\r\n";
const std::string strSendMailTo="RCPT TO:receiver@cppemail.com\r\n";
const std::string strSendData="DATA\r\n";
const std::string strSendSubject="Subject:Design Plan\r\n";
const std::string strSendFrom="From:<dennismi@163.com>\r\n";
const std::string strSendTo="To:<dennismi1024@gmail.com>\r\n";
const std::string strEmailContext="我是米小，你有什么问题吗.\r\n";
const std::string strEmailContextEnd="\r\n.\r\n";
const std::string strSendEmailBody="我是米小，你有什么问题吗.\r\n";
const std::string strSendEmailEnd=".\r\n";
const std::string strSendQuit="QUIT\r\n";


TEST_CASE("SMTP_SEND_HELO_HELO_FIRST_AUTH_LOGIN") {
    int sockFd = Open("127.0.0.1",25);
    CHECK(sockFd > 0);
    std::string strMsg;
    CHECK(Recv(sockFd,strMsg));
    CHECK_EQ(strMsg,strOnConnected);
   
    CHECK(Send(sockFd,strAUTH_LOGIN));
    strMsg.clear();
    CHECK(Recv(sockFd,strMsg));
    CHECK_EQ(strMsg,"503 Error: send HELO/EHLO first\r\n");
}


TEST_CASE("SMTP_SEND_HELO_HELO_FIRST_MAIL_FROM") {
    int sockFd = Open("127.0.0.1",25);
    CHECK(sockFd > 0);
    std::string strMsg;
    CHECK(Recv(sockFd,strMsg));
    CHECK_EQ(strMsg,strOnConnected);
   
    CHECK(Send(sockFd,strSendMailFrom));
    strMsg.clear();
    CHECK(Recv(sockFd,strMsg));
    CHECK_EQ(strMsg,"503 Error: send HELO/EHLO first\r\n");
}

TEST_CASE("SMTP_SEND_HELO_HELO_FIRST_MAIL_TO") {
    int sockFd = Open("127.0.0.1",25);
    CHECK(sockFd > 0);
    std::string strMsg;
    CHECK(Recv(sockFd,strMsg));
    CHECK_EQ(strMsg,strOnConnected);
   
    CHECK(Send(sockFd,strSendMailTo));
    strMsg.clear();
    CHECK(Recv(sockFd,strMsg));
    CHECK_EQ(strMsg,"503 Error: send HELO/EHLO first\r\n");
}



TEST_CASE("SMTP_SIMPLE") {
    int sockFd = Open("127.0.0.1",25);
    CHECK(sockFd > 0);
    std::string strMsg;
    CHECK(Recv(sockFd,strMsg));
    CHECK_EQ(strMsg,strOnConnected);
    CHECK(Send(sockFd,strEHLO));

    strMsg.clear();
    CHECK(Recv(sockFd,strMsg));
    std::vector<std::string> strArray;
    strArray = cpp_email::CProtoUtil::SplitStringByLine(strMsg);
    CHECK_FALSE(strArray.empty());
    CHECK_EQ(4,strArray.size());
    if(strArray.size() <= 4)
    {
        CHECK_EQ(strArray[0],strEhloRsp[0]);
        CHECK_EQ(strArray[1],strEhloRsp[1]);
        CHECK_EQ(strArray[2],strEhloRsp[2]);
        CHECK_EQ(strArray[3],strEhloRsp[3]);
    }
    
    CHECK(Send(sockFd,strAUTH_LOGIN));
    strMsg.clear();
    CHECK(Recv(sockFd,strMsg));
    CHECK_EQ(strMsg,strRecvName);

    CHECK(Send(sockFd,strSendUserName));

    strMsg.clear();
    CHECK(Recv(sockFd,strMsg));
    CHECK_EQ(strMsg,strRecvPassword);
    CHECK(Send(sockFd,strSendPassword));

    strMsg.clear();
    CHECK(Recv(sockFd,strMsg));
    CHECK_EQ(strMsg,strRecvAuthSuccess);

    CHECK(Send(sockFd,strSendMailFrom));
    
    strMsg.clear();
    CHECK(Recv(sockFd,strMsg));
    CHECK_EQ(strMsg,strRecvMailFrom);

    
    CHECK(Send(sockFd,strSendMailTo));
    
    strMsg.clear();
    CHECK(Recv(sockFd,strMsg));
    CHECK_EQ(strMsg,strRecvRcptTo);

    CHECK(Send(sockFd,strSendQuit));
    
    strMsg.clear();
    CHECK(Recv(sockFd,strMsg));
    CHECK_EQ(strMsg,strRecvQuit);
}


TEST_CASE("SMTP_AUTH_QUIT") {
    int sockFd = Open("127.0.0.1",25);
    CHECK(sockFd > 0);
    std::string strMsg;
    CHECK(Recv(sockFd,strMsg));
    CHECK_EQ(strMsg,strOnConnected);
    CHECK(Send(sockFd,strEHLO));

    strMsg.clear();
    CHECK(Recv(sockFd,strMsg));
    std::vector<std::string> strArray;
    strArray = cpp_email::CProtoUtil::SplitStringByLine(strMsg);
    CHECK_FALSE(strArray.empty());
    CHECK_EQ(4,strArray.size());
    if(strArray.size() <= 4)
    {
        CHECK_EQ(strArray[0],strEhloRsp[0]);
        CHECK_EQ(strArray[1],strEhloRsp[1]);
        CHECK_EQ(strArray[2],strEhloRsp[2]);
        CHECK_EQ(strArray[3],strEhloRsp[3]);
    }
    
    CHECK(Send(sockFd,strAUTH_LOGIN));
    strMsg.clear();
    CHECK(Recv(sockFd,strMsg));
    CHECK_EQ(strMsg,strRecvName);

    CHECK(Send(sockFd,strSendUserName));

    strMsg.clear();
    CHECK(Recv(sockFd,strMsg));
    CHECK_EQ(strMsg,strRecvPassword);
    CHECK(Send(sockFd,strSendPassword));

    strMsg.clear();
    CHECK(Recv(sockFd,strMsg));
    CHECK_EQ(strMsg,strRecvAuthSuccess);

    CHECK(Send(sockFd,strSendQuit));
    
    strMsg.clear();
    CHECK(Recv(sockFd,strMsg));
    CHECK_EQ(strMsg,strRecvQuit);
}


bool SendEmail()
{
    int sockFd = Open("127.0.0.1",25);
    std::string strMsg;
    Recv(sockFd,strMsg);
    //CHECK_EQ(strMsg,strOnConnected);
    Send(sockFd,strEHLO);

    strMsg.clear();
    CHECK(Recv(sockFd,strMsg));
    /*std::vector<std::string> strArray;
    strArray = cpp_email::CProtoUtil::SplitStringByLine(strMsg);
    CHECK_FALSE(strArray.empty());
    CHECK_EQ(4,strArray.size());
    if(strArray.size() <= 4)
    {
        CHECK_EQ(strArray[0],strEhloRsp[0]);
        CHECK_EQ(strArray[1],strEhloRsp[1]);
        CHECK_EQ(strArray[2],strEhloRsp[2]);
        CHECK_EQ(strArray[3],strEhloRsp[3]);
    }*/
    
    Send(sockFd,strAUTH_LOGIN);
    strMsg.clear();
    Recv(sockFd,strMsg);
    //CHECK_EQ(strMsg,strRecvName);

    Send(sockFd,strSendUserName);

    strMsg.clear();
    Recv(sockFd,strMsg);
    //CHECK_EQ(strMsg,strRecvPassword);
    Send(sockFd,strSendPassword);

    strMsg.clear();
    Recv(sockFd,strMsg);
    //CHECK_EQ(strMsg,strRecvAuthSuccess);

    Send(sockFd,strSendMailFrom);
    strMsg.clear();
    CHECK(Recv(sockFd,strMsg));
    CHECK_EQ(strMsg,strRecvMailFrom);


    CHECK(Send(sockFd,strSendMailTo));
    strMsg.clear();
    CHECK(Recv(sockFd,strMsg));
    CHECK_EQ(strMsg,strRecvRcptTo);

    CHECK(Send(sockFd,strSendData));
    strMsg.clear();
    CHECK(Recv(sockFd,strMsg));
    CHECK_EQ(strMsg,strRecvData);

    CHECK(Send(sockFd,strSendQuit));
    strMsg.clear();
    CHECK(Recv(sockFd,strMsg));
    CHECK_EQ(strMsg,strRecvQuit);

    return true;
}


TEST_CASE("SMTP_SEND_MAIL") {
    int sockFd = Open("127.0.0.1",25);
    CHECK(sockFd > 0);
    std::string strMsg;
    CHECK(Recv(sockFd,strMsg));
    CHECK_EQ(strMsg,strOnConnected);
    CHECK(Send(sockFd,strEHLO));

    strMsg.clear();
    CHECK(Recv(sockFd,strMsg));
    std::vector<std::string> strArray;
    strArray = cpp_email::CProtoUtil::SplitStringByLine(strMsg);
    CHECK_FALSE(strArray.empty());
    CHECK_EQ(4,strArray.size());
    if(strArray.size() <= 4)
    {
        CHECK_EQ(strArray[0],strEhloRsp[0]);
        CHECK_EQ(strArray[1],strEhloRsp[1]);
        CHECK_EQ(strArray[2],strEhloRsp[2]);
        CHECK_EQ(strArray[3],strEhloRsp[3]);
    }
    
    CHECK(Send(sockFd,strAUTH_LOGIN));
    strMsg.clear();
    CHECK(Recv(sockFd,strMsg));
    CHECK_EQ(strMsg,strRecvName);

    CHECK(Send(sockFd,strSendUserName));

    strMsg.clear();
    CHECK(Recv(sockFd,strMsg));
    CHECK_EQ(strMsg,strRecvPassword);
    CHECK(Send(sockFd,strSendPassword));

    strMsg.clear();
    CHECK(Recv(sockFd,strMsg));
    CHECK_EQ(strMsg,strRecvAuthSuccess);

    CHECK(Send(sockFd,strSendMailFrom));
    strMsg.clear();
    CHECK(Recv(sockFd,strMsg));
    CHECK_EQ(strMsg,strRecvMailFrom);


    CHECK(Send(sockFd,strSendMailTo));
    strMsg.clear();
    CHECK(Recv(sockFd,strMsg));
    CHECK_EQ(strMsg,strRecvRcptTo);

    CHECK(Send(sockFd,strSendData));
    strMsg.clear();
    CHECK(Recv(sockFd,strMsg));
    CHECK_EQ(strMsg,strRecvData);

    CHECK(Send(sockFd,strSendQuit));
    strMsg.clear();
    CHECK(Recv(sockFd,strMsg));
    CHECK_EQ(strMsg,strRecvQuit);
}



TEST_CASE("SMTP_SEND_MAIL_CPP_EMAIL") {
    int sockFd = Open("127.0.0.1",25);
    CHECK(sockFd > 0);
    std::string strMsg;
    CHECK(Recv(sockFd,strMsg));
    CHECK_EQ(strMsg,strOnConnected);
    CHECK(Send(sockFd,strEHLO));

    strMsg.clear();
    CHECK(Recv(sockFd,strMsg));
    std::vector<std::string> strArray;
    strArray = cpp_email::CProtoUtil::SplitStringByLine(strMsg);
    CHECK_FALSE(strArray.empty());
    //CHECK_EQ(4,strArray.size());
    
    CHECK(Send(sockFd,strAUTH_LOGIN));
    strMsg.clear();
    CHECK(Recv(sockFd,strMsg));
    //CHECK_EQ(strMsg,strRecvName);

    CHECK(Send(sockFd,cpp_email::CProtoUtil::Base64Encode("sender@cppemail.com")+"\r\n"));

    strMsg.clear();
    CHECK(Recv(sockFd,strMsg));
    //CHECK_EQ(strMsg,strRecvPassword);
    CHECK(Send(sockFd,cpp_email::CProtoUtil::Base64Encode("sender")+"\r\n"));

    strMsg.clear();
    CHECK(Recv(sockFd,strMsg));
    CHECK_EQ(strMsg,"235 auth successfully\r\n");




    CHECK(Send(sockFd,"MAIL FROM: <sender@cppemail.com>\r\n"));
    strMsg.clear();
    CHECK(Recv(sockFd,strMsg));
    CHECK_EQ(strMsg,"250 MAIL FROM Succeed\r\n");

    CHECK(Send(sockFd,"RCPT TO: <receiver@cppemail.com>\r\n"));
    strMsg.clear();
    CHECK(Recv(sockFd,strMsg));
    CHECK_EQ(strMsg,"250 RCPT TO Succeed\r\n");

    CHECK(Send(sockFd,strSendData));
    strMsg.clear();
    CHECK(Recv(sockFd,strMsg));
    CHECK_EQ(strMsg,"354 Enter mail, end with \".\" on a line by itself\r\n");
    CHECK(Send(sockFd,strSendEmailBody));
    CHECK(Send(sockFd,strSendEmailEnd));
    strMsg.clear();
    CHECK(Recv(sockFd,strMsg));
    
    CHECK(Send(sockFd,strSendQuit));
    strMsg.clear();
    CHECK(Recv(sockFd,strMsg));
    CHECK_EQ(strMsg,strRecvQuit);
}


TEST_CASE("SMTP_SEND_MAIL_CPP_EMAIL_INNER") {
    int sockFd = Open("127.0.0.1",25);
    CHECK(sockFd > 0);
    std::string strMsg;
    CHECK(Recv(sockFd,strMsg));
    CHECK_EQ(strMsg,strOnConnected);
    CHECK(Send(sockFd,strEHLO));

    strMsg.clear();
    CHECK(Recv(sockFd,strMsg));
    std::vector<std::string> strArray;
    strArray = cpp_email::CProtoUtil::SplitStringByLine(strMsg);
    CHECK_FALSE(strArray.empty());
    //CHECK_EQ(4,strArray.size());
    
    CHECK(Send(sockFd,strAUTH_LOGIN));
    strMsg.clear();
    CHECK(Recv(sockFd,strMsg));
    //CHECK_EQ(strMsg,strRecvName);

    CHECK(Send(sockFd,cpp_email::CProtoUtil::Base64Encode("sender@cppemail.com")+"\r\n"));

    strMsg.clear();
    CHECK(Recv(sockFd,strMsg));
    //CHECK_EQ(strMsg,strRecvPassword);
    CHECK(Send(sockFd,cpp_email::CProtoUtil::Base64Encode("sender")+"\r\n"));

    strMsg.clear();
    CHECK(Recv(sockFd,strMsg));
    CHECK_EQ(strMsg,"235 auth successfully\r\n");

    CHECK(Send(sockFd,"MAIL FROM: <sender@cppemail.com>\r\n"));
    strMsg.clear();
    CHECK(Recv(sockFd,strMsg));
    CHECK_EQ(strMsg,"250 MAIL FROM Succeed\r\n");

    CHECK(Send(sockFd,"RCPT TO: <receiver@cppemail.com>\r\n"));
    strMsg.clear();
    CHECK(Recv(sockFd,strMsg));
    CHECK_EQ(strMsg,"250 RCPT TO Succeed\r\n");

    CHECK(Send(sockFd,strSendData));
    strMsg.clear();
    CHECK(Recv(sockFd,strMsg));
    CHECK_EQ(strMsg,"354 Enter mail, end with \".\" on a line by itself\r\n");
    CHECK(Send(sockFd,strSendEmailBody));
    CHECK(Send(sockFd,strSendEmailEnd));
    strMsg.clear();
    CHECK(Recv(sockFd,strMsg));
    
    CHECK(Send(sockFd,strSendQuit));
    strMsg.clear();
    CHECK(Recv(sockFd,strMsg));
    CHECK_EQ(strMsg,strRecvQuit);
}
#endif