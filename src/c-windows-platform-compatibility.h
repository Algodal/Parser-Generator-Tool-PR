//////////////////////////////////////////////////////
//  Copyright (C) 2023 Alrick Grandison, Algodal™   //
//  filename: c-windows-platform-compatibility.h    //
//  created: 2023-08-30 12:33 AM                    //
//  description:                                    //
//////////////////////////////////////////////////////

//MARKER
#ifndef C_WINDOWS_PLATFORM_COMPATIBILITY_H
#define C_WINDOWS_PLATFORM_COMPATIBILITY_H

///@file c-windows-platform-compatibility.h
/// The primary purpose of this library is to make is easier to compile
/// linux code on Windows.  Unfortunately, Windows does not seriously
/// support C standards and make crazy code breaking changes that differ
/// greatly from how linux and unix do things.
/// The library may very lightly support differences linux/unix and android does
/// things differently.
/// This code does not support Apple.

#include <stdio.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
//Windows (64-bit and 32-bit)
//----------------------------

#include <direct.h>
#include <stdarg.h>

#define CWPC_BUFSIZ (size_t)1024 
//< Arbitary large size for buffers for (sprintf).  
//< We assume most strings will be less than this.
//< Edit this if you need a larger size.
//< We assume the buffer passed will be large enough

inline static FILE * cwpc_fopen(const char *filename, const char *mode)
{
    FILE *fp = 0;
    (void)fopen_s(&fp, filename, mode);
    return fp;
}

inline static int cwpc_sprintf(char *buffer, const char *format, ...)
{
    va_list args;
    va_start(args, format);
    int ret = vsprintf_s(buffer, CWPC_BUFSIZ, format, args);
    va_end(args);
    return ret;
}

inline static int cwpc_printf(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    int ret = vprintf_s(format, args);
    va_end(args);
    return ret;
}

inline static int cwpc_fprintf(FILE *fp, const char *format, ...)
{
    va_list args;
    va_start(args, format);
    int ret = vfprintf_s(fp, format, args);
    va_end(args);
    return ret;
}

inline static int cwpc_mkdir(const char * dirname, int mode)
{
    (void)mode;
    return _mkdir(dirname);
}

inline static int cwpc_rmdir(const char * dirname)
{
    return _mkdir(dirname);
}

inline static int cwpc_fclose(FILE *fp)
{
    return fclose(fp);
}

inline static int cwpc_remove(const char *filename)
{
    return remove(filename);
}

inline static char *cwpc_strdup(const char * srcStr)
{
    return _strdup(srcStr);
}

#ifdef _WIN64
//Windows (64-bit only)
//----------------------------

//

#else
//Windows (32-bit only)
//------------------------------

//

#endif
#else

//All Non-Windows System
//----------------------
#include <unistd.h>
#include <sys/stat.h>

#define cwpc_fopen(...) fopen(__VA_ARGS__)
#define cwpc_sprintf(...) sprintf(__VA_ARGS__)
#define cwpc_printf(...) printf(__VA_ARGS__)
#define cwpc_fprintf(...) fprintf(__VA_ARGS__)
#define cwpc_mkdir(...) mkdir(__VA_ARGS__)
#define cwpc_rmdir(...) rmdir(__VA_ARGS__)
#define cwpc_fclose(...) fclose(__VA_ARGS__)
#define cwpc_remove(...) remove(__VA_ARGS__)
#define cwpc_strdup(...) strdup(__VA_ARGS__)

#if __linux__ || __unix__
//Linux and Unix
//---------------

//

#endif

#if __ANDROID__
//Android
//-------

//

#endif

#if defined(_POSIX_VERSION)
//Posix
//----

//

#endif

#endif


#ifdef __cplusplus
}
#endif

#endif //C_WINDOWS_PLATFORM_COMPATIBILITY_H
//MARKER








