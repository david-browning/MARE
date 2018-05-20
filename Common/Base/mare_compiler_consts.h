#pragma once

#include <annotations.h>
#include "mare_atom_types.h"

///////////////////////////////////////////////////////////////////////////////////////////////////
//Conversions between pixels, centimeters, and inches.
///////////////////////////////////////////////////////////////////////////////////////////////////
/*
 MARE programs use this DPI.
 */
static constexpr mare_float32_t PIXELS_PER_INCH = 96.0f;

/*
 Centimeters per inch.
 */
static constexpr mare_float32_t CM_PER_INCH = 2.54f;

/*
 Pixels per centimeter. This is a function of PIXELS_PER_INCH.
 */
static constexpr mare_float32_t PIXELS_PER_CM = PIXELS_PER_INCH / CM_PER_INCH;
///////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////
//These are literal values that determine the page dimensions of a MARE program.
///////////////////////////////////////////////////////////////////////////////////////////////////
/*
 Width of the page in inches. Set this to change the MARE program's output dimmensions. 
 */
static mare_float32_t PAPER_WIDTH_INCHES = 8.5f;

/*
 Height of the page in inches. Set this to change the MARE program's output dimmensions. 
 */
static mare_float32_t PAPER_HEIGHT_INCHES = 11.0f;

/*
 Height of the page in pixels.
 */
static mare_int32_t GetMAREPageHeight()
{
    return int32_t(PAPER_HEIGHT_INCHES * PIXELS_PER_INCH);
}

/*
 Width of the page in pixels.
 */
static mare_int32_t GetMAREPageWidth()
{
    return int32_t(PAPER_WIDTH_INCHES * PIXELS_PER_INCH);
}

/*
 Value of true in a MARE program.
 */
static constexpr mare_bool_t MARE_TRUE = 1;

/*
 Value of false in a MARE program.
 */
static constexpr mare_bool_t MARE_FALSE = 0;
///////////////////////////////////////////////////////////////////////////////////////////////////

/*
 Default file extension for a MARE source code file.
 */
static const std::string MARE_FILE_EXT = ".mare";

///////////////////////////////////////////////////////////////////////////////////////////////////
//MARE compiler program version info and copyright.
///////////////////////////////////////////////////////////////////////////////////////////////////
/*
 MARE compiler major version.
 */
static constexpr uint8_t MARE_VERSION_MAJOR = 1;

/*
 MARE compiler minor version.
 */
static constexpr uint8_t MARE_VERSION_MINOR = 0;

/*
 Copyright year.
 */
static constexpr int MARE_COPYRIGHT_YEAR = 2018;
///////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////
//Symbols for functions in a compiled MARE program.
///////////////////////////////////////////////////////////////////////////////////////////////////
/*
 Name of the compiled MARE program class.
 */
static const std::string MARE_PROG_CLASS_NAME = "mareprog";

/*
 Symbol for the function which runs a MARE program.
 */
static const std::string MARE_PROGRAM_ENTRY = "RunMareProgram";

/*
 Symbol for the function to get a MARE program's page width.
 Use this string to lookup the address of the get page width function.
 */
static const std::string MARE_GET_PAGE_WIDTH_ENTRY = "GetPageWidth";

/*
 Symbol for the function to get a MARE program's page height.
 Use this string to lookup the address of the get page height function. 
 */
static const std::string MARE_GET_PAGE_HEIGHT_ENTRY = "GetPageHeight";
///////////////////////////////////////////////////////////////////////////////////////////////////