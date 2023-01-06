#include "CSessManager.h"
#include "CClientSess.h"
#include "CSourceServer.h"
#include <algorithm>
using namespace SourceServer;
namespace SourceServer
{
std::shared_ptr<spdlog::logger> CSessManager::ms_loger;

/**
 * @brief 启动SessManager
 * 
 * @param pServer SouceServer服务类
 * @param ioService asio::io_service 实例
 * @param ec 发生的异常
 */
void CSessManager::start(CSourceServer *pServer, asio::io_service &ioService, std::error_code &ec)
{
	INFO(ms_loger, "Queue Start");
	m_server = pServer;

	int nSessIndex = 0;
	auto pSess = std::make_shared<CClientSess>(ioService, m_config.m_strServerIp, m_config.m_nPort, this);
	if (pSess)
	{
		INFO(ms_loger, "Add Sess To Map");
		m_SessMap.insert(std::pair<int, std::shared_ptr<CClientSess>>(nSessIndex, pSess));
	}
	nSessIndex++;

	for (auto &item : m_SessMap)
	{
		WARN(ms_loger, "Sess id:{}  Connect:{}", item.first, item.second->GetConnectInfo());
		item.second->StartConnect();
	}
	ec.clear();
}

/**
 * @brief 检查所有的连接
 * 
 */
void CSessManager::CheckSessConn()
{
	for (auto &item : m_SessMap)
	{
		item.second->SendKeepAlive();
	}
}

/**
 * @brief 响应定时器
 * 
 */
void CSessManager::OnTimer()
{
	INFO(this->ms_loger, "Queue On Timer");
	CheckSessConn();
}

/**
 * @brief 响应收到的消息
 * 
 * @param pMsg 接收到的消息
 */
void CSessManager::handleMessage(const TransBaseMsg_t *pMsg)
{
	if (nullptr != pMsg)
	{
		m_server->handleMessage(pMsg);
	}
}
} // namespace SourceServer