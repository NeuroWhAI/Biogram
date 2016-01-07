#pragma once

#include <memory>
#include <vector>

class TimeManager;
class BiogramCage;
class Memory;
class Device;
class Director;



























class BiogramWorld
{
public:
	typedef std::shared_ptr<TimeManager> TimeManagerPtr;
	typedef std::shared_ptr<BiogramCage> BiogramCagePtr;
	typedef std::shared_ptr<Memory> MemoryPtr;
	typedef std::shared_ptr<Device> DevicePtr;
	typedef std::shared_ptr<Director> DirectorPtr;


public:
	BiogramWorld();
	virtual ~BiogramWorld();


protected:
	TimeManagerPtr m_pTimeManager;
	double m_maxTimePerGeneration;
	size_t m_generationNumber;


protected:
	std::vector<BiogramCagePtr> m_pCageList;
	MemoryPtr m_pSharedMemory;


protected:
	std::vector<DevicePtr> m_deviceList;
	std::vector<DirectorPtr> m_directorList;


public:
	int clear();
	int clearForNextGeneration();
	int initWorld(size_t cageCount, double maxTimePerGeneration);
	template <typename T_DEVICE>
	int initDeviceForeachCage(const T_DEVICE& originalDevice);
	template <typename T_DIRECTOR>
	int initDirector(const T_DIRECTOR& originalDirector);

	
public:
	int update();


protected:
	bool isReadyForNextGeneration();
	int stepToNextGeneration();


protected:
	int updateTimeSpeed();
	int updateCage();
	int updateDevice();
	int evaluateCage();
	int checkReadyForNext();


public:
	int addCage(BiogramCagePtr pCage);
	int addDevice(DevicePtr pDevice);


public:
	size_t getGenerationNumber() const;
	double getTimeSpeed() const;
	double getElapsedTime() const;
	const std::vector<BiogramCagePtr>& getCageList() const;
	MemoryPtr getSharedMemory() const;
	const std::vector<DevicePtr>& getDeviceList() const;
};


#include "BiogramWorld.inl"