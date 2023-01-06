/**
 * @file CMySql.cpp
 * @author DennisMi (https://www.dennisthink.com/)
 * @brief 数据库相关操作的实现类
 * @version 0.1
 * @date 2020-04-05
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include "CMySql.h"
#include <iostream>
#include <stdlib.h>
#define FMT_STRING_ALIAS 1
#include <fmt/format.h>

namespace TinyWeatherService
{

/**
 * @brief MySQL的连接初始化
 * 
 * @return true 初始化成功
 * @return false 初始化失败
 */
bool CMysql::Init()
{
    if (!m_pConnect)
    {
        m_pConnect = mysql_init(NULL);
    }
    return true;
}

/**
 * @brief Construct a new CMysql::CMysql object
 * 
 */
CMysql::CMysql()
{
    SetLogFunc([](const std::string strLog)->void{
        std::cout<<strLog<<std::endl;
    });
}

/**
 * @brief Destroy the CMysql::CMysql object
 * 
 */
CMysql::~CMysql()
{
    if (m_pConnect)
    {
        mysql_close(m_pConnect);
        m_pConnect = nullptr;
    }
}

/**
 * @brief 根据配置连接到mysql数据库
 * 
 * @param cfg 连接配置
 * @return true 连接成功
 * @return false 连接失败
 */
bool CMysql::Connect(const CMySqlConfig& cfg)
{
    return Connect(cfg.m_Ip,
                   cfg.m_Port,
                   cfg.m_db,
                   cfg.m_userName,
                   cfg.m_passwd);
}

/**
 * @brief 根据IP地址,端口号,数据库名称,用户名,密码的信息连接到mysql数据库
 * 
 * @param serverIp mysql服务的IP地址
 * @param port mysql服务的端口号
 * @param strDb 数据库名称
 * @param userName 用户名
 * @param passed 用户密码
 * @return true 连接成功
 * @return false 连接失败
 */
bool CMysql::Connect(const std::string serverIp, const int port, const std::string strDb, const std::string userName, const std::string passed)
{
    Init();
    MYSQL *result = mysql_real_connect(m_pConnect,
                                       serverIp.c_str(),
                                       userName.c_str(),
                                       passed.c_str(),
                                       strDb.c_str(),
                                       (unsigned int)(port), 0, 0);
    if (nullptr != result)
	{
		int nResult = mysql_set_character_set(m_pConnect, "utf8");
		//Show Variable
		{
			std::string strSql = "SHOW VARIABLES LIKE \"%char%\";";
			nResult = mysql_query(m_pConnect, strSql.c_str());
			std::cout << nResult << std::endl;
			MYSQL_RES *result = mysql_store_result(m_pConnect);
			if (result)
			{
				int num_fields = mysql_num_fields(result);
				std::string Fileds[18] = { "" };
				MYSQL_ROW row;

				while ((row = mysql_fetch_row(result)))
				{
					for (int i = 0; i < num_fields; i++)
					{
						Fileds[i] = std::string(row[i]);
						m_logFunc(Fileds[i]);
					}
				}
				mysql_free_result(result);
			}
		}
        return true;
    }
    else
    {
        m_logFunc("Connect To DB Error "+std::string(__FILE__)+"  "+std::to_string(__LINE__));
        return false;
    }
}

/**
 * @brief 根据cityCode和日期,获取当天的天气
 * 
 * @param cityCode 城市代码
 * @param strDate 日期
 * @param weatherBean 当天的天气
 * @return true 获取成功
 * @return false 获取失败
 */
