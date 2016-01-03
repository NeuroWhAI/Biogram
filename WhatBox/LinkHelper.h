#pragma once

#include <memory>

class Unit;
class Linker;



























class LinkHelper
{
private:
	LinkHelper() = delete;


public:
	typedef std::shared_ptr<Unit> UnitPtr;
	typedef std::shared_ptr<Linker> LinkerPtr;


public: // 실행흐름 연결
	// * pInLinker --Flow--> pOutUnit
	// * @Return: 연결성공 여부
	static bool ConnectFlow(
		LinkerPtr pInLinker,
		UnitPtr pOutUnit);

	// * pInUnit --Flow--> pOutLinker
	// * @Return: 연결성공 여부
	static bool ConnectFlow(
		UnitPtr pInUnit,
		LinkerPtr pOutLinker);

	// * pInUnit --Flow--> @Return --Flow--> pOutUnit
	// * @Return: 연결을 위해 새로 생성한 Linker. 연결실패시 nullptr.
	static LinkerPtr ConnectFlow(
		UnitPtr pInUnit,
		UnitPtr pOutUnit);


	// * pInLinker X-Flow-X> pOutUnit
	// * @Return: 끊기성공 여부
	static bool DisconnectFlow(
		LinkerPtr pInLinker,
		UnitPtr pOutUnit);

	// * pInUnit X-Flow-X> pOutLinker
	// * @Return: 끊기성공 여부
	static bool DisconnectFlow(
		UnitPtr pInUnit,
		LinkerPtr pOutLinker);

	// * pInUnit X-Flow-X> @Return X-Flow-X> pOutUnit
	// * @Return: 연결이 끊어진 Linker. 끊기실패시 nullptr
	static LinkerPtr DisconnectFlow(
		UnitPtr pInUnit,
		UnitPtr pOutUnit);


public: // 인자전달 연결
	// * pInUnit --Param--> pOutLinker
	// * @Return: 연결성공 여부
	static bool ConnectParam(
		UnitPtr pInUnit,
		LinkerPtr pOutLinker);

	// * pInLinker --Param--> )-paramIndex=)pOutUnit
	// * @Return: 연결성공 여부
	static bool ConnectParam(
		LinkerPtr pInLinker,
		UnitPtr pOutUnit, int paramIndex);

	// * pInUnit --Param--> @Return --Param--> )-paramIndex=)pOutUnit
	// * @Return: 연결을 위해 새로 생성한 Linker. 연결실패시 nullptr
	static LinkerPtr ConnectParam(
		UnitPtr pInUnit,
		UnitPtr pOutUnit, int paramIndex);


	// * pInUnit X-Param-X> pOutLinker
	// * @Return: 끊기성공 여부
	static bool DisconnectParam(
		UnitPtr pInUnit,
		LinkerPtr pOutLinker);

	// * pInLinker X-Param-X> )-paramIndex=)pOutUnit
	// * @Return: 끊기성공 여부
	static bool DisconnectParam(
		LinkerPtr pInLinker,
		UnitPtr pOutUnit, int paramIndex);

	// * pInUnit X-Param-X> @Return X-Param-X> )-paramIndex=)pOutUnit
	// * @Return: 연결이 끊어진 Linker. 끊기실패시 nullptr
	static LinkerPtr DisconnectParam(
		UnitPtr pInUnit,
		UnitPtr pOutUnit, int paramIndex);
};

