#include <gtest/gtest.h>
#include <iostream>
#include <ostream>
#include <regex>
#include <string>
#include "../event.h"
#include "../colors.h"
#include "../rules/rule.h"
#include "../rules/day-of-week.h"
#include "../rules/dynamic-range.h"
#include "../rules/fixed.h"
#include "../rules/fixed-range.h"
#include "../rules/wildcard.h"

TEST(EventTest, RuleDayOfWeek) {
	Event event("#2 * * Minecraft Snapshot");

	ASSERT_TRUE(event.getRules() != nullptr);

	std::list<Rule*> rules = *event.getRules();

	ASSERT_EQ(rules.size(), 3);

	ASSERT_EQ(dynamic_cast<RuleDayOfWeek*>(rules.front())->getDay(), 2);

	Date date(17, 2, 2026);
	ASSERT_TRUE(event.isValidIn(&date));

	ASSERT_EQ(event.getDescription(), std::string("Minecraft Snapshot"));
}

TEST(EventTest, RuleDynamicRange) {
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

TEST(EventTest, RuleFixed) {
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

TEST(EventTest, RuleFixedRange) {
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

TEST(EventTest, RuleWildcard) {
	Event event("08 11 2002* My Birthday!");

	ASSERT_TRUE(event.getRules() != nullptr);

	std::list<Rule*> rules = *event.getRules();

	ASSERT_EQ(rules.size(), 3);

	Date date(8, 11, 2024);
	ASSERT_TRUE(event.isValidIn(&date));

	ASSERT_EQ(event.getDescription(), std::string("My Birthday!"));
}

TEST(EventTest, RegexFailures) {
	EXPECT_THROW(Event("28"), std::invalid_argument);
	EXPECT_THROW(Event("28 missing month and year"), std::invalid_argument);
	EXPECT_THROW(Event("28 02"), std::invalid_argument);
	EXPECT_THROW(Event("02 04 missing year"), std::invalid_argument);
	EXPECT_THROW(Event("29 02 2024"), std::invalid_argument);
	EXPECT_THROW(Event("28022024this has no spaces on Date!"), std::invalid_argument);
}

TEST(EventTest, Print) {
	//Change std::cout buffer
	std::stringstream capturedOutput;
	std::streambuf* originalCoutBuf = std::cout.rdbuf();
	std::cout.rdbuf(capturedOutput.rdbuf());

	std::cout << "\033[0m";
	Colors::add("red", {224, 27, 36});
	Event event("08 11 * [color=red bold underline] My Birthday");
	Date date(8, 11, 2002);
	event.print(&date);

	std::cout.rdbuf(originalCoutBuf);
	std::string expectedOutput("\033[0m8 11 2002 \033[1m\033[4m\033[38;2;224;27;36mMy Birthday\033[0m\n");
	ASSERT_EQ(capturedOutput.str(), expectedOutput);
}

TEST(ColorTest, AddAndGet) {
	Colors::add("purple", {255, 0, 255});
	std::array<int_least16_t, 3> purple = *Colors::get("purple");
	EXPECT_TRUE(purple[0] == 255);
	EXPECT_TRUE(purple[1] == 0);
	EXPECT_TRUE(purple[2] == 255);
}

TEST(ColorTest, InvalidAddition) {
	EXPECT_THROW(Colors::add("overflow", {256, 256, 256}), std::invalid_argument);
	EXPECT_THROW(Colors::add("negative", {-1, -1, -1}), std::invalid_argument);
	EXPECT_THROW(Colors::add("this name is wrong", {255, 255, 255}), std::invalid_argument);
}

TEST(ColorTest, NonExistingColor) {
	std::array<int_least16_t, 3> white = *Colors::get("idontexist");
	EXPECT_TRUE(white[0] == 255);
	EXPECT_TRUE(white[1] == 255);
	EXPECT_TRUE(white[2] == 255);
}

TEST(ColorTest, Replace) {
	Colors::add("green", {0, 255, 0});
	std::array<int_least16_t, 3> green = *Colors::get("green");
	EXPECT_TRUE(green[0] == 0);
	EXPECT_TRUE(green[1] == 255);
	EXPECT_TRUE(green[2] == 0);

	Colors::add("green", {0, 254, 0});
	green = *Colors::get("green");
	EXPECT_TRUE(green[1] == 254);
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
