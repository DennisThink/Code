/**
 * @file WXCommonMsg.cpp
 * @author DennisMi (https://www.dennisthink.com/)
 * @brief 微信公众号接收用户消息以及被动回复消息的实现
 * @version 0.1
 * @date 2020-03-22
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include "WXCommonMsg.h"
#include "tinyxml2/tinyxml2.h"





std::string CreateCDATA(const std::string strSrc)
{
	return "![CDATA[" + strSrc + "]]";
}

using namespace tinyxml2;
/**
 * @brief 从XML数据中,获取指定Tag的值
 * 
 * @param doc XML的doc
 * @param strTag XML的tag
 * @return std::string tag的值
 */
std::string GetXMLElemOrgValue(XMLDocument& doc, const std::string strTag)
{
	XMLElement* titleElement = doc.FirstChildElement("xml")->FirstChildElement(strTag.c_str());
	const char* title = titleElement->GetText();
	return std::string(title);
}

/**
 * @brief 从XML数据中,获取指定TAG的CDATA的值
 * TODO: 没有什么用,只是用来和获取普通的值进行区分
 * @param doc 消息的xml结构
 * @param strTag xml结构的tag
 * @return std::string tag的值
 */
std::string GetXMLElem_CDATA_Value(XMLDocument& doc, const std::string strTag)
{
	XMLElement* titleElement = doc.FirstChildElement("xml")->FirstChildElement(strTag.c_str());
	const char* title = titleElement->GetText();
	return title;
}

/**
 * @brief 解析消息数据,获得消息类型
 * 
 * @param strXml 消息的XML数据
 * @return WXMsgType 消息类型
 */
WXMsgType ParseMsgType(const std::string& strXml)
{
	XMLDocument doc;
	if (XMLError::XML_SUCCESS == doc.Parse(strXml.c_str()))
	{
		std::string strType = GetXMLElem_CDATA_Value(doc, "MsgType");
		if ("text" == strType)
		{
			return WXMsgType::UserSendTxt;
		}
		else if ("image" == strType)
		{
			return WXMsgType::UserSendImage;
		}
		else if ("voice" == strType)
		{
			return WXMsgType::UserSendVoice;
		}
		else if ("video" == strType)
		{
			return WXMsgType::UserSendVideo;
		}
		else if ("shortvideo" == strType)
		{
			return WXMsgType::UserSendShortVideo;
		}
		else if ("location" == strType)
		{
			return WXMsgType::UserSendLocation;
		}
		else if ("link" == strType)
		{
			return WXMsgType::UserSendLink;
		}
		else 
		{
			return WXMsgType::BaseType;
		}
	}
	else
	{
		return WXMsgType::UnKnownType;
	}
}

/**
 * @brief Set the Xml Elem Org Value object
 * 
 * @param doc XML的doc
 * @param strTag XML的tag标签
 * @param strValue XML的tag数据
 * @return true 设置成功
 * @return false 设置失败
 */
bool SetXmlElemOrgValue(XMLDocument& doc, const std::string strTag, const std::string strValue)
{
	XMLElement* pElement = doc.FirstChildElement();
	{
		XMLElement * pInsert = doc.NewElement(strTag.c_str());
		pInsert->SetText(strValue.c_str());
		pElement->InsertEndChild(pInsert);
	}
	return true;
}

/**
 * @brief 设置XML数据中的CDATA数据
 * 
 * @param doc XML结构Doc
 * @param strTag XML的标签
 * @param strValue 标签的数据
 * @return true 设置成功
 * @return false 设置失败
 */
bool SetXmlElem_CDATA_Value(XMLDocument& doc, const std::string strTag, const std::string strValue)
{
	XMLElement* pElement = doc.FirstChildElement();
	{
		XMLElement * pInsert = doc.NewElement(strTag.c_str());
		{
			XMLText * pText = doc.NewText(strValue.c_str());
			pText->SetCData(true);
			pInsert->InsertEndChild(pText);
		}
		pElement->InsertEndChild(pInsert);
	}
	return true;
}

/**
 * @brief 设置XML的CDATA的二级数据
 * 
 * @param doc XML的doc
 * @param strTag XML的标签
 * @param strSonTag XML的子标签
 * @param strSonValue 子标签的值
 * @return true 设置成功
 * @return false 设置失败
 */
