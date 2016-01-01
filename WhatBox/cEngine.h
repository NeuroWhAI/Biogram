#pragma once
#include <Windows.h>
#include <string>

#include "Option.h"

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

class cCore;
class cD3DDevice;
class cSqMgr;
class cWorld;

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
#ifdef USE_COORDINATE
class cCoordinate;
#endif

class cRSLight;

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/













///////////////////////////////////////////////////////////////////////////////////////////////////////
// Name : ���α׷�����
// Desc : ���α׷��� ���ۺ��� ��������� ������ �����Ѵ�.
///////////////////////////////////////////////////////////////////////////////////////////////////////

class cEngine
{
public:
	cEngine();
	~cEngine();


private: /* �⺻ ������ ���� */
	HWND m_hWnd;
	std::string m_Name;

	WNDCLASSEX m_Wc;
	MSG m_Msg;

	bool m_bTransparent;
	DWORD m_clearColor;


private: /* �߾��ھ� */
	cCore* m_pCore;

private: /* D3D */
	cD3DDevice* m_pD3DDevice;
#ifdef USE_COORDINATE
	cCoordinate* m_pCoordinate;			// ��ǥ��
#endif
#ifdef USE_RSLIGHT
	cRSLight* m_pRSLight;				// D3DRS_LIGHTING
#endif


private: /* ������ */
	cSqMgr* m_pSqMgr;

public: /* �� �Լ� */
	int Create(HINSTANCE hInst
		, std::string Name, int Width, int Height
		, LRESULT (CALLBACK *MsgProc) (HWND, UINT, WPARAM, LPARAM)
		, bool bWindowed
		, bool bTransparent = false);
	int MsgLoop();
	int MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	WPARAM CleanUp();


private: /* ���� */
	cWorld* m_pWorld;


private:
	int InitCore(HINSTANCE hInst); // �ھ��ʱ�ȭ

	int Release();
	int Restore();
	int ResetDevice(); // ����̽�����


private:
	int RenderLoop(); // Render����
	int RenderState();// D3D SetRenderState


private: /* ��ƿ */
	HRESULT Screenshot();
};

