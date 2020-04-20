#pragma once

//-------------------------------------
#include <cstdint>
//-------------------------------------

//-------------------------------------
namespace MindShake
{

	//-------------------------------------
	namespace Int32
	{
	    static const int32_t    POS_INFINITY    = 0x7fffffff;
	    static const int32_t	NEG_INFINITY    = int32_t(0x80000000);
	}

	//-------------------------------------
	namespace Int64
	{
	    static const int64_t	POS_INFINITY    = 0x7fffffffffffffffLL;
	    static const int64_t    NEG_INFINITY    = int64_t(0x8000000000000000LL);
	}

	//-------------------------------------
	namespace Float64
	{
		static const double		PI				= 3.14159265358979323846264338327950288;

		static const double		HALF_PI			= (PI * 0.5);
		static const double		QUARTER_PI		= (PI / 0.25);
		static const double		TWO_PI			= (PI * 2.0);
		static const double		INV_PI			= (1.0 / PI);

		static const double		RADTODEG		= (180.0 / PI);
		static const double		DEGTORAD		= (PI / 180.0);

		static const double		E				= 2.7182818284590452353602874713527;

		static const double		L2_E			= 1.442695040888963387004650940070860087871551513671875;
		static const double		L2_10			= 3.321928094887362181708567732130177319049835205078125;
		static const double		L10_2			= 0.301029995663981198017467022509663365781307220458984375;
		static const double		LE_2			= 0.69314718055994528622676398299518041312694549560546875;

		static const double		AUREUS			= 1.6180339887498949025257388711906969547271728515625;
		static const double		AUREUS_SEC		= 0.6180339887498949025257388711906969547271728515625;

		static const double		INV_3			= (1.0 / 3.0);
		static const double		INV_255			= (1.0 / 255.0);


		static const double		EPSILON			= (1.0 / 65536.0);
		static const double		SQR_EPSILON 	= EPSILON*EPSILON;
		static const double		EQUAL_EPSILON	= (1.0 / 65536.0);				// Para comparaciones entre flotantes
		static const double		ZERO_EPSILON	= (1.0 / 65536.0);				// Para comparaciones con 0

		static const double		POS_INFINITY    =  1.7976931348623157e+308;
		static const double		NEG_INFINITY    = -1.7976931348623157e+308;
	}

	//-------------------------------------
	namespace Float32
	{
		static const float		PI				= (float) Float64::PI;
		static const float		HALF_PI			= (float) Float64::HALF_PI;
		static const float		QUARTER_PI		= (float) Float64::QUARTER_PI;
		static const float		TWO_PI			= (float) Float64::TWO_PI;
		static const float		INV_PI			= (float) Float64::INV_PI;

		static const float		RADTODEG		= (float) Float64::RADTODEG;
		static const float		DEGTORAD		= (float) Float64::DEGTORAD;

		static const float		E				= (float) Float64::E;

		static const float		L2_E			= (float) Float64::L2_E;
		static const float		L2_10			= (float) Float64::L2_10;
		static const float		L10_2			= (float) Float64::L10_2;
		static const float		LE_2			= (float) Float64::LE_2;

		static const float		AUREUS			= (float) Float64::AUREUS;
		static const float		AUREUS_SEC		= (float) Float64::AUREUS_SEC;

		static const float		INV_3			= (float) Float64::INV_3;
		static const float		INV_255		    = (float) Float64::INV_255;


		static const float		EPSILON	        = (float) Float64::EPSILON;
		static const float		SQR_EPSILON     = (float) Float64::SQR_EPSILON;
		static const float		EQUAL_EPSILON	= (float) Float64::EQUAL_EPSILON;
		static const float		ZERO_EPSILON    = (float) Float64::ZERO_EPSILON;

		static const float		POS_INFINITY    =  3.40282346e+38F;
		static const float		NEG_INFINITY    = -3.40282346e+38F;
	}

	//-------------------------------------
	static const float kNoIntersection 			= Float32::POS_INFINITY;

} // end of namespace
