#include "CClientSmtpProto.h"
#include "ProtoUtil.h"
#include <algorithm>
namespace cpp_email
{
std::string CClientSmtpProto::GetSend()
{
    SendMail();
    switch (m_step)
    {
    case SEND_HELO:
    {
        return "HELO SMTP.163.com\r\n";
    }
    break;
    case SEND_AUTH_LOGIN:
    {
        return "AUTH LOGIN\r\n";
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
    }break;
    case SEND_MAIL_FROM:
    {
        return "MAIL FROM: <dennismi@163.com>\r\n";
    }break;
    case SEND_MAIL_TO:
    {
        return "RCPT TO: <dennismi1024@gmail.com>\r\n";
    }break;
    case SEND_DATA_HEAD:
    {
        return "DATA\r\n";
    }break;
    case SEND_DATA_BODY:
    {
        return std::string("Subject:Design Plan\r\n")+
               std::string("From:""<dennismi@163.com>\r\n")+
               std::string("To:""<dennismi1024@gmail.com>\r\n")+
               std::string("\r\n")+
               std::string("我是米小，你有什么问题吗\r\n")+
               std::string("\r\n.\r\n");
    }break;
    case SEND_DATA_TAIL:
    {
        return "\r\n.\r\n";
    }break;
    default:
    {
        return "";
    }
    break;
    }
}

bool CClientSmtpProto::OnRecv(const std::string &strRecv)
{
    std::vector<std::string> strArray = CProtoUtil::SplitStringByLine(strRecv);
    for (const auto &item : strArray)
    {
        if (item.length() > 3)
        {
            m_recvCmdVec.emplace_back(CSmtpProtoCmd::FromString(item));
        }
    }
    for (const auto &item : m_recvCmdVec)
    {
        if (item.isFinish())
        {
            m_step = GetNextCmd(m_step, item.GetCode());
            if (m_step == AUTH_SUCCESS)
            {
                m_bAuthFinish = true;
            }
            break;
        }
    }
    m_recvCmdVec.clear();
    return true;
}

struct elem_t
{
    elem_t(Smtp_Step_t curStep,
           ProtoCode_t protoCode,
           Smtp_Step_t nextStep)
    {
        curStep_ = curStep;
        protoCode_ = protoCode;
        nextStep_ = nextStep;
    }

    Smtp_Step_t curStep_;
    ProtoCode_t protoCode_;
    Smtp_Step_t nextStep_;
};

const static elem_t Array[] =
    {
        {SMTP_STEP_BEGIN, CODE_220, SEND_HELO},
        {SEND_HELO, CODE_250, SEND_AUTH_LOGIN},
        {SEND_AUTH_LOGIN, CODE_334, SEND_USER_NAME},
        {SEND_USER_NAME, CODE_334, SEND_PASSWORD},
        {SEND_PASSWORD, CODE_235, AUTH_SUCCESS},
        {SEND_MAIL_FROM,CODE_250,SEND_MAIL_TO},
        {SEND_MAIL_TO,CODE_250,SEND_DATA_HEAD},
        {SEND_DATA_HEAD,CODE_354,SEND_DATA_BODY},
        {SEND_DATA_BODY,CODE_354,SEND_DATA_TAIL},
        {SEND_DATA_TAIL,CODE_250,SEND_NO_OP}};
const int ARRAY_SIZE = sizeof(Array) / sizeof(Array[0]);
Smtp_Step_t CClientSmtpProto::GetNextCmd(const Smtp_Step_t curStep, const ProtoCode_t code)
{
    for (int i = 0; i < ARRAY_SIZE; i++)
    {
        if (Array[i].curStep_ == curStep &&
            ( Array[i].protoCode_ == code || Array[i].protoCode_ == CODE_ANY))
        {
            return Array[i].nextStep_;
        }
    }
    return SEND_NO_OP;
}

bool CClientSmtpProto::SendMail()
{
    if(IsAuthFinished() && m_step == AUTH_SUCCESS)
    {
        m_step = SEND_MAIL_FROM;
    }
    return true;
}
} // namespace cpp_email