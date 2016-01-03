#pragma once

#include "Object.h"

#include <memory>
#include <array>

class Linker;



























class Unit : public Object
{
public:
	Unit();
	virtual ~Unit();


protected:
	int m_cmdNumber;
	double m_memory;


protected:
	// * 실행흐름 연결
	std::shared_ptr<Linker> m_pInFlowLinker, m_pOutFlowLinker;

	// * 인자 연결
	std::array<std::shared_ptr<Linker>, 2> m_pParamLinkers;

	
protected:
	// * 수행된 시간
	double m_timeGage;


public:
	int update(double timePitch);


public:
	void setCmdNumber(int cmdNumber);
	int getCmdNumber() const;

	void setMemory(double memory);
	void addMemory(double deltaMemory);
	double getMemory() const;


public:
	int setInLinker(std::shared_ptr<Linker> pInLinker);
	int setOutLinker(std::shared_ptr<Linker> pOutLinker);
	std::shared_ptr<Linker> getInLinker() const;
	std::shared_ptr<Linker> getOutLinker() const;

	int setParamLinker(std::shared_ptr<Linker> pParamLinker, int index);
	std::shared_ptr<Linker> getParamLinker(int index) const;

	std::shared_ptr<Unit> getRelativeFlowUnit(int relativeIndex) const;


public:
	void setTimeGage(double gage);
	void addTimeGage(double deltaGage);
	double getTimeGage() const;
};

