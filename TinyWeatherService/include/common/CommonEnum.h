/**
 * @brief 定义基础的枚举类型
 * 
 */

#ifndef _COMMON_ENUM_H_
#define _COMMON_ENUM_H_
/**
 * @brief 两个地址的区别的不同级别
 * 
 */
enum DIFF_LEVEL
{
    COUNTRY_DIFF=0,//国家不同
    PROVINCE_DIFF=1,//省不同
    CITY_DIFF=2,//市不同
    AREA_DIFF=3,//县不同
    NO_DIFF=4//没有不同
};
#endif