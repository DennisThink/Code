#ifndef _CPP_EMAIL_SERVER_SMTP_PROTO_H_
#define _CPP_EMAIL_SERVER_SMTP_PROTO_H_
#include "CEmailProtoInterface.h"
#include "CProtoCmd.h"
#include "CMemDataBase.h"
#include "thirdLib.h"
#include <vector>
namespace cpp_email
{
    class CServerSmtpProto:public CEmailProtoInterface
    {
    public:
        explicit CServerSmtpProto(log_ptr_t log,CDataBaseInterface_SHARED_PTR ptr);
        virtual bool OnRecv(const std::string& strRecv) override;
        virtual std::string GetSend() override;
        virtual bool IsFinish() override { return m_step == SERVER_SMTP_SEND_TOO_MANY_ERROR_CMDS_421;}
        bool IsAuthFinished(){return m_bAuthFinish;};
        bool SendMail();
    private:
        bool OnRsetRecv();
        bool OnAuthRecv();
        bool OnMailFromRecv();
        bool OnMailRecpToRecv();
        std::vector<CSmtpProtoCmd> m_recvCmdVec;
        Smtp_Step_t m_step;
        bool m_bAuthFinish;
        log_ptr_t m_log;
        std::string m_strEmailDomain;
        CDataBaseInterface_SHARED_PTR m_dataBase;
        std::string m_emailData;
        int m_errorCmdCount;
    };
}
#endif