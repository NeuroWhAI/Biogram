#include "cServerSygnMgr.h"

#include "NetMsgType.h"
#include "NetMsgUtil.h"
#include "cBinaryReader.h"
#include "cBinaryWriter.h"
#include "Array.h"
#include "NetDefine.h"

#include "cSygnVal.h"
#include "cMessageSender.h"
#include "cNetMessage.h"































cServerSygnMgr::cServerSygnMgr(cMessageSender* pMsgSender)
	: m_pMsgSender(pMsgSender)
{

}


cServerSygnMgr::~cServerSygnMgr()
{

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int cServerSygnMgr::AddSygnVal(cSygnVal* pSygnVal)
{
	for (UINT i = 0; i<m_pSygnValList.size(); ++i)
	{
		if (m_pSygnValList[i] == nullptr)
		{
			m_pSygnValList[i] = pSygnVal;
			return 1;
		}
	}


	m_pSygnValList.push_back(pSygnVal);


	return 0;
}


int cServerSygnMgr::SetSygnVal(cSygnVal* pSygnVal, int Idx)
{
	while(static_cast<UINT>(Idx) >= m_pSygnValList.size()) m_pSygnValList.push_back(NULL);


	m_pSygnValList[Idx] = pSygnVal;


	return 0;
}


int cServerSygnMgr::RemoveSygnVal(const cSygnVal* pSygnVal)
{
	for(UINT i=0; i<m_pSygnValList.size(); i++)
	{
		if(m_pSygnValList[i] == pSygnVal)
		{
			m_pSygnValList[i] = nullptr;
			break;
		}
	}


	return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int cServerSygnMgr::Recv(const cNetMessage* pMsg, const SOCKADDR_IN* pAdr)
{// [HEAD] [(UINT)쓰레기값]
	if(pMsg->Header->MsgType != NetMsgType::RQ_SygnVal_Info) return -1;


	cBinaryReader br(pMsg);


	/* 버퍼 크기 구함 */
	UINT Size = 0;

	for(UINT i=0; i<m_pSygnValList.size(); i++)
	{
		if(m_pSygnValList[i] == NULL)
			Size += sizeof(BYTE);
		else
			Size += sizeof(BYTE) + sizeof(UINT) + m_pSygnValList[i]->GetByteSize();
	}


	/* 바이트화 */
	cBinaryWriter bw(Size + sizeof(UINT) + sizeof(int));

	// ValType
	bw.Write(br.Read<int>());

	// SygnVal 갯수
	bw.Write(m_pSygnValList.size());

	// 각 SygnVal들
	for(UINT i=0; i<m_pSygnValList.size(); i++)
	{
		if(m_pSygnValList[i] == NULL)
		{// 없음
			bw.Write(NetDefine::NO); // 다음 바이트는 없다고 알림
		}
		else
		{// 있음
			bw.Write(NetDefine::YES); // 다음 바이트가 있다고 알림


			UINT ValSize = m_pSygnValList[i]->GetByteSize();

			
			bw.Write(ValSize); // 바이트 크기


			// 데이터 바이트배열
			BYTE* ValBytes = new BYTE[ValSize];
			m_pSygnValList[i]->GetBytes(ValBytes);

			bw.WriteBytes((char*)ValBytes, ValSize);

			delete[] ValBytes;
		}
	}


	/* 전송 */
	cNetMessage* pSendMsg = NetMsgUtil::MakeMessage(NetMsgType::RP_SygnVal_Info, &bw);
	m_pMsgSender->PushUdpSendMsg(pSendMsg, pAdr);


	return 0;
}

