#pragma once

class TextPrinterDevice;



























class Director
{
public:
	Director();
	virtual ~Director();


public:
	virtual double evaluate(const TextPrinterDevice& device);
};

