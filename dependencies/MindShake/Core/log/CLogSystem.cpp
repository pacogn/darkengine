//-------------------------------------
#include <Common/Core/configCoreLib.h>
#include <Common/Core/printfAux.h>
//-------------------------------------
#include "CLogSystem.h"
#include "CLogger.h"
//-------------------------------------
#include <assert.h>
//-------------------------------------
#if defined(TARGET_PLATFORM_WINDOWS) || defined(TARGET_PLATFORM_LINUX) || defined(TARGET_PLATFORM_MACOSX)
	#include "CLogConsole.h"

	MindShake::CLogConsole	console;
#endif
//-------------------------------------

//-------------------------------------
namespace MindShake
{

	//-------------------------------------
	bool			CLogSystem::mHaveOwner   = false;
	const char *	CLogSystem::mpSourceFile = nullptr;
	unsigned int	CLogSystem::mSourceLine  = 0;
	const char *	CLogSystem::mpSourceFunc = nullptr;

	CLogger	*		CLogSystem::mpLoggers    = nullptr;
	//-------------------------------------

	//-------------------------------------
	//-------------------------------------

	//-------------------------------------
	void
	CLogSystem::Free()
	{
		CLogger	*pLogger;

		pLogger = mpLoggers;
		while(pLogger != nullptr)
		{
			mpLoggers = mpLoggers->mpNext;
			delete pLogger;
			pLogger = mpLoggers;
		}
	}

	//-------------------------------------
	bool
	CLogSystem::SetOwner(const char *_sourceFile, const unsigned int _sourceLine, const char *_sourceFunc)
	{
		mHaveOwner   = true;
		mpSourceFile = _sourceFile;
		mSourceLine  = _sourceLine;
		mpSourceFunc = _sourceFunc;

		return true;
	}

	void
	CLogSystem::LogColor(uint8_t _color, const char *_pMessage, ...)
	{
		va_list		lstParams;

		va_start(lstParams, _pMessage);
		SendMessage(ELogMessage::LM_LogColor, _pMessage, lstParams, _color);
		va_end(lstParams);
	}

	//-------------------------------------
	void
	CLogSystem::Log(const char *_pMessage, ...)
	{
		va_list		lstParams;

		va_start(lstParams, _pMessage);
		SendMessage(ELogMessage::LM_Log, _pMessage, lstParams);
		va_end(lstParams);
	}

	//-------------------------------------
	void
	CLogSystem::Warning(const char *_pMessage, ...)
	{
		va_list		lstParams;

		va_start(lstParams, _pMessage);
		SendMessage(ELogMessage::LM_Warning, _pMessage, lstParams);
		va_end(lstParams);
	}

	//-------------------------------------
	void
	CLogSystem::Error(const char *_pMessage, ...)
	{
		va_list		lstParams;

		va_start(lstParams, _pMessage);
		SendMessage(ELogMessage::LM_Error, _pMessage, lstParams);
		va_end(lstParams);
	}

#if defined(_DEBUG) || defined(DEBUG)
	//-------------------------------------
	void
	CLogSystem::Debug(const char *_pMessage, ...)
	{
		va_list		lstParams;

		va_start(lstParams, _pMessage);
		SendMessage(ELogMessage::LM_Debug, _pMessage, lstParams);
		va_end(lstParams);
	}

	//-------------------------------------
	void
	CLogSystem::Assert(bool _isCondition, const char *_pMessage, ...)
	{
		va_list		lstParams;

		assert(_isCondition);
		if(_isCondition == false)
		{
			va_start(lstParams, _pMessage);
			SendMessage(ELogMessage::LM_Assert, _pMessage, lstParams);
			va_end(lstParams);
		}
	}

#else

	//-------------------------------------
	void
	CLogSystem::Debug(const char *, ...)
	{
	}

	//-------------------------------------
	void
	CLogSystem::Assert(bool, const char *, ...)
	{
	}

#endif

	//-------------------------------------
	void
	CLogSystem::Register(CLogger *_ptLogger)
	{
		if(mpLoggers != nullptr)
			_ptLogger->mpNext = mpLoggers;

#if defined(DEBUG) || defined(_DEBUG)
		else
			printf("Logger enabled\n");
#endif

		mpLoggers = _ptLogger;
	}

	//-------------------------------------
	void
	CLogSystem::UnRegister(CLogger *_ptLogger)
	{
		CLogger	*pLogger, *ptLast = 0;

		pLogger = mpLoggers;
		while(pLogger != nullptr)
		{
			if(pLogger == _ptLogger)
			{
				if(ptLast != nullptr)
					ptLast->mpNext = pLogger->mpNext;
				else
					mpLoggers = pLogger->mpNext;

				return;
			}
			ptLast = pLogger;
			pLogger  = pLogger->mpNext;
		}
	}

	//-------------------------------------
	void
	CLogSystem::SendMessage(ELogMessage _type, const char *_pMessage, va_list lst, uint8_t _color)
	{
		char		pBuffer[1024];
		CLogger *	pLogger;

		vsnprintf(pBuffer, sizeof(pBuffer), _pMessage, lst);

		pLogger = mpLoggers;
		while(pLogger != 0)
		{
			switch(_type)
			{
				case ELogMessage::LM_Log:
					pLogger->Log(pBuffer);
					break;

				case ELogMessage::LM_LogColor:
					pLogger->LogColor(_color, pBuffer);
					break;

				case ELogMessage::LM_Warning:
					pLogger->Warning(pBuffer);
					break;

				case ELogMessage::LM_Error:
					pLogger->Error(pBuffer);
					break;

				case ELogMessage::LM_Debug:
					pLogger->Debug(pBuffer);
					break;

				case ELogMessage::LM_Assert:
					pLogger->Assert(pBuffer);
					break;
			}
			pLogger = pLogger->mpNext;
		}
	}

} // end of namespace
