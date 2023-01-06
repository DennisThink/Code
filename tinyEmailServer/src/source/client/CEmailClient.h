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
            CEmailClient(asio::io_context& service,const log_ptr_t log):
            m_ioService(service),m_loger(log){
                //m_ProtoHandler = std::make_shared<CClientSmtpProto>();
                m_ProtoHandler = std::make_shared<CPop3Proto>("dennismi","srpPr9MXwp285Su");
                //m_ProtoHandler = std::make_shared<CImapProto>();
            }
            void Start();
            virtual ~CEmailClient()=default;
        public:
            virtual void OnConnected() override;
            virtual void OnSend() override;
            virtual void OnRecive(const std::string strValue) override;
            virtual void OnTimer() override {};
            virtual void OnClose() override {};
        protected:
            CTcpClient_ptr_t m_tcpSocket;
            //CSmtpProto  m_smtpProto;
            ProtoHandlerPtr_t m_ProtoHandler;
            asio::io_context& m_ioService;
            log_ptr_t m_loger;
    };
} // cpp_email

#endif