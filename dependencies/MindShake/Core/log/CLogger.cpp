//-------------------------------------
#include <Common/Core/configCoreLib.h>
//-------------------------------------
#include "CLogger.h"
#include "CLogSystem.h"
//-------------------------------------


//-------------------------------------
namespace MindShake
{

	//---------------------------------
	CLogger::CLogger()
	{
		mLoggerType = ELoggerType::LT_Unknown;
		mShowTime   = false;
		mpNext      = nullptr;
		CLogSystem::Register(this);
	}

	//---------------------------------
	CLogger::~CLogger()
	{
		CLogSystem::UnRegister(this);
	}

	//---------------------------------
	void
	CLogger::SetShowTime(bool _set)
	{
		mShowTime = _set;
	}

} // end os namespace
