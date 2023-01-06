#include "WXManagerMsg.h"
#include "json11.hpp"
std::string GetUserBaseInfoReq::ToString()
{
	return "access_token=" + m_strAccessToken + "&openid=" + m_strOpenId+"&lang="+m_strLang;
}

bool GetUserBaseInfoRsp::FromString(const std::string strRsp)
{
	std::string strErr;
	auto userJson = json11::Json::parse(strRsp, strErr);
	if (!strErr.empty())
	{
		return false;
	}
	
	if (userJson["subscribe"].is_number())
	{
		m_nSubscribe = userJson["subscribe"].int_value();
	}

	if (userJson["openid"].is_string())
	{
		m_strOpenId = userJson["openid"].string_value();
	}

	if (userJson["nickname"].is_string())
	{
		m_strNickName = userJson["nickname"].string_value();
	}

	if (userJson["sex"].is_number())
	{
		m_nSex = userJson["sex"].int_value();
	}

	if (userJson["language"].is_string())
	{
		m_strLanguage = userJson["language"].string_value();
	}


	if (userJson["city"].is_string())
	{
		m_strCity = userJson["city"].string_value();
	}

	if (userJson["province"].is_string())
	{
		m_strProvince = userJson["province"].string_value();
	}

	if (userJson["country"].is_string())
	{
		m_strCountry = userJson["country"].string_value();
	}

	if (userJson["headimgurl"].is_string())
	{
		m_strHeadImgUrl = userJson["headimgurl"].string_value();
	}

	if (userJson["unionid"].is_string())
	{
		m_strUnionId = userJson["unionid"].string_value();
	}


	if (userJson["remark"].is_string())
	{
		m_strRemark = userJson["remark"].string_value();
	}
	if (userJson["groupid"].is_number())
	{
		m_nGroupId = userJson["groupid"].int_value();
	}
	//Tag List
	{

	}
	if (userJson["subscribe_scene"].is_string())
	{
		m_strSubScribeScene = userJson["subscribe_scene"].string_value();
	}

	if (userJson["qr_scene"].is_number())
	{
		m_nQrScene = userJson["qr_scene"].int_value();
	}

	if (userJson["qr_scene_str"].is_string())
	{
		m_strQrSceneStr = userJson["qr_scene_str"].string_value();
	}
	return true;
}