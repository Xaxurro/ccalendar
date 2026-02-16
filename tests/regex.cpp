#include <gtest/gtest.h>

#include "../event.h"
#include "../rules/rule.h"
#include "../rules/day-of-week.h"
#include "../rules/dynamic-range.h"
#include "../rules/fixed.h"
#include "../rules/fixed-range.h"
#include "../rules/wildcard.h"

TEST(RegexTest, RuleDayOfWeek) {
	Event event("#2 * * Minecraft Snapshot");

	ASSERT_TRUE(event.getRules() != nullptr);

	std::list<Rule*> rules = *event.getRules();

	ASSERT_EQ(rules.size(), 3);

	ASSERT_EQ(dynamic_cast<RuleDayOfWeek*>(rules.front())->getDay(), 2);

	Date date(17, 2, 2026);
	ASSERT_TRUE(event.isValidIn(&date));

	ASSERT_EQ(event.getDescription(), std::string("Minecraft Snapshot"));
}

TEST(RegexTest, RuleDynamicRange) {
	Event event("1-4 02 2024 Trip");

	ASSERT_TRUE(event.getRules() != nullptr);

	std::list<Rule*> rules = *event.getRules();

	ASSERT_EQ(rules.size(), 3);

	EXPECT_EQ(dynamic_cast<RuleDynamicRange*>(rules.front())->getValueLower(), 1);
	EXPECT_EQ(dynamic_cast<RuleDynamicRange*>(rules.front())->getValueUpper(), 4);

	Date date(2, 2, 2024);
	ASSERT_TRUE(event.isValidIn(&date));

	ASSERT_EQ(event.getDescription(), std::string("Trip"));
}

TEST(RegexTest, RuleFixed) {
	Event event("28 02 2024this has no space in between!");

	ASSERT_TRUE(event.getRules() != nullptr);

	std::list<Rule*> rules = *event.getRules();

	ASSERT_EQ(rules.size(), 3);

	RuleFixed* rule = dynamic_cast<RuleFixed*>(rules.front());
	ASSERT_TRUE(rule != nullptr);

	EXPECT_EQ(rule->getValue(), 28);

	Date date(28, 2, 2024);
	ASSERT_TRUE(event.isValidIn(&date));

	ASSERT_EQ(event.getDescription(), std::string("this has no space in between!"));
}

TEST(RegexTest, RuleFixedRange) {
	Event event("29 1 2026 - 2 2 2026 Trip");

	ASSERT_TRUE(event.getRules() != nullptr);

	std::list<Rule*> rules = *event.getRules();

	ASSERT_EQ(rules.size(), 1);

	RuleFixedRange* rule = dynamic_cast<RuleFixedRange*>(rules.front());

	ASSERT_TRUE(rule != nullptr);

	const Date* upperLimit = rule->getUpperLimit();
	const Date* lowerLimit = rule->getLowerLimit();

	ASSERT_TRUE(upperLimit != nullptr);
	ASSERT_TRUE(lowerLimit != nullptr);

	Date date(1, 2, 2026);
	ASSERT_TRUE(event.isValidIn(&date));

	EXPECT_EQ(*upperLimit, Date(2, 2, 2026));
	EXPECT_EQ(*lowerLimit, Date(29, 1, 2026));

	ASSERT_EQ(event.getDescription(), std::string("Trip"));
}

TEST(RegexTest, RuleWildcard) {
	Event event("08 11 2002* My Birthday!");

	ASSERT_TRUE(event.getRules() != nullptr);

	std::list<Rule*> rules = *event.getRules();

	ASSERT_EQ(rules.size(), 3);

	Date date(8, 11, 2024);
	ASSERT_TRUE(event.isValidIn(&date));

	ASSERT_EQ(event.getDescription(), std::string("My Birthday!"));
}

TEST(RegexTest, EventInvalid) {
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
// TEST(RegexTest, InvalidTagSyntax) {
// 	checkTagSize("06 01 2025 [this event has no tags!", 0);
// 	checkTagSize("06 01 2025 this one neither!", 0);
// 	checkTagSize("06 01 2025 [] this one neither!", 0);
// 	checkTagSize("06 01 2025 [,] this does!", 1);
// 	checkTagSize("06 01 2025 [bold] this one is bold!", 1);
// 	checkTagSize("06 01 2025 [bold, ] this one is just bold!", 1);
// 	checkTagSize("06 01 2025 [bold underline] this one is bold and underline!", 2);
// }
//
//

TEST(RegexTest, Tags) {
	Tags tags("hello this color=red is a test");
	// Has no value
	EXPECT_FALSE(tags.has("bold"));
	EXPECT_TRUE(tags.has("this"));
	EXPECT_FALSE(tags.has("thi"));

	// Has value
	EXPECT_TRUE(tags.has("color"));
	EXPECT_TRUE(tags.has("color="));
	EXPECT_TRUE(tags["color"] == "red");
	EXPECT_FALSE(tags.has("col"));
	EXPECT_FALSE(tags.has("red"));
	EXPECT_FALSE(tags.has("=red"));
	EXPECT_FALSE(tags.has("="));

	tags.setTags(" =red");
	EXPECT_EQ(tags.size(), 0);
	EXPECT_FALSE(tags.has("red"));

	tags.setTags("color= ");
	EXPECT_EQ(tags.size(), 1);
	EXPECT_TRUE(tags.has("color"));
	EXPECT_FALSE(tags.has("="));
}
