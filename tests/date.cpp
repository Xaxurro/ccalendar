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
	date.setMonth(11);
	EXPECT_THROW(date.setDay(31), std::out_of_range);
}

TEST(DateTest, OutOfRangeFebruaryNoLeapYear) {
	Date date;
	//February had 28 days on 2025
	date.setYear(2025);
	date.setMonth(2);
	EXPECT_THROW(date.setDay(29), std::out_of_range);
}

TEST(DateTest, OutOfRangeFebruaryLeapYear) {
	Date date;
	//February had 28 days on 2024
	date.setYear(2024);
	date.setMonth(2);
	EXPECT_NO_THROW(date.setDay(29));
}

TEST(DateTest, OutOfRangeChangedMonth) {
	Date date;
	date.setYear(2025);
	date.setMonth(12);
	date.setDay(31);
	EXPECT_THROW(date.setMonth(11), std::out_of_range);
}
