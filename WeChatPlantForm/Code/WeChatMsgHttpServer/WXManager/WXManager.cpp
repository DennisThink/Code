/**
 * @file WXManager.cpp
 * @author DennisMi (https://www.dennisthink.com/)
 * @brief 公众号管理的类的实现文件
 * @version 0.1
 * @date 2020-03-22
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include "WXManager.h"
#include "json11.hpp"
#include "WXManagerMsg.h"
std::shared_ptr<spdlog::logger> CWXManager::m_loger=nullptr;
/**
 * @brief Construct a new CWXManager::CWXManager object
 * 
 * @param strAppId 公众号AppId
 * @param strAppSecrect 公众号AppSecrect
 */
CWXManager::CWXManager(const std::string strAppId,const std::string strAppSecrect)
{
    m_strAppId =strAppId;
    m_strAppSecrect = strAppSecrect;
	//TODO: 此处需要改为对域名的解析
	m_httpClient = std::make_shared<HttpClient>("101.226.212.27",false);
}

/**
 * @brief 获取AccessToken
 * 
 * @return true 成功
 * @return false 失败
 */
bool  CWXManager::GetAccessToken()
{
	GetAccessTokenReq reqMsg;
	reqMsg.m_strAppId = m_strAppId;
	reqMsg.m_strGrantType = "client_credential";
	reqMsg.m_strSecrect = m_strAppSecrect;
	std::string strUrl = "/cgi-bin/token?";
	if (m_httpClient)
	{
		try
		{
			auto rsp = m_httpClient->request("GET",strUrl+reqMsg.ToString(),"");
			std::string strRsp = rsp->content.string();
			GetAccessTokenRsp rspMsg;
			if (rspMsg.FromString(strRsp))
			{
				LOG_INFO(m_loger, "Token: {} [{} {}]", rspMsg.m_strAccessToken, __FILENAME__, __LINE__);
				m_strAccessToken = rspMsg.m_strAccessToken;
			}
			else
			{
				LOG_INFO(m_loger, "RSP: {} [{} {}]",strRsp, __FILENAME__, __LINE__);
			}
		}
		catch (const SimpleWeb::system_error& e) {
			LOG_INFO(m_loger, "Client Req Error : {} [{} {}]", e.what(), __FILENAME__, __LINE__);
		}
	}
    return false;
}

/**
 * @brief 获取用户列表
 * 
 * @return true 成功
 * @return false 失败
 */
bool CWXManager::GetUserList()
{
	GetUserListReq reqMsg;
	reqMsg.m_strAccessToken = m_strAccessToken;
	if (m_httpClient)
	{
		try
		{
			std::string strUrl = "/cgi-bin/user/get?";
			auto rsp = m_httpClient->request("GET", strUrl+reqMsg.ToString(), "");
			std::string strRsp = rsp->content.string();
			LOG_INFO(m_loger, "RSP: {} [{} {}]", strRsp, __FILENAME__, __LINE__);
			GetUserListRsp rspMsg;
			if (rspMsg.FromString(strRsp))
			{
				m_userList = rspMsg.m_vecUserOpenId;
			}
			else
			{
			}
			//m_strAccessToken = ParseAccessToken(strRsp);
		}
		catch (const SimpleWeb::system_error& e) {
			LOG_INFO(m_loger, "RSP: {} [{} {}]", e.what(), __FILENAME__, __LINE__);
		}
	}
	return false;
}

/**
 * @brief 发送客服消息的核心函数,被每种客服消息调用
 * 
 * @param strPost 客服消息序列化后的JSON字符串
 * @return true 发送成功
 * @return false 发送失败
 */
