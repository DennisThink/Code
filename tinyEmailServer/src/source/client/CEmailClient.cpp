#include "CEmailClient.h"
namespace cpp_email
{

    void CEmailClient::OnConnected()
    {
        if(m_tcpSocket->isConnected())
        {
        }
    }

    void CEmailClient::OnRecive(const std::string strValue)
    {
        if(m_ProtoHandler->OnRecv(strValue))
        {
            m_tcpSocket->Send(m_ProtoHandler->GetSend());
        }
    }

    void CEmailClient::OnSend()
    {

    }

    void CEmailClient::Start()
    {
        INetWorkHandler_SHARED_PTR ptr = shared_from_this();
        m_tcpSocket = std::make_shared<CTcpClient>(m_ioService,m_loger,ptr);
        //m_tcpSocket->ConnectTo("smtp.163.com","smtp");
        m_tcpSocket->ConnectTo("pop3.163.com","pop3");
        //m_tcpSocket->ConnectTo("imap.163.com","");
        //m_tcpSocket->ConnectTo("127.0.0.1",2500);
    }
}
