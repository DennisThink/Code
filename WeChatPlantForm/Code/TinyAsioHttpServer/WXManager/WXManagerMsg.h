/*
用来保存
*/
#ifndef _DENNIS_THINK_WX_MANAGER_MSG_H_
#define _DENNIS_THINK_WX_MANAGER_MSG_H_
#include <string>
#include <vector>
//获取用户基本信息的请求
class GetUserBaseInfoReq
{
public:
	std::string m_strAccessToken;
	std::string m_strOpenId;
	std::string m_strLang;
public:
	std::string ToString();
};

class GetUserBaseInfoRsp
{
public:
	int m_nSubscribe;
	std::string m_strOpenId;
	std::string m_strNickName;
	int m_nSex;
	std::string m_strLanguage;
	std::string m_strCity;
	std::string m_strProvince;
	std::string m_strCountry;
	std::string m_strHeadImgUrl;
	std::string m_strSubscribeTime;
	std::string m_strUnionId;
	std::string m_strRemark;
	std::string m_nGroupId;
	std::vector<int> m_TagIdList;
	std::string m_strSubScribeScene;
	int m_nQrScene;
	std::string m_strQrSceneStr;
public:
	bool FromString(const std::string strRsp);
};
#endif