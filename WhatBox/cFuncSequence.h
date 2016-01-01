#pragma once
#include <vector>
#include <functional>


























///////////////////////////////////////////////////////////////////////////////////////////////////////
// Name : 함수 시퀀서
// Desc : 함수단위로 시퀀스를 구현
///////////////////////////////////////////////////////////////////////////////////////////////////////

#define LAMBDA_FUNC(Func) [&] () -> int {return (Func)();}


enum FUNCRESULT
{
	FUNCRESULT_Continue = -1,
	FUNCRESULT_End = -2,
};


class cFuncSequence
{
public:
	cFuncSequence();
	~cFuncSequence();


private:
	std::vector<std::function<int()>> m_FuncList;
	int m_CurrFuncNum;


public:
	int Update();
	bool IsEnd() const;


public:
	int SetCurrFuncNum(int FuncNum);
	int AddFunction(std::function<int()> Func, unsigned int Idx);
};

