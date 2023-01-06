#ifndef _PROTO_UTIL_TEST_CPP_NEW_
#define _PROTO_UTIL_TEST_CPP_NEW_
#include "ServerTest.h"
TEST_CASE("ParseFromTo")
{
    std::string strFrom="From: \"sender@cppemail.com\" <sender@cppemail.com>\r\n";
    std::string strName;
    std::string strAddr;
    CHECK(cpp_email::CProtoUtil::ParseFromToString(strFrom,strName,strAddr));
    CHECK_EQ(strName,"sender@cppemail.com");
    CHECK_EQ(strAddr,"sender@cppemail.com");
}
TEST_CASE("ParseTo")
{
    std::string strFrom="To: receiver <receiver@cppemail.com>\r\n";
    std::string strName;
    std::string strAddr;
    CHECK(cpp_email::CProtoUtil::ParseFromToString(strFrom,strName,strAddr));
    CHECK_EQ(strName,"receiver@cppemail.com");
    CHECK_EQ(strAddr,"receiver@cppemail.com");
}
#endif