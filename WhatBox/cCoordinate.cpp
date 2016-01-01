#include "cCoordinate.h"

#include "cLine.h"
#include "Util.h"






















cCoordinate::cCoordinate()
	: m_pLine(NULL)
	, m_nLine2(0)
{

}


cCoordinate::~cCoordinate()
{
	Release();
}

/*---------------------------------------------------------------------------------------*/

int cCoordinate::Create(float Size)
{
	m_pLine = new cLine[3];

	m_pLine[X].Create(D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(Size, 0, 0), 0xffff0000);
	m_pLine[Y].Create(D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, Size, 0), 0xff00ff00);
	m_pLine[Z].Create(D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, 0, Size), 0xff0000ff);


	m_nLine2 = static_cast<int>(floorf(Size));

	for(int i=0; i<3; i++)
	{
		m_pLine2[i] = new cLine[m_nLine2];
	}

	for(int i=0; i<m_nLine2; i++)
	{
		m_pLine2[X][i].Create(D3DXVECTOR3((float)(i+1), 0, 0), D3DXVECTOR3((float)(i+1), 0, +0.1f)
			, 0xffffffff);
		m_pLine2[Y][i].Create(D3DXVECTOR3(0, (float)(i+1), 0), D3DXVECTOR3(+0.1f, (float)(i+1), 0)
			, 0xffffffff);
		m_pLine2[Z][i].Create(D3DXVECTOR3(0, 0, (float)(i+1)), D3DXVECTOR3(+0.1f, 0, (float)(i+1))
			, 0xffffffff);
	}


	return 0;
}


int cCoordinate::Release()
{
	for(int i=0; i<3; i++)
	{
		m_pLine[i].Release();

		for(int j=0; j<m_nLine2; j++)
			m_pLine2[i][j].Release();
		SAFE_DELETE_ARR(m_pLine2[i]);
	}

	SAFE_DELETE_ARR(m_pLine);


	return 0;
}


int cCoordinate::Draw()
{
	for(int i=0; i<3; i++)
	{
		m_pLine[i].Draw();

		for(int j=0; j<m_nLine2; j++)
			m_pLine2[i][j].Draw();
	}


	return 0;
}

