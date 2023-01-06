#include "CServerImapProto.h"
#include "CImapProtoCmd.h"
#include <iostream>
namespace cpp_email
{
    std::string CServerImapProto::GetSelectSend()
    {
        std::string strResult="";
        strResult+="* 0 EXISTS\r\n";
        strResult+="* 0 RECENT\r\n";
        strResult+="* OK [UIDVALIDITY 1] UIDs valid\r\n";
        
        strResult+=R"(* FLAGS (\Answered \Seen \Deleted \Draft \Flagged))";
        strResult+="\r\n";
        
        strResult+=R"(* OK [PERMANENTFLAGS (\Answered \Seen \Deleted \Draft \Flagged)] Limited)";
        strResult+="\r\n";

        strResult  +=m_cmd.GetOrderId();
        strResult +=" OK [READ-WRITE] SELECT completed\r\n";
        return strResult;
    }

    std::string CServerImapProto::GetExamineSend()
    {
        std::string strResult="";
        strResult+="* 0 EXISTS\r\n";
        strResult+="* 0 RECENT\r\n";
        strResult+="* OK [UIDVALIDITY 1] UIDs valid\r\n";
        
        strResult+=R"(* FLAGS (\Answered \Seen \Deleted \Draft \Flagged))";
        strResult+="\r\n";
        
        strResult+=R"(* OK [PERMANENTFLAGS (\Answered \Seen \Deleted \Draft \Flagged)] Limited)";
        strResult+="\r\n";

        strResult  +=m_cmd.GetOrderId();
        strResult+=" OK [READ-WRITE] EXAMINE completed\r\n";
        return strResult;
    }

    std::string CServerImapProto::GetListSend()
    {
        std::string strResult = "";
        strResult += R"(* LIST () "/" "INBOX")";
        strResult += "\r\n";
        strResult += R"(* LIST (\Drafts) "/" "&g0l6P3ux-")";
        strResult += "\r\n";
        strResult += R"(* LIST (\Sent) "/" "&XfJT0ZAB-")";
        strResult += "\r\n";
        strResult += R"(* LIST (\Trash) "/" "&XfJSIJZk-")";
        strResult += "\r\n";
        strResult += R"(* LIST (\Junk) "/" "&V4NXPpCuTvY-")";
        strResult += "\r\n";
        strResult += R"(* LIST () "/" "&dcVr0mWHTvZZOQ-")";
        strResult += "\r\n";
        strResult += R"(* LIST () "/" "&XeVPXA-")";
        strResult += "\r\n";
        strResult += R"(C12 OK LIST Completed)";
        strResult += "\r\n";
        return strResult;
    }

    std::string CServerImapProto::GetLsubSend()
    {
        std::string strResult = "";
        strResult += R"(* LSUB () "/" "&XeVPXA-")";
        strResult += "\r\n";

        strResult  +=m_cmd.GetOrderId();
        strResult+=" OK LSUB Completed\r\n";

        return strResult;
    }

