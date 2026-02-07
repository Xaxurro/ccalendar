#include "event.h"
#include "rules/fixed-range.h"
#include <iostream>
#include <regex>
#include <stdexcept>
#include <string>

// event_string: a line that defines an event
Event::Event(std::list<Rule*>* rules, Tags* tags, std::string description) {
	 this->rules = rules;
	 this->tags = tags;
	 this->description = description;
}

Event::Event(std::string str) {
	std::regex fixedRangeEventRegex(EVENT_FIXED_RANGE_REGEX);
	std::smatch match;

	if (std::regex_match(str, match, fixedRangeEventRegex)) {
		Date lowerLimit(std::stoi(match[1]), std::stoi(match[2]), std::stoi(match[3]));
		Date upperLimit(std::stoi(match[4]), std::stoi(match[5]), std::stoi(match[6]));
		RuleFixedRange rule(&lowerLimit, &upperLimit);
		rules->push_back(&rule);
		return;
	}

	std::regex eventRegex(EVENT_REGEX_STR);
	if (!std::regex_match(str, match, eventRegex)) throw std::invalid_argument("EVENT: Does not match EVENT_REGEX or EVENT_FIXED_RANGE_REGEX");
}
