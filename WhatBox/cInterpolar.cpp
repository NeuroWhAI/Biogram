#include "cInterpolar.h"

#include "cCore.h"




















cInterpolar::cInterpolar(float Start, float End, DWORD Time)
	: m_CurrVal(Start)
	, m_EndVal(End)

	, m_Bigger(m_EndVal > m_CurrVal ? 1.f : -1.f)

	, m_Speed((m_EndVal - m_CurrVal)/Time*1000.f)

	, m_isEnd(false)
{

}


cInterpolar::~cInterpolar()
{

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////

int cInterpolar::FrameMove()
{
	if(m_isEnd) return 1;


	m_CurrVal += EST(m_Speed);

	if(m_CurrVal*m_Bigger > m_EndVal*m_Bigger)
	{
		m_CurrVal = m_EndVal;

		m_isEnd = true;
	}


	return 0;
}


bool cInterpolar::isEnd() const
{
	return m_isEnd;
}



float cInterpolar::Value() const
{
	return m_CurrVal;
}

