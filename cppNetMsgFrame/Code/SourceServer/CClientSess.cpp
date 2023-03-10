
//
// Copyright(c) 2018 DennisMi.
// dennismi1024@gmail.com
// https://www.dennisthink.com/
// Distributed under the MIT License (http://opensource.org/licenses/MIT)
//

#include "CClientSess.h"
#include "json11.hpp"
#include "CSessManager.h"
#include <iostream>
namespace SourceServer
{
std::shared_ptr<spdlog::logger> CClientSess::ms_loger;

CClientSess::CClientSess(asio::io_service &ioService, std::string &strIp, int port, CSessManager *manager) : m_ioService(ioService),
																											 m_manager(manager),
																											 m_serverIp(strIp),
																											 m_serverPort(port),
																											 m_socket(ioService),
																											 m_ConnectState(STATE_E::ST_NOT_CONNECT)
{
	m_connectInfo = m_serverIp + ":" + std::to_string(m_serverPort);
	//m_bReciveKeepAlive =true;
	StartConnect();
}

/**
 * @brief 连接到服务器
 * 
 */
void CClientSess::StartConnect()
{
	DBG(ms_loger, "Try To Connected To :{}", GetConnectInfo());
	if (!IsConnect())
	{
		m_ConnectState = STATE_E::ST_CONNING;
		WARN(ms_loger, "Start Connect To  IP:{} Port:{}", m_serverIp, m_serverPort);
		tcp::resolver reso(m_ioService);
		std::string strPort = std::to_string(m_serverPort);
		auto endpoint_iterator = reso.resolve({m_serverIp, strPort});
		asio::async_connect(m_socket, endpoint_iterator, [this](std::error_code ec, tcp::endpoint endPt) {
			if (!ec)
			{
				m_ConnectState = STATE_E::ST_CONN_FINISHED;
				do_read();
				INFO(ms_loger, "Connect Success IP:{} Port:{}", this->m_serverIp, this->m_serverPort);
				INFO(ms_loger, "ConnectID :{}:{}", endPt.address().to_string(), endPt.port());
			}
			else
			{
				m_ConnectState = STATE_E::ST_NOT_CONNECT;
				WARN(ms_loger, "Connect Failed To {} Code:{} Msg:{}", this->GetConnectInfo(), ec.value(), ec.message());
			}
		});
	}
	else
	{
		INFO(ms_loger, "Connect Has Established IP:{} Port:{}", this->m_serverIp, this->m_serverPort);
	}
}

/**
 * @brief 断开Socket的连接
 * 
 */
void CClientSess::StopConnect()
{
	INFO(ms_loger, "Connect Closed IP:{},port:{}", m_serverIp, m_serverPort);
	m_ConnectState = STATE_E::ST_NOT_CONNECT;
	m_socket.close();
}

/**
 * @brief 获取套接字的连接状态
 * 
 * @return true 
 * @return false 
 */
bool CClientSess::IsConnect()
{
	return (STATE_E::ST_CONN_FINISHED == m_ConnectState);
}

void CClientSess::handleMessage(const TransBaseMsg_t *msg)
{
	if (msg == nullptr)
	{
		return;
	}
	switch (msg->GetType())
	{
	case MessageType::KeepAliveReq_Type:
	{
		KeepAliveReqMsg reqMsg;
		if (reqMsg.FromString(msg->to_string()))
		{
			handleKeepAliveReq(reqMsg);
		}
		else
		{
			ERR(ms_loger, "Message Not Match:{} {}", msg->to_string(), reqMsg.ToString());
		}
	}
	break;
	case MessageType::KeepAliveRsp_Type:
	{
		KeepAliveRspMsg rspMsg;
		if (rspMsg.FromString(msg->to_string()))
		{
			handleKeepAliveRsp(rspMsg);
		}
		else
		{
			ERR(ms_loger, "Message Not Match:{} {}", msg->to_string(), rspMsg.ToString());
		}
	}
	break;
	default:
	{
		if (m_manager)
		{
			m_manager->handleMessage(msg);
		}
	}
	}
}

/**
 * @brief 从socket读取数据
 * 
 * @return int 
 */
int CClientSess::do_read()
{
	if (IsConnect())
	{
		INFO(ms_loger, "Client  read data ");
		auto self = shared_from_this();
		m_socket.async_read_some(
			asio::buffer(m_recvbuf + m_recvpos, max_length - m_recvpos), [this, self](std::error_code ec, std::size_t length) {
				if (ec)
				{
					m_socket.close();
					m_ConnectState = STATE_E::ST_NOT_CONNECT;
				}
				else
				{
					TransBaseMsg_t msg(m_recvbuf);
					auto curlen = m_recvpos + length;
					INFO(ms_loger, "Client async_read_some:size:{:#x}  ec:{}", length, ec.message());
					while (curlen >= sizeof(Header) && curlen >= msg.GetSize())
					{
						INFO(ms_loger, " read data {} ", curlen);
						handleMessage(&msg);
						curlen -= msg.GetSize();
						memmove(m_recvbuf, m_recvbuf + msg.GetSize(), curlen);
					}
					m_recvpos = (uint32_t)curlen;
					if (m_recvpos < max_length && !ec)
					{
						do_read();
					}
				}
			});
	}
	return 0;
}

/**
 * @brief 发送心跳请求消息
 * 
 * @return true 发送成功
 * @return false 发送失败
 */
bool CClientSess::SendKeepAlive()
{
	DBG(ms_loger, "Send Keep Alive");
	if (IsConnect())
	{
		KeepAliveReqMsg msg("SourceServer");
		auto pMsg = std::make_shared<TransBaseMsg_t>(msg.GetMsgType(), msg.ToString());
		send_msg(pMsg);
		return true;
	}
	else
	{
		WARN(ms_loger, "{} Not Connect", GetConnectInfo());
		StartConnect();
		return false;
	}
}

/**
 * @brief 发送消息到远端服务器
 * 
 * @param msg 待发送的消息
 */
void CClientSess::send_msg(std::shared_ptr<TransBaseMsg_t> msg)
{
	INFO(ms_loger, " send message ");
	auto self = shared_from_this();
	asio::async_write(m_socket, asio::buffer(msg->GetData(), msg->GetSize()), [this, self, msg](std::error_code ec, std::size_t length) {
		if (ec)
		{
			StopConnect();
			StartConnect();
		}
		else
		{
			INFO(ms_loger, "Send Succeed {}", length);
		}
	});
}

/**
 * @brief 处理接收到的心跳请求消息
 * 
 * @param reqMsg 
 */
void CClientSess::handleKeepAliveReq(const KeepAliveReqMsg &reqMsg)
{
	INFO(ms_loger, "Recv KeepAliveReq:{}", reqMsg.ToString());
	KeepAliveRspMsg msg("SourceServer");
	auto pMsg = std::make_shared<TransBaseMsg_t>(msg.GetMsgType(), msg.ToString());
	send_msg(pMsg);
}

/**
 * @brief 处理心跳回复消息
 * 
 * @param rspMsg 心跳回复消息
 */
void CClientSess::handleKeepAliveRsp(const KeepAliveRspMsg &rspMsg)
{
	INFO(ms_loger, "Recv KeepAliveRsp:{}", rspMsg.ToString());
}
} // namespace SourceServer