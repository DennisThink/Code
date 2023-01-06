#include "CServerSmtpProto.h"
#include "CProtoCmd.h"
#include "ProtoUtil.h"
#include <algorithm>
#include <iostream>
namespace cpp_email
{
CServerSmtpProto::CServerSmtpProto(log_ptr_t log,CDataBaseInterface_SHARED_PTR ptr) : m_log(log),m_dataBase(ptr)
{
    m_step = SERVER_SMTP_SEND_ON_CONNECT;
    m_bAuthFinish = false;
    m_strEmailDomain = "cppemail.com";
    m_errorCmdCount = 0;
}
std::string CServerSmtpProto::GetSend()
{
    if(m_step == SERVER_SMTP_EMAIL_DATA)
    {
        return "";
    }
    switch (m_step)
    {
        case SERVER_SMTP_SEND_HELO_HELO_FIRST:
        {
            return "503 Error: send HELO/EHLO first\r\n";
        }break;
    case SERVER_SMTP_SEND_ON_CONNECT:
    {
        std::string strCode = "220 ";
        std::string strTail = " Anti-spam GT for Coremail System\r\n";
        return strCode + m_strEmailDomain + strTail;
    }
    break;
    case SERVER_SMTP_SEND_250:
    {
        std::string strFirst = "250-mail\r\n";
        std::string strAuth1 = "250-AUTH LOGIN PLAIN\r\n";
        std::string strAuth2 = "250-AUTH=LOGIN PLAIN\r\n";
        std::string str8BitTime = "250 8BITMIME\r\n";
        return strFirst + strAuth1 + strAuth2 + str8BitTime;
    }
    break;
    case SERVER_SMTP_SEND_BYE_221:
    {
        return "221 Bye\r\n";
    }break;
    case SERVER_SMTP_SEND_USER_NAME_334:
    {
        std::string strCode = "334 ";
        std::string userName = CProtoUtil::Base64Encode("UserName");
        return strCode + userName + "\r\n";
    }
    break;
    case SERVER_SMTP_SEND_PASS_WORD_334:
    {
        std::string strCode = "334 ";
        std::string password = CProtoUtil::Base64Encode("Password");
        return strCode + password + "\r\n";
    }
    break;
    case SERVER_SMTP_SEND_AUTH_SUCCESS:
    {
        return "235 auth successfully\r\n";
    }
    break;
    case SEND_USER_NAME:
    {
        return CProtoUtil::Base64Encode("dennismi@163.com") + "\r\n";
    }
    break;
    case SEND_PASSWORD:
    {
        return CProtoUtil::Base64Encode("srpPr9MXwp285Su") + "\r\n";
    }
    break;
    case SEND_MAIL_FROM:
    {
        return "MAIL FROM: <dennismi@163.com>\r\n";
    }
    break;
    case SEND_MAIL_TO:
    {
        return "RCPT TO: <dennismi1024@gmail.com>\r\n";
    }
    break;
    case SERVER_SMTP_SEND_AUTH_FAILED_535:
    {
        return "535 Error: authentication failed\r\n";
    }
    break;
    case SERVER_SMTP_SEND_CMD_NOT_IMPLEMENT_502:
    {
        m_errorCmdCount++;
        return "502 Error: command not implemented\r\n";
    }
    break;
    case SERVER_SMTP_SEND_TOO_MANY_ERROR_CMDS_421:
    {
        return "421 Too many error commands\r\n";
    }
    break;
    case SERVER_SMTP_SEND_MAIL_FROM_250:
    {
        return "250 MAIL FROM Succeed\r\n";
    }break;
    case SERVER_SMTP_SEND_RCPT_TO_250:
    {
        return "250 RCPT TO Succeed\r\n";
    }break;
    case SERVER_SMTP_SEND_QUIT:
    {
        return "221 Bye\r\n";
    }break;
    case SERVER_SMTP_SEND_DATA:
    {
        m_step = SERVER_SMTP_EMAIL_DATA;
        return "354 Enter mail, end with \".\" on a line by itself\r\n";
    }break;
    case SERVER_SMTP_EMAIL_DATA:
    {
        return "";
    }break;
    case SERVER_SMTP_EMAIL_FINISH:
    {
       return "250 Mail OK queued as smtp11,D8CowAD3q0+vOSBc4a4JEg--.44272S2 1545615792\r\n";
    }break;
    default:
    {
        return "";
    }
    break;
    }
}


bool CServerSmtpProto::OnAuthRecv()
{
    if(m_step == SERVER_SMTP_SEND_ON_CONNECT)
    {
        m_step = SERVER_SMTP_SEND_HELO_HELO_FIRST;
    }
    else
    {
        m_step = SERVER_SMTP_SEND_USER_NAME_334;
    }
    return true;
}

bool CServerSmtpProto::OnMailFromRecv()
{
    if(m_step == SERVER_SMTP_SEND_ON_CONNECT)
    {
        m_step = SERVER_SMTP_SEND_HELO_HELO_FIRST;
    }
    else
    {
        m_step = SERVER_SMTP_SEND_MAIL_FROM_250;
    }
    return true;
}


bool CServerSmtpProto::OnMailRecpToRecv()
{
    if(m_step == SERVER_SMTP_SEND_ON_CONNECT)
    {
        m_step = SERVER_SMTP_SEND_HELO_HELO_FIRST;
    }
    else
    {
        m_step = SERVER_SMTP_SEND_RCPT_TO_250;
    }
    return true;
}
bool CServerSmtpProto::OnRecv(const std::string &strRecv)
{
    CSmtpProtoReqCmd cmd;
    PARSE_SMTP_RESULT result = CSmtpProtoReqCmd::FromString(strRecv,cmd);
    std::cout<<static_cast<int>(result)<<static_cast<int>(cmd.GetCode())<<std::endl;
    if(PARSE_SMTP_RESULT::PARSE_SMTP_SUCCEED == result)
    {
        if(cmd.GetCode() == SMTP_CMD_t::SMTP_CMD_HELO_EHLO)
        {
            m_step = SERVER_SMTP_SEND_250;
            return true;
        }

        if(cmd.GetCode() == SMTP_CMD_t::SMTP_CMD_AUTH)
        {
            return OnAuthRecv();
        }

        if(cmd.GetCode() == SMTP_CMD_t::SMTP_CMD_MAIL_FROM)
        {
            return OnMailFromRecv();
        }

        if(cmd.GetCode() == SMTP_CMD_t::SMTP_CMD_RECP_TO)
        {
            return OnMailRecpToRecv();
        }

        if(cmd.GetCode() == SMTP_CMD_t::SMTP_CMD_QUIT)
        {
            m_step = SERVER_SMTP_SEND_QUIT;
            return true;
        }

        if(cmd.GetCode() == SMTP_CMD_t::SMTP_CMD_DATA)
        {
            m_step = SERVER_SMTP_SEND_DATA;
            return true;
        }

        if(cmd.GetCode() == SMTP_CMD_t::SMTP_CMD_RSET)
        {
            return OnRsetRecv();   
        }
    }
    


    if (SERVER_SMTP_SEND_USER_NAME_334 == m_step)
    {
        std::string strUserName = CProtoUtil::Base64Decode(strRecv);
        if (m_dataBase->IsUserExist(strUserName))
        {
            m_log->info("UserName: {} Good", strUserName);
            m_step = SERVER_SMTP_SEND_PASS_WORD_334;
        }
        else
        {
            m_log->warn("UserName: {} Bad", strUserName);
            m_step = SERVER_SMTP_SEND_AUTH_FAILED_535;
        }

        return true;
    }

    if (SERVER_SMTP_SEND_PASS_WORD_334 == m_step)
    {
        std::cout << "Password:  " << CProtoUtil::Base64Decode(strRecv) << std::endl;
        m_step = SERVER_SMTP_SEND_AUTH_SUCCESS;
        return true;
    }

    if(m_step == SERVER_SMTP_EMAIL_DATA)
    {
        m_emailData = m_emailData.append(strRecv);
        if(m_emailData.find("\r\n.\r\n") != std::string::npos)
        {
            m_step = SERVER_SMTP_EMAIL_FINISH;
            email_info_t email;
            if(ParseEmailFromRecv(m_emailData,email))
            {
                m_dataBase->SaveSendMailInfo(email);
                m_log->info("Save Email");
                m_emailData.clear();
            }
            m_log->info("EMAILDATA:\r\n {}",m_emailData);
        }
        return true;
    }
    m_step = SERVER_SMTP_SEND_CMD_NOT_IMPLEMENT_502;
    if (m_errorCmdCount > 3)
    {
        m_step = SERVER_SMTP_SEND_TOO_MANY_ERROR_CMDS_421;
    }
    return true;
}

bool CServerSmtpProto::OnRsetRecv()
{
    if(m_step == SERVER_SMTP_SEND_ON_CONNECT )
    {
        m_step = SERVER_SMTP_SEND_HELO_HELO_FIRST;
    }
    return true;
}

bool CServerSmtpProto::SendMail()
{
    if (IsAuthFinished() && m_step == AUTH_SUCCESS)
    {
        m_step = SEND_MAIL_FROM;
    }
    return true;
}
} // namespace cpp_email


