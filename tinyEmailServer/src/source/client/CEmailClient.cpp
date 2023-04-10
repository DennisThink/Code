#include "CEmailClient.h"
#include "CProtoCmd.h"
#include "ProtoUtil.h"
namespace cpp_email
{
    void CEmailClient::Start()
    {
        if (m_smtpHandler)
        {
            m_smtpHandler->Start(m_ioService, m_loger);
        }
        /*m_smtpSocket = std::make_shared<CTcpClient>(m_ioService, m_loger, m_smtpHandler);
        std::size_t index = m_strUserName.find_first_of("@");
        std::string strSmtpAddr = "smtp." + m_strUserName.substr(index + 1);

        m_smtpSocket->ConnectTo(strSmtpAddr,"smtp");*/
        //m_tcpSocket->ConnectTo("pop3.163.com","pop3");
        //m_tcpSocket->ConnectTo("imap.163.com","");
        //m_tcpSocket->ConnectTo("127.0.0.1",2500);
    }

    bool CEmailClient::SendMailTo(const std::string strReciver, const std::string strContent)
    {
        return false;
    }

    bool CEmailClient::ReceiveMail()
    {
        return false;
    }


}