bool CMysql::GetOneDayWeatherByCityCode(const std::string &cityCode, const std::string &strDate, C_T_WEATHER_BEAN &weatherBean)
{
    if (cityCode.empty())
    {
        return false;
    }
    if (!m_pConnect)
    {
        return false;
    }
    std::string SQL_TEMPLATE =
        "SELECT F_WEATHER,\
F_HIGH_TEMP,\
F_LOW_TEMP,\
F_WIND_LEVEL,\
F_WIND_DIRECT \
FROM T_WEATHER WHERE F_CITY_CODE='" +
        cityCode + "' AND F_DATE='" + strDate + "';";
	int nResult = mysql_query(m_pConnect, SQL_TEMPLATE.c_str());
	if(nResult != 0)
    {
        m_logFunc(SQL_TEMPLATE);
		m_logFunc(std::to_string(__LINE__));
        return false;
    }

    MYSQL_RES *result = mysql_store_result(m_pConnect);

    if (result == NULL)
    {
        m_logFunc(SQL_TEMPLATE);
		m_logFunc(std::to_string(__LINE__));
        return false;
    }

    int num_fields = mysql_num_fields(result);
    std::string Fileds[18] = {""};
    MYSQL_ROW row;

    while ((row = mysql_fetch_row(result)))
    {
        for (int i = 0; i < num_fields; i++)
        {
            Fileds[i] = std::string(row[i]);
        }
    }
    weatherBean.m_F_DATE = strDate;
    weatherBean.m_F_CITY_CODE = cityCode;
    weatherBean.m_F_WEATHER = Fileds[0];
    //std::cout << weatherBean.m_F_WEATHER.length() << std::endl;
    weatherBean.m_F_HIGH_TEMP = std::atoi(Fileds[1].c_str());
    weatherBean.m_F_LOW_TEMP = std::atoi(Fileds[2].c_str());
    weatherBean.m_F_WIND_LEVEL = Fileds[3];
    weatherBean.m_F_WIND_DIRECT = Fileds[4];

    mysql_free_result(result);
	m_logFunc(std::to_string(__LINE__));
    return weatherBean.Valid();
}

/**
 * @brief 更新某一天的天气
 * 
 * @param weatherBean 新的天气信息
 * @return true 更新成功
 * @return false 更新失败
 */
bool CMysql::UpdateOneDayWeather(const C_T_WEATHER_BEAN &weatherBean)
{
    if (!weatherBean.Valid())
    {
        m_logFunc("Param Error");
        return false;
    }
    if (!m_pConnect)
    {
        m_logFunc("Connect Failes");
        return false;
    }

#define SQL_ONE_DAY_WEATHER_UPDATE "UPDATE T_WEATHER SET F_WEATHER=\'{}\',F_HIGH_TEMP={},F_LOW_TEMP={},F_WIND_LEVEL=\'{}\',F_WIND_DIRECT=\'{}\',F_UPDATE_TIME=now() WHERE F_CITY_CODE=\'{}\' AND F_DATE=\'{}\';"
    std::string strSql = format(fmt(SQL_ONE_DAY_WEATHER_UPDATE), weatherBean.m_F_WEATHER,
                                weatherBean.m_F_HIGH_TEMP,
                                weatherBean.m_F_LOW_TEMP,
                                weatherBean.m_F_WIND_LEVEL,
                                weatherBean.m_F_WIND_DIRECT,
                                weatherBean.m_F_CITY_CODE,
                                weatherBean.m_F_DATE);
    m_logFunc(strSql);
    if (mysql_query(m_pConnect, strSql.c_str()))
    {
        return false;
    }

    return true;
}

/**
 * @brief 插入一天的天气
 * 
 * @param weatherBean 天气信息
 * @return true 插入成功
 * @return false 插入失败
 */
bool CMysql::InsertOneDayWeather(const C_T_WEATHER_BEAN &weatherBean)
{
    if (!weatherBean.Valid())
    {
        return false;
    }
    if (!m_pConnect)
    {
        return false;
    }

#define SQL_TEMPLATE_INSERT "INSERT INTO T_WEATHER(F_CITY_CODE,F_DATE,F_WEATHER,F_HIGH_TEMP,F_LOW_TEMP,F_WIND_LEVEL,F_WIND_DIRECT) VALUES(\'{}\',\'{}\',\'{}\',{},{},\'{}\',\'{}\');"

    std::string strSql = format(fmt(SQL_TEMPLATE_INSERT), weatherBean.m_F_CITY_CODE,
                                weatherBean.m_F_DATE,
                                weatherBean.m_F_WEATHER,
                                weatherBean.m_F_HIGH_TEMP,
                                weatherBean.m_F_LOW_TEMP,
                                weatherBean.m_F_WIND_LEVEL,
                                weatherBean.m_F_WIND_DIRECT);
    m_logFunc(strSql);
    if (mysql_query(m_pConnect, strSql.c_str()))
    {
        return false;
    }

    MYSQL_RES *result = mysql_store_result(m_pConnect);
    mysql_free_result(result);
    return true;
}

/**
 * @brief 根据城市代码获取城市信息
 * 
 * @param cityCode 城市代码
 * @param addrBean 城市信息
 * @return true 获取成功
 * @return false 获取失败
 */
