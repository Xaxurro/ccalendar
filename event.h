#ifndef H_CALENDAR_EVENT
#define H_CALENDAR_EVENT

#include <cctype>
#include <cstdint>
#include <sstream>
#include <stdexcept>
#include <string>
#include "date.h"
#include "tags.h"

class Event {
	private:
		Date date();
		Tags tags;
		std::string description = "";
	public:
		std::string getDescription() {
			return description;
		}

		Tags* getTags() {
			return &tags;
		}

		// event_string: a line that defines an event
		Event(std::string event_string) : tags() {
			std::stringstream ss;

			// storing `event_string` into `stringstream`
			ss << event_string;

			int value_found;
			// sets the first 3 words in the string to date values according to index.
			for (int index = 0; index < 3; index++) {
				if (!(ss >> value_found)) {
					throw std::invalid_argument("Event has incorrect format (correct: YYYY MM DD)");
				}
				switch (index) {
				case 0:
					setYear(value_found);
					break;
				case 1:
					setMonth(value_found);
					break;
				case 2:
					setDay(value_found);
					break;
				}
			}
			// Set remaining contents to description and delete initial trail spaces
			std::getline(ss, description);
			while (description.size() > 0 && isspace(description[0])) {
				description.erase(0, 1);
			}

			//Searches for [...] in the description and sends ... to Tag constructor
			std::size_t tagClosureIndex = description.find_first_of(']');
			if (tagClosureIndex != description.npos && description[0] == '[') {
				tags.setTags(description.substr(1, tagClosureIndex-1));
			}

			//Sets the Event Object as Invalid if no description, there should be a better way to do this
			if (description.empty()) {
				year = 0;
				month = 0;
				day = 0;
			}
		}
};
#endif // !H_CALENDAR_EVENT
