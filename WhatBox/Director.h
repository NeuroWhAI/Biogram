#pragma once

class TextPrinterDevice;



























class Director
{
public:
	Director();
	virtual ~Director();


public:
	virtual int readyForNextG();
	virtual double evaluate(const TextPrinterDevice& device);
};

