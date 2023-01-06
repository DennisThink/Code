/**
 * @file WXCommonMsg.h
 * @author DennisMi (https://www.dennisthink.com/)
 * @brief 微信公众号接收用户消息以及被动回复消息的定义
 * @version 0.1
 * @date 2020-03-22
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef _DENNIS_THINK_WX_COMMON_MSG_H_
#define _DENNIS_THINK_WX_COMMON_MSG_H_

#include <string>

/**
 * @brief 微信消息类型
 * 
 */
enum class WXMsgType
{
	UnKnownType = -1,
	BaseType,//基础类型
	UserSendTxt,//用户发送的普通消息
	UserRecvTxt,//回复用户发送的普通消息
	UserSendImage,//用户发送图片消息
	UserRecvImage,//回复用户图片消息
	UserSendVoice,//用户发送语音消息
	UserRecvVoice,//回复用户语音消息
	UserSendVideo,//用户发送视频消息
	UserRecvVideo,//回复用户视频消息
	UserSendShortVideo,//用户发送小视频消息
	UserRecvShortVideo,//回复用户小视频消息
	UserSendLocation,//用户发送地理位置消息
	UserRecvLocation,//用户接收地理位置消息
	UserSendLink,//用户发送链接消息
	UserRecvLink,//用户接收链接消息
	UserRecvMusic,//用户接收音乐消息
	UserRecvNews,//用户接收图文消息
};

/**
 * @brief 从消息内容解析出消息类型
 * 
 * @param strXml 消息的XML数据
 * @return WXMsgType 消息类型
 */
WXMsgType ParseMsgType(const std::string& strXml);

/**
 * @brief 基础消息类型
 * 
 */
class WXMsgBase
{
public:
	virtual WXMsgType getMsgType();
	virtual std::string ToString();
	virtual bool FromString(const std::string strMsg);
};


/**
 * @brief 用户发送文本消息
 * 
 */
class UserSendTxtMsg :public WXMsgBase
{
public:
	std::string m_strToUserName;//公众号ID
	std::string m_strFromUserName;//关注者的ID号
	std::string m_strCreateTime;//消息创建时间
	std::string m_strContent;//消息内容
	std::string m_strMsgId;//消息ID
public:
	virtual WXMsgType getMsgType() override final;
	virtual std::string ToString() override final;
	virtual bool FromString(const std::string strMsg) override final;
};


/**
 * @brief 回复用户文本消息
 * 
 */
class UserRecvTxtMsg :public WXMsgBase
{
public:
	std::string m_strToUserName;//公众号ID TODO:
	std::string m_strFromUserName;//关注者的ID号 TODO:
	std::string m_strCreateTime;//消息创建时间
	std::string m_strContent;//消息内容
public:
	virtual WXMsgType getMsgType() override final;
	virtual std::string ToString() override final;
	virtual bool FromString(const std::string strMsg) override final;
};


/**
 * @brief 用户发送图片消息
 * 
 */
class UserSendImageMsg :public WXMsgBase
{
public:
	std::string m_strToUserName;//公众号ID
	std::string m_strFromUserName;//关注者的ID号
	std::string m_strCreateTime;//消息创建时间
	std::string m_strPicUrl;//图像URL
	std::string m_strMediaId;//媒体ID
	std::string m_strMsgId;//消息ID
public:
	virtual WXMsgType getMsgType() override final;
	virtual std::string ToString() override final;
	virtual bool FromString(const std::string strMsg) override final;
};

/**
 * @brief 用户被动接收图片消息
 * 
 */
class UserRecvImageMsg :public WXMsgBase
{
public:
	std::string m_strToUserName;//关注者的openId
	std::string m_strFromUserName;//公众号openId
	std::string m_strCreateTime;//TODO 需要去掉
	std::string m_strMediaId;//资源ID
	std::string m_strMsgId;//消息ID
public:
	virtual WXMsgType getMsgType() override final;
	virtual std::string ToString() override final;
	virtual bool FromString(const std::string strMsg) override final;
};

/**
 * @brief 用户发送语音消息
 * 
 */
class UserSendVoiceMsg :public WXMsgBase
{
public:
	std::string m_strToUserName;//公众号openid
	std::string m_strFromUserName;//关注者的openId
	std::string m_strCreateTime;//消息创建时间
	std::string m_strMediaId;//语音媒体ID
	std::string m_strFormat;//语音格式
	std::string m_strMsgId;//消息ID
public:
	virtual WXMsgType getMsgType() override final;
	virtual std::string ToString() override final;
	virtual bool FromString(const std::string strMsg) override final;
};


/**
 * @brief 被动回复用户的语音消息
 * 
 */
