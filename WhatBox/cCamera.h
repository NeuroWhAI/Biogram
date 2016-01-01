#pragma once
#include <d3d9.h>
#include <d3dx9.h>















///////////////////////////////////////////////////////////////////////////////////////////////////////
// Name : ī�޶�
// Desc : ī�޶���ġ�� ���°������� ����� ��� ����
///////////////////////////////////////////////////////////////////////////////////////////////////////

class cCamera
{
public:
	cCamera();
	~cCamera();


private:
	static int Number;
	static int CurrCamera;
	int m_Number;

public:
	static int CurrCameraNum();
	static void SetCurrCamera(int num);


private:
	D3DXMATRIX m_mtWorld;


	D3DXMATRIX m_mtView;

	D3DXVECTOR3 m_vEyePt;
	D3DXVECTOR3 m_vLookAt;
	D3DXVECTOR3 m_vUpVec;


	D3DXMATRIX m_mtPrj;


public:
	int Setup(D3DXVECTOR3 vEyePt, D3DXVECTOR3 vLookAt);

	int FrameMove();


public:
	int Control();


	void MoveForward(float speed);
	void MoveBackward(float speed);

	void MoveSideward(float speed/* �����̳� ����ķ� ���� ���� */, bool MoveLookAt = true);

	void Rotation(float speed/* �����̳� ����ķ� ���� ���� */);



public:
	void SetEyePt(float x, float y, float z);
	void SetLookAt(float x, float y, float z);
	void SetUpVec(float x, float y, float z);

	void AddEyePt(float x, float y, float z);
	void AddLookAt(float x, float y, float z);


public:
	D3DXVECTOR3 GetEyePt() const;
	D3DXVECTOR3 GetLookAt() const;
	D3DXVECTOR3 GetUpVec() const;
	D3DXMATRIX GetPrj() const;
	D3DXMATRIX GetView() const;
};

