#include <gtest/gtest.h>

#include "../colors.h"

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

