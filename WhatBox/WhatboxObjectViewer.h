#pragma once

#include "ObjectViewer.h"

#include <vector>
#include <string>



























class WhatboxObjectViewer : public ObjectViewer
{
public:
	WhatboxObjectViewer();
	virtual ~WhatboxObjectViewer();


protected:
	std::vector<std::wstring> m_cmdNameList;


public:
	virtual int drawBiogramWorld(const BiogramWorld& world) const override;
	virtual int drawBiogramCage(const BiogramCage& cage) const override;
	virtual int drawUnitDetail(const Unit& unit) const override;


public:
	virtual int draw(const TextPrinterDevice& device) const override;
};

