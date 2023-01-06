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
#include "WXCommonMsg.h"
#include "WXManager.h"
#include "CommonConfig.h"
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

	WeChatMpConfig m_WXCfg;//公众号平台的相关设置

    std::shared_ptr<asio::high_resolution_timer> m_timer = nullptr;

	std::shared_ptr<CHttpServer> m_httpServer;
    void SetTimer(int nSeconds);
    void OnTimer();

    std::error_code m_ec;

    void do_accept();

  public:
	std::string HandlePost(const std::string& strPost);
	
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

		m_managerUtil->m_loger = ms_loger;
    }

	void start(const std::function<void(const std::error_code &)> &callback);

    bool loadConfig(const json11::Json &cfg);
    //获取server的ip和端口,
    std::string getServerIpPort();
private:
	std::string HandleTxtMsg(const UserSendTxtMsg& reqMsg);
	std::string HandleMenuMsg(const UserSendMenuChoiceMsg& reqMsg);
	std::string GetNickName(const std::string& strUserId);
	bool SendChoiceMenu(const std::string strUserId);
	bool DisMatchUser(const std::string& strUserId, const std::string& strMatchId);
	bool IsUserActived(const std::string& strUserId);
	bool IsUserMatched(const std::string& strUserId, std::string& strMatchId);
	
	bool IsEnterChatCmd(const std::string& strUserCmd);

	bool IsQuitChatCmd(const std::string& strUserCmd);

	bool IsActiveCode(const std::string& strActiveCode);
	bool MatchUser(const std::string& strUserId,std::string& strMatchId);
	bool IsInChatTime();
    std::vector<std::string> m_strActiveVec; //记录已经Active的openid

	std::shared_ptr<CWXManager> m_managerUtil;//发送客服消息的工具
	std::map<std::string, std::string> m_matchMap;//记录聊天的匹配关系
	std::map<std::string, std::string> m_strNickNameMap;//openID和昵称的对应关系Map
	time_t m_tmGetTokenTime;//最近获取AccessToken的时间,用来检查Token是否过期
};
} // namespace MediumServer

#endif // HTTP2T1_CAGENTSERVER_H
