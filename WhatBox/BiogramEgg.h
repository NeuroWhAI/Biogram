#pragma once

#include <memory>
#include <vector>

#include "BiogramDNA.h"

class Unit;
class Linker;
class CommandOperator;



























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
	int buildBiogram(std::vector<UnitPtr>* pUnitOut,
		std::vector<LinkerPtr>* pFlowLinkerOut,
		std::vector<LinkerPtr>* pParamLinkerOut,
		CmdOperatorPtr pCmdOperator);


protected:
	size_t proceedData(int& sequence,
		const std::vector<bool>& data,
		std::vector<UnitPtr>* pUnitOut,
		std::vector<LinkerPtr>* pFlowLinkerOut,
		std::vector<LinkerPtr>* pParamLinkerOut,
		CmdOperatorPtr pCmdOperator);
	/*
	* data�� ������ �������� �޾Ƶ鿩 ������ �ٲ۴�.
	* @Return: ��ȯ�� ���� ��
	*/
	int toInt(const std::vector<bool>& data);
	/*
	* data�� �� ��Ʈ�� ���ؼ� ������ �ٲ۴�.
	* @Return: ��ȯ�� ���� ��
	*/
	int bitTotal(const std::vector<bool>& data);
};
