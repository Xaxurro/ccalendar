#include "rule.h"
#include "../date.h"


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
