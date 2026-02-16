#ifndef H_CALENDAR_RULE_FIXED_RANGE
#define H_CALENDAR_RULE_FIXED_RANGE
#include "rule.h"
#include "../date.h"

class RuleFixedRange: public Rule {
	private: 
		const Date lowerLimit;
		const Date upperLimit;
		bool inbetween(int_least16_t value, int_least16_t lowerLimit, int_least16_t upperLimit);
	public:
		~RuleFixedRange();
		RuleFixedRange(const Date& lower, const Date& upper);
		const Date* getLowerLimit() { return &lowerLimit; };
		const Date* getUpperLimit() { return &upperLimit; };
		bool isValidIn(const Date* date);
};
#endif //H_CALENDAR_RULE_FIXED_RANGE