bool CWXManager::SendCustomerMsg_Core(const std::string& strPost)
{
	LOG_INFO(m_loger,"CORE: {} [{} {}]",strPost,__FILENAME__, __LINE__);
	std::string strUrl = "/cgi-bin/message/custom/send?access_token=" + m_strAccessToken;
	try
	{
		auto rsp = m_httpClient->request("POST", strUrl, strPost);
		std::string strRsp = rsp->content.string();
		LOG_INFO(m_loger, "RSP: {} [{} {}]", strRsp, __FILENAME__, __LINE__);
		SendCustomerMsgRsp rspMsg;
		if (rspMsg.FromString(strRsp))
		{
			return rspMsg.m_strErrMsg == "ok";
		}
		else
		{
			return false;
		}
	}
	catch (const SimpleWeb::system_error& e) {
		LOG_INFO(m_loger, "RSP: {} [{} {}]", e.what(), __FILENAME__, __LINE__);
		return false;
	}

	return true;
}

/**
 * @brief 发送客服消息
 * 
 * @return true 成功
 * @return false 失败
 */
bool CWXManager::SendCustomerMsg()
{
	SendCustomerTxtMsg_Demo();
	SendCustomerImageMsg_Demo();
	SendCustomerMenuMsg_Demo();

	return true;
}

/**
 * @brief 发送客服文本消息示例
 * 
 * @return true 成功
 * @return false 失败
 */
bool CWXManager::SendCustomerTxtMsg_Demo()
{
	SendCustomerTextMsgReq reqMsg;
	for (auto item : m_userList)
	{
		reqMsg.m_strContext = "DennisThink Text";
		reqMsg.m_strToUser = item;
		SendCustomerTxtMsg(reqMsg);
	}
	return false;
}

/**
 * @brief 发送客服图像消息示例
 * 
 * @return true 成功
 * @return false 失败
 */
bool CWXManager::SendCustomerImageMsg_Demo()
{
	SendCustomerImageMsgReq reqMsg;
	for (auto item : m_userList)
	{
		reqMsg.m_strMediaId = "Media_Id";
		reqMsg.m_strToUser = item;
		SendCustomerImageMsg(reqMsg);
	}
	return false;
}

/**
 * @brief 发送客服语音消息的示例
 * 
 * @return true 
 * @return false 
 */
bool CWXManager::SendCustomerVoiceMsg_Demo()
{
	SendCustomerImageMsgReq reqMsg;
	for (auto item : m_userList)
	{
		reqMsg.m_strMediaId = "Media_Id";
		reqMsg.m_strToUser = item;
		SendCustomerImageMsg(reqMsg);
	}
	return false;
}

/**
 * @brief 发送客服视频消息的示例
 * 
 * @return true 
 * @return false 
 */
bool CWXManager::SendCustomerVideoMsg_Demo()
{
	SendCustomerVideoMsgReq reqMsg;
	for (auto item : m_userList)
	{
		reqMsg.m_strMediaId = "Media_Id";
		reqMsg.m_strToUser = item;
		SendCustomerVideoMsg(reqMsg);
	}
	return false;
}

/**
 * @brief 发送客服音乐消息的示例
 * 
 * @return true 
 * @return false 
 */
bool CWXManager::SendCustomerMusicMsg_Demo()
{
	SendCustomerVideoMsgReq reqMsg;
	for (auto item : m_userList)
	{
		reqMsg.m_strMediaId = "Media_Id";
		reqMsg.m_strToUser = item;
		SendCustomerVideoMsg(reqMsg);
	}
	return false;
}

/**
 * @brief 发送客服MPNews消息的示例
 * 
 * @return true 
 * @return false 
 */
bool CWXManager::SendCustomerMPNewsMsg_Demo()
{
	return false;
}

/**
 * @brief 发送客服News消息的示例
 * 
 * @return true 
 * @return false 
 */
bool CWXManager::SendCustomerNewsMsg_Demo()
{

	SendCustomerNewsMsgReq reqMsg;
	MsgArticleElem elem;
	elem.m_strTitle = "DennisThink Test";
	elem.m_strDescription = "Demo";
	elem.m_strPicUrl = "PicUrl";
	elem.m_strUrl = "Url";
	for (auto item : m_userList)
	{
		reqMsg.m_strToUser = item;
		reqMsg.m_article = elem;
		SendCustomerNewsMsg(reqMsg);
	}
	return false;
}

