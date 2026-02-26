#include "../rules/rule.h"
#include "../colors.h"
#include <iostream>

int main () {
	std::cout << "EVENT_REGEX_STR\n" << EVENT_REGEX_STR << std::endl;
	std::cout << "EVENT_FIXED_RANGE_REGEX\n" << EVENT_FIXED_RANGE_REGEX << std::endl;
	std::cout << "COLOR_RGB_REGEX\n" << COLOR_RGB_REGEX << std::endl;
	std::cout << "COLOR_HEX_REGEX\n" << COLOR_HEX_REGEX << std::endl;
	return 0;
}
