#include "date.h"
#include <cmath>
#include <cstdint>
#include <stdexcept>

void Date::checkExistance() const {
	if (isInvalid()) return;
	if (int_least16_t max_day = maxDayIn(month, year); day > max_day) {
        	throw std::out_of_range("This date does not exists!: " + toString());
        }
}

//Returns the valur of the maximum day in given month
 int_least16_t Date::maxDayIn(int_least16_t month, int_least16_t year) {
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

//Return the Day of the week using Zeller's Congruence, but with 1 = Monday, 2 = Tuesday, ..., 7 = Sunday
int_least16_t Date::getDayOfTheWeek() const {
	int_least16_t monthAux = month;
	int_least16_t yearAux = year;

	if (monthAux == JANUARY || monthAux == FEBRUARY) {
		monthAux += 12;
		yearAux -= 1;
	}

	// 22 13 2025
	int_least16_t dayOfTheWeek = day;
	dayOfTheWeek += floor((float)(13 * (monthAux + 1)) / 5);
	dayOfTheWeek += (yearAux % 100);
	dayOfTheWeek += floor((float)(yearAux % 100) / 4);
	dayOfTheWeek += floor((float)yearAux/100);
	dayOfTheWeek %= 7;
	if (dayOfTheWeek == 0) return SUNDAY;
	return dayOfTheWeek;
}

Date Date::operator+(int_least16_t days_added) {
	int_least16_t day_new = day;
	int_least16_t month_new = month;
	int_least16_t year_new = year;
	while (days_added > 0) {
		//Day within month
		int_least16_t sum = day_new + days_added;
		int_least16_t maxDay = maxDayIn(month_new, year_new);
		if (sum <= maxDay) {
			days_added = 0;
			day_new = sum;
			continue;
		}
		//next month
		if (day_new == maxDay) {
			days_added -= 1;
			day_new = 1;
			month_new += 1;
			if (month_new > DECEMBER) {
				month_new = JANUARY;
				year_new += 1;
			}
		//distance until month border
		} else {
			days_added -= maxDay - day_new;
			day_new = maxDay;
		}
	}
	return Date(day_new, month_new, year_new);
}

Date Date::operator-(int_least16_t days_substracted) {
	int_least16_t day_new = day;
	int_least16_t month_new = month;
	int_least16_t year_new = year;
	while (days_substracted > 0) {
		//Day within month
		int_least16_t substraction = day_new - days_substracted;
		if (substraction >= 1) {
			days_substracted = 0;
			day_new = substraction;
			continue;
		}
		//previous month
		if (day_new == 1) {
			days_substracted -= 1;
			month_new -= 1;
			if (month_new < JANUARY) {
				month_new = DECEMBER;
				year_new -= 1;
			}
			day_new = maxDayIn(month_new, year_new);
		//distance until month border
		} else {
			days_substracted -= day_new - 1;
			day_new = 1;
		}
	}
	return Date(day_new, month_new, year_new);
}

bool Date::operator>(Date dateToCompare) {
	if (year > dateToCompare.getYear()) return true;
	if (year < dateToCompare.getYear()) return false;
	if (month > dateToCompare.getMonth()) return true;
	if (month < dateToCompare.getMonth()) return false;
	if (day > dateToCompare.getDay()) return true;
	return false;
}

bool Date::operator<(Date dateToCompare) {
	if (year > dateToCompare.getYear()) return false;
	if (year < dateToCompare.getYear()) return true;
	if (month > dateToCompare.getMonth()) return false;
	if (month < dateToCompare.getMonth()) return true;
	if (day < dateToCompare.getDay()) return true;
	return false;
}

bool Date::operator==(Date dateToCompare) {
	return year == dateToCompare.getYear() && month == dateToCompare.getMonth() && day == dateToCompare.getDay();
}

bool Date::operator!=(Date dateToCompare) {
	return year != dateToCompare.getYear() || month != dateToCompare.getMonth() || day != dateToCompare.getDay();
}

bool Date::operator>=(Date dateToCompare) {
	if (*this == dateToCompare) return true;
	return *this > dateToCompare;
}

bool Date::operator<=(Date dateToCompare) {
	if (*this == dateToCompare) return true;
	return *this < dateToCompare;
}
