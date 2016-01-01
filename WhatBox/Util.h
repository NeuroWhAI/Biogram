#pragma once
#include <d3dx9.h>
#include <string>
#include "Option.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////
// Name : 유틸전용
#include "c3DPoint.h"
#include "cCoord.h"
///////////////////////////////////////////////////////////////////////////////////////////////////////

class cTexture;
class cD3DVtxBuffer;
class cD3DIdxBuffer;
class cFont;

///////////////////////////////////////////////////////////////////////////////////////////////////////
// Name : 유틸모음
// Desc : 프로그램을 좀더 쉽게 짜게해준다.
///////////////////////////////////////////////////////////////////////////////////////////////////////










/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

#define EPSILON 0.0001f

#define SAFE_DELETE(p)				{ if(p) { delete (p);     (p)=NULL; } }
#define SAFE_DELETE_ARR(p)			{ if(p) { delete[] (p);   (p)=NULL; } }
#define SAFE_RELEASE(p)				{ if(p) { (p)->Release(); (p)=NULL; } }
#define SAFE_ACCESS(p, a)			{ if(p) { (p)->a; } }

#define CAST(v, type)				static_cast<type>(v)

#define STRING(x) #x

#ifdef USE_VFR
#define EST(x) ((x)*cCore::ElapsedTime)

#define VFR(x) ((x)*cCore::FrameRate)
#define VFR2X(x) ((x)*2.f*cCore::FrameRate)
#define VFR4X(x) ((x)*4.f*cCore::FrameRate)
#define VFR8X(x) ((x)*8.f*cCore::FrameRate)
#define VFR16X(x) ((x)*16.f*cCore::FrameRate)
#else
#define EST(x) (x)

#define VFR(x) (x)
#define VFR2X(x) (x)
#define VFR4X(x) (x)
#define VFR8X(x) (x)
#define VFR16X(x) (x)
#endif


inline DWORD FtoDW(float& p) { return *((DWORD*)&p); }

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

namespace Util
{
	/* 디버깅 */
	void ShowNumber(int Num, int x, int y, DWORD Color);
	void ShowNumber(long Num, int x, int y, DWORD Color);
	void ShowNumber(float Num, int x, int y, DWORD Color);
	void ShowNumber(double Num, int x, int y, DWORD Color);

	void Log(const char* sFormatLog, ...);

	void ShowText(const char Format[], float x, float y, DWORD Color, ...);
	void ShowText(const char Format[], float x, float y, DWORD Color, cFont* pFont, ...);

	void PushMessage(::std::wstring msg, DWORD color);


	int ErrorMessage(::std::string Msg);


	/* 숫자 계산 */
	bool FloatEqual(float A, float B);
	double logB(double x, double base);
	float flogB(float x, float base);
	DWORD GetReverseColor(DWORD rawColor);


	/* D3D관련 */
	void D3DXMatrixViewport(D3DXMATRIX* pOut);

	void MouseRay(D3DXVECTOR3* pDir, D3DXVECTOR3* pOrig); // 피킹을 위한 마우스선 계산
	bool IntersectTriangle(const D3DXVECTOR3& vDir, const D3DXVECTOR3& vOrig
		, const D3DXVECTOR3& v0, const D3DXVECTOR3& v1, const D3DXVECTOR3& v2/*삼각형 정점들 위치*/
		, FLOAT* t, FLOAT* u, FLOAT* v); // 피킹을 위한 삼각형 충돌검사

	void SetAlphaChannel(BOOL OnOff);

	void SetMatrixToDevice(D3DXVECTOR3* Position = NULL
		, D3DXVECTOR3* Rotation = NULL
		, D3DXVECTOR3* Scale = NULL); // RST 3차원 행렬 적용
	void SetIdentityMatrix(); // 단위행렬 적용

	void CalculateNormal(D3DXVECTOR3* pOut
		, const D3DXVECTOR3* v0, const D3DXVECTOR3* v1, const D3DXVECTOR3* v2); // 노멀벡터 계산

	void DrawVtxByIdx(const cD3DVtxBuffer* pVtx, const cD3DIdxBuffer* pIdx); // 인덱스버퍼와 버텍스버퍼로 그림


	class TempRenderState // 생성시에 RenderState의 값을 바꿨다가 객체가 파괴될때 복구시킴
	{
	public:
		TempRenderState(D3DRENDERSTATETYPE State, DWORD Value);
		~TempRenderState();
	private:
		TempRenderState(TempRenderState&) {}
	private:
		D3DRENDERSTATETYPE m_State;
		DWORD m_oldValue;
	};


	class TempSamplerState // 생성시에 SamplerState의 값을 바꿨다가 객체가 파괴될때 복구시킴
	{
	public:
		TempSamplerState(DWORD Sampler, D3DSAMPLERSTATETYPE Type, DWORD Value);
		~TempSamplerState();
	private:
		TempSamplerState(TempSamplerState&) {}
	private:
		DWORD m_Sampler;
		D3DSAMPLERSTATETYPE m_Type;
		DWORD m_oldValue;
	};


	class TempOffCamera
	{
	public:
		TempOffCamera();
		~TempOffCamera();
	private:
		bool m_wasOn;
	};


	/* 정보 */
	const D3DXVECTOR2& CenterPos();
	const POINT& CenterPt();


	/* 선택 */
	ULONG Rand();
	bool Probable(UINT Percent);
	bool Probable(double Percent);


	/* 조작 */
	int GetControlVector(D3DXVECTOR2* pOut, char UpKey, char DownKey, char LeftKey, char RightKey, float Speed); // 해당 조작키에 해당하는 벡터값 반환


	/* 문자열 */
	void StrToWStr(const ::std::string& str, ::std::wstring* pOut);
	void WStrToStr(const ::std::wstring& wStr, ::std::string* pOut);

	void StrToWStr(const char str[], ::std::wstring* pOut);
	void WStrToStr(const wchar_t wStr[], ::std::string* pOut);
};

