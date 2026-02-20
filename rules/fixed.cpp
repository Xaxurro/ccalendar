#include "fixed.h"

RuleFixed::RuleFixed(int_least16_t measure, int_least16_t valueNew) {
	setMeasure(measure);
	switch(measure) {
	case DAY:
		Date::isDayOutOfRange(valueNew);
	break;
	case MONTH:
		Date::isMonthOutOfRange(valueNew);
	break;
	case YEAR:
		Date::isYearOutOfRange(valueNew);
	break;
	}
	value = valueNew;
}

bool RuleFixed::isValidIn(const Date* date) {
	switch(measure) {
	case DAY: {
		int_least16_t maxDay = date->maxDayIn(date->getMonth(), date->getYear());
		return value == date->getDay() || (date->getDay() == maxDay && value > maxDay);
	}
	break;
	case MONTH:
		return value == date->getMonth();
	break;
	case YEAR:
		return value == date->getYear();
	break;
	}
	return false;
}
