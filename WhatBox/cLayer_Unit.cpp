#include "cLayer_Unit.h"

#include "cCore.h"

#include "cUnit.h"



























cLayer_Unit::cLayer_Unit()
{

}


cLayer_Unit::~cLayer_Unit()
{
	
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////

int cLayer_Unit::OnInit()
{



	return 0;
}


int cLayer_Unit::OnDestory()
{
	


	return 0;
}

/*-------------------------------------------------------------------------------------------------------*/

int cLayer_Unit::OnUpdate()
{
	for(UINT i=0; i<m_pUnitList.size(); i++)
	{
		if(m_pUnitList[i] == NULL) continue;


		m_pUnitList[i]->Update();
	}


	return 0;
}


int cLayer_Unit::OnRender()
{
	for(UINT i=0; i<m_pUnitList.size(); i++)
	{
		if(m_pUnitList[i] == NULL) continue;


		m_pUnitList[i]->Render();
	}


	return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////

int cLayer_Unit::Reset()
{
	m_pUnitList.clear();


	return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////

int cLayer_Unit::AddUnit(cUnit* pUnit)
{
	m_pUnitList.push_back(pUnit);


	return 0;
}


int cLayer_Unit::RemoveUnitControl(const cUnit* pUnit)
{
	for(UINT i=0; i<m_pUnitList.size(); i++)
	{
		if(m_pUnitList[i] == pUnit)
		{
			m_pUnitList.erase(m_pUnitList.begin() + i);
			return 0;
		}
	}


	return -1;
}

