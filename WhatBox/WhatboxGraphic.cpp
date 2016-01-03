#include "WhatboxGraphic.h"

#include <sstream>

#include "cCore.h"

#include "BiogramWorld.h"
#include "Unit.h"
#include "Linker.h"
#include "CommandOperator.h"



























WhatboxGraphic::WhatboxGraphic()
{

}


WhatboxGraphic::~WhatboxGraphic()
{

}

//###############################################################

int WhatboxGraphic::drawLineBegin(float width) const
{
	cCore::Resource.Line.SetWidth(width);
	cCore::Resource.Line.Begin();


	return 0;
}


int WhatboxGraphic::drawLine(float x1, float y1, float x2, float y2,
	int r, int g, int b, int a) const
{
	cCore::Resource.Line.Draw(x1, y1, x2, y2,
		D3DCOLOR_ARGB(a, r, g, b));


	return 0;
}



int WhatboxGraphic::drawLine(Utility::PointF p1, Utility::PointF p2,
	Utility::Color color) const
{
	return drawLine(p1.x, p1.y, p2.x, p2.y,
		color.r, color.g, color.b, color.a);
}


int WhatboxGraphic::drawLineEnd() const
{
	cCore::Resource.Line.End();


	return 0;
}

//---------------------------------------------------------------

int WhatboxGraphic::drawText(std::string text, float x, float y, bool isCenter,
	int r, int g, int b, int a) const
{
	cCore::Resource.Font0.ShowText(text, x, y,
		D3DCOLOR_ARGB(a, r, g, b),
		isCenter ? DT_CENTER : 0UL);


	return 0;
}


int WhatboxGraphic::drawText(std::string text, Utility::PointF location, bool isCenter,
	Utility::Color color) const
{
	return drawText(text, location.x, location.y, isCenter,
		color.r, color.g, color.b, color.a);
}


int WhatboxGraphic::drawText(std::wstring text, float x, float y, bool isCenter,
	int r, int g, int b, int a) const
{
	cCore::Resource.Font0.ShowText(text, x, y,
		D3DCOLOR_ARGB(a, r, g, b),
		isCenter ? DT_CENTER : 0UL);


	return 0;
}


int WhatboxGraphic::drawText(std::wstring text, Utility::PointF location, bool isCenter,
	Utility::Color color) const
{
	return drawText(text, location.x, location.y, isCenter,
		color.r, color.g, color.b, color.a);
}

//###############################################################

int WhatboxGraphic::drawBiogramWorld(const BiogramWorld& world) const
{
	std::wostringstream oss;


	// 인자연결선 그리기
	drawLineBegin(4.0f);

	const auto& pParamLinkerList = world.getParamLinkerList();
	for (auto& pLinker : pParamLinkerList)
	{
		auto pInUnit = pLinker->getInUnit();
		auto pOutUnit = pLinker->getOutUnit();

		if (pInUnit && pOutUnit)
		{
			drawLine(pInUnit->getLocation(), pOutUnit->getLocation(),
				Utility::Color::ORANGE);
		}
	}

	drawLineEnd();


	// 실행흐름선 그리기
	drawLineBegin(8.0f);

	const auto& pFlowLinkerList = world.getFlowLinkerList();
	for (auto& pLinker : pFlowLinkerList)
	{
		auto pInUnit = pLinker->getInUnit();
		auto pOutUnit = pLinker->getOutUnit();

		if (pInUnit && pOutUnit)
		{
			drawLine(pInUnit->getLocation(), pOutUnit->getLocation(),
				Utility::Color::GRAY);
		}
	}

	drawLineEnd();


	// 유닛 그리기
	cCore::Sprite.BeginDraw();

	const auto& pUnitList = world.getUnitList();
	for (auto& pUnit : pUnitList)
	{
		auto location = pUnit->getLocation();

		cCore::Sprite.DrawTextureCenter(cCore::Resource.m_pTxList[TxList_Biogram]->GetTexture(0),
			D3DXVECTOR2(location.x, location.y));
		cCore::Sprite.EndDraw();

		oss.str(L"");
		oss << pUnit->getTimeGage();
		drawText(oss.str(),
			location, true, Utility::Color::BLACK);
		cCore::Sprite.BeginDraw();
	}

	cCore::Sprite.EndDraw();


	// 명령어 진행 상태 표시
	oss.str(L"");
	auto cmdOperator = world.getCmdOperator();
	oss << L"CurrentUnitCount: " << cmdOperator->getCurrentUnitCount();
	drawText(oss.str(),
		Utility::PointF(8, 32), false, Utility::Color::BLACK);


	// 시간흐름 속도 표시
	oss.str(L"");
	oss << L"TimeSpeed: " << world.getTimeSpeed() << "x";
	drawText(oss.str(),
		Utility::PointF(8, 8), false, Utility::Color::BLACK);


	return 0;
}

