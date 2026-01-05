#include <gtest/gtest.h>
#include "../event.h"

TEST(EventTest, ConstructorNoDescription) {
	EXPECT_THROW(Event("2024 02 29"), std::invalid_argument);
}

TEST(EventTest, ConstructorIncompleteDate) {
	EXPECT_THROW(Event("2024 02"), std::invalid_argument);
}

TEST(EventTest, ConstructorMissingYearWithDescription) {
	EXPECT_THROW(Event("02 29 This should throw an error!"), std::invalid_argument);
}

TEST(EventTest, ConstructorInvalidDateFebruary) {
	EXPECT_THROW(Event("2021 02 29 This should throw an error!"), std::invalid_argument);
}

TEST(EventTest, ConstructorInvalidDateMonthWith30Days) {
	EXPECT_THROW(Event("2021 04 31 This should throw an error!"), std::invalid_argument);
}

TEST(EventTest, ConstructorInvalidDateMonthWith31Days) {
	EXPECT_THROW(Event("2021 05 32 This should throw an error!"), std::invalid_argument);
}
