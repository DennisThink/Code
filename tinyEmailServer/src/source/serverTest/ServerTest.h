#ifndef _SERVER_TEST_H_
#define _SERVER_TEST_H_


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#ifdef WIN32
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <WinSock2.h>
#pragma comment(lib,"Ws2_32.lib ")
#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <unistd.h>
#include <fcntl.h>
#endif
#include <regex>
#include "ProtoUtil.h"
#define MAXLINE 4096
#include <string>
#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"

bool IsRegexMatch(const std::string strRegex,const std::string strValue)
{
    std::regex self_regex(strRegex,
            std::regex_constants::ECMAScript | std::regex_constants::icase);
    return std::regex_search(strValue, self_regex);
}
int Open(std::string strIp,int port)
{
#ifdef WIN32
//�����׽��ֿ�
WSADATA wsaData;
int iRet = 0;
iRet = WSAStartup(MAKEWORD(2, 2), &wsaData);
if (iRet != 0)
{
	return -1;
}
if (2 != LOBYTE(wsaData.wVersion) || 2 != HIBYTE(wsaData.wVersion))
{
	WSACleanup();
	return -1;
}
#endif

    int sockfd;
    struct sockaddr_in servaddr;
    if ((sockfd = static_cast<int>(socket(AF_INET, SOCK_STREAM, 0))) < 0)
    {
        return -1;
    }
   
    
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(port);

#ifdef WIN32
	servaddr.sin_addr.S_un.S_addr = inet_addr(strIp.c_str());
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(port);
#else

	if (inet_pton(AF_INET, strIp.c_str(), &servaddr.sin_addr) <= 0)
	{
		return -1;
	}
#endif

    if (connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
    {
        return -1;
    }
    return sockfd;
}

bool Close(int socketFd)
{
#ifdef WIN32
	closesocket(socketFd);
#else
    close(socketFd);
#endif
	return true;
}

bool Send(int sockFd,std::string strMsg)
{
#ifdef WIN32
	std::size_t sendLen = send(sockFd, strMsg.data(), static_cast<int>(strMsg.length()), 0);
#else
    std::size_t sendLen = send(sockFd, strMsg.data(), strMsg.length(), 0);
#endif
	if(sendLen != strMsg.length())
    {
        return false;
    }
    std::cout<<"SEND:"<<strMsg<<std::endl;
    return true;
}

bool Recv(int sockFd,std::string& strMsg)
{
    const int BUF_LEN = 512;
    char buf[BUF_LEN] = {0};
    std::size_t nRecvLen = 0;
    do{
        memset(buf,0,BUF_LEN);
        nRecvLen =  recv(sockFd,buf,BUF_LEN,0);
        strMsg = strMsg+std::string(buf,nRecvLen);
        if(nRecvLen < BUF_LEN-1)
        {
            break;
        }
    }while(nRecvLen>0);
    std::cout<<"RECV:  "<<strMsg<<std::endl;
    return true;
}

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h>
#include <resolv.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <openssl/ssl.h>
#include <openssl/err.h>
 
#define MAXBUF 1024
 
void ShowCerts(SSL * ssl)
{
X509 *cert;
char *line;
 
cert = SSL_get_peer_certificate(ssl);
if (cert != NULL) {
printf("数字证书信息:\n");
line = X509_NAME_oneline(X509_get_subject_name(cert), 0, 0);
printf("证书: %s\n", line);
free(line);
line = X509_NAME_oneline(X509_get_issuer_name(cert), 0, 0);
printf("颁发者: %s\n", line);
free(line);
X509_free(cert);
} else
printf("无证书信息！\n");
}
/************关于本文档********************************************
*filename: ssl-client.c
*purpose: 演示利用 OpenSSL 库进行基于 IP层的 SSL 加密通讯的方法，这是客户端例子
*wrote by: zhoulifa(zhoulifa@163.com) 周立发(http://zhoulifa.bokee.com)
Linux爱好者 Linux知识传播者 SOHO族 开发者 最擅长C语言
*date time:2007-02-02 20:10
*Note: 任何人可以任意复制代码并运用这些文档，当然包括你的商业用途
* 但请遵循GPL
*Thanks to:Google
*Hope:希望越来越多的人贡献自己的力量，为科学技术发展出力
* 科技站在巨人的肩膀上进步更快！感谢有开源前辈的贡献！
*********************************************************************/
class CSslSocket
{
public:
    explicit CSslSocket()
    {
        SSL_library_init();
        OpenSSL_add_all_algorithms();
        SSL_load_error_strings();
        m_ctx = SSL_CTX_new(SSLv23_client_method());
    }

    virtual ~CSslSocket()
    {
        SSL_shutdown(m_ssl);
        SSL_free(m_ssl);
        close(m_sockfd);
        SSL_CTX_free(m_ctx);
    }
    bool Connect(const std::string& strIp,const int port)
    {
        struct sockaddr_in dest;
        /* 创建一个 socket 用于 tcp 通信 */
        if ((m_sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
            perror("Socket");
            return false;
        }
    
        
        /* 初始化服务器端（对方）的地址和端口信息 */
        bzero(&dest, sizeof(dest));
        dest.sin_family = AF_INET;
        dest.sin_port = htons(port);
        if (inet_aton(strIp.c_str(), (struct in_addr *) &dest.sin_addr.s_addr) == 0) {
            perror(strIp.c_str());
            return false;
        }

        
        /* 连接服务器 */
        if (connect(m_sockfd, (struct sockaddr *) &dest, sizeof(dest)) != 0) {
            perror("Connect ");
            return false;
        }
        printf("server connected\n");
        
        /* 基于 ctx 产生一个新的 SSL */
        m_ssl = SSL_new(m_ctx);
        SSL_set_fd(m_ssl, m_sockfd);
        /* 建立 SSL 连接 */
        if (SSL_connect(m_ssl) == -1){
            ERR_print_errors_fp(stderr);
            return false;
        }
        else {
            printf("Connected with %s encryption\n", SSL_get_cipher(m_ssl));
            ShowCerts(m_ssl);
            return true;
        }
    }

    bool Send(const std::string& strValue)
    {
        char buff[512]={0};
        strcpy(buff,strValue.c_str());
        int len = SSL_write(m_ssl, buff, strValue.length());
        std::cout<<"SEND: "<<len<<std::endl;
        if(len == static_cast<int>(strValue.length()))
        {
            return true;
        }

        return false;
    }

    bool Recv(std::string& strValue)
    {
        char buff[MAXBUF]={0};
        bzero(buff, MAXBUF);
        int len = SSL_read(m_ssl, buff, MAXBUF);
        while(len > 0)
        {
            strValue = strValue+std::string(buff);
            bzero(buff, MAXBUF);
            len = SSL_read(m_ssl, buff, MAXBUF);
        }
        std::cout<<"RECV:  "<<strValue<<std::endl;
        return true;
    }
private:
    SSL_CTX * m_ctx;
    SSL * m_ssl;
    int m_sockfd;
};
#endif