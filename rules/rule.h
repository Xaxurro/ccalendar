#pragma once

#include <algorithm>
#include <cstdint>
#include <list>
#include <regex>
#include <stdexcept>
#include <string>
#include "../date.h"

#define DAY 1
#define MONTH 2
#define YEAR 3

#define REGEX_DATE_SEPARATOR	"[ \\t.:,;\\-_?!\\\\\\/|]"
#define REGEX_DAY_MONTH		"\\d{1,2}"
#define REGEX_YEAR		"\\d{4}"
#define REGEX_TAG		"\\[.*?\\]"
#define REGEX_DESCRIPTION	"\\S.*"

#define EVENT_FIXED_RANGE_REGEX		"^(" REGEX_DAY_MONTH ")" REGEX_DATE_SEPARATOR "+(" REGEX_DAY_MONTH ")" REGEX_DATE_SEPARATOR "+(" REGEX_YEAR ")" REGEX_DATE_SEPARATOR "*-" REGEX_DATE_SEPARATOR "*(" REGEX_DAY_MONTH ")" REGEX_DATE_SEPARATOR "+(" REGEX_DAY_MONTH ")" REGEX_DATE_SEPARATOR "+(" REGEX_YEAR ")" REGEX_DATE_SEPARATOR "*(" REGEX_TAG ")?[ \\t]*(" REGEX_DESCRIPTION")$"

#define REGEX_WILDCARD "(?:\\d{4})?\\*"

#define REGEX_DAY_OF_WEEK "#[0-7]"

#define REGEX_DYNAMIC_RANGE_DAY_MONTH	REGEX_DAY_MONTH "-" REGEX_DAY_MONTH
#define REGEX_DYNAMIC_RANGE_YEAR	REGEX_YEAR	"-" REGEX_YEAR

#define REGEX_FIXED_DAY_MONTH		REGEX_DAY_MONTH
#define REGEX_FIXED_YEAR		REGEX_YEAR

#define REGEX_RULES_DAY		REGEX_DYNAMIC_RANGE_DAY_MONTH	"|" REGEX_FIXED_DAY_MONTH "|" REGEX_DAY_OF_WEEK 
#define REGEX_RULES_MONTH	REGEX_DYNAMIC_RANGE_DAY_MONTH	"|" REGEX_FIXED_DAY_MONTH
#define REGEX_RULES_YEAR	REGEX_DYNAMIC_RANGE_YEAR	"|" REGEX_FIXED_YEAR

#define REGEX_FORMAT_DAY	REGEX_WILDCARD "|" REGEX_RULES_DAY	"|\\{ *(?:" REGEX_RULES_DAY	")(?: +(?:" REGEX_RULES_DAY	"))*}"
#define REGEX_FORMAT_MONTH	REGEX_WILDCARD "|" REGEX_RULES_MONTH	"|\\{ *(?:" REGEX_RULES_MONTH	")(?: +(?:" REGEX_RULES_MONTH	"))*}"
#define REGEX_FORMAT_YEAR	REGEX_WILDCARD "|" REGEX_RULES_YEAR	"|\\{ *(?:" REGEX_RULES_YEAR	")(?: +(?:" REGEX_RULES_YEAR	"))*}"

// The idea of this regex is to make it as flexible as possible to
// allow multiple formats like DD-MM-YYYY without messing up the rules
#define EVENT_REGEX_STR "^" REGEX_DATE_SEPARATOR "*("  REGEX_FORMAT_DAY ")" REGEX_DATE_SEPARATOR "+(" REGEX_FORMAT_MONTH ")" REGEX_DATE_SEPARATOR "+(" REGEX_FORMAT_YEAR ")" REGEX_DATE_SEPARATOR "*(" REGEX_TAG ")?[ \\t]*(\\S.*)$"

class Rule {
	protected:
		int_least16_t measure = 0;
	public:
		void setMeasure(int_least16_t measureNew) {
			if (measureNew != DAY && measureNew != MONTH && measureNew != YEAR) throw std::invalid_argument("INVALID MEASURE FOR RULE");
			measure = measureNew;
		}

		virtual bool isValidIn(const Date* date) = 0;
		virtual ~Rule() = default;

		static Rule* fromString(std::string str, int_least16_t measure);

		static Rule* parseRule(std::string str, int_least16_t measure);
};
