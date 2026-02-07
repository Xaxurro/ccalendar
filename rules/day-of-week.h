#include "rule.h"
#include "../date.h"

class RuleDayOfWeek: public Rule {
	private: 
		int_least16_t day = 0;
	public:
		RuleDayOfWeek(int_least16_t day);
		const int_least16_t getDay() { return day; };
		const bool isValidIn(Date* date);
};
