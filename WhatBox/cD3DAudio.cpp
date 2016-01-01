#include "cD3DAudio.h"

#include "c2DSound.h"
#include "c3DSound.h"

#include "Util.h"
























cD3DAudio::cD3DAudio()
	: m_Pos(0.f, 0.f, 0.f)
	, m_Dir(0.f, 0.f, 1.f)

	, m_UnitLength(1.f)
	, m_MaxDis(256.f)
{

}


cD3DAudio::~cD3DAudio()
{

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////

int cD3DAudio::SetUnitLength(float UnitLength)
{
	if(UnitLength <= 0.f)
		return -1;


	m_UnitLength = UnitLength;


	return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////

int cD3DAudio::Add3DSound(c2DSound* p2DSound, D3DXVECTOR3 Pos)
{
	return Add3DSound(p2DSound, &Pos);
}


int cD3DAudio::Add3DSound(c2DSound* p2DSound, const D3DXVECTOR3* pPos)
{
	if(p2DSound == NULL)
		return -1;


	/* 중복검사 */
	for(UINT i=0; i<m_p2DSound.size(); i++)
	{
		if(m_p2DSound[i] == p2DSound)
		{
			return 1;
		}
	}

	// 목록 추가
	m_p2DSound.push_back(p2DSound);
	m_SndPos.push_back(*pPos);


	// 3D변환
	Convert(p2DSound, pPos);


	return 0;
}


int cD3DAudio::Delete3DSound(const c2DSound* p2DSound)
{
	if(p2DSound == NULL)
		return -1;


	for(UINT i=0; i<m_p2DSound.size(); i++)
	{
		if(m_p2DSound[i] == p2DSound)
		{
			m_p2DSound.erase(m_p2DSound.begin() + i);
			m_SndPos.erase(m_SndPos.begin() + i);


			return 1;
		}
	}


	return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////

int cD3DAudio::SetEarPos(D3DXVECTOR3 Pos)
{
	return SetEarPos(&Pos);
}


int cD3DAudio::SetEarPos(const D3DXVECTOR3* pPos)
{
	m_Pos = *pPos;


	// 등록된 사운드 모두 변환
	for(UINT i=0; i<m_p2DSound.size(); i++)
	{
		Convert(m_p2DSound[i], &m_SndPos[i]);
	}


	return 0;
}



int cD3DAudio::SetEarDir(D3DXVECTOR3 Dir)
{
	return SetEarDir(&Dir);
}


int cD3DAudio::SetEarDir(const D3DXVECTOR3* pDir)
{
	m_Dir = *pDir;
	D3DXVec3Normalize(&m_Dir, &m_Dir); // 단위벡터화


	// 등록된 사운드 모두 변환
	for(UINT i=0; i<m_p2DSound.size(); i++)
	{
		Convert(m_p2DSound[i], &m_SndPos[i]);
	}


	return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int cD3DAudio::SetSoundPos(c2DSound* p2DSound, D3DXVECTOR3 Pos)
{
	return SetSoundPos(p2DSound, &Pos);
}


int cD3DAudio::SetSoundPos(c2DSound* p2DSound, const D3DXVECTOR3* pPos)
{
	for(UINT i=0; i<m_p2DSound.size(); i++)
	{
		if(m_p2DSound[i] == p2DSound)
		{
			m_SndPos[i] = *pPos;			// 위치 갱신
			Convert(p2DSound, pPos);		// 3D변환


			break;
		}
	}


	return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int cD3DAudio::Convert(c2DSound* p2DSound, const D3DXVECTOR3* pSndPos)
{// UpVec는 항상 Y축방향이라고 가정한다. (기술적인 어려움)
	D3DXVECTOR3 Line(*pSndPos - m_Pos); // 스피커의 상대적인 위치계산

	D3DXVECTOR3 LineNor;
	D3DXVec3Normalize(&LineNor, &Line);

	float Distance = D3DXVec3Length(&Line);

	D3DXVECTOR2 Dir(m_Dir.x, m_Dir.z);
	D3DXVec2Normalize(&Dir, &Dir);


	if(Distance < m_MaxDis)
	{// 최대가청거리 안이면
		if(Distance > 0.f)
		{// 거리가 0(완전히 겹침)이 아니면
			float fVol = 0.f;


			// 스피커가 후면에 있는지 판단 (양수: 전면, 음수: 후면)
			D3DXVECTOR2 SndPos1(LineNor.x, LineNor.z);

			D3DXVec2Normalize(&SndPos1, &SndPos1);

			float Dot1 = D3DXVec2Dot(&Dir, &SndPos1);


			fVol = Dot1*10.f; // 전면후면 볼륨차이 적용


			// 거리로 볼륨 설정
			fVol += 106.f - /*6.f*/10.f * Util::flogB(Distance/m_UnitLength, 2.f);
			// 거리가 2배될때마다 6dB씩 줄어든다는 연구결과 적용하지만 게임적인 요소를 위해 비율증가


			// 위아래 볼륨 조정
			D3DXVECTOR3 UpDownSnd(LineNor.x, LineNor.z, LineNor.y);
			float UpDownDot = D3DXVec3Dot(&m_Dir, &UpDownSnd);
			UpDownDot = fabsf(UpDownDot);

			fVol -= UpDownDot*16.f;


			p2DSound->SetVolume(CAST( fVol, long ));						// 볼륨 조정
		}
		else
		{// 스피커와 청취자의 위치가 일치할때는 그냥 최고볼륨
			p2DSound->SetVolume(100L);
		}
	}
	else
	{// 가청거리 밖이면 음소거
		p2DSound->SetVolumeEx(-10000L);
	}


	// Y축은 쓰지않기 때문에 Y축을 제외한 2차원벡터로 재표현
	D3DXVECTOR2 SndPos2(-LineNor.z, LineNor.x);

	D3DXVec2Normalize(&SndPos2, &SndPos2);

	float Dot2 = D3DXVec2Dot(&Dir, &SndPos2);


	p2DSound->SetPan(CAST( pow(Dot2*20.f, 3.f), long ));			// LR볼륨 차이 조정


	return 0;
}

