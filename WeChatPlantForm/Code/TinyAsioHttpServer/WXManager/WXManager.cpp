#include "WXManager.h"
#include "json11.hpp"
#include "WXManagerMsg.h"
CWXManager::CWXManager(const std::string strAppId,const std::string strAppSecrect)
{
    m_strAppId =strAppId;
    m_strAppSecrect = strAppSecrect;
	m_httpClient = std::make_shared<HttpClient>("101.226.212.27",false);
}
bool  CWXManager::GetAccessToken()
{
	std::string strUrl = "/cgi-bin/token?grant_type=client_credential&appid="+m_strAppId+"&secret="+ m_strAppSecrect;
	if (m_httpClient)
	{
		try
		{
			auto rsp = m_httpClient->request("GET",strUrl,"");
			std::string strRsp = rsp->content.string();
			std::cout << strRsp << std::endl;
			m_strAccessToken = ParseAccessToken(strRsp);
		}
		catch (const SimpleWeb::system_error& e) {
			std::cerr << "Client Req Error " << e.what() << std::endl;
		}
	}
    return false;
}

bool CWXManager::GetUserList()
{
	std::string strUrl = "/cgi-bin/user/get?access_token=" + m_strAccessToken + "&next_openid=";
	if (m_httpClient)
	{
		try
		{
			auto rsp = m_httpClient->request("GET", strUrl, "");
			std::string strRsp = rsp->content.string();
			std::cout << strRsp << std::endl;
			m_userList = ParseUserList(strRsp);
			//m_strAccessToken = ParseAccessToken(strRsp);
		}
		catch (const SimpleWeb::system_error& e) {
			std::cerr << "Client Req Error " << e.what() << std::endl;
		}
	}
	return false;
}

bool CWXManager::SendCustomerMsg()
{
	for (auto item : m_userList)
	{
		std::string strMsg = R"({
			"touser":"oTD7svyMMzqVmeNw7dohBMCyRSw8",
			"msgtype" : "text",
			"text" :
		{
			"content":"Design By Dennis Think"
		};
		})";
		std::string strUrl = "/cgi-bin/message/custom/send?access_token=" + m_strAccessToken;
		try
		{
			auto rsp = m_httpClient->request("POST", strUrl,strMsg);
			std::string strRsp = rsp->content.string();
			std::cout << strRsp << std::endl;
			//m_strAccessToken = ParseAccessToken(strRsp);
		}
		catch (const SimpleWeb::system_error& e) {
			std::cerr << "Client Req Error " << e.what() << std::endl;
		}
	}
	return false;
}
std::string CWXManager::ParseAccessToken(const std::string& strRsp)
{
	std::string strErrMsg;
	auto orgJson = json11::Json::parse(strRsp,strErrMsg);
	if (strErrMsg.empty())
	{
		if (orgJson["access_token"].is_string())
		{
			return orgJson["access_token"].string_value();
		}
	}
	return "";
}

std::vector<std::string> CWXManager::ParseUserList(const std::string& strRsp)
{
	std::vector<std::string> result;
	std::string strErrMsg;
	auto orgJson = json11::Json::parse(strRsp, strErrMsg);
	if (strErrMsg.empty())
	{
		if (orgJson["data"].is_object())
		{
			auto dataJson = orgJson["data"];
			if (dataJson["openid"].is_array())
			{
				for (auto item : dataJson["openid"].array_items())
				{
					result.push_back(item.string_value());
				}
			}
		}
	}
	return result;
}

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
			std::cout << strRsp << std::endl;
			if (rspMsg.FromString(strRsp))
			{
				std::cout << "Get User Base Info Succeed " << rspMsg.m_strNickName << std::endl;
			}
			else
			{
				std::cout << "Get User Base Info Failed " << std::endl;
			}
			//m_strAccessToken = ParseAccessToken(strRsp);
		}
		catch (const SimpleWeb::system_error& e) {
			std::cerr << "Client Req Error " << e.what() << std::endl;
		}
	}
	return false;
}