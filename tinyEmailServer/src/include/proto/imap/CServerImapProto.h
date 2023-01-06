#ifndef _CPP_EMAIL_SERVER_IMAP_PROTO_H_
#define _CPP_EMAIL_SERVER_IMAP_PROTO_H_
#include "CEmailProtoInterface.h"
#include "CProtoCode.h"
#include "CImapProtoCmd.h"
#include "CMemDataBase.h"
namespace cpp_email
{
    class CServerImapProto:public CEmailProtoInterface
    {
    public:
        explicit CServerImapProto(CDataBaseInterface_SHARED_PTR ptr){
            m_dataBase = ptr;
            m_step = IMAP_STEP_t::IMAP_STEP_SERVER_ON_CONNECTED;
        }
        virtual bool OnRecv(const std::string& strRecv) override;
        virtual bool IsFinish() override { return false;};
        virtual std::string GetSend() override;
    private:
        bool OnBadParseCmd();
        bool OnLogin();
        std::string GetSelectSend();
        std::string GetExamineSend();
        std::string GetLsubSend();
        std::string GetListSend();
        std::string GetFetchSend();
        IMAP_STEP_t m_step;
        CImapProtoReqCmd m_cmd;
        CDataBaseInterface_SHARED_PTR m_dataBase=nullptr;
    };
}
#endif