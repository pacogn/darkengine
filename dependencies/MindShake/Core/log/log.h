#pragma once

//-------------------------------------
#include <Common/Core/configCoreLib.h>
#include <Common/Core/console/msColors.h>
//-------------------------------------

#if defined(USE_LOG_SYSTEM)

	#include "CLogSystem.h"

	//---------------------------------
	#define MS_LOG			MindShake::CLogSystem::SetOwner(__FILE__,__LINE__,__FUNCTION__), MindShake::CLogSystem::Log
	#define MS_LOGCOLOR		MindShake::CLogSystem::SetOwner(__FILE__,__LINE__,__FUNCTION__), MindShake::CLogSystem::LogColor
	#define MS_WARNING		MindShake::CLogSystem::SetOwner(__FILE__,__LINE__,__FUNCTION__), MindShake::CLogSystem::Warning
	#define MS_ERROR		MindShake::CLogSystem::SetOwner(__FILE__,__LINE__,__FUNCTION__), MindShake::CLogSystem::Error
	#define MS_DEBUG		MindShake::CLogSystem::SetOwner(__FILE__,__LINE__,__FUNCTION__), MindShake::CLogSystem::Debug
	#define MS_ASSERT		MindShake::CLogSystem::SetOwner(__FILE__,__LINE__,__FUNCTION__), MindShake::CLogSystem::Assert
	//---------------------------------
	#define kAssertOrReturn(x)					if((x) == false)	{ MS_ERROR("\nFile: %s\nFunction: %s, Line: %d\nAssertion failed: '"#x"'", __FILE__, __FUNCTION__, __LINE__); return;       }
	#define kAssertOrReturnValue(x, value)		if((x) == false)	{ MS_ERROR("\nFile: %s\nFunction: %s, Line: %d\nAssertion failed: '"#x"', return '"#value"'", __FILE__, __FUNCTION__, __LINE__); return value; }
	//---------------------------------

#else

	#include <stdio.h>

	//---------------------------------
	#define MS_LOG			printf
	#define MS_WARNING		printf
	#define MS_ERROR		printf
	#define MS_DEBUG		printf
	#define MS_ASSERT		printf
	//-------------------------------------
	#define kAssertOrReturn(x)					if((x) == false)	{ printf("\nFile: %s\nFunction: %s, Line: %d\nAssertion failed: '"#x"'", __FILE__, __FUNCTION__, __LINE__); return;       }
	#define kAssertOrReturnValue(x, value)		if((x) == false)	{ printf("\nFile: %s\nFunction: %s, Line: %d\nAssertion failed: '"#x"', return '"#value"'", __FILE__, __FUNCTION__, __LINE__); return value; }
	//-------------------------------------

#endif
