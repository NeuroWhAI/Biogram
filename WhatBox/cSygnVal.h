#pragma once
#include <Windows.h>



























///////////////////////////////////////////////////////////////////////////////////////////////////////
// Name : ��Ʈ��ũ ����ȭ����
// Desc : �� Ŭ������ ����ؼ� �����ϸ� cSygnMgr�� ����� �� �ֽ��ϴ�
///////////////////////////////////////////////////////////////////////////////////////////////////////

class cSygnVal
{
public:
	cSygnVal();
	virtual ~cSygnVal();


public:
	// �ڽ��� ������ ����Ʈȭ
	virtual int GetBytes(BYTE* pOut) = 0;

	// ����Ʈ�迭�� ũ��
	virtual UINT GetByteSize() const = 0; // ���� : ���ڿ��� ���ڰ��� + sizeof(int)��. �����ڵ��� ��� ���ڰ���*2 + sizeof(int)��.

	// ����Ʈ�迭�� �ڽ��� ������ ����
	virtual int SetBytes(const BYTE* Bytes) = 0;
};

