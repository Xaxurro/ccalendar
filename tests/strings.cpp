#include <cassert>
#include <gtest/gtest.h>
#include <string>

#include "../strings.h"

TEST(StringTest, Split) {
	std::string str = "a b c";
	std::string delimeter = " ";
	std::list<std::string> listTest = str::split(delimeter, str);
	ASSERT_EQ(listTest.size(), 3);
	std::list<std::string> listCorrect = {"a", "b", "c"};
	std::list<std::string>::iterator iteratorTest = listTest.begin();
	std::list<std::string>::iterator iteratorCorrect;
	for (iteratorCorrect = listCorrect.begin(); iteratorCorrect != listCorrect.end(); ++iteratorCorrect) {
		ASSERT_EQ(*iteratorCorrect, *iteratorTest);
		++iteratorTest;
	}
}
