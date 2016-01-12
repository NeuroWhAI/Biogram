#include "WhatboxObjectViewer.h"

#include <sstream>

#include "System.h"
#include "cCore.h"

#include "BiogramWorld.h"
#include "BiogramCage.h"
#include "Unit.h"
#include "Linker.h"
#include "CommandOperator.h"
#include "Memory.h"

#include "TextPrinterDevice.h"
#include "VoidGameDevice.h"

#define CMD_FUNC(name) m_cmdNameList.emplace_back(L#name);



























WhatboxObjectViewer::WhatboxObjectViewer()
{
	// 명령어 함수 이름들을 목록화 함
#include "CommandFunction.h"
#undef CMD_FUNC
}


WhatboxObjectViewer::~WhatboxObjectViewer()
{

}

//#################################################################

int WhatboxObjectViewer::drawBiogramWorld(const BiogramWorld& world) const
{
	auto& graphic = System::getInstance().getGraphic();
	std::wostringstream oss;


	// 세대 번호 표시
	oss << L"G: " << world.getGenerationNumber() << std::endl;
	

	// 돌연변이율 표시
	oss << L"Mutation Rate:" << std::endl;
	oss << L" " << world.getMutationRate() << std::endl;


	// 선택된 Cage와 그 Cage에 연결된 Device 그리기
	double totalScore = 0.0;
	const auto& cageList = world.getCageList();
	for (auto& cage : cageList)
	{
		totalScore += cage->getGeneScore();
	}
	oss << L"Cage Count: " << cageList.size() << std::endl;
	oss << L"Total Score: " << totalScore << std::endl;

	size_t cageNum = world.getFocusedCageNumber();
	oss << L"Current Cage: " << cageNum + 1 << std::endl;

	const auto& deviceList = world.getDeviceList();

	if (cageNum < cageList.size())
	{
		// Cage 그리기
		drawBiogramCage(*cageList[cageNum]);


		// Device 그리기
		for (auto& device : deviceList)
		{
			if (device->getConnectedCage() == cageList[cageNum])
				device->render();
		}
	}
	oss << L"Device Count: " << deviceList.size() << std::endl;


	// 시간속도 및 경과시간 표시
	oss << L"Time Speed: " << world.getTimeSpeed() << std::endl;
	oss << L"World Elapsed Time: " << world.getElapsedTime() << std::endl;


	// 공유메모리 표시
	oss << L"Shared Memory:" << std::endl;

	auto sharedMem = world.getSharedMemory();
	auto memory = sharedMem->getMemory();

	size_t count = 0;
	size_t nlCount = memory.size() / 64;
	for (const auto& cell : memory)
	{
		oss << L" (" << cell.first << L": " << cell.second << L")" << std::endl;

		++count;
		if (count > 32)
		{
			count = 0;
			oss << L"..." << std::endl;
			break;
		}
	}

	graphic.drawText(oss.str(),
		Utility::PointF(8.0f, 8.0f), false, Utility::Color::BLACK);


	return 0;
}


