/**
 * @file CWeatherSpider.cpp
 * @author DennisMi (https://www.dennisthink.com/)
 * @brief 
 * @version 0.1
 * @date 2020-04-01
 * 
 * @copyright Copyright (c) 2020
 * 
 */
// TODO: 部分没有用的头文件考虑删除 
#include "CWeatherSpider.h"
#include <iostream>
#include "../include/thirdparty/httpServer/client_http.hpp"
using HttpClient = SimpleWeb::Client<SimpleWeb::HTTP>;
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <string>
#include <array>
#include <assert.h>
#include "CDate.h"



/**
 * @brief 从string中解析出一天的天气
 * 
 * @param strContext 天气的HTML字符串
 * @return C_T_WEATHER_BEAN 当天的天气
 */
C_T_WEATHER_BEAN GetDetailWeather(const std::string strContext)
{
    C_T_WEATHER_BEAN bean;
/*<li class="sky skyid lv1">
<h1>6日（明天）</h1>
<big class="png40 d00"></big>
<big class="png40 n00"></big>
<p title="晴" class="wea">晴</p>
<p class="tem">
<span>11</span>/<i>-2℃</i>
</p>
<p class="win">
<em>
<span title="北风" class="N"></span>
<span title="西南风" class="SW"></span>
</em>
<i>4-5级转<3级</i>
</p>
<div class="slid"></div>*/
    {
        auto h1Start = strContext.find("<h1>");
        auto h1End = strContext.find("</h1>");
        std::string strDate = strContext.substr(h1Start+4,h1End-h1Start-4);
        //bean.m_F_DATE = strDate;
        //std::cout<<"Date : "<<strDate<<std::endl;
    }
    {
        auto weatherStart = strContext.find("class=\"wea\">");
        auto weatherEnd = strContext.find("</p>",weatherStart);
        std::string strDate = strContext.substr(weatherStart+12,weatherEnd-weatherStart-12);
        bean.m_F_WEATHER = strDate;
        //std::cout<<"Weather : "<<strDate<<std::endl;
    }
    {
        auto weatherStart = strContext.find("<span>");
        auto weatherEnd = strContext.find("</span>",weatherStart);
        std::string strDate = strContext.substr(weatherStart+6,weatherEnd-weatherStart-6);
        bean.m_F_HIGH_TEMP = std::atoi(strDate.c_str());
        //std::cout<<"HighTemp : "<<strDate<<std::endl;
    }

    {
        auto weatherStart = strContext.find("<i>");
        auto weatherEnd = strContext.find("</i>",weatherStart);
        std::string strDate = strContext.substr(weatherStart+3,weatherEnd-weatherStart-3);
        bean.m_F_LOW_TEMP = std::atoi(strDate.c_str());
       // std::cout<<"LowTemp : "<<strDate<<std::endl;
    }

    std::size_t WindDirectIndex = 0;
    {
        auto windStart = strContext.find("<span title=\"");
        auto windEnd = strContext.find("\"",windStart+13);
        std::string strDate = strContext.substr(windStart+13,windEnd-windStart-13);
        //std::cout<<"WindLevel : "<<strDate<<std::endl;
        bean.m_F_WIND_DIRECT = strDate;
        WindDirectIndex = windEnd;
    }
    {
        auto windStart = strContext.find("<i>",WindDirectIndex);
        auto windEnd = strContext.find("</i>",windStart+3);
        std::string strDate = strContext.substr(windStart+3,windEnd-windStart-3);
        bean.m_F_WIND_LEVEL = strDate;
        //std::cout<<"WindDirect : "<<strDate<<std::endl;
    }
    return bean;
}

/**
 * @brief 从li标签的字符串中提取天气HTML字符串
 * 
 * @param strContext 带li标签的天气字符串
 * @return std::string 提取出的天气HTML字符串
 */
std::string GetWeatherArrayStr(const std::string strContext)
{
    std::string strStartTag="<ul class=\"t clearfix\">";
    std::string strEndTag = "</ul>";
    std::size_t startIndex = strContext.find(strStartTag);
    std::size_t endIndex = strContext.find(strEndTag,startIndex);
    std::string subStr = strContext.substr(startIndex,endIndex-startIndex+strEndTag.length());
    return subStr;
}

/**
 * @brief 解析某个地区一周的天气
 * 
 * @param strContext 获取的HTML的页面内容
 * @return C_T_WEATHER_BEAN_ARRAY 一周的天气数组
 */
C_T_WEATHER_BEAN_ARRAY ParseHtmlGetWeather2(const std::string strContext)
{
    C_T_WEATHER_BEAN_ARRAY beanArray;
    std::string subStr = GetWeatherArrayStr(strContext);
    {
        std::size_t liStart = 0;
        std::size_t liEnd = 0;
       
        while(liEnd != std::string::npos)
        {
            liStart = subStr.find("<li",liEnd);
            liEnd = subStr.find("</li>",liStart);
            if(liEnd != std::string::npos)
            {
                std::string strLi = subStr.substr(liStart+3,liEnd-liStart-7);
                auto bean = GetDetailWeather(strLi);
                beanArray.push_back(bean);
            }
           
            liStart = liEnd;
        }
    }
    return beanArray;
}

/**
 * @brief 根据地区编码,获取一周的天气
 * 
 * @param strCode 地区编码
 * @return C_T_WEATHER_BEAN_ARRAY 一周的天气
 */
C_T_WEATHER_BEAN_ARRAY CWeatherSpider::GetWeatherByCityWeatherCode(const std::string& strCode)
{
	HttpClient client("www.weather.com.cn:80");
    C_T_WEATHER_BEAN_ARRAY beanArray;
    if(!strCode.empty())
    {
        std::string strWeather="/weather/"+strCode+".shtml";
		auto httpRsp = client.request("GET", strWeather, "");
        if(httpRsp->status_code == "200 OK")
        {
            beanArray= ParseHtmlGetWeather2(httpRsp->content.string());
        }
    }
    
    if(!beanArray.empty())
    {
        Date date;
        for(auto& item:beanArray)
        {
            item.m_F_DATE = date.ToString();
            date=date+1;
        }

    }
    return beanArray; 
}
