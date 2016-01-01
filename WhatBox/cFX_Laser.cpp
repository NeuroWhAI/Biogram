#include "cFX_Laser.h"

#include "cCore.h"





































cFX_Laser::cFX_Laser(DWORD color,
					 const D3DXVECTOR2* dir,
					 int count,
					 float targetLength, float beginLength, float lengthSpeed,
					 float targetSize, float beginSize, float sizeSpeed,
					 float sizeAccelSpeed, float lengthAccelSpeed)
					 : cFX()

					 , m_color(color)
					 , m_dir(*dir)
					 , m_count(count)
					 , m_targetLength(targetLength)
					 , m_lengthSpeed(lengthSpeed)
					 , m_targetSize(targetSize)
					 , m_sizeSpeed(sizeSpeed)
					 , m_sizeAccelSpeed(sizeAccelSpeed)
					 , m_lengthAccelSpeed(lengthAccelSpeed)

					 , m_currSize(beginSize)
{
	D3DXVec2Normalize(&m_dir, &m_dir);
	m_currPos = m_dir*beginLength;


	m_sequencer.AddFunction(LAMBDA_FUNC(Seq_IsEnd), 0);


	m_sequencer.SetCurrFuncNum(0);
}


cFX_Laser::cFX_Laser(cTexture* pTx, DWORD color,
					 const D3DXVECTOR2* dir,
					 int count,
					 float targetLength, float beginLength, float lengthSpeed,
					 float targetSize, float beginSize, float sizeSpeed,
					 float sizeAccelSpeed, float lengthAccelSpeed)
					 : cFX(pTx)

					 , m_color(color)
					 , m_dir(*dir)
					 , m_count(count)
					 , m_targetLength(targetLength)
					 , m_lengthSpeed(lengthSpeed)
					 , m_targetSize(targetSize)
					 , m_sizeSpeed(sizeSpeed)
					 , m_sizeAccelSpeed(sizeAccelSpeed)
					 , m_lengthAccelSpeed(lengthAccelSpeed)

					 , m_currSize(beginSize)
{
	D3DXVec2Normalize(&m_dir, &m_dir);
	m_currPos = m_dir*beginLength;


	m_sequencer.AddFunction(LAMBDA_FUNC(Seq_IsEnd), 0);


	m_sequencer.SetCurrFuncNum(0);
}


cFX_Laser::~cFX_Laser()
{
	
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////

int cFX_Laser::OnUpdate()
{
	m_currPos += m_dir*VFR(m_lengthSpeed);
	m_lengthSpeed += VFR(m_lengthAccelSpeed);

	if((m_lengthSpeed > 0.f  &&  D3DXVec2Length(&m_currPos) > m_targetLength)
		||
		(m_lengthSpeed < 0.f  &&  D3DXVec2Length(&m_currPos) < m_targetLength))
	{
		m_currPos = m_dir*m_targetLength;
	}


	m_currSize += VFR(m_sizeSpeed);
	m_sizeSpeed += VFR(m_sizeAccelSpeed);

	if((m_sizeSpeed > 0.f  &&  m_currSize > m_targetSize)
		||
		(m_sizeSpeed < 0.f  &&  m_currSize < m_targetSize))
	{
		m_currSize = m_targetSize;
	}


	return 0;
}


int cFX_Laser::OnRender()
{
	if(m_pTx == nullptr)
	{
		for(int i=m_count; i>=1; --i)
		{
			float scale = CAST(i, float)/CAST(m_count, float);

			int a = CAST(scale * CAST((m_color & 0xff000000) >> 24, int), int);
			int r = CAST(scale * CAST((m_color & 0x00ff0000) >> 16, int), int);
			int g = CAST(scale * CAST((m_color & 0x0000ff00) >> 8, int), int);
			int b = CAST(scale * CAST((m_color & 0x000000ff), int), int);

			D3DXVECTOR2 endPos = m_Pos+m_currPos;
			cCore::Resource.Line.Render(&m_Pos, &endPos, D3DCOLOR_ARGB(a, r, g, b), scale*m_currSize);
		}
	}
	else
	{
		for(int i=m_count; i>=1; --i)
		{
			float scale = CAST(i, float)/CAST(m_count, float);

			int a = CAST(scale * CAST((m_color & 0xff000000) >> 24, int), int);
			int r = CAST(scale * CAST((m_color & 0x00ff0000) >> 16, int), int);
			int g = CAST(scale * CAST((m_color & 0x0000ff00) >> 8, int), int);
			int b = CAST(scale * CAST((m_color & 0x000000ff), int), int);

			D3DXVECTOR2 pos = m_Pos+m_currPos/2.f;
			D3DXVECTOR2 zeroPos(0.f, 0.f);
			float angle = cCore::ShapeMath.GetAngle(&m_dir, &zeroPos);
			D3DXVECTOR2 imgScale(m_currSize/m_pTx->Width(), D3DXVec2Length(&m_currPos)/m_pTx->Height());

			cCore::Sprite.SetColor(D3DCOLOR_ARGB(a, r, g, b));
			cCore::Sprite.RenderTextureCenter(m_pTx, pos, angle, imgScale);
		}
	}


	return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////

int cFX_Laser::Seq_IsEnd()
{
	if(((m_lengthSpeed > 0.f  &&  D3DXVec2Length(&m_currPos)+1.f >= m_targetLength)
		||
		(m_lengthSpeed < 0.f  &&  (D3DXVec2Length(&m_currPos)-1.f <= m_targetLength  ||  D3DXVec2Length(&m_currPos)-1.f <= 0.f)))
		&&
		((m_sizeSpeed > 0.f  &&  m_currSize >= m_targetSize)
		||
		(m_sizeSpeed < 0.f  &&  (m_currSize <= m_targetSize  ||  m_currSize <= 0.f))))
		return FUNCRESULT_End;


	return 0;
}

