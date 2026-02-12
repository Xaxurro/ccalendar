#include "fixed-range.h"
#include <stdexcept>

RuleFixedRange::~RuleFixedRange() {}

RuleFixedRange::RuleFixedRange(const Date &lower,const  Date &upper): lowerLimit(lower), upperLimit(upper){
	if (lowerLimit > upperLimit) throw std::invalid_argument("Rule Fixed Range: Lower Limit can't be after Upper Limit!");
}

bool RuleFixedRange::isValidIn(const Date* date) {
	if (*date < lowerLimit || *date > upperLimit) return false;
	return true;
}
