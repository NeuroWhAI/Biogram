#pragma once

#include <string>
#include <vector>

#include "Device.h"



























class TextPrinterDevice : public Device
{
public:
	TextPrinterDevice();
	virtual ~TextPrinterDevice();


protected:
	std::wstring m_text;
	std::vector<wchar_t> m_realText;


public:
	virtual int init() override;
	virtual int update(double timeSpeed) override;
	virtual int render() override;


public:
	virtual double evaluate(std::shared_ptr<Director> pDirector);


public:
	const std::wstring& getText() const;
	const std::vector<wchar_t>& getRealText() const;
};

