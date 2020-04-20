#pragma once

#include <Common/Core/platform.h>

#if defined(TARGET_PLATFORM_WINDOWS)

    #include <stdlib.h>
    #define splitpath       _splitpath
    #define wsplitpath      _wsplitpath
    
#else

    void    splitpath(const char* path, char* drive, char* dir, char* fname, char* ext);
    void    wsplitpath(const wchar_t* path, wchar_t* drive, wchar_t* dir, wchar_t* fname, wchar_t* ext);

 #endif

bool    SetApplicationDirectory(char **argv);
