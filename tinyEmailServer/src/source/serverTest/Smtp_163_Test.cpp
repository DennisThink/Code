#ifndef _SMTP_163_TEST_CPP_
#define _SMTP_163_TEST_CPP_
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
const std::string strSendMailFrom="MAIL FROM:<sender@cppemail.com\r\n";
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
TEST_CASE("SMTP_SEND_MAIL_163") {
    int sockFd = Open("220.181.12.11",25);
    CHECK(sockFd > 0);
    std::string strMsg;
    CHECK(Recv(sockFd,strMsg));
    //CHECK_EQ(strMsg,strOnConnected);
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

    CHECK(Send(sockFd,cpp_email::CProtoUtil::Base64Encode("dennismi@163.com")+"\r\n"));

    strMsg.clear();
    CHECK(Recv(sockFd,strMsg));
    //CHECK_EQ(strMsg,strRecvPassword);
    CHECK(Send(sockFd,cpp_email::CProtoUtil::Base64Encode("srpPr9MXwp285Su")+"\r\n"));

    strMsg.clear();
    CHECK(Recv(sockFd,strMsg));
    CHECK_EQ(strMsg,"235 Authentication successful\r\n");




    CHECK(Send(sockFd,"MAIL FROM: <dennismi@163.com>\r\n"));
    strMsg.clear();
    CHECK(Recv(sockFd,strMsg));
    CHECK_EQ(strMsg,"250 Mail OK\r\n");

    CHECK(Send(sockFd,"RCPT TO: <dennismi1024@gmail.com>\r\n"));
    strMsg.clear();
    CHECK(Recv(sockFd,strMsg));
    CHECK_EQ(strMsg,"250 Mail OK\r\n");

    CHECK(Send(sockFd,strSendData));
    strMsg.clear();
    CHECK(Recv(sockFd,strMsg));
    CHECK_EQ(strMsg,"354 End data with <CR><LF>.<CR><LF>\r\n");
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