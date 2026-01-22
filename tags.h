#ifndef H_CALENDAR_TAGS
#define H_CALENDAR_TAGS
#include <cctype>
#include <cstddef>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
class Tags {
	private:
		std::map<std::string, std::string> tags {};

		bool isEmpty(std::string str) {
			for (char c : str) if (!isspace(c)) return false;
			return true;
		}

		// Returns `true` if has ONLY one '=', meaning it has a valid value otherwise `false`
		bool hasValidValue(std::string tag) {
			return tag.find('=') != tag.npos && tag.find_first_of('=') == tag.find_last_of('=');
		}
	public:
		size_t size() {
			int size_value = tags.size();
			return tags.size();
		}

		// Returns `true` if tag is present in tag list
		bool has(std::string tagToSearch) {
			if (isEmpty(tagToSearch)) return false;

			if (hasValidValue(tagToSearch)) tagToSearch = tagToSearch.substr(0, tagToSearch.find('='));
			if (isEmpty(tagToSearch)) return false; 

			return tags.count(tagToSearch) > 0;
		}

		std::string getValue(std::string tagToSearch) {
			return tags[tagToSearch];
		}

		void setTags(std::string tagsStr) {
			tags.clear();
			if (isEmpty(tagsStr)) return;

			std::stringstream ss;
			ss << tagsStr;
			std::string newTag = "";
			while(ss >> newTag) {
				size_t position = newTag.find('=');
				if (position == newTag.npos) {
					tags[newTag] = "";
					continue;
				}
				std::stringstream ssTagWithValue;
				std::string newValue = "";

				newTag.replace(position, 1, " ");
				if (isEmpty(newTag) || newTag[0] == ' ') continue;

				ssTagWithValue << newTag;
				ssTagWithValue >> newTag;
				ssTagWithValue >> newValue;
				if (isEmpty(newTag)) continue;
				if (isEmpty(newValue)) tags[newTag] = "";
				tags[newTag] = newValue;
			}
		}
};
#endif // !H_CALENDAR_TAGS
