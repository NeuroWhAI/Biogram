#pragma once
#include <d3dx9.h>


class cShp_Sphere;
class cShp_Rectangle;
class cShp_Line;
class cShp_Polygon;
class cShp_Triangle;


















///////////////////////////////////////////////////////////////////////////////////////////////////////
// Name : 도형수학
// Desc : 도형에 관련된 수학적 처리를 해줌
///////////////////////////////////////////////////////////////////////////////////////////////////////

class cShapeMath
{
public:
	cShapeMath();
	~cShapeMath();


public: /* 계산 */
	float GetLength(const D3DXVECTOR2* Vec) const;
	float GetLengthSq(const D3DXVECTOR2* Vec) const;

	float GetDistance(const D3DXVECTOR3* P1, const D3DXVECTOR3* P2) const; // 점, 점
	float GetDistanceSq(const D3DXVECTOR3* P1, const D3DXVECTOR3* P2) const; // 점, 점 (거리의 제곱값을 반환)
	float GetDistance(const D3DXVECTOR2* P1, const D3DXVECTOR2* P2) const; // 점, 점
	float GetDistanceSq(const D3DXVECTOR2* P1, const D3DXVECTOR2* P2) const; // 점, 점 (거리의 제곱값을 반환)

	float GetAngle(const D3DXVECTOR2* P1, const D3DXVECTOR2* P2) const; // 두 점 사이의 각
	float GetAngle(const cShp_Line* L1, const cShp_Line* L2) const; // 두 선분 사이의 각
	float GetAngle(const D3DXVECTOR2* L1_P1, const D3DXVECTOR2* L1_P2, const D3DXVECTOR2* L2_P1, const D3DXVECTOR2* L2_P2) const; // 두 선분 사이의 각

	void GetPosition(D3DXVECTOR2* pOut, float DistanceFromCenter, float Degree) const; // 거리, 각으로 위치를 계산

	void GetAnglePos(float* pAngleOut, float* pDistanceOut, const D3DXVECTOR2* Center, const D3DXVECTOR2* P) const; // 중심점과 상대점사이의 거리와 각을 계산

	void GetNormalVec(D3DXVECTOR2* pOut, const D3DXVECTOR2* Vec) const; // 법선벡터 구하기
	void GetNormalVec(D3DXVECTOR2* pOut, const D3DXVECTOR2* P1, const D3DXVECTOR2* P2) const; // 법선벡터 구하기

	void GetCenterPos(D3DXVECTOR2* pOut, const D3DXVECTOR2* P1, const D3DXVECTOR2* P2) const; // 중심점 구하기

	void GetReflectionVec(D3DXVECTOR2* pOut, const D3DXVECTOR2* GuideVec, const D3DXVECTOR2* Vec) const; // 반사벡터 구하기
	void GetReflectionVec(D3DXVECTOR2* pOut, const cShp_Line* GuideLine, const cShp_Line* Line) const; // 반사벡터 구하기

	float GetAttractionPower(const D3DXVECTOR2* P1, float M1, const D3DXVECTOR2* P2, float M2) const;


public: /* 충돌 검사 */
	bool isCollided(const D3DXVECTOR3* P1, const D3DXVECTOR3* P2) const; // 점, 점
	bool isCollided(const D3DXVECTOR3* P, const cShp_Sphere* S) const; // 점, 구
	bool isCollided(const cShp_Sphere* S1, const cShp_Sphere* S2) const; // 구, 구
	bool isCollided(const D3DXVECTOR2* P, const D3DXVECTOR2* C, float R) const; // 점, 원
	bool isCollided(const D3DXVECTOR2* C1, float R1, const D3DXVECTOR2* C2, float R2) const; // 원, 원
	bool isCollided(const D3DXVECTOR2* P, const cShp_Rectangle* RC) const; // 점, 사각형
	bool isCollided(const cShp_Rectangle* RC1, const cShp_Rectangle* RC2) const; // 사각형, 사각형
	bool isCollided(const cShp_Line* L1, const cShp_Line* L2, D3DXVECTOR2* IntersectPos = nullptr) const; // 선, 선
	bool isCollided(const D3DXVECTOR2* L1_P1, const D3DXVECTOR2* L1_P2, const D3DXVECTOR2* L2_P1, const D3DXVECTOR2* L2_P2, D3DXVECTOR2* IntersectPos = nullptr) const; // 선, 선
	bool isCollided(const cShp_Polygon* Polygon1, const cShp_Polygon* Polygon2) const;
	bool isCollided(const cShp_Polygon* Polygon1, const cShp_Polygon* Polygon2, D3DXVECTOR2* IntersectPos) const; // 다각형, 다각형
	bool isCollided(const cShp_Polygon* Polygon1, const cShp_Polygon* Polygon2, cShp_Line* GetLine1, cShp_Line* GetLine2, D3DXVECTOR2* IntersectPos = nullptr) const; // 다각형, 다각형 (충돌 선 반환)
	bool isCollided(const cShp_Polygon* Polygon, const D3DXVECTOR2* P) const; // 다각형, 점
	bool isCollided(const cShp_Triangle* Triangle, const D3DXVECTOR2* P) const; // 삼각형, 점
	bool isCollided(const cShp_Line* L, const D3DXVECTOR2* C, float R, int* pColNum, D3DXVECTOR2* pColPos1 = nullptr, D3DXVECTOR2* pColPos2 = nullptr) const; // 선, 원


public: /* 충돌 처리 */

};

