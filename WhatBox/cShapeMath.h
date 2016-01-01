#pragma once
#include <d3dx9.h>


class cShp_Sphere;
class cShp_Rectangle;
class cShp_Line;
class cShp_Polygon;
class cShp_Triangle;


















///////////////////////////////////////////////////////////////////////////////////////////////////////
// Name : ��������
// Desc : ������ ���õ� ������ ó���� ����
///////////////////////////////////////////////////////////////////////////////////////////////////////

class cShapeMath
{
public:
	cShapeMath();
	~cShapeMath();


public: /* ��� */
	float GetLength(const D3DXVECTOR2* Vec) const;
	float GetLengthSq(const D3DXVECTOR2* Vec) const;

	float GetDistance(const D3DXVECTOR3* P1, const D3DXVECTOR3* P2) const; // ��, ��
	float GetDistanceSq(const D3DXVECTOR3* P1, const D3DXVECTOR3* P2) const; // ��, �� (�Ÿ��� �������� ��ȯ)
	float GetDistance(const D3DXVECTOR2* P1, const D3DXVECTOR2* P2) const; // ��, ��
	float GetDistanceSq(const D3DXVECTOR2* P1, const D3DXVECTOR2* P2) const; // ��, �� (�Ÿ��� �������� ��ȯ)

	float GetAngle(const D3DXVECTOR2* P1, const D3DXVECTOR2* P2) const; // �� �� ������ ��
	float GetAngle(const cShp_Line* L1, const cShp_Line* L2) const; // �� ���� ������ ��
	float GetAngle(const D3DXVECTOR2* L1_P1, const D3DXVECTOR2* L1_P2, const D3DXVECTOR2* L2_P1, const D3DXVECTOR2* L2_P2) const; // �� ���� ������ ��

	void GetPosition(D3DXVECTOR2* pOut, float DistanceFromCenter, float Degree) const; // �Ÿ�, ������ ��ġ�� ���

	void GetAnglePos(float* pAngleOut, float* pDistanceOut, const D3DXVECTOR2* Center, const D3DXVECTOR2* P) const; // �߽����� ����������� �Ÿ��� ���� ���

	void GetNormalVec(D3DXVECTOR2* pOut, const D3DXVECTOR2* Vec) const; // �������� ���ϱ�
	void GetNormalVec(D3DXVECTOR2* pOut, const D3DXVECTOR2* P1, const D3DXVECTOR2* P2) const; // �������� ���ϱ�

	void GetCenterPos(D3DXVECTOR2* pOut, const D3DXVECTOR2* P1, const D3DXVECTOR2* P2) const; // �߽��� ���ϱ�

	void GetReflectionVec(D3DXVECTOR2* pOut, const D3DXVECTOR2* GuideVec, const D3DXVECTOR2* Vec) const; // �ݻ纤�� ���ϱ�
	void GetReflectionVec(D3DXVECTOR2* pOut, const cShp_Line* GuideLine, const cShp_Line* Line) const; // �ݻ纤�� ���ϱ�

	float GetAttractionPower(const D3DXVECTOR2* P1, float M1, const D3DXVECTOR2* P2, float M2) const;


public: /* �浹 �˻� */
	bool isCollided(const D3DXVECTOR3* P1, const D3DXVECTOR3* P2) const; // ��, ��
	bool isCollided(const D3DXVECTOR3* P, const cShp_Sphere* S) const; // ��, ��
	bool isCollided(const cShp_Sphere* S1, const cShp_Sphere* S2) const; // ��, ��
	bool isCollided(const D3DXVECTOR2* P, const D3DXVECTOR2* C, float R) const; // ��, ��
	bool isCollided(const D3DXVECTOR2* C1, float R1, const D3DXVECTOR2* C2, float R2) const; // ��, ��
	bool isCollided(const D3DXVECTOR2* P, const cShp_Rectangle* RC) const; // ��, �簢��
	bool isCollided(const cShp_Rectangle* RC1, const cShp_Rectangle* RC2) const; // �簢��, �簢��
	bool isCollided(const cShp_Line* L1, const cShp_Line* L2, D3DXVECTOR2* IntersectPos = nullptr) const; // ��, ��
	bool isCollided(const D3DXVECTOR2* L1_P1, const D3DXVECTOR2* L1_P2, const D3DXVECTOR2* L2_P1, const D3DXVECTOR2* L2_P2, D3DXVECTOR2* IntersectPos = nullptr) const; // ��, ��
	bool isCollided(const cShp_Polygon* Polygon1, const cShp_Polygon* Polygon2) const;
	bool isCollided(const cShp_Polygon* Polygon1, const cShp_Polygon* Polygon2, D3DXVECTOR2* IntersectPos) const; // �ٰ���, �ٰ���
	bool isCollided(const cShp_Polygon* Polygon1, const cShp_Polygon* Polygon2, cShp_Line* GetLine1, cShp_Line* GetLine2, D3DXVECTOR2* IntersectPos = nullptr) const; // �ٰ���, �ٰ��� (�浹 �� ��ȯ)
	bool isCollided(const cShp_Polygon* Polygon, const D3DXVECTOR2* P) const; // �ٰ���, ��
	bool isCollided(const cShp_Triangle* Triangle, const D3DXVECTOR2* P) const; // �ﰢ��, ��
	bool isCollided(const cShp_Line* L, const D3DXVECTOR2* C, float R, int* pColNum, D3DXVECTOR2* pColPos1 = nullptr, D3DXVECTOR2* pColPos2 = nullptr) const; // ��, ��


public: /* �浹 ó�� */

};

