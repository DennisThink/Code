

#include "CMediumServer.h"
#include "json11.hpp"
#include "DaemonSvcApp.h"
namespace MediumServer
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
	INFO(ms_loger,"loadConfig");
    ec.clear();
    m_serverCfg.m_strServerIp=serverCfg["ip"].string_value();
    m_serverCfg.m_nPort=(uint16_t)serverCfg["port"].int_value();
    INFO(ms_loger,"ServerIp: {}",m_serverCfg.to_string());
    if(!m_serverCfg.Valid())
	{
		ERR(ms_loger,"Config Error {}",m_serverCfg.to_string());
        return;
    }

	auto clientsCfg = cfg["clients"];
	if(!clientsCfg.is_array())
	{
		ERR(ms_loger,"Clients Config Error {}",cfg.string_value());
        return;
	}
	for(auto item:clientsCfg.array_items())
	{
		IpPortCfg clientCfg;
		clientCfg.m_strServerIp = item["ip"].string_value();
		clientCfg.m_nPort = item["port"].int_value();
		INFO(ms_loger,"Client Config: {}",clientCfg.to_string());
		m_clientCfgVec.push_back(clientCfg);
	}
}


/**
 * @brief 检查所有的socket连接
 * 
 */
void CMediumServer::CheckAllConnect()
{
	for(auto item = m_listenList.begin() ; item != m_listenList.end() ; item++)
	{
		if((*item)->IsConnected())
		{
			INFO(ms_loger,"Client is Connected");
		}
		else
		{
			INFO(ms_loger,"Client is Closed");
			m_listenList.erase(item);
			break;
		}
	}
}

/**
 * @brief 接受来自客户端的连接
 * 
 */
void CMediumServer::do_accept() 
{
		INFO(ms_loger,"CMediumServer do_accept");
        m_acceptor.async_accept(m_socket, [this](std::error_code ec) {
            if (!ec)
			{
			   INFO(ms_loger,"Server accept Successed");
               auto agentSess= std::make_shared<CServerSess>(std::move(m_socket),this);
			   agentSess->Start();
			   m_listenList.push_back(agentSess);
			}
            do_accept();
        });
}

/**
 * @brief 响应定时器的任务，一些需要定时处理的任务，可以写成一个函数，在此函数中调用
 * 
 */
void CMediumServer::OnTimer()
{
	INFO(this->ms_loger,"On Timer at APNsServer");
	for(auto& item:m_queueVec)
	{
		item->OnTimer();
	}
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
				INFO(this->ms_loger,"On Timer at APNsServer");
				this->OnTimer();
				this->SetTimer(nSeconds);
			}
			else
			{
				WARN(this->ms_loger,"On Timer at APNsServer {}",ec.message());
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

/**
 * @brief 处理从ClientSess中，回传的消息
 * 
 * @param msg 消息
 */
void CMediumServer::SendBack(const TransBaseMsg_t *msg)
{
	if(msg)
	{
		INFO(ms_loger,"{}",msg->to_string());
	}
}
}