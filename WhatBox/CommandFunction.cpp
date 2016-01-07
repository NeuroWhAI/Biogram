#define DO_NOT_DELETE_CMD_FUNC_DEFINE // CMD_FUNC�� CMD_FUNC_PARAM�� undef���� �ʵ��� ��.
#include "CommandOperator.h"

#include "Unit.h"
#include "Linker.h"

#include <numeric>

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


CMD_FUNC_DECL(Cmd_JumpIfNot)
{
	/*
	* [1, *]
	* 1�� ���� 0�̸�
	  here�� ���� �����ǥ�� �Ͽ� Jump�Ѵ�.
	*/


	return Cmd_JumpToIfNot(pNextUnit, here, here, param1);
}


CMD_FUNC_DECL(Cmd_JumpToIfNot)
{
	/*
	* [1, 2]
	* 2�� ���� 0�̸�
	  1�� ���� �����ǥ�� �Ͽ� Jump�Ѵ�.
	*/


	if (param1 && param2)
	{
		if (param2->getMemory() <= std::numeric_limits<double>::epsilon())
		{
			auto targetUnit = here->getRelativeFlowUnit(
				static_cast<int>(param1->getMemory()));

			if (targetUnit)
			{
				*pNextUnit = targetUnit;
			}
		}


		return 0.0;
	}


	return -0.1;
}


CMD_FUNC_DECL(Cmd_JumpIfBig)
{
	/*
	* [1, 2]
	* 1�� ���� 2�� ������ ũ��
	  here�� ���� �����ǥ�� �Ͽ� Jump�Ѵ�.
	*/


	if (param1 && param2)
	{
		if (param1->getMemory() > param2->getMemory())
		{
			auto targetUnit = here->getRelativeFlowUnit(
				static_cast<int>(here->getMemory()));

			if (targetUnit)
			{
				*pNextUnit = targetUnit;


				return 0.0;
			}
		}
	}


	return -0.1;
}


CMD_FUNC_DECL(Cmd_JumpToIfBig)
{
	/*
	* [1, 2]
	* 1�� ���� 2�� ������ ũ��
	  1�� ���� �����ǥ�� �Ͽ� Jump�Ѵ�.
	*/


	if (param1 && param2)
	{
		if (param1->getMemory() > param2->getMemory())
		{
			auto targetUnit = here->getRelativeFlowUnit(
				static_cast<int>(param1->getMemory()));

			if (targetUnit)
			{
				*pNextUnit = targetUnit;


				return 0.0;
			}
		}
	}


	return -0.1;
}


CMD_FUNC_DECL(Cmd_JumpIfSmall)
{
	/*
	* [1, 2]
	* 1�� ���� 2�� ������ ������
	  here�� ���� �����ǥ�� �Ͽ� Jump�Ѵ�.
	*/


	if (param1 && param2)
	{
		if (param1->getMemory() < param2->getMemory())
		{
			auto targetUnit = here->getRelativeFlowUnit(
				static_cast<int>(here->getMemory()));

			if (targetUnit)
			{
				*pNextUnit = targetUnit;


				return 0.0;
			}
		}
	}


	return -0.1;
}


CMD_FUNC_DECL(Cmd_JumpToIfSmall)
{
	/*
	* [1, 2]
	* 1�� ���� 2�� ������ ������
	  1�� ���� �����ǥ�� �Ͽ� Jump�Ѵ�.
	*/


	if (param1 && param2)
	{
		if (param1->getMemory() < param2->getMemory())
		{
			auto targetUnit = here->getRelativeFlowUnit(
				static_cast<int>(param1->getMemory()));

			if (targetUnit)
			{
				*pNextUnit = targetUnit;


				return 0.0;
			}
		}
	}


	return -0.1;
}


CMD_FUNC_DECL(Cmd_JumpIfBigEqual)
{
	/*
	* [1, 2]
	* 1�� ���� 2�� ������ ũ�ų� ������
	  here�� ���� �����ǥ�� �Ͽ� Jump�Ѵ�.
	*/


	if (param1 && param2)
	{
		if (param1->getMemory() >= param2->getMemory())
		{
			auto targetUnit = here->getRelativeFlowUnit(
				static_cast<int>(here->getMemory()));

			if (targetUnit)
			{
				*pNextUnit = targetUnit;


				return 0.0;
			}
		}
	}


	return -0.1;
}


CMD_FUNC_DECL(Cmd_JumpToIfBigEqual)
{
	/*
	* [1, 2]
	* 1�� ���� 2�� ������ ũ�ų� ������
	  1�� ���� �����ǥ�� �Ͽ� Jump�Ѵ�.
	*/


	if (param1 && param2)
	{
		if (param1->getMemory() >= param2->getMemory())
		{
			auto targetUnit = here->getRelativeFlowUnit(
				static_cast<int>(param1->getMemory()));

			if (targetUnit)
			{
				*pNextUnit = targetUnit;


				return 0.0;
			}
		}
	}


	return -0.1;
}


