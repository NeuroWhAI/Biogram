#pragma once

#include <memory>
#include <unordered_set>
#include <vector>

class Unit;
class Linker;

#define CMD_FUNC_PARAM (std::shared_ptr<Unit>* pNextUnit, std::shared_ptr<Unit> here, std::shared_ptr<Unit> param1, std::shared_ptr<Unit> param2)
#define CMD_FUNC(name) double name CMD_FUNC_PARAM



























class CommandOperator
{
public:
	CommandOperator();
	virtual ~CommandOperator();


protected:
	std::unordered_set<std::shared_ptr<Unit>> m_pCurrentUnitList;
	std::unordered_set<std::shared_ptr<Unit>> m_pRemovalUnitList;
	std::unordered_set<std::shared_ptr<Unit>> m_pNextUnitList;


protected:
	using CommandFuncType = double(CommandOperator::*) CMD_FUNC_PARAM;
	std::vector<CommandFuncType> m_cmdFuncList;


public:
	int update(double timePitch);


public:
	// * 명령어를 실행시킬 유닛 목록에 pUnit을 추가합니다.
	// * @Return: 추가성공 여부
	bool addUnit(std::shared_ptr<Unit> pUnit);

	void removeUnit(std::shared_ptr<Unit> pUnit);


public:
	size_t getCurrentUnitCount() const;


protected: // 명령어실행용 함수들 선언
#include "CommandFunction.h"
};


#ifndef DO_NOT_DELETE_CMD_FUNC_DEFINE
#undef CMD_FUNC
#undef CMD_FUNC_PARAM
#endif