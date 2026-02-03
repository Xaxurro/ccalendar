#include "event.h"
#include <regex>

// event_string: a line that defines an event
Event::Event(Date dateNew, Tags tagsNew, std::string descriptionNew) {
	 date = dateNew;
	 tags = tagsNew;
	 description = descriptionNew;
}

std::list<Event> Event::fromString(std::string str) {
	std::regex eventRegex(EVENT_REGEX_STR);
	std::smatch match;
	std::regex_match(str, match, eventRegex);

}
