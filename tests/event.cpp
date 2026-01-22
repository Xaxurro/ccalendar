#include <gtest/gtest.h>
#include <string>
#include "../event.h"

TEST(EventTest, ConstructorNoDescription) {
	EXPECT_EQ(Event("2024 02 29").isValid(), false);
}

TEST(EventTest, ConstructorIncompleteDate) {
	EXPECT_THROW(Event("2024 02"), std::invalid_argument);
}

TEST(EventTest, ConstructorNoSpaceBetweenDateAndDescription) {
	//EXPECT_THROW(Event("2024 02 28This should throw something"), std::invalid_argument);
	Event event("2024 02 28this has no space in between!");
	EXPECT_EQ(event.toDateString(), std::string("2024 2 28"));
	EXPECT_EQ(event.getDescription(), std::string("this has no space in between!"));
}

TEST(EventTest, ConstructorMissingYearWithDescription) {
	EXPECT_THROW(Event("02 04 This should throw an error!"), std::invalid_argument);
}

TEST(EventTest, DateNegativeYearMonthDay) {
	EXPECT_THROW(Event("2021 12 -31 Day cant be negative!"), std::out_of_range);
	EXPECT_THROW(Event("2021 -12 31 Month cant be negative!"), std::out_of_range);
	EXPECT_THROW(Event("-2021 12 31 Year cant be negative!"), std::out_of_range);
}

TEST(EventTest, DateZeroYearMonthDay) {
	EXPECT_THROW(Event("0 12 31 Year cant be zero!"), std::out_of_range);
	EXPECT_THROW(Event("2021 0 31 Month cant be zero!"), std::out_of_range);
	EXPECT_THROW(Event("2021 12 0 Day cant be zero!"), std::out_of_range);
}

TEST(EventTest, DateInvalidOutOfRange) {
	EXPECT_THROW(Event("2021 13 31 Month 13 doesnt exists!"), std::out_of_range);
	EXPECT_THROW(Event("2021 12 32 There is no month with 32 days!"), std::out_of_range);
	EXPECT_THROW(Event("2021 02 29 This year doesnt has a february with 29 days!"), std::invalid_argument);
	EXPECT_THROW(Event("2021 04 31 This month doesnt has 31 days!"), std::invalid_argument);
}
