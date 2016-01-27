#include "StdAfx.h"
#include "BWHelper.h"
#include <stdarg.h>

CBWHelper::CBWHelper(void)
{
}

CBWHelper::~CBWHelper(void)
{
}

void CBWHelper::StringTokenize(const std::string & str, std::vector<std::string>& tokens, const std::string & delimiters)
{
	// Skip delimiters at beginning.
	std::string::size_type lastPos = str.find_first_not_of(delimiters, 0);
	// Find first "non-delimiter".
	std::string::size_type pos = str.find_first_of(delimiters, lastPos);

	while (std::string::npos != pos || std::string::npos != lastPos)
	{
		// Found a token, add it to the vector.
		tokens.push_back(str.substr(lastPos, pos - lastPos));
		// Skip delimiters.  Note the "not_of"
		lastPos = str.find_first_not_of(delimiters, pos);
		// Find next "non-delimiter"
		pos = str.find_first_of(delimiters, lastPos);
	}
}

std::string CBWHelper::StringFormat(const char * fmt, ...)
{
	int result = -1, length = 256;
	char *buffer = NULL;
	va_list args;
	va_start(args, fmt);

	while (result == -1)
	{
		if (buffer) delete[] buffer;
		buffer = new char[length + 1];
		memset(buffer, 0x00, length + 1);
		result = _vsnprintf_s(buffer,length, _TRUNCATE, fmt, args);
		length *= 2;
	}
	va_end(args);

	std::string retStr(buffer);
	delete[] buffer;

	return retStr;
}
