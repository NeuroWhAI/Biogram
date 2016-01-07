#define DO_NOT_DELETE_CMD_FUNC_DEFINE // CMD_FUNC와 CMD_FUNC_PARAM가 undef되지 않도록 함.
#include "CommandOperator.h"

#include "Unit.h"
#include "Linker.h"

#include <numeric>

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


CMD_FUNC_DECL(Cmd_JumpIfNot)
{
	/*
	* [1, *]
	* 1의 값이 0이면
	  here의 값을 상대좌표로 하여 Jump한다.
	*/


	return Cmd_JumpToIfNot(pNextUnit, here, here, param1);
}


CMD_FUNC_DECL(Cmd_JumpToIfNot)
{
	/*
	* [1, 2]
	* 2의 값이 0이면
	  1의 값을 상대좌표로 하여 Jump한다.
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
	* 1의 값이 2의 값보다 크면
	  here의 값을 상대좌표로 하여 Jump한다.
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
	* 1의 값이 2의 값보다 크면
	  1의 값을 상대좌표로 하여 Jump한다.
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
	* 1의 값이 2의 값보다 작으면
	  here의 값을 상대좌표로 하여 Jump한다.
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
	* 1의 값이 2의 값보다 작으면
	  1의 값을 상대좌표로 하여 Jump한다.
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
	* 1의 값이 2의 값보다 크거나 같으면
	  here의 값을 상대좌표로 하여 Jump한다.
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
	* 1의 값이 2의 값보다 크거나 같으면
	  1의 값을 상대좌표로 하여 Jump한다.
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
	* 1의 값이 2의 값보다 작거나 같으면
	  here의 값을 상대좌표로 하여 Jump한다.
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
	* 1의 값이 2의 값보다 작거나 같으면
	  1의 값을 상대좌표로 하여 Jump한다.
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
	* here의 값과 1의 값이 같으면
	  1의 값을 상대좌표로 하여 Jump한다.
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
	* 1의 값과 2의 값이 같으면
	  here의 값을 상대좌표로 하여 Jump한다.
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


CMD_FUNC_DECL(Cmd_ReadCageMem)
{
	/*
	* [1, *]
	* 지역메모리에서 1의 값에 해당하는 주소의 값을
	  here로 읽어온다.
	*/


	return Cmd_ReadCageMemTo(pNextUnit, here, here, param1);
}


CMD_FUNC_DECL(Cmd_ReadCageMemTo)
{
	/*
	* [1, 2]
	* 지역메모리에서 2의 값에 해당하는 주소의 값을
	  1로 읽어온다.
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
	* 지역메모리에서 here의 값에 해당하는 주소에
	  1의 값을 쓴다.
	*/


	return Cmd_WriteCageMemFrom(pNextUnit, here, here, param1);
}


CMD_FUNC_DECL(Cmd_WriteCageMemFrom)
{
	/*
	* [1, 2]
	* 지역메모리에서 1의 값에 해당하는 주소에
	  2의 값을 쓴다.
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


CMD_FUNC_DECL(Cmd_Increase)
{
	/*
	* [*, *]
	* here의 값을 1 증가시킨다.
	*/


	here->addMemory(1.0);


	return 0.0;
}


CMD_FUNC_DECL(Cmd_IncreaseThis)
{
	/*
	* [1, *]
	* 1의 값을 1 증가시킨다.
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
	* here의 값을 1 감소시킨다.
	*/


	here->addMemory(-1.0);


	return 0.0;
}


CMD_FUNC_DECL(Cmd_DecreaseThis)
{
	/*
	* [1, *]
	* 1의 값을 1 감소시킨다.
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


CMD_FUNC_DECL(Cmd_Swap)
{
	/*
	* [1, *]
	* 1의 값과 here의 값을 서로 바꾼다.
	*/


	return Cmd_SwapBoth(pNextUnit, here, here, param1);
}


CMD_FUNC_DECL(Cmd_SwapBoth)
{
	/*
	* [1, 2]
	* 1의 값과 2의 값을 서로 바꾼다.
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
	* here의 값의 부호를 반전시킨다.
	*/


	return Cmd_NegativeThis(pNextUnit, here, here, nullptr);
}


CMD_FUNC_DECL(Cmd_NegativeThis)
{
	/*
	* [1, *]
	* 1의 값의 부호를 반전시킨다.
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
	* here의 값과 1의 값을 곱한 값을 here에 쓴다.
	*/


	return Cmd_MultiplyBoth(pNextUnit, here, here, param1);
}


