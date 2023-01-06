/**
 * @file CMediumServer.cpp
 * @author DennisMi (https://www.dennisthink.com/)
 * @brief 
 * @version 0.1
 * @date 2019-09-12
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include "CMediumServer.h"
#include "json11.hpp"
#include "DaemonSvcApp.h"
namespace ClientCore
{
std::shared_ptr<spdlog::logger> CMediumServer::ms_loger;

/**
 * @brief 加载配置文件
 * 
 * @param cfg 配置文件的json
 * @param ec 发生的异常
 */
void CMediumServer::loadConfig(const json11::Json &cfg, std::error_code& ec) 
{
	auto serverCfg = cfg["server"];
	LOG_INFO(ms_loger,"loadConfig");
    ec.clear();
    m_serverCfg.m_strServerIp=serverCfg["ip"].string_value();
    m_serverCfg.m_nPort=(uint16_t)serverCfg["port"].int_value();
    LOG_INFO(ms_loger,"ServerIp: {}",m_serverCfg.to_string());
    if(!m_serverCfg.Valid())
	{
		LOG_ERR(ms_loger,"Config Error {}",m_serverCfg.to_string());
        return;
    }
	if (cfg["mysql"].is_object())
	{
		m_mysqlCfg.FromJson(cfg["mysql"]);
	}

}


/**
 * @brief 启动服务
 * 
 * @param callback 
 */
void CMediumServer::start(const std::function<void(const std::error_code &)> &callback)
{
	if (!m_serverCfg.Valid())
	{
		LOG_ERR(ms_loger, "ServerConfig Is Error {}", m_serverCfg.to_string());
		LOG_WARN(ms_loger, "Bind To {} Failed [{} {}]", m_serverCfg.to_string(), __FILENAME__, __LINE__);
#ifndef WIN32
		exit(BIND_FAILED_EXIT);
#endif
	}
	else
	{
		SetTimer(5);
		do_accept();
		m_httpServer->Start(m_serverCfg,m_mysqlCfg);
		m_httpServer->ms_loger = ms_loger;

	}
	std::error_code ec;
	callback(ec);
}
/**
 * @brief 检查所有的socket连接
 * 
 */
void CMediumServer::CheckAllConnect()
{

}

/**
 * @brief 接受来自客户端的连接
 * 
 */
void CMediumServer::do_accept() 
{

}


/**
 * @brief 响应定时器的任务，一些需要定时处理的任务，可以写成一个函数，在此函数中调用
 * 
 */
void CMediumServer::OnTimer()
{
	CheckAllConnect();
}

/**
 * @brief 设置定时器，单位秒
 * 
 * @param nSeconds 定时的秒数
 */
void CMediumServer::SetTimer(int nSeconds)
{
	if(m_timer)
	{
		m_timer->expires_from_now(std::chrono::seconds(nSeconds));
		auto self = shared_from_this();
		m_timer->async_wait([this,nSeconds,self](const std::error_code& ec){
			if(!ec)
			{
				LOG_INFO(this->ms_loger,"On Timer at MediumServer [{} {}]",__FILENAME__, __LINE__);
				this->OnTimer();
				this->SetTimer(nSeconds);
			}
			else
			{
				LOG_WARN(this->ms_loger,"On Timer at MediumServer {} [{} {}]",ec.message(),__FILENAME__, __LINE__);
			}
		});
	}
}

/**
 * @brief 获取Listen的服务器的IP和端口
 * 
 * @return std::string 
 */
std::string CMediumServer::getServerIpPort()
{
	return m_serverCfg.to_string();
}

}