#include "event.h"
#include "colors.h"
#include "rules/day-of-week.h"
#include "rules/dynamic-range.h"
#include "rules/fixed.h"
#include "rules/fixed-range.h"
#include "rules/wildcard.h"

Event::~Event() {
	for (Rule* rule : rules) delete rule;
	rules.clear();
	delete tags;
}

// event_string: a line that defines an event
Event::Event(std::list<Rule*>* rules, Tags* tags, std::string description) {
	 this->rules = *rules;
	 this->tags = tags;
	 this->description = description;
}

void Event::print(const Date* date) {
	std::cout << date->toString() << " ";
	if (tags->has("bold")) {
		std::cout << "\033[1m";
	}
	if (tags->has("italic")) {
		std::cout << "\033[3m";
	}
	if (tags->has("underline")) {
		std::cout << "\033[4m";
	}
	if (tags->has("blink")) {
		std::cout << "\033[5m";
	}
	if (tags->has("inverse")) {
		std::cout << "\033[7m";
	}
	if (tags->has("strike")) {
		std::cout << "\033[9m";
	}
	// TODO: Add Dynamic Colors
	if (tags->has("color")) {
		std::string colorName = (*tags)["color"];
		std::array<int_least16_t, 3> color = *Colors::get(colorName);
		std::cout << "\033[38;2;" << color[0] << ";" << color[1] << ";" << color[2] << "m";
	}

	std::cout << description;
	std::cout << "\033[0m";
	std::cout << std::endl;
}

Event::Event(std::string str) {
	std::regex fixedRangeEventRegex(EVENT_FIXED_RANGE_REGEX);
	std::smatch match;

	// matches 1, 2, 3 = LowerLimit Date
	// matches 4, 5, 6 = UpperLimit Date
	if (std::regex_match(str, match, fixedRangeEventRegex)) {
		Date lowerLimit(std::stoi(match[1]), std::stoi(match[2]), std::stoi(match[3]));
		Date upperLimit(std::stoi(match[4]), std::stoi(match[5]), std::stoi(match[6]));

		this->tags		= new Tags(match[7]);
		this->description	= match[8];

		rules.push_back(new RuleFixedRange (lowerLimit, upperLimit));
		return;
	}

	std::regex eventRegex(EVENT_REGEX_STR);
	if (!std::regex_match(str, match, eventRegex)) throw std::invalid_argument("EVENT: Does not match EVENT_REGEX or EVENT_FIXED_RANGE_REGEX");

	parseRules(match);
}

void Event::parseRules(std::smatch match) {
	std::string day		= match[1];
	std::string month	= match[2];
	std::string year	= match[3];
	this->tags		= new Tags(match[4]);
	this->description	= match[5];

	// Rule Day of Week
	if (std::regex_search(day, std::regex("^" REGEX_DAY_OF_WEEK "$"))) {
		RuleDayOfWeek rule(day);
		rules.push_back(new RuleDayOfWeek(day));
	}

	// Rule Dynamic Range
	if (std::regex_search(day, std::regex("^" REGEX_DYNAMIC_RANGE_DAY_MONTH "$"))) {
		rules.push_back(new RuleDynamicRange(DAY, day));
	}

	if (std::regex_search(month, std::regex("^" REGEX_DYNAMIC_RANGE_DAY_MONTH "$"))) {
		rules.push_back(new RuleDynamicRange (MONTH, month));
	}

	if (std::regex_search(year, std::regex("^" REGEX_DYNAMIC_RANGE_YEAR "$"))) {
		rules.push_back(new RuleDynamicRange (YEAR, year));
	}

	// Rule Fixed
	if (std::regex_search(day, std::regex("^" REGEX_FIXED_DAY_MONTH "$"))) {
		rules.push_back(new RuleFixed (DAY, std::stoi(day)));
	}

	if (std::regex_search(month, std::regex("^" REGEX_FIXED_DAY_MONTH "$"))) {
		rules.push_back(new RuleFixed (MONTH, std::stoi(month)));
	}

	if (std::regex_search(year, std::regex("^" REGEX_FIXED_YEAR "$"))) {
		rules.push_back(new RuleFixed (YEAR, std::stoi(year)));
	}

	// Rule Wildcard
	if (std::regex_search(day, std::regex("^" REGEX_WILDCARD "$"))) {
		rules.push_back(new RuleWildcard);
	}
	if (std::regex_search(month, std::regex("^" REGEX_WILDCARD "$"))) {
		rules.push_back(new RuleWildcard);
	}
	if (std::regex_search(year, std::regex("^" REGEX_WILDCARD "$"))) {
		if (year.size() > 1) {
			int_least16_t initialYear = std::stoi(year.substr(0, 3));
			rules.push_back(new RuleWildcard(initialYear));
			return;
		}
		rules.push_back(new RuleWildcard);
	}
}

bool Event::isValidIn(const Date* date) {
	for (Rule* rule : rules) {
		if (!rule->isValidIn(date)) return false;
	}
	return true;
}
