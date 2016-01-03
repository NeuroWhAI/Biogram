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


	auto targetUnit = here->getRelativeFlowUnit(
		static_cast<int>(param1->getMemory()));

	// Jump�� �����ϸ� ������ ������ 0�� ��ȯ�����μ� �˸�
	if (targetUnit)
	{
		*pNextUnit = targetUnit;


		return 0.0;
	}


	// Jump�� ���������Ƿ� ������ �Ǵ� ������ ��ȯ�����μ� �˸�
	return -0.1;
}

