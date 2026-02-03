#include "rule.h"
class RuleRangedFixed: public Rule {
	private: 
		int_least16_t valueLower = 0;
		int_least16_t valueUpper = 0;
	public:
		RuleRangedFixed(int_least16_t measure, int_least16_t valueLowerNew, int_least16_t valueUpperNew);
		bool isValidIn(Date date);
};
