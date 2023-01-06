#ifndef _CPP_EMAIL_SMTP_SERVER_HANDLER_H_
#define _CPP_EMAIL_SMTP_SERVER_HANDLER_H_
#include "networkHandler.h"
#include "CTcpClient.h"
#include "CServerSmtpProto.h"
#include "thirdLib.h"
namespace cpp_email
{
    class CSmtpHandler:public INetWorkHandler
    {
    public:
       explicit CSmtpHandler(log_ptr_t log,CDataBaseInterface_SHARED_PTR ptr):
       m_proto(log,ptr), m_log(log){}
       virtual ~CSmtpHandler()=default;
       virtual void OnConnected() override;
       virtual void OnSend() override;
       virtual void OnRecive(const std::string strValue) override;
       virtual void OnTimer() override{};
       virtual void OnClose() override{};
       void SetTcpSocket(CTcpClient_ptr_t tcpSock)
       {
           m_client = tcpSock;
           if(m_client->isConnected())
           {
                m_client->Send(m_proto.GetSend());
           }
       }
       void Start()
       {
           m_client->Start();
       }
    private:
       CTcpClient_ptr_t m_client;
       CServerSmtpProto m_proto;
       log_ptr_t m_log;
    };
    using CSmtpHandler_PTR = std::shared_ptr<CSmtpHandler>;
}
#endif