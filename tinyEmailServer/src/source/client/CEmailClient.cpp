#include "CEmailClient.h"
#include "CProtoCmd.h"
#include "ProtoUtil.h"
namespace cpp_email
{
    void CEmailClient::Start()
    {
        /*if (m_smtpHandler)
        {
            m_smtpHandler->Start(m_ioService, m_loger);
        }*/

        if (m_pop3Handler)
        {
            m_pop3Handler->Start(m_ioService, m_loger);
        }
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
