#pragma once
#include <d3dx9.h>
#include <vector>
#include <algorithm>
































class cShp_Triangle
{
public:
	cShp_Triangle();
	cShp_Triangle(const D3DXVECTOR2* P1, const D3DXVECTOR2* P2, const D3DXVECTOR2* P3);
	~cShp_Triangle();


public:
	D3DXVECTOR2 m_P1, m_P2, m_P3;


private:
	std::vector<D3DXVECTOR2> m_points;
	std::vector<POINT> m_li;


public:
	const D3DXVECTOR2* GetP1() const;
	const D3DXVECTOR2* GetP2() const;
	const D3DXVECTOR2* GetP3() const;

	void GetP1(D3DXVECTOR2* pOut) const;
	void GetP2(D3DXVECTOR2* pOut) const;
	void GetP3(D3DXVECTOR2* pOut) const;

	void SetP1(float x, float y);
	void SetP2(float x, float y);
	void SetP3(float x, float y);

	void SetP1(const D3DXVECTOR2* vtx);
	void SetP2(const D3DXVECTOR2* vtx);
	void SetP3(const D3DXVECTOR2* vtx);


public:
	// 삼각형이 변경되었으면 래스터화를 해야함
	int Rasterize();

	// 래스터화한 픽셀들
	int GetPixelList(std::vector<D3DXVECTOR2>* pOut);


public:
	int Render(DWORD color, float width = 1.f);
	int Draw(DWORD color);


private:
	int GetXInline(const POINT a, const POINT b, int y)
	{
		float k = (float)(a.x - b.x) / (a.y - b.y);
		return (int)(k*(y - a.y) + (a.x));
	}

	bool CuttingY(const POINT& A, const POINT& B, const POINT& C, POINT& D)
	{
		D.y = B.y;
		D.x = GetXInline(A, C, B.y);
		return true;
	}

	void RasterizerType1(const POINT& A, const POINT& B, const POINT& C)
	{
		int x1, x2, y, x;
		for (y = A.y; y <= B.y; ++y)
		{
			x1 = GetXInline(A, B, y);
			x2 = GetXInline(A, C, y);
			for (x = x1; x < x2; ++x)
			{
				m_points.emplace_back(static_cast<float>(x), static_cast<float>(y));
			}
		}
	}

	void RasterizerType2(const POINT& A, const POINT& B, const POINT& C)
	{
		int x1, x2, y, x;
		for (y = A.y; y <= C.y; ++y)
		{
			x1 = GetXInline(A, C, y);
			x2 = GetXInline(B, C, y);
			for (x = x1; x < x2; ++x)
			{
				m_points.emplace_back(static_cast<float>(x), static_cast<float>(y));
			}
		}
	}

	void Classify(POINT &A, POINT &B, POINT &C)
	{
		m_li.push_back(A);
		m_li.push_back(B);
		m_li.push_back(C);
		sort(m_li.begin(), m_li.end(), [](POINT A, POINT B) {
			return A.y > B.y;
		});
		std::vector<POINT>::iterator iter = m_li.begin();
		C = *iter;
		++iter;
		B = *iter;
		++iter;
		A = *iter;
	}
};

