#include "cValueProcMgr.h"

#include "cCore.h"




































cValueProcMgr::cValueProcMgr()
{

}


cValueProcMgr::~cValueProcMgr()
{

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////

int cValueProcMgr::AddValueAnimation(float* pVal, float targetVal, float speed, float accelSpeed)
{
	if(*pVal > targetVal)
		speed = -fabsf(speed);
	else if(*pVal < targetVal)
		speed = fabsf(speed);
	else
		return -1;


	m_ptrValueList.emplace_back(pVal, targetVal, speed, accelSpeed);


	return 0;
}


int cValueProcMgr::Remove(const float* pVal)
{
	for(UINT i=0; i<m_ptrValueList.size(); i++)
	{
		if(m_ptrValueList[i].pVal == pVal)
		{
			m_ptrValueList.erase(m_ptrValueList.begin() + i);


			return static_cast<int>(i);
		}
	}


	return -1;
}


bool cValueProcMgr::isEnd(const float* pVal)
{
	for(UINT i=0; i<m_ptrValueList.size(); i++)
	{
		if(m_ptrValueList[i].pVal == pVal)
		{
			if(m_ptrValueList[i].speed < 0.f)
			{
				return (*pVal <= m_ptrValueList[i].targetVal);
			}


			return (*pVal >= m_ptrValueList[i].targetVal);
		}
	}


	return false;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////

int cValueProcMgr::FrameMove()
{
	for(UINT i=0; i<m_ptrValueList.size(); i++)
	{
		float* pVal = m_ptrValueList[i].pVal;


		*pVal += VFR(m_ptrValueList[i].speed);
		m_ptrValueList[i].speed += VFR(m_ptrValueList[i].accelSpeed);


		if(m_ptrValueList[i].speed < 0.f)
		{
			if(*pVal <= m_ptrValueList[i].targetVal)
			{
				*pVal = m_ptrValueList[i].targetVal;
			}
		}
		else
		{
			if(*pVal >= m_ptrValueList[i].targetVal)
			{
				*pVal = m_ptrValueList[i].targetVal;
			}
		}
	}


	return 0;
}

