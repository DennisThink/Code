#include "CImapProtoCmd.h"
#include "ProtoUtil.h"
#include <algorithm>
#include <iostream>
namespace cpp_email
{
CImapProtoCmd CImapProtoCmd::FromString(const std::string &strValue)
{
    {
        auto okPos = strValue.find_first_of("* OK");
        if (okPos != std::string::npos)
        {
            return CImapProtoCmd(ImapCode_t::IMAP_OK, strValue.substr(okPos, strValue.length() - okPos - 1), false);
        }
    }
    {
        auto errPos = strValue.find_first_of("* CAPABILITY");
        if (errPos != std::string::npos)
        {
            return CImapProtoCmd(ImapCode_t::IMAP_OK, strValue.substr(errPos, strValue.length() - errPos - 1), false);
        }
    }
    return CImapProtoCmd(ImapCode_t::IMAP_BAD, "UnKnown Cmd", false);
}

PARSE_IMAP_RESULT CImapProtoReqCmd::FromString(const std::string &strValue, CImapProtoReqCmd &cmd)
{
    auto firstSpacePos = strValue.find(" ");
    if (firstSpacePos != std::string::npos)
    {
        auto secondSpacePos = strValue.find(" ", firstSpacePos+1);
        std::string strId = strValue.substr(0, firstSpacePos);
        std::string strCode ="";
        

        std::string strMessage="";
        if (secondSpacePos != std::string::npos)
        {
            strCode = strValue.substr(firstSpacePos+1, secondSpacePos - firstSpacePos-1);
            strMessage = strValue.substr(secondSpacePos+1, strValue.length() - secondSpacePos-3);
        }
        else
        {
            strCode = strValue.substr(firstSpacePos+1,strValue.length() - firstSpacePos-3);
            strMessage = "";
        }
        
        std::transform(strCode.begin(), strCode.end(), strCode.begin(), ::toupper);
        std::cout<<strCode<<std::endl;
        if (strCode == "LOGIN")
        {
            cmd = CImapProtoReqCmd(strId, IMAP_CMD_t::IMAP_CMD_LOGIN, strMessage);
            return PARSE_IMAP_RESULT::PARSE_IMAP_SUCCEED;
        }
        else if (strCode == "CAPABILITY")
        {
            cmd = CImapProtoReqCmd(strId, IMAP_CMD_t::IMAP_CMD_CAPABILITY, strMessage);
            return PARSE_IMAP_RESULT::PARSE_IMAP_SUCCEED;
        }
        else if (strCode == "SELECT")
        {
            cmd = CImapProtoReqCmd(strId, IMAP_CMD_t::IMAP_CMD_SELECT, strMessage);
            return PARSE_IMAP_RESULT::PARSE_IMAP_SUCCEED;
        }
        else if (strCode == "EXAMINE")
        {
            cmd = CImapProtoReqCmd(strId, IMAP_CMD_t::IMAP_CMD_EXAMINE, strMessage);
            return PARSE_IMAP_RESULT::PARSE_IMAP_SUCCEED;
        }
        else if (strCode == "CREATE")
        {
            cmd = CImapProtoReqCmd(strId, IMAP_CMD_t::IMAP_CMD_CREATE, strMessage);
            return PARSE_IMAP_RESULT::PARSE_IMAP_SUCCEED;
        }
        else if (strCode == "RENAME")
        {
            cmd = CImapProtoReqCmd(strId, IMAP_CMD_t::IMAP_CMD_RENAME, strMessage);
            return PARSE_IMAP_RESULT::PARSE_IMAP_SUCCEED;
        }
        else if (strCode == "DELETE")
        {
            cmd = CImapProtoReqCmd(strId, IMAP_CMD_t::IMAP_CMD_DELETE, strMessage);
            return PARSE_IMAP_RESULT::PARSE_IMAP_SUCCEED;
        }
        else if (strCode == "SUBSCRIBE")
        {
            cmd = CImapProtoReqCmd(strId, IMAP_CMD_t::IMAP_CMD_SUBSCRIBE, strMessage);
            return PARSE_IMAP_RESULT::PARSE_IMAP_SUCCEED;
        }
        else if (strCode == "UNSUBSCRIBE")
        {
            cmd = CImapProtoReqCmd(strId, IMAP_CMD_t::IMAP_CMD_UN_SUBSCRIBE, strMessage);
            return PARSE_IMAP_RESULT::PARSE_IMAP_SUCCEED;
        }
        else if (strCode == "LSUB")
        {
            cmd = CImapProtoReqCmd(strId, IMAP_CMD_t::IMAP_CMD_LSUB, strMessage);
            return PARSE_IMAP_RESULT::PARSE_IMAP_SUCCEED;
        }
        else if (strCode == "LIST")
        {
            cmd = CImapProtoReqCmd(strId, IMAP_CMD_t::IMAP_CMD_LIST, strMessage);
            return PARSE_IMAP_RESULT::PARSE_IMAP_SUCCEED;
        }
        else if (strCode == "FETCH")
        {
            cmd = CImapProtoReqCmd(strId, IMAP_CMD_t::IMAP_CMD_FETCH, strMessage);
            return PARSE_IMAP_RESULT::PARSE_IMAP_SUCCEED;
        }
        else if (strCode == "LOGOUT")
        {
            cmd = CImapProtoReqCmd(strId, IMAP_CMD_t::IMAP_CMD_LOGOUT, strMessage);
            return PARSE_IMAP_RESULT::PARSE_IMAP_SUCCEED;
        }
        else
        {
            cmd = CImapProtoReqCmd(strId, IMAP_CMD_t::IMAP_CMD_UNKNOWN_CMD, strMessage);
            return PARSE_IMAP_RESULT::PARSE_IMAP_FAILED;
        }
    }
    return PARSE_IMAP_RESULT::PARSE_IMAP_FAILED;
}

} // namespace cpp_email