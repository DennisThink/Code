/**
 * @file WXManagerMsg.h
 * @author DennisMi (https://www.dennisthink.com/)
 * @brief 公众号管理的相关消息的头文件
 * @version 0.1
 * @date 2020-03-22
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#ifndef _DENNIS_THINK_WX_MANAGER_MSG_H_
#define _DENNIS_THINK_WX_MANAGER_MSG_H_
#include <string>
#include <vector>


/**
 * @brief 获取AccessToken的请求消息
 * 
 */
class GetAccessTokenReq
{
public:
	std::string m_strGrantType;//获取access_token填写client_credential
	std::string m_strAppId;//AppId 由公众号平台设置
	std::string m_strSecrect;//AppSecrect 从公众号平台获取
public:
	std::string ToString();
};

/**
 * @brief 获取AccessToken的回复消息
 * 
 */
class GetAccessTokenRsp
{
public:
	std::string m_strAccessToken;//获取的AccessToken
	int m_nExpiresIn;//失效时间,单位秒
public:
	bool FromString(const std::string strRsp);
};

/**
 * @brief 获取用户列表的请求
 * 
 */
class GetUserListReq
{
public:
	std::string m_strAccessToken;//AcceccToken 从Token获取接口得到
	std::string m_strNextOpenId;//关注者太多的时候,分页开始的openid,第一次获取的时候,为空
public:
	std::string ToString();
};

/**
 * @brief 获取关注者列表的回复
 * 
 */
class GetUserListRsp
{
public:
	int m_nTotal;//总的关注者的数量
	int m_nCount;//本次获取的数量
	std::vector<std::string> m_vecUserOpenId;//本次获取的关注者ID
	std::string m_strLastOpenId;//本次获取的最后一个关注者的ID
public:
	bool FromString(const std::string& strRsp);
};

/**
 * @brief 获取用户基本信息的请求
 * 
 */
class GetUserBaseInfoReq
{
public:
	std::string m_strAccessToken;//AccessToken,需要定时获取
	std::string m_strOpenId;//关注者的openid
	std::string m_strLang;//语言选择,例如zh-CN
public:
	std::string ToString();
};

/**
 * @brief 获取用户信息的回复
 * 
 */
class GetUserBaseInfoRsp
{
public:
	int m_nSubscribe;//用户是否关注了公众号 1为关注了
	std::string m_strOpenId;//用户的openid
	std::string m_strNickName;//用户昵称
	int m_nSex;//用户性别
	std::string m_strLanguage;//信息的语言(中文、英文等)
	std::string m_strCity;//所在城市
	std::string m_strProvince;//所在省份
	std::string m_strCountry;//所在国家
	std::string m_strHeadImgUrl;//头像超链接
	std::string m_strSubscribeTime;//用户订阅公众号的时间
	std::string m_strUnionId;//TODO: 
	std::string m_strRemark;//用户备注
	std::string m_nGroupId;//分组ID
	std::vector<int> m_TagIdList;//标签ID列表
	std::string m_strSubScribeScene;//订阅场景
	int m_nQrScene;
	std::string m_strQrSceneStr;//订阅场景描述
public:
	bool FromString(const std::string strRsp);
};

/**
 * @brief 发送客服文本消息
 * 
 */
class SendCustomerTextMsgReq
{
public:
	std::string m_strToUser;//关注者的openid
	std::string m_strContext;//消息文本UTF8编码
public:
	std::string ToString() const;
};


/**
 * @brief 发送客服图片消息
 * 
 */
class SendCustomerImageMsgReq
{
public:
	std::string m_strToUser;//关注者的openid
	std::string m_strMediaId;//图片媒体ID
public:
	std::string ToString() const;
};


/**
 * @brief 发送客服语音消息
 * 
 */
class SendCustomerVoiceMsgReq
{
public:
	std::string m_strToUser;//关注者的openid
	std::string m_strMediaId;//图片媒体ID
public:
	std::string ToString() const;
};

/**
 * @brief 发送客服视频消息
 * 
 */
class SendCustomerVideoMsgReq
{
public:
	std::string m_strToUser;//关注者的openid
	std::string m_strMediaId;//视频媒体ID
public:
	std::string ToString() const ;
};

/**
 * @brief 发送客服音乐消息
 * 
 */
class SendCustomerMusicMsgReq
{
public:
	std::string m_strToUser;//关注者的openid
	std::string m_strTitle;//音乐标题
	std::string m_strDescription;//音乐描述
	std::string m_strMusicUrl;//音乐的URL
	std::string m_strHQMusicUrl;//高清音乐的URL
	std::string m_strThumb_Media_Id;//缩略图的媒体ID
public:
	std::string ToString() const;
};

/**
 * @brief 发送客服MP模式的News消息
 * 
 */
class SendCustomerMPNewsMsgReq
{
public:
	std::string m_strToUser;//关注者的openid
	std::string m_strMediaId;//资源媒体的ID
public:
	std::string ToString() const;
};

/**
 * @brief 文章元素定义
 * 
 */
struct MsgArticleElem
{
	std::string m_strTitle;//文章标题
	std::string m_strDescription;//文章描述
	std::string m_strUrl;//文章URL
	std::string m_strPicUrl;//文章图片的URL
};

/**
 * @brief 
 * TODO: 此处需要完善
 */
class SendCustomerNewsMsgReq
{
public:
	std::string m_strToUser;
	MsgArticleElem m_article;
public:
	std::string ToString() const;
};

/**
 * @brief 
 * 
 */
struct MsgMenuElem
{
	std::string m_strId;//菜单ID,字符串
	std::string m_strContent;//菜单的显示内容
};

/**
 * @brief 
 * 
 */
class SendCustomerMenuMsgReq
{
public:
	std::string m_strToUser;//关注者的openid
	std::string m_strHeadContent;//菜单消息的开始内容
	std::vector<MsgMenuElem> m_vecMenus;//
	std::string m_strTailContent;//菜单消息的结束内容
public:
	std::string ToString() const; 
};

/**
 * @brief 发送客服消息的回复
 * 
 */
class SendCustomerMsgRsp
{
public:
	int m_nErrCode;//错误码
	std::string m_strErrMsg;//错误消息
public:
	bool FromString(const std::string& strRsp);
};

//
#endif