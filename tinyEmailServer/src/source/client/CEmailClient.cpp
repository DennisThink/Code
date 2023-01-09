#include "CEmailClient.h"
namespace cpp_email
{

    void CEmailClient::OnConnected()
    {
        if(m_smtpSocket->isConnected())
        {
        }
    }

    void CEmailClient::OnRecive(const std::string strValue)
    {
        if(m_smtpHandler->OnRecv(strValue))
        {
            m_smtpSocket->Send(m_smtpHandler->GetSend());
        }
    }

    void CEmailClient::OnSend()
    {

    }

    void CEmailClient::Start()
    {
        INetWorkHandler_SHARED_PTR ptr = shared_from_this();
        m_smtpSocket = std::make_shared<CTcpClient>(m_ioService,m_loger,ptr);
        std::size_t index = m_strUserName.find_first_of("@");
        std::string strSmtpAddr = "smtp." + m_strUserName.substr(index + 1);

        m_smtpSocket->ConnectTo(strSmtpAddr,"smtp");
        //m_tcpSocket->ConnectTo("pop3.163.com","pop3");
        //m_tcpSocket->ConnectTo("imap.163.com","");
        //m_tcpSocket->ConnectTo("127.0.0.1",2500);
    }

    bool CEmailClient::SendMailTo(const std::string strReciver, const std::string strContent)
    {
        return false;
    }
}
