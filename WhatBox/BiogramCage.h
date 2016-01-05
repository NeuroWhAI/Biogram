#pragma once

#include <memory>
#include <vector>

class TimeManager;
class Unit;
class Linker;
class CommandOperator;
class Memory;



























enum class LinkerTypes : int
{
	Flow,
	Param,
};


class BiogramCage
{
public:
	BiogramCage();
	virtual ~BiogramCage();
	

protected:
	std::vector<std::shared_ptr<Unit>> m_pUnitList;
	std::vector<std::shared_ptr<Linker>> m_pFlowLinkerList;
	std::vector<std::shared_ptr<Linker>> m_pParamLinkerList;


protected:
	std::shared_ptr<CommandOperator> m_pCmdOperator;


public:
	int setSharedMemory(std::shared_ptr<Memory> sharedMemory);
	virtual int update(double timeSpeed);


protected:
	int updateUnit(double timeSpeed);
	int updateLinker(double timeSpeed);
	int updateCommand(double timeSpeed);


public:
	bool addUnit(std::shared_ptr<Unit> pUnit);
	bool removeUnit(std::shared_ptr<Unit> pUnit);
	bool addLinker(std::shared_ptr<Linker> pLinker, LinkerTypes type);
	bool removeLinker(std::shared_ptr<Linker> pLinker, LinkerTypes type);


public:
	const std::vector<std::shared_ptr<Unit>>& getUnitList() const;
	const std::vector<std::shared_ptr<Linker>>& getFlowLinkerList() const;
	const std::vector<std::shared_ptr<Linker>>& getParamLinkerList() const;
	std::shared_ptr<const CommandOperator> getCmdOperator() const;
};

