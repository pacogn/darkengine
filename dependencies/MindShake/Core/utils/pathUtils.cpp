#include "pathUtils.h"

#if defined(TARGET_PLATFORM_WINDOWS)

    #include <direct.h>

    #define chdir		_chdir
    #define mkdir		_mkdir
    #define rmdir		_rmdir
    #define	getcwd		_getcwd
    #define	stat		_stat

#else

    //-------------------------------------
    #include <Common/Core/stringAux.h>
    #include <unistd.h>
    #include <wchar.h>
    //-------------------------------------

    // small helper function, copies only a part of a string into another
    // (we append a 0 in contrary to strncpy)
    static inline void
    strcpypart(char* dest, const char* src, size_t size)
    {
        memcpy(dest, src, size);
        dest[size] = 0;
    }

    // Unix version of the _splitpath functions which breaks a path into it's
    // components. (Warning: Don't use in your own code, you're asking for security
    // problems (buffer overflow)
    void
    splitpath(const char* path, char* drive, char* dir, char* fname, char* ext)
    {
        // Step1: Fill in driver ("" on unix systems since we don't have drives)
        if(drive)
            strcpy(drive, "");

        // Step1: find the last slash in the path
        const char* lastslash = 0;
        for(const char* p = path; *p != '\0'; p++) {
            if(*p == '/')
                lastslash = p;
        }
        // now fill in directory
        if(dir) 
        {
            if(lastslash == 0)
                strcpy(dir, "");
            else
                strcpypart(dir, path, lastslash - path + 1);
        }

        // Step2: Get the (last) dot in the filename
        const char* lastdot = 0;
        const char* begin = (lastslash != 0) ? lastslash+1 : path;
        for(const char* p = begin; *p != '\0'; p++) {
            if(*p == '.')
                lastdot = p;
        }
        // now we can fill in filename and extension
        if(lastdot==0) {
            if(fname)
                strcpy(fname, begin);
            if(ext)
                strcpy(ext, "");
        } else {
            if(fname)
                strcpypart(fname, begin, lastdot - begin);
            if(ext)
                strcpy(ext, lastdot);
        }

    }

    // small helper function, copies only a part of a string into another
    // (we append a 0 in contrary to strncpy)
    static inline void
    wstrcpypart(wchar_t* dest, const wchar_t* src, size_t size)
    {
        memcpy(dest, src, size*sizeof(wchar_t));
        dest[size] = L'\0';
    }

    // Unix version of the _splitpath functions which breaks a path into it's
    // components. (Warning: Don't use in your own code, you're asking for security
    // problems (buffer overflow)
    void 
    wsplitpath(const wchar_t* path, wchar_t* drive, wchar_t* dir, wchar_t* fname, wchar_t* ext)
    {
        // Step1: Fill in driver ("" on unix systems since we don't have drives)
        if(drive)
            wcscpy(drive, L"");

        // Step1: find the last slash in the path
        const wchar_t* lastslash = 0;
        for(const wchar_t* p = path; *p != L'\0'; p++) {
            if(*p == L'/')
                lastslash = p;
        }
        // now fill in directory
        if(dir) 
        {
            if(lastslash == 0)
                wcscpy(dir, L"");
            else
                wstrcpypart(dir, path, lastslash - path + 1);
        }

        // Step2: Get the (last) dot in the filename
        const wchar_t* lastdot = 0;
        const wchar_t* begin = (lastslash != 0) ? lastslash+1 : path;
        for(const wchar_t* p = begin; *p != L'\0'; p++) {
            if(*p == L'.')
                lastdot = p;
        }
        // now we can fill in filename and extension
        if(lastdot==0) {
            if(fname)
                wcscpy(fname, begin);
            if(ext)
                wcscpy(ext, L"");
        } else {
            if(fname)
                wstrcpypart(fname, begin, lastdot - begin);
            if(ext)
                wcscpy(ext, lastdot);
        }

        //printf ("Splitted Path : %s => %s - %s - %s - %s.\n", path,
        //          drive, dir, fname, ext);
    }

#endif

//-------------------------------------
bool
SetApplicationDirectory(char **argv) {
    char    dir[2048];
    int     res;

    if (argv == nullptr || argv[0] == nullptr)
        return false;

    splitpath(argv[0], nullptr, dir, nullptr, nullptr);

#if defined(TARGET_PLATFORM_MACOSX)
    strcat(dir, "../");
#endif

    res = chdir(dir);

    return (res == 0);
}

