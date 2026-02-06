#include "rule.h"
#include "../date.h"

#define REGEX_FIXED_RANGE "(" REGEX_DAY_MONTH ")" REGEX_DATE_SEPARATOR "+(" REGEX_DAY_MONTH ")" REGEX_DATE_SEPARATOR "+(" REGEX_YEAR ")" REGEX_DATE_SEPARATOR "*-" REGEX_DATE_SEPARATOR "*(" REGEX_DAY_MONTH ")" REGEX_DATE_SEPARATOR "+(" REGEX_DAY_MONTH ")" REGEX_DATE_SEPARATOR "+(" REGEX_YEAR ")"

class RuleFixedRange: public Rule {
	private: 
		Date* lowerLimit;
		Date* upperLimit;
		bool inbetween(int_least16_t value, int_least16_t lowerLimit, int_least16_t upperLimit);
	public:
		RuleFixedRange(Date* lowerLimit, Date* upperLimit);
		const Date* getLowerLimit() { return lowerLimit; };
		const Date* getUpperLimit() { return upperLimit; };
		const bool isValidIn(Date* date);
};