bool CMysql::GetCityCodeAddr(const std::string &cityCode, C_T_CITY_CODE_ADDR &addrBean)
{
    if (cityCode.empty())
    {
        return false;
    }
    if (!m_pConnect)
    {
        return false;
    }

    std::string SQL_TEMPLATE =
        "SELECT F_CITY_CODE,\
F_COUNTRY,\
F_PROVINCE,\
F_CITY,\
F_AREA,\
F_WEATHER_CODE \
FROM T_CITY_CODE_ADDR WHERE F_CITY_CODE='" +
        cityCode + "';";
     m_logFunc(std::to_string(__LINE__));
    if (mysql_query(m_pConnect, SQL_TEMPLATE.c_str()))
    {
        return false;
    }

    MYSQL_RES *result = mysql_store_result(m_pConnect);

    if (result == NULL)
    {
        return false;
    }

    int num_fields = mysql_num_fields(result);
    std::string Fileds[18] = {""};
    MYSQL_ROW row;

    while ((row = mysql_fetch_row(result)))
    {
        for (int i = 0; i < num_fields; i++)
        {
            Fileds[i] = std::string(row[i]);
        }
    }
    addrBean.m_F_CITY_CODE = Fileds[0];
    addrBean.m_F_COUNTRY = Fileds[1];
    addrBean.m_F_PROVINCE = Fileds[2];
    addrBean.m_F_CITY = Fileds[3];
    addrBean.m_F_AREA = Fileds[4];
    addrBean.m_F_WEATHER_CODE = Fileds[5];

    mysql_free_result(result);
    return true;
}


/**
 * @brief 根据城市信息获取城市代码
 * 
 * @param strProvince 省级信息
 * @param strCity 城市级信息
 * @param allBeans 所有可能的情况
 * @return true 获取成功
 * @return false 获取失败
 */
bool CMysql::GetCityCodeByAddr(const std::string& strProvince,const std::string& strCity,C_T_CITY_CODE_ADDR_ARRAY_T& allBeans)
{
    if (!m_pConnect)
    {
        return false;
    }

    if(strProvince.empty())
    {
        return false;
    }

    if(strCity.empty())
    {
        return false;
    }
    std::string SQL_TEMPLATE =
        "SELECT F_CITY_CODE,\
F_COUNTRY,\
F_PROVINCE,\
F_CITY,\
F_AREA,\
F_WEATHER_CODE \
FROM T_CITY_CODE_ADDR WHERE F_PROVINCE LIKE '"+strProvince+"' AND ( F_CITY LIKE '"+strCity+"' OR F_AREA LIKE '"+strCity+"');";
	if (m_logFunc)
	{
		m_logFunc(SQL_TEMPLATE);
	}
    if (mysql_query(m_pConnect, SQL_TEMPLATE.c_str()))
	{
		m_logFunc(std::to_string(__LINE__));
        return false;
    }

    MYSQL_RES *result = mysql_store_result(m_pConnect);

    if (result == NULL)
    {
        return false;
    }
	m_logFunc(std::to_string(__LINE__));
    int num_fields = mysql_num_fields(result);
	m_logFunc(std::to_string(num_fields) + " "+std::to_string(result->row_count)+"  "+ std::to_string(__LINE__));
    std::string Fileds[18] = {""};
    MYSQL_ROW row;
    C_T_CITY_CODE_ADDR addrBean;
	row = mysql_fetch_row(result);
    while (row)
    {
        for (int i = 0; i < num_fields; i++)
        {
            Fileds[i] = std::string(row[i]);
        }
        addrBean.m_F_CITY_CODE = Fileds[0];
        addrBean.m_F_COUNTRY = Fileds[1];
        addrBean.m_F_PROVINCE = Fileds[2];
        addrBean.m_F_CITY = Fileds[3];
        addrBean.m_F_AREA = Fileds[4];
        addrBean.m_F_WEATHER_CODE = Fileds[5];
        allBeans.push_back(addrBean);
		m_logFunc(std::to_string(__LINE__));
		row = mysql_fetch_row(result);
    }
    mysql_free_result(result);
	m_logFunc(std::to_string(__LINE__));
    return true;
}


/**
 * @brief 获取所有城市的城市代码
 * 
 * @param beanArray 城市代码数据(返回参数)
 * @return true 获取成功
 * @return false 获取失败
 */
