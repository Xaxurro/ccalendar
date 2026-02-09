#include <gtest/gtest.h>
#include <string>
#include "../event.h"
#include "../rules/rule.h"
#include "../rules/day-of-week.h"
#include "../rules/dynamic-range.h"
#include "../rules/fixed.h"
#include "../rules/fixed-range.h"
#include "../rules/wildcard.h"

TEST(EventTest, NoSpaceBetweenDateAndDescription) {
	Event event("28 02 2024this has no space in between!");

	ASSERT_TRUE(event.getRules() != nullptr);

	std::list<Rule*> rules = *event.getRules();

	ASSERT_EQ(rules.size(), 3);

	Date date(28, 2, 2024);
	ASSERT_TRUE(event.isValidIn(&date));

	ASSERT_EQ(event.getDescription(), std::string("this has no space in between!"));
}

TEST(EventTest, DynamicRangeRule) {
	Event event("1-4 02 2024 Trip");

	ASSERT_TRUE(event.getRules() != nullptr);

	std::list<Rule*> rules = *event.getRules();

	ASSERT_EQ(rules.size(), 3);

	EXPECT_EQ(dynamic_cast<RuleDynamicRange*>(rules.front())->getValueLower(), 1);
	EXPECT_EQ(dynamic_cast<RuleDynamicRange*>(rules.front())->getValueUpper(), 4);

	ASSERT_EQ(event.getDescription(), std::string("Trip"));
}

TEST(EventTest, RegexFailures) {
	EXPECT_THROW(Event("28"), std::invalid_argument);
	EXPECT_THROW(Event("28 missing month and year"), std::invalid_argument);
	EXPECT_THROW(Event("28 02"), std::invalid_argument);
	EXPECT_THROW(Event("02 04 missing year"), std::invalid_argument);
	EXPECT_THROW(Event("29 02 2024"), std::invalid_argument);
	EXPECT_THROW(Event("28022024this has no spaces on Date!"), std::invalid_argument);
}

// // TODO: FIX THIS TO make it check for the syntax using the constructor or something idk
// void checkTagSize(std::string str, size_t expectedSize) {
// 	Tags tags;
// 	tags.setTags(str);
// 	ASSERT_EQ(tags.size(), expectedSize);
// }
//
// TEST(EventTest, InvalidTagSyntax) {
// 	checkTagSize("06 01 2025 [this event has no tags!", 0);
// 	checkTagSize("06 01 2025 this one neither!", 0);
// 	checkTagSize("06 01 2025 [] this one neither!", 0);
// 	checkTagSize("06 01 2025 [,] this does!", 1);
// 	checkTagSize("06 01 2025 [bold] this one is bold!", 1);
// 	checkTagSize("06 01 2025 [bold, ] this one is just bold!", 1);
// 	checkTagSize("06 01 2025 [bold underline] this one is bold and underline!", 2);
// }
//
