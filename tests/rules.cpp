#include <gtest/gtest.h>
#include <stdexcept>
#include "../date.h"
#include "../rules/fixed.h"

TEST(Fixed, MatchingValues) {
	Date date(8, 11, 2002);

	// Day
	RuleFixed rule(DAY, 8);
	ASSERT_TRUE(rule.isValidIn(date));
	rule = RuleFixed(DAY, 9);
	ASSERT_FALSE(rule.isValidIn(date));

	// Month
	rule = RuleFixed(MONTH, 11);
	ASSERT_TRUE(rule.isValidIn(date));
	rule = RuleFixed(MONTH, 12);
	ASSERT_FALSE(rule.isValidIn(date));

	// Year
	rule = RuleFixed(YEAR, 2002);
	ASSERT_TRUE(rule.isValidIn(date));
	rule = RuleFixed(MONTH, 2001);
	ASSERT_FALSE(rule.isValidIn(date));
}

TEST(Fixed, MaximumDate) {
	Date date(28, 2, 2002);
	RuleFixed rule(DAY, 27);
	ASSERT_FALSE(rule.isValidIn(date));
	rule = RuleFixed(DAY, 28);
	ASSERT_TRUE(rule.isValidIn(date));
	rule = RuleFixed(DAY, 29);
	ASSERT_TRUE(rule.isValidIn(date));
	rule = RuleFixed(DAY, 30);
	ASSERT_TRUE(rule.isValidIn(date));
	rule = RuleFixed(DAY, 31);
	ASSERT_TRUE(rule.isValidIn(date));
}