bool CMysql::GetAllCityCodeAddr(C_T_CITY_CODE_ADDR_ARRAY_T &beanArray)
{
    if (!m_pConnect)
    {
        return false;
    }

    std::string SQL_TEMPLATE =
        "SELECT F_CITY_CODE,\
F_COUNTRY,\
F_PROVINCE,\
F_CITY,\
F_AREA,\
F_WEATHER_CODE \
FROM T_CITY_CODE_ADDR;";
	if (m_logFunc)
	{
		m_logFunc(SQL_TEMPLATE);
	}
    if (mysql_query(m_pConnect, SQL_TEMPLATE.c_str()))
    {
        std::cout << "SQL: " << SQL_TEMPLATE << std::endl;
        return false;
    }

    MYSQL_RES *result = mysql_store_result(m_pConnect);

    if (result == NULL)
    {
        return false;
    }
    int num_fields = mysql_num_fields(result);
    std::string Fileds[18] = {""};
    MYSQL_ROW row;
    C_T_CITY_CODE_ADDR addrBean;
    while ((row = mysql_fetch_row(result)))
    {
        for (int i = 0; i < num_fields; i++)
        {
            Fileds[i] = std::string(row[i]);
        }
        addrBean.m_F_CITY_CODE = Fileds[0];
        addrBean.m_F_COUNTRY = Fileds[1];
        addrBean.m_F_PROVINCE = Fileds[2];
        addrBean.m_F_CITY = Fileds[3];
        addrBean.m_F_AREA = Fileds[4];
        addrBean.m_F_WEATHER_CODE = Fileds[5];
        beanArray.push_back(addrBean);
    }
    mysql_free_result(result);
    return true;
}

/**
 * @brief 插入城市的地址信息
 * 
 * @param addrBean 城市地址信息
 * @return true 插入成功
 * @return false 插入失败
 */
bool CMysql::InsertCityCodeAddr(const C_T_CITY_CODE_ADDR &addrBean)
{
    if (!addrBean.Valid())
    {
        return false;
    }
    if (!m_pConnect)
    {
        return false;
    }

#define SQL_CITY_CODE_ADDR_INSERT "INSERT INTO T_CITY_CODE_ADDR(F_CITY_CODE,F_COUNTRY,F_PROVINCE,F_CITY,F_AREA,F_WEATHER_CODE) VALUES(\'{}\',\'{}\',\'{}\',\'{}\',\'{}\',\'{}\');"

    std::string strSql = format(fmt(SQL_CITY_CODE_ADDR_INSERT), addrBean.m_F_CITY_CODE,
                                addrBean.m_F_COUNTRY,
                                addrBean.m_F_PROVINCE,
                                addrBean.m_F_CITY,
                                addrBean.m_F_AREA,
                                addrBean.m_F_WEATHER_CODE);
	if (m_logFunc)
	{
		m_logFunc(strSql);
	}

    if (mysql_query(m_pConnect, strSql.c_str()))
    {
        return false;
    }

    MYSQL_RES *result = mysql_store_result(m_pConnect);
    mysql_free_result(result);
    return true;
}

/**
 * @brief 插入邮件订阅列表
 * 
 * @param emailCodeBean 邮件订阅信息
 * @return true 插入成功
 * @return false 插入失败
 */
bool CMysql::InsertSubEmailList(const C_T_SUBSCRIBE_EMAIL_BEAN& emailCodeBean)
{
    if (!emailCodeBean.Valid())
    {
        return false;
    }
    if (!m_pConnect)
    {
        return false;
    }

#define SQL_SUB_EMAIL_LIST_INSERT "INSERT INTO T_SUBSCRIBE_EMAIL_LIST(F_EMAIL,F_CITY_CODE,F_START_DATE,F_END_DATE) VALUES(\'{}\',\'{}\',\'{}\',\'{}\');"

    std::string strSql = format(fmt(SQL_SUB_EMAIL_LIST_INSERT), emailCodeBean.m_F_EMAIL,
                                emailCodeBean.m_F_CITY_CODE,
                                emailCodeBean.m_F_START_DATE,
                                emailCodeBean.m_F_END_DATE);
	if (m_logFunc)
	{
		m_logFunc(strSql);
	}
    if (mysql_query(m_pConnect, strSql.c_str()))
    {
        return false;
    }

    MYSQL_RES *result = mysql_store_result(m_pConnect);
    mysql_free_result(result);
    return true;
}

/**
 * @brief 删除邮件和订阅城市的对应关系
 * 
 * @param strEmail 订阅者的邮件
 * @param strCityCode 订阅的城市
 * @return true 删除成功
 * @return false 删除失败
 */
bool CMysql::DeleteSubEmailList(const std::string &strEmail, const std::string &strCityCode)
{
    if(strEmail.empty())
    {
        return false;
    }
    if(strCityCode.empty())
    {
        return false;
    }

#define SQL_SUB_EMAIL_LIST_DELETE "DELETE FROM  T_SUBSCRIBE_EMAIL_LIST WHERE F_EMAIL=\'{}\' AND F_CITY_CODE=\'{}\';"

    std::string strSql = format(fmt(SQL_SUB_EMAIL_LIST_DELETE),strEmail,strCityCode);
	if (m_logFunc)
	{
		m_logFunc(strSql);
	}
    if (mysql_query(m_pConnect, strSql.c_str()))
    {
        return false;
    }

    MYSQL_RES *result = mysql_store_result(m_pConnect);
    mysql_free_result(result);
    return true;
}

