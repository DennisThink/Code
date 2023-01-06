#ifndef _CPP_EMAIL_POP3_SERVER_HANDLER_H_
#define _CPP_EMAIL_POP3_SERVER_HANDLER_H_
#include "networkHandler.h"
#include "CTcpClient.h"
#include "CPop3ServerProto.h"
#include "thirdLib.h"
namespace cpp_email
{
    class CPop3Handler:public INetWorkHandler
    {
    public:
       explicit CPop3Handler(log_ptr_t log,CDataBaseInterface_SHARED_PTR ptr):
       m_proto(log,ptr),m_log(log){}
       virtual ~CPop3Handler()=default;
       virtual void OnConnected() override{}
       virtual void OnTimer() override{};
       virtual void OnClose() override{};
       virtual void OnSend() override;
       virtual void OnRecive(const std::string strValue) override;
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
       CPop3ServerProto m_proto;
       log_ptr_t m_log;
    };
    using CPop3Handler_SHARED_PTR = std::shared_ptr<CPop3Handler>;
}
#endif