#include "event.h"
#include "rules/day-of-week.h"
#include "rules/dynamic-range.h"
#include "rules/fixed.h"
#include "rules/fixed-range.h"
#include "rules/wildcard.h"
#include <regex>
#include <stdexcept>
#include <string>

Event::~Event() {
	for (Rule* rule : rules) delete rule;
	rules.clear();
}

// event_string: a line that defines an event
Event::Event(std::list<Rule*>* rules, Tags* tags, std::string description) {
	 this->rules = *rules;
	 this->tags = tags;
	 this->description = description;
}

Event::Event(std::string str) {
	std::regex fixedRangeEventRegex(EVENT_FIXED_RANGE_REGEX);
	std::smatch match;

	// matches 1, 2, 3 = LowerLimit Date
	// matches 4, 5, 6 = UpperLimit Date
	if (std::regex_match(str, match, fixedRangeEventRegex)) {
		Date lowerLimit(std::stoi(match[1]), std::stoi(match[2]), std::stoi(match[3]));
		Date upperLimit(std::stoi(match[4]), std::stoi(match[5]), std::stoi(match[6]));
		RuleFixedRange rule(&lowerLimit, &upperLimit);
		rules.push_back(&rule);
		return;
	}

	std::regex eventRegex(EVENT_REGEX_STR);
	if (!std::regex_match(str, match, eventRegex)) throw std::invalid_argument("EVENT: Does not match EVENT_REGEX or EVENT_FIXED_RANGE_REGEX");

	std::string day		= match[1];
	std::string month	= match[2];
	std::string year	= match[3];
	std::string tags	= match[4];
	this->description	= match[5];

	// Rule Day of Week
	if (std::regex_match(day, std::regex("^" REGEX_DAY_OF_WEEK "$"))) {
		RuleDayOfWeek rule(day);
		rules.push_back(new RuleDayOfWeek(day));
	}

	// Rule Dynamic Range
	if (std::regex_match(day, std::regex("^" REGEX_DYNAMIC_RANGE_DAY_MONTH "$"))) {
		rules.push_back(new RuleDynamicRange(DAY, day));
	}

	if (std::regex_match(month, std::regex("^" REGEX_DYNAMIC_RANGE_DAY_MONTH "$"))) {
		rules.push_back(new RuleDynamicRange (MONTH, month));
	}

	if (std::regex_match(year, std::regex("^" REGEX_DYNAMIC_RANGE_YEAR "$"))) {
		rules.push_back(new RuleDynamicRange (YEAR, year));
	}

	// Rule Fixed
	if (std::regex_match(day, std::regex("^" REGEX_FIXED_DAY_MONTH "$"))) {
		rules.push_back(new RuleFixed (DAY, std::stoi(day)));
	}

	if (std::regex_match(month, std::regex("^" REGEX_FIXED_DAY_MONTH "$"))) {
		rules.push_back(new RuleFixed (MONTH, std::stoi(month)));
	}

	if (std::regex_match(year, std::regex("^" REGEX_FIXED_YEAR "$"))) {
		rules.push_back(new RuleFixed (YEAR, std::stoi(year)));
	}

	// Discuss if I should just get rid of the Wildcard Rule
	// Rule Wildcard
	if (std::regex_match(day, std::regex("^" REGEX_WILDCARD "$")) || std::regex_match(month, std::regex("^" REGEX_WILDCARD "$")) || std::regex_match(year, std::regex("^" REGEX_WILDCARD "$"))) {
		rules.push_back(new RuleWildcard);
	}
}

const bool Event::isValidIn(Date* date) {
	for (Rule* rule : rules) {
		if (!rule->isValidIn(date)) return false;
	}
	return true;
}
