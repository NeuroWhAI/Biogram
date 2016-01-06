#pragma once

#include "BiogramCage.h"

#include "Utility.h"

#include "BiogramDNA.h"



























class BiogramLab : public BiogramCage
{
public:
	BiogramLab();
	virtual ~BiogramLab();


protected:
	std::shared_ptr<Unit> m_pSelectedUnit;
	BiogramDNA m_currentDNA;
	bool m_bLoop;


public:
	virtual int update(double timeSpeed) override;


protected:
	int touchDownCallback(Utility::Point cursor);
	int touchPressCallback(Utility::Point cursor);
	int touchUpCallback(Utility::Point cursor);


protected:
	std::shared_ptr<Unit> getUnitContain(Utility::Point point) const;
	int clear();
	int initBiogram(BiogramDNA dna);
};