int WhatboxObjectViewer::drawBiogramCage(const BiogramCage& cage) const
{
	auto& graphic = System::getInstance().getGraphic();
	D3DXVECTOR2 camPos = *cCore::Camera2D.Pos();
	std::wostringstream oss;
	//std::wostringstream oss2;


	// 경과시간 표시
	oss << L"Elapsed Time:" << std::endl;
	oss << L" " << cage.getElapsedTime() << std::endl;


	// 적합도 표시
	oss << L"Gene Score:" << std::endl;
	oss << L" " << cage.getGeneScore() << std::endl;


	// 메모리 표시
	oss << L"Cage Memory:" << std::endl;

	auto cageMem = cage.getCageMemory();
	auto memory = cageMem->getMemory();

	size_t count = 0;
	for (const auto& cell : memory)
	{
		oss << L" (" << cell.first << L": " << cell.second << L")" << std::endl;
	
		++count;
		if (count > 32)
		{
			count = 0;
			oss << L"..." << std::endl;
			break;
		}
	}


	// 인자연결선 그리기
	graphic.drawLineBegin(2.0f);

	const auto& pParamLinkerList = cage.getParamLinkerList();
	for (auto& pLinker : pParamLinkerList)
	{
		auto pInUnit = pLinker->getInUnit();
		auto pOutUnit = pLinker->getOutUnit();

		if (pInUnit && pOutUnit)
		{
			graphic.drawLine(pInUnit->getLocation(), pOutUnit->getLocation(),
				Utility::Color::ORANGE);
		}
	}

	graphic.drawLineEnd();


	// 실행흐름선 그리기
	graphic.drawLineBegin(1.0f);

	const auto& pFlowLinkerList = cage.getFlowLinkerList();
	for (auto& pLinker : pFlowLinkerList)
	{
		auto pInUnit = pLinker->getInUnit();
		auto pOutUnit = pLinker->getOutUnit();

		if (pInUnit && pOutUnit)
		{
			graphic.drawLine(pInUnit->getLocation(), pOutUnit->getLocation(),
				Utility::Color::GRAY);
		}
	}

	graphic.drawLineEnd();


	// 유닛 그리기
	cCore::Sprite.BeginDraw();

	//oss2 << L"Command Flow:" << std::endl;

	const auto& pUnitList = cage.getUnitList();
	for (auto& pUnit : pUnitList)
	{
		auto location = pUnit->getLocation();
		float scale = pUnit->getRadius() / 16.0f;

		int color = (pUnit->getTimeGage() > 0.0) ? 255 : 64;
		cCore::Sprite.SetColor(
			D3DCOLOR_ARGB(color, 255, 255, 255));
		cCore::Sprite.DrawTextureCenter(cCore::Resource.m_pTxList[TxList_Biogram]->GetTexture(0),
			D3DXVECTOR2(location.x, location.y), 0.0f,
			D3DXVECTOR2(scale, scale));

		/*if (pUnit->getInLinker() || pUnit->getOutLinker())
		{
			int cmdNumber = pUnit->getCmdNumber();
			if (static_cast<size_t>(cmdNumber) < m_cmdNameList.size())
				oss2 << L" " << m_cmdNameList[cmdNumber] << std::endl;
			else
				oss2 << L" Cmd_????" << std::endl;
		}*/
	}

	cCore::Sprite.EndDraw();


	// 유닛 메모리 표시
	/*oss.str(L"");
	int count = 0;
	for (auto& pUnit : pUnitList)
	{
	oss << pUnit->getMemory() << std::endl;
	++count;

	if (count > 64)
	{
	oss << L"...";
	break;
	}
	}*/


	// 유닛 세부정보 표시
	/*for (auto& pUnit : pUnitList)
	{
		auto location = pUnit->getLocation();
		D3DXVECTOR2 vec;
		vec.x = location.x;
		vec.y = location.y;


		if (cCore::ShapeMath.isCollided(
			&cCore::Input.fCursorPos(),
			&vec,
			pUnit->getRadius()))
		{
			drawUnitDetail(*pUnit);

			break;
		}
	}*/


	// 텍스트 정보 표시
	graphic.drawText(oss.str(),
		Utility::PointF(-200.0f, 8.0f), false, Utility::Color::BLACK);

	//graphic.drawText(oss2.str(),
	//	Utility::PointF(-500.0f, 8.0f), false, Utility::Color::BLACK);


	return 0;
}


int WhatboxObjectViewer::drawUnitDetail(const Unit& unit) const
{
	auto& graphic = System::getInstance().getGraphic();
	std::wostringstream oss;


	oss << "[Unit]" << std::endl;
	int cmdNumber = unit.getCmdNumber();
	if (static_cast<size_t>(cmdNumber) < m_cmdNameList.size())
		oss << "CmdNumber: " << m_cmdNameList[cmdNumber] << std::endl;
	else
		oss << "CmdNumber: ????" << std::endl;
	oss << "Memory: " << unit.getMemory() << std::endl;

	oss << std::endl;

	oss << "[Object]" << std::endl;
	oss << "Mass: " << unit.getMass() << std::endl;
	oss << "Temperature: " << unit.getTemperature() << std::endl;


	graphic.drawText(oss.str(),
		unit.getLocation(), false, Utility::Color::BLACK);


	return 0;
}

//#################################################################

int WhatboxObjectViewer::draw(const TextPrinterDevice& device) const
{
	auto& graphic = System::getInstance().getGraphic();
	std::wostringstream oss;


	oss << L"TextPrinterDevice:" << std::endl;
	oss << L" " << device.getText();


	graphic.drawText(oss.str(),
		Utility::PointF(400.0f, 8.0f), false, Utility::Color::BLACK);


	return 0;
}


int WhatboxObjectViewer::draw(const VoidGameDevice& device) const
{
	auto& graphic = System::getInstance().getGraphic();
	std::wostringstream oss;


	oss << L"VoidGameDevice:" << std::endl;
	oss << L" ";


	graphic.drawText(oss.str(),
		Utility::PointF(400.0f, 8.0f), false, Utility::Color::BLACK);


	return 0;
}

