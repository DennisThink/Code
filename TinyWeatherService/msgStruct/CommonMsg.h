/**
 * @file CommonMsg.h
 * @author DennisMi (https://www.dennisthink.com/)
 * @brief 定义交互消息的头文件，包括了序列化和反序列化
 * @version 0.1
 * @date 2019-07-18
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#ifndef _COMMON_MSG_H_
#define _COMMON_MSG_H_
#include <stdlib.h>
#include <string.h>
#include <string>
#include <vector>
struct IpPortCfg
{
	std::string m_strServerIp;
	int 		m_nPort;
	/**
	 * @brief 获取配置的字符串表示，类似于 127.0.0.1:80
	 *
	 * @return std::string
	 */
	std::string to_string()
	{
		return m_strServerIp + ":" + std::to_string(m_nPort);
	}

	/**
	 * @brief 检查配置是否有效
	 *
	 * @return true 配置有效
	 * @return false 配置无效
	 */
	bool Valid() {
		if(m_strServerIp.empty() || m_nPort < 1024)
		{
			return false;
		}
		else
		{
			return true;
		}
	}
};
/**
 * @brief 服务器配置
 * 
 */
class CServerConfig
{
public:
	std::vector<IpPortCfg> m_clientCfgVec;
	IpPortCfg              m_serverCfg;
	explicit CServerConfig()
	{
		m_serverCfg.m_strServerIp = "127.0.0.1";
		m_serverCfg.m_nPort = 9000;

		m_clientCfgVec.push_back({"127.0.0.1",8000});
	}
};

#endif
