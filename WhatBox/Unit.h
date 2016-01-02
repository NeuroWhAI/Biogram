#pragma once

#include "Object.h"



























class Unit : public Object
{
public:
	Unit();
	virtual ~Unit();


protected:
	int m_cmdNumber;
	double m_memory;


public:
	int update(double timePitch);


public:
	void setCmdNumber(int cmdNumber);
	int getCmdNumber() const;

	void setMemory(double memory);
	void addMemory(double deltaMemory);
	double getMemory() const;
};

