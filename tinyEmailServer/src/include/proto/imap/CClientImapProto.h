#ifndef _CPP_MAIL_IMAP_PROTO_CMD_H_
#define _CPP_MAIL_IMAP_PROTO_CMD_H_
#include "CEmailProtoInterface.h"
#include "CProtoCode.h"
namespace cpp_email
{
    class CImapProto:public CEmailProtoInterface
    {
    public:
        explicit CImapProto(){m_step = IMAP_WAIT_VERIFY;}
        virtual bool OnRecv(const std::string& strRecv) override;
        virtual std::string GetSend() override;
    private:
        ImapCode_t GetNextState(ImapCode_t cur,ImapCode_t recv);
        ImapCode_t m_step;
    };
}
#endif