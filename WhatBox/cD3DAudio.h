#pragma once
#include <d3dx9.h>
#include <vector>

class c2DSound;





















///////////////////////////////////////////////////////////////////////////////////////////////////////
// Name : 3D오디오 믹서
// Desc : 3D사운드들로부터 얻어온 정보를 토대로 2D사운드를 3D사운드로 변형시킨다. 청취자의 위치 지정가능
///////////////////////////////////////////////////////////////////////////////////////////////////////

class cD3DAudio
{
public:
	cD3DAudio();
	~cD3DAudio();


private:
	float m_UnitLength;		// 단위길이(클수록 줄어드는 진폭의 양이 작아짐)
	float m_MaxDis;			// 들을 수 있는 최대거리


private:
	D3DXVECTOR3 m_Pos;		// 듣는이의 위치
	D3DXVECTOR3 m_Dir;		// 듣는이의 방향

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

