#pragma once

#include <memory>
#include <vector>

class TimeManager;
class Unit;
class Linker;
class CommandOperator;
template <typename T_OBJ>
class TileMap;



























enum class LinkerTypes : int
{
	Flow,
	Param,
};


class BiogramWorld
{
public:
	BiogramWorld(float width, float height);
	virtual ~BiogramWorld();


protected:
	std::shared_ptr<TimeManager> m_pTimeManager;
	

protected:
	std::shared_ptr<TileMap<Unit>> m_pCloseUnitBoard;


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
	int updateLinker();
	int updateCommand();
	int updateCloseUnitBoard();


public:
	bool addUnit(std::shared_ptr<Unit> pUnit);
	bool removeUnit(std::shared_ptr<Unit> pUnit);
	bool addLinker(std::shared_ptr<Linker> pLinker, LinkerTypes type);
	bool removeLinker(std::shared_ptr<Linker> pLinker, LinkerTypes type);


public:
	double getTimeSpeed() const;
	const std::vector<std::shared_ptr<Unit>>& getUnitList() const;
	const std::vector<std::shared_ptr<Linker>>& getFlowLinkerList() const;
	const std::vector<std::shared_ptr<Linker>>& getParamLinkerList() const;
	std::shared_ptr<const CommandOperator> getCmdOperator() const;
};