CMD_FUNC_DECL(Cmd_MultiplyBoth)
{
	/*
	* [1, 2]
	* 1의 값과 2의 값을 곱한 값을 1에 쓴다.
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
	* here의 값에 1의 값을 나눈 값을 here에 쓴다.
	*/


	return Cmd_MultiplyBoth(pNextUnit, here, here, param1);
}


CMD_FUNC_DECL(Cmd_DivideBoth)
{
	/*
	* [1, 2]
	* 1의 값에 2의 값을 나눈 값을 1에 쓴다.
	*/


	if (param1 && param2)
	{
		double under = param2->getMemory();

		if(std::abs(under) > std::numeric_limits<double>::epsilon())
			param1->setMemory(param1->getMemory() / under);
		else return -1.0; // 0으로 나누는 상황은 최악


		return 0.0;
	}


	return -0.1;
}


CMD_FUNC_DECL(Cmd_Not)
{
	/*
	* [*, *]
	* here의 값을 논리 반전 시켜 here에 쓴다.
	*/


	return Cmd_NotThis(pNextUnit, here, here, nullptr);
}


CMD_FUNC_DECL(Cmd_NotThis)
{
	/*
	* [1, *]
	* 1의 값을 논리 반전 시켜 1에 쓴다.
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
	* here의 값과 1의 값을 논리합한 값을 here에 쓴다.
	*/


	return Cmd_OrBoth(pNextUnit, here, here, param1);
}


CMD_FUNC_DECL(Cmd_OrBoth)
{
	/*
	* [1, 2]
	* 1의 값과 2의 값을 논리합한 값을 1에 쓴다.
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
	* here의 값과 1의 값을 논리곱한 값을 here에 쓴다.
	*/


	return Cmd_AndBoth(pNextUnit, here, here, param1);
}


CMD_FUNC_DECL(Cmd_AndBoth)
{
	/*
	* [1, 2]
	* 1의 값과 2의 값을 논리곱한 값을 1에 쓴다.
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
	* here의 값과 1의 값을 배타적 논리합한 값을 here에 쓴다.
	*/


	return Cmd_XorBoth(pNextUnit, here, here, param1);
}


CMD_FUNC_DECL(Cmd_XorBoth)
{
	/*
	* [1, 2]
	* 1의 값과 2의 값을 배타적 논리합한 값을 1에 쓴다.
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
	* 1의 온도를 here의 값에 쓴다.
	*/


	return Cmd_GetTemperatureTo(pNextUnit, here, here, param1);
}


CMD_FUNC_DECL(Cmd_GetTemperatureTo)
{
	/*
	* [1, 2]
	* 2의 온도를 1의 값에 쓴다.
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
	* 1의 질량을 here의 값에 쓴다.
	*/


	return Cmd_GetMassTo(pNextUnit, here, here, param1);
}


CMD_FUNC_DECL(Cmd_GetMassTo)
{
	/*
	* [1, 2]
	* 2의 질량을 1의 값에 쓴다.
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
	* 1의 반지름을 here의 값에 쓴다.
	*/


	return Cmd_GetRadiusTo(pNextUnit, here, here, param1);
}


CMD_FUNC_DECL(Cmd_GetRadiusTo)
{
	/*
	* [1, 2]
	* 2의 반지름을 1의 값에 쓴다.
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
	* here의 x위치를 1의 값에 쓰고
	  y위치를 2의 값에 쓴다.
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
	* here의 값이 가르키는 Unit의 x위치를 1의 값에 쓰고
	  y위치를 2의 값에 쓴다.
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
	* 현재 시간을 here의 값에 쓴다.
	*/


	return Cmd_GetTimeTo(pNextUnit, here, here, nullptr);
}


CMD_FUNC_DECL(Cmd_GetTimeTo)
{
	/*
	* [1, *]
	* 현재 시간을 1의 값에 쓴다.
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
	* 적합도 점수를 here의 값에 쓴다.
	*/


	return Cmd_GetScoreTo(pNextUnit, here, here, nullptr);
}


CMD_FUNC_DECL(Cmd_GetScoreTo)
{
	/*
	* [1, *]
	* 적합도 점수를 1의 값에 쓴다.
	*/


	if (param1)
	{
		param1->setMemory(m_geneScore);


		return 0.0;
	}


	return -0.1;
}

