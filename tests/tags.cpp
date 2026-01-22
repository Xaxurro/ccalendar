#include <cstddef>
#include <gtest/gtest.h>
#include <string>
#include "../event.h"

void checkTagSize(std::string str, size_t expectedSize) {
	Event event(str);
	Tags* tags = event.getTags();
	EXPECT_EQ(tags->size(), expectedSize);
}

TEST(TagsTest, InvalidTagSyntax) {
	checkTagSize("06 01 2025 [this event has no tags!", 0);
	checkTagSize("06 01 2025 this one neither!", 0);
	checkTagSize("06 01 2025 [] this one neither!", 0);
	checkTagSize("06 01 2025 [,] this does!", 1);
	checkTagSize("06 01 2025 [bold] this one is bold!", 1);
	checkTagSize("06 01 2025 [bold, ] this one is just bold!", 1);
	checkTagSize("06 01 2025 [bold underline] this one is bold and underline!", 2);
}

void checkEmptyTags(std::string str) {
	Tags tags;
	tags.setTags(str);
	EXPECT_EQ(tags.size(), 0);
	EXPECT_FALSE(tags.has("="));
}

TEST(TagsTest, BlankTags) {
	checkEmptyTags("");
	checkEmptyTags("=");
	checkEmptyTags("= ");
	checkEmptyTags(" =");
	checkEmptyTags(" = ");
	checkEmptyTags("  =  ");
}

TEST(TagsTest, InvalidParsing) {
	Tags tags;
	tags.setTags("hello this color=red is a test");
	// Has no value
	EXPECT_FALSE(tags.has("bold"));
	EXPECT_TRUE(tags.has("this"));
	EXPECT_FALSE(tags.has("thi"));

	// Has value
	EXPECT_TRUE(tags.has("color"));
	EXPECT_TRUE(tags.has("color="));
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
