#include "rule.h"

#define REGEX_FIXED_DAY_MONTH	REGEX_DAY_MONTH REGEX_DATE_SEPARATOR REGEX_DAY_MONTH
#define REGEX_FIXED_YEAR	REGEX_YEAR	REGEX_DATE_SEPARATOR REGEX_YEAR

class RuleFixed: public Rule {
	private: 
		int_least16_t value = 0;
	public:
		RuleFixed(int_least16_t measure, int_least16_t valueNew);
		const int_least16_t getValue() { return value; };
		const bool isValidIn(Date* date);
};
