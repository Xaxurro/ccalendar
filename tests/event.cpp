#include <gtest/gtest.h>
#include <iostream>
#include <ostream>
#include <string>
#include "../event.h"
#include "../colors.h"

std::string getPrint(Event* event, Date* date) {
	std::stringstream capturedOutput;
	std::streambuf* originalCoutBuf = std::cout.rdbuf();
	std::cout.rdbuf(capturedOutput.rdbuf());
	event->print(date);
	std::cout.rdbuf(originalCoutBuf);
	return capturedOutput.str();
}

TEST(EventTest, SpecialCharacters) {

	Event event("* 1 * Global Game Jam \\y");
	Date date(10, 1, 2022);

	std::string expectedOutput("10 1 2022 Global Game Jam 2022\033[0m\n");

	ASSERT_EQ(getPrint(&event, &date), expectedOutput);
}

TEST(EventTest, Print) {
	Colors::add("red", {224, 27, 36});
	Event event("08 11 * [color=red bold underline] My Birthday");
	Date date(8, 11, 2002);

	std::string expectedOutput("8 11 2002 \033[1m\033[4m\033[38;2;224;27;36mMy Birthday\033[0m\n");
	ASSERT_EQ(getPrint(&event, &date), expectedOutput);
}