/**
 * @brief 获取所有的邮件订阅信息
 * 
 * @param emailCodeBean 所有的订阅信息
 * @return true 获取成功
 * @return false 获取失败
 */
bool CMysql::GetAllEmailList(C_T_SUBSCRIBE_EMAIL_BEAN_VECTOR_T& emailCodeBean)
{
    if(!emailCodeBean.empty())
    {
        return false;
    }
    if (!m_pConnect)
    {
        return false;
    }

    std::string SQL_TEMPLATE =
        "SELECT F_EMAIL,\
F_CITY_CODE,\
F_START_DATE,\
F_END_DATE \
FROM T_SUBSCRIBE_EMAIL_LIST;";
	if (m_logFunc)
	{
		m_logFunc(SQL_TEMPLATE);
	}
    if (mysql_query(m_pConnect, SQL_TEMPLATE.c_str()))
    {
        std::cout << "SQL: " << SQL_TEMPLATE << std::endl;
        return false;
    }

    MYSQL_RES *result = mysql_store_result(m_pConnect);

    if (result == NULL)
    {
        return false;
    }
    int num_fields = mysql_num_fields(result);
    std::string Fileds[18] = {""};
    MYSQL_ROW row;
    C_T_SUBSCRIBE_EMAIL_BEAN addrBean;
    while ((row = mysql_fetch_row(result)))
    {
        for (int i = 0; i < num_fields; i++)
        {
            Fileds[i] = std::string(row[i]);
        }
        addrBean.m_F_EMAIL = Fileds[0];
        addrBean.m_F_CITY_CODE = Fileds[1];
        addrBean.m_F_START_DATE = Fileds[2];
        addrBean.m_F_END_DATE = Fileds[3];
        emailCodeBean.push_back(addrBean);
    }
    mysql_free_result(result);
    return true;
}

/**
 * @brief 获取某个邮箱的订阅城市列表
 * 
 * @param strEmail 邮箱
 * @param emailCodeBean 订阅列表 
 * @return true 获取成功
 * @return false 获取失败
 */
bool CMysql::SelectSubEmailList(const std::string& strEmail,C_T_SUBSCRIBE_EMAIL_BEAN_VECTOR_T& emailCodeBean)
{
    if(strEmail.empty())
    {
        return false;
    }
    if(!emailCodeBean.empty())
    {
        return false;
    }
    if (!m_pConnect)
    {
        return false;
    }

    std::string SQL_TEMPLATE =
        "SELECT F_EMAIL,\
F_CITY_CODE,\
F_START_DATE,\
F_END_DATE \
FROM T_SUBSCRIBE_EMAIL_LIST WHERE F_EMAIL='"+strEmail+"';";
	if (m_logFunc)
	{
		m_logFunc(SQL_TEMPLATE);
	}
    if (mysql_query(m_pConnect, SQL_TEMPLATE.c_str()))
    {
        std::cout << "SQL: " << SQL_TEMPLATE << std::endl;
        return false;
    }

    MYSQL_RES *result = mysql_store_result(m_pConnect);

    if (result == NULL)
    {
        return false;
    }
    int num_fields = mysql_num_fields(result);
    std::string Fileds[18] = {""};
    MYSQL_ROW row;
    C_T_SUBSCRIBE_EMAIL_BEAN addrBean;
    while ((row = mysql_fetch_row(result)))
    {
        for (int i = 0; i < num_fields; i++)
        {
            Fileds[i] = std::string(row[i]);
        }
        addrBean.m_F_EMAIL = Fileds[0];
        addrBean.m_F_CITY_CODE = Fileds[1];
        addrBean.m_F_START_DATE = Fileds[2];
        addrBean.m_F_END_DATE = Fileds[3];
        emailCodeBean.push_back(addrBean);
    }
    mysql_free_result(result);
    return true;
}

/**
 * @brief 
 * 
 * @return true 
 * @return false 
 */
bool CMysql::Close()
{
    if (m_pConnect)
    {
        mysql_close(m_pConnect);
        m_pConnect = nullptr;
        return true;
    }
    else
    {
        return false;
    }
}
} // namespace DennisThink