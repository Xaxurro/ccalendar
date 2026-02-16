#ifndef H_CALENDAR_RULE_DYNAMIC_RANGE
#define H_CALENDAR_RULE_DYNAMIC_RANGE
#include "rule.h"

class RuleDynamicRange: public Rule {
	private: 
		int_least16_t valueLower = 0;
		int_least16_t valueUpper = 0;
	public:
		RuleDynamicRange(int_least16_t measure, std::string str);
		RuleDynamicRange(int_least16_t measure, int_least16_t valueLowerNew, int_least16_t valueUpperNew);
		int_least16_t getValueLower() { return valueLower; };
		int_least16_t getValueUpper() { return valueUpper; };
		bool isValidIn(const Date* date);
};
#endif //H_CALENDAR_RULE_DYNAMIC_RANGE
