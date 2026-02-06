#include "rule.h"

#define REGEX_DYNAMIC_RANGE_DAY_MONTH	REGEX_DAY_MONTH REGEX_DATE_SEPARATOR REGEX_DAY_MONTH
#define REGEX_DYNAMIC_RANGE_YEAR	REGEX_YEAR	REGEX_DATE_SEPARATOR REGEX_YEAR

class RuleDynamicRange: public Rule {
	private: 
		int_least16_t valueLower = 0;
		int_least16_t valueUpper = 0;
	public:
		RuleDynamicRange(int_least16_t measure, int_least16_t valueLowerNew, int_least16_t valueUpperNew);
		const int_least16_t getValueLower() { return valueLower; };
		const int_least16_t getValueUpper() { return valueUpper; };
		const bool isValidIn(Date* date);
};
