#pragma once
#include <Windows.h>























class NetMsgType
{
public: // �޼��� ������ ��ȣ
	enum MSGTYPE
	{// RQ(��û), RP(����), CM(���), NF(�˸�)
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

