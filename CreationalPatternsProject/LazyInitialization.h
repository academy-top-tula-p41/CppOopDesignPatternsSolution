#pragma once
#include <iostream>

class Widget
{
	std::string* str{};
public:
	std::string GetStr()
	{
		if (!str)
			str = new std::string();

		return *str;
	}
};

