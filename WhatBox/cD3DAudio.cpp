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


	/* �ߺ��˻� */
	for(UINT i=0; i<m_p2DSound.size(); i++)
	{
		if(m_p2DSound[i] == p2DSound)
		{
			return 1;
		}
	}

	// ��� �߰�
	m_p2DSound.push_back(p2DSound);
	m_SndPos.push_back(*pPos);


	// 3D��ȯ
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


	// ��ϵ� ���� ��� ��ȯ
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
	D3DXVec3Normalize(&m_Dir, &m_Dir); // ��������ȭ


	// ��ϵ� ���� ��� ��ȯ
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
			m_SndPos[i] = *pPos;			// ��ġ ����
			Convert(p2DSound, pPos);		// 3D��ȯ


			break;
		}
	}


	return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int cD3DAudio::Convert(c2DSound* p2DSound, const D3DXVECTOR3* pSndPos)
{// UpVec�� �׻� Y������̶�� �����Ѵ�. (������� �����)
	D3DXVECTOR3 Line(*pSndPos - m_Pos); // ����Ŀ�� ������� ��ġ���

	D3DXVECTOR3 LineNor;
	D3DXVec3Normalize(&LineNor, &Line);

	float Distance = D3DXVec3Length(&Line);

	D3DXVECTOR2 Dir(m_Dir.x, m_Dir.z);
	D3DXVec2Normalize(&Dir, &Dir);


	if(Distance < m_MaxDis)
	{// �ִ밡û�Ÿ� ���̸�
		if(Distance > 0.f)
		{// �Ÿ��� 0(������ ��ħ)�� �ƴϸ�
			float fVol = 0.f;


			// ����Ŀ�� �ĸ鿡 �ִ��� �Ǵ� (���: ����, ����: �ĸ�)
			D3DXVECTOR2 SndPos1(LineNor.x, LineNor.z);

			D3DXVec2Normalize(&SndPos1, &SndPos1);

			float Dot1 = D3DXVec2Dot(&Dir, &SndPos1);


			fVol = Dot1*10.f; // �����ĸ� �������� ����


			// �Ÿ��� ���� ����
			fVol += 106.f - /*6.f*/10.f * Util::flogB(Distance/m_UnitLength, 2.f);
			// �Ÿ��� 2��ɶ����� 6dB�� �پ��ٴ� ������� ���������� �������� ��Ҹ� ���� ��������


			// ���Ʒ� ���� ����
			D3DXVECTOR3 UpDownSnd(LineNor.x, LineNor.z, LineNor.y);
			float UpDownDot = D3DXVec3Dot(&m_Dir, &UpDownSnd);
			UpDownDot = fabsf(UpDownDot);

			fVol -= UpDownDot*16.f;


			p2DSound->SetVolume(CAST( fVol, long ));						// ���� ����
		}
		else
		{// ����Ŀ�� û������ ��ġ�� ��ġ�Ҷ��� �׳� �ְ���
			p2DSound->SetVolume(100L);
		}
	}
	else
	{// ��û�Ÿ� ���̸� ���Ұ�
		p2DSound->SetVolumeEx(-10000L);
	}


	// Y���� �����ʱ� ������ Y���� ������ 2�������ͷ� ��ǥ��
	D3DXVECTOR2 SndPos2(-LineNor.z, LineNor.x);

	D3DXVec2Normalize(&SndPos2, &SndPos2);

	float Dot2 = D3DXVec2Dot(&Dir, &SndPos2);


	p2DSound->SetPan(CAST( pow(Dot2*20.f, 3.f), long ));			// LR���� ���� ����


	return 0;
}

