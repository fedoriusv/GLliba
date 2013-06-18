#include "CLogger.h"

static const int	LOGGER_FILENAME_MAX						= 256;
static char			g_LoggerFileName[LOGGER_FILENAME_MAX]	= "error.log";

void LoggerCreate(const char* _fileName)
{
	FILE *output;

	memset(g_LoggerFileName, 0, LOGGER_FILENAME_MAX);
	strncpy(g_LoggerFileName, _fileName, LOGGER_FILENAME_MAX - 1);

	if ((output = fopen(g_LoggerFileName, "w")) != NULL)
		fclose(output);
}

void LoggerDestroy()
{
	//
}

void LoggerWrite(const char* _format, ...)
{
	va_list ap;
	FILE    *output;

	if ((output = fopen(g_LoggerFileName, "a+")) == NULL)
		return;

	va_start(ap, _format);
	vfprintf(output, _format, ap);
	va_end(ap);

	fclose(output);
}
