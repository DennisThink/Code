/**
 * @file WXManagerMsg.cpp
 * @author DennisMi (https://www.dennisthink.com/)
 * @brief 公众号管理的相关消息的实现类
 * @version 0.1
 * @date 2020-03-22
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include "WXManagerMsg.h"
#include "json11.hpp"

std::string GetAccessTokenReq::ToString()
{
	return "grant_type=client_credential&appid="+m_strAppId+"&secret="+ m_strSecrect;
}

bool GetAccessTokenRsp::FromString(const std::string strRsp)
{
	std::string strErrMsg;
	auto orgJson = json11::Json::parse(strRsp, strErrMsg);
	if (strErrMsg.empty())
	{
		if (orgJson["expires_in"].is_number())
		{
			m_nExpiresIn = orgJson["expires_in"].int_value();
		}
		if (orgJson["access_token"].is_string())
		{
			m_strAccessToken = orgJson["access_token"].string_value();
			return true;
		}
	}
	return false;
}


std::string GetUserListReq::ToString()
{
	return "access_token=" + m_strAccessToken + "&openid=" + m_strNextOpenId;
}

bool GetUserListRsp::FromString(const std::string& strRsp)
{
	m_vecUserOpenId.clear();
	std::string strErrMsg;
	auto orgJson = json11::Json::parse(strRsp, strErrMsg);
	if (strErrMsg.empty())
	{
		if (orgJson["total"].is_number())
		{
			m_nTotal = orgJson["total"].int_value();
		}

		if (orgJson["count"].is_number())
		{
			m_nCount = orgJson["count"].int_value();
		}

		if (orgJson["next_openid"].is_string())
		{
			m_strLastOpenId = orgJson["next_openid"].string_value();
		}
		if (orgJson["data"].is_object())
		{
			auto dataJson = orgJson["data"];
			if (dataJson["openid"].is_array())
			{
				for (auto item : dataJson["openid"].array_items())
				{
					m_vecUserOpenId.push_back(item.string_value());
				}
			}
		}
		return true;
	}
	return false;
}

std::string SendCustomerTextMsgReq::ToString() const
{
	json11::Json contentJson = json11::Json::object({ {"content",m_strContext }, });
	json11::Json resultJson = json11::Json({
		{"touser",m_strToUser},
		{"msgtype","text"},
		{"text",contentJson},
		});

	return resultJson.dump();
}

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

std::string SendCustomerImageMsgReq::ToString() const
{
	json11::Json mediaJson = json11::Json({ "media_id",m_strMediaId });
	json11::Json resultJson = json11::Json({
		{"touser",m_strToUser},
		{"msgtype","image"},
		{"image",mediaJson},
		});

	return resultJson.dump();
}

std::string SendCustomerVoiceMsgReq::ToString() const
{
	json11::Json mediaJson = json11::Json({ "media_id",m_strMediaId });
	json11::Json resultJson = json11::Json({
		{"touser",m_strToUser},
		{"msgtype","voice"},
		{"voice",mediaJson},
		});

	return resultJson.dump();
}

std::string SendCustomerVideoMsgReq::ToString() const
{
	json11::Json mediaJson = json11::Json({ "media_id",m_strMediaId });
	json11::Json resultJson = json11::Json({
		{"touser",m_strToUser},
		{"msgtype","video"},
		{"video",mediaJson},
		});

	return resultJson.dump();
}

std::string SendCustomerMusicMsgReq::ToString() const
{
	json11::Json mediaJson = json11::Json({
		{"title",m_strTitle },
		{"description",m_strDescription},
		{"musicurl",m_strMusicUrl},
		{"hqmusicurl",m_strHQMusicUrl},
		{"thumb_media_id",m_strThumb_Media_Id}
		});
	json11::Json resultJson = json11::Json({
		{"touser",m_strToUser},
		{"msgtype","music"},
		{"music",mediaJson},
		});

	return resultJson.dump();
}

std::string SendCustomerMenuMsgReq::ToString() const
{

	json11::Json::array listArray;
	for (auto item : m_vecMenus)
	{
		listArray.push_back(
			json11::Json({
			{"id",item.m_strId},
			{"content",item.m_strContent},
		})
		);
	}

	json11::Json menuJson = json11::Json({
		{"head_content",m_strHeadContent },
		{"list",listArray},
		{"tail_content",m_strTailContent},
	});

	json11::Json resultJson = json11::Json({
		{"touser",m_strToUser},
		{"msgtype","msgmenu"},
		{"msgmenu",menuJson},
	});

	return resultJson.dump();
}

std::string SendCustomerNewsMsgReq::ToString() const
{
	json11::Json::array articles;
	//for(auto item:)
	{
		json11::Json article = json11::Json::object({
			{"title",m_article.m_strTitle},
			{"description",m_article.m_strDescription},
			{"url",m_article.m_strUrl},
			{"picurl",m_article.m_strPicUrl},
		});
		articles.push_back(article);
	}
	json11::Json newsJson = json11::Json::object({
			{"articles",articles},
	});
	
	json11::Json resultJson = json11::Json::object({
		{"touser",m_strToUser},
		{"msgtype","news"},
		{"news",newsJson},
		});

	return resultJson.dump();
}

bool SendCustomerMsgRsp::FromString(const std::string& strRsp)
{
	std::string strErr;
	auto userJson = json11::Json::parse(strRsp, strErr);
	if (!strErr.empty())
	{
		return false;
	}

	if (userJson["errcode"].is_number())
	{
		m_nErrCode = userJson["errcode"].int_value();
	}

	if (userJson["errmsg"].is_string())
	{
		m_strErrMsg = userJson["errmsg"].string_value();
	}
	return true;
}