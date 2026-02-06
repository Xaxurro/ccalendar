#include "dynamic-range.h"

RuleDynamicRange::RuleDynamicRange(int_least16_t measure, int_least16_t valueLowerNew, int_least16_t valueUpperNew) {
	setMeasure(measure);
	switch(measure) {
	case DAY:
		Date::isDayOutOfRange(valueLowerNew);
		Date::isDayOutOfRange(valueUpperNew);
	break;
	case MONTH:
		Date::isMonthOutOfRange(valueLowerNew);
		Date::isMonthOutOfRange(valueUpperNew);
	break;
	case YEAR:
		Date::isYearOutOfRange(valueLowerNew);
		Date::isYearOutOfRange(valueUpperNew);
	break;
	}
	valueLower = valueLowerNew;
	valueUpper = valueUpperNew;
}

bool RuleDynamicRange::isValidIn(Date date) {
	switch(measure) {
	case DAY: {
		int_least16_t maxDay = date.maxDayIn(date.getMonth(), date.getYear());
		if (valueUpper > maxDay) valueUpper = maxDay;
		return date.getDay() >= valueLower && date.getDay() <= valueUpper;
	}
	break;
	case MONTH:
		return date.getMonth() >= valueLower && date.getMonth() <= valueUpper;
	break;
	case YEAR:
		return date.getYear() >= valueLower && date.getYear() <= valueUpper;
	break;
	}
	return false;
}
