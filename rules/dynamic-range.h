#include "rule.h"


class RuleDynamicRange: public Rule {
	private: 
		int_least16_t valueLower = 0;
		int_least16_t valueUpper = 0;
	public:
		RuleDynamicRange(int_least16_t measure, std::string str);
		RuleDynamicRange(int_least16_t measure, int_least16_t valueLowerNew, int_least16_t valueUpperNew);
		const int_least16_t getValueLower() { return valueLower; };
		const int_least16_t getValueUpper() { return valueUpper; };
		const bool isValidIn(Date* date);
};
