#include "strings.h"
#include <cctype>
#include <cstdint>
#include <list>
#include <string>

namespace str {
	bool is_blank(std::string str) {
		for (char c : str) if (!isspace(c)) return false;
		return true;
	}

	int_least16_t find_tag_clousure(std::string str, char opening, char closure) {
		if (str[0] != opening) return -1;
		size_t tagClosureIndex = str.find_first_of(closure);
		if (tagClosureIndex == str.npos) return -1;
		return tagClosureIndex;
	}

	std::string get_contents(std::string str, char opening, char closure) {
		size_t closure_position = str::find_tag_clousure(str, opening, closure);
		if (closure_position == (size_t)-1) return "";
		return str.substr(1, closure_position-1);
	}

	bool has_value(std::string tag) {
		return tag.find('=') != tag.npos && tag.find_first_of('=') == tag.find_last_of('=');
	}

	std::string trim_left(std::string str) {
		int_least16_t index = 0;
		char c = str[0];
		while (isspace(c)) {
			index++;
			c = str[index];
		}
		return str.substr(index);
	}

	//Searches in `str` all ocurrences of `strToSearch` and replaces them with `strToReplace`
	void replace(std::string strToSearch, std::string strToReplace, std::string* str) {
		size_t ocurrence = str->find(strToSearch);
		while (ocurrence != std::string::npos) {
			str->replace(ocurrence, strToSearch.size(), strToReplace);
			ocurrence = str->find(strToSearch, ocurrence + strToReplace.size());
		}
	}

	std::list<std::string> split(std::string delimiter, std::string* str) {
		std::list<std::string> ocurrencesList = {};
		size_t position = str->find(delimiter);

		while(position != str->npos) {
			ocurrencesList.push_back(str->substr(0, position));
			str->erase(0, position + 1);
			position = str->find(delimiter, position + delimiter.size());
		}

		ocurrencesList.push_back(*str);
		return ocurrencesList;
	}
}
