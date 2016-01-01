#pragma once
#include <d3dx9.h>
#include <vector>

class c2DSound;





















///////////////////////////////////////////////////////////////////////////////////////////////////////
// Name : 3D����� �ͼ�
// Desc : 3D�����κ��� ���� ������ ���� 2D���带 3D����� ������Ų��. û������ ��ġ ��������
///////////////////////////////////////////////////////////////////////////////////////////////////////

class cD3DAudio
{
public:
	cD3DAudio();
	~cD3DAudio();


private:
	float m_UnitLength;		// ��������(Ŭ���� �پ��� ������ ���� �۾���)
	float m_MaxDis;			// ���� �� �ִ� �ִ�Ÿ�


private:
	D3DXVECTOR3 m_Pos;		// ������� ��ġ
	D3DXVECTOR3 m_Dir;		// ������� ����

	std::vector<c2DSound*> m_p2DSound;
	std::vector<D3DXVECTOR3> m_SndPos;


public:
	int SetUnitLength(float UnitLength);


public:
	int Add3DSound(c2DSound* p2DSound, D3DXVECTOR3 Pos);
	int Add3DSound(c2DSound* p2DSound, const D3DXVECTOR3* pPos);
	int Delete3DSound(const c2DSound* p2DSound);


public:
	int SetEarPos(D3DXVECTOR3 Pos);
	int SetEarPos(const D3DXVECTOR3* pPos);

	int SetEarDir(D3DXVECTOR3 Dir);
	int SetEarDir(const D3DXVECTOR3* pDir);


public:
	int SetSoundPos(c2DSound* p2DSound, D3DXVECTOR3 Pos);
	int SetSoundPos(c2DSound* p2DSound, const D3DXVECTOR3* pPos);


private:
	int Convert(c2DSound* p2DSound, const D3DXVECTOR3* pSndPos);
};

