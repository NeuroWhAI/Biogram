#pragma once

#include <memory>

class Unit;



























class Linker
{
public:
	Linker();
	Linker(std::shared_ptr<Unit> pInUnit, std::shared_ptr<Unit> pOutUnit);
	virtual ~Linker();


protected:
	std::shared_ptr<Unit> m_pInUnit, m_pOutUnit;
	float m_realLength;


public:
	int update(double timePitch);


public:
	int setInUnit(std::shared_ptr<Unit> pInUnit);
	int setOutUnit(std::shared_ptr<Unit> pOutUnit);
	std::shared_ptr<Unit> getInUnit() const;
	std::shared_ptr<Unit> getOutUnit() const;


public:
	float getRealLength() const;


protected:
	bool updateRealLength();
};

