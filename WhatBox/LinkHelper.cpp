#include "LinkHelper.h"

#include "Unit.h"
#include "Linker.h"

using UnitPtr = LinkHelper::UnitPtr;
using LinkerPtr = LinkHelper::LinkerPtr;



























bool LinkHelper::ConnectFlow(
	LinkerPtr pInLinker,
	UnitPtr pOutUnit)
{
	pInLinker->setOutUnit(pOutUnit);
	pOutUnit->setInLinker(pInLinker);


	return true;
}


bool LinkHelper::ConnectFlow(
	UnitPtr pInUnit,
	LinkerPtr pOutLinker)
{
	pInUnit->setOutLinker(pOutLinker);
	pOutLinker->setInUnit(pInUnit);


	return true;
}


LinkerPtr LinkHelper::ConnectFlow(
	UnitPtr pInUnit,
	UnitPtr pOutUnit)
{
	auto pNewLinker = std::make_shared<Linker>(pInUnit, pOutUnit);

	pInUnit->setOutLinker(pNewLinker);
	pOutUnit->setInLinker(pNewLinker);


	return pNewLinker;
}

//---------------------------------------------------------------

bool LinkHelper::DisconnectFlow(
	LinkerPtr pInLinker,
	UnitPtr pOutUnit)
{
	if (pInLinker->getOutUnit() == pOutUnit
		||
		pOutUnit->getInLinker() == pInLinker)
	{
		pInLinker->setOutUnit(nullptr);
		pOutUnit->setInLinker(nullptr);


		return true;
	}


	return false;
}


bool LinkHelper::DisconnectFlow(
	UnitPtr pInUnit,
	LinkerPtr pOutLinker)
{
	if (pInUnit->getOutLinker() == pOutLinker
		||
		pOutLinker->getInUnit() == pInUnit)
	{
		pInUnit->setOutLinker(nullptr);
		pOutLinker->setInUnit(nullptr);


		return true;
	}


	return false;
}


LinkerPtr LinkHelper::DisconnectFlow(
	UnitPtr pInUnit,
	UnitPtr pOutUnit)
{
	auto disconnectedLinker = pInUnit->getOutLinker();

	if (disconnectedLinker // != nullptr
		&&
		disconnectedLinker == pOutUnit->getInLinker())
	{
		pInUnit->setOutLinker(nullptr);
		pOutUnit->setInLinker(nullptr);

		disconnectedLinker->setInUnit(nullptr);
		disconnectedLinker->setOutUnit(nullptr);


		return disconnectedLinker;
	}


	return nullptr;
}

//###############################################################

bool LinkHelper::ConnectParam(
	UnitPtr pInUnit,
	LinkerPtr pOutLinker)
{
	pInUnit->addOutParamLinker(pOutLinker);
	pOutLinker->setInUnit(pInUnit);


	return true;
}


bool LinkHelper::ConnectParam(
	LinkerPtr pInLinker,
	UnitPtr pOutUnit, int paramIndex)
{
	pInLinker->setOutUnit(pOutUnit);
	pOutUnit->setParamLinker(pInLinker, paramIndex);


	return true;
}


LinkerPtr LinkHelper::ConnectParam(
	UnitPtr pInUnit,
	UnitPtr pOutUnit, int paramIndex)
{
	auto pNewLinker = std::make_shared<Linker>(pInUnit, pOutUnit);

	pInUnit->addOutParamLinker(pNewLinker);
	pOutUnit->setParamLinker(pNewLinker, paramIndex);


	return pNewLinker;
}

//---------------------------------------------------------------

bool LinkHelper::DisconnectParam(
	UnitPtr pInUnit,
	LinkerPtr pOutLinker)
{
	if (pOutLinker->getInUnit() == pInUnit)
	{
		pInUnit->removeOutParamLinker(pOutLinker);
		pOutLinker->setInUnit(nullptr);


		return true;
	}


	return false;
}


bool LinkHelper::DisconnectParam(
	LinkerPtr pInLinker,
	UnitPtr pOutUnit, int paramIndex)
{
	if (pInLinker->getOutUnit() == pOutUnit
		&&
		pOutUnit->getParamLinker(paramIndex) == pInLinker)
	{
		pInLinker->setOutUnit(nullptr);
		pOutUnit->setParamLinker(nullptr, paramIndex);


		return true;
	}


	return false;
}


bool LinkHelper::DisconnectParam(
	LinkerPtr pInLinker,
	UnitPtr pOutUnit)
{
	if (pInLinker->getOutUnit() == pOutUnit)
	{
		pInLinker->setOutUnit(nullptr);


		int paramCount = static_cast<int>(pOutUnit->getParamCount());
		for (int paramIndex = 0; paramIndex < paramCount; ++paramIndex)
		{
			if (pOutUnit->getParamLinker(paramIndex) == pInLinker)
			{
				pOutUnit->setParamLinker(nullptr, paramIndex);
			}
		}


		return true;
	}


	return false;
}


LinkerPtr LinkHelper::DisconnectParam(
	UnitPtr pInUnit,
	UnitPtr pOutUnit, int paramIndex)
{
	auto disconnectedLinker = pOutUnit->getParamLinker(paramIndex);

	if (disconnectedLinker // != nullptr
		&&
		disconnectedLinker->getInUnit() == pInUnit)
	{
		pOutUnit->setParamLinker(nullptr, paramIndex);

		disconnectedLinker->setInUnit(nullptr);
		disconnectedLinker->setOutUnit(nullptr);


		return disconnectedLinker;
	}


	return nullptr;
}

