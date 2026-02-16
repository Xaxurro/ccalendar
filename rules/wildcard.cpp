#include "wildcard.h"

RuleWildcard::RuleWildcard() {
}

RuleWildcard::RuleWildcard(const int_least16_t initialYear) {
	this->initialYear = initialYear;
}

bool RuleWildcard::isValidIn([[maybe_unused]] const Date* date) {
	return true;
}

bool RuleWildcard::hasInitialYear() {
	return initialYear != 0;
}

int_least16_t  RuleWildcard::getInitialYear() {
	return initialYear;
}
