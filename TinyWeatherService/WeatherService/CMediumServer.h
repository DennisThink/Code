/**
 * @file CMediumServer.h
 * @author DennisMi (https://www.dennisthink.com/)
 * @brief 总控类
 * @version 0.1
 * @date 2019-08-30
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef _MEDIUM_SERVER_C_MEDIUM_SERVER_H_
#define _MEDIUM_SERVER_C_MEDIUM_SERVER_H_

#include <functional>

#include <map>
#include "Log.h"
#include "asio_common.h"
#include "json11.hpp"

#include "CHttpServer.h"
#include "planform.h"
#include "CommonMsg.h"

namespace ClientCore
{
using tcp = asio::ip::tcp;
class CClientSess;
class CMediumServer : public std::enable_shared_from_this<CMediumServer>
{
  protected:
    asio::io_service &m_ioService;

    tcp::socket m_socket;

    tcp::acceptor m_acceptor;

    //服务器的IP端口设置
    IpPortCfg m_serverCfg;

	CMySqlConfig m_mysqlCfg;

    std::shared_ptr<asio::high_resolution_timer> m_timer = nullptr;

	std::shared_ptr<CHttpServer> m_httpServer;
    void SetTimer(int nSeconds);
    void OnTimer();

    std::error_code m_ec;

    void do_accept();

  public:
    static std::shared_ptr<spdlog::logger> ms_loger;
    inline IpPortCfg &config() { return m_serverCfg; }

	void SendBack(const std::shared_ptr<CClientSess>& pClientSess, const std::string msg);

    void CheckAllConnect();

    CMediumServer(asio::io_service &io_service)
        : m_ioService(io_service), m_socket(io_service), m_acceptor(io_service)
    {
        if (!m_timer)
        {
            m_timer = std::make_shared<asio::high_resolution_timer>(m_ioService);
        }
		m_httpServer = std::make_shared<CHttpServer>(m_ioService,this);
    }

	void start(const std::function<void(const std::error_code &)> &callback);

    void loadConfig(const json11::Json &cfg, std::error_code &ec);
    //获取server的ip和端口,
    std::string getServerIpPort();
private:

};
} // namespace MediumServer

#endif // HTTP2T1_CAGENTSERVER_H
