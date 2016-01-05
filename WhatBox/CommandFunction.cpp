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


	if (param1)
	{
		auto targetUnit = here->getRelativeFlowUnit(
			static_cast<int>(param1->getMemory()));

		// Jump에 성공하면 문제가 없음을 0을 반환함으로서 알림
		if (targetUnit)
		{
			*pNextUnit = targetUnit;


			return 0.0;
		}
	}


	// Jump에 실패했으므로 문제가 되는 정도를 반환함으로서 알림
	return -0.1;
}


CMD_FUNC_DECL(Cmd_JumpIf)
{
	/*
	* [1, *]
	* 1의 값이 0이 아니면 here의 값을 상대좌표로 해서
	  해당 유닛으로 실행포인터를 옮긴다.
	*/


	return Cmd_JumpToIf(pNextUnit, here, here, param1);
}


CMD_FUNC_DECL(Cmd_JumpToIf)
{
	/*
	* [1, 2]
	* 2의 값이 0이 아니면 1의 값을 상대좌표로 해서
	  해당 유닛으로 실행포인터를 옮긴다.
	*/


	if (param1 && param2
		&&
		static_cast<int>(param2->getMemory()) != 0)
	{
		auto targetUnit = here->getRelativeFlowUnit(
			static_cast<int>(param1->getMemory()));

		// Jump에 성공하면 문제가 없음을 0을 반환함으로서 알림
		if (targetUnit)
		{
			*pNextUnit = targetUnit;


			return 0.0;
		}
	}


	// Jump에 실패했으므로 문제가 되는 정도를 반환함으로서 알림
	return -0.1;
}


CMD_FUNC_DECL(Cmd_ReadSharedMem)
{
	/*
	* [1, *]
	* 공유메모리에서 1의 값에 해당하는 주소의 값을
	  here로 읽어온다.
	*/


	return Cmd_ReadSharedMemTo(pNextUnit, here, here, param1);
}


CMD_FUNC_DECL(Cmd_ReadSharedMemTo)
{
	/*
	* [1, 2]
	* 공유메모리에서 2의 값에 해당하는 주소의 값을
	  1로 읽어온다.
	*/


	if (param1 && param2)
	{
		param1->setMemory(readSharedMem(static_cast<int>(
			param2->getMemory())));


		return 0.0;
	}


	return -0.1;
}


CMD_FUNC_DECL(Cmd_WriteSharedMem)
{
	/*
	* [1, *]
	* 공유메모리에서 here의 값에 해당하는 주소에
	  1의 값을 쓴다.
	*/


	return Cmd_WriteSharedMemFrom(pNextUnit, here, here, param1);
}


CMD_FUNC_DECL(Cmd_WriteSharedMemFrom)
{
	/*
	* [1, 2]
	* 공유메모리에서 1의 값에 해당하는 주소에
	  2의 값을 쓴다.
	*/


	if (param1 && param2)
	{
		writeSharedMem(static_cast<int>(param1->getMemory()),
			param2->getMemory());


		return 0.0;
	}


	return -0.1;
}


CMD_FUNC_DECL(Cmd_Move)
{
	/*
	* [1, *]
	* 1의 값을 here의 값에 쓴다.
	*/


	return Cmd_MoveTo(pNextUnit, here, here, param1);
}


CMD_FUNC_DECL(Cmd_MoveTo)
{
	/*
	* [1, 2]
	* 2의 값을 1의 값에 쓴다.
	*/


	if (param1 && param2)
	{
		param1->setMemory(param2->getMemory());


		return 0.0;
	}


	return -0.1;
}


CMD_FUNC_DECL(Cmd_Add)
{
	/*
	* [1, 2]
	* 1의 값과 2의 값을 더한 값을 here에 쓴다.
	*/


	if (param1 && param2)
	{
		here->setMemory(
			param1->getMemory() + param2->getMemory());


		return 0.0;
	}


	return -0.1;
}


CMD_FUNC_DECL(Cmd_AddTo)
{
	/*
	* [1, 2]
	* 1의 값과 2의 값을 더한 값을 1에 쓴다.
	*/


	if (param1 && param2)
	{
		param1->setMemory(
			param1->getMemory() + param2->getMemory());


		return 0.0;
	}


	return -0.1;
}


CMD_FUNC_DECL(Cmd_Sub)
{
	/*
	* [1, 2]
	* 1의 값에서 2의 값을 뺀 값을 here에 쓴다.
	*/


	if (param1 && param2)
	{
		here->setMemory(
			param1->getMemory() - param2->getMemory());


		return 0.0;
	}


	return -0.1;
}


CMD_FUNC_DECL(Cmd_SubTo)
{
	/*
	* [1, 2]
	* 1의 값에 2의 값을 뺀 값을 1에 쓴다.
	*/


	if (param1 && param2)
	{
		param1->setMemory(
			param1->getMemory() - param2->getMemory());


		return 0.0;
	}


	return -0.1;
}

