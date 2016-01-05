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
	std::unordered_set<std::shared_ptr<Unit>> m_pCurrentUnitList;
	std::unordered_set<std::shared_ptr<Unit>> m_pRemovalUnitList;
	std::unordered_set<std::shared_ptr<Unit>> m_pNextUnitList;


protected:
	std::shared_ptr<Memory> m_pSharedMemory;


protected:
	using CommandFuncType = double(CommandOperator::*) CMD_FUNC_PARAM;
	std::vector<CommandFuncType> m_cmdFuncList;


public:
	int update(double timePitch);


public:
	// * ��ɾ �����ų ���� ��Ͽ� pUnit�� �߰��մϴ�.
	// * @Return: �߰����� ����
	bool addUnit(std::shared_ptr<Unit> pUnit);

	void removeUnit(std::shared_ptr<Unit> pUnit);


public:
	size_t getCurrentUnitCount() const;


public:
	int setSharedMemory(std::shared_ptr<Memory> pSharedMemory);
	double readSharedMem(int address);
	void writeSharedMem(int address, double value);


protected: // ��ɾ����� �Լ��� ����
#include "CommandFunction.h"
};


#ifndef DO_NOT_DELETE_CMD_FUNC_DEFINE
#undef CMD_FUNC
#undef CMD_FUNC_PARAM
#endif