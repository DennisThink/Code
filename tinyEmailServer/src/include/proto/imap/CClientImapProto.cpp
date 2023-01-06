#include "CClientImapProto.h"
#include "CImapProtoCmd.h"
namespace cpp_email
{
    std::string CImapProto::GetSend()
    {
        switch(m_step)
        {
            case IMAP_SEND_VERIFY:
            {
                return "C3 LOGIN dennismi@163.com \"srpPr9MXwp285Su\"\r\n";
            }break;
            default:
            {
                return "";
            }
        }
        return "";
    }

    struct ImapElem
    {
        ImapElem(ImapCode_t cur,ImapCode_t recv,ImapCode_t next)
        {
            curState_ = cur;
            recvState_ = recv;
            nextState_ = next;
        }
        ImapCode_t curState_;
        ImapCode_t recvState_;
        ImapCode_t nextState_;
    };

    ImapElem ArrayImap[]=
    {
        {IMAP_WAIT_VERIFY,IMAP_OK,IMAP_SEND_VERIFY},
    };
    int ARRAY_SIZE_IMAP = sizeof(ArrayImap)/sizeof(ArrayImap[0]);

    ImapCode_t CImapProto::GetNextState(ImapCode_t cur,ImapCode_t recv)
    {
        for(int i = 0 ; i < ARRAY_SIZE_IMAP ; i++)
        {
            if(ArrayImap[i].curState_ == cur &&
               ArrayImap[i].recvState_ == recv)
            {
                return ArrayImap[i].nextState_;
            }
        }
        return IMAP_NO_OP;
    }

    bool CImapProto::OnRecv(const std::string& strRecv)
    {
        CImapProtoCmd curCmd = CImapProtoCmd::FromString(strRecv);
        if(curCmd.GetCode() == IMAP_OK)
        {
            m_step = GetNextState(m_step,curCmd.GetCode());
        } 
        return true;
    }
}