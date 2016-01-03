#define DO_NOT_DELETE_CMD_FUNC_DEFINE // CMD_FUNC와 CMD_FUNC_PARAM가 undef되지 않도록 함.
#include "CommandOperator.h"

#include "Unit.h"
#include "Linker.h"

#define CMD_FUNC_DECL(name) double CommandOperator::name CMD_FUNC_PARAM



























CMD_FUNC_DECL(Cmd_None)
{
	/* 
	* [*, *]
	* 아무 일도 안함.
	* 그저 메모리 용량을 늘리는 용도
	*/


	return 0.0;
}


CMD_FUNC_DECL(Cmd_Jump)
{
	/* 
	* [*, *]
	* here에 저장된 값을 상대좌표로 활용해서
	  해당 유닛으로 실행포인터를 옮긴다.
	*/


	return Cmd_JumpTo(pNextUnit, here, here, nullptr);
}


CMD_FUNC_DECL(Cmd_JumpTo)
{
	/*
	* [1, *]
	* 1에 저장된 값을 상대좌표로 활용해서
	  해당 유닛으로 실행포인터를 옮긴다.
	*/


	auto targetUnit = here->getRelativeFlowUnit(
		static_cast<int>(param1->getMemory()));

	// Jump에 성공하면 문제가 없음을 0을 반환함으로서 알림
	if (targetUnit)
	{
		*pNextUnit = targetUnit;


		return 0.0;
	}


	// Jump에 실패했으므로 문제가 되는 정도를 반환함으로서 알림
	return -0.1;
}

