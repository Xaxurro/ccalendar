#ifndef H_RULES
#define H_RULES

#include <algorithm>
#include <stdexcept>
#include "../date.h"

#define REGEX_DATE_SEPARATOR "[ \\t.:,;\\-_?!\\\\\\/|]"
#define REGEX_DAY_MONTH "\\d{1,2}"
#define REGEX_YEAR "\\d{4}"

#define EVENT_FIXED_RANGE_REGEX		"(" REGEX_DAY_MONTH ")" REGEX_DATE_SEPARATOR "+(" REGEX_DAY_MONTH ")" REGEX_DATE_SEPARATOR "+(" REGEX_YEAR ")" REGEX_DATE_SEPARATOR "*-" REGEX_DATE_SEPARATOR "*(" REGEX_DAY_MONTH ")" REGEX_DATE_SEPARATOR "+(" REGEX_DAY_MONTH ")" REGEX_DATE_SEPARATOR "+(" REGEX_YEAR ")"

#define REGEX_WILDCARD "\\*"

#define REGEX_DAY_OF_WEEK "#[0-7]"

#define REGEX_DYNAMIC_RANGE_DAY_MONTH	REGEX_DAY_MONTH "-" REGEX_DAY_MONTH
#define REGEX_DYNAMIC_RANGE_YEAR	REGEX_YEAR	"-" REGEX_YEAR

#define REGEX_FIXED_DAY_MONTH		REGEX_DAY_MONTH
#define REGEX_FIXED_YEAR		REGEX_YEAR

#define DAY 1
#define MONTH 2
#define YEAR 3

class Rule {
	protected:
		int_least16_t measure = 0;
	public:
		void setMeasure(int_least16_t measureNew) {
			if (measureNew != DAY && measureNew != MONTH && measureNew != YEAR) throw std::invalid_argument("INVALID MEASURE FOR RULE");
			measure = measureNew;
		}

		const virtual bool isValidIn(Date* date) = 0;
};

#endif // !H_RULES
