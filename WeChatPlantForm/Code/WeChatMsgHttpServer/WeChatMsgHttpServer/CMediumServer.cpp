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
#include "WXCommonMsg.h"
#include "EncodingUtil.h"

//退出聊天菜单指令代码
const static std::string MENU_QUIT_CHAT_QUIT_MATCH = "101";

//退出聊天菜单指令字符串
const static std::string MENU_QUIT_CHAT_QUIT_MATCH_STR = "退出聊天";

//换人聊天菜单指令代码
const static std::string MENU_QUIT_CHAT_CONTIN_MATCH = "102";

//换人聊天菜单指令字符串
const static std::string MENU_QUIT_CHAT_CONTIN_MATCH_STR = "换人聊天";

//进入聊天的命令
const static std::string G_START_MATCH_CMD = "匹配";

//退出聊天的命令
const static std::string G_QUIT_MATCH_CMD = "退出";

//匹配指令错误的时候,提示消息
const static std::string G_WRONG_MATCH_CMD_TIPS = "输入\n \"匹配\" \n ,可以开始聊天,输入 \n \"退出\" \n 可以结束聊天";

//等待匹配的时候,提示消息
const static std::string G_WAIT_MATCH_TIPS = "系统正在为您匹配,输入\n \"退出\" \n 可以换人聊天";

//管理员微信
const static std::string G_MANAGER_WECHAT = "管理员微信: miyanhui1990";

//退出匹配的时候,提示消息
const static std::string G_QUIT_CHAT_TIPS = "您已退出聊天\n感谢您使用本软件\n,如果有任何建议和意见,请联系管理员\n";

namespace ClientCore
{
std::shared_ptr<spdlog::logger> CMediumServer::ms_loger;

/**
 * @brief 加载配置文件
 * 
 * @param cfg 配置文件的json
 * @param ec 发生的异常
 */
bool CMediumServer::loadConfig(const json11::Json &cfg) 
{
	if (!cfg["server"].is_object())
	{
		return false;
	}
	auto serverCfg = cfg["server"];
	LOG_INFO(ms_loger,"loadConfig");
	if (serverCfg["ip"].is_string())
	{
		m_serverCfg.m_strServerIp = serverCfg["ip"].string_value();
	}
	else
	{
		return false;
	}
	if (serverCfg["port"].is_number())
	{
		m_serverCfg.m_nPort = (uint16_t)serverCfg["port"].int_value();
	}
	else
	{
		return false;
	}
    LOG_INFO(ms_loger,"ServerIp: {}",m_serverCfg.to_string());
    if(!m_serverCfg.Valid())
	{
		LOG_ERR(ms_loger,"Config Error {}",m_serverCfg.to_string());
        return false;
    }

	{

		auto wxCfgJson = cfg["wechat"];
		if (wxCfgJson["token"].is_string())
		{
			m_WXCfg.m_strToken = wxCfgJson["token"].string_value();
		}
		else
		{
			return false;
		}

		if (wxCfgJson["appid"].is_string())
		{
			m_WXCfg.m_strAppId = wxCfgJson["appid"].string_value();
		}
		else
		{
			return false;
		}

		if (wxCfgJson["secrect"].is_string())
		{
			m_WXCfg.m_strAppSecrect = wxCfgJson["secrect"].string_value();
		}
		else
		{
			return false;
		}

		if (wxCfgJson["startHour"].is_number())
		{
			m_WXCfg.m_startHour = wxCfgJson["startHour"].int_value();
		}
		else
		{
			return false;
		}

		if (wxCfgJson["endHour"].is_number())
		{
			m_WXCfg.m_endHour = wxCfgJson["endHour"].int_value();
		}
		else
		{
			return false;
		}
	}
	return true;
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
		SetTimer(30);
		do_accept();
		m_httpServer->Start(m_serverCfg,m_WXCfg.m_strToken);
		m_managerUtil = std::make_shared<CWXManager>(m_WXCfg.m_strAppId,m_WXCfg.m_strAppSecrect);
		if (m_managerUtil)
		{
			m_managerUtil->GetAccessToken();
			m_tmGetTokenTime = time(nullptr);
		}
		std::error_code ec;
		callback(ec);
	}
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
	time_t nowTime = time(nullptr);
	//TODO : Token过期时间
	if (nowTime - m_tmGetTokenTime >= 7200)
	{
		if (m_managerUtil)
		{
			m_managerUtil->GetAccessToken();
			m_tmGetTokenTime = nowTime;
			LOG_INFO(ms_loger, "Get Token: [{} {}]", __FILENAME__, __LINE__);
		}
	}
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


bool CMediumServer::IsInChatTime()
{
	auto tmpTime = time(nullptr);
	struct tm curTimePart;
	localtime_s(&curTimePart,&tmpTime);
	if ((curTimePart.tm_hour >= m_WXCfg.m_startHour) &&
		(curTimePart.tm_hour < m_WXCfg.m_endHour) &&
		(curTimePart.tm_min > 0)
		)
	{
		return true;
	}
	else
	{
		return false;
	}
}
/**
 * @brief 处理从公众号服务器过来的消息
 * 
 * @param strPost 公众号服务器发送的XML格式消息
 * @return std::string 被动消息回复内容
 */
std::string CMediumServer::HandlePost(const std::string& strPost)
{
		std::string strRsp;
		WXMsgType type = ParseMsgType(strPost);
		switch (type)
		{
		case WXMsgType::UserSendTxt:
		{
			UserSendTxtMsg reqMsg;
			if (reqMsg.FromString(strPost))
			{
				if (IsInChatTime())
				{
					return HandleTxtMsg(reqMsg);
				}
				else
				{
					std::string strMsg = "当前时间不是聊天时间,请在 " + std::to_string(m_WXCfg.m_endHour) + "---" + std::to_string(m_WXCfg.m_endHour) + "之间聊天";
					UserRecvTxtMsg rspMsg;
					rspMsg.m_strFromUserName = reqMsg.m_strToUserName;
					rspMsg.m_strToUserName = reqMsg.m_strFromUserName;
					rspMsg.m_strContent = EncodeUtil::AnsiToUtf8(strMsg);
					return  rspMsg.ToString();
				}
			}
		}break;
		case WXMsgType::UserSendImage:
		{
			UserSendImageMsg reqMsg;
			if (reqMsg.FromString(strPost))
			{
				UserRecvTxtMsg rspMsg;
				rspMsg.m_strContent = EncodeUtil::AnsiToUtf8(std::string("暂不支持图片消息"));
				rspMsg.m_strFromUserName = reqMsg.m_strToUserName;
				rspMsg.m_strToUserName = reqMsg.m_strFromUserName;
				rspMsg.m_strCreateTime = std::to_string(time(nullptr));
				strRsp = rspMsg.ToString();
			}
		}break;
		case WXMsgType::UserSendVoice:
		{
			UserSendVoiceMsg reqMsg;
			if (reqMsg.FromString(strPost))
			{
				UserRecvTxtMsg rspMsg;
				rspMsg.m_strContent = EncodeUtil::AnsiToUtf8(std::string("暂不支持语音消息"));
				rspMsg.m_strFromUserName = reqMsg.m_strToUserName;
				rspMsg.m_strToUserName = reqMsg.m_strFromUserName;
				rspMsg.m_strCreateTime = std::to_string(time(nullptr));
				strRsp = rspMsg.ToString();
			}
		}break;
		case WXMsgType::UserSendVideo:
		{
			UserSendVideoMsg reqMsg;
			if (reqMsg.FromString(strPost))
			{
				UserRecvTxtMsg rspMsg;
				rspMsg.m_strContent = EncodeUtil::AnsiToUtf8(std::string("暂不支持视频消息"));
				rspMsg.m_strFromUserName = reqMsg.m_strToUserName;
				rspMsg.m_strToUserName = reqMsg.m_strFromUserName;
				rspMsg.m_strCreateTime = std::to_string(time(nullptr));
				strRsp = rspMsg.ToString();
			}
		}break;
		case WXMsgType::UserSendShortVideo:
		{
			UserSendShortVideoMsg reqMsg;
			if (reqMsg.FromString(strPost))
			{
				UserRecvTxtMsg rspMsg;
				rspMsg.m_strContent = EncodeUtil::AnsiToUtf8(std::string("暂不支持短视频消息"));
				rspMsg.m_strFromUserName = reqMsg.m_strToUserName;
				rspMsg.m_strToUserName = reqMsg.m_strFromUserName;
				rspMsg.m_strCreateTime = std::to_string(time(nullptr));
				strRsp = rspMsg.ToString();
			}
		}break;
		case WXMsgType::UserSendLocation:
		{
			UserSendLocationMsg reqMsg;
			if (reqMsg.FromString(strPost))
			{
				UserRecvTxtMsg rspMsg;
				rspMsg.m_strContent = EncodeUtil::AnsiToUtf8(std::string("暂不支持地址消息"));
				rspMsg.m_strFromUserName = reqMsg.m_strToUserName;
				rspMsg.m_strToUserName = reqMsg.m_strFromUserName;
				rspMsg.m_strCreateTime = std::to_string(time(nullptr));
				strRsp = rspMsg.ToString();
			}
		}break;
		case WXMsgType::UserSendLink:
		{
			UserSendLinkMsg reqMsg;
			if (reqMsg.FromString(strPost))
			{
				UserRecvTxtMsg rspMsg;
				rspMsg.m_strContent = EncodeUtil::AnsiToUtf8(std::string("暂不支持超链接消息"));
				rspMsg.m_strFromUserName = reqMsg.m_strToUserName;
				rspMsg.m_strToUserName = reqMsg.m_strFromUserName;
				rspMsg.m_strCreateTime = std::to_string(time(nullptr));
				strRsp = rspMsg.ToString();
			}
		}break;
		case WXMsgType::UserSendMenuChoice:
		{
			UserSendMenuChoiceMsg reqMsg;
			if (reqMsg.FromString(strPost))
			{
				HandleMenuMsg(reqMsg);
			}
		}break;
		default:
		{
		}
		}
		return strRsp;
}

/**
 * @brief 解除UserId和MatchId的匹配关系
 * 
 * @param strUserId 主动解除匹配的用户的Openid
 * @param strMatchId 被动解除匹配的用户的openid
 * @return true 解除成功
 * @return false 解除失败
 */
bool CMediumServer::DisMatchUser(const std::string& strUserId, const std::string& strMatchId)
{
	{
		SendCustomerTextMsgReq cusMsg;
		cusMsg.m_strToUser = strMatchId;
		cusMsg.m_strContext = EncodeUtil::AnsiToUtf8(std::string("对方已经和你解除聊天"));
		m_managerUtil->SendCustomerTxtMsg(cusMsg);
	}
	{
		SendCustomerTextMsgReq cusMsg;
		cusMsg.m_strToUser = strUserId;
		cusMsg.m_strContext = EncodeUtil::AnsiToUtf8(std::string("你已经和对方解除聊天: "));
		m_managerUtil->SendCustomerTxtMsg(cusMsg);
	}
	m_matchMap.erase(strUserId);
	m_matchMap.erase(strMatchId);
	return true;
}

/**
 * @brief 处理用户的菜单选择消息
 * 
 * @param reqMsg 菜单消息
 * @return std::string 被动回复消息
 */
std::string CMediumServer::HandleMenuMsg(const UserSendMenuChoiceMsg& reqMsg)
{
	if (MENU_QUIT_CHAT_QUIT_MATCH == reqMsg.m_strBizMsgMenuId)
	{
		std::string strMatchId;
		if (IsUserMatched(reqMsg.m_strFromUserName, strMatchId))
		{
			DisMatchUser(reqMsg.m_strFromUserName, strMatchId);
			m_strActiveVec.push_back(strMatchId);
			{
				SendCustomerTextMsgReq cusMsg;
				cusMsg.m_strToUser = reqMsg.m_strFromUserName;
				cusMsg.m_strContext = EncodeUtil::AnsiToUtf8(G_QUIT_CHAT_TIPS+G_MANAGER_WECHAT);
				m_managerUtil->SendCustomerTxtMsg(cusMsg);
			}
			{
				SendCustomerTextMsgReq cusMsg;
				cusMsg.m_strToUser = strMatchId;
				cusMsg.m_strContext = EncodeUtil::AnsiToUtf8(std::string("对方已经退出聊天,系统会继续为您匹配"));
				m_managerUtil->SendCustomerTxtMsg(cusMsg);
			}
		}
		else
		{
			SendCustomerTextMsgReq cusMsg;
			cusMsg.m_strToUser = reqMsg.m_strFromUserName;
			cusMsg.m_strContext = EncodeUtil::AnsiToUtf8(G_QUIT_CHAT_TIPS+G_MANAGER_WECHAT);
			m_managerUtil->SendCustomerTxtMsg(cusMsg);
			if (!m_strActiveVec.empty())
			{
				auto item = std::find(m_strActiveVec.begin(), m_strActiveVec.end(), reqMsg.m_strFromUserName);
				m_strActiveVec.erase(item);
				LOG_INFO(ms_loger, "User:{} Quit all [{} {}]", reqMsg.m_strFromUserName, __FILENAME__, __LINE__);
			}
			else
			{
				LOG_ERR(ms_loger, "User:{} Quit all [{} {}]", reqMsg.m_strFromUserName, __FILENAME__, __LINE__);
			}
		}
	}
	else if(MENU_QUIT_CHAT_CONTIN_MATCH == reqMsg.m_strBizMsgMenuId)
	{
		std::string strMatchId;
		if (IsUserMatched(reqMsg.m_strFromUserName, strMatchId))
		{
			DisMatchUser(reqMsg.m_strFromUserName, strMatchId);
			SendChoiceMenu(reqMsg.m_strFromUserName);
			SendChoiceMenu(strMatchId);
			m_strActiveVec.push_back(reqMsg.m_strFromUserName);
			m_strActiveVec.push_back(strMatchId);
		}
		else
		{
			SendCustomerTextMsgReq cusMsg;
			cusMsg.m_strToUser = reqMsg.m_strFromUserName;
			cusMsg.m_strContext = EncodeUtil::AnsiToUtf8(std::string("系统会继续为您匹配"));
			m_managerUtil->SendCustomerTxtMsg(cusMsg);
			LOG_ERR(ms_loger, "ERROR:{} [{} {}]", reqMsg.m_strFromUserName, __FILENAME__, __LINE__);
		}
	}
	return "";
}

/**
 * @brief 根据用户openid获取昵称
 * 
 * @param strUserId 用户openid
 * @return std::string 用户的昵称
 */
std::string CMediumServer::GetNickName(const std::string& strUserId)
{
	if (!strUserId.empty())
	{
		auto item = m_strNickNameMap.find(strUserId);
		if (item != m_strNickNameMap.end())
		{
			return item->second + EncodeUtil::AnsiToUtf8(std::string(" 说: "));
		}
		else
		{
			if (m_managerUtil)
			{
				auto rspMsg = m_managerUtil->GetUserBaseInfo(strUserId);
				m_strNickNameMap.insert({ strUserId,rspMsg.m_strNickName });
				return GetNickName(strUserId);
			}
		}
	}
	return EncodeUtil::AnsiToUtf8(std::string("匿名说: "));
}

/**
 * @brief 给用户发送菜单消息
 * 
 * @param strUserId 用户的openid
 * @return true 成功
 * @return false 失败
 */
bool CMediumServer::SendChoiceMenu(const std::string strUserId)
{
	{
		SendCustomerMenuMsgReq menuMsg;
		menuMsg.m_strHeadContent = EncodeUtil::AnsiToUtf8(std::string("欢迎使用聊天系统"));
		menuMsg.m_strToUser = strUserId;
		menuMsg.m_strTailContent = EncodeUtil::AnsiToUtf8(std::string("感谢使用聊天系统"));
		{
			MsgMenuElem elem;
			elem.m_strId = MENU_QUIT_CHAT_QUIT_MATCH;
			elem.m_strContent = EncodeUtil::AnsiToUtf8(MENU_QUIT_CHAT_QUIT_MATCH_STR);
			menuMsg.m_vecMenus.push_back(elem);
		}
		{
			MsgMenuElem elem;
			elem.m_strId = MENU_QUIT_CHAT_CONTIN_MATCH;
			elem.m_strContent = EncodeUtil::AnsiToUtf8(MENU_QUIT_CHAT_CONTIN_MATCH_STR);
			menuMsg.m_vecMenus.push_back(elem);

		}
		if (m_managerUtil)
		{
			m_managerUtil->SendCustomerMenuMsg(menuMsg);
		}
	}

	return true;
}

/**
 * @brief 处理用户发送的文本消息
 * 
 * @param reqMsg 用户发送的文字消息
 * @return std::string 被动回复的消息
 */
std::string CMediumServer::HandleTxtMsg(const UserSendTxtMsg& reqMsg)
{
	std::string strMatchId;
	if (IsUserMatched(reqMsg.m_strFromUserName,strMatchId))
	{
		if (IsQuitChatCmd(reqMsg.m_strContent))
		{
			SendChoiceMenu(reqMsg.m_strFromUserName);
		}
		else
		{
			SendCustomerTextMsgReq cusMsg;
			cusMsg.m_strToUser = strMatchId;
			cusMsg.m_strContext = GetNickName(reqMsg.m_strFromUserName) + reqMsg.m_strContent;
			m_managerUtil->SendCustomerTxtMsg(cusMsg);
		}
	}
	else
	{
		if (IsUserActived(reqMsg.m_strFromUserName))
		{
			if (IsQuitChatCmd(reqMsg.m_strContent))
			{
				SendChoiceMenu(reqMsg.m_strFromUserName);
			}
			else
			{
				UserRecvTxtMsg rspMsg;
				rspMsg.m_strFromUserName = reqMsg.m_strToUserName;
				rspMsg.m_strToUserName = reqMsg.m_strFromUserName;
				rspMsg.m_strContent = EncodeUtil::AnsiToUtf8(G_WAIT_MATCH_TIPS);
				return  rspMsg.ToString();
			}
		}
		else
		{
			if (IsEnterChatCmd(reqMsg.m_strContent))
			{
				m_strActiveVec.push_back(reqMsg.m_strFromUserName);
				if (MatchUser(reqMsg.m_strFromUserName, strMatchId))
				{
					m_matchMap.insert({ reqMsg.m_strFromUserName,strMatchId });
					m_matchMap.insert({ strMatchId,reqMsg.m_strFromUserName });
					if (m_managerUtil)
					{
						SendCustomerTextMsgReq reqMsg;
						reqMsg.m_strToUser = strMatchId;
						reqMsg.m_strContext = EncodeUtil::AnsiToUtf8(std::string("聊天对象已经匹配,可以开始聊天了"));
						m_managerUtil->SendCustomerTxtMsg(reqMsg);
					}
					{
						UserRecvTxtMsg rspMsg;
						rspMsg.m_strFromUserName = reqMsg.m_strToUserName;
						rspMsg.m_strToUserName = reqMsg.m_strFromUserName;
						rspMsg.m_strContent = EncodeUtil::AnsiToUtf8(std::string("聊天对象已经匹配,可以开始聊天了"));
						return  rspMsg.ToString();
					}
				}
				else
				{
					UserRecvTxtMsg rspMsg;
					rspMsg.m_strFromUserName = reqMsg.m_strToUserName;
					rspMsg.m_strToUserName = reqMsg.m_strFromUserName;
					rspMsg.m_strContent = EncodeUtil::AnsiToUtf8(G_WAIT_MATCH_TIPS);
					return  rspMsg.ToString();
				}
			}
			else
			{
				UserRecvTxtMsg rspMsg;
				rspMsg.m_strFromUserName = reqMsg.m_strToUserName;
				rspMsg.m_strToUserName = reqMsg.m_strFromUserName;
				rspMsg.m_strContent = EncodeUtil::AnsiToUtf8(G_WRONG_MATCH_CMD_TIPS);
				return  rspMsg.ToString();
			}
		}
	}
	return "";
}

/**
 * @brief 根据用户的openid判断用户是否已经激活
 * 
 * @param strUserId 用户的openid
 * @return true 已激活
 * @return false 未激活
 */
bool CMediumServer::IsUserActived(const std::string& strUserId)
{
	if (m_strActiveVec.empty())
	{
		return false;
	}
	else
	{
		return m_strActiveVec.end() != std::find(m_strActiveVec.begin(), m_strActiveVec.end(),strUserId);
	}
}


/**
 * @brief 判断某个用户是否有匹配的聊天对象
 * 
 * @param strUserId 用户的openid
 * @param strMatchId 匹配者的openid(返回参数)
 * @return true 有匹配者
 * @return false 没有匹配者
 */
bool CMediumServer::IsUserMatched(const std::string& strUserId, std::string& strMatchId)
{
	if (m_matchMap.empty())
	{
		return false;
	}
	else
	{
		auto item = m_matchMap.find(strUserId);
		if (item != m_matchMap.end())
		{
			strMatchId = item->second;
			return true;
		}
		else
		{
			return false;
		}
	}
}

/**
 * @brief 是否为进入聊天指令
 * 
 * @param strUserCmd 用户输入的指令 
 * @return true 是进入聊天
 * @return false 不是进入聊天
 */
bool CMediumServer::IsEnterChatCmd(const std::string& strUserCmd)
{
	if (strUserCmd == EncodeUtil::AnsiToUtf8(G_START_MATCH_CMD))
	{
		return true;
	}
	else
	{
		return false;
	}
}

/**
 * @brief 是否为退出聊天指令
 * 
 * @param strUserCmd 用户输入的指令
 * @return true 是退出聊天
 * @return false 不是退出聊天
 */
bool CMediumServer::IsQuitChatCmd(const std::string& strUserCmd)
{
	if (strUserCmd == EncodeUtil::AnsiToUtf8(G_QUIT_MATCH_CMD))
	{
		return true;
	}
	else
	{
		return false;
	}
}
/**
 * @brief 是否为聊天激活码
 * 
 * @param strActiveCode 用户输入的内容 
 * @return true 是激活码
 * @return false 不是激活码
 */
bool CMediumServer::IsActiveCode(const std::string& strActiveCode)
{
	if (strActiveCode == "1990")
	{
		return true;
	}
	else
	{
		return false;
	}
}

/**
 * @brief 对用户进行匹配
 * 
 * @param strUserId 待匹配的用户的openid
 * @param strMatchId 匹配成功的用户的openid(返回参数)
 * @return true 匹配成功
 * @return false 匹配失败
 */
bool CMediumServer::MatchUser(const std::string& strUserId,std::string& strMatchId)
{
	if (IsUserActived(strUserId))
	{
		if (m_strActiveVec.size() >= 2)
		{
			auto item = std::find(m_strActiveVec.begin(), m_strActiveVec.end(), strUserId);
			m_strActiveVec.erase(item);
			strMatchId = m_strActiveVec[0];
			m_strActiveVec.erase(m_strActiveVec.begin());
			return true;
		}
	}
	return false;
}

}