#include "fixed-range.h"
#include <cstdint>
#include <stdexcept>

RuleFixedRange::RuleFixedRange(Date* lowerLimit, Date* upperLimit) {
	if (*lowerLimit > *upperLimit) throw std::invalid_argument("Rule Fixed Range: Lower Limit can't be after Upper Limit!");
	this->lowerLimit = lowerLimit;
	this->upperLimit = upperLimit;
}

const bool RuleFixedRange::isValidIn(Date* date) {
	if (*date < *lowerLimit || *date > *upperLimit) return false;
	return true;
}
