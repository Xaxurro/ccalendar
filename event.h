#ifndef H_CALENDAR_EVENT
#define H_CALENDAR_EVENT

#include <cctype>
#include <list>
#include <sstream>
#include <stdexcept>
#include <string>
#include "date.h"
#include "strings.h"
#include "tags.h"
#include "rules/rule.h"

#define REGEX_TAG		"\\[.*\\]"
#define REGEX_RULES_DAY		REGEX_DYNAMIC_RANGE_DAY_MONTH "|" REGEX_FIXED_DAY_MONTH "|" REGEX_DAY_OF_WEEK 
#define REGEX_RULES_MONTH	REGEX_DYNAMIC_RANGE_DAY_MONTH "|" REGEX_FIXED_DAY_MONTH
#define REGEX_RULES_YEAR	REGEX_DYNAMIC_RANGE_YEAR "|" REGEX_FIXED_YEAR

#define REGEX_FORMAT_DAY	REGEX_WILDCARD "|" REGEX_RULES_DAY	"|\\{ *(?:" REGEX_RULES_DAY	")(?: |" REGEX_RULES_DAY	")*}"
#define REGEX_FORMAT_MONTH	REGEX_WILDCARD "|" REGEX_RULES_MONTH	"|\\{ *(?:" REGEX_RULES_MONTH	")(?: |" REGEX_RULES_MONTH	")*}"
#define REGEX_FORMAT_YEAR	REGEX_WILDCARD "|" REGEX_RULES_YEAR	"|\\{ *(?:" REGEX_RULES_YEAR	")(?: |" REGEX_RULES_YEAR	")*}"

// The idea of this regex is to make it as flexible as possible to
// allow multiple formats like DD-MM-YYYY without messing up the rules
#define EVENT_REGEX_STR "^" REGEX_DATE_SEPARATOR "*("  REGEX_FORMAT_DAY ")" REGEX_DATE_SEPARATOR "+(" REGEX_FORMAT_MONTH ")" REGEX_DATE_SEPARATOR "+(" REGEX_FORMAT_YEAR ")" REGEX_DATE_SEPARATOR "*(" REGEX_TAG ")? *(\\S.*)$"

class Event {
	private:
		std::list<Rule*> rules;
		Tags* tags;
		std::string description = "";

	public:
		const std::string getDescription() { return description; }
		const std::list<Rule*>* getRules() { return &rules; }
		const Tags* getTags() { return tags; }

		const bool isInvalid() { return str_is_blank(description); }

		const bool isValidIn(Date* date);

		// event_string: a line that defines an event
		Event(std::list<Rule*>* rules, Tags* tags, std::string description);
		Event(std::string str);
		~Event();
};
#endif // !H_CALENDAR_EVENT
