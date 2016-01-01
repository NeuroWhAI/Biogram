#include "cClientSygnMgr.h"

#include "NetMsgType.h"
#include "NetMsgUtil.h"
#include "cBinaryReader.h"
#include "cBinaryWriter.h"
#include "Array.h"
#include "NetDefine.h"

#include "cSygnVal.h"
#include "cMessageSender.h"
#include "cNetMessage.h"































cClientSygnMgr::cClientSygnMgr(cMessageSender* pMsgSender)
	: m_pMsgSender(pMsgSender)

	, m_prevTime(timeGetTime())
{

}


cClientSygnMgr::~cClientSygnMgr()
{

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int cClientSygnMgr::AddSygnVal(cSygnVal* pSygnVal)
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


int cClientSygnMgr::SetSygnVal(cSygnVal* pSygnVal, int Idx)
{
	while(static_cast<UINT>(Idx) >= m_pSygnValList.size()) m_pSygnValList.push_back(NULL);


	m_pSygnValList[Idx] = pSygnVal;


	return 0;
}


int cClientSygnMgr::RemoveSygnVal(const cSygnVal* pSygnVal)
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


int cClientSygnMgr::RemoveSygnVal(int Idx)
{
	if(static_cast<unsigned int>(Idx) < m_pSygnValList.size())
	{
		m_pSygnValList[Idx] = nullptr;
	}


	return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int cClientSygnMgr::Update(int ValType)
{
	if(timeGetTime() - m_prevTime > 14)
	{
		cBinaryWriter br(sizeof(ValType));

		br.Write(ValType);


		cNetMessage* pMsg = NetMsgUtil::MakeMessage(NetMsgType::RQ_SygnVal_Info, &br);

		m_pMsgSender->PushSendMsg(pMsg);


		m_prevTime = timeGetTime();
	}


	return 0;
}


int cClientSygnMgr::Recv(const cNetMessage* pMsg, std::vector<int>* pCreateList, std::vector<int>* pDeleteList)
{// [HEAD] [갯수, 바이트배열(존재여부, 데이터크기, 데이터)...]
	if(pMsg->Header->MsgType != NetMsgType::RP_SygnVal_Info) return -1;


	cBinaryReader br(pMsg);

	// ValType
	int valType = br.Read<int>();

	// 갯수
	UINT Count = br.Read<UINT>();

	// SygnVal들
	for(UINT i=0; i<Count; i++)
	{
		BYTE bNotNull = br.Read<BYTE>(); // Null이 아닌지 여부값

		if(bNotNull == NetDefine::NO)
		{// 없음 NULL임
			pDeleteList->push_back(i);
		}
		else
		{// 있음
			UINT ByteSize = br.Read<UINT>(); // 데이터크기


			BYTE* Bytes = new BYTE[ByteSize]; // 바이트배열 생성

			br.ReadBytes((char*)Bytes, ByteSize); // 데이터 읽기


			if(i >= m_pSygnValList.size()  ||  m_pSygnValList[i] == NULL)
			{// 범위가 초과이거나 없으면
				pCreateList->push_back(i); // 생성목록에 인덱스 추가
			}
			else
			{
				m_pSygnValList[i]->SetBytes(Bytes); // 동기화
			}


			delete[] Bytes;
		}
	}


	return 0;
}

