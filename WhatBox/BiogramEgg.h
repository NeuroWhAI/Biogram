#pragma once

#include <memory>
#include <vector>

#include "BiogramDNA.h"

class Unit;
class Linker;
class CommandOperator;
template <typename T>
class ObjectPool;



























class BiogramEgg
{
public:
	typedef std::shared_ptr<Unit> UnitPtr;
	typedef std::shared_ptr<Linker> LinkerPtr;
	typedef std::shared_ptr<CommandOperator> CmdOperatorPtr;


public:
	BiogramEgg();
	explicit BiogramEgg(const BiogramDNA& dna);
	virtual ~BiogramEgg();


protected:
	BiogramDNA m_dna;


protected:
	UnitPtr m_pUnitOnProcess;
	LinkerPtr m_pLinkerOnProcess;
	int m_dataFromPast;


public:
	int setDNA(const BiogramDNA& dna);
	int buildBiogram(ObjectPool<Unit>& unitPool,
		ObjectPool<Linker>& linkerPool,
		std::vector<UnitPtr>* pUnitOut,
		std::vector<LinkerPtr>* pFlowLinkerOut,
		std::vector<LinkerPtr>* pParamLinkerOut,
		CmdOperatorPtr pCmdOperator);


protected:
	size_t proceedData(int& sequence,
		std::vector<bool>::const_iterator begin,
		size_t bufferSize,
		ObjectPool<Unit>& unitPool,
		ObjectPool<Linker>& linkerPool,
		std::vector<UnitPtr>* pUnitOut,
		std::vector<LinkerPtr>* pFlowLinkerOut,
		std::vector<LinkerPtr>* pParamLinkerOut,
		CmdOperatorPtr pCmdOperator);
	/*
	* data를 이진수 형식으로 받아들여 정수로 바꾼다.
	* @Return: 변환된 정수 값
	*/
	int toInt(std::vector<bool>::const_iterator begin,
		size_t size);
	/*
	* data의 각 비트를 더해서 정수로 바꾼다.
	* @Return: 변환된 정수 값
	*/
	int bitTotal(std::vector<bool>::const_iterator begin,
		size_t size);
	/*
	* 부분적으로 이진수 형식으로 계산한다음 합산한다.
	* @Return: 변환된 정수 값
	*/
	int toPartialInt(std::vector<bool>::const_iterator begin,
		size_t size);
};

