#include "strings.h"
#include <cctype>
#include <cstdint>

bool str_is_blank(std::string str) {
	for (char c : str) if (!isspace(c)) return false;
	return true;
}

int_least16_t str_find_tag_clousure(std::string description) {
	//Searches for [...] at the start of description, returns -1 if NOT found, otherwise the index of the ']' character
	if (description[0] != '[') return -1;
	int_least16_t tagClosureIndex = description.find_first_of(']');
	if (tagClosureIndex == description.npos) return -1;
	return tagClosureIndex;
}

bool str_has_value(std::string tag) {
	return tag.find('=') != tag.npos && tag.find_first_of('=') == tag.find_last_of('=');
}
