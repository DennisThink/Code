#ifndef _C_EMAIL_PARSER_H_
#define _C_EMAIL_PARSER_H_
#include <string>
namespace cpp_email
{
class CEmail
{
public:
    CEmail();
    virtual ~CEmail();
    bool Valid(){
        return true;
    }

    std::string ToString(){
        return "";
    }

    bool FromString(std::string strContext){
        if(!strContext.empty())
        {
            return true;
        }
        else
        {
            return false;
        }
    }
private:
    std::string m_strReceived;
    std::string m_strDate;
    std::string m_strFrom;
    std::string m_strTo;
    std::string m_strMsgId;
    std::string m_strX_CM_SysSentMVD;
    std::string m_strX_Netease_Folder;
    std::string m_strSubject;
    std::string m_strMime_Version;
    std::string m_strContent_Type;
    std::string m_strX_Originating_IP;
    std::string m_strContentType;
    std::string m_strContentTransferEncoding;
    std::string m_strContext;

};
}; // namespace cpp_email
#endif