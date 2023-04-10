#ifndef _CPP_EMAIL_SMTP_CLIENT_H_
#define _CPP_EMAIL_SMTP_CLIENT_H_
#include "CSmtpClient.h"
#include "networkHandler.h"
#include "CTcpClient.h"
#include "CClientSmtpProto.h"
#include "CPop3Proto.h"
#include "CClientImapProto.h"
#include "ProtoUtil.h"
namespace cpp_email {
    class CSmtpClientHandler;
    class SmtpClientBridge :public INetWorkHandler
    {
    public:
        SmtpClientBridge(CSmtpClientHandler* ptr) { m_callBack = ptr; }
        virtual void OnConnected() override;
        virtual void OnSend() override;
        virtual void OnReceive(const std::string strValue) override;
        virtual void OnClose() override;
        virtual void OnTimer() override;
    private:
       CSmtpClientHandler* m_callBack;
    };
    class CSmtpClientHandler
    {
    public:
        CSmtpClientHandler(const std::string strUserName, const std::string strPassword);
        bool SendMail(const std::string strReciver, const std::string strMailContent);
        void Start(asio::io_context& m_ioService, log_ptr_t m_loger);
    public:
        void OnReceive(const std::string strValue);
    private:
        std::string GetSend();
        Smtp_Step_t GetNextCmd(const Smtp_Step_t curStep, const ProtoCode_t code);
        std::vector<CSmtpProtoCmd> m_recvCmdVec;
        Smtp_Step_t m_step;
        bool m_bAuthFinish;
        std::string m_strEmailAddr;
        std::string m_strSmtpAddr;
        std::string m_strUserName;
        std::string m_strPassword;
        std::string m_strReceiverAddr;
        std::string m_strContent;
        CTcpClient_ptr_t m_smtpSocket;
        std::shared_ptr<SmtpClientBridge> m_handler;
    };
}
#endif