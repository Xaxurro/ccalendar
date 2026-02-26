#pragma once

#include <cstdint>
#include <list>
#include <string>
#include "date.h"

namespace str {
	//returns `true` if has only whitespaces, `false otherwise`
	bool is_blank(std::string str);

	//returns the position of `clousure` inside `description` ONLY if `opening` is present **BEFORE**
	//also returns -1 when the initial character isn't tag opening
	int_least16_t find_tag_clousure(std::string str, char opening, char closure);

	//returns the contents that are in between `opening` and `closure`
	std::string get_contents(std::string str, char opening, char closure);

	//Searches inside "[...]" and checks `tag` exists within
	bool has_value(std::string tag);

	std::string trim_left(std::string str);

	//Searches each ocurrence of `strToSearch` and replaces it with `strToCompare` inside `str`
	void replace(std::string strToSearch, std::string strToReplace, std::string* str);

	//Splits `str` everytime `delimiter` is present
	std::list<std::string> split(std::string delimiter, std::string* str);
}
