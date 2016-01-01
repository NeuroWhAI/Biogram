#include "cShapeMath.h"

#include "cCore.h"


#include "cShp_Sphere.h"
#include "cShp_Rectangle.h"
#include "cShp_Line.h"
#include "cShp_Polygon.h"
#include "cShp_Triangle.h"























cShapeMath::cShapeMath()
{

}


cShapeMath::~cShapeMath()
{

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

float cShapeMath::GetLength(const D3DXVECTOR2* Vec) const
{
	return D3DXVec2Length(Vec);
}


float cShapeMath::GetLengthSq(const D3DXVECTOR2* Vec) const
{
	return D3DXVec2LengthSq(Vec);
}

/*------------------------------------------------------------------------------------------------------*/

float cShapeMath::GetDistance(const D3DXVECTOR3* P1, const D3DXVECTOR3* P2) const
{
	D3DXVECTOR3 SubVec(*P1 - *P2);
	return D3DXVec3Length(&SubVec);
}


float cShapeMath::GetDistanceSq(const D3DXVECTOR3* P1, const D3DXVECTOR3* P2) const
{
	D3DXVECTOR3 SubVec(*P1 - *P2);
	return D3DXVec3LengthSq(&SubVec);
}


float cShapeMath::GetDistance(const D3DXVECTOR2* P1, const D3DXVECTOR2* P2) const
{
	D3DXVECTOR2 SubVec(*P1 - *P2);
	return D3DXVec2Length(&SubVec);
}


float cShapeMath::GetDistanceSq(const D3DXVECTOR2* P1, const D3DXVECTOR2* P2) const
{
	D3DXVECTOR2 SubVec(*P1 - *P2);
	return D3DXVec2LengthSq(&SubVec);
}

/*------------------------------------------------------------------------------------------------------*/

float cShapeMath::GetAngle(const D3DXVECTOR2* P1, const D3DXVECTOR2* P2) const
{
	/*
	*     -90
	* -180 P1 0
	*      90
	*/
	return D3DXToDegree(atan2f(P2->y - P1->y, P2->x - P1->x));
}


float cShapeMath::GetAngle(const cShp_Line* L1, const cShp_Line* L2) const
{
	return GetAngle(&L1->P1, &L1->P2, &L2->P1, &L2->P2);
}


float cShapeMath::GetAngle(const D3DXVECTOR2* L1_P1, const D3DXVECTOR2* L1_P2, const D3DXVECTOR2* L2_P1, const D3DXVECTOR2* L2_P2) const
{
	D3DXVECTOR2 Sub1, Sub2;

	D3DXVec2Subtract(&Sub1, L1_P1, L1_P2);
	D3DXVec2Subtract(&Sub2, L2_P1, L2_P2);

	D3DXVec2Normalize(&Sub1, &Sub1);
	D3DXVec2Normalize(&Sub2, &Sub2);


	float Radian = acosf(D3DXVec2Dot(&Sub1, &Sub2));


	return D3DXToDegree(min(D3DX_PI - Radian, Radian));
}

/*------------------------------------------------------------------------------------------------------*/

void cShapeMath::GetPosition(D3DXVECTOR2* pOut, float DistanceFromCenter, float Degree) const
{
	pOut->x = cosf(D3DXToRadian(Degree)) * DistanceFromCenter;
	pOut->y = sinf(D3DXToRadian(Degree)) * DistanceFromCenter;
}

/*------------------------------------------------------------------------------------------------------*/

void cShapeMath::GetAnglePos(float* pAngleOut, float* pDistanceOut, const D3DXVECTOR2* Center, const D3DXVECTOR2* P) const
{
	*pAngleOut = GetAngle(Center, P);
	*pDistanceOut = GetDistance(Center, P);
}

/*------------------------------------------------------------------------------------------------------*/

void cShapeMath::GetNormalVec(D3DXVECTOR2* pOut, const D3DXVECTOR2* Vec) const
{
	pOut->x = Vec->y;
	pOut->y = -Vec->x;

	D3DXVec2Normalize(pOut, pOut);
}


void cShapeMath::GetNormalVec(D3DXVECTOR2* pOut, const D3DXVECTOR2* P1, const D3DXVECTOR2* P2) const
{
	D3DXVECTOR2 SubVec(*P1 - *P2);
	GetNormalVec(pOut, &SubVec);
}

/*------------------------------------------------------------------------------------------------------*/

void cShapeMath::GetCenterPos(D3DXVECTOR2* pOut, const D3DXVECTOR2* P1, const D3DXVECTOR2* P2) const
{
	pOut->x = (P1->x + P2->x) / 2.f;
	pOut->y = (P1->y + P2->y) / 2.f;
}

/*------------------------------------------------------------------------------------------------------*/

void cShapeMath::GetReflectionVec(D3DXVECTOR2* pOut, const D3DXVECTOR2* GuideVec, const D3DXVECTOR2* Vec) const
{
	D3DXVECTOR2 NormalVec;
	GetNormalVec(&NormalVec, GuideVec);

	float Dot = D3DXVec2Dot(Vec, &NormalVec);

	*pOut = *Vec - NormalVec * 2.f * Dot;
	D3DXVec2Normalize(pOut, pOut);
}


void cShapeMath::GetReflectionVec(D3DXVECTOR2* pOut, const cShp_Line* GuideLine, const cShp_Line* Line) const
{
	D3DXVECTOR2 Sub1, Sub2;

	D3DXVec2Subtract(&Sub1, &GuideLine->P1, &GuideLine->P2);
	D3DXVec2Subtract(&Sub2, &Line->P1, &Line->P2);

	GetReflectionVec(pOut, &Sub1, &Sub2);
}

/*------------------------------------------------------------------------------------------------------*/

float cShapeMath::GetAttractionPower(const D3DXVECTOR2* P1, float M1, const D3DXVECTOR2* P2, float M2) const
{
	float disRq = GetDistanceSq(P1, P2);
	

	if(disRq == 0.f)
		return M1*M2;

	return (M1*M2/disRq);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool cShapeMath::isCollided(const D3DXVECTOR3* P1, const D3DXVECTOR3* P2) const
{
	return (Util::FloatEqual(P1->x, P2->x)  &&  Util::FloatEqual(P1->y, P2->y)  &&  Util::FloatEqual(P1->z, P2->z));
}


bool cShapeMath::isCollided(const D3DXVECTOR3* P, const cShp_Sphere* S) const
{
	return (GetDistanceSq(P, &S->Center)  <=  S->Radius * S->Radius);
}


bool cShapeMath::isCollided(const cShp_Sphere* S1, const cShp_Sphere* S2) const
{
	float Dis = S1->Radius + S2->Radius;
	return (GetDistanceSq(&S1->Center, &S2->Center)  <=  Dis*Dis);
}


bool cShapeMath::isCollided(const D3DXVECTOR2* P, const D3DXVECTOR2* C, float R) const
{
	return (GetDistanceSq(P, C)  <=  R*R);
}


bool cShapeMath::isCollided(const D3DXVECTOR2* C1, float R1, const D3DXVECTOR2* C2, float R2) const
{
	float Dis = R1 + R2;
	return (GetDistanceSq(C1, C2)  <=  Dis*Dis);
}


bool cShapeMath::isCollided(const D3DXVECTOR2* P, const cShp_Rectangle* RC) const
{
	return ((P->x >= RC->left) && (P->x <= RC->right) && (P->y >= RC->top) && (P->y <= RC->bottom));
}


bool cShapeMath::isCollided(const cShp_Rectangle* RC1, const cShp_Rectangle* RC2) const
{
	return ((RC1->left < RC2->right) && (RC1->top < RC2->bottom) && (RC1->right > RC2->left) && (RC1->bottom > RC2->top));
}


bool cShapeMath::isCollided(const cShp_Line* L1, const cShp_Line* L2, D3DXVECTOR2* IntersectPos) const
{
	return isCollided(&L1->P1, &L1->P2, &L2->P1, &L2->P2, IntersectPos);
}


bool cShapeMath::isCollided(const D3DXVECTOR2* L1_P1, const D3DXVECTOR2* L1_P2, const D3DXVECTOR2* L2_P1, const D3DXVECTOR2* L2_P2, D3DXVECTOR2* IntersectPos) const
{
	float den = (L2_P2->y - L2_P1->y)*(L1_P2->x - L1_P1->x) - (L2_P2->x - L2_P1->x)*(L1_P2->y - L1_P1->y);
	// (y4 - y3) * (x2 - x1) - (x4 - x3) * (y2 - y1)

	if(abs(den) < 0.000001f)
		return false;		// 평행선


	float t = (L2_P2->x - L2_P1->x)*(L1_P1->y - L2_P1->y) - (L2_P2->y-L2_P1->y)*(L1_P1->x - L2_P1->x);
	float s = (L1_P2->x - L1_P1->x)*(L1_P1->y - L2_P1->y) - (L1_P2->y-L1_P1->y)*(L1_P1->x - L2_P1->x);

	float ua = t / den;
	float ub = s / den;
	// ua = ((x4 - x3) * (y1 - y3) - (y4 - y3) * (x1 - x3)) / den
	// ub = ((x2 - x1) * (y1 - y3) - (y2 - y1) * (x1 - x3)) / den

	if(abs(t) < 0.000001f  &&  abs(s) < 0.000001f)
		return false;

	if(0.f <= ua  &&  ua <= 1.f
		&&
		0.f <= ub  &&  ub <= 1.f)
	{/* 충돌 */
		if(IntersectPos != nullptr)
		{// 교점 구하기
			IntersectPos->x = L1_P1->x + ua*(L1_P2->x - L1_P1->x);
			IntersectPos->y = L1_P1->y + ua*(L1_P2->y - L1_P1->y);
		}


		return true;
	}


	return false;
}


bool cShapeMath::isCollided(const cShp_Polygon* Polygon1, const cShp_Polygon* Polygon2) const
{
	UINT VtxNum1 = Polygon1->VtxCount();
	UINT VtxNum2 = Polygon2->VtxCount();

	const std::vector<D3DXVECTOR2>& VtxList1 = *Polygon1->GetVtxList();
	const std::vector<D3DXVECTOR2>& VtxList2 = *Polygon2->GetVtxList();


	// 폴리곤1의 점들중 하나라도 폴리곤2에 들어있나 확인
	for(UINT i=0; i<VtxNum1; i++)
	{
		if(isCollided(Polygon2, &VtxList1[i]))
			return true;
	}

	// 폴리곤2의 점들중 하나라도 폴리곤1에 들어있나 확인
	for(UINT i=0; i<VtxNum2; i++)
	{
		if(isCollided(Polygon1, &VtxList2[i]))
			return true;
	}


	return false;
}


bool cShapeMath::isCollided(const cShp_Polygon* Polygon1, const cShp_Polygon* Polygon2, D3DXVECTOR2* IntersectPos) const
{
	return isCollided(Polygon1, Polygon2, NULL, NULL, IntersectPos);
}


bool cShapeMath::isCollided(const cShp_Polygon* Polygon1, const cShp_Polygon* Polygon2, cShp_Line* GetLine1, cShp_Line* GetLine2, D3DXVECTOR2* IntersectPos) const
{
	const std::vector<D3DXVECTOR2>& VtxList1 = *Polygon1->GetVtxList();
	const std::vector<D3DXVECTOR2>& VtxList2 = *Polygon2->GetVtxList();


	UINT VtxCount1 = VtxList1.size();
	UINT VtxCount2 = VtxList2.size();

	if(VtxCount1 == 0  ||  VtxCount2 == 0) return false;


	for(UINT i=0; i<=VtxCount1; i++)
	{
		UINT Idx1 = i % VtxCount1;
		UINT Idx2 = (i + 1) % VtxCount1;

		for(UINT j=0; j<=VtxCount2; j++)
		{
			UINT Idx21 = j % VtxCount2;
			UINT Idx22 = (j+1)%VtxCount2;

			if(cCore::ShapeMath.isCollided(&VtxList1[Idx1], &VtxList1[Idx2],
				&VtxList2[Idx21], &VtxList2[Idx22],
				IntersectPos))
			{
				if(GetLine1 != NULL)
				{
					GetLine1->P1 = VtxList1[Idx1];
					GetLine1->P2 = VtxList1[Idx2];
				}

				if(GetLine2 != NULL)
				{
					GetLine2->P1 = VtxList2[Idx21];
					GetLine2->P2 = VtxList2[Idx22];
				}


				return true;
			}
		}
	}


	return false;
}


bool cShapeMath::isCollided(const cShp_Polygon* Polygon, const D3DXVECTOR2* P) const
{
	float xnew,ynew;
	float xold,yold;
	float x1,y1;
	float x2,y2;
	bool inside = false;
	UINT nPoints = Polygon->VtxCount();

	if (nPoints < 3U) {
		return false;
	}

	const std::vector<D3DXVECTOR2>& VtxList = *Polygon->GetVtxList();

	xold=VtxList[nPoints-1].x;
	yold=VtxList[nPoints-1].y;

	for (UINT i=0; i < nPoints; i++)
	{
		xnew=VtxList[i].x;
		ynew=VtxList[i].y;

		if (xnew > xold)
		{
			x1=xold;
			x2=xnew;
			y1=yold;
			y2=ynew;
		}
		else
		{
			x1=xnew;
			x2=xold;
			y1=ynew;
			y2=yold;
		}

		if ((xnew < P->x) == (P->x <= xold)          /* edge "open" at one end */
			&& (P->y - y1) * (x2-x1)
			< (y2 - y1) * (P->x - x1))
		{
			inside=!inside;
		}

		xold=xnew;
		yold=ynew;
	}


	return inside;
}


bool cShapeMath::isCollided(const cShp_Triangle* Triangle, const D3DXVECTOR2* P) const
{// TODO: 성능 테스트 필요
	POINT PosArr[3] = {
		{ CAST(Triangle->m_P1.x, LONG), CAST(Triangle->m_P1.y, LONG) },
		{ CAST(Triangle->m_P2.x, LONG), CAST(Triangle->m_P2.y, LONG) },
		{ CAST(Triangle->m_P3.x, LONG), CAST(Triangle->m_P3.y, LONG) }
	};

	HRGN Rgn = CreatePolygonRgn(PosArr, 3, ALTERNATE);
	

	return (PtInRegion(Rgn, CAST(P->x, int), CAST(P->y, int)) != TRUE ? false : true);
}


bool cShapeMath::isCollided(const cShp_Line* L, const D3DXVECTOR2* C, float R, int* pColNum, D3DXVECTOR2* pColPos1, D3DXVECTOR2* pColPos2) const
{
	*pColNum = 0;

	float x = C->x;
	float y = C->y;

	float a = L->P1.x;
	float b = L->P1.y;
	float c = L->P2.x;
	float d = L->P2.y;

	float m, n;

	// A,B1,C 원과 직선으로부터 얻어지는 2차방정식의 계수들
	// D: 판별식
	// X,Y: 교점의 좌표
	float A, B1, _C, D;
	float X, Y;

	// A,B1,C,D게산
	if( c!=a )
	{
		// m, n계산
		m = (d-b)/(c-a);
		n = (b*c-a*d)/(c-a);

		A = m*m + 1;
		B1= (m*n-m*y-x);
		_C = (x*x + y*y - R*R + n*n - 2*n*y);
		D = B1*B1 - A*_C;

		if( D < 0 )
			return false;
		else if( D == 0 )
		{
			X = -B1/A;
			Y = m*X + n;

			if(pColPos1 != nullptr)
			{
				pColPos1->x = X;
				pColPos1->y = Y;
			}


			*pColNum = 1;


			return true;
		}
		else
		{
			X = -(B1 + sqrt(D))/A;
			Y = m*X + n;

			if(pColPos1 != nullptr)
			{
				pColPos1->x = X;
				pColPos1->y = Y;
			}


			X = -(B1 - sqrt(D))/A;
			Y = m*X + n;

			if(pColPos2 != nullptr)
			{
				pColPos2->x = X;
				pColPos2->y = Y;
			}


			*pColNum = 2;


			return true;
		}
	}
	else
	{
		// a == c 인 경우는 수직선이므로
		// 근을 가지려면 a >= (x-r) && a <=(x+r) )
		// (a-x)*(a-x)
		// 1. 근이 없는 경우
		// a < (x-r) || a > (x+r)

		// 근이 없음
		if( a < (x-R) || a > (x+R) )
			return false;
		// 하나의 중근
		else if( a==(x-R) || a ==(x+R) )
		{
			X = a;
			Y = y;

			if(pColPos1 != nullptr)
			{
				pColPos1->x = X;
				pColPos1->y = Y;
			}


			*pColNum = 1;


			return true;
		}
		// 두개의 근
		else
		{
			// x = a를 대입하여 Y에 대하여 풀면
			X = a;
			Y = y + sqrt( R*R - (a-x)*(a-x) );

			if(pColPos1 != nullptr)
			{
				pColPos1->x = X;
				pColPos1->y = Y;
			}


			Y = y - sqrt( R*R - (a-x)*(a-x) );

			if(pColPos2 != nullptr)
			{
				pColPos2->x = X;
				pColPos2->y = Y;
			}


			*pColNum = 2;


			return true;
		}
	}


	return false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

