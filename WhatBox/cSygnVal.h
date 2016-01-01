#pragma once
#include <Windows.h>



























///////////////////////////////////////////////////////////////////////////////////////////////////////
// Name : 네트워크 동기화지원
// Desc : 이 클래스를 상속해서 구현하면 cSygnMgr에 등록할 수 있습니다
///////////////////////////////////////////////////////////////////////////////////////////////////////

class cSygnVal
{
public:
	cSygnVal();
	virtual ~cSygnVal();


public:
	// 자신의 정보를 바이트화
	virtual int GetBytes(BYTE* pOut) = 0;

	// 바이트배열의 크기
	virtual UINT GetByteSize() const = 0; // 주의 : 문자열은 문자갯수 + sizeof(int)임. 유니코드일 경우 문자갯수*2 + sizeof(int)임.

	// 바이트배열로 자신의 정보를 갱신
	virtual int SetBytes(const BYTE* Bytes) = 0;
};

