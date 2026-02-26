#pragma once

#include <cctype>
#include <list>
#include <regex>
#include <sstream>
#include <stdexcept>
#include <string>
#include "date.h"
#include "strings.h"
#include "tags.h"
#include "rules/rule.h"


class Event {
	private:
		std::list<Rule*> rules;
		Tags* tags;
		std::string description = "";

		void parseRules(std::smatch match);
	public:
		const std::string getDescription() { return description; }
		const std::list<Rule*>* getRules() { return &rules; }
		const Tags* getTags() { return tags; }

		bool isInvalid() { return str::is_blank(description); }
		//Returns `true` if all rules are valid in `date`, otherwise `false`
		bool isValidIn(const Date* date);
		bool hasLabel(const std::string label);
		int_least16_t getRuleCount();
		void print(const Date* date);

		// event_string: a line that defines an event
		Event(std::list<Rule*>* rules, Tags* tags, std::string description);
		Event(std::string str);
		~Event();
};
