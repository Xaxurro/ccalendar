#include "event.h"
#include "colors.h"
#include "rules/fixed-range.h"
#include "rules/list.h"
#include "rules/wildcard.h"

Event::~Event() {
	for (Rule* rule : rules) delete rule;
	rules.clear();
	delete tags;
}

Event::Event(std::list<Rule*>* rules, Tags* tags, std::string description) {
	 this->rules = *rules;
	 this->tags = tags;
	 this->description = description;
}

int_least16_t Event::getRuleCount() {
	int_least16_t count = 0;
	for (Rule* rule : rules) {
		RuleList* ruleList = dynamic_cast<RuleList*>(rule);
		if (ruleList != nullptr) {
			count += ruleList->getRulesList()->size();
		} else {
			count += 1;
		}
	}
	return count;
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

	str::replace("\\d", std::to_string(date->getDay()), &description);
	str::replace("\\m", std::to_string(date->getMonth()), &description);
	str::replace("\\y", std::to_string(date->getYear()), &description);

	for (Rule* rule : rules) {
		RuleWildcard* ruleWildcard = dynamic_cast<RuleWildcard*>(rule);
		if (ruleWildcard == nullptr) continue;
		if (!ruleWildcard->hasInitialYear()) continue;
		str::replace("\\Y", std::to_string(date->getYearsAfter(ruleWildcard->getInitialYear())), &description);
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
	if (!std::regex_match(str, match, eventRegex)) {
		std::cout << str << std::endl;
		throw std::invalid_argument("EVENT: Does not match EVENT_REGEX or EVENT_FIXED_RANGE_REGEX");
	}

	this->tags		= new Tags(match[4]);
	this->description	= match[5];

	rules.push_back(Rule::fromString(match[1], DAY));
	rules.push_back(Rule::fromString(match[2], MONTH));
	rules.push_back(Rule::fromString(match[3], YEAR));
}

bool Event::isValidIn(const Date* date) {
	for (Rule* rule : rules) if (!rule->isValidIn(date)) return false;
	return true;
}

bool Event::hasLabel(const std::string label) {
	if (!tags->has("label")) return false;
	return (*tags)["label"] == label;
}
