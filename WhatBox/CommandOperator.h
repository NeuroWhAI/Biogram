#pragma once

#include <memory>
#include <unordered_set>
#include <vector>

class Unit;
class Linker;
class Memory;

#define CMD_FUNC_PARAM (std::shared_ptr<Unit>* pNextUnit, std::shared_ptr<Unit> here, std::shared_ptr<Unit> param1, std::shared_ptr<Unit> param2)
#define CMD_FUNC(name) double name CMD_FUNC_PARAM



























class CommandOperator
{
public:
	CommandOperator();
	virtual ~CommandOperator();


protected:
	std::shared_ptr<Unit> m_pCurrentUnit;


protected:
	std::shared_ptr<Memory> m_pSharedMemory;
	std::shared_ptr<Memory> m_pCageMemory;
	double m_elapsedTime;
	double m_geneScore;


protected:
	using CommandFuncType = double(CommandOperator::*) CMD_FUNC_PARAM;
	std::vector<CommandFuncType> m_cmdFuncList;


public:
	int update(double timePitch, double totalTime);
	int clear();
	bool isEnd() const;


public:
	// * 명령어를 실행시킬 유닛 목록에 pUnit을 추가합니다.
	// * @Return: 추가성공 여부
	bool addUnit(std::shared_ptr<Unit> pUnit);

	void removeUnit(std::shared_ptr<Unit> pUnit);


public:
	size_t getCurrentUnitCount() const;
	size_t getCmdFunctionCount() const;


public:
	int setSharedMemory(std::shared_ptr<Memory> pSharedMemory);
	double readSharedMem(int address);
	void writeSharedMem(int address, double value);

	int setCageMemory(std::shared_ptr<Memory> pCageMemory);
	double readCageMem(int address);
	void writeCageMem(int address, double value);


public:
	void setGeneScore(double score);


protected: // 명령어실행용 함수들 선언
#include "CommandFunction.h"
};


#ifndef DO_NOT_DELETE_CMD_FUNC_DEFINE
#undef CMD_FUNC
#undef CMD_FUNC_PARAM
#endif