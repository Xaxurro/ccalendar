#ifndef H_DATE
#define H_DATE
#include <cstdint>
#include <string>
#define MONDAY		1
#define TUESDAY		2
#define WEDNESDAY	3
#define THURSDAY	4
#define FRIDAY		5
#define SATURDAY	6
#define SUNDAY		7
#define JANUARY		1
#define FEBRUARY	2
#define MARCH		3
#define APRIL		4
#define MAY		5
#define JUNE		6
#define JULY		7
#define AUGUST		8
#define SEPTEMBER	9
#define OCTOBER		10
#define NOVEMBER	11
#define DECEMBER	12

class Date {
	private:
		int_least16_t year = 0;
		int_least16_t month = 0;
		int_least16_t day = 0;

		void checkExistance() const;

		int_least16_t maxDayIn(int_least16_t month) const;

		static bool isYearOutOfRange(int_least16_t year) { return year < 1 || year > 9999; }
		static bool isMonthOutOfRange(int_least16_t month) { return month < JANUARY || month > DECEMBER; }
		static bool isDayOutOfRange(int_least16_t day) { return day < 1 || day > 31; }
			
	public:
		std::string toString() const { return std::to_string(year) + " " + std::to_string(month) + " " + std::to_string(day); }
		bool isInvalid() const { return year == 0 || month == 0 || day == 0; }

		Date () {};
		Date (int_least16_t day_new, int_least16_t month_new, int_least16_t year_new) : day(day_new), month(month_new), year(year_new){
			checkExistance();
		}


		int_least16_t getYear() const { return year; }
		int_least16_t getMonth() const { return month; }
		int_least16_t getDay() const { return day; }
		int_least16_t getDayOfTheWeek() const;

		void setYear(int_least16_t year_new);
		void setMonth(int_least16_t month_new);
		void setDay(int_least16_t day_new);

		Date operator + (int_least16_t days);
		Date operator - (int_least16_t days);
};
#endif
