#pragma once
#include <Windows.h>























class NetMsgType
{
public: // 메세지 종류별 번호
	enum MSGTYPE
	{// RQ(요청), RP(응답), CM(명령), NF(알림)
		RQ_Test,
		RP_Test,

		RQ_SygnVal_Info,
		RP_SygnVal_Info,

		RQ_LoginUser,
		RP_LoginUser,

		RQ_RegisterUser,
		RP_RegisterUser,

		RQ_ChatMsg,
		RP_ChatMsg,

		NF_PushMsg,

		RQ_FileSend,
		RP_FileSend,

		NF_FileSendData,
		RP_FileSendData,

		NF_FileSendEnd,
		RP_FileSendEnd,

	};
};

