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
#include "WXCommonMsg.h"
#include "sha1.hpp"
#include "base64.h"
#include <time.h>
namespace ClientCore
{
	const static std::string strTOKEN = "dennismi1024gmail";
	std::shared_ptr<spdlog::logger> CHttpServer::ms_loger;
	/**
	 * @brief 获取服务程序的版本
	 * 
	 * @param response 
	 * @param request 
	 */
	void CHttpServer::Get_Version(std::shared_ptr<HttpServer::Response> response, std::shared_ptr<HttpServer::Request> request) {
		std::string strSignature = GetHttpParamValue(request, "signature");
		std::string strTimeStamp = GetHttpParamValue(request, "timestamp");
		std::string strNonce = GetHttpParamValue(request, "nonce");
		std::string strEchoStr = GetHttpParamValue(request, "echostr");
		{
			std::vector<std::string> strArray;
			strArray.push_back(strTimeStamp);
			strArray.push_back(strNonce);
			strArray.push_back(strTOKEN);
			std::sort(strArray.begin(), strArray.end());

			std::string strSHA1Src = strArray[0] + strArray[1] + strArray[2];

			char szSHA1[32] = { 0 };
			SHA1 util;
			util.update(strSHA1Src);
			std::string strSha1 = util.final();
			if (strSha1 == strSignature)
			{
				LOG_INFO(ms_loger, "My Base64:{} Org Base 64:{}", strSha1, strSignature);
			}
			else
			{
				LOG_ERR(ms_loger, "My Base64:{} Org Base 64:{}", strSha1, strSignature);
			}

		}
		*response << "HTTP/1.1 200 OK\r\nContent-Length: " << strEchoStr.length() << "\r\n\r\n"
			<< strEchoStr;
	}

	std::string CHttpServer::HandlePost(const std::string& strReq)
	{
		std::string strRsp;
		WXMsgType type = ParseMsgType(strReq);
		switch (type)
		{
		case WXMsgType::UserSendTxt:
		{
			UserSendTxtMsg reqMsg;
			if (reqMsg.FromString(strReq))
			{
				UserRecvTxtMsg rspMsg;
				rspMsg.m_strContent = "Recv Txt Message";
				rspMsg.m_strFromUserName = reqMsg.m_strToUserName;
				rspMsg.m_strToUserName = reqMsg.m_strFromUserName;
				rspMsg.m_strCreateTime = std::to_string(time(nullptr));
				strRsp = rspMsg.ToString();
			}
		}break;
		case WXMsgType::UserSendImage:
		{
			UserSendImageMsg reqMsg;
			if (reqMsg.FromString(strReq))
			{
				UserRecvTxtMsg rspMsg;
				rspMsg.m_strContent = "Image  " + reqMsg.m_strPicUrl;
				rspMsg.m_strFromUserName = reqMsg.m_strToUserName;
				rspMsg.m_strToUserName = reqMsg.m_strFromUserName;
				rspMsg.m_strCreateTime = std::to_string(time(nullptr));
				strRsp = rspMsg.ToString();
			}
		}break;
		case WXMsgType::UserSendVoice:
		{
			UserSendVoiceMsg reqMsg;
			if (reqMsg.FromString(strReq))
			{
				UserRecvTxtMsg rspMsg;
				rspMsg.m_strContent = "Voice " + reqMsg.m_strMediaId;
				rspMsg.m_strFromUserName = reqMsg.m_strToUserName;
				rspMsg.m_strToUserName = reqMsg.m_strFromUserName;
				rspMsg.m_strCreateTime = std::to_string(time(nullptr));
				strRsp = rspMsg.ToString();
			}
		}break;
		case WXMsgType::UserSendVideo:
		{
			UserSendVideoMsg reqMsg;
			if (reqMsg.FromString(strReq))
			{
				UserRecvTxtMsg rspMsg;
				rspMsg.m_strContent = "Video " + reqMsg.m_strMediaId;
				rspMsg.m_strFromUserName = reqMsg.m_strToUserName;
				rspMsg.m_strToUserName = reqMsg.m_strFromUserName;
				rspMsg.m_strCreateTime = std::to_string(time(nullptr));
				strRsp = rspMsg.ToString();
			}
		}break;
		case WXMsgType::UserSendShortVideo:
		{
			UserSendShortVideoMsg reqMsg;
			if (reqMsg.FromString(strReq))
			{
				UserRecvTxtMsg rspMsg;
				rspMsg.m_strContent = "Short Video " + reqMsg.m_strMediaId;
				rspMsg.m_strFromUserName = reqMsg.m_strToUserName;
				rspMsg.m_strToUserName = reqMsg.m_strFromUserName;
				rspMsg.m_strCreateTime = std::to_string(time(nullptr));
				strRsp = rspMsg.ToString();
			}
		}break;
		case WXMsgType::UserSendLocation:
		{
			UserSendLocationMsg reqMsg;
			if (reqMsg.FromString(strReq))
			{
				UserRecvTxtMsg rspMsg;
				rspMsg.m_strContent = "Location " + reqMsg.m_strLabel;
				rspMsg.m_strFromUserName = reqMsg.m_strToUserName;
				rspMsg.m_strToUserName = reqMsg.m_strFromUserName;
				rspMsg.m_strCreateTime = std::to_string(time(nullptr));
				strRsp = rspMsg.ToString();
			}
		}break;
		case WXMsgType::UserSendLink:
		{
			UserSendLinkMsg reqMsg;
			if (reqMsg.FromString(strReq))
			{
				UserRecvTxtMsg rspMsg;
				rspMsg.m_strContent = "Link " + reqMsg.m_strTitle;
				rspMsg.m_strFromUserName = reqMsg.m_strToUserName;
				rspMsg.m_strToUserName = reqMsg.m_strFromUserName;
				rspMsg.m_strCreateTime = std::to_string(time(nullptr));
				strRsp = rspMsg.ToString();
			}
		}break;
		default:
		{
		}
		}
		return strRsp;
	}

	//在此处进行消息的回复
	void CHttpServer::Post_Chat(std::shared_ptr<HttpServer::Response> response, std::shared_ptr<HttpServer::Request> request) {
		std::string strPost = request->content.string();
		LOG_INFO(ms_loger, "Post:{} [{} {}]", strPost, __FILENAME__, __LINE__);
		std::string	strRsp = HandlePost(strPost);
		*response << "HTTP/1.1 200 OK\r\nContent-Length: " << strRsp.length() << "\r\n\r\n"
		<< strRsp;
	}

	/**
	 * @brief 从HTTP的Get请求中，获取UserId参数
	 * 
	 * @param request HTTP的请求
	 * @return std::string 用户ID
	 */
	std::string CHttpServer::GetHttpParamUserId(std::shared_ptr<HttpServer::Request> request)
	{
		auto paramMap = request->parse_query_string();
		if (0 == paramMap.count("UserId"))
		{
			return "";
		}
		else
		{
			return paramMap.equal_range("UserId").first->second;
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


	std::string CHttpServer::GetHeaderValue(std::shared_ptr<HttpServer::Request> request,const std::string strKey)
	{
		auto paramMap = request->header;
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
	 * @brief 初始化URL和函数的对应关系
	 * 
	 */
	void CHttpServer::Init() {
		m_httpServer.config.port = 9000;
		auto pSelf = shared_from_this();
		
		m_httpServer.resource["/version"]["GET"] = [pSelf, this](std::shared_ptr<HttpServer::Response> response, std::shared_ptr<HttpServer::Request> request) {
			this->Get_Version(response, request);
		};

		m_httpServer.resource["/version"]["POST"] = [pSelf, this](std::shared_ptr<HttpServer::Response> response, std::shared_ptr<HttpServer::Request> request) {
			this->Post_Chat(response, request);
		};
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
