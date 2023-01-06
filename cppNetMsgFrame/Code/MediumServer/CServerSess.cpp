#include "CClientSess.h"
namespace MediumServer
{
std::shared_ptr<spdlog::logger> CServerSess::ms_loger;

/**
 * @brief 从socket的读取数据的函数
 * 
 */
void CServerSess::do_read()
{
	INFO(ms_loger, "Server Read Data ");
	auto self = shared_from_this();
	m_socket.async_read_some(
		asio::buffer(m_recvbuf + m_recvpos, max_length - m_recvpos),
		[this, self](std::error_code ec, std::size_t length) {
			TransBaseMsg_t msg(m_recvbuf);
			auto curlen = m_recvpos + length;
			INFO(ms_loger, "Server async_read_some:size:{:#x}  ec:{}", length,
				 ec.message());
			while (curlen >= sizeof(Header) && curlen >= msg.GetSize())
			{
				INFO(ms_loger, "Server  read data {} ", curlen);
				handle_message(&msg);
				curlen -= msg.GetSize();
				memmove(m_recvbuf, m_recvbuf + msg.GetSize(), curlen);
			}
			m_recvpos = (uint32_t)curlen;
			if (m_recvpos < max_length && !ec)
			{
				do_read();
			}
			else
			{
				m_bConnect = false;
				m_server->CheckAllConnect();
			}
		});
}

/**
 * @brief 当do_read函数接收到一个完整消息的时候，调用此函数，在此函数中完成消息类型的判断和消息分发
 * 
 * @param hdr 
 */
void CServerSess::handle_message(const TransBaseMsg_t *hdr)
{
	switch (hdr->GetType())
	{
	case MessageType::KeepAliveReq_Type:
	{
		KeepAliveReqMsg msg;
		if (msg.FromString(hdr->to_string()))
		{
			handleKeepAliveReq(msg);
		}
		else
		{
			ERR(ms_loger, "Bad KeepAlivReqMsg {}", hdr->to_string());
		}
	}
	break;
	case MessageType::KeepAliveRsp_Type:
	{
		KeepAliveRspMsg msg;
		if (msg.FromString(hdr->to_string()))
		{
			handleKeepAliveRsp(msg);
		}
		else
		{
			ERR(ms_loger, "Bad KeepAlivReqMsg {}", hdr->to_string());
		}
	}
	break;
	default:
	{
	}
	break;
	}
}

/**
 * @brief 处理心跳请求消息
 * 
 * @param reqMsg 心跳请求消息
 */
void CServerSess::handleKeepAliveReq(const KeepAliveReqMsg &reqMsg)
{
	INFO(ms_loger, "KeepAliveReq:{}", reqMsg.ToString());
	KeepAliveRspMsg rspMsg("MediumServer");
	auto pMsg =
		std::make_shared<TransBaseMsg_t>(rspMsg.GetMsgType(), rspMsg.ToString());
	SendMessage(pMsg);
}

/**
 * @brief 处理心跳回复消息
 * 
 * @param rspMsg 心跳回复消息
 */
void CServerSess::handleKeepAliveRsp(const KeepAliveRspMsg &rspMsg)
{
	INFO(ms_loger, "KeepAliveRsp:{}", rspMsg.ToString());
}
} // namespace MediumServer