bool SetXmlElem_CDATA_Value(XMLDocument& doc, const std::string strTag,const std::string strSonTag, const std::string strSonValue)
{
	XMLElement* pElement = doc.FirstChildElement();
	{
		XMLElement * pTag = nullptr;
		pTag = pElement->FirstChildElement(strTag.c_str());
		if (!pTag)
		{
			pTag = doc.NewElement(strTag.c_str());
		}
		{
			XMLElement * pSonTag = doc.NewElement(strSonTag.c_str());
			{
				XMLText * pText = doc.NewText(strSonValue.c_str());
				pText->SetCData(true);
				pSonTag->InsertEndChild(pText);
			}
			pTag->InsertFirstChild(pSonTag);
		}
		pElement->InsertEndChild(pTag);
	}
	return true;
}

bool WXMsgBase::FromString(const std::string strMsg)
{
	return false;
}

std::string WXMsgBase::ToString()
{
	return "";
}

WXMsgType WXMsgBase::getMsgType()
{
	return WXMsgType::BaseType;
}

/**
 * @brief 用户发送文本消息的反序列化
 * 
 * @param strMsg 公众号服务器发送过来的文本消息数据
 * @return true 成功
 * @return false 失败
 */
bool UserSendTxtMsg::FromString(const std::string strMsg)
{

	XMLDocument doc;
	if (XMLError::XML_SUCCESS == doc.Parse(strMsg.c_str()))
	{
		m_strToUserName = GetXMLElem_CDATA_Value(doc, "ToUserName");
		m_strFromUserName = GetXMLElem_CDATA_Value(doc, "FromUserName");
		m_strCreateTime = GetXMLElemOrgValue(doc, "CreateTime");
		m_strContent = GetXMLElem_CDATA_Value(doc, "Content");
		m_strMsgId = GetXMLElemOrgValue(doc, "MsgId");
		return true;
	}
	else
	{
		return false;
	}
}

/**
 * @brief 
 * TODO: 后期去掉
 * @return std::string 
 */
std::string UserSendTxtMsg::ToString()
{
	return "";
}

WXMsgType UserSendTxtMsg::getMsgType()
{
	return WXMsgType::UserSendTxt;
}


bool UserRecvTxtMsg::FromString(const std::string strMsg)
{
	return false;
}

/**
 * @brief 被动回复用户文本消息的序列化
 * 
 * @return std::string 序列化以后的文本
 */
std::string UserRecvTxtMsg::ToString()
{
	XMLDocument doc;
	doc.InsertFirstChild(doc.NewElement("xml"));
	{
		SetXmlElem_CDATA_Value(doc, "ToUserName", m_strToUserName);
		SetXmlElem_CDATA_Value(doc, "FromUserName",m_strFromUserName);
		SetXmlElemOrgValue(doc, "CreateTime",m_strCreateTime);
		SetXmlElem_CDATA_Value(doc, "MsgType", "text");
		SetXmlElem_CDATA_Value(doc, "Content", m_strContent);
	}
	XMLPrinter streamer;
	doc.Print(&streamer);
	std::string strResult = streamer.CStr();
	return strResult;
}

WXMsgType UserRecvTxtMsg::getMsgType()
{
	return WXMsgType::UserRecvTxt;
}


/**
 * @brief 用户发送图片消息的反序列化
 * 
 * @param strMsg 公众号服务器发来的图片消息数据
 * @return true 成功
 * @return false 失败
 */
bool UserSendImageMsg::FromString(const std::string strMsg)
{
	XMLDocument doc;
	if (XMLError::XML_SUCCESS == doc.Parse(strMsg.c_str()))
	{
		m_strToUserName = GetXMLElem_CDATA_Value(doc, "ToUserName");
		m_strFromUserName = GetXMLElem_CDATA_Value(doc, "FromUserName");
		m_strCreateTime = GetXMLElemOrgValue(doc, "CreateTime");
		m_strPicUrl = GetXMLElem_CDATA_Value(doc, "PicUrl");
		m_strMediaId = GetXMLElem_CDATA_Value(doc, "MediaId");
		m_strMsgId = GetXMLElemOrgValue(doc, "MsgId");

		return true;
	}
	else
	{
		return false;
	}
}

std::string UserSendImageMsg::ToString()
{
	return "";
}

