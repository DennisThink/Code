/**
 * @file CommonConfigStruct.h
 * @author DennisMi (https://www.dennisthink.com/)
 * @brief 定义Mysql连接的配置
 * @version 0.1
 * @date 2020-04-05
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef _COMMON_CONFIG_STRUCT_H_
#define _COMMON_CONFIG_STRUCT_H_
#include <string>
#include <json11.hpp>
class CMySqlConfig
{
public:
    /**
     * @brief 从Json转为Mysql的配置
     * 
     * @param jsonObj 
     * @return true 
     * @return false 
     */
    bool FromJson(json11::Json jsonObj)
    {
        if(!jsonObj["ip"].is_string())
        {
            return false;
        }
        m_Ip = jsonObj["ip"].string_value();


        if(!jsonObj["port"].is_number())
        {
            return false;
        }
        m_Port = jsonObj["port"].int_value();


        if(!jsonObj["username"].is_string())
        {
            return false;
        }
        m_userName = jsonObj["username"].string_value();

        if(!jsonObj["password"].is_string())
        {
            return false;
        }
        m_passwd = jsonObj["password"].string_value();

        if(!jsonObj["database"].is_string())
        {
            return false;
        }
        m_db = jsonObj["database"].string_value();
        return true;
    }
    json11::Json::object ToJson()
    {
        json11::Json::object result=json11::Json::object({
            {"ip",m_Ip},
            {"port",m_Port},
            {"username",m_userName},
            {"password",m_passwd},
            {"database",m_db},
        });
        return result;
    }
public:
    std::string m_Ip;//Mysql服务器的IP地址
    int         m_Port;//MySQL服务器的端口
    std::string m_userName;//数据库用户名
    std::string m_passwd;//数据库密码
    std::string m_db;//数据库名称
};
#endif