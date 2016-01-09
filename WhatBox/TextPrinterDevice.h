#pragma once

#include <string>

#include "Device.h"



























class TextPrinterDevice : public Device
{
public:
	TextPrinterDevice();
	virtual ~TextPrinterDevice();


protected:
	std::wstring m_text;
	std::wstring m_textCompleted;


public:
	virtual int readyForNextG() override;
	virtual int update(double timeSpeed) override;
	virtual int render() override;


public:
	virtual double evaluate(std::shared_ptr<Director> pDirector);


public:
	std::wstring getText() const;
};