CMD_FUNC_DECL(Cmd_JumpIfSmallEqual)
{
	/*
	* [1, 2]
	* 1�� ���� 2�� ������ �۰ų� ������
	  here�� ���� �����ǥ�� �Ͽ� Jump�Ѵ�.
	*/


	if (param1 && param2)
	{
		if (param1->getMemory() <= param2->getMemory())
		{
			auto targetUnit = here->getRelativeFlowUnit(
				static_cast<int>(here->getMemory()));

			if (targetUnit)
			{
				*pNextUnit = targetUnit;


				return 0.0;
			}
		}
	}


	return -0.1;
}


CMD_FUNC_DECL(Cmd_JumpToIfSmallEqual)
{
	/*
	* [1, 2]
	* 1�� ���� 2�� ������ �۰ų� ������
	  1�� ���� �����ǥ�� �Ͽ� Jump�Ѵ�.
	*/


	if (param1 && param2)
	{
		if (param1->getMemory() <= param2->getMemory())
		{
			auto targetUnit = here->getRelativeFlowUnit(
				static_cast<int>(param1->getMemory()));

			if (targetUnit)
			{
				*pNextUnit = targetUnit;


				return 0.0;
			}
		}
	}


	return -0.1;
}


CMD_FUNC_DECL(Cmd_JumpIfEqual)
{
	/*
	* [1, *]
	* here�� ���� 1�� ���� ������
	  1�� ���� �����ǥ�� �Ͽ� Jump�Ѵ�.
	*/


	if (param1)
	{
		if (std::abs(param1->getMemory() - here->getMemory())
			<=
			std::numeric_limits<double>::epsilon())
		{
			auto targetUnit = here->getRelativeFlowUnit(
				static_cast<int>(param1->getMemory()));

			if (targetUnit)
			{
				*pNextUnit = targetUnit;
			}
		}


		return 0.0;
	}


	return -0.1;
}


