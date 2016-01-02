#pragma once

#include "Graphic.h"



























class WhatboxGraphic : public Graphic
{
public:
	WhatboxGraphic();
	virtual ~WhatboxGraphic();


public:
	virtual int drawLineBegin(float width) const override;
	virtual int drawLine(float x1, float y1, float x2, float y2,
		int r, int g, int b, int a = 255) const override;
	virtual int drawLine(Utility::PointF p1, Utility::PointF p2,
		Utility::Color color) const override;
	virtual int drawLineEnd() const override;

	virtual int drawText(std::string text, float x, float y, bool isCenter,
		int r, int g, int b, int a = 255) const override;
	virtual int drawText(std::string text, Utility::PointF location, bool isCenter,
		Utility::Color color) const override;
	virtual int drawText(std::wstring text, float x, float y, bool isCenter,
		int r, int g, int b, int a = 255) const override;
	virtual int drawText(std::wstring text, Utility::PointF location, bool isCenter,
		Utility::Color color) const override;


public:
	virtual int drawBiogramWorld(const BiogramWorld& world) const override;
};

