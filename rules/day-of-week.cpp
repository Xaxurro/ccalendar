#include "day-of-week.h"
#include <string>

RuleDayOfWeek::RuleDayOfWeek(const std::string& str): RuleDayOfWeek(static_cast<int_least16_t>(str[1] - '0')) { }

RuleDayOfWeek::RuleDayOfWeek(int_least16_t day) {
	if (day < MONDAY || day > SUNDAY) Date::isDayOutOfRange(day);
	this->day = day;
}

bool RuleDayOfWeek::isValidIn(const Date* date) {
	return date->getDayOfTheWeek() == day;
}
