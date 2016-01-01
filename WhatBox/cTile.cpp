#include "cTile.h"

#include "cCore.h"

#include "cShp_Rectangle.h"
#include "c2DCoord.h"





























cTile::cTile(float X, float Y, float Size)
	: m_pRect(new cShp_Rectangle())
	, m_Size(Size)
{
	for(int i=0; i<8; i++)
		m_pNode[i] = NULL;


	m_pRect->left = X;
	m_pRect->top = Y;
	m_pRect->right = m_pRect->left + Size;
	m_pRect->bottom = m_pRect->top + Size; // 정사각형
}


cTile::~cTile()
{
	SAFE_DELETE(m_pRect);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////

/* // 이렇게 사용해야 합니다.
for(UINT i=0; i<TileList.size(); i++)
	TileList[i]->UpdateOutCheck();
for(UINT i=0; i<TileList.size(); i++)
	TileList[i]->Update();
*/


int cTile::UpdateOutCheck() // Update()보다 먼저 호출되어야 합니다.
{// NOTE: 여기서 유닛들의 Update를 하지말것! (CheckOut를 거치고나서 Update를 못하는 유닛이 발생할 수 있음)
	// 타일 밖으로 나간거 처리
	CheckOut();


	return 0;
}


int cTile::Update()
{// NOTE: 유닛들의 Update 진행
	


	return OnUpdate();
}


int cTile::Render()
{
	


	return OnRender();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////

int cTile::OnUpdate()
{



	return 0;
}


int cTile::OnRender()
{



	return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////

UINT cTile::ObjCount() const
{
	return m_pObjList.size();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////

D3DXVECTOR2 cTile::GetPos() const
{
	return D3DXVECTOR2(m_pRect->left, m_pRect->top);
}


int cTile::AddPos(float X, float Y)
{
	m_pRect->left += X;
	m_pRect->top += Y;
	m_pRect->right += X;
	m_pRect->bottom += Y;


	/* 물체 이동 */
	for(UINT i=0; i<m_pObjList.size(); i++)
	{
		m_pObjList[i]->AddPos(X, Y);
	}


	return 0;
}


float cTile::GetSize() const
{
	return m_Size;
}


const cShp_Rectangle* cTile::GetRect() const
{
	return m_pRect;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////

int cTile::SetNode(cTile* pTile, int Idx)
{
	m_pNode[Idx] = pTile;


	return 0;
}


cTile* cTile::GetNode(int Idx)
{
	return m_pNode[Idx];
}

////////////////////////////////////////////////////////////////////////////////////////////////////////

UINT cTile::AddObj(c2DCoord* pObj)
{
	if(IndexOf(pObj) < 0) // 중복이 아니면
	{
		UINT Idx = m_pObjList.size();


		m_pObjList.push_back(pObj);


		OnAddObj(pObj, Idx);


		return Idx;
	}


	return 0;
}


int cTile::RemoveObj(const c2DCoord* pObj)
{
	int Idx = IndexOf(pObj);


	if(Idx >= 0)
	{
		OnRemoveObj(pObj, Idx);


		m_pObjList.erase(m_pObjList.begin() + Idx);
	}


	return 0;
}


std::vector<c2DCoord*>* cTile::GetObjList()
{
	return &m_pObjList;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////

int cTile::IndexOf(const c2DCoord* pObj) const
{
	for(UINT i=0; i<m_pObjList.size(); i++)
	{
		if(m_pObjList[i] == pObj)
			return CAST(i, int);
	}


	return -1;
}


UINT cTile::CheckOutIdx(const D3DXVECTOR2* Pos)
{
	UINT Idx = 1234;

	if(Pos->x < m_pRect->left)
	{
		if(Pos->y < m_pRect->top)
		{// 0
			Idx = 0;
		}
		else if(Pos->y >= m_pRect->bottom)
		{// 6
			Idx = 6;
		}
		else
		{// 7
			Idx = 7;
		}
	}
	else if(Pos->x >= m_pRect->right)
	{
		if(Pos->y < m_pRect->top)
		{// 2
			Idx = 2;
		}
		else if(Pos->y >= m_pRect->bottom)
		{// 4
			Idx = 4;
		}
		else
		{// 3
			Idx = 3;
		}
	}
	else
	{
		if(Pos->y < m_pRect->top)
		{// 1
			Idx = 1;
		}
		else if(Pos->y >= m_pRect->bottom)
		{// 5
			Idx = 5;
		}
	}


	return Idx;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////

int cTile::CheckOut()
{
	/* 기본단위 확인 */
	for(UINT i=0; i<m_pObjList.size();)
	{
		const D3DXVECTOR2* Pos = m_pObjList[i]->Pos();
		UINT Idx = CheckOutIdx(Pos);


		if(Idx < 8)
		{
			if(m_pNode[Idx] == NULL) // 더이상 갈 수 없음
			{
				D3DXVECTOR2 Speed(*m_pObjList[i]->Speed());
				GetMirrorSpeed(Pos, &Speed);

				m_pObjList[i]->SetSpeed(&Speed);

				
				if(Pos->x < m_pRect->left)
					m_pObjList[i]->SetXPos(m_pRect->left);
				else if(Pos->x >= m_pRect->right)
					m_pObjList[i]->SetXPos(m_pRect->right - 1.f);

				if(Pos->y < m_pRect->top)
					m_pObjList[i]->SetYPos(m_pRect->top);
				else if(Pos->y >= m_pRect->bottom)
					m_pObjList[i]->SetYPos(m_pRect->bottom - 1.f);
			}
			else // 노드로 이동
			{
				UINT ListIdx = m_pNode[Idx]->AddObj(m_pObjList[i]);

				OnRemoveObj(m_pObjList[i], i);

				m_pObjList.erase(m_pObjList.begin() + i);

				continue; // i++ 안함
			}
		}


		i++;
	}


	return 0;
}


void cTile::GetMirrorSpeed(const D3DXVECTOR2* Pos, D3DXVECTOR2* Speed)
{
	if(Pos->x < m_pRect->left)
		Speed->x = abs(Speed->x);
	else if(Pos->x >= m_pRect->right)
		Speed->x = -abs(Speed->x);

	if(Pos->y < m_pRect->top)
		Speed->y = abs(Speed->y);
	else if(Pos->y >= m_pRect->bottom)
		Speed->y = -abs(Speed->y);
}


UINT cTile::ObjCountFromNode()
{
	UINT Count = m_pObjList.size();

	for(int i=0; i<8; i++)
	{
		if(m_pNode[i] != NULL)
		{
			Count += m_pNode[i]->ObjCount();
		}
	}


	return Count;
}


c2DCoord* cTile::GetObjFromNode(UINT Idx)
{
	if(Idx < m_pObjList.size())
		return m_pObjList[Idx];
	else
	{
		Idx -= m_pObjList.size();

		for(int i=0; i<8; i++)
		{
			if(m_pNode[i] == NULL) continue;


			if(Idx < m_pNode[i]->ObjCount())
				return (*m_pNode[i]->GetObjList())[Idx];
			else Idx -= m_pNode[i]->ObjCount();
		}
	}


	return NULL;
}

