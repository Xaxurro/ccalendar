#include "rule.h"
class RuleFixed: public Rule {
	private: 
		int_least16_t value = 0;
	public:
		RuleFixed(int_least16_t measure, int_least16_t valueNew);
		const int_least16_t getValue() { return value; };
		const bool isValidIn(Date* date);
};
