#include "user_info.h"
#include "../util/ProtoUtil.h"
namespace cpp_email 
{
    bool ParseEmailFromRecv(const std::string& strContext,email_info_t& email)
    {
        StringArray parseArray = CProtoUtil::SplitStringByLine(strContext);
        std::size_t index = 0;
        std::size_t Count = parseArray.size();
        for(index = 0 ; index < Count ; index++)
        {
            if(parseArray[index].find("Date: ") != std::string::npos)
            {
                email.date_=parseArray[index];
            }
            if(parseArray[index].find("From: ") != std::string::npos)
            {
                std::string strName;
                std::string strAddr;
                CProtoUtil::ParseFromToString(parseArray[index],strName,strAddr);
                email.emailSender_=senderReceiverInfo(strAddr);
            }
            
            if(parseArray[index].find("To: ") != std::string::npos)
            {
                std::string strName;
                std::string strAddr;
                CProtoUtil::ParseFromToString(parseArray[index],strName,strAddr);
                email.copyReceivers_.push_back(senderReceiverInfo(strAddr));
            }

            if(parseArray[index].find("Content-Type: ") != std::string::npos)
            {
                while(index < Count)
                {
                    email.context_.append(parseArray[index]);
                    index++;
                }
            }
        }
        return true;
    }
}
