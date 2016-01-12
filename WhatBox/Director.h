#pragma once

class TextPrinterDevice;
class VoidGameDevice;



























class Director
{
public:
	Director();
	virtual ~Director();


public:
	virtual int init();
	virtual double evaluate(const TextPrinterDevice& device);
	virtual double evaluate(const VoidGameDevice& device);
};

