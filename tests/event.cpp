#include <gtest/gtest.h>
#include <string>
#include "../event.h"

TEST(EventTest, ConstructorNoDescription) {
	EXPECT_EQ(Event("29 02 2024").isInvalid(), true);
}

TEST(EventTest, ConstructorIncompleteDate) {
	EXPECT_THROW(Event("28"), std::invalid_argument);
	EXPECT_THROW(Event("28 This should throw an error!"), std::invalid_argument);
	EXPECT_THROW(Event("28 02"), std::invalid_argument);
	EXPECT_THROW(Event("02 04 This should throw an error!"), std::invalid_argument);
}

TEST(EventTest, ConstructorNoSpaceBetweenDateAndDescription) {
	//EXPECT_THROW(Event("2024 02 28This should throw something"), std::invalid_argument);
	Event event("28 02 2024this has no space in between!");
	EXPECT_EQ(event.getDate()->toString(), std::string("2024 2 28"));
	EXPECT_EQ(event.getDescription(), std::string("this has no space in between!"));
}

TEST(EventTest, ConstructorDateNoSpace) {
	EXPECT_THROW(Event event("28022024this has no spaces on Date!"), std::invalid_argument);
}

TEST(EventTest, DateNegativeYearMonthDay) {
	EXPECT_THROW(Event("-12 31 2021 Day cant be negative!"), std::out_of_range);
	EXPECT_THROW(Event("12 -31 2021 Month cant be negative!"), std::out_of_range);
	EXPECT_THROW(Event("12 31 -2021 Year cant be negative!"), std::out_of_range);
}
