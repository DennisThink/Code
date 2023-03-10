#ifndef _CPP_EMAIL_PROTO_UTIL_H_
#define _CPP_EMAIL_PROTO_UTIL_H_
#include <string>
#include <vector>
namespace cpp_email
{
    class CProtoUtil final
    {
    public:
        static std::vector<std::string> SplitStringByLine(const std::string& strValue);
        static bool SplitLine(const std::string& strInput,int& code,std::string& value,bool& bFinish);
        static std::string Base64Encode(const std::string strInput);
        static std::string Base64Decode(const std::string strInput);
        static bool ParseFromToString(const std::string strInput,std::string& name,std::string& emailAddr);
        static std::string& Trim(std::string &s); 
    };
}
#endif