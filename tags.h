#ifndef H_CALENDAR_TAGS
#define H_CALENDAR_TAGS
#include "strings.h"
#include <cctype>
#include <cstddef>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
class Tags {
	private:
		std::map<std::string, std::string> tags {};

		void addTag(std::string tagStr);
	public:
		Tags(std::string str);
		size_t size() { return tags.size(); }

		std::string operator [](std::string tagToSearch) { return tags[tagToSearch]; }

		// Returns `true` if tag is present
		bool has(std::string tagToSearch);

		void setTags(std::string tagsStr);
};
#endif // !H_CALENDAR_TAGS
