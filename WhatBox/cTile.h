#pragma once
#include <d3dx9.h>
#include <vector>


class cShp_Rectangle;
class c2DCoord;
























class cTile
{
public:
	cTile(float X, float Y, float Size);
	virtual ~cTile();


protected:
	cShp_Rectangle* m_pRect;					// 타일 영역
	float m_Size;								// 타일 크기 (최적화용)


protected:
	cTile* m_pNode[8];


protected:
	std::vector<c2DCoord*> m_pObjList;


public:
	int UpdateOutCheck();
	int Update();
	int Render();


protected:
	virtual int OnUpdate();
	virtual int OnRender();


public:
	UINT ObjCount() const;


public:
	D3DXVECTOR2 GetPos() const;
	int AddPos(float X, float Y);
	float GetSize() const;
	const cShp_Rectangle* GetRect() const;


public:
	int SetNode(cTile* pTile, int Idx);
	cTile* GetNode(int Idx);


public:
	UINT AddObj(c2DCoord* pObj); // 인덱스 반환해줌
	int RemoveObj(const c2DCoord* pObj);
	std::vector<c2DCoord*>* GetObjList();


public:
	int IndexOf(const c2DCoord* pObj) const;
	UINT CheckOutIdx(const D3DXVECTOR2* Pos); // Node 인덱스 반환


protected:
	int CheckOut();
	void GetMirrorSpeed(const D3DXVECTOR2* Pos, D3DXVECTOR2* Speed);
	
	
protected:
	UINT ObjCountFromNode();
	c2DCoord* GetObjFromNode(UINT Idx);
	

protected:
	virtual int OnAddObj(c2DCoord* pObj, UINT idx) = 0;
	virtual int OnRemoveObj(const c2DCoord* pObj, UINT idx) = 0;
};

