#include "event.h"
#include <regex>
#include <string>

// event_string: a line that defines an event
Event::Event(std::list<Rule*>* yearRules, std::list<Rule*>* monthRules, std::list<Rule*>* dayRules, Tags* tags, std::string description) {
	 this->yearRules = yearRules;
	 this->monthRules = monthRules;
	 this->dayRules = dayRules;
	 this->tags = tags;
	 this->description = description;
}

Event::Event(std::string str) {
	std::regex eventRegex(EVENT_REGEX_STR);
	std::smatch match;
	std::regex_match(str, match, eventRegex);

}
