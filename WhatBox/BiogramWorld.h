#pragma once

#include <memory>
#include <vector>

class TimeManager;
class BiogramCage;
class Memory;



























class BiogramWorld
{
public:
	typedef std::shared_ptr<TimeManager> TimeManagerPtr;
	typedef std::shared_ptr<BiogramCage> BiogramCagePtr;
	typedef std::shared_ptr<Memory> MemoryPtr;


public:
	BiogramWorld();
	virtual ~BiogramWorld();


protected:
	TimeManagerPtr m_pTimeManager;


protected:
	std::vector<BiogramCagePtr> m_pCageList;
	MemoryPtr m_pSharedMemory;


public:
	int update();


protected:
	int updateTimeSpeed();
	int updateCage();


public:
	int addCage(BiogramCagePtr pCage);


public:
	double getTimeSpeed() const;
	const std::vector<BiogramCagePtr>& getCageList() const;
	MemoryPtr getSharedMemory() const;
};