WXMsgType UserSendImageMsg::getMsgType()
{
	return WXMsgType::UserSendImage;
}


bool UserRecvImageMsg::FromString(const std::string strMsg)
{
	return false;
}


/**
 * @brief 被动回复用户图片消息的序列化
 * 
 * @return std::string 序列化以后的XML字符串
 */
std::string UserRecvImageMsg::ToString()
{
	XMLDocument doc;
	doc.InsertFirstChild(doc.NewElement("xml"));
	{
		SetXmlElem_CDATA_Value(doc, "ToUserName", m_strToUserName);
		SetXmlElem_CDATA_Value(doc, "FromUserName", m_strFromUserName);
		SetXmlElemOrgValue(doc, "CreateTime", m_strCreateTime);
		SetXmlElem_CDATA_Value(doc, "MsgType", "image");
		{
			SetXmlElem_CDATA_Value(doc, "Image", "MediaId", m_strMediaId);
		}
	}
	XMLPrinter streamer;
	doc.Print(&streamer);
	std::string strResult = streamer.CStr();
	return strResult;
}

WXMsgType UserRecvImageMsg::getMsgType()
{
	return WXMsgType::UserRecvImage;
}



/**
 * @brief 用户发送的语音消息的反序列化
 * 
 * @param strMsg 公众号服务器发送的语音消息
 * @return true 成功
 * @return false 失败
 */
bool UserSendVoiceMsg::FromString(const std::string strMsg)
{
	XMLDocument doc;
	if (XMLError::XML_SUCCESS == doc.Parse(strMsg.c_str()))
	{
		m_strToUserName = GetXMLElem_CDATA_Value(doc, "ToUserName");
		m_strFromUserName = GetXMLElem_CDATA_Value(doc, "FromUserName");
		m_strCreateTime = GetXMLElemOrgValue(doc, "CreateTime");
		m_strFormat = GetXMLElem_CDATA_Value(doc, "Format");
		m_strMediaId = GetXMLElem_CDATA_Value(doc, "MediaId");
		m_strMsgId = GetXMLElemOrgValue(doc, "MsgId");

		return true;
	}
	else
	{
		return false;
	}
}

std::string UserSendVoiceMsg::ToString()
{
	return "";
}

WXMsgType UserSendVoiceMsg::getMsgType()
{
	return WXMsgType::UserSendVoice;
}



/**
 * @brief 反序列用户发送的视频消息
 * 
 * @param strMsg 公众号服务发送的视频消息XML字符串
 * @return true 成功
 * @return false 失败
 */
bool UserSendVideoMsg::FromString(const std::string strMsg)
{
	XMLDocument doc;
	if (XMLError::XML_SUCCESS == doc.Parse(strMsg.c_str()))
	{
		m_strToUserName = GetXMLElem_CDATA_Value(doc, "ToUserName");
		m_strFromUserName = GetXMLElem_CDATA_Value(doc, "FromUserName");
		m_strCreateTime = GetXMLElemOrgValue(doc, "CreateTime");
		m_strMediaId = GetXMLElem_CDATA_Value(doc, "MediaId");
		m_strThumbMediaId = GetXMLElem_CDATA_Value(doc, "ThumbMediaId");
		m_strMsgId = GetXMLElemOrgValue(doc, "MsgId");

		return true;
	}
	else
	{
		return false;
	}
}

std::string UserSendVideoMsg::ToString()
{
	return "";
}

WXMsgType UserSendVideoMsg::getMsgType()
{
	return WXMsgType::UserSendVideo;
}

/**
 * @brief 反序列化用户发送的短视频信息
 * 
 * @param strMsg 公众号发过来的短视频XML消息
 * @return true 成功
 * @return false 失败
 */
bool UserSendShortVideoMsg::FromString(const std::string strMsg)
{
	XMLDocument doc;
	if (XMLError::XML_SUCCESS == doc.Parse(strMsg.c_str()))
	{
		m_strToUserName = GetXMLElem_CDATA_Value(doc, "ToUserName");
		m_strFromUserName = GetXMLElem_CDATA_Value(doc, "FromUserName");
		m_strCreateTime = GetXMLElemOrgValue(doc, "CreateTime");
		m_strMediaId = GetXMLElem_CDATA_Value(doc, "MediaId");
		m_strThumbMediaId = GetXMLElem_CDATA_Value(doc, "ThumbMediaId");
		m_strMsgId = GetXMLElemOrgValue(doc, "MsgId");

		return true;
	}
	else
	{
		return false;
	}
}