class UserRecvVoiceMsg :public WXMsgBase
{
public:
	std::string m_strToUserName;//关注者的openid
	std::string m_strFromUserName;//公众号的openid
	std::string m_strCreateTime;//消息创建时间
	std::string m_strMediaId;//资源ID
public:
	virtual WXMsgType getMsgType() override final;
	virtual std::string ToString() override final;
	virtual bool FromString(const std::string strMsg) override final;
};

/**
 * @brief 用户发送视频消息
 * 
 */
class UserSendVideoMsg :public WXMsgBase
{
public:
	std::string m_strToUserName;//公众号的openid
	std::string m_strFromUserName;//关注者的openid
	std::string m_strCreateTime;//消息创建时间
	std::string m_strMediaId;//媒体ID
	std::string m_strThumbMediaId;//缩略图媒体ID
	std::string m_strMsgId;//消息ID
public:
	virtual WXMsgType getMsgType() override final;
	virtual std::string ToString() override final;
	virtual bool FromString(const std::string strMsg) override final;
};

/**
 * @brief 用户被动接收视频消息
 * 
 */
class UserRecvVideoMsg :public WXMsgBase
{
public:
	std::string m_strToUserName;//关注者的openid
	std::string m_strFromUserName;//公众号的openid
	std::string m_strCreateTime;//消息创建时间
	std::string m_strMediaId;//资源ID
	std::string m_strTitle;//资源Title
	std::string m_strDescription;//视频描述
public:
	virtual WXMsgType getMsgType() override final;
	virtual std::string ToString() override final;
	virtual bool FromString(const std::string strMsg) override final;
};

/**
 * @brief 用户发送短视频消息
 * 
 */
class UserSendShortVideoMsg :public WXMsgBase
{
public:
	std::string m_strToUserName;//公众号openid
	std::string m_strFromUserName;//关注者的openid
	std::string m_strCreateTime;//消息创建时间
	std::string m_strMediaId;//短视频媒体id
	std::string m_strThumbMediaId;//视频缩略图的媒体ID
	std::string m_strMsgId;//消息ID
public:
	virtual WXMsgType getMsgType() override final;
	virtual std::string ToString() override final;
	virtual bool FromString(const std::string strMsg) override final;
};

/**
 * @brief 被动回复用户的音乐消息
 * 
 */
class UserRecvMusicMsg :public WXMsgBase
{
public:
	std::string m_strToUserName;//关注者的openid
	std::string m_strFromUserName;//公众号的openid
	std::string m_strCreateTime;//消息创建时间

	std::string m_strTitle;//音乐标题
	std::string m_strDescription;//音乐描述
	std::string m_strMusicUrl;//音乐的URL
	std::string m_strHQMusicUrl;//高清音乐的URL
	std::string m_strThumbMediaId;//缩略图ID
public:
	virtual WXMsgType getMsgType() override final;
	virtual std::string ToString() override final;
	virtual bool FromString(const std::string strMsg) override final;
};

/**
 * @brief 用户发送位置消息
 * 
 */
class UserSendLocationMsg :public WXMsgBase
{
public:
	std::string m_strToUserName;//公众号openid
	std::string m_strFromUserName;//关注者的openid
	std::string m_strCreateTime;//消息创建时间
	std::string m_strLocation_X;//经度坐标
	std::string m_strLocation_Y;//纬度坐标
	std::string m_strScale;//缩放比例尺
	std::string m_strLabel;//位置标识
	std::string m_strMsgId;//消息ID
public:
	virtual WXMsgType getMsgType() override final;
	virtual std::string ToString() override final;
	virtual bool FromString(const std::string strMsg) override final;
};

//class UserRecvNewsMsg :public WXMsgBase
//{
//public:
//	std::string m_strToUserName;
//	std::string m_strFromUserName;
//	std::string m_strCreateTime;
//	std::string m_strArticleCount;
//
//	std::string m_strTitle;
//	std::string m_strDescription;
//	std::string m_strPicUrl;
//	std::string m_strUrl;
//
//public:
//	virtual WXMsgType getMsgType() override final;
//	virtual std::string ToString() override final;
//	virtual bool FromString(const std::string strMsg) override final;
//};

/**
 * @brief 用户发送超链接消息
 * 
 */
class UserSendLinkMsg :public WXMsgBase
{
public:
	std::string m_strToUserName;//公众号的OpenId
	std::string m_strFromUserName;//关注者的openid
	std::string m_strCreateTime;//消息创建时间
	std::string m_strTitle;//超链接的标题
	std::string m_strDescription;//超链接的描述
	std::string m_strUrl;//超链接的链接地址
	std::string m_strMsgId;//消息ID
public:
	virtual WXMsgType getMsgType() override final;
	virtual std::string ToString() override final;
	virtual bool FromString(const std::string strMsg) override final;
};
#endif