#include <iostream>
#include "CEmailClient.h"

log_ptr_t g_console=nullptr;
void InitLog()
{
    g_console = spdlog::stdout_color_mt("email_client");
}
void Email_163_test(asio::io_context& ioService)
{
    using namespace cpp_email;
    auto email = std::make_shared<CEmailClient>(ioService,g_console);
}
int main(int argc,char * argv[])
{   
    std::cout<<argc<<argv[0]<<std::endl;
    asio::io_context service;
    InitLog();
    auto client = std::make_shared<cpp_email::CEmailClient>(service,g_console);
    client->Start();
    service.run();
    std::cout<<"Hello World"<<std::endl;
    return 0;
}