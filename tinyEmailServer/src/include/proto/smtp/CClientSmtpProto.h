#ifndef _CPP_EMAIL_SMTP_PROTO_H_
#define _CPP_EMAIL_SMTP_PROTO_H_
#include "CEmailProtoInterface.h"
#include "CProtoCmd.h"
#include <vector>
namespace cpp_email
{
    class CClientSmtpProto:public CEmailProtoInterface
    {
    public:
        explicit CClientSmtpProto(){m_step = SMTP_STEP_BEGIN;m_bAuthFinish = false;}
        virtual ~CClientSmtpProto()=default;
        virtual bool OnRecv(const std::string& strRecv) override;
        virtual std::string GetSend() override;
        bool IsAuthFinished(){return m_bAuthFinish;};
        bool SendMail();
        virtual bool IsFinish() override { return false;}
    private:
        Smtp_Step_t GetNextCmd(const Smtp_Step_t curStep,const ProtoCode_t code);
        std::vector<CSmtpProtoCmd> m_recvCmdVec;
        Smtp_Step_t m_step;
        bool m_bAuthFinish;
    };
}
#endif