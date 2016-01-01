#include "cRSLight.h"

#include "cCore.h"

int cRSLight::s_Number = 0;

void cRSLight::ResetNum()
{ s_Number = 0; }



















cRSLight::cRSLight(D3DLIGHTTYPE LightType, D3DXVECTOR3 Vec, D3DXCOLOR Color
				   , D3DXVECTOR3 Pos)
	: m_Vec(Vec)
{
	m_Number = s_Number;
	s_Number++;


	// 재질
	D3DMATERIAL9 mtrl;
    ZeroMemory( &mtrl, sizeof(D3DMATERIAL9) );
    mtrl.Diffuse.r = mtrl.Ambient.r = 1.0f;
    mtrl.Diffuse.g = mtrl.Ambient.g = 1.0f;
    mtrl.Diffuse.b = mtrl.Ambient.b = 1.0f;
    mtrl.Diffuse.a = mtrl.Ambient.a = 1.0f;
    cCore::pd3dDevice->SetMaterial( &mtrl );


	memset(&m_Light, 0, sizeof m_Light);
	m_Light.Type = LightType; 

	if(LightType == D3DLIGHT_POINT)
	{// 점광원
		m_Light.Ambient = Color * 0.3f; 
		m_Light.Diffuse = Color; 
		m_Light.Specular = Color*0.2f; 
		m_Light.Position = m_Vec; 
		m_Light.Range = 2000.0f; m_Light. Falloff = 1.0f; 
		m_Light.Attenuation0 = 0.5f; m_Light.Attenuation1 = 0.1f; m_Light.Attenuation2 = 0.1f; 
	}
	else if(LightType == D3DLIGHT_SPOT)
	{// 점적 광원
		D3DXVec3Normalize(&Vec, &Vec); // 빛의 방향 

		m_Light.Ambient = Color * 0.0f; 
		m_Light.Diffuse = Color; 
		m_Light.Specular = Color * 0.7f; 
		m_Light.Position = Pos; 
		m_Light.Direction = Vec; 
		m_Light.Range = 5000.0f; m_Light.Falloff = 1.0f; 
		m_Light.Attenuation0 = 0.1f; m_Light.Attenuation1 = 0.1f; m_Light.Attenuation2 = 0.0f; 
		m_Light.Theta = 0.5f; m_Light.Phi = 1.2f;
	}
	else //if(LightType == D3DLIGHT_DIRECTIONAL)
	{// 방향광원
		D3DXVec3Normalize(&Vec, &Vec); 

		m_Light.Ambient = Color * 0.2f; m_Light.Diffuse = Color; 
		m_Light.Specular = Color * 0.7f; m_Light.Direction = Vec;
	}

	if(m_Number < 8)
	{
		// 라이팅 설정 
		cCore::pd3dDevice->SetLight(m_Number, &m_Light); 
		cCore::pd3dDevice->LightEnable(m_Number, TRUE); 
	}
}


cRSLight::cRSLight(D3DLIGHT9 Light)
	: m_Light(Light)
{
	m_Number = s_Number;
	s_Number++;


	// 재질
	D3DMATERIAL9 mtrl;
    ZeroMemory( &mtrl, sizeof(D3DMATERIAL9) );
    mtrl.Diffuse.r = mtrl.Ambient.r = 1.0f;
    mtrl.Diffuse.g = mtrl.Ambient.g = 1.0f;
    mtrl.Diffuse.b = mtrl.Ambient.b = 1.0f;
    mtrl.Diffuse.a = mtrl.Ambient.a = 1.0f;
    cCore::pd3dDevice->SetMaterial( &mtrl );


	if(m_Number < 8)
	{
		// 라이팅 설정 
		cCore::pd3dDevice->SetLight(m_Number, &m_Light); 
		cCore::pd3dDevice->LightEnable(m_Number, TRUE); 
	}
}


cRSLight::~cRSLight()
{
	
}

/*-----------------------------------------------------------------------------------*/

int cRSLight::On()
{
	cCore::pd3dDevice->LightEnable(m_Number, TRUE); 


	return 0;
}


int cRSLight::Off()
{
	cCore::pd3dDevice->LightEnable(m_Number, FALSE); 


	return 0;
}

