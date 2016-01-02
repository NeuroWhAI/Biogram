#include "WhatboxGraphic.h"

#include <sstream>

#include "cCore.h"

#include "BiogramWorld.h"
#include "Unit.h"



























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
	cCore::Sprite.BeginDraw();

	auto& pUnitList = world.getUnitList();
	for (auto& pUnit : pUnitList)
	{
		auto location = pUnit->getLocation();

		cCore::Sprite.DrawTextureCenter(cCore::Resource.m_pTxList[TxList_Biogram]->GetTexture(0),
			D3DXVECTOR2(location.x, location.y));
	}

	cCore::Sprite.EndDraw();


	std::wostringstream oss;
	oss << L"TimeSpeed: " << world.getTimeSpeed() << "x";
	drawText(oss.str(),
		Utility::Point(8, 8), false, Utility::Color::BLACK);


	return 0;
}

