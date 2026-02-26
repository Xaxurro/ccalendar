#include "rule.h"
#include "day-of-week.h"
#include "dynamic-range.h"
#include "fixed.h"
#include "list.h"
#include "wildcard.h"

#include "../strings.h"
#include <iostream>
#include <stdexcept>
#include <string>

Rule* Rule::fromString(std::string str, int_least16_t measure) {
	std::string listContents = str::get_contents(str, '{', '}');
	//Single Rule
	if (str::is_blank(listContents)) {
		Rule* newRule = parseRule(str, measure);
		return newRule;
	}
	//Multiple Rules
	RuleList* ruleList = new RuleList();
	for (std::string newRuleStr : str::split(" ", &listContents)) {

		Rule* newRule = parseRule(newRuleStr, measure);
		//Checking for default nullptr return value
		if (newRule == nullptr) {
			std::cout << str << std::endl;
			throw std::invalid_argument("Error when parsing line above, didn't matched any regex");
		}
		ruleList->addRule(newRule);
	}
	return ruleList;
}

Rule* Rule::parseRule(std::string str, int_least16_t measure) {
	// Rule Day of Week
	if (std::regex_search(str, std::regex("^" REGEX_DAY_OF_WEEK "$"))) {
		if (measure != DAY) {
			std::cout << str << std::endl;
			throw std::invalid_argument("RULE DAY OF WEEK CAN ONLY BE APPLIED TO DAYS");
		}
		return new RuleDayOfWeek(str);
	}

	// Rule Dynamic Range
	if (std::regex_search(str, std::regex("^" REGEX_DYNAMIC_RANGE_DAY_MONTH "$"))) {
		if (measure == YEAR) {
			std::cout << REGEX_DYNAMIC_RANGE_DAY_MONTH << "\n";
			std::cout << str << std::endl;
			throw std::invalid_argument("Regex matches on wrong measure");
		}
		return new RuleDynamicRange(measure, str);
	}

	if (std::regex_search(str, std::regex("^" REGEX_DYNAMIC_RANGE_YEAR "$"))) {
		if (measure != YEAR) {
			std::cout << REGEX_DYNAMIC_RANGE_YEAR  << "\n";
			std::cout << str << std::endl;
			throw std::invalid_argument("Regex matches on wrong measure");
		}
		return new RuleDynamicRange(measure, str);
	}

	// Rule Fixed
	if (std::regex_search(str, std::regex("^" REGEX_FIXED_DAY_MONTH "$"))) {
		if (measure == YEAR) {
			std::cout << REGEX_FIXED_DAY_MONTH   << "\n";
			std::cout << str << std::endl;
			throw std::invalid_argument("Regex matches on wrong measure");
		}
		return new RuleFixed(measure, std::stoi(str));
	}

	if (std::regex_search(str, std::regex("^" REGEX_FIXED_YEAR "$"))) {
		if (measure != YEAR) {
			std::cout << REGEX_FIXED_YEAR    << "\n";
			std::cout << str << std::endl;
			throw std::invalid_argument("Regex matches on wrong measure");
		}
		return new RuleFixed(measure, std::stoi(str));
	}

	// Rule Wildcard
	if (std::regex_search(str, std::regex("^" REGEX_WILDCARD "$"))) {
		if (measure != YEAR) return new RuleWildcard;

		//Has no Initial Year
		if (str.size() == 1) return new RuleWildcard;
		int_least16_t initialYear = std::stoi(str.substr(0, 4));
		return new RuleWildcard(initialYear);
	}
	return nullptr;
}
