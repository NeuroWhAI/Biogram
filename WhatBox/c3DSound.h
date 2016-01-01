// TODO: ������۸� ������ �Ҹ��� �� 3D��ġ�� �༭ ����ϸ� D3DAudio��ü�� �ڽ��� ���/�����Ѵ�.
#pragma once
#include <d3dx9.h>

class c2DSound;


















///////////////////////////////////////////////////////////////////////////////////////////////////////
// Name : 3D����
// Desc : 2D���带 �����ϰ� D3DAudio���� 3D���带 ����ϱ����� �������̽� ����
///////////////////////////////////////////////////////////////////////////////////////////////////////

class c3DSound
{
public:
	c3DSound();
	~c3DSound();


private:
	c2DSound* m_pSound;


public:
	int SetSound(c2DSound* pSound, D3DXVECTOR3 Pos);
	int SetSound(c2DSound* pSound, const D3DXVECTOR3* pPos);
	
	int Play(D3DXVECTOR3 Pos, bool bLoop);				// �ʱ���ġ ������ ���
	int Play(const D3DXVECTOR3* pPos, bool bLoop);		// �ʱ���ġ ������ ���

	int Pause();
	int Stop();

	int UpdatePos(D3DXVECTOR3 Pos);						// ����Ŀ ��ġ ����
	int UpdatePos(const D3DXVECTOR3* pPos);				// ����Ŀ ��ġ ����


public:
	int Release();
};

