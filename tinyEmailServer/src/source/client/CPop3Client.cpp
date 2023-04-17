#include "CPop3Client.h"
#include "ProtoUtil.h"
#include <iostream>
namespace cpp_email{
void Pop3ClientBridge::OnConnected()
{

}
void Pop3ClientBridge::OnSend()
{

}
void Pop3ClientBridge::OnReceive(const std::string strValue)
{
    if (m_callBack)
    {
        m_callBack->OnReceive(strValue);
    }
}

void Pop3ClientBridge::OnClose()
{

}

void Pop3ClientBridge::OnTimer()
{

}

CPop3ClientHandler::CPop3ClientHandler(const std::string strUserName, const std::string strPassword)
{
    m_strUserName = strUserName;
    m_strPassword = strPassword;
}

void CPop3ClientHandler::Start(asio::io_context& m_ioService, log_ptr_t m_loger)
{
    m_handler = std::make_shared<Pop3ClientBridge>(this);
    m_pop3Socket = std::make_shared<CTcpClient>(m_ioService, m_loger, m_handler);
    std::size_t index = m_strUserName.find_first_of("@");
    m_strSmtpAddr = "pop." + m_strUserName.substr(index + 1);
    m_strUserName = m_strUserName.substr(0, index);
    m_pop3Socket->ConnectTo(m_strSmtpAddr, "pop3");
    m_step = POP3_CLIENT_STEP_t::POP3_CLIENT_STEP_BEGIN;
}

void CPop3ClientHandler::OnReceive(const std::string strValue)
{
    if (m_step == POP3_CLIENT_STEP_t::POP3_CLIENT_LIST_ALL)
    {
        m_strListAll += strValue;
        if (strValue.find('.') == std::string::npos)
        {
            return;
        }
        else
        {
            std::vector<std::string> result = CProtoUtil::SplitStringByLine(m_strListAll);
            m_strListAll.clear();
            m_unreadIndexVec.clear();
            for (std::size_t i = 1; i < result.size() - 1; i++)
            {
                std::size_t index = result[i].find_first_of(' ');
                std::string strIndex = result[i].substr(0, index);
                std::size_t count = std::atol(result[i].substr(index).c_str());
                m_unreadIndexVec.push_back({strIndex,count});
            }
            {
                std::string strCmd = "RETR " + (m_unreadIndexVec.begin()->m_strIndex) + "\r\n";
                m_strEmailCount = m_unreadIndexVec.begin()->m_emailSize;
                m_unreadIndexVec.erase(m_unreadIndexVec.begin());
                m_pop3Socket->Send(strCmd);
                m_step = POP3_CLIENT_STEP_t::POP3_CLIENT_LIST_UNREAD;
                return;
            }
        }
    }
    if (m_step == POP3_CLIENT_STEP_t::POP3_CLIENT_LIST_UNREAD)
    {
        if (m_strEmailFormat.length()+strValue.length()< m_strEmailCount)
        {
            m_strEmailFormat += strValue;
        }
        else
        {
            m_strEmailFormat += strValue;
            std::cout << "----------------------------------------" << std::endl;
            std::cout << "EMail: " << m_strEmailFormat << std::endl;
            std::cout << "----------------------------------------" << std::endl;
            std::cout << "EMailLen: " << m_strEmailFormat.length() << "     " << m_strEmailCount << std::endl;
            m_strEmailFormat.clear();
            m_strEmailCount = 0;
            if (!m_unreadIndexVec.empty())
            {
                std::string strCmd = "RETR " + (m_unreadIndexVec.begin()->m_strIndex) + "\r\n";
                m_strEmailCount = m_unreadIndexVec.begin()->m_emailSize;
                m_unreadIndexVec.erase(m_unreadIndexVec.begin());
                m_pop3Socket->Send(strCmd);
            }
            else
            {
                std::string strCmd = "QUIT \r\n";
                m_pop3Socket->Send(strCmd);
            }
        }
    }
    else
    { 
        CPop3ProtoCmd curCmd = CPop3ProtoCmd::FromString(strValue);
        m_step = GetNextCmd(m_step, curCmd.GetCode());
        std::string strNextCmd = GetSend();
        m_pop3Socket->Send(strNextCmd);
    }

}

std::string CPop3ClientHandler::GetSend()
{
    if (m_step == POP3_CLIENT_STEP_t::POP3_CLIENT_SEND_USER_NAME)
    {
        return "USER " + m_strUserName + "\r\n";
    }
    
    if (m_step == POP3_CLIENT_STEP_t::POP3_CLIENT_SEND_PASS_WORD)
    {
        return "PASS " + m_strPassword + "\r\n";
    }

    if (m_step == POP3_CLIENT_STEP_t::POP3_CLIENT_SEND_STAT)
    {
        return "STAT \r\n";
    }

    if (m_step == POP3_CLIENT_STEP_t::POP3_CLIENT_LIST_ALL)
    {
        return "LIST \r\n";
    }
    if (m_step == POP3_CLIENT_STEP_t::POP3_CLIENT_LIST_UNREAD)
    {
        return "LIST \r\n";
    }
    return "";
}
struct Pop3ClientElem_t
{
    Pop3ClientElem_t(POP3_CLIENT_STEP_t curStep,
        Pop3Code_t protoCode,
        POP3_CLIENT_STEP_t nextStep)
    {
        curStep_ = curStep;
        protoCode_ = protoCode;
        nextStep_ = nextStep;
    }

