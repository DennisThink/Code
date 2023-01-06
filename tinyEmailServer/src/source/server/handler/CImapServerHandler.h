#ifndef _CPP_EMAIL_IMAP_SERVER_HANDLER_H_
#define _CPP_EMAIL_IMAP_SERVER_HANDLER_H_
#include "networkHandler.h"
#include "CTcpClient.h"
#include "CServerImapProto.h"
#include "thirdLib.h"
namespace cpp_email
{
    class CImapServerHandler:public INetWorkHandler
    {
    public:
       explicit CImapServerHandler(log_ptr_t log,CDataBaseInterface_SHARED_PTR ptr):
       m_proto(ptr),m_log(log){}
       virtual ~CImapServerHandler()=default;
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
       CServerImapProto m_proto;
       log_ptr_t m_log;
    };
    using CImapServerHandler_SHARED_PTR = std::shared_ptr<CImapServerHandler>;
}
#endif