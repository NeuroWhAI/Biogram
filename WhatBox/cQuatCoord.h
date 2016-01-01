#pragma once
#include "c2DCoord.h"




































///////////////////////////////////////////////////////////////////////////////////////////////////////
// Name : ���ͺ� ��������
// Desc : ��ġ, �ӵ�, ũ��, ����, ���ӵ� ����
///////////////////////////////////////////////////////////////////////////////////////////////////////

class cQuatCoord : public c2DCoord
{
public:
	cQuatCoord();
	virtual ~cQuatCoord();


public:
	// 3���� ��ǥ�� ���ͺ� ��ǥ�� �������� ��
	static void GetQuaterPos(D3DXVECTOR2* pOut, float x, float y, float z);
	// 3���� ��ǥ�� ���ͺ� ��ǥ�� �������� ��
	static void GetQuaterPos(D3DXVECTOR2* pOut, const D3DXVECTOR2* xy, float z);
	// 3���� ��ǥ�� ���ͺ� ��ǥ�� �������� ��
	static void GetQuaterPos(D3DXVECTOR2* pOut, const D3DXVECTOR3* xyz);
	// ȭ�� ��ǥ�� ���ͺ���� 3���� ��ǥ�� �������� ��
	static void GetQuarterPosFromScreenPos(D3DXVECTOR3* pOut, float x, float y);
	// ȭ�� ��ǥ�� ���ͺ���� 3���� ��ǥ�� �������� ��
	static void GetQuarterPosFromScreenPos(D3DXVECTOR3* pOut, const D3DXVECTOR2* pos);
	// ȭ�� ��ǥ�� ���ͺ���� 3���� ��ǥ�� �������� ��
	static void GetQuarterPosFromScreenPos(D3DXVECTOR2* pOut, const D3DXVECTOR2* pos);


protected:
	float m_zPos;
	float m_zSpeed;


private:
	D3DXVECTOR2 m_tempVec;


public:
	virtual float GetZPos() const;
	virtual void SetZPos(float z);
	virtual void AddZPos(float z);

	virtual float GetZSpeed() const;
	virtual void SetZSpeed(float z);
	virtual void AddZSpeed(float z);

	virtual void SetQuatPos(const D3DXVECTOR3* pos);
	virtual void AddQuatPos(const D3DXVECTOR3* pos);

	virtual void SetQuatSpeed(const D3DXVECTOR3* speed);
	virtual void AddQuatSpeed(const D3DXVECTOR3* speed);


public:
	virtual const D3DXMATRIX* Matrix() override;


public:
	virtual void GetQuaterPos(D3DXVECTOR2* pOut) const;
	virtual const D3DXVECTOR2* GetQuaterPos();
};

