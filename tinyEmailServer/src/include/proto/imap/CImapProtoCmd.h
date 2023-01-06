#ifndef _CPP_EMAIL_IMAP_PROTO_CMD_H_
#define _CPP_EMAIL_IMAP_PROTO_CMD_H_

#include <string>
#include "CProtoCode.h"
namespace cpp_email
{
    class CImapProtoCmd
    {
    public:
        static CImapProtoCmd FromString(const std::string& strValue);
        ImapCode_t GetCode() const
        {
            return m_code;
        }

        std::string GetMessage() const 
        {
            return m_message;
        }
        
        bool isFinish() const 
        {
            return m_bFinish;
        }
    private:
        explicit CImapProtoCmd(ImapCode_t code,std::string message,bool bFinish)
        {
            m_code = code;
            m_message = message;
            m_bFinish = bFinish;
        }
        ImapCode_t m_code;
        std::string m_message;
        bool m_bFinish=false;
    };


    class CImapProtoReqCmd
    {
    public:
        explicit CImapProtoReqCmd(){m_orderId="";m_code=IMAP_CMD_t::IMAP_CMD_NOOP;m_message="";}
        static PARSE_IMAP_RESULT FromString(const std::string& strValue,CImapProtoReqCmd& cmd);
        
        std::string GetOrderId()
        {
            return m_orderId;
        }

        IMAP_CMD_t GetCode() const
        {
            return m_code;
        }

        std::string GetMessage() const 
        {
            return m_message;
        }
        
    private:
        explicit CImapProtoReqCmd(std::string strId,IMAP_CMD_t code,std::string message)
        {
            m_orderId=strId;
            m_code = code;
            m_message = message;
        }
        std::string m_orderId;
        IMAP_CMD_t m_code;
        std::string m_message;
    };
}
#endif