#include "strings.h"
#include <cctype>
#include <cstdint>
#include <string>

bool str_is_blank(std::string str) {
	for (char c : str) if (!isspace(c)) return false;
	return true;
}

int_least16_t str_find_tag_clousure(std::string str, char opening, char closure) {
	//Searches for [...] at the start of description, returns -1 if NOT found, otherwise the index of the ']' character
	//also returns -1 when the initial character isn't tag opening
	if (str[0] != opening) return -1;
	size_t tagClosureIndex = str.find_first_of(closure);
	if (tagClosureIndex == str.npos) return -1;
	return tagClosureIndex;
}

bool str_has_value(std::string tag) {
	return tag.find('=') != tag.npos && tag.find_first_of('=') == tag.find_last_of('=');
}

std::string str_trim_left(std::string str) {
	int_least16_t index = 0;
	char c = str[0];
	while (isspace(c)) {
		index++;
		c = str[index];
	}
	return str.substr(index);
}
