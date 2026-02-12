#ifndef H_RULES
#define H_RULES

#include <algorithm>
#include <list>
#include <stdexcept>
#include <string>
#include "../date.h"

#define DAY 1
#define MONTH 2
#define YEAR 3

class Rule {
	protected:
		int_least16_t measure = 0;
	public:
		void setMeasure(int_least16_t measureNew) {
			if (measureNew != DAY && measureNew != MONTH && measureNew != YEAR) throw std::invalid_argument("INVALID MEASURE FOR RULE");
			measure = measureNew;
		}

		virtual bool isValidIn(const Date* date) = 0;
		virtual ~Rule() = default;
};

#endif // !H_RULES
