#pragma once

//-------------------------------------
#include "CLogger.h"
#include "logEnums.h"
//-------------------------------------
#include <Common/Kernel/mt/CMiniCriticalSection.h>
#include <Common/Core/console/msColors.h>
//-------------------------------------
#include <stdio.h>
//-------------------------------------


//-------------------------------------
namespace MindShake
{

	//---------------------------------
	class CLogFile : public CLogger
	{
		public:
							CLogFile(FILE *_pFile, bool _autoFlush=true, bool _showExtraInfo=true, bool _showLogCaption=true);
							CLogFile(const char *_pFilename="Logs.log", bool _autoFlush=true, bool _showExtraInfo=true, bool _showLogCaption=true);
			virtual			~CLogFile();

					void	SetThreadSafe(bool _set = true);

					void	Log(const char *_pMessage);
			virtual	void	LogColor(uint8_t _color, const char *_pMessage)		{ Log(_pMessage); } 
					void 	Warning(const char *_pMessage);
					void 	Error(const char *_pMessage);
					void 	Debug(const char *_pMessage);
					void	Assert(const char *_pMessage);

		protected:
					//void	Write(bool _cond, const char *_pCaption, const char *_pMsg);
			virtual	void	Write(ELogMessage _type, const char *_pMsg, uint8_t _color = MindShake::FC_LightGray);
			virtual	void	WriteAux(ELogMessage _type, const char *_pMsg, uint8_t _color = MindShake::FC_LightGray);

		protected:
			CMiniCriticalSection	mMutexLog;

		protected:
			FILE *	mpFile;
			bool	mMustCloseFile;

		public:
			bool	mAutoFlush;
			bool	mShowExtraInfo;
			bool	mShowLogCaption;
			bool	mThreadSafe;
	};

} // end of namespace
