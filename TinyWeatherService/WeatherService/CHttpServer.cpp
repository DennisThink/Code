/**
 * @file CHttpServer.cpp
 * @author DennisMi (https://www.dennisthink.com/)
 * @brief HTTP请求处理的实现
 * @version 0.1
 * @date 2019-09-12
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include "CHttpServer.h"
#include "CMediumServer.h"
#include "HttpReqRspStruct.h"
#include "CDate.h"
#include "CMySQLBean.h"
#include "CommonConfig.h"
#include <time.h>
namespace ClientCore
{
	std::shared_ptr<spdlog::logger> CHttpServer::ms_loger;
	/**
	 * @brief 获取服务程序的版本
	 * 
	 * @param response 
	 * @param request 
	 */
	void CHttpServer::Get_Version(std::shared_ptr<HttpServer::Response> response, std::shared_ptr<HttpServer::Request> request) {
		if (request)
		{
			std::string strEchoStr = "TinyWeatherService " + g_SERVER_VERSION + " Support by https://www.dennisthink.com/";
			*response << "HTTP/1.1 200 OK\r\nContent-Length: " << strEchoStr.length() << "\r\n\r\n"
				<< strEchoStr;
		}
	}

	std::string CHttpServer::GetHttpParamValue(std::shared_ptr<HttpServer::Request> request, const std::string strKey)
	{
		auto paramMap = request->parse_query_string();
		if (0 == paramMap.count(strKey))
		{
			return "";
		}
		else
		{
			return paramMap.equal_range(strKey).first->second;
		}
	}

	/**
	 * @brief 获取当天的天气
	 * 
	 * @param response HTTP回复
	 * @param request HTTP请求
	 */
	void CHttpServer::Get_OneDayWeather(std::shared_ptr<HttpServer::Response> response, std::shared_ptr<HttpServer::Request> request)
	{
		//LOG_INFO(ms_loger, "URL:{} Params:{}  Body:{} ", req.url().URI(), req.url().query(), req.body());
		std::string strCityCode =GetHttpParamValue(request,"CityCode");
		std::string strToken = GetHttpParamValue(request, "Token");

		if (strCityCode.empty())
		{
			HttpRspBase rspMsg(EMPTY_CITY_CODE);
			WriteToRsp(response, rspMsg.ToString());
			LOG_INFO(ms_loger, "RSP:{}", rspMsg.ToString());
			return;
		}
		if (strToken.empty())
		{
			HttpRspBase rspMsg(EMPTY_TOKEN);
			WriteToRsp(response, rspMsg.ToString());
			LOG_INFO(ms_loger, "RSP:{}", rspMsg.ToString());
			return;
		}
		C_T_WEATHER_BEAN weatherBean;

		Date dateUtil;
		m_mySqlUtil.GetOneDayWeatherByCityCode(strCityCode, dateUtil.ToString(), weatherBean);

		C_T_CITY_CODE_ADDR addrBean;
		m_mySqlUtil.GetCityCodeAddr(strCityCode, addrBean);

		HttpGetOneDayWeatherRsp rspMsg;
		OneDayWeatherElem_t elem;
		elem.m_cityName = addrBean.m_F_COUNTRY + addrBean.m_F_PROVINCE + addrBean.m_F_CITY + addrBean.m_F_AREA;
		elem.m_date = dateUtil.ToString();
		elem.m_highTemp = weatherBean.m_F_HIGH_TEMP;
		elem.m_lowTemp = weatherBean.m_F_LOW_TEMP;
		elem.m_weather = weatherBean.m_F_WEATHER;
		elem.m_windDirect = weatherBean.m_F_WIND_DIRECT;
		elem.m_windLevel = weatherBean.m_F_WIND_LEVEL;
		rspMsg.SetElem(elem);
		WriteToRsp(response, rspMsg.ToString());
		LOG_INFO(ms_loger, "RSP:{}", rspMsg.ToString());
		return;
	}

	void CHttpServer::WriteToRsp(std::shared_ptr<HttpServer::Response> response, const std::string strRsp)
	{
		SimpleWeb::CaseInsensitiveMultimap headerMap;
		headerMap.insert({ "content-type","text/json;charset=utf-8" });
		response->write(strRsp,headerMap);
	}

	void CHttpServer::Get_OneWeekWeather(std::shared_ptr<HttpServer::Response> response, std::shared_ptr<HttpServer::Request> request)
	{
		std::string strCityCode = GetHttpParamValue(request, "CityCode");
		std::string strToken = GetHttpParamValue(request, "Token");

		if (strCityCode.empty())
		{
			HttpRspBase rspMsg(EMPTY_CITY_CODE);
			WriteToRsp(response, rspMsg.ToString());
			LOG_INFO(ms_loger, "RSP:{}", rspMsg.ToString());
			return;
		}
		if (strToken.empty())
		{
			HttpRspBase rspMsg(EMPTY_TOKEN);
			WriteToRsp(response, rspMsg.ToString());
			LOG_INFO(ms_loger, "RSP:{}", rspMsg.ToString());
			return;
		}
		C_T_WEATHER_BEAN weatherBean;

		C_T_CITY_CODE_ADDR addrBean;
		m_mySqlUtil.GetCityCodeAddr(strCityCode, addrBean);
		Date dateUtil;
		HttpGetOneWeekWeatherRsp rspMsg;
		for (int i = 0; i < 7; i++)
		{
			OneDayWeatherElem_t elem;
			m_mySqlUtil.GetOneDayWeatherByCityCode(strCityCode, dateUtil.ToString(), weatherBean);
			elem.m_cityName = addrBean.m_F_COUNTRY + addrBean.m_F_PROVINCE + addrBean.m_F_CITY + addrBean.m_F_AREA;
			elem.m_date = dateUtil.ToString();
			elem.m_highTemp = weatherBean.m_F_HIGH_TEMP;
			elem.m_lowTemp = weatherBean.m_F_LOW_TEMP;
			elem.m_weather = weatherBean.m_F_WEATHER;
			elem.m_windDirect = weatherBean.m_F_WIND_DIRECT;
			elem.m_windLevel = weatherBean.m_F_WIND_LEVEL;
			rspMsg.AddElem(elem);
			dateUtil = dateUtil + 1;
		}
		WriteToRsp(response, rspMsg.ToString());
		LOG_INFO(ms_loger, "RSP:{}", rspMsg.ToString());
		return;
	}

	//get_sub_list_by_email
	void CHttpServer::Get_SubListByEmail(std::shared_ptr<HttpServer::Response> response, std::shared_ptr<HttpServer::Request> request)
	{
		if (request)
		{
			std::string strRsp = "Design By https://www.dennisthink.com/ Email dennismi1024@gmail.com";
			WriteToRsp(response, strRsp);
			LOG_INFO(ms_loger, "RSP:{}", strRsp);
		}
	}

	//add_sub_city_by_email
	void CHttpServer::handlePostAddSubCityByEmail(std::shared_ptr<HttpServer::Response> response, std::shared_ptr<HttpServer::Request> request)
	{
		if (request)
		{
			std::string strRsp = "Design By https://www.dennisthink.com/ Email dennismi1024@gmail.com";
			WriteToRsp(response, strRsp);
			LOG_INFO(ms_loger, "RSP:{}", strRsp);
		}
	}
	//del_sub_city_by_email
	void CHttpServer::handlePostDelSubCityByEmail(std::shared_ptr<HttpServer::Response> response, std::shared_ptr<HttpServer::Request> request)
	{
		if (request)
		{
			std::string strRsp = "Design By https://www.dennisthink.com/ Email dennismi1024@gmail.com";
			WriteToRsp(response, strRsp);
			LOG_INFO(ms_loger, "RSP:{}", strRsp);
		}
	}
	//
	void CHttpServer::Get_CityCode(std::shared_ptr<HttpServer::Response> response, std::shared_ptr<HttpServer::Request> request)
	{
		std::string strCountry = GetHttpParamValue(request,"Country");
		std::string strProvince = GetHttpParamValue(request, "Province");
		std::string strCity = GetHttpParamValue(request, "City");
		LOG_INFO(ms_loger, "Country {} Province:{} City:{}", strCountry, strProvince, strCity);
		if (strCountry.empty())
		{
			HttpRspBase rspMsg(EMPTY_COUNTRY);
			WriteToRsp(response, rspMsg.ToString());
			LOG_INFO(ms_loger, "RSP:{}", rspMsg.ToString());
			return;
		}
		if (strCity.empty())
		{
			HttpRspBase rspMsg(EMPTY_CITY);
			WriteToRsp(response, rspMsg.ToString());
			LOG_INFO(ms_loger, "RSP:{}", rspMsg.ToString());
			return;
		}
		C_T_CITY_CODE_ADDR_ARRAY_T allBean;
		m_mySqlUtil.GetCityCodeByAddr(strProvince, strCity, allBean);

		HttpGetCityCodeRsp rspMsg;
		for (auto& item : allBean)
		{
			rspMsg.m_elemVec.push_back(CityCodeAddrElem_t{ item.m_F_CITY_CODE,item.GetAddress() });
		}
		WriteToRsp(response, rspMsg.ToString());
		LOG_INFO(ms_loger, "RSP:{}", rspMsg.ToString());
		return;
	}
	/**
	 * @brief 初始化URL和函数的对应关系
	 * 
	 */
	void CHttpServer::Init() {
		auto pSelf = shared_from_this();
		
		m_httpServer.resource["/version"]["GET"] = [pSelf, this](std::shared_ptr<HttpServer::Response> response, std::shared_ptr<HttpServer::Request> request) {
			this->Get_Version(response, request);
		};
		m_httpServer.resource["/weather/v1/get_one_day_base_weather"]["GET"] = [pSelf, this](std::shared_ptr<HttpServer::Response> response, std::shared_ptr<HttpServer::Request> request) {
			this->Get_OneDayWeather(response, request);
		};
		m_httpServer.resource["/weather/v1/get_one_week_base_weather"]["GET"] = [pSelf, this](std::shared_ptr<HttpServer::Response> response, std::shared_ptr<HttpServer::Request> request) {
			this->Get_OneWeekWeather(response, request);
		};
		m_httpServer.resource["/weather/v1/get_city_code"]["GET"] = [pSelf, this](std::shared_ptr<HttpServer::Response> response, std::shared_ptr<HttpServer::Request> request) {
			this->Get_CityCode(response, request);
		};

		auto pLoger = ms_loger;
		m_mySqlUtil.SetLogFunc([pLoger](const std::string strMsg)->void {
			LOG_INFO(pLoger, "{} ", strMsg);
		});
	}
}































