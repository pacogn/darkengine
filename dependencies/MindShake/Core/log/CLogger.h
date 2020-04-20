#pragma once

#include <cstdint>

//-------------------------------------
namespace MindShake
{

	//---------------------------------
	class CLogSystem;
	//---------------------------------

	//---------------------------------
	class CLogger
	{
		friend class CLogSystem;

		public:
			enum class ELoggerType
			{
				LT_Unknown,
				LT_Console,
				LT_File,
			};

		public:
							CLogger();
			virtual			~CLogger();

					void	SetShowTime(bool _set);

		protected:
			virtual void	Log(const char *_pMessage)                         = 0;
			virtual void	LogColor(uint8_t _color, const char *_pMessage)      = 0;
			virtual void 	Warning(const char *_pMessage)                     = 0;
			virtual void 	Error(const char *_pMessage)                       = 0;
			virtual void 	Debug(const char *_pMessage)                       = 0;
			virtual void	Assert(const char *_pMessage)                      = 0;

		protected:
			CLogger		*mpNext;
			ELoggerType	mLoggerType;
			bool		mShowTime;
	};

} // end of namespace
