#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <filesystem>
#include <gtest/gtest.h>
#include <list>
#include <string>
#include <unistd.h>
#include "../files.h"

#define TEST_DIRECTORY "./tests/test-files"

const char* setFakeRootDirectory(std::string fakeRootDirectory) {
	const char* originalEnv = getenv("CALENDAR_DIRECTORY");
	setenv("CALENDAR_DIRECTORY", fakeRootDirectory.c_str(), 1);
	files::setRootDirectory();
	return originalEnv;
}

const char* setFakeRootDirectory() {
	return setFakeRootDirectory(TEST_DIRECTORY);
}

void restoreFakeRootDirectory(const char* originalEnv) {
	setenv("CALENDAR_DIRECTORY", originalEnv, 1);
}



TEST(FilesTest, SetEnvUndefined) {
	std::string originalRootEnv = std::string(getenv(DIRECTORY_ENV));
	unsetenv(DIRECTORY_ENV);
	files::setRootDirectory();
	ASSERT_EQ(std::string(getenv("HOME")) + "/calendar", files::rootDirectory);
	setenv(DIRECTORY_ENV, originalRootEnv.c_str(), 1);
}

TEST(FilesTest, EnvRestoration) {
	const char* originalEnv = setFakeRootDirectory();
	ASSERT_EQ(std::filesystem::path(TEST_DIRECTORY), files::rootDirectory);
	restoreFakeRootDirectory(originalEnv);
}

TEST(FilesTest, FindCldrFiles) {
	const char* originalEnv = setFakeRootDirectory();
	std::list<std::filesystem::path> files = files::getAllFiles();
	ASSERT_FALSE(files.empty());
	ASSERT_TRUE(files.size() == 3);

	for (std::filesystem::path file : files) {
		ASSERT_TRUE(std::filesystem::is_regular_file(file));
		ASSERT_TRUE(file.has_extension());
		ASSERT_TRUE(file.extension() == ".cldr");
	}
	restoreFakeRootDirectory(originalEnv);
}

TEST(FilesTest, EnsureRootNonExistant) {
	std::string fakeRootDirectory = TEST_DIRECTORY "/i-dont-exist";
	const char* originalEnv = setFakeRootDirectory(fakeRootDirectory);
	if (std::filesystem::exists(fakeRootDirectory)) std::filesystem::remove_all(fakeRootDirectory.c_str());
	ASSERT_FALSE(std::filesystem::exists(fakeRootDirectory));

	files::ensureRootDirExists();
	ASSERT_TRUE(std::filesystem::exists(fakeRootDirectory));

	ASSERT_FALSE(std::filesystem::exists(fakeRootDirectory + "/color"));
	files::ensureFileExists("color");
	ASSERT_TRUE(std::filesystem::exists(fakeRootDirectory + "/color"));

	std::filesystem::remove_all(fakeRootDirectory.c_str());
	ASSERT_FALSE(std::filesystem::exists(fakeRootDirectory));
	restoreFakeRootDirectory(originalEnv);
}

TEST(FilesTest, EnsureRootExistant) {
	std::string fakeRootDirectory = TEST_DIRECTORY "/i-do-fully-exist";
	const char* originalEnv = setFakeRootDirectory(fakeRootDirectory);

	files::ensureRootDirExists();
	ASSERT_TRUE(std::filesystem::exists(fakeRootDirectory));

	files::ensureFileExists("color");
	ASSERT_TRUE(std::filesystem::exists(fakeRootDirectory + "/color"));
	restoreFakeRootDirectory(originalEnv);
}

TEST(FilesTest, GetSpecialFiles) {
	const char* originalEnv = setFakeRootDirectory();

	ASSERT_EQ(std::string(files::getFileColors().c_str()), TEST_DIRECTORY "/colors");
	ASSERT_EQ(std::string(files::getFileConfig().c_str()), TEST_DIRECTORY "/config");

	restoreFakeRootDirectory(originalEnv);
}

TEST(FilesTest, ReadPerfectFile) {
	const char* originalEnv = setFakeRootDirectory();

	std::list<std::filesystem::path> pathList = files::getAllFiles();
	ASSERT_EQ(pathList.size(), 3);

	std::filesystem::path perfectFile;
	for (std::filesystem::path path : pathList) {
		if (path.filename() == "perfect.cldr") perfectFile = path;
	}

	ASSERT_TRUE(std::filesystem::exists(perfectFile));

	std::list<Event*> eventList = files::readFile(perfectFile);
	ASSERT_TRUE(eventList.size() == 1);

	Date date(8, 11, 2026);
	eventList.front()->print(&date);

	for (Event* event : eventList) {
		delete event;
	}

	restoreFakeRootDirectory(originalEnv);
}

