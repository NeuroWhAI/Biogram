#include "cFuncList.h"


































cFuncList::cFuncList()
{

}


cFuncList::~cFuncList()
{

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int cFuncList::CallAll()
{
	for(unsigned int i=0; i<m_FuncList.size(); i++)
	{
		m_FuncList[i]();
	}


	return 0;
}


int cFuncList::Call(int Idx)
{
	if(Idx < 0  ||  static_cast<unsigned int>(Idx) >= m_FuncList.size()) return -1;


	return m_FuncList[Idx]();
}


int cFuncList::AddFunc(std::function<cFuncList_F_TYPE> Func)
{
	m_FuncList.emplace_back(Func);


	return 0;
}


int cFuncList::AddFuncAt(std::function<cFuncList_F_TYPE> Func, int Idx)
{
	if(Idx < 0) return -1;


	unsigned int uIdx = static_cast<unsigned int>(Idx);

	while(uIdx > m_FuncList.size()) m_FuncList.emplace_back();


	m_FuncList.emplace_back(Func);


	return 0;
}


int cFuncList::RemoveAt(int Idx)
{
	if(Idx < 0  ||  static_cast<unsigned int>(Idx) >= m_FuncList.size()) return -1;


	m_FuncList.erase(m_FuncList.begin() + Idx);


	return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

cFuncList& cFuncList::operator+= (std::function<cFuncList_F_TYPE> right)
{
	m_FuncList.emplace_back(right);


	return *this;
}


cFuncList& cFuncList::operator+= (cFuncList& right)
{
	for(unsigned int i=0; i<right.m_FuncList.size(); i++)
	{
		m_FuncList.emplace_back(right.m_FuncList[i]);
	}
	

	return *this;
}

