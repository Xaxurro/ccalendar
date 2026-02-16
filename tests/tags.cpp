#include <cstddef>
#include <gtest/gtest.h>
#include <string>
#include "../tags.h"

void checkEmptyTags(std::string str) {
	Tags tags(str);
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