std::string UserSendShortVideoMsg::ToString()
{
	return "";
}

WXMsgType UserSendShortVideoMsg::getMsgType()
{
	return WXMsgType::UserSendShortVideo;
}


/**
 * @brief 用户发送的位置信息的反序列化
 * 
 * @param strMsg 公众号发送的位置信息XML字符串
 * @return true 成功
 * @return false 失败
 */
bool UserSendLocationMsg::FromString(const std::string strMsg)
{
	XMLDocument doc;
	if (XMLError::XML_SUCCESS == doc.Parse(strMsg.c_str()))
	{
		m_strToUserName = GetXMLElem_CDATA_Value(doc, "ToUserName");
		m_strFromUserName = GetXMLElem_CDATA_Value(doc, "FromUserName");
		m_strCreateTime = GetXMLElemOrgValue(doc, "CreateTime");
		m_strLocation_X = GetXMLElemOrgValue(doc, "Location_X");
		m_strLocation_Y = GetXMLElemOrgValue(doc, "Location_Y");
		m_strScale = GetXMLElemOrgValue(doc, "Scale");
		m_strLabel = GetXMLElem_CDATA_Value(doc, "Label");
		m_strMsgId = GetXMLElemOrgValue(doc, "MsgId");

		return true;
	}
	else
	{
		return false;
	}
}

std::string UserSendLocationMsg::ToString()
{
	return "";
}

WXMsgType UserSendLocationMsg::getMsgType()
{
	return WXMsgType::UserSendLocation;
}

/**
 * @brief 反序列化用户发送的超链接信息
 * 
 * @param strMsg 公众号发送的超链接XML信息
 * @return true 成功
 * @return false 失败
 */
bool UserSendLinkMsg::FromString(const std::string strMsg)
{
	XMLDocument doc;
	if (XMLError::XML_SUCCESS == doc.Parse(strMsg.c_str()))
	{
		m_strToUserName = GetXMLElem_CDATA_Value(doc, "ToUserName");
		m_strFromUserName = GetXMLElem_CDATA_Value(doc, "FromUserName");
		m_strCreateTime = GetXMLElemOrgValue(doc, "CreateTime");
		m_strTitle = GetXMLElem_CDATA_Value(doc, "Title");
		m_strDescription = GetXMLElem_CDATA_Value(doc, "Description");
		m_strUrl = GetXMLElem_CDATA_Value(doc, "Url");
		m_strMsgId = GetXMLElemOrgValue(doc, "MsgId");

		return true;
	}
	else
	{
		return false;
	}
}

std::string UserSendLinkMsg::ToString()
{
	return "";
}

WXMsgType UserSendLinkMsg::getMsgType()
{
	return WXMsgType::UserSendLink;
}

bool UserRecvVoiceMsg::FromString(const std::string strMsg)
{
	return false;
}

/**
 * @brief 序列化被动回复的语音消息
 * 
 * @return std::string 序列化以后的字符串
 */
std::string UserRecvVoiceMsg::ToString()
{
	XMLDocument doc;
	doc.InsertFirstChild(doc.NewElement("xml"));
	{
		SetXmlElem_CDATA_Value(doc, "ToUserName", m_strToUserName);
		SetXmlElem_CDATA_Value(doc, "FromUserName", m_strFromUserName);
		SetXmlElemOrgValue(doc, "CreateTime", m_strCreateTime);
		SetXmlElem_CDATA_Value(doc, "MsgType", "voice");
		SetXmlElem_CDATA_Value(doc, "Voice","MediaId",m_strMediaId);
	}
	XMLPrinter streamer;
	doc.Print(&streamer);
	std::string strResult = streamer.CStr();
	return strResult;
}

WXMsgType UserRecvVoiceMsg::getMsgType()
{
	return WXMsgType::UserRecvVoice;
}

bool UserRecvVideoMsg::FromString(const std::string strMsg)
{
	return false;
}

/**
 * @brief 序列化被动回复的视频消息
 * 
 * @return std::string 序列化以后的字符串
 */
