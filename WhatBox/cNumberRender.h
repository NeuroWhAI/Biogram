#pragma once


class cTextureList;





















///////////////////////////////////////////////////////////////////////////////////////////////////////
// Name : ���� �׸���
// Desc : int�� ���� 2D ��������Ʈ�� �̿��ؼ� �׷���
///////////////////////////////////////////////////////////////////////////////////////////////////////

class cNumberRender
{
public:
	cNumberRender();
	cNumberRender(cTextureList* pTxList);

	~cNumberRender();


private:
	cTextureList* m_pTxList;
	float m_TxWidth;
	int m_Number;


public:
	int SetTextureList(cTextureList* pTxList);
	int SetNumber(int Number);
	int GetNumber() const;


public:
	int Render(float x, float y) const;
	int Render(int Number, float x, float y) const;


private:
	int Pow(int x, int y) const;
};

