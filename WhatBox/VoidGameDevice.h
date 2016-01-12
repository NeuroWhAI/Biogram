#pragma once

#include "Device.h"



























class VoidGameDevice : public Device
{
public:
	VoidGameDevice();
	virtual ~VoidGameDevice();


protected:
	bool m_bBombInLeft;

	size_t m_failCount, m_successCount;


public:
	virtual int init() override;
	virtual int update(double timeSpeed) override;
	virtual int render() override;


public:
	virtual double evaluate(std::shared_ptr<Director> pDirector);


public:
	size_t getFailCount() const;
	size_t getSuccessCount() const;
};

#pragma once
