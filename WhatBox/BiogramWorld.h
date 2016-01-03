#pragma once

#include <memory>
#include <vector>

class TimeManager;
class Unit;
class Linker;
class CommandOperator;



























class BiogramWorld
{
public:
	BiogramWorld();
	virtual ~BiogramWorld();


protected:
	std::shared_ptr<TimeManager> m_pTimeManager;


protected:
	std::vector<std::shared_ptr<Unit>> m_pUnitList;
	std::vector<std::shared_ptr<Linker>> m_pFlowLinkerList;
	std::vector<std::shared_ptr<Linker>> m_pParamLinkerList;


protected:
	std::shared_ptr<CommandOperator> m_pCmdOperator;


public:
	int update();


protected:
	// * 시뮬레이션 속도가 빠름으로 인해서
	//   부정확함이 발생하는 것을 방지하기위해
	//   시간이 흐르는 속도를 재계산.
	int updateTimeSpeed();
	int updateUnit();
	int updateCommand();


public:
	double getTimeSpeed() const;
	const std::vector<std::shared_ptr<Unit>>& getUnitList() const;
	const std::vector<std::shared_ptr<Linker>>& getFlowLinkerList() const;
	const std::vector<std::shared_ptr<Linker>>& getParamLinkerList() const;
	std::shared_ptr<const CommandOperator> getCmdOperator() const;
};

