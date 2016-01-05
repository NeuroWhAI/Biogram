#define DO_NOT_DELETE_CMD_FUNC_DEFINE // CMD_FUNC�� CMD_FUNC_PARAM�� undef���� �ʵ��� ��.
#include "CommandOperator.h"

#include "Unit.h"
#include "Linker.h"

#define CMD_FUNC_DECL(name) double CommandOperator::name CMD_FUNC_PARAM



























CMD_FUNC_DECL(Cmd_None)
{
	/* 
	* [*, *]
	* �ƹ� �ϵ� ����.
	* ���� �޸� �뷮�� �ø��� �뵵
	*/


	return 0.0;
}


CMD_FUNC_DECL(Cmd_Jump)
{
	/* 
	* [*, *]
	* here�� ����� ���� �����ǥ�� Ȱ���ؼ�
	  �ش� �������� ���������͸� �ű��.
	*/


	return Cmd_JumpTo(pNextUnit, here, here, nullptr);
}


CMD_FUNC_DECL(Cmd_JumpTo)
{
	/*
	* [1, *]
	* 1�� ����� ���� �����ǥ�� Ȱ���ؼ�
	  �ش� �������� ���������͸� �ű��.
	*/


	if (param1)
	{
		auto targetUnit = here->getRelativeFlowUnit(
			static_cast<int>(param1->getMemory()));

		// Jump�� �����ϸ� ������ ������ 0�� ��ȯ�����μ� �˸�
		if (targetUnit)
		{
			*pNextUnit = targetUnit;


			return 0.0;
		}
	}


	// Jump�� ���������Ƿ� ������ �Ǵ� ������ ��ȯ�����μ� �˸�
	return -0.1;
}


CMD_FUNC_DECL(Cmd_JumpIf)
{
	/*
	* [1, *]
	* 1�� ���� 0�� �ƴϸ� here�� ���� �����ǥ�� �ؼ�
	  �ش� �������� ���������͸� �ű��.
	*/


	return Cmd_JumpToIf(pNextUnit, here, here, param1);
}


CMD_FUNC_DECL(Cmd_JumpToIf)
{
	/*
	* [1, 2]
	* 2�� ���� 0�� �ƴϸ� 1�� ���� �����ǥ�� �ؼ�
	  �ش� �������� ���������͸� �ű��.
	*/


	if (param1 && param2
		&&
		static_cast<int>(param2->getMemory()) != 0)
	{
		auto targetUnit = here->getRelativeFlowUnit(
			static_cast<int>(param1->getMemory()));

		// Jump�� �����ϸ� ������ ������ 0�� ��ȯ�����μ� �˸�
		if (targetUnit)
		{
			*pNextUnit = targetUnit;


			return 0.0;
		}
	}


	// Jump�� ���������Ƿ� ������ �Ǵ� ������ ��ȯ�����μ� �˸�
	return -0.1;
}


CMD_FUNC_DECL(Cmd_ReadSharedMem)
{
	/*
	* [1, *]
	* �����޸𸮿��� 1�� ���� �ش��ϴ� �ּ��� ����
	  here�� �о�´�.
	*/


	return Cmd_ReadSharedMemTo(pNextUnit, here, here, param1);
}


CMD_FUNC_DECL(Cmd_ReadSharedMemTo)
{
	/*
	* [1, 2]
	* �����޸𸮿��� 2�� ���� �ش��ϴ� �ּ��� ����
	  1�� �о�´�.
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
	* �����޸𸮿��� here�� ���� �ش��ϴ� �ּҿ�
	  1�� ���� ����.
	*/


	return Cmd_WriteSharedMemFrom(pNextUnit, here, here, param1);
}


CMD_FUNC_DECL(Cmd_WriteSharedMemFrom)
{
	/*
	* [1, 2]
	* �����޸𸮿��� 1�� ���� �ش��ϴ� �ּҿ�
	  2�� ���� ����.
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
	* 1�� ���� here�� ���� ����.
	*/


	return Cmd_MoveTo(pNextUnit, here, here, param1);
}


CMD_FUNC_DECL(Cmd_MoveTo)
{
	/*
	* [1, 2]
	* 2�� ���� 1�� ���� ����.
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
	* 1�� ���� 2�� ���� ���� ���� here�� ����.
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
	* 1�� ���� 2�� ���� ���� ���� 1�� ����.
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
	* 1�� ������ 2�� ���� �� ���� here�� ����.
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
	* 1�� ���� 2�� ���� �� ���� 1�� ����.
	*/


	if (param1 && param2)
	{
		param1->setMemory(
			param1->getMemory() - param2->getMemory());


		return 0.0;
	}


	return -0.1;
}

