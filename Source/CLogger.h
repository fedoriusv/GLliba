#ifndef _CLOGGER_H_
#define _CLOGGER_H_

#include <cstdio>
#include <cstring>
#include <cstdarg>
#include <assert.h>

#ifdef _DEBUG
#	define LOG_CONSOLE(x)	std::cout << x << "\n"
#	define ASSERT(x)        assert(x)
#else
#	define LOG_CONSOLE(x)
#	define ASSERT(x)        
#endif

#if defined(_MSC_VER)
#	define LOG_DEBUG(str,...) LoggerWrite("%s:%s:%d DEBUG " str, __FILE__, __FUNCTION__, __LINE__, ##__VA_ARGS__)
#	define LOG_ERROR(str,...) LoggerWrite("%s:%s:%d ERROR " str, __FILE__, __FUNCTION__, __LINE__, ##__VA_ARGS__)
#elif defined(__MINGW32__)
#	define LOG_DEBUG(str,...) LoggerWrite("%s:%s:%d DEBUG " str, __FILE__, __func__, __LINE__, ##__VA_ARGS__)
#	define LOG_ERROR(str,...) LoggerWrite("%s:%s:%d ERROR " str, __FILE__, __func__, __LINE__, ##__VA_ARGS__)
#endif

void LoggerCreate( const char* _fileName );

void LoggerDestroy();

void LoggerWrite( const char* _format, ... );

#endif

