#ifndef _POP3_QQ_TEST_CPP_
#define _POP3_QQ_TEST_CPP_
namespace POP3_QQ
{

//POP3 BEGIN
//POP3 RECV
const std::string strPop3Recv="+OK QQMail POP3 Server v1.0 Service Ready(QQMail v2.0)\r\n";
const std::string strPop3RecvOkCoreMail="+OK\r\n";
//POP3 SEND
const std::string strPop3SendUser="USER 2475027682@qq.com\r\n";
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
const std::string strPop3LocalSendUser="USER sender\r\n\r\n";
const std::string strPop3LocalSendPasswd="PASS sender\r\n";
const std::string strPop3LocalSendStat ="STAT\r\n";
const std::string strPop3LocalSendUidl ="UIDL 1\r\n";
const std::string strPop3LocalSendRetr ="RETR 1\r\n";
const std::string strPop3LocalSendNoop ="NOOP\r\n";
const std::string strPop3LocalSendDel  ="DELE 1\r\n";
const std::string strPop3LocalSendList ="LIST\r\n";
const std::string strPop3LocalSendQuit ="QUIT\r\n";
TEST_CASE("POP3_QQ_BASE_TEST") {
    CSslSocket sslSocket;
    CHECK_EQ(true,sslSocket.Connect("58.251.139.219",995));
    std::string strMsg;
    CHECK(sslSocket.Recv(strMsg));
    CHECK_EQ(strMsg,strPop3Recv);
    
    CHECK(sslSocket.Send(strPop3SendUser));

    strMsg.clear();
    CHECK(sslSocket.Recv(strMsg));
    CHECK_EQ(strMsg,strPop3RecvOkCoreMail);

    CHECK(sslSocket.Send(strPop3SendPasswd));
    strMsg.clear();
    CHECK(sslSocket.Recv(strMsg));
    CHECK(strMsg.find("+OK ")!=std::string::npos);

    CHECK(sslSocket.Send(strPop3SendStat));
    strMsg.clear();
    CHECK(sslSocket.Recv(strMsg));
    CHECK(strMsg.find("+OK ")!=std::string::npos);

    CHECK(sslSocket.Send(strPop3SendStat));
    strMsg.clear();
    CHECK(sslSocket.Recv(strMsg));
    CHECK(strMsg.find("+OK ")!=std::string::npos);

    /*CHECK(Send(sockFd,strPop3SendUidl));
    strMsg.clear();
    CHECK(Recv(sockFd,strMsg));
    CHECK(strMsg.find("+OK ")!=std::string::npos);*/

    CHECK(sslSocket.Send(strPop3SendNoop));
    strMsg.clear();
    CHECK(sslSocket.Recv(strMsg));
    CHECK(strMsg.find("+OK ")!=std::string::npos);

    /*CHECK(Send(sockFd,strPop3SendDel));
    strMsg.clear();
    CHECK(Recv(sockFd,strMsg));
    CHECK(strMsg.find("+OK ")!=std::string::npos);*/

    CHECK(sslSocket.Send(strPop3SendList));
    strMsg.clear();
    CHECK(sslSocket.Recv(strMsg));
    CHECK(strMsg.find("+OK ")!=std::string::npos);

    CHECK(sslSocket.Send(strPop3SendQuit));
    strMsg.clear();
    CHECK(sslSocket.Recv(strMsg));
    CHECK(strMsg.find("+OK ")!=std::string::npos);
}


TEST_CASE("POP3_QQ_RECV_EMAIL_TEST") {
    int sockFd = Open("58.251.139.219",995);
    CHECK(sockFd > 0);
    std::string strMsg;
    CHECK(Recv(sockFd,strMsg));
    CHECK_EQ(strMsg,strPop3Recv);
    
    CHECK(Send(sockFd,strPop3SendUser));

    strMsg.clear();
    CHECK(Recv(sockFd,strMsg));
    std::cout<<__LINE__<<strMsg<<std::endl;
    CHECK_EQ(strMsg,strPop3RecvOkCoreMail);

    CHECK(Send(sockFd,strPop3SendPasswd));
    strMsg.clear();
    CHECK(Recv(sockFd,strMsg));
    std::cout<<__LINE__<<strMsg<<std::endl;
    CHECK(strMsg.find("+OK")!=std::string::npos);

    CHECK(Send(sockFd,strPop3SendQuit));
    strMsg.clear();
    CHECK(Recv(sockFd,strMsg));
    std::cout<<__LINE__<<strMsg<<std::endl;
    CHECK(strMsg.find("+OK")!=std::string::npos);
}
}
#endif