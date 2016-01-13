#pragma once

#include <memory>
#include <vector>

class TimeManager;
class Unit;
class Linker;
class CommandOperator;
class Memory;
class ComPort;
class BiogramDNA;
template <typename T>
class ObjectPool;



























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
	std::shared_ptr<ObjectPool<Unit>> m_pUnitPool;
	std::shared_ptr<ObjectPool<Linker>> m_pLinkerPool;


protected:
	double m_elapsedTime;
	

protected:
	std::shared_ptr<BiogramDNA> m_DNA;
	double m_geneScore, m_prevGeneScore;


protected:
	std::vector<std::shared_ptr<Unit>> m_pUnitList;
	std::vector<std::shared_ptr<Linker>> m_pFlowLinkerList;
	std::vector<std::shared_ptr<Linker>> m_pParamLinkerList;
	
	std::shared_ptr<Memory> m_cageMemory;
	std::vector<std::shared_ptr<ComPort>> m_comPortList;
	size_t m_assignedPortCount;


protected:
	std::shared_ptr<CommandOperator> m_pCmdOperator;


public:
	int setSharedMemory(std::shared_ptr<Memory> sharedMemory);
	virtual int update(double timeSpeed);
	/*
	* 명령어 진행이 종료되었고 적합도의 변화가 없는가?
	* @Return: 종료 여부
	*/
	bool isEnd() const;


protected:
	int updateCommand(double timeSpeed);


public:
	std::shared_ptr<const BiogramDNA> getDNA() const;
	void setGeneScore(double score);
	double getGeneScore() const;
	double getOldGeneScore() const;


public:
	int buildBiogram(const BiogramDNA& dna);
	int buildBiogramWithoutClear(const BiogramDNA& dna);
	int clear();
	int clearWithoutComPort();


public:
	double getElapsedTime() const;


public:
	bool addUnit(std::shared_ptr<Unit> pUnit);
	bool removeUnit(std::shared_ptr<Unit> pUnit);
	bool addLinker(std::shared_ptr<Linker> pLinker, LinkerTypes type);
	bool removeLinker(std::shared_ptr<Linker> pLinker, LinkerTypes type);


public:
	std::shared_ptr<ComPort> assignComPort(
		std::vector<std::pair<int, int>> portNum_address);
	size_t getValidPortCount() const;


public:
	const std::vector<std::shared_ptr<Unit>>& getUnitList() const;
	const std::vector<std::shared_ptr<Linker>>& getFlowLinkerList() const;
	const std::vector<std::shared_ptr<Linker>>& getParamLinkerList() const;
	std::shared_ptr<const Memory> getCageMemory() const;
	std::shared_ptr<const CommandOperator> getCmdOperator() const;
};

