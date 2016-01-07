#pragma once

#include "Director.h"

#include <string>



























class TextCheckDirector : public Director
{
public:
	explicit TextCheckDirector(std::wstring answer);
	virtual ~TextCheckDirector();


protected:
	std::wstring m_answer;


public:
	double evaluate(const TextPrinterDevice& device) override;
};

