#ifndef _CPP_EMAIL_HTTP_MAIL_SERVER_H_
#define _CPP_EMAIL_HTTP_MAIL_SERVER_H_

#include "thirdLib.h"
#include "served.hpp"
#include <memory>
namespace cpp_email
{
    class CHttpMailServer:public std::enable_shared_from_this<CHttpMailServer>
    {
        using  HTTP_SERVER_PTR_T=std::shared_ptr<served::net::server>;
    public:
        explicit CHttpMailServer(asio::io_context& ioServer,log_ptr_t log):
        m_ioServer(ioServer),
        m_loger(log),
        m_timer(ioServer)
        {
        };
        void Start();
        void Stop();
        void SetTimer();
        void OnTimer();
    private:
        asio::io_context& m_ioServer;
        log_ptr_t m_loger;
        asio::steady_timer m_timer;
        served::multiplexer m_mux;
        HTTP_SERVER_PTR_T   m_httpServer;
    };
    using CHttpMailServer_PTR_t = std::shared_ptr<CHttpMailServer>;
}
#endif