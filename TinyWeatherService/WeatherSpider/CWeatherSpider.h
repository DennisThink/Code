/**
 * @file CWeatherSpider.h
 * @author DennisMi (https://www.dennisthink.com/)
 * @brief 天气爬虫的头文件
 * @version 0.1
 * @date 2020-04-01
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef _WEATHER_SPIDER_C_WEATHER_SPIDER_H_
#define _WEATHER_SPIDER_C_WEATHER_SPIDER_H_
#include "CMySQLBean.h"
#include <vector>
using C_T_WEATHER_BEAN_ARRAY = std::vector<C_T_WEATHER_BEAN>; 
class CWeatherSpider final
{
public:
    explicit CWeatherSpider(){}
    virtual ~CWeatherSpider(){};
    static C_T_WEATHER_BEAN_ARRAY GetWeatherByCityWeatherCode(const std::string& strCode);
};
#endif