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
	* data�� ������ �������� �޾Ƶ鿩 ������ �ٲ۴�.
	* @Return: ��ȯ�� ���� ��
	*/
	int toInt(std::vector<bool>::const_iterator begin,
		size_t size);
	/*
	* data�� �� ��Ʈ�� ���ؼ� ������ �ٲ۴�.
	* @Return: ��ȯ�� ���� ��
	*/
	int bitTotal(std::vector<bool>::const_iterator begin,
		size_t size);
	/*
	* �κ������� ������ �������� ����Ѵ��� �ջ��Ѵ�.
	* @Return: ��ȯ�� ���� ��
	*/
	int toPartialInt(std::vector<bool>::const_iterator begin,
		size_t size);
};