/**
 * @brief 发送客服菜单消息的示例
 * 
 * @return true 
 * @return false 
 */
bool CWXManager::SendCustomerMenuMsg_Demo()
{
	SendCustomerMenuMsgReq reqMsg;
	for (auto item : m_userList)
	{
		{
			reqMsg.m_strHeadContent = "Welcome To DennisThink " + item;
			reqMsg.m_strTailContent = "Thanks For Use DennisThink " + item;
			{
				MsgMenuElem elem1;
				elem1.m_strId = "101";
				elem1.m_strContent = "Start Chat";
				reqMsg.m_vecMenus.push_back(elem1);
			}

			{
				MsgMenuElem elem1;
				elem1.m_strId = "102";
				elem1.m_strContent = "Stop Chat";
				reqMsg.m_vecMenus.push_back(elem1);
			}

			reqMsg.m_strToUser = item;
		}
		SendCustomerMenuMsg(reqMsg);
	}
	return false;
}

/**
 * @brief 发送客服文本消息
 * 
 * @param reqMsg 待发送的消息
 * @return true 成功
 * @return false 失败
 */
bool CWXManager::SendCustomerTxtMsg(const SendCustomerTextMsgReq& reqMsg)
{
	std::string strRsp = reqMsg.ToString();
	return SendCustomerMsg_Core(reqMsg.ToString());
}

/**
 * @brief 发送客服图片消息
 * 
 * @param reqMsg 待发送的客服图片消息
 * @return true 
 * @return false 
 */
bool CWXManager::SendCustomerImageMsg(const SendCustomerImageMsgReq& reqMsg)
{
	{
		std::string strRsp = reqMsg.ToString();
		return SendCustomerMsg_Core(reqMsg.ToString());
	}
}

/**
 * @brief 发送客服语音消息
 * 
 * @param reqMsg 待发送的消息
 * @return true 成功
 * @return false 失败
 */
bool CWXManager::SendCustomerVoiceMsg(const SendCustomerVoiceMsgReq& reqMsg)
{
	std::string strRsp = reqMsg.ToString();
	return SendCustomerMsg_Core(reqMsg.ToString());
}

/**
 * @brief 发送客服视频消息
 * 
 * @param reqMsg 待发送的视频消息
 * @return true 成功
 * @return false 失败
 */
bool CWXManager::SendCustomerVideoMsg(const SendCustomerVideoMsgReq& reqMsg)
{
	std::string strRsp = reqMsg.ToString();
	return SendCustomerMsg_Core(reqMsg.ToString());
}

/**
 * @brief 发送客服音乐消息
 * 
 * @param reqMsg 客服音乐消息
 * @return true 成功
 * @return false 失败
 */
bool CWXManager::SendCustomerMusicMsg(const SendCustomerMusicMsgReq& reqMsg)
{
	std::string strRsp = reqMsg.ToString();
	return SendCustomerMsg_Core(reqMsg.ToString());
}

/**
 * @brief 发送客服News消息
 * 
 * @param reqMsg 待发送的News消息
 * @return true 成功
 * @return false 失败
 */
bool CWXManager::SendCustomerNewsMsg(const SendCustomerNewsMsgReq& reqMsg)
{
	std::string strRsp = reqMsg.ToString();
	return SendCustomerMsg_Core(reqMsg.ToString());
}

/**
 * @brief 发送客服菜单消息
 * 
 * @param reqMsg 待发送的菜单消息
 * @return true 
 * @return false 
 */
