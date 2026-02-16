#ifndef H_CALENDAR_RULE_WILDCARD
#define H_CALENDAR_RULE_WILDCARD
#include "rule.h"
#include <cstdint>

class RuleWildcard: public Rule {
	private:
		int_least16_t initialYear = 0;
	public:
		RuleWildcard();
		RuleWildcard(const int_least16_t initialYear);

        	bool isValidIn(const Date* date);
        	bool hasInitialYear();
        	int_least16_t getInitialYear();
};
#endif //H_CALENDAR_RULE_WILDCARD
