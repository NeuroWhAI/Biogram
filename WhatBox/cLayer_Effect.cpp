#include "cLayer_Effect.h"

#include "cCore.h"

#include "cEffect.h"



























cLayer_Effect::cLayer_Effect()
{

}


cLayer_Effect::~cLayer_Effect()
{
	for(UINT i=0; i<m_pEffectList.size(); i++)
	{
		if(m_pEffectList[i] != NULL  &&  m_DeleteWhenEndList[i])
		{
			delete m_pEffectList[i];
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////

int cLayer_Effect::OnInit()
{



	return 0;
}


int cLayer_Effect::OnDestory()
{
	


	return 0;
}

/*-------------------------------------------------------------------------------------------------------*/

int cLayer_Effect::OnUpdate()
{
	for(UINT i=0; i<m_pEffectList.size(); )
	{
		if(m_pEffectList[i] == NULL) continue;


		m_pEffectList[i]->Update();

		if(m_pEffectList[i]->isEnd())
		{
			if(m_DeleteWhenEndList[i])
			{
				delete m_pEffectList[i];
			}

			m_pEffectList.erase(m_pEffectList.begin() + i);
			m_DeleteWhenEndList.erase(m_DeleteWhenEndList.begin() + i);

			continue;
		}


		//------------------------------
		i++;
	}


	cCore::FxMgr.Update();


	return 0;
}


int cLayer_Effect::OnRender()
{
	cCore::FxMgr.Render();


	for(UINT i=0; i<m_pEffectList.size(); i++)
	{
		if(m_pEffectList[i] == NULL) continue;


		m_pEffectList[i]->RenderCenter();
	}


	return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////

int cLayer_Effect::Reset()
{
	for(UINT i=0; i<m_pEffectList.size(); i++)
	{
		if(m_pEffectList[i] != NULL  &&  m_DeleteWhenEndList[i])
		{
			delete m_pEffectList[i];
		}
	}

	m_pEffectList.clear();
	m_DeleteWhenEndList.clear();


	return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////

int cLayer_Effect::AddEffect(cEffect* pEffect, bool DeleteWhenEnd)
{
	m_pEffectList.push_back(pEffect);
	m_DeleteWhenEndList.push_back(DeleteWhenEnd);


	return 0;
}


int cLayer_Effect::RemoveEffectControl(const cEffect* pEffect)
{
	for(UINT i=0; i<m_pEffectList.size(); i++)
	{
		if(m_pEffectList[i] == pEffect)
		{
			if(m_DeleteWhenEndList[i])
			{
				delete m_pEffectList[i];
			}

			m_pEffectList.erase(m_pEffectList.begin() + i);
			m_DeleteWhenEndList.erase(m_DeleteWhenEndList.begin() + i);
			return 0;
		}
	}


	return -1;
}