    POP3_CLIENT_STEP_t curStep_;
    Pop3Code_t protoCode_;
    POP3_CLIENT_STEP_t nextStep_;
};

const static Pop3ClientElem_t Pop3Array[] =
{
    {POP3_CLIENT_STEP_t::POP3_CLIENT_STEP_BEGIN,Pop3Code_t::POP3_OK,POP3_CLIENT_STEP_t::POP3_CLIENT_SEND_USER_NAME},
    {POP3_CLIENT_STEP_t::POP3_CLIENT_SEND_USER_NAME,Pop3Code_t::POP3_OK,POP3_CLIENT_STEP_t::POP3_CLIENT_SEND_PASS_WORD},
    {POP3_CLIENT_STEP_t::POP3_CLIENT_SEND_PASS_WORD,Pop3Code_t::POP3_OK,POP3_CLIENT_STEP_t::POP3_CLIENT_SEND_STAT,},
    {POP3_CLIENT_STEP_t::POP3_CLIENT_SEND_STAT,Pop3Code_t::POP3_OK,POP3_CLIENT_STEP_t::POP3_CLIENT_LIST_ALL,},
    {POP3_CLIENT_STEP_t::POP3_CLIENT_LIST_UNREAD,Pop3Code_t::POP3_OK,POP3_CLIENT_STEP_t::POP3_CLIENT_LIST_UNREAD_FINISHED,},
    {POP3_CLIENT_STEP_t::POP3_CLIENT_LIST_ALL,Pop3Code_t::POP3_OK,POP3_CLIENT_STEP_t::POP3_CLIENT_LIST_UNREAD_FINISHED,},
    {POP3_CLIENT_STEP_t::POP3_CLIENT_LIST_UNREAD_FINISHED,Pop3Code_t::POP3_OK,POP3_CLIENT_STEP_t::POP3_CLIENT_LIST_UNREAD,},
    {POP3_CLIENT_STEP_t::POP3_CLIENT_LIST_UNREAD,Pop3Code_t::POP3_OK,POP3_CLIENT_STEP_t::POP3_CLIENT_LIST_UNREAD,},
};
const int POP3_ARRAY_SIZE = sizeof(Pop3Array) / sizeof(Pop3Array[0]);
POP3_CLIENT_STEP_t CPop3ClientHandler::GetNextCmd(const POP3_CLIENT_STEP_t curStep, const Pop3Code_t code)
{
    for (std::size_t i = 0; i < POP3_ARRAY_SIZE; i++)
    {
        if (Pop3Array[i].curStep_ == curStep && code == Pop3Array[i].protoCode_)
        {
            return Pop3Array[i].nextStep_;
        }
    }
    return POP3_CLIENT_STEP_t::POP3_CLIENT_STEP_NO_OP;
}

}