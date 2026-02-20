#include "tags.h"
#include <string>

Tags::Tags(std::string str) {
	if (str[0] == '[' && str[str.size() - 1] == ']') {
		setTags(str.substr(1, str.size() - 2));
		return;
	}
	setTags(str);
}

// Returns `true` if tag is present in tag list
bool Tags::has(std::string tagToSearch) {
	if (str::is_blank(tagToSearch)) return false;

	if (str::has_value(tagToSearch)) tagToSearch = tagToSearch.substr(0, tagToSearch.find('='));
	if (str::is_blank(tagToSearch)) return false; 

	//true if exist in map
	return tags.count(tagToSearch) > 0;
}

void Tags::addTag(std::string tagsStr) {
	std::stringstream ss;
	ss << tagsStr;
	std::string newTag = "";
	while(ss >> newTag) {
		//Set Tag's value "" if '=' not present
		size_t valuePosition = newTag.find('=');
		if (valuePosition == newTag.npos) {
			tags[newTag] = "";
			continue;
		}

		std::stringstream ssTagWithValue;
		std::string newValue = "";

		newTag.replace(valuePosition, 1, " ");
		if (str::is_blank(newTag) || newTag[0] == ' ') continue;

		ssTagWithValue << newTag;
		ssTagWithValue >> newTag;
		ssTagWithValue >> newValue;
		//If no tag name can't add the tag, if 1st character blank is this case -> "=value"
		if (str::is_blank(newTag)) continue;
		//If no tag value add the default ("")
		if (str::is_blank(newValue)) tags[newTag] = "";
		//If both add the value to the tag
		tags[newTag] = newValue;
	}
}

void Tags::setTags(std::string tagsStr) {
	tags.clear();
	if (str::is_blank(tagsStr)) return;

	addTag(tagsStr);
}
