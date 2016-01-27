#pragma once
#include <string>
#include <vector>

class CBWHelper
{
public:
	CBWHelper(void);
	~CBWHelper(void);

	void StringTokenize(const std::string& str, std::vector<std::string>& tokens, const std::string& delimiters = " ");
	std::string StringFormat(const char *fmt, ...);

};
