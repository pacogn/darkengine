//-------------------------------------
#include <Common/Core/configCoreLib.h>
//-------------------------------------
#include "CLogConsole.h"
//-------------------------------------


//-------------------------------------
namespace MindShake
{

	//---------------------------------
	CLogConsole::CLogConsole(bool _autoFlush, bool _showExtraInfo, bool _showLogCaption) :
					CLogFile(stderr, _autoFlush, _showExtraInfo, _showLogCaption)
	{
		mLoggerType = ELoggerType::LT_Console;

		printf("LogConsole created\n");

#if defined(TARGET_PLATFORM_WINDOWS)
		mpHandler = GetStdHandle(STD_OUTPUT_HANDLE);
#endif
	}

	//---------------------------------
	void
	CLogConsole::LogColor(uint8_t _color, const char *_pMessage)
	{
		Write(ELogMessage::LM_Log, _pMessage, _color);
	}

#if defined(TARGET_PLATFORM_WINDOWS)

	//---------------------------------
	void
	CLogConsole::Write(ELogMessage _type, const char *_pMsg, uint8_t _color)
	{

		if(mThreadSafe) mMutexLog.Lock();
		{
			switch(_type)
			{
				case ELogMessage::LM_Log:
				case ELogMessage::LM_LogColor:
					SetConsoleTextAttribute(mpHandler, _color);
					break;

				case ELogMessage::LM_Warning:
					SetConsoleTextAttribute(mpHandler, MindShake::FC_Yellow);
					break;

				case ELogMessage::LM_Error:
					SetConsoleTextAttribute(mpHandler, MindShake::FC_LightRed);
					break;

				case ELogMessage::LM_Debug:
					SetConsoleTextAttribute(mpHandler, MindShake::FC_LightGray);
					break;

				case ELogMessage::LM_Assert:
					SetConsoleTextAttribute(mpHandler, MindShake::FC_Red);
					break;
			}

			CLogFile::WriteAux(_type, _pMsg);

		}
		if(mThreadSafe) mMutexLog.Unlock();

	}

#endif

} // end of namespace
