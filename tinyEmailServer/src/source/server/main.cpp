#include "CEmailServer.h"
#include <iostream>
int main(int argc,char* argv[])
{
    std::cout<<argc<<argv[0]<<std::endl;
    using namespace cpp_email;
    CEmailServer server;
    server.Start();
    return 0;
}