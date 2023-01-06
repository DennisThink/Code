#ifndef _CPP_EMAIL_EMAIL_PROTO_INTERFACE_H_
#define _CPP_EMAIL_EMAIL_PROTO_INTERFACE_H_
#include <string>
#include <memory>
namespace cpp_email
{
    class CEmailProtoInterface
    {
    public:
        virtual bool OnRecv(const std::string& recvData)=0;
        virtual std::string  GetSend()=0;
        virtual bool IsFinish() = 0;
    };
    using ProtoHandlerPtr_t = std::shared_ptr<CEmailProtoInterface>;
}
#endif