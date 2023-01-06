/**
 * @file CDate.h
 * @author DennisMi (https://www.dennisthink.com/)
 * @brief 时间工具类的实现
 * @version 0.1
 * @date 2020-04-01
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef _C_DATE_H_
#define _C_DATE_H_
#include <string>
#include <time.h>
class Date
{
public:
  explicit Date(int year, int month, int day)  //构造
  :_year(year)
  , _month(month)
  , _day(day)
  {
    if (!isInvalidDate(_year, _month, _day))
    {
      _year = 1900;
      _month = 1;
      _day = 1;
    }
  }
  explicit Date()
  {

    // 基于当前系统的当前日期/时间
    time_t now = time(0);
   
#ifdef WIN32
	tm gmtm;
  localtime_s(&gmtm, &now);
  this->_year = gmtm.tm_year;
  this->_month = gmtm.tm_mon;
  this->_day = gmtm.tm_mday;
#else
	tm *gmt = localtime(&now);
	this->_year = gmt->tm_year;
	this->_month = gmt->tm_mon;
	this->_day = gmt->tm_mday;
#endif
  }

  /**
   * @brief 将当前时间转为YYYY-MM-DD的格式
   * 
   * @return std::string 转换后的字符串
   */
  std::string ToString()
  {
      char buff[16]={0};
#ifdef WIN32
	  sprintf_s(buff, "%4d-%02d-%02d", _year + 1900, _month + 1, _day);
#else
	  sprintf(buff, "%4d-%02d-%02d", _year + 1900, _month + 1, _day);
#endif //  _WIN32

      return std::string(buff);
  }
  
  /**
   * @brief 当前日期增加count天
   * 
   * @param count 增加的天数
   * @return Date 增加后的日期
   */
  Date operator+(int count)
  { 
    Date tmp(*this);
    tmp._day += count;
    ToCorrect(tmp);
    return tmp;
  }
private:
  
  
  /**
   * @brief 当前日期减少若干天
   * 
   * @param count 减少的天数
   * @return Date 减少后的日期
   */
  Date operator-(int count)
  {
    Date tmp(*this);
    tmp._day -= count;
    ToCorrect(tmp);
    return tmp;
  }
  
  /**
   * @brief 前置++
   * 
   * @return Date& 
   */
  Date& operator++()  //前置++
  {
    (*this)++;
    return *this;
  }
  
  /**
   * @brief 后置++
   * 
   * @return Date 
   */
  Date operator++(int) 
  {
    Date tmp(*this);
    (*this)+=1;
    return tmp;
  }
  
  /**
   * @brief 前置--
   * 
   * @return Date& 
   */
  Date& operator--()
  {
    (*this)--;
    return *this;
  }

  /**
   * @brief 后置--
   * 
   * @return Date 
   */
  Date operator--(int)
  {
    Date tmp(*this);
    (*this)--;
    return tmp;
  }


  int operator-(const Date &d)
  {
    int flag = 1;
    Date max = *this;
    Date min = d;
    if (*this<d)
    {
      max = d;
      min = *this;
      flag = -1;
    }
    int count=0;
    while (min != max)
    {
      ++min;
      count++;
    }
    return count*flag;
  }

  Date& operator+=(int day)
  {
    *this = *this + day;
    return *this;
  }

  bool operator!=(const Date &d)
  {
    return !(*this == d);
  }

  bool operator<(const Date &d)
  {
    return !((*this>d)||(*this==d));
  }

  bool operator>=(const Date &d)
  {
    return !(*this<d);
  }

  bool operator>(const Date &d)
  {
    return (_year > d._year
      || (_year == d._year && _month > d._month)
      || (_year == d._year && _month == d._month && _day > d._day));
  }

  bool operator==(const Date &d)
  {
    return ((_year == d._year) && (_month == d._month) && (_day == d._day));
  }
  
public:  
  /**
   * @brief 是否是闰年
   * 
   * @param year 年份
   * @return true 是闰年
   * @return false 不是闰年
   */
  bool IsLeapYear(int year)
  {
    if(year % 400 || (year % 4 && year % 100))
      return true;
    return false;
  }
  
  /**
   * @brief 返回某一年的第几个月的天数
   * 
   * @param year 年份
   * @param month 月数的索引
   * @return int 月份的天数
   */
  int YearsOfMonth(int year, int month)
  {
    int day;
    int days[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    day = days[month];
    if (month == 2)
      day += IsLeapYear(year);
    return day;
  }
  
  /**
   * @brief 更正日期信息
   * 
   * @param d 待修改的日期
   * @return Date 修改后的日志
   */
  Date ToCorrect(Date &d)
  {
    if (d._day>YearsOfMonth(d._year, d._month))
    {
      while (d._day > YearsOfMonth(d._year, d._month))
      {
         d._day -= YearsOfMonth(d._year,d._month);

        if (d._month == 12)
        {
          d._year++;
          d._month = 1;
        }
        else
        {
          ++d._month;
        }
      }
    }
    else
    {
      while (d._day <= 0)
      {
        if (d._month == 1)
        {
          d._year--;
          d._month = 12;
        }
        else
        {
          --d._month;
        }
        d._day += YearsOfMonth(d._year, d._month);
      }
    }
    return d;
  }
  

  /**
   * @brief 是否是合法的日期
   * 
   * @param year 年
   * @param month 月
   * @param day 日
   * @return true 日期合法
   * @return false 日期非法
   */
  bool isInvalidDate(int year, int month, int day)
  {
    if ((year < 1) || (month<0 || month>12) || (day<0 || day>YearsOfMonth(year,month)))
      return false;
    return true;
  }
private:
  int _year;
  int _month;
  int _day;
};

#endif