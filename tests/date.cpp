#include <cstdint>
#include <gtest/gtest.h>
#include <stdexcept>
#include "../date.h"

TEST(DateTest, OutOfRangeMinMax) {
	Date date;
	//Min Max values
	EXPECT_THROW(date.setDay(-1), std::out_of_range);
	EXPECT_THROW(date.setDay(0), std::out_of_range);
	EXPECT_THROW(date.setDay(32), std::out_of_range);
	EXPECT_THROW(date.setMonth(0), std::out_of_range);
	EXPECT_THROW(date.setMonth(13), std::out_of_range);
	EXPECT_THROW(date.setYear(0), std::out_of_range);
}

TEST(DateTest, OutOfRangeNovember31Days) {
	Date date;
	//November has 30 days only
	date.setYear(2025);
	date.setMonth(NOVEMBER);
	EXPECT_THROW(date.setDay(31), std::out_of_range);
}

TEST(DateTest, OutOfRangeFebruaryNoLeapYear) {
	Date date;
	//February had 28 days on 2025
	date.setYear(2025);
	date.setMonth(FEBRUARY);
	EXPECT_THROW(date.setDay(29), std::out_of_range);
}

TEST(DateTest, OutOfRangeFebruaryLeapYear) {
	Date date;
	//February had 28 days on 2024
	date.setYear(2024);
	date.setMonth(APRIL);
	EXPECT_NO_THROW(date.setDay(29));
}

TEST(DateTest, OutOfRangeChangedMonth) {
	Date date;
	date.setYear(2025);
	date.setMonth(DECEMBER);
	date.setDay(31);
	EXPECT_THROW(date.setMonth(NOVEMBER), std::out_of_range);
}

TEST(DateTest, DaysAdded) {
	Date date;
	date.setYear(2002);
	date.setMonth(NOVEMBER);
	date.setDay(8);

	Date date_future = date + 150;
	EXPECT_EQ(date_future.getDay(), 7);
	EXPECT_EQ(date_future.getMonth(), APRIL);
	EXPECT_EQ(date_future.getYear(), 2003);
}

TEST(DateTest, DaysSubstracted) {
	Date date;
	date.setYear(2009);
	date.setMonth(MAY);
	date.setDay(17);

	Date date_past = date - 17;
	EXPECT_EQ(date_past.getDay(), 30);
	EXPECT_EQ(date_past.getMonth(), APRIL);
	EXPECT_EQ(date_past.getYear(), 2009);
}