    std::string CServerImapProto::GetFetchSend()
    {
        return "";
    }
std::string CServerImapProto::GetSend()
{
    std::string strOK=" OK ";
    std::string strComplete = " Complete \r\n";
    switch (m_step)
    {
    case IMAP_STEP_SERVER_ON_CONNECTED:
    {
        return "* OK Coremail System IMap Server Ready(cppemail[1.0])\r\n";
    }
    break;
    case IMAP_STEP_SERVER_SEND_LOGIN_SUCCEED:
    {
        std::string strLoginTail= " OK LOGIN completed (cpp email)\r\n";
        return m_cmd.GetOrderId() + strLoginTail;
    }
    break;
    case IMAP_STEP_SERVER_SEND_LOGIN_FAILED:
    {
        std::string strLoginTail= " NO LOGIN Login error password error (cpp email)\r\n";
        return m_cmd.GetOrderId() + strLoginTail;
    }
    break;
    case IMAP_STEP_SERVER_SEND_SELECT:
    {
        return GetSelectSend();
    }
    break;
    case IMAP_STEP_SERVER_SEND_EXAMINE:
    {
        return GetExamineSend();
    }
    break;
    case IMAP_STEP_SERVER_SEND_CREATE:
    {
        return m_cmd.GetOrderId() + strOK +  strComplete;
    }
    break;
    case IMAP_STEP_SERVER_SEND_RENAME:
    {
        return m_cmd.GetOrderId() + strOK +  strComplete;
    }
    break;
    case IMAP_STEP_SERVER_SEND_DELETE:
    {
        return m_cmd.GetOrderId() + strOK +  strComplete;
    }
    break;
    case IMAP_STEP_SERVER_SEND_SUBSCRIBE:
    {
        return m_cmd.GetOrderId() + strOK +  strComplete;
    }
    break;
    case IMAP_STEP_SERVER_SEND_UN_SUBSCRIBE:
    {
        return m_cmd.GetOrderId() + strOK +  strComplete;
    }
    break;
    case IMAP_STEP_SERVER_SEND_LSUB:
    {
        return GetLsubSend();
    }
    break;
    case IMAP_STEP_SERVER_SEND_LIST:
    {
       return GetListSend();
    }
    break;
    case IMAP_STEP_SERVER_SEND_FETCH:
    {
        return m_cmd.GetOrderId() + strOK +  strComplete;
    }
    break;
    case IMAP_STEP_SERVER_SEND_LOGOUT:
    {
        return m_cmd.GetOrderId() + strOK +  strComplete;
    }
    break;
    case IMAP_STEP_SERVER_SEND_CAPALIBITY:
    {
        std::string strBegin="* CAPABILITY IMAP4rev1 XLIST SPECIAL-USE ID LITERAL+ STARTTLS XAPPLEPUSHSERVICE UIDPLUS X-CM-EXT-1\r\n";
        std::string strCapalityComplete="CAPABILITY completed (cpp email)\r\n";
        return strBegin + m_cmd.GetOrderId() + strOK +  strCapalityComplete;
    }break;
    case IMAP_STEP_SERVER_SEND_BAD_PARSE_CMD_ERROR:
    {
        std::string strCapalityComplete=" BAD Parse command error (cpp email)\r\n";
        return  m_cmd.GetOrderId() + strCapalityComplete;
    }break;
    default:
    {
        return "";
    }
    }
    return "";
}
bool CServerImapProto::OnLogin()
{
    std::string strMsg = m_cmd.GetMessage();
    auto spacePos = strMsg.find(" ");
    std::cout<<strMsg<<std::endl;
    if(spacePos != std::string::npos)
    {
        std::string strUser = strMsg.substr(0,spacePos);
        std::string strPasswd = strMsg.substr(spacePos+1,strMsg.length()-spacePos-1);
        std::cout<<strUser<<"\t"<<strPasswd<<std::endl;
        if(m_dataBase)
        {
            if(m_dataBase->IsPasswordRight(strUser,strPasswd))
            {
                m_step = IMAP_STEP_t::IMAP_STEP_SERVER_SEND_LOGIN_SUCCEED;
                std::cout<<strUser<<"\t"<<strPasswd<<std::endl;
                return true;
            }
        }
    }
    m_step = IMAP_STEP_t::IMAP_STEP_SERVER_SEND_LOGIN_FAILED;
    return true;
    
}

bool CServerImapProto::OnBadParseCmd()
{
    return false;
}

bool CServerImapProto::OnRecv(const std::string &strRecv)
{

    PARSE_IMAP_RESULT result = CImapProtoReqCmd::FromString(strRecv, m_cmd);
    if (result == PARSE_IMAP_RESULT::PARSE_IMAP_SUCCEED)
    {
        switch (m_cmd.GetCode())
        {
        case IMAP_CMD_CAPABILITY:
        {
            m_step = IMAP_STEP_t::IMAP_STEP_SERVER_SEND_CAPALIBITY;
        }
        break;
        case IMAP_CMD_LOGIN:
        {
            return OnLogin();
        }
        break;
        case IMAP_CMD_NOOP:
        {
            m_step = IMAP_STEP_t::IMAP_STEP_SERVER_SEND_NOOP;
        }
        break;
        case IMAP_CMD_SELECT:
        {
            m_step = IMAP_STEP_t::IMAP_STEP_SERVER_SEND_SELECT;
        }
        break;
        case IMAP_CMD_EXAMINE:
        {
            m_step = IMAP_STEP_t::IMAP_STEP_SERVER_SEND_EXAMINE;
        }
        break;
        case IMAP_CMD_CREATE:
        {
            m_step = IMAP_STEP_t::IMAP_STEP_SERVER_SEND_CREATE;
        }
        break;
        case IMAP_CMD_RENAME:
        {
            m_step = IMAP_STEP_t::IMAP_STEP_SERVER_SEND_RENAME;
        }
        break;
        case IMAP_CMD_DELETE:
        {
            m_step = IMAP_STEP_t::IMAP_STEP_SERVER_SEND_DELETE;
        }
        break;
        case IMAP_CMD_SUBSCRIBE:
        {
            m_step = IMAP_STEP_t::IMAP_STEP_SERVER_SEND_SUBSCRIBE;
        }
        break;
        case IMAP_CMD_UN_SUBSCRIBE:
        {
            m_step = IMAP_STEP_t::IMAP_STEP_SERVER_SEND_UN_SUBSCRIBE;
        }
        break;
        case IMAP_CMD_LSUB:
        {
            m_step = IMAP_STEP_t::IMAP_STEP_SERVER_SEND_LSUB;
        }
        break;
        case IMAP_CMD_LIST:
        {
            m_step = IMAP_STEP_t::IMAP_STEP_SERVER_SEND_LIST;
        }
        break;
        case IMAP_CMD_FETCH:
        {
            m_step = IMAP_STEP_t::IMAP_STEP_SERVER_SEND_FETCH;
        }
        break;
        case IMAP_CMD_LOGOUT:
        {
            m_step = IMAP_STEP_t::IMAP_STEP_SERVER_SEND_LOGOUT;
        }
        default:
        {

        }break;
        }
        return true;
    }
    else if(PARSE_IMAP_RESULT::PARSE_IMAP_FAILED == result)
    {
        m_step = IMAP_STEP_t::IMAP_STEP_SERVER_SEND_BAD_PARSE_CMD_ERROR;
        return false;
    }
    return false;
}
} // namespace cpp_email