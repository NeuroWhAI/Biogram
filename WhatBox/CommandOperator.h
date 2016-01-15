#pragma once

#include <memory>
#include <vector>

class Unit;
class Linker;
class Memory;

#define CMD_FUNC_PARAM (int* pNextRelativeNum, std::shared_ptr<Unit> here, std::shared_ptr<Unit> param1, std::shared_ptr<Unit> param2)
#define CMD_FUNC(name) double name CMD_FUNC_PARAM



























class CommandOperator
{
public:
	CommandOperator();
	virtual ~CommandOperator();


protected:
	size_t m_currentFlowIndex;
	std::vector<std::shared_ptr<Unit>> m_pFlowUnitList;
	bool m_bIsEnd;


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
	int restart();
	int clear();
	bool isEnd() const;


public:
	int addFlowUnit(std::shared_ptr<Unit> pUnit);
	const std::vector<std::shared_ptr<Unit>>& getFlowUnitList() const;


public:
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