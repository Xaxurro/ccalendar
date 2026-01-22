#include "date.h"
#include <stdexcept>

void Date::checkExistance() const {
	if (isInvalid()) return;
	if (int_least16_t max_day = maxDayIn(month); day > max_day) {
        	throw std::out_of_range("This date does not exists!: " + toString());
        }
}

//Returns the valur of the maximum day in given month
int_least16_t Date::maxDayIn(int_least16_t month) const {
	if (isMonthOutOfRange(month)) {
		throw std::out_of_range("New month is in an invalid range (< 1 || > 12)");
	}
	if (month == FEBRUARY) {
		//Non-leap year
		if (year % 4 != 0) return 28;
		//Leap year
		else return 29;
	}
	if (month == APRIL || month == JUNE || month == SEPTEMBER || month == NOVEMBER) return 30;
	return 31;
}

void Date::setYear(int_least16_t year_new) {
	if (isYearOutOfRange(year_new)) {
		throw std::out_of_range("Year can't be negative!");
	}
	year = year_new;
	checkExistance();
}

void Date::setMonth(int_least16_t month_new) {
	// `month` is in range 1 - 12 (inclusive both)
	if (isMonthOutOfRange(month_new)) {
		throw std::out_of_range("New month is in an invalid range (< 1 || > 12)");
	}
	month = month_new;
	checkExistance();
}

void Date::setDay(int_least16_t day_new) {
	if (isDayOutOfRange(day_new)) {
		throw std::out_of_range("New day is in an invalid range (< 1 || > 31)");
	}
	day = day_new;
	checkExistance();
}
