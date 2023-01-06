#ifndef _CPP_EMAIL_EMAIL_SERVER_H_
#define _CPP_EMAIL_EMAIL_SERVER_H_
#include <string>
#include "thirdLib.h"
#include "CTcpServer.h"
#include "CHttpMailServer.h"
namespace cpp_email 
{
    class CEmailServer 
    {
    public:
        explicit CEmailServer()
        {
        }

        void Start();
    private:
        asio::io_context m_ioService;
        CSmtpServer_SHARED_PTR m_smtpHandler;
        CPop3Server_SHARED_PTR m_pop3Handler;
        CImapServer_SHARED_PTR m_imapHandler;
        CDataBaseInterface_SHARED_PTR m_dataPtr;
        CHttpMailServer_PTR_t m_mailHttpServer;
    };
}
#endif