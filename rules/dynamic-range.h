#include "rule.h"
class RuleDynamicRange: public Rule {
	private: 
		int_least16_t valueLower = 0;
		int_least16_t valueUpper = 0;
	public:
		RuleDynamicRange(int_least16_t measure, int_least16_t valueLowerNew, int_least16_t valueUpperNew);
		bool isValidIn(Date date);
};
