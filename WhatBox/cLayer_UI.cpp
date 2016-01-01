#include "cLayer_UI.h"

#include "cCore.h"

#include "cUIControl.h"



























cLayer_UI::cLayer_UI()
{

}


cLayer_UI::~cLayer_UI()
{
	
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////

int cLayer_UI::OnInit()
{



	return 0;
}


int cLayer_UI::OnDestory()
{
	


	return 0;
}

/*-------------------------------------------------------------------------------------------------------*/

int cLayer_UI::OnUpdate()
{
	for(UINT i=0; i<m_pUIList.size(); i++)
	{
		if(m_pUIList[i] == NULL) continue;


		m_pUIList[i]->Update();
	}


	return 0;
}


int cLayer_UI::OnRender()
{
	for(UINT i=0; i<m_pUIList.size(); i++)
	{
		if(m_pUIList[i] == NULL) continue;


		m_pUIList[i]->Render();
	}


	return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////

int cLayer_UI::Reset()
{
	m_pUIList.clear();


	return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////

int cLayer_UI::AddUIControl(cUIControl* pUI)
{
	m_pUIList.push_back(pUI);


	return 0;
}


int cLayer_UI::RemoveUIControl(const cUIControl* pUI)
{
	for(UINT i=0; i<m_pUIList.size(); i++)
	{
		if(m_pUIList[i] == pUI)
		{
			m_pUIList.erase(m_pUIList.begin() + i);
			return 0;
		}
	}


	return -1;
}

