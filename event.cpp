#include "event.h"
#include "strings.h"

// event_string: a line that defines an event
Event::Event(std::string event_string) : tags() {
	std::stringstream ss;

	ss << event_string;

	// sets the first 3 words in the string to date values according to index.
	for (int_least16_t index = 0; index < 3; index++) {
		int_least16_t value_found;
		if (!(ss >> value_found)) {
			throw std::invalid_argument("Event has incorrect format (correct: DD MM YYYY [TAGS] DESCRIPTION)");
		}
		switch (index) {
		case 0:
			date.setDay(value_found);
			break;
		case 1:
			date.setMonth(value_found);
			break;
		case 2:
			date.setYear(value_found);
			break;
		}
	}
	// Set remaining contents to description and delete initial trail spaces
	std::getline(ss, description);
	while (description.size() > 0 && isspace(description[0])) {
		description.erase(0, 1);
	}

	if (int_least16_t tagClosureIndex = str_find_tag_clousure(description) != -1) {
		tags.setTags(description.substr(1, tagClosureIndex-1));
	}
}
