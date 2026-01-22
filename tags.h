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
		size_t size() { return tags.size(); }

		std::string operator [](std::string tagToSearch) { return tags[tagToSearch]; }

		// Returns `true` if tag is present in tag list
		bool has(std::string tagToSearch);

		void setTags(std::string tagsStr);
};
#endif // !H_CALENDAR_TAGS
