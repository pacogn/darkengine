#pragma once

//-------------------------------------
#include "logEnums.h"
//-------------------------------------
#include <cstdarg>
#include <cstdint>
//-------------------------------------


//-------------------------------------
namespace MindShake
{

	//---------------------------------
	class CLogger;
	//---------------------------------

	//---------------------------------
	class CLogSystem
	{
		friend class CLogger;

		public:
			static void		Free();												// Destructor

			static bool 	SetOwner(const char *_sourceFile, const unsigned int _sourceLine, const char *_sourceFunc);

			static void		LogColor(uint8_t _color, const char *_pMessage, ...);
			static void		Log(const char *_pMessage, ...);
			static void 	Warning(const char *_pMessage, ...);
			static void 	Error(const char *_pMessage, ...);

	#if defined(_DEBUG) || defined(DEBUG)
			static void 	Debug(const char *_pMessage, ...);
			static void		Assert(bool _isCondition, const char *_pMessage, ...);
	#else
			static void 	Debug(const char *_pMessage, ...);
			static void		Assert(bool _isCondition, const char *_pMessage, ...);
	#endif

		// Do not use this if you aren't Darky!
		public:
			static void		Register(CLogger *_ptLogger);
			static void		UnRegister(CLogger *_ptLogger);

		protected:
			static void		SendMessage(ELogMessage _type, const char *_pMessage, va_list lst, uint8_t _color = 0);

		protected:
			static bool			mHaveOwner;
			static const char *	mpSourceFile;
			static unsigned int	mSourceLine;
			static const char *	mpSourceFunc;

			static CLogger	*	mpLoggers;
	};

} // end of namespace
