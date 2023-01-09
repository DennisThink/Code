#ifndef _CPP_EMAIL_EMAIL_CLIENT_H_
#define _CPP_EMAIL_EMAIL_CLIENT_H_
#include "networkHandler.h"
#include "CTcpClient.h"
#include "CClientSmtpProto.h"
#include "CPop3Proto.h"
#include "CClientImapProto.h"
namespace cpp_email
{
    class CEmailClient:public INetWorkHandler,public std::enable_shared_from_this<CEmailClient>
    {
        public:
            CEmailClient(asio::io_context& service, const log_ptr_t log,const std::string strUserName,const std::string strPassword) :
                m_ioService(service), m_loger(log),m_strUserName(strUserName),m_strPassword(strPassword) {
                m_smtpHandler = std::make_shared<CClientSmtpProto>(strUserName,strPassword);
            }
            void Start();
            virtual ~CEmailClient()=default;
            bool SendMailTo(const std::string strReciver, const std::string strContent);
        public:
            virtual void OnConnected() override;
            virtual void OnSend() override;
            virtual void OnRecive(const std::string strValue) override;
            virtual void OnTimer() override {};
            virtual void OnClose() override {};
        protected:
            CTcpClient_ptr_t m_smtpSocket;
            CTcpClient_ptr_t m_pop3Socket;
            CTcpClient_ptr_t m_imtpSocket;
            //CSmtpProto  m_smtpProto;
            ProtoHandlerPtr_t m_smtpHandler;
            ProtoHandlerPtr_t m_pop3Handler;
            ProtoHandlerPtr_t m_imtpHandler;
            asio::io_context& m_ioService;
            log_ptr_t m_loger;
            std::string m_strUserName;
            std::string m_strPassword;
    };
} // cpp_email

#endif