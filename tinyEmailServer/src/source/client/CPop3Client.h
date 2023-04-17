#ifndef _CPP_EMAIL_POP3_CLIENT_H_
#define _CPP_EMAIL_POP3_CLIENT_H_
#include "networkHandler.h"
#include "CTcpClient.h"
#include "CPop3Proto.h"
namespace cpp_email
{
    class CPop3ClientHandler;
    class Pop3ClientBridge:public INetWorkHandler
    {
    public:
        Pop3ClientBridge(CPop3ClientHandler* ptr) { m_callBack = ptr; }
        virtual void OnConnected() override;
        virtual void OnSend() override;
        virtual void OnReceive(const std::string strValue) override;
        virtual void OnClose() override;
        virtual void OnTimer() override;
    private:
        CPop3ClientHandler* m_callBack;
    };

    struct Pop3EmailElem_t {
        std::string m_strIndex;
        std::size_t m_emailSize;
    };
    class CPop3ClientHandler
    {
    public:
        CPop3ClientHandler(const std::string strUserName, const std::string strPassword);
        void Start(asio::io_context& m_ioService, log_ptr_t m_loger);
    public:
        void OnReceive(const std::string strValue);
    private:
        std::string GetSend();
        POP3_CLIENT_STEP_t GetNextCmd(const POP3_CLIENT_STEP_t curStep, const Pop3Code_t code);
        POP3_CLIENT_STEP_t m_step;
        bool m_bAuthFinish;
        std::string m_strEmailAddr;
        std::string m_strSmtpAddr;
        std::string m_strUserName;
        std::string m_strPassword;
        std::string m_strReceiverAddr;
        std::string m_strContent;
        CTcpClient_ptr_t m_pop3Socket;
        std::shared_ptr<Pop3ClientBridge> m_handler;
        std::vector<CPop3ProtoCmd> m_serverRspVec;
        std::string m_strListAll;
        std::string m_strEmailFormat;
        std::size_t m_strEmailCount;
        std::vector<Pop3EmailElem_t> m_unreadIndexVec;
    };
}
#endif