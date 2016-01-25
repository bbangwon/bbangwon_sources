// BWHelper.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"
#include "BWUtil.h"

#include <algorithm>
#include <iostream>
#include <iterator>

CBWUtil util;
void StringTokenize();

int main()
{
	StringTokenize();
    return 0;
}

void StringTokenize()
{
	//StringTokenize Sample
	std::vector<std::string> tokens;
	std::string str = "Split me up! Word1 Word2 Word3.";
	util.StringTokenize(str, tokens);

	std::copy(tokens.begin(), tokens.end(), std::ostream_iterator<std::string>(std::cout, ", "));
}

