#pragma once

#include "Utility.h"

class BiogramWorld;
class BiogramCage;
class Unit;

class TextPrinterDevice;
class VoidGameDevice;



























class ObjectViewer
{
public:
	ObjectViewer();
	virtual ~ObjectViewer();


public:
	virtual int drawBiogramWorld(const BiogramWorld& world) const = 0;
	virtual int drawBiogramCage(const BiogramCage& cage) const = 0;
	virtual int drawUnitDetail(const Unit& unit) const = 0;


public: // 각종 Device 그리기
	virtual int draw(const TextPrinterDevice& device) const = 0;
	virtual int draw(const VoidGameDevice& device) const = 0;
};

