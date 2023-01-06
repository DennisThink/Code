#include "CHttpMailServer.h"
namespace cpp_email
{
    void CHttpMailServer::Start()
    {
		auto self = shared_from_this();
		m_mux.handle("/hello")
			.get([self, this](served::response & res, const served::request & req) {
			m_loger->info("REQ FROM:{} {}", req.source(), res.body_size());
			res << "Hello world";
		});
		m_httpServer = std::make_shared<served::net::server>(m_ioServer, "127.0.0.1", "8123", m_mux);
        SetTimer();
    }

    void CHttpMailServer::Stop()
    {

    }

    void CHttpMailServer::SetTimer()
    {
        m_timer.expires_from_now(std::chrono::seconds(5));
		auto self = shared_from_this();
        m_timer.async_wait([self,this](std::error_code ec){
            if(!ec)
            {
                OnTimer();
            }
        });
    }

    void CHttpMailServer::OnTimer()
    {
        SetTimer();
        m_loger->info("CHttpMailServer On Timer");
    }
}