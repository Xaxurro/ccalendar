#include <cstddef>
#include <gtest/gtest.h>
#include <iostream>
#include <string>
#include "../event.h"

void checkTagSize(std::string str, size_t expectedSize) {
	Event event(str);
	Tags* tags = event.getTags();
	EXPECT_TRUE(tags->size() == expectedSize);
}

TEST(EventTest, InvalidTagSyntax) {
	checkTagSize("2025 01 06 [this event has no tags!", 0);
	checkTagSize("2025 01 06 this one neither!", 0);
	checkTagSize("2025 01 06 [] this one neither!", 0);
	checkTagSize("2025 01 06 [,] this does!", 1);
	checkTagSize("2025 01 06 [bold] this one is bold!", 1);
	checkTagSize("2025 01 06 [bold, ] this one is just bold!", 1);
	checkTagSize("2025 01 06 [bold underline] this one is bold and underline!", 2);
}

void checkEmptyTags(Tags* tags) {
	EXPECT_TRUE(tags->size() == 0);
	EXPECT_FALSE(tags->has("="));
}

TEST(EventTest, InvalidParsing) {
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

	// Empty
	tags.setTags("");
	EXPECT_FALSE(tags.has("this"));
	checkEmptyTags(&tags);

	tags.setTags("=");
	checkEmptyTags(&tags);

	tags.setTags("= ");
	checkEmptyTags(&tags);

	tags.setTags(" =");
	checkEmptyTags(&tags);

	tags.setTags(" = ");
	checkEmptyTags(&tags);

	tags.setTags(" =red");
	EXPECT_TRUE(tags.size() == 0);
	EXPECT_FALSE(tags.has("="));

	tags.setTags("color= ");
	EXPECT_TRUE(tags.size() == 1);
	EXPECT_TRUE(tags.has("color"));
	EXPECT_FALSE(tags.has("="));
}
