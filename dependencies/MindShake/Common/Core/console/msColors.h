#pragma once


namespace MindShake
{

#if !defined(FOREGROUND_BLUE)
	#define FOREGROUND_BLUE      0x0001 // text color contains blue.
	#define FOREGROUND_GREEN     0x0002 // text color contains green.
	#define FOREGROUND_RED       0x0004 // text color contains red.
	#define FOREGROUND_INTENSITY 0x0008 // text color is intensified.

	#define BACKGROUND_BLUE      0x0010 // background color contains blue.
	#define BACKGROUND_GREEN     0x0020 // background color contains green.
	#define BACKGROUND_RED       0x0040 // background color contains red.
	#define BACKGROUND_INTENSITY 0x0080 // background color is intensified.
#endif

	//---------------------------------
	enum EForegroundColor
	{
	#if defined(_WIN32) && !defined(__CYGWIN32__)
		FC_Black        = (0),
		FC_Red          = (FOREGROUND_RED),
		FC_Green        = (FOREGROUND_GREEN),
		FC_Yellow       = (FOREGROUND_RED      | FOREGROUND_GREEN),
		FC_Blue         = (FOREGROUND_BLUE),
		FC_Magenta      = (FOREGROUND_RED      | FOREGROUND_BLUE),
		FC_Cyan         = (FOREGROUND_GREEN    | FOREGROUND_BLUE),
		FC_LightGray    = (FOREGROUND_RED      | FOREGROUND_GREEN     | FOREGROUND_BLUE),
		FC_DarkGray     = (FOREGROUND_INTENSITY),
		FC_LightRed     = (FOREGROUND_RED      | FOREGROUND_INTENSITY),
		FC_LightGreen   = (FOREGROUND_GREEN    | FOREGROUND_INTENSITY),
		FC_LightYellow  = (FOREGROUND_RED      | FOREGROUND_GREEN     | FOREGROUND_INTENSITY),
		FC_LightBlue    = (FOREGROUND_BLUE     | FOREGROUND_INTENSITY),
		FC_LightMagenta = (FOREGROUND_RED      | FOREGROUND_BLUE      | FOREGROUND_INTENSITY),
		FC_LightCyan    = (FOREGROUND_GREEN    | FOREGROUND_BLUE      | FOREGROUND_INTENSITY),
		FC_White        = (FOREGROUND_RED      | FOREGROUND_GREEN     | FOREGROUND_BLUE      | FOREGROUND_INTENSITY),
	#else
		FC_Black        = 30,
		FC_Red          = 31,
		FC_Green        = 32,
		FC_Yellow       = 33,
		FC_Blue         = 34,
		FC_Magenta      = 35,
		FC_Cyan         = 36,
		FC_LightGray    = 37,
		FC_DarkGray     = 30,
		FC_LightRed     = 31,
		FC_LightGreen   = 32,
		FC_LightYellow  = 33,
		FC_LightBlue    = 34,
		FC_LightMagenta = 35,
		FC_LightCyan    = 36,
		FC_White        = 37,
	#endif
		FC_MAX = 16
	};

	//---------------------------------
	enum EBackgroundColor
	{
	#if defined(_WIN32) && !defined(__CYGWIN32__)
		BC_Black     = (0),
		BC_Red       = (BACKGROUND_RED),
		BC_Green     = (BACKGROUND_GREEN),
		BC_Yellow    = (BACKGROUND_RED   | BACKGROUND_GREEN),
		BC_Blue      = (BACKGROUND_BLUE),
		BC_Magenta   = (BACKGROUND_RED   | BACKGROUND_BLUE),
		BC_Cyan      = (BACKGROUND_GREEN | BACKGROUND_BLUE),
		BC_LightGray = (BACKGROUND_RED   | BACKGROUND_GREEN | BACKGROUND_BLUE),
	#else
		BC_Black     = 40,
		BC_Red       = 44,
		BC_Green     = 42,
		BC_Yellow    = 46,
		BC_Blue      = 41,
		BC_Magenta   = 45,
		BC_Cyan      = 43,
		BC_LightGray = 47,
	#endif
		BC_MAX = 8
	};

} // end of namespace
