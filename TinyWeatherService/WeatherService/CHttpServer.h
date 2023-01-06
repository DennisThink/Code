/**
 * @file CHttpServer.h
 * @author DennisMi (https://www.dennisthink.com/)
 * @brief 用来处理HTTP请求的类
 * @version 0.1
 * @date 2019-08-30
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#ifndef _DENNIS_THINK_C_HTTP_SERVER_H_
#define _DENNIS_THINK_C_HTTP_SERVER_H_
#include "asio_common.h"
#include "Log.h"
#include <memory>
#include <map>
#include "server_http.hpp"
#include "SnowFlake.h"
#include "CommonMsg.h"
#include "CMySql.h"
using HttpServer = SimpleWeb::Server<SimpleWeb::HTTP>;

namespace ClientCore {
	class CMediumServer;
	class CHttpServer : public std::enable_shared_from_this<CHttpServer>
	{
	public:
		explicit CHttpServer(asio::io_service& ioService,CMediumServer* pServer) :m_httpServer(ioService),m_pServer(pServer),m_msgIdUtil(2,2) {

		}

		void Start(const IpPortCfg& cfg,const CMySqlConfig& mysqlCfg)
		{
			m_httpServer.config.port = cfg.m_nPort;
			Init();
			m_httpServer.start();
			m_mySqlUtil.Connect(mysqlCfg);
		}

		void Stop()
		{
			m_httpServer.stop();
		}

		static std::shared_ptr<spdlog::logger> ms_loger;

		std::string GenerateMsgId() {
			return std::to_string(m_msgIdUtil.nextId());
		}
	private:
		void Get_OneDayWeather(std::shared_ptr<HttpServer::Response> response, std::shared_ptr<HttpServer::Request> request);
		void Get_OneWeekWeather(std::shared_ptr<HttpServer::Response> response, std::shared_ptr<HttpServer::Request> request);
		//get_sub_list_by_email
		void Get_SubListByEmail(std::shared_ptr<HttpServer::Response> response, std::shared_ptr<HttpServer::Request> request);
		//add_sub_city_by_email
		void handlePostAddSubCityByEmail(std::shared_ptr<HttpServer::Response> response, std::shared_ptr<HttpServer::Request> request);
		//del_sub_city_by_email
		void handlePostDelSubCityByEmail(std::shared_ptr<HttpServer::Response> response, std::shared_ptr<HttpServer::Request> request);
		//
		void Get_CityCode(std::shared_ptr<HttpServer::Response> response, std::shared_ptr<HttpServer::Request> request);
		
		void Get_Version(std::shared_ptr<HttpServer::Response> response, std::shared_ptr<HttpServer::Request> request);

		void WriteToRsp(std::shared_ptr<HttpServer::Response> response, const std::string strRsp);
		void Init();

		std::string GetHttpParamValue(std::shared_ptr<HttpServer::Request> request,const std::string strKey);
		HttpServer m_httpServer;
		CMediumServer* m_pServer;
		SnowFlake m_msgIdUtil;

		TinyWeatherService::CMysql m_mySqlUtil;//数据库操作的类
	};
}
#endif