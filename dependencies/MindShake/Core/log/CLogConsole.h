#pragma once

//-------------------------------------
#include <Common/Core/platform.h>
//-------------------------------------
#include "CLogFile.h"
//-------------------------------------


//-------------------------------------
namespace MindShake
{

	//---------------------------------
	class CLogConsole : public CLogFile
	{
		public:
							CLogConsole(bool _autoFlush=true, bool _showExtraInfo=true, bool _showLogCaption=false);
			virtual			~CLogConsole() {}

					void	LogColor(uint8_t _color, const char *_pMessage);

#if defined(TARGET_PLATFORM_WINDOWS)
					void	Write(ELogMessage _type, const char *_pMsg, uint8_t _color = FC_LightGray);
#endif

#if defined(TARGET_PLATFORM_WINDOWS)
		protected:
			void	*mpHandler;
#endif
	};

} // end of namespace
