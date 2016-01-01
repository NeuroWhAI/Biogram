#include "cFuncSequence.h"
































cFuncSequence::cFuncSequence()
	: m_CurrFuncNum(FUNCRESULT_End)
{

}


cFuncSequence::~cFuncSequence()
{

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////

int cFuncSequence::Update()
{
	if(m_CurrFuncNum >= 0)
	{
		int FuncCount = static_cast<int>(m_FuncList.size());


		int NextNum = m_FuncList[m_CurrFuncNum]();

		if(NextNum >= 0  &&  NextNum < FuncCount)
		{
			m_CurrFuncNum = NextNum;
		}
		else if(NextNum == FUNCRESULT_End)
		{
			m_CurrFuncNum = FUNCRESULT_End;
		}
	}


	return 0;
}


bool cFuncSequence::IsEnd() const
{
	return (m_CurrFuncNum < 0);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////

int cFuncSequence::SetCurrFuncNum(int FuncNum)
{
	m_CurrFuncNum = FuncNum;


	return 0;
}


int cFuncSequence::AddFunction(std::function<int()> Func, unsigned int Idx)
{
	while(Idx >= m_FuncList.size()) m_FuncList.emplace_back();


	m_FuncList[Idx] = Func;


	return 0;
}

