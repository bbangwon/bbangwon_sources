// BWCHelperPrj.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "BWHelper.h"

#include <algorithm>
#include <iostream>
#include <iterator>

CBWHelper util;

void StringTokenize()
{
	//StringTokenize Sample
	std::vector<std::string> tokens;
	std::string str = "Split me up! Word1 Word2 Word3.";
	util.StringTokenize(str, tokens);

	std::copy(tokens.begin(), tokens.end(), std::ostream_iterator<std::string>(std::cout, ", "));
	std::cout << std::endl;
}

void StringForamt()
{
	std::cout << util.StringFormat("Hello %s!", "Format String") << std::endl;

}

int _tmain(int argc, _TCHAR* argv[])
{
	StringTokenize();
	StringForamt();

	return 0;
}