std::string UserRecvVideoMsg::ToString()
{
	XMLDocument doc;
	doc.InsertFirstChild(doc.NewElement("xml"));
	{
		SetXmlElem_CDATA_Value(doc, "ToUserName", m_strToUserName);
		SetXmlElem_CDATA_Value(doc, "FromUserName", m_strFromUserName);
		SetXmlElemOrgValue(doc, "CreateTime", m_strCreateTime);
		SetXmlElem_CDATA_Value(doc, "MsgType", "video");
		SetXmlElem_CDATA_Value(doc, "Video", "MediaId", m_strMediaId);
		SetXmlElem_CDATA_Value(doc, "Video", "Title", m_strTitle);
		SetXmlElem_CDATA_Value(doc, "Video", "Description", m_strDescription);
	}
	XMLPrinter streamer;
	doc.Print(&streamer);
	std::string strResult = streamer.CStr();
	return strResult;
}

WXMsgType UserRecvVideoMsg::getMsgType()
{
	return WXMsgType::UserRecvVideo;
}

bool UserRecvMusicMsg::FromString(const std::string strMsg)
{
	return false;
}


/**
 * @brief 序列化用户被动接收音乐消息
 * 
 * @return std::string 序列化以后的字符串
 */
std::string UserRecvMusicMsg::ToString()
{
	XMLDocument doc;
	doc.InsertFirstChild(doc.NewElement("xml"));
	{
		SetXmlElem_CDATA_Value(doc, "ToUserName", m_strToUserName);
		SetXmlElem_CDATA_Value(doc, "FromUserName", m_strFromUserName);
		SetXmlElemOrgValue(doc, "CreateTime", m_strCreateTime);
		SetXmlElem_CDATA_Value(doc, "MsgType", "music");
		SetXmlElem_CDATA_Value(doc, "Music", "Title", m_strTitle);
		SetXmlElem_CDATA_Value(doc, "Music", "Description", m_strDescription);
		SetXmlElem_CDATA_Value(doc, "Music", "MusicUrl", m_strMusicUrl);
		SetXmlElem_CDATA_Value(doc, "Music", "HQMusicUrl", m_strHQMusicUrl);
		SetXmlElem_CDATA_Value(doc, "Music", "ThumbMediaId", m_strThumbMediaId);
	}
	XMLPrinter streamer;
	doc.Print(&streamer);
	std::string strResult = streamer.CStr();
	return strResult;
}

WXMsgType UserRecvMusicMsg::getMsgType()
{
	return WXMsgType::UserRecvMusic;
}

//bool UserRecvNewsMsg::FromString(const std::string strMsg)
//{
//	return false;
//}
//
////TODO:
//std::string UserRecvNewsMsg::ToString()
//{
//	XMLDocument doc;
//	doc.InsertFirstChild(doc.NewElement("xml"));
//	{
//		SetXmlElem_CDATA_Value(doc, "ToUserName", m_strToUserName);
//		SetXmlElem_CDATA_Value(doc, "FromUserName", m_strFromUserName);
//		SetXmlElemOrgValue(doc, "CreateTime", m_strCreateTime);
//		SetXmlElem_CDATA_Value(doc, "MsgType", "music");
//		SetXmlElem_CDATA_Value(doc, "Music", "Title", m_strTitle);
//		SetXmlElem_CDATA_Value(doc, "Music", "Description", m_strDescription);
//	}
//	XMLPrinter streamer;
//	doc.Print(&streamer);
//	std::string strResult = streamer.CStr();
//	return strResult;
//}
//
//WXMsgType UserRecvNewsMsg::getMsgType()
//{
//	return WXMsgType::UserRecvNews;
//}
/*
bool WXMsgBase::FromString(const std::string strMsg)
{
	return false;
}

std::string WXMsgBase::ToString()
{
	return "";
}

WXMsgType WXMsgBase::getMsgType()
{
	return WXMsgType::BaseType;
}



bool WXMsgBase::FromString(const std::string strMsg)
{
	return false;
}

std::string WXMsgBase::ToString()
{
	return "";
}

WXMsgType WXMsgBase::getMsgType()
{
	return WXMsgType::BaseType;
}



bool WXMsgBase::FromString(const std::string strMsg)
{
	return false;
}

std::string WXMsgBase::ToString()
{
	return "";
}

WXMsgType WXMsgBase::getMsgType()
{
	return WXMsgType::BaseType;
}*/