//#include "client_http.hpp"
//#include "server_http.hpp"
//
//// Added for the json-example
//
//// Added for the default_resource example
//#include <algorithm>
//#include <fstream>
//#include <vector>
//#ifdef HAVE_OPENSSL
//#include "crypto.hpp"
//#endif
//
//using namespace std;
//// Added for the json-example:
//
//using HttpServer = SimpleWeb::Server<SimpleWeb::HTTP>;
//using HttpClient = SimpleWeb::Client<SimpleWeb::HTTP>;
//
//int mainTest() {
//	asio::io_service ioService;
//  // HTTP-server at port 8080 using 1 thread
//  // Unless you do more heavy non-threaded processing in the resources,
//  // 1 thread is usually faster than several threads
//  HttpServer server(ioService);
//  server.config.port = 8080;
//
//  // Add resources using path-regex and method-string, and an anonymous function
//  // POST-example for the path /string, responds the posted string
//  server.resource["^/string$"]["POST"] = [](shared_ptr<HttpServer::Response> response, shared_ptr<HttpServer::Request> request) {
//    // Retrieve string:
//    auto content = request->content.string();
//    // request->content.string() is a convenience function for:
//    // stringstream ss;
//    // ss << request->content.rdbuf();
//    // auto content=ss.str();
//
//    *response << "HTTP/1.1 200 OK\r\nContent-Length: " << content.length() << "\r\n\r\n"
//              << content;
//
//
//    // Alternatively, use one of the convenience functions, for instance:
//    // response->write(content);
//  };
//
//  // POST-example for the path /json, responds firstName+" "+lastName from the posted json
//  // Responds with an appropriate error message if the posted json is not valid, or if firstName or lastName is missing
//  // Example posted json:
//  // {
//  //   "firstName": "John",
//  //   "lastName": "Smith",
//  //   "age": 25
//  // }
//  server.resource["^/json$"]["POST"] = [](shared_ptr<HttpServer::Response> response, shared_ptr<HttpServer::Request> request) {
//    try {
//      //ptree pt;
//      //read_json(request->content, pt);
//
//      //auto name = pt.get<string>("firstName") + " " + pt.get<string>("lastName");
//	  std::string name = "https://www.dennisthink.com";
//      *response << "HTTP/1.1 200 OK\r\n"
//                << "Content-Length: " << name.length() << "\r\n\r\n"
//                << name;
//    }
//    catch(const exception &e) {
//      *response << "HTTP/1.1 400 Bad Request\r\nContent-Length: " << strlen(e.what()) << "\r\n\r\n"
//                << e.what();
//    }
//
//
//    // Alternatively, using a convenience function:
//    // try {
//    //     ptree pt;
//    //     read_json(request->content, pt);
//
//    //     auto name=pt.get<string>("firstName")+" "+pt.get<string>("lastName");
//    //     response->write(name);
//    // }
//    // catch(const exception &e) {
//    //     response->write(SimpleWeb::StatusCode::client_error_bad_request, e.what());
//    // }
//  };
//
//  // GET-example for the path /info
//  // Responds with request-information
//  server.resource["^/info$"]["GET"] = [](shared_ptr<HttpServer::Response> response, shared_ptr<HttpServer::Request> request) {
//    stringstream stream;
//    stream << "<h1>Request from " << request->remote_endpoint_address() << ":" << request->remote_endpoint_port() << "</h1>";
//
//    stream << request->method << " " << request->path << " HTTP/" << request->http_version;
//
//    stream << "<h2>Query Fields</h2>";
//    auto query_fields = request->parse_query_string();
//    for(auto &field : query_fields)
//      stream << field.first << ": " << field.second << "<br>";
//
//    stream << "<h2>Header Fields</h2>";
//    for(auto &field : request->header)
//      stream << field.first << ": " << field.second << "<br>";
//
//    response->write(stream);
//  };
//
//  // GET-example for the path /match/[number], responds with the matched string in path (number)
//  // For instance a request GET /match/123 will receive: 123
//  server.resource["^/match/([0-9]+)$"]["GET"] = [](shared_ptr<HttpServer::Response> response, shared_ptr<HttpServer::Request> request) {
//    response->write(request->path_match[1]);
//  };
//
//  // GET-example simulating heavy work in a separate thread
//  server.resource["^/work$"]["GET"] = [](shared_ptr<HttpServer::Response> response, shared_ptr<HttpServer::Request> /*request*/) {
//    thread work_thread([response] {
//      this_thread::sleep_for(chrono::seconds(5));
//      response->write("Work done");
//    });
//    work_thread.detach();
//  };
//
//  // Default GET-example. If no other matches, this anonymous function will be called.
//  // Will respond with content in the web/-directory, and its subdirectories.
//  // Default file: index.html
//  // Can for instance be used to retrieve an HTML 5 client that uses REST-resources on this server
//  server.default_resource["GET"] = [](shared_ptr<HttpServer::Response> response, shared_ptr<HttpServer::Request> request) {
////    try {
////     /* auto web_root_path = boost::filesystem::canonical("web");
////      auto path = boost::filesystem::canonical(web_root_path / request->path);
////      // Check if path is within web_root_path
////      if(distance(web_root_path.begin(), web_root_path.end()) > distance(path.begin(), path.end()) ||
////         !equal(web_root_path.begin(), web_root_path.end(), path.begin()))
////        throw invalid_argument("path must be within root path");
////      if(boost::filesystem::is_directory(path))
////        path /= "index.html";*/
////
////      SimpleWeb::CaseInsensitiveMultimap header;
////
////      // Uncomment the following line to enable Cache-Control
////      // header.emplace("Cache-Control", "max-age=86400");
////
////#ifdef HAVE_OPENSSL
//////    Uncomment the following lines to enable ETag
//////    {
//////      ifstream ifs(path.string(), ifstream::in | ios::binary);
//////      if(ifs) {
//////        auto hash = SimpleWeb::Crypto::to_hex_string(SimpleWeb::Crypto::md5(ifs));
//////        header.emplace("ETag", "\"" + hash + "\"");
//////        auto it = request->header.find("If-None-Match");
//////        if(it != request->header.end()) {
//////          if(!it->second.empty() && it->second.compare(1, hash.size(), hash) == 0) {
//////            response->write(SimpleWeb::StatusCode::redirection_not_modified, header);
//////            return;
//////          }
//////        }
//////      }
//////      else
//////        throw invalid_argument("could not read file");
//////    }
////#endif
////
////      auto ifs = make_shared<ifstream>();
////      ifs->open(path.string(), ifstream::in | ios::binary | ios::ate);
////
////      if(*ifs) {
////        auto length = ifs->tellg();
////        ifs->seekg(0, ios::beg);
////
////        header.emplace("Content-Length", to_string(length));
////        response->write(header);
////
////        // Trick to define a recursive function within this scope (for example purposes)
////        class FileServer {
////        public:
////          static void read_and_send(const shared_ptr<HttpServer::Response> &response, const shared_ptr<ifstream> &ifs) {
////            // Read and send 128 KB at a time
////            static vector<char> buffer(131072); // Safe when server is running on one thread
////            streamsize read_length;
////            if((read_length = ifs->read(&buffer[0], static_cast<streamsize>(buffer.size())).gcount()) > 0) {
////              response->write(&buffer[0], read_length);
////              if(read_length == static_cast<streamsize>(buffer.size())) {
////                response->send([response, ifs](const SimpleWeb::error_code &ec) {
////                  if(!ec)
////                    read_and_send(response, ifs);
////                  else
////                    cerr << "Connection interrupted" << endl;
////                });
////              }
////            }
////          }
////        };
////        FileServer::read_and_send(response, ifs);
////      }
////      else
////        throw invalid_argument("could not read file");
////    }
////    catch(const exception &e) {
////      response->write(SimpleWeb::StatusCode::client_error_bad_request, "Could not open path " + request->path + ": " + e.what());
////    }
//	  response->write(SimpleWeb::StatusCode::client_error_bad_request, "Could not open path " + request->path + ": ");
//  };
//
//  server.on_error = [](shared_ptr<HttpServer::Request> /*request*/, const SimpleWeb::error_code & /*ec*/) {
//    // Handle errors here
//  };
//
//    // Start server
//    server.start();
// 
//	ioService.run();
//
//	return 0;
//}
