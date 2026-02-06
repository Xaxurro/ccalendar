#include <cstddef>
#include <gtest/gtest.h>
#include <string>
#include "../tags.h"

void checkEmptyTags(std::string str) {
	Tags tags;
	tags.setTags(str);
	ASSERT_EQ(tags.size(), 0);
	ASSERT_FALSE(tags.has("="));
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
	ASSERT_FALSE(tags.has("bold"));
	ASSERT_TRUE(tags.has("this"));
	ASSERT_FALSE(tags.has("thi"));

	// Has value
	ASSERT_TRUE(tags.has("color"));
	ASSERT_TRUE(tags.has("color="));
	ASSERT_FALSE(tags.has("col"));
	ASSERT_FALSE(tags.has("red"));
	ASSERT_FALSE(tags.has("=red"));
	ASSERT_FALSE(tags.has("="));

	tags.setTags(" =red");
	ASSERT_EQ(tags.size(), 0);
	ASSERT_FALSE(tags.has("red"));

	tags.setTags("color= ");
	ASSERT_EQ(tags.size(), 1);
	ASSERT_TRUE(tags.has("color"));
	ASSERT_FALSE(tags.has("="));
}
