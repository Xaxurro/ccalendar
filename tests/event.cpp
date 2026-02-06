#include <gtest/gtest.h>
#include <string>
#include "../event.h"
#include "../rules/rule.h"
#include "../rules/fixed.h"

TEST(EventTest, ConstructorNoDescription) {
	ASSERT_EQ(Event("29 02 2024").isInvalid(), true);
}

TEST(EventTest, ConstructorIncompleteDate) {
	ASSERT_THROW(Event("28"), std::invalid_argument);
	ASSERT_THROW(Event("28 This should throw an error!"), std::invalid_argument);
	ASSERT_THROW(Event("28 02"), std::invalid_argument);
	ASSERT_THROW(Event("02 04 This should throw an error!"), std::invalid_argument);
}

TEST(EventTest, ConstructorNoSpaceBetweenDateAndDescription) {
	Event event("28 02 2024this has no space in between!");

	ASSERT_TRUE(event.getDayRules() != nullptr);
	ASSERT_TRUE(event.getMonthRules() != nullptr);
	ASSERT_TRUE(event.getYearRules() != nullptr);

	std::list<Rule*> dayRules = *event.getDayRules();
	std::list<Rule*> monthRules = *event.getMonthRules();
	std::list<Rule*> yearRules = *event.getYearRules();

	ASSERT_EQ(dayRules.size(), 1);
	ASSERT_EQ(monthRules.size(), 1);
	ASSERT_EQ(yearRules.size(), 1);

	ASSERT_EQ(dynamic_cast<RuleFixed*>(dayRules.front())->getValue(), 28);
	ASSERT_EQ(dynamic_cast<RuleFixed*>(monthRules.front())->getValue(), 2);
	ASSERT_EQ(dynamic_cast<RuleFixed*>(yearRules.front())->getValue(), 2024);
	ASSERT_EQ(event.getDescription(), std::string("this has no space in between!"));
}

TEST(EventTest, ConstructorDateNoSpace) {
	ASSERT_THROW(Event event("28022024this has no spaces on Date!"), std::invalid_argument);
}

TEST(EventTest, DateNegativeYearMonthDay) {
	ASSERT_THROW(Event("-12 31 2021 Day cant be negative!"), std::out_of_range);
	ASSERT_THROW(Event("12 -31 2021 Month cant be negative!"), std::out_of_range);
	ASSERT_THROW(Event("12 31 -2021 Year cant be negative!"), std::out_of_range);
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
