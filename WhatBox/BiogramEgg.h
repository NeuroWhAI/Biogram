#pragma once

#include <memory>
#include <vector>

#include "BiogramDNA.h"

class Unit;
class Linker;



























class BiogramEgg
{
public:
	typedef std::shared_ptr<Unit> UnitPtr;
	typedef std::shared_ptr<Linker> LinkerPtr;


public:
	BiogramEgg();
	explicit BiogramEgg(const BiogramDNA& dna);
	virtual ~BiogramEgg();


protected:
	BiogramDNA m_dna;


protected:
	UnitPtr m_pUnitOnProcess;
	LinkerPtr m_pLinkerOnProcess;


public:
	int setDNA(const BiogramDNA& dna);
	int buildBiogram(std::vector<UnitPtr>* pUnitOut,
		std::vector<LinkerPtr>* pFlowLinkerOut,
		std::vector<LinkerPtr>* pParamLinkerOut);


protected:
	size_t proceedData(int& sequence,
		const std::vector<bool>& data,
		std::vector<UnitPtr>* pUnitOut,
		std::vector<LinkerPtr>* pFlowLinkerOut,
		std::vector<LinkerPtr>* pParamLinkerOut);
	int toInt(const std::vector<bool>& data);
};

