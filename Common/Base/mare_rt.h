#pragma once

#include <cstdint>
#include <vector>
#include <initializer_list>

#if defined _WINDOWS || defined _WIN32
#define WIN32_LEAN_AND_MEAN   
#include <windows.h>
#include <ObjIdl.h>

#pragma warning(push)
#pragma warning(disable:4458)

#include <gdiplus.h>
using namespace Gdiplus;

#pragma warning(pop)

#define EXPORT_FUNC __declspec(dllexport)

typedef HDC window_handle_t;
typedef Gdiplus::Graphics graphics_dev_t;
typedef Gdiplus::Pen pen_t;

#else

typedef void* window_handle_t;
typedef void* graphics_dev_t;
typedef void* pen_t;

#define EXPORT_FUNC __attribute__((__visibility__("default")))

#endif

/*
 MARE runtime driver class. MARE programs use this to draw in a window.
 */
class EXPORT_FUNC MareRT
{
	public:
	MareRT(window_handle_t hdc,
			int32_t windowWidth,
			int32_t windowHeight,
			int32_t pageWidth,
			int32_t pageHeight);

	MareRT(const MareRT& c);

	virtual ~MareRT();

	void Line(float x1, float y1, float x2, float y2);

	void Lines(const float* xPositions, const float* yPositions, size_t vertCount);

	void Arc(float x, float y, float w, float h, float startAngle, float sweep);

	void Rectangle(float x, float y, float w, float h);
	
   //Draws an ellipse where the center is (x, y). The ellipse is w pixels wide, and h
   //pixels tall. W and H refer to width and height diameters. They are not radiuses. 
   //The ellipse outline color is set by calling SetPenColor before calling this.
	void Ellipse(float x, float y, float w, float h); 

	void Polygon(const float* xPositions, const float* yPositions, size_t vertCount);

   //Draws an ellipse where the center is (x, y). The ellipse is w pixels wide, and h
   //pixels tall. W and H refer to width and height diameters. They are not radiuses. 
   //The ellipse color is set by calling SetPenColor before calling this.
	void FilledEllipse(float x, float y, float w, float h);

	//Draws a rectangle and fills it in with the current pen color.
	void FilledRectangle(float x, float y, float w, float h);

	void FilledPolygon(const float* xPositions, const float* yPositions, size_t vertCount);

	void SetPenColor(uint8_t r, uint8_t g, uint8_t b);

	void SetPenWidth(float w);

	float GetPageWtoHRatio();

   //Copy constructor.
	MareRT operator=(const MareRT& r);

	private:
	pen_t* _pen_p;
	graphics_dev_t* _gd_p;
	
	/*
	 Window width in pixels.
	 */
	int32_t _wW;

	/*
	 Window height in pixels.
	 */
	int32_t _wH;

	/*
	 Page width in pixels.
	 */
	const int32_t _pW;

	/*
	 Page height in pixels.
	 */
	const int32_t _pH;

};

typedef void(*MareRunProc)(MareRT& rt);

typedef int32_t(*MareGetPageSizeProc)();
