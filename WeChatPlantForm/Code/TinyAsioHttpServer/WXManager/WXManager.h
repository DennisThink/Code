#ifndef _DENNIS_THINK_WX_MANAGER_H_
#define _DENNIS_THINK_WX_MANAGER_H_
#include "../include/thirdparty/httpServer/client_https.hpp"
using HttpClient = SimpleWeb::Client<SimpleWeb::HTTPS>;
class CWXManager
{
public:
    CWXManager(const std::string strAppId,const std::string strAppSecrect);
    bool GetAccessToken();
	bool GetUserList();
	bool SendCustomerMsg();
	bool GetUserBaseInfo();
private:
	bool SendCustomerMsg(const std::string targetId, const std::string strMsg);
	std::string ParseAccessToken(const std::string& strRsp);
	std::vector<std::string> ParseUserList(const std::string& strRsp);
    std::string m_strAccessToken;
    std::string m_strAppId;
    std::string m_strAppSecrect;
    std::shared_ptr<HttpClient> m_httpClient;
	std::vector<std::string> m_userList;
};
#endif