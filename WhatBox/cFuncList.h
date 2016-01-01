#pragma once
#include <vector>
#include <functional>




























#define cFuncList_F_TYPE int(void)

#ifndef LAMBDA_FUNC
#define LAMBDA_FUNC(Func) [&] () -> int {return (Func)();}
#endif


class cFuncList
{
public:
	cFuncList();
	~cFuncList();


private:
	std::vector<std::function<cFuncList_F_TYPE>> m_FuncList;


public:
	int CallAll();
	int Call(int Idx);
	int AddFunc(std::function<cFuncList_F_TYPE> Func);
	int AddFuncAt(std::function<cFuncList_F_TYPE> Func, int Idx);
	int RemoveAt(int Idx);


public:
	cFuncList& operator+= (std::function<cFuncList_F_TYPE> right);
	cFuncList& operator+= (cFuncList& right);
};

