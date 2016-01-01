#include "cWorld.h"

#include "cCore.h"

#include "cLayer.h"
#include "cLayer_Fade.h"
#include "cLayer_UI.h"
#include "cLayer_Effect.h"
#include "cLayer_Unit.h"
#include "cLayer_Back.h"































cWorld::cWorld()
{
	m_pLayerList.push_back(new cLayer_Fade());
	m_pLayerList.push_back(new cLayer_UI());
	m_pLayerList.push_back(new cLayer_Effect());
	m_pLayerList.push_back(new cLayer_Unit());
	m_pLayerList.push_back(new cLayer_Back());
}


cWorld::~cWorld()
{
	for(UINT i=0; i<m_pLayerList.size(); i++)
	{
		SAFE_DELETE(m_pLayerList[i]);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int cWorld::Init()
{
	m_pLayerList[LAYER_Fade]->Init();
	m_pLayerList[LAYER_UI]->Init();
	m_pLayerList[LAYER_Effect]->Init();
	m_pLayerList[LAYER_Unit]->Init();
	m_pLayerList[LAYER_Back]->Init();


	return 0;
}


int cWorld::Destroy()
{
	m_pLayerList[LAYER_Fade]->Destroy();
	m_pLayerList[LAYER_UI]->Destroy();
	m_pLayerList[LAYER_Effect]->Destroy();
	m_pLayerList[LAYER_Unit]->Destroy();
	m_pLayerList[LAYER_Back]->Destroy();


	return 0;
}

/*-----------------------------------------------------------------------------------------------------*/

int cWorld::Update()
{
	m_pLayerList[LAYER_Back]->Update();
	m_pLayerList[LAYER_Unit]->Update();
	m_pLayerList[LAYER_Effect]->Update();
	m_pLayerList[LAYER_UI]->Update();
	m_pLayerList[LAYER_Fade]->Update();


	return 0;
}


int cWorld::Render()
{
	m_pLayerList[LAYER_Back]->Render();
	m_pLayerList[LAYER_Unit]->Render();
	m_pLayerList[LAYER_Effect]->Render();
	m_pLayerList[LAYER_UI]->Render();
	m_pLayerList[LAYER_Fade]->Render();


	return 0;
}

/*-----------------------------------------------------------------------------------------------------*/

int cWorld::Reset()
{
	GetUILayer()->Reset();
	GetEffectLayer()->Reset();
	GetBackLayer()->Reset();


	return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

cLayer_Fade* cWorld::GetFadeLayer()
{
	return dynamic_cast<cLayer_Fade*>(m_pLayerList[LAYER_Fade]);
}


cLayer_UI* cWorld::GetUILayer()
{
	return dynamic_cast<cLayer_UI*>(m_pLayerList[LAYER_UI]);
}


cLayer_Effect* cWorld::GetEffectLayer()
{
	return dynamic_cast<cLayer_Effect*>(m_pLayerList[LAYER_Effect]);
}


cLayer_Unit* cWorld::GetUnitLayer()
{
	return dynamic_cast<cLayer_Unit*>(m_pLayerList[LAYER_Unit]);
}


cLayer_Back* cWorld::GetBackLayer()
{
	return dynamic_cast<cLayer_Back*>(m_pLayerList[LAYER_Back]);
}

