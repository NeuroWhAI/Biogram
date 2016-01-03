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


public: // �����帧 ����
	// * pInLinker --Flow--> pOutUnit
	// * @Return: ���Ἲ�� ����
	static bool ConnectFlow(
		LinkerPtr pInLinker,
		UnitPtr pOutUnit);

	// * pInUnit --Flow--> pOutLinker
	// * @Return: ���Ἲ�� ����
	static bool ConnectFlow(
		UnitPtr pInUnit,
		LinkerPtr pOutLinker);

	// * pInUnit --Flow--> @Return --Flow--> pOutUnit
	// * @Return: ������ ���� ���� ������ Linker. ������н� nullptr.
	static LinkerPtr ConnectFlow(
		UnitPtr pInUnit,
		UnitPtr pOutUnit);


	// * pInLinker X-Flow-X> pOutUnit
	// * @Return: ���⼺�� ����
	static bool DisconnectFlow(
		LinkerPtr pInLinker,
		UnitPtr pOutUnit);

	// * pInUnit X-Flow-X> pOutLinker
	// * @Return: ���⼺�� ����
	static bool DisconnectFlow(
		UnitPtr pInUnit,
		LinkerPtr pOutLinker);

	// * pInUnit X-Flow-X> @Return X-Flow-X> pOutUnit
	// * @Return: ������ ������ Linker. ������н� nullptr
	static LinkerPtr DisconnectFlow(
		UnitPtr pInUnit,
		UnitPtr pOutUnit);


public: // �������� ����
	// * pInUnit --Param--> pOutLinker
	// * @Return: ���Ἲ�� ����
	static bool ConnectParam(
		UnitPtr pInUnit,
		LinkerPtr pOutLinker);

	// * pInLinker --Param--> )-paramIndex=)pOutUnit
	// * @Return: ���Ἲ�� ����
	static bool ConnectParam(
		LinkerPtr pInLinker,
		UnitPtr pOutUnit, int paramIndex);

	// * pInUnit --Param--> @Return --Param--> )-paramIndex=)pOutUnit
	// * @Return: ������ ���� ���� ������ Linker. ������н� nullptr
	static LinkerPtr ConnectParam(
		UnitPtr pInUnit,
		UnitPtr pOutUnit, int paramIndex);


	// * pInUnit X-Param-X> pOutLinker
	// * @Return: ���⼺�� ����
	static bool DisconnectParam(
		UnitPtr pInUnit,
		LinkerPtr pOutLinker);

	// * pInLinker X-Param-X> )-paramIndex=)pOutUnit
	// * @Return: ���⼺�� ����
	static bool DisconnectParam(
		LinkerPtr pInLinker,
		UnitPtr pOutUnit, int paramIndex);

	// * pInUnit X-Param-X> @Return X-Param-X> )-paramIndex=)pOutUnit
	// * @Return: ������ ������ Linker. ������н� nullptr
	static LinkerPtr DisconnectParam(
		UnitPtr pInUnit,
		UnitPtr pOutUnit, int paramIndex);
};

