#include <gtest/gtest.h>
#include <stdexcept>
#include "../date.h"
#include "../rules/fixed.h"
#include "../rules/dynamic-range.h"
#include "../rules/fixed-range.h"
#include "../rules/wildcard.h"
#include "../rules/day-of-week.h"

TEST(Fixed, MatchingValues) {
	Date date(8, 11, 2002);

	// Day
	RuleFixed rule(DAY, 8);
	EXPECT_TRUE(rule.isValidIn(&date));
	rule = RuleFixed(DAY, 9);
	EXPECT_FALSE(rule.isValidIn(&date));

	// Month
	rule = RuleFixed(MONTH, 11);
	EXPECT_TRUE(rule.isValidIn(&date));
	rule = RuleFixed(MONTH, 12);
	EXPECT_FALSE(rule.isValidIn(&date));

	// Year
	rule = RuleFixed(YEAR, 2002);
	EXPECT_TRUE(rule.isValidIn(&date));
	rule = RuleFixed(MONTH, 2001);
	EXPECT_FALSE(rule.isValidIn(&date));
}

TEST(Fixed, MaximumDate) {
	Date date(28, 2, 2002);
	RuleFixed rule(DAY, 27);
	EXPECT_FALSE(rule.isValidIn(&date));
	rule = RuleFixed(DAY, 28);
	EXPECT_TRUE(rule.isValidIn(&date));
	rule = RuleFixed(DAY, 29);
	EXPECT_TRUE(rule.isValidIn(&date));
	rule = RuleFixed(DAY, 30);
	EXPECT_TRUE(rule.isValidIn(&date));
	rule = RuleFixed(DAY, 31);
	EXPECT_TRUE(rule.isValidIn(&date));
}

TEST(RangedDynamic, MatchingValues) {
	Date date(9, 5, 2009);
	RuleDynamicRange rule(DAY, 1, 10);
	EXPECT_TRUE(rule.isValidIn(&date));

	rule = RuleDynamicRange(DAY, 10, 20);
	EXPECT_FALSE(rule.isValidIn(&date));
}

TEST(RangedDynamic, InvertedValues) {
	Date date(9, 5, 2009);
	EXPECT_THROW(RuleDynamicRange(DAY, 10, 1), std::invalid_argument);
}

TEST(RangedFixed, InvertedLimits) {
	Date lowerLimit(01, 6, 2009);
	Date upperLimit(01, 7, 2009);
	EXPECT_THROW(RuleFixedRange(upperLimit, lowerLimit), std::invalid_argument);
}

TEST(RangedFixed, MatchingValues) {
	Date date(9, 5, 2009);
	Date lowerLimit(15, 04, 2009);
	Date upperLimit(04, 06, 2009);
	RuleFixedRange rule(lowerLimit, upperLimit);
	EXPECT_TRUE(rule.isValidIn(&date));
}

TEST(Wildcard, AssertNoFalses) {
	Date date(31, 10, 2026);
	RuleWildcard rule;
	EXPECT_TRUE(rule.isValidIn(&date));
}

TEST(Wildcard, InitialYear) {
	Date date(8, 11, 2026);
	RuleWildcard rule(2002);
	EXPECT_TRUE(rule.hasInitialYear());
}

TEST(DayOfWeek, getDayOfWeek) {
	// 31 of December is a THURSDAY
	Date date(31, 12, 2026);

	EXPECT_FALSE(RuleDayOfWeek(MONDAY).isValidIn(&date));
	EXPECT_FALSE(RuleDayOfWeek(TUESDAY).isValidIn(&date));
	EXPECT_FALSE(RuleDayOfWeek(WEDNESDAY).isValidIn(&date));
	EXPECT_FALSE(RuleDayOfWeek(FRIDAY).isValidIn(&date));
	EXPECT_FALSE(RuleDayOfWeek(SATURDAY).isValidIn(&date));
	EXPECT_FALSE(RuleDayOfWeek(MONDAY).isValidIn(&date));

	EXPECT_TRUE(RuleDayOfWeek(THURSDAY).isValidIn(&date));
}
