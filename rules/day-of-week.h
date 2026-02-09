#include "rule.h"
#include "../date.h"
#include <string>

class RuleDayOfWeek: public Rule {
	private: 
		int_least16_t day = 0;
	public:
		RuleDayOfWeek(const std::string& str);
		RuleDayOfWeek(int_least16_t day);
		const int_least16_t getDay() { return day; };
		const bool isValidIn(Date* date);
};