bool CWXManager::SendCustomerMenuMsg(const SendCustomerMenuMsgReq& reqMsg)
{
	std::string strRsp = reqMsg.ToString();
	return SendCustomerMsg_Core(reqMsg.ToString());
}
//bool CWXManager::SendMenuMsg()
//{
//	SendCustomerMenuMsgReq reqMsg;
//	for (auto item : m_userList)
//	{
//		reqMsg.m_strHeadContent = "Welcome To DennisThink";
//		reqMsg.m_strTailContent = "Thanks For Use DennisThink";
//		{
//			MsgMenuElem elem1;
//			elem1.m_strId = "101";
//			elem1.m_strContent = "Start Chat";
//			reqMsg.m_vecMenus.push_back(elem1);
//		}
//
//		{
//			MsgMenuElem elem1;
//			elem1.m_strId = "102";
//			elem1.m_strContent = "Stop Chat";
//			reqMsg.m_vecMenus.push_back(elem1);
//		}
//
//		reqMsg.m_strToUser = item;
//
//		std::string strUrl = "/cgi-bin/message/custom/send?access_token=" + m_strAccessToken;
//		try
//		{
//			auto rsp = m_httpClient->request("POST", strUrl, reqMsg.ToString());
//			std::string strRsp = rsp->content.string();
//			std::cout << strRsp << std::endl;
//			//m_strAccessToken = ParseAccessToken(strRsp);
//		}
//		catch (const SimpleWeb::system_error& e) {
//			std::cerr << "Client Req Error " << e.what() << std::endl;
//		}
//	}
//	return false;
//}

/**
 * @brief 获取关注者的基本信息
 * 
 * @param strUserId 关注者的openid
 * @return GetUserBaseInfoRsp 用户基本信息的回复
 */
GetUserBaseInfoRsp CWXManager::GetUserBaseInfo(const std::string& strUserId)
{
	GetUserBaseInfoReq reqMsg;
	reqMsg.m_strAccessToken = m_strAccessToken;
	reqMsg.m_strLang = "zh_CN";
	GetUserBaseInfoRsp rspMsg;
	std::string strUrl = "/cgi-bin/user/info?";
	try
	{
		reqMsg.m_strOpenId = strUserId;
		auto rsp = m_httpClient->request("GET", strUrl + reqMsg.ToString(), "");
		std::string strRsp = rsp->content.string();
		LOG_INFO(m_loger, "RSP: {} [{} {}]", strRsp, __FILENAME__, __LINE__);
		if (rspMsg.FromString(strRsp))
		{
			LOG_INFO(m_loger, "Get User Base Info Succeed: {} [{} {}]", rspMsg.m_strNickName, __FILENAME__, __LINE__);
		}
		else
		{
			LOG_ERR(m_loger, "Get User Base Info Failed: {} [{} {}]", strRsp, __FILENAME__, __LINE__);
		}
	}
	catch (const SimpleWeb::system_error& e) {
		LOG_ERR(m_loger, "Get User Base Info Succeed: {} [{} {}]", e.what(), __FILENAME__, __LINE__);
	}

	return rspMsg;
}

/**
 * @brief 获取关注者的基本信息的示例
 * 
 * @return true 成功
 * @return false 失败
 */
bool CWXManager::GetUserBaseInfo()
{
	GetUserBaseInfoReq reqMsg;
	reqMsg.m_strAccessToken = m_strAccessToken;
	reqMsg.m_strLang = "zh_CN";
	GetUserBaseInfoRsp rspMsg;
	for (auto item : m_userList)
	{
		std::string strUrl = "/cgi-bin/user/info?" ;
		try
		{
			reqMsg.m_strOpenId = item;
			auto rsp = m_httpClient->request("GET", strUrl+reqMsg.ToString(), "");
			std::string strRsp = rsp->content.string();
			LOG_INFO(m_loger, "RSP: {} [{} {}]", strRsp, __FILENAME__, __LINE__);
			if (rspMsg.FromString(strRsp))
			{
				LOG_INFO(m_loger, "UserNickName: {} [{} {}]",rspMsg.m_strNickName, __FILENAME__, __LINE__);
			}
			else
			{
				LOG_ERR(m_loger, "Get NickName Failed: {} [{} {}]",strRsp, __FILENAME__, __LINE__);
			}
			//m_strAccessToken = ParseAccessToken(strRsp);
		}
		catch (const SimpleWeb::system_error& e) {
			LOG_ERR(m_loger, "Client Req Error: {} [{} {}]", e.what(), __FILENAME__, __LINE__);
		}
	}
	return false;
}