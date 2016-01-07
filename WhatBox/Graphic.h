#pragma once

#include <string>

#include "Utility.h"



























class Graphic
{
public:
	Graphic();
	virtual ~Graphic();


public:
	virtual int drawLineBegin(float width) const = 0;
	virtual int drawLine(float x1, float y1, float x2, float y2,
		int r, int g, int b, int a = 255) const = 0;
	virtual int drawLine(Utility::PointF p1, Utility::PointF p2,
		Utility::Color color) const = 0;
	virtual int drawLineEnd() const = 0;

	virtual int drawText(std::string text, float x, float y, bool isCenter,
		int r, int g, int b, int a = 255) const = 0;
	virtual int drawText(std::string text, Utility::PointF location, bool isCenter,
		Utility::Color color) const = 0;
	virtual int drawText(std::wstring text, float x, float y, bool isCenter,
		int r, int g, int b, int a = 255) const = 0;
	virtual int drawText(std::wstring text, Utility::PointF location, bool isCenter,
		Utility::Color color) const = 0;
};

