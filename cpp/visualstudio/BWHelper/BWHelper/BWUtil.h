#pragma once
#include<string>
#include<vector>

class CBWUtil
{
public:
	CBWUtil();
	~CBWUtil();

	void StringTokenize(const std::string& str, std::vector<std::string>& tokens, const std::string& delimiters = " ");
 
};

