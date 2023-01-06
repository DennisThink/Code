#ifndef _POP3_163_TEST_CPP_
#define _POP3_163_TEST_CPP_
//POP3 BEGIN
//POP3 RECV
const std::string strPop3Recv="+OK Welcome to coremail Mail Pop3 Server (163coms[b62aaa251425b4be4eaec4ab4744cf47s])\r\n";
const std::string strPop3RecvOkCoreMail="+OK core mail\r\n";
//POP3 SEND
const std::string strPop3SendUser="USER dennismi\r\n";
const std::string strPop3SendPasswd="PASS srpPr9MXwp285Su\r\n";
const std::string strPop3SendStat ="STAT\r\n";
const std::string strPop3SendUidl ="UIDL 1\r\n";
const std::string strPop3SendRetr ="RETR 1\r\n";
const std::string strPop3SendNoop ="NOOP\r\n";
const std::string strPop3SendDel  ="DELE 1\r\n";
const std::string strPop3SendList ="LIST\r\n";
const std::string strPop3SendQuit ="QUIT\r\n";
//POP3 END


//POP3 BEGIN
//POP3 RECV
const std::string strPop3LocalRecv="+OK Welcome to coremail Mail Pop3 Server (163coms[b62aaa251425b4be4eaec4ab4744cf47s])\r\n";
const std::string strPop3LocalRecvOkCoreMail="+OK core mail\r\n";
//POP3 SEND
const std::string strPop3LocalSendUser="USER sender\r\n";
const std::string strPop3LocalSendPasswd="PASS sender\r\n";
const std::string strPop3LocalSendStat ="STAT\r\n";
const std::string strPop3LocalSendUidl ="UIDL 1\r\n";
const std::string strPop3LocalSendRetr ="RETR 1\r\n";
const std::string strPop3LocalSendNoop ="NOOP\r\n";
const std::string strPop3LocalSendDel  ="DELE 1\r\n";
const std::string strPop3LocalSendList ="LIST\r\n";
const std::string strPop3LocalSendQuit ="QUIT\r\n";
TEST_CASE("POP3_163_BASE_TEST") {
    int sockFd = Open("123.125.50.29",110);
    CHECK(sockFd > 0);
    std::string strMsg;
    CHECK(Recv(sockFd,strMsg));
    CHECK_EQ(strMsg,strPop3Recv);
    
    CHECK(Send(sockFd,strPop3SendUser));

    strMsg.clear();
    CHECK(Recv(sockFd,strMsg));
    CHECK_EQ(strMsg,strPop3RecvOkCoreMail);

    CHECK(Send(sockFd,strPop3SendPasswd));
    strMsg.clear();
    CHECK(Recv(sockFd,strMsg));
    CHECK(strMsg.find("+OK ")!=std::string::npos);

    CHECK(Send(sockFd,strPop3SendStat));
    strMsg.clear();
    CHECK(Recv(sockFd,strMsg));
    CHECK(strMsg.find("+OK ")!=std::string::npos);

    CHECK(Send(sockFd,strPop3SendStat));
    strMsg.clear();
    CHECK(Recv(sockFd,strMsg));
    CHECK(strMsg.find("+OK ")!=std::string::npos);

    CHECK(Send(sockFd,strPop3SendNoop));
    strMsg.clear();
    CHECK(Recv(sockFd,strMsg));
    CHECK(strMsg.find("+OK ")!=std::string::npos);

    CHECK(Send(sockFd,strPop3SendList));
    strMsg.clear();
    CHECK(Recv(sockFd,strMsg));
    CHECK(strMsg.find("+OK ")!=std::string::npos);

    CHECK(Send(sockFd,strPop3SendQuit));
    strMsg.clear();
    CHECK(Recv(sockFd,strMsg));
    CHECK(strMsg.find("+OK ")!=std::string::npos);
}


TEST_CASE("POP3_163_RECV_EMAIL_TEST") {
    int sockFd = Open("123.125.50.29",110);
    CHECK(sockFd > 0);
    std::string strMsg;
    CHECK(Recv(sockFd,strMsg));
    CHECK_EQ(strMsg,strPop3Recv);
    
    CHECK(Send(sockFd,strPop3SendUser));

    strMsg.clear();
    CHECK(Recv(sockFd,strMsg));
    CHECK_EQ(strMsg,strPop3RecvOkCoreMail);

    CHECK(Send(sockFd,strPop3SendPasswd));
    strMsg.clear();
    CHECK(Recv(sockFd,strMsg));
    CHECK(strMsg.find("+OK ")!=std::string::npos);

    CHECK(Send(sockFd,strPop3SendQuit));
    strMsg.clear();
    CHECK(Recv(sockFd,strMsg));
    CHECK(strMsg.find("+OK ")!=std::string::npos);
}

#endif