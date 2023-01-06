/**
 * @file WXManager.h
 * @author DennisMi (https://www.dennisthink.com/)
 * @brief 公众号管理的类的头文件
 * @version 0.1
 * @date 2020-03-22
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#ifndef _DENNIS_THINK_WX_MANAGER_H_
#define _DENNIS_THINK_WX_MANAGER_H_
#include "../include/thirdparty/httpServer/client_https.hpp"
#include "WXManagerMsg.h"
#include "Log.h"
using HttpClient = SimpleWeb::Client<SimpleWeb::HTTPS>;
class CWXManager
{
public:
	static std::shared_ptr<spdlog::logger> m_loger;
    CWXManager(const std::string strAppId,const std::string strAppSecrect);
    bool GetAccessToken();
	bool GetUserList();
	bool SendCustomerMsg();
	bool GetUserBaseInfo();
	GetUserBaseInfoRsp GetUserBaseInfo(const std::string& strUserId);


	bool SendCustomerTxtMsg(const SendCustomerTextMsgReq& reqMsg);
	bool SendCustomerImageMsg(const SendCustomerImageMsgReq& reqMsg);
	bool SendCustomerVoiceMsg(const SendCustomerVoiceMsgReq& reqMsg);
	bool SendCustomerVideoMsg(const SendCustomerVideoMsgReq& reqMsg);
	bool SendCustomerMusicMsg(const SendCustomerMusicMsgReq& reqMsg);
	bool SendCustomerNewsMsg(const SendCustomerNewsMsgReq& reqMsg);
	bool SendCustomerMenuMsg(const SendCustomerMenuMsgReq& reqMsg);
private:

	bool SendCustomerTxtMsg_Demo();
	bool SendCustomerImageMsg_Demo();
	bool SendCustomerVoiceMsg_Demo();
	bool SendCustomerVideoMsg_Demo();
	bool SendCustomerMusicMsg_Demo();
	bool SendCustomerMPNewsMsg_Demo();
	bool SendCustomerNewsMsg_Demo();
	bool SendCustomerMenuMsg_Demo();

	bool SendCustomerMsg(const std::string targetId, const std::string strMsg);
	bool SendCustomerMsg_Core(const std::string& strPost);
    std::string m_strAccessToken;//accessToken 定时获取
    std::string m_strAppId;//AppId 由公众号平台设置
    std::string m_strAppSecrect;//AppSecrect 由公众号平台设置
    std::shared_ptr<HttpClient> m_httpClient; //进行HTTP请求工具
	std::vector<std::string> m_userList;//关注者的openid列表
};
#endif