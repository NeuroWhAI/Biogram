#pragma once
#include <d3dx9.h>
#include <string>
#include "Option.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////
// Name : ��ƿ����
#include "c3DPoint.h"
#include "cCoord.h"
///////////////////////////////////////////////////////////////////////////////////////////////////////

class cTexture;
class cD3DVtxBuffer;
class cD3DIdxBuffer;
class cFont;

///////////////////////////////////////////////////////////////////////////////////////////////////////
// Name : ��ƿ����
// Desc : ���α׷��� ���� ���� ¥�����ش�.
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
	/* ����� */
	void ShowNumber(int Num, int x, int y, DWORD Color);
	void ShowNumber(long Num, int x, int y, DWORD Color);
	void ShowNumber(float Num, int x, int y, DWORD Color);
	void ShowNumber(double Num, int x, int y, DWORD Color);

	void Log(const char* sFormatLog, ...);

	void ShowText(const char Format[], float x, float y, DWORD Color, ...);
	void ShowText(const char Format[], float x, float y, DWORD Color, cFont* pFont, ...);

	void PushMessage(::std::wstring msg, DWORD color);


	int ErrorMessage(::std::string Msg);


	/* ���� ��� */
	bool FloatEqual(float A, float B);
	double logB(double x, double base);
	float flogB(float x, float base);
	DWORD GetReverseColor(DWORD rawColor);


	/* D3D���� */
	void D3DXMatrixViewport(D3DXMATRIX* pOut);

	void MouseRay(D3DXVECTOR3* pDir, D3DXVECTOR3* pOrig); // ��ŷ�� ���� ���콺�� ���
	bool IntersectTriangle(const D3DXVECTOR3& vDir, const D3DXVECTOR3& vOrig
		, const D3DXVECTOR3& v0, const D3DXVECTOR3& v1, const D3DXVECTOR3& v2/*�ﰢ�� ������ ��ġ*/
		, FLOAT* t, FLOAT* u, FLOAT* v); // ��ŷ�� ���� �ﰢ�� �浹�˻�

	void SetAlphaChannel(BOOL OnOff);

	void SetMatrixToDevice(D3DXVECTOR3* Position = NULL
		, D3DXVECTOR3* Rotation = NULL
		, D3DXVECTOR3* Scale = NULL); // RST 3���� ��� ����
	void SetIdentityMatrix(); // ������� ����

	void CalculateNormal(D3DXVECTOR3* pOut
		, const D3DXVECTOR3* v0, const D3DXVECTOR3* v1, const D3DXVECTOR3* v2); // ��ֺ��� ���

	void DrawVtxByIdx(const cD3DVtxBuffer* pVtx, const cD3DIdxBuffer* pIdx); // �ε������ۿ� ���ؽ����۷� �׸�


	class TempRenderState // �����ÿ� RenderState�� ���� �ٲ�ٰ� ��ü�� �ı��ɶ� ������Ŵ
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


	class TempSamplerState // �����ÿ� SamplerState�� ���� �ٲ�ٰ� ��ü�� �ı��ɶ� ������Ŵ
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


	/* ���� */
	const D3DXVECTOR2& CenterPos();
	const POINT& CenterPt();


	/* ���� */
	ULONG Rand();
	bool Probable(UINT Percent);
	bool Probable(double Percent);


	/* ���� */
	int GetControlVector(D3DXVECTOR2* pOut, char UpKey, char DownKey, char LeftKey, char RightKey, float Speed); // �ش� ����Ű�� �ش��ϴ� ���Ͱ� ��ȯ


	/* ���ڿ� */
	void StrToWStr(const ::std::string& str, ::std::wstring* pOut);
	void WStrToStr(const ::std::wstring& wStr, ::std::string* pOut);

	void StrToWStr(const char str[], ::std::wstring* pOut);
	void WStrToStr(const wchar_t wStr[], ::std::string* pOut);
};

