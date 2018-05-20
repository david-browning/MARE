#include <annotations.h>
#include "mare_rt.h"

MareRT::MareRT(window_handle_t hdc, 
					int32_t windowWidth, 
					int32_t windowHeight,
					int32_t pageWidth,
					int32_t pageHeight) :
	_wW(windowWidth), _wH(windowHeight), _pW(pageWidth), _pH(pageHeight)
{
	_pen_p = new Gdiplus::Pen(Color(255, 0, 0, 0), 1.0);
	_gd_p = new Gdiplus::Graphics(hdc);
	_gd_p->SetPageUnit(Unit::UnitPixel);
	Region clipArea(Rect(0, 0, _wW, _wH));
	_gd_p->SetClip(&clipArea, CombineMode::CombineModeReplace);
	_gd_p->ScaleTransform(float(_wW) / float(_pW), float(_wH) / float(_pH));
}

MareRT::MareRT(const MareRT& c):
	_wW(c._wW), _wH(c._wH), _pW(c._pW), _pH(c._pH)
{
	_pen_p = new Gdiplus::Pen(c._pen_p->GetBrush(), c._pen_p->GetWidth());
	_gd_p = new Gdiplus::Graphics(c._gd_p->GetHDC());
	_gd_p->SetPageUnit(Unit::UnitPixel);
	Region clipArea(Rect(0, 0, _wW, _wH));
	_gd_p->SetClip(&clipArea, CombineMode::CombineModeReplace);
	_gd_p->ScaleTransform(float(_wW) / float(_pW), float(_wH) / float(_pH));
}

MareRT::~MareRT()
{
	delete _gd_p;
	delete _pen_p;
}

void MareRT::Line(float x1, float y1, float x2, float y2)
{
	_gd_p->DrawLine(_pen_p, x1, y1, x2, y2);
}

void MareRT::Arc(float x, float y, float w, float h, float startAngle, float sweep)
{
	_gd_p->DrawArc(_pen_p, x, y, w, h, startAngle, sweep);
}

void MareRT::Rectangle(float x, float y, float w, float h)
{
	_gd_p->DrawRectangle(_pen_p, x, y, w, h);
}

void MareRT::Ellipse(float x, float y, float w, float h)
{
	_gd_p->DrawEllipse(_pen_p, x - w / 2, y - h / 2, w, h);
}

void MareRT::Polygon(const float* xPositions, const float* yPositions, size_t vertCount)
{
	std::vector<Point> points(vertCount);
	for(size_t i = 0; i < vertCount; i++)
	{
		points[i] = Point(xPositions[i], yPositions[i]);
	}

	_gd_p->DrawPolygon(_pen_p, &points[0], vertCount);
}

void MareRT::Lines(const float* xPositions, const float* yPositions, size_t vertCount)
{
	std::vector<Point> points(vertCount);
	for(size_t i = 0; i < vertCount; i++)
	{
		points[i] = Point(xPositions[i], yPositions[i]);
	}

	_gd_p->DrawLines(_pen_p, &points[0], vertCount);
}

void MareRT::FilledEllipse(float x, float y, float w, float h)
{
	Color c;
	_pen_p->GetColor(&c);
	SolidBrush b(c);
	_gd_p->FillEllipse(&b, x - w / 2, y - h / 2, w, h);
}

void MareRT::FilledRectangle(float x, float y, float w, float h)
{
	Color c;
	_pen_p->GetColor(&c);
	SolidBrush b(c);
	_gd_p->FillRectangle(&b, x, y, w, h);
}

void MareRT::FilledPolygon(const float* xPositions, const float* yPositions, size_t vertCount)
{
	std::vector<Point> points(vertCount);
	for(size_t i = 0; i < vertCount; i++)
	{
		points[i] = Point(xPositions[i], yPositions[i]);
	}

	Color c;
	_pen_p->GetColor(&c);
	SolidBrush b(c);
	_gd_p->FillPolygon(&b, &points[0], vertCount);
}

void MareRT::SetPenColor(uint8_t r, uint8_t g, uint8_t b)
{
	_pen_p->SetColor(Color(255, r, g, b));
}

void MareRT::SetPenWidth(float w)
{
	_pen_p->SetWidth(w);
}

float MareRT::GetPageWtoHRatio()
{
	return float(_pW) / float(_pH);
}

MareRT MareRT::operator=(const MareRT & r)
{
	return MareRT(r);
}