CMD_FUNC_DECL(Cmd_JumpToIfEqual)
{
	/*
	* [1, 2]
	* 1�� ���� 2�� ���� ������
	  here�� ���� �����ǥ�� �Ͽ� Jump�Ѵ�.
	*/


	if (param1 && param2)
	{
		if (std::abs(param1->getMemory() - param2->getMemory())
			<=
			std::numeric_limits<double>::epsilon())
		{
			auto targetUnit = here->getRelativeFlowUnit(
				static_cast<int>(here->getMemory()));

			if (targetUnit)
			{
				*pNextUnit = targetUnit;
			}
		}


		return 0.0;
	}


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


CMD_FUNC_DECL(Cmd_ReadCageMem)
{
	/*
	* [1, *]
	* �����޸𸮿��� 1�� ���� �ش��ϴ� �ּ��� ����
	  here�� �о�´�.
	*/


	return Cmd_ReadCageMemTo(pNextUnit, here, here, param1);
}


CMD_FUNC_DECL(Cmd_ReadCageMemTo)
{
	/*
	* [1, 2]
	* �����޸𸮿��� 2�� ���� �ش��ϴ� �ּ��� ����
	  1�� �о�´�.
	*/


	if (param1 && param2)
	{
		param1->setMemory(readCageMem(static_cast<int>(
			param2->getMemory())));


		return 0.0;
	}


	return -0.1;
}


CMD_FUNC_DECL(Cmd_WriteCageMem)
{
	/*
	* [1, *]
	* �����޸𸮿��� here�� ���� �ش��ϴ� �ּҿ�
	  1�� ���� ����.
	*/


	return Cmd_WriteCageMemFrom(pNextUnit, here, here, param1);
}


CMD_FUNC_DECL(Cmd_WriteCageMemFrom)
{
	/*
	* [1, 2]
	* �����޸𸮿��� 1�� ���� �ش��ϴ� �ּҿ�
	  2�� ���� ����.
	*/


	if (param1 && param2)
	{
		writeCageMem(static_cast<int>(param1->getMemory()),
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


CMD_FUNC_DECL(Cmd_Increase)
{
	/*
	* [*, *]
	* here�� ���� 1 ������Ų��.
	*/


	here->addMemory(1.0);


	return 0.0;
}


CMD_FUNC_DECL(Cmd_IncreaseThis)
{
	/*
	* [1, *]
	* 1�� ���� 1 ������Ų��.
	*/


	if (param1)
	{
		param1->addMemory(1.0);


		return 0.0;
	}


	return -0.1;
}


CMD_FUNC_DECL(Cmd_Decrease)
{
	/*
	* [*, *]
	* here�� ���� 1 ���ҽ�Ų��.
	*/


	here->addMemory(-1.0);


	return 0.0;
}


CMD_FUNC_DECL(Cmd_DecreaseThis)
{
	/*
	* [1, *]
	* 1�� ���� 1 ���ҽ�Ų��.
	*/


	if (param1)
	{
		param1->addMemory(-1.0);


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


CMD_FUNC_DECL(Cmd_Swap)
{
	/*
	* [1, *]
	* 1�� ���� here�� ���� ���� �ٲ۴�.
	*/


	return Cmd_SwapBoth(pNextUnit, here, here, param1);
}


CMD_FUNC_DECL(Cmd_SwapBoth)
{
	/*
	* [1, 2]
	* 1�� ���� 2�� ���� ���� �ٲ۴�.
	*/


	if (param1 && param2)
	{
		double temp = param2->getMemory();
		param2->setMemory(param1->getMemory());
		param1->setMemory(temp);


		return 0.0;
	}


	return -0.1;
}


CMD_FUNC_DECL(Cmd_Negative)
{
	/*
	* [*, *]
	* here�� ���� ��ȣ�� ������Ų��.
	*/


	return Cmd_NegativeThis(pNextUnit, here, here, nullptr);
}


CMD_FUNC_DECL(Cmd_NegativeThis)
{
	/*
	* [1, *]
	* 1�� ���� ��ȣ�� ������Ų��.
	*/


	if (param1)
	{
		param1->setMemory(-param1->getMemory());


		return 0.0;
	}


	return -0.1;
}


CMD_FUNC_DECL(Cmd_Multiply)
{
	/*
	* [1, *]
	* here�� ���� 1�� ���� ���� ���� here�� ����.
	*/


	return Cmd_MultiplyBoth(pNextUnit, here, here, param1);
}


CMD_FUNC_DECL(Cmd_MultiplyBoth)
{
	/*
	* [1, 2]
	* 1�� ���� 2�� ���� ���� ���� 1�� ����.
	*/


	if (param1 && param2)
	{
		param1->setMemory(param1->getMemory() * param2->getMemory());


		return 0.0;
	}


	return -0.1;
}


CMD_FUNC_DECL(Cmd_Divide)
{
	/*
	* [1, *]
	* here�� ���� 1�� ���� ���� ���� here�� ����.
	*/


	return Cmd_MultiplyBoth(pNextUnit, here, here, param1);
}


CMD_FUNC_DECL(Cmd_DivideBoth)
{
	/*
	* [1, 2]
	* 1�� ���� 2�� ���� ���� ���� 1�� ����.
	*/


	if (param1 && param2)
	{
		double under = param2->getMemory();

		if(std::abs(under) > std::numeric_limits<double>::epsilon())
			param1->setMemory(param1->getMemory() / under);
		else return -1.0; // 0���� ������ ��Ȳ�� �־�


		return 0.0;
	}


	return -0.1;
}


CMD_FUNC_DECL(Cmd_Not)
{
	/*
	* [*, *]
	* here�� ���� �� ���� ���� here�� ����.
	*/


	return Cmd_NotThis(pNextUnit, here, here, nullptr);
}


CMD_FUNC_DECL(Cmd_NotThis)
{
	/*
	* [1, *]
	* 1�� ���� �� ���� ���� 1�� ����.
	*/


	if (param1)
	{
		param1->setMemory(
			(std::abs(param1->getMemory()) > std::numeric_limits<double>::epsilon()) ? 
			0.0 : 1.0);


		return 0.0;
	}


	return -0.1;
}


CMD_FUNC_DECL(Cmd_Or)
{
	/*
	* [1, *]
	* here�� ���� 1�� ���� ������ ���� here�� ����.
	*/


	return Cmd_OrBoth(pNextUnit, here, here, param1);
}


CMD_FUNC_DECL(Cmd_OrBoth)
{
	/*
	* [1, 2]
	* 1�� ���� 2�� ���� ������ ���� 1�� ����.
	*/


	if (param1 && param2)
	{
		if (std::abs(param1->getMemory()) > std::numeric_limits<double>::epsilon()
			||
			std::abs(param2->getMemory()) > std::numeric_limits<double>::epsilon())
		{
			param1->setMemory(1.0);
		}
		else
		{
			param1->setMemory(0.0);
		}


		return 0.0;
	}


	return -0.1;
}


CMD_FUNC_DECL(Cmd_And)
{
	/*
	* [1, *]
	* here�� ���� 1�� ���� ������ ���� here�� ����.
	*/


	return Cmd_AndBoth(pNextUnit, here, here, param1);
}


CMD_FUNC_DECL(Cmd_AndBoth)
{
	/*
	* [1, 2]
	* 1�� ���� 2�� ���� ������ ���� 1�� ����.
	*/


	if (param1 && param2)
	{
		if (std::abs(param1->getMemory()) > std::numeric_limits<double>::epsilon()
			&&
			std::abs(param2->getMemory()) > std::numeric_limits<double>::epsilon())
		{
			param1->setMemory(1.0);
		}
		else
		{
			param1->setMemory(0.0);
		}


		return 0.0;
	}


	return -0.1;
}


CMD_FUNC_DECL(Cmd_Xor)
{
	/*
	* [1, *]
	* here�� ���� 1�� ���� ��Ÿ�� ������ ���� here�� ����.
	*/


	return Cmd_XorBoth(pNextUnit, here, here, param1);
}


CMD_FUNC_DECL(Cmd_XorBoth)
{
	/*
	* [1, 2]
	* 1�� ���� 2�� ���� ��Ÿ�� ������ ���� 1�� ����.
	*/


	if (param1 && param2)
	{
		if ((std::abs(param1->getMemory()) > std::numeric_limits<double>::epsilon())
			!=
			(std::abs(param2->getMemory()) > std::numeric_limits<double>::epsilon()))
		{
			param1->setMemory(1.0);
		}
		else
		{
			param1->setMemory(0.0);
		}


		return 0.0;
	}


	return -0.1;
}


CMD_FUNC_DECL(Cmd_GetTemperature)
{
	/*
	* [1, *]
	* 1�� �µ��� here�� ���� ����.
	*/


	return Cmd_GetTemperatureTo(pNextUnit, here, here, param1);
}


CMD_FUNC_DECL(Cmd_GetTemperatureTo)
{
	/*
	* [1, 2]
	* 2�� �µ��� 1�� ���� ����.
	*/


	if (param1 && param2)
	{
		param1->setMemory(param2->getTemperature());


		return 0.0;
	}


	return -0.1;
}


CMD_FUNC_DECL(Cmd_GetMass)
{
	/*
	* [1, *]
	* 1�� ������ here�� ���� ����.
	*/


	return Cmd_GetMassTo(pNextUnit, here, here, param1);
}


CMD_FUNC_DECL(Cmd_GetMassTo)
{
	/*
	* [1, 2]
	* 2�� ������ 1�� ���� ����.
	*/


	if (param1 && param2)
	{
		param1->setMemory(param2->getMass());


		return 0.0;
	}


	return -0.1;
}


CMD_FUNC_DECL(Cmd_GetRadius)
{
	/*
	* [1, *]
	* 1�� �������� here�� ���� ����.
	*/


	return Cmd_GetRadiusTo(pNextUnit, here, here, param1);
}


CMD_FUNC_DECL(Cmd_GetRadiusTo)
{
	/*
	* [1, 2]
	* 2�� �������� 1�� ���� ����.
	*/


	if (param1 && param2)
	{
		param1->setMemory(param2->getRadius());


		return 0.0;
	}


	return -0.1;
}


CMD_FUNC_DECL(Cmd_GetLocation)
{
	/*
	* [1, 2]
	* here�� x��ġ�� 1�� ���� ����
	  y��ġ�� 2�� ���� ����.
	*/


	if (param1 && param2)
	{
		auto location = here->getLocation();

		param1->setMemory(location.x);
		param2->setMemory(location.y);


		return 0.0;
	}


	return -0.1;
}


CMD_FUNC_DECL(Cmd_GetLocationThis)
{
	/*
	* [1, 2]
	* here�� ���� ����Ű�� Unit�� x��ġ�� 1�� ���� ����
	  y��ġ�� 2�� ���� ����.
	*/


	if (param1 && param2)
	{
		auto target = here->getRelativeFlowUnit(
			static_cast<int>(here->getMemory()));

		if (target)
		{
			auto location = target->getLocation();

			param1->setMemory(location.x);
			param2->setMemory(location.y);


			return 0.0;
		}
	}


	return -0.1;
}


CMD_FUNC_DECL(Cmd_GetTime)
{
	/*
	* [*, *]
	* ���� �ð��� here�� ���� ����.
	*/


	return Cmd_GetTimeTo(pNextUnit, here, here, nullptr);
}


CMD_FUNC_DECL(Cmd_GetTimeTo)
{
	/*
	* [1, *]
	* ���� �ð��� 1�� ���� ����.
	*/


	if (param1)
	{
		param1->setMemory(m_elapsedTime);


		return 0.0;
	}


	return -0.1;
}


CMD_FUNC_DECL(Cmd_GetScore)
{
	/*
	* [*, *]
	* ���յ� ������ here�� ���� ����.
	*/


	return Cmd_GetScoreTo(pNextUnit, here, here, nullptr);
}


CMD_FUNC_DECL(Cmd_GetScoreTo)
{
	/*
	* [1, *]
	* ���յ� ������ 1�� ���� ����.
	*/


	if (param1)
	{
		param1->setMemory(m_geneScore);


		return 0.0;
	}


	return -0.1;
}

