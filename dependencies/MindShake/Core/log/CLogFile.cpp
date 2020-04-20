//-------------------------------------
#include <Common/Core/configCoreLib.h>
//-------------------------------------
#include "CLogFile.h"
#include "log.h"
//-------------------------------------
#include <time.h>
//-------------------------------------


//-------------------------------------
namespace MindShake
{

	//---------------------------------
	CLogFile::CLogFile(FILE *_pFile, bool _autoFlush, bool _showExtraInfo, bool _showLogCaption)
	{
		mLoggerType     = ELoggerType::LT_File;

		mpFile          = _pFile;
		mMustCloseFile  = false;
		mAutoFlush      = _autoFlush;
		mShowExtraInfo  = _showExtraInfo;
		mShowLogCaption = _showLogCaption;
		mThreadSafe     = false;
	}

	//---------------------------------
	CLogFile::CLogFile(const char *_pFilename, bool _autoFlush, bool _showExtraInfo, bool _showLogCaption)
	{
		mpFile = fopen(_pFilename, "wt");
		if(mpFile == nullptr)
			MS_ERROR("No se puede crear el fichero '%s'", _pFilename);

		mMustCloseFile  = true;
		mAutoFlush      = _autoFlush;
		mShowExtraInfo  = _showExtraInfo;
		mShowLogCaption = _showLogCaption;
		mThreadSafe     = false;
	}

	//---------------------------------
	CLogFile::~CLogFile()
	{
		if(mMustCloseFile && (mpFile != nullptr))
		{
			fclose(mpFile);
			mpFile = nullptr;
		}
	}

	//---------------------------------
	void
	CLogFile::SetThreadSafe(bool _set)
	{
		mThreadSafe = _set;
	}

	//---------------------------------
	void
	CLogFile::Log(const char *_pMessage)
	{
		//Write(mShowExtraInfo & mShowLogCaption, "Log", _pMessage);
		Write(ELogMessage::LM_Log, _pMessage);
	}

	//---------------------------------
	void
	CLogFile::Warning(const char *_pMessage)
	{
		//Write(mShowExtraInfo, "Warning", _pMessage);
		Write(ELogMessage::LM_Warning, _pMessage);
	}

	//---------------------------------
	void
	CLogFile::Error(const char *_pMessage)
	{
//		Write(mShowExtraInfo, "Error", _pMessage);
		Write(ELogMessage::LM_Error, _pMessage);
	}

	//---------------------------------
	void
	CLogFile::Debug(const char *_pMessage)
	{
//		Write(mShowExtraInfo, "Debug", _pMessage);
		Write(ELogMessage::LM_Debug, _pMessage);
	}

	//---------------------------------
	void
	CLogFile::Assert(const char *_pMessage)
	{
//		Write(mShowExtraInfo, "Assert", _pMessage);
		Write(ELogMessage::LM_Assert, _pMessage);
	}

	//---------------------------------
//	void
//	CLogFile::Write(bool _cond, const char *_pCaption, const char *_pMsg)
//	{
//		if(mpFile == nullptr)
//			return;
//
//		if(mThreadSafe) mMutexLog.Lock();
//		{
//
//			if(mShowTime)
//			{
//
//#if defined(TARGET_PLATFORM_WINDOWS)
//				SYSTEMTIME st;
//
//				GetSystemTime(&st);
//				fprintf(mpFile, "%02d:%02d:%02d:%03d ", st.wHour+1, st.wMinute, st.wSecond, st.wMilliseconds);
//#else
//				time_t			timeStart;
//				struct tm 		currentTime;
//
//				time(&timeStart);
//				currentTime = *localtime(&timeStart);
//				fprintf(mpFile, "%02d:%02d:%02d ", currentTime.tm_hour, currentTime.tm_min, currentTime.tm_sec);
//#endif
//			}
//
//			if(_cond)
//				fprintf(mpFile, "%s: ", _pCaption);
//
//			fprintf(mpFile, "%s\n", _pMsg);
//		}
//		if(mThreadSafe) mMutexLog.Unlock();
//
//		if(mAutoFlush)
//			fflush(mpFile);
//	}

	//---------------------------------
	void
	CLogFile::Write(ELogMessage _type, const char *_pMsg, uint8_t _color)
	{
		if(mpFile == nullptr)
			return;

		if(mThreadSafe) mMutexLog.Lock();
		{
			WriteAux(_type, _pMsg, _color);
		}
		if(mThreadSafe) mMutexLog.Unlock();

		if(mAutoFlush)
			fflush(mpFile);
	}

	//---------------------------------
	void
	CLogFile::WriteAux(ELogMessage _type, const char *_pMsg, uint8_t)
	{
		if(mShowTime)
		{

#if defined(TARGET_PLATFORM_WINDOWS)
			SYSTEMTIME st;

			GetSystemTime(&st);
			fprintf(mpFile, "%02d:%02d:%02d:%03d ", st.wHour+1, st.wMinute, st.wSecond, st.wMilliseconds);
#else
			time_t			timeStart;
			struct tm 		currentTime;

			time(&timeStart);
			currentTime = *localtime(&timeStart);
			fprintf(mpFile, "%02d:%02d:%02d ", currentTime.tm_hour, currentTime.tm_min, currentTime.tm_sec);
#endif
		}

		if(mShowExtraInfo)
		{
			switch(_type)
			{
				case ELogMessage::LM_Log:
				case ELogMessage::LM_LogColor:
					if(mShowLogCaption)
						fprintf(mpFile, "Log: ");
					break;

				case ELogMessage::LM_Warning:
					fprintf(mpFile, "Warning: ");
					break;

				case ELogMessage::LM_Error:
					fprintf(mpFile, "Error: ");
					break;

				case ELogMessage::LM_Debug:
					fprintf(mpFile, "Debug: ");
					break;

				case ELogMessage::LM_Assert:
					fprintf(mpFile, "Assert: ");
					break;
			}
		}

		fprintf(mpFile, "%s\n", _pMsg);
	}

} // end of namespace
