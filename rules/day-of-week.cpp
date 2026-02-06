#include "day-of-week.h"

RuleDayOfWeek::RuleDayOfWeek(int_least16_t day) {
	if (day < MONDAY || day > SUNDAY) Date::isDayOutOfRange(day);
	this->day = day;
}

const bool RuleDayOfWeek::isValidIn(Date* date) {
	return date->getDayOfTheWeek() == day;
}
