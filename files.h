#pragma once

#include <list>
#include <filesystem>
#include <string>
#include "event.h"

#define CALENDAR_EXTENSION ".cldr"
#define DIRECTORY_DEFAULT "/calendar"
#define DIRECTORY_ENV "CALENDAR_DIRECTORY"

namespace files {
	extern std::filesystem::path rootDirectory;

	//sets rootDirectory to "$CALENDAR_DIRECTORY" if exists, if not "$HOME/calendar"
	void setRootDirectory();

	//Returns all the `.cldr` files under $CALENDAR_DIRECTORY
	std::list<std::filesystem::path> getAllFiles();

	//Returns the path to the "$CALENDAR_DIRECTORY/colors" file
	std::filesystem::path getFileColors();

	//Returns the path to the "$CALENDAR_DIRECTORY/config" file
	std::filesystem::path getFileConfig();

	//Given the `path` if it doesn't exists, it creates the directory, if it's a file throws error
	void ensureRootDirExists();

	//Given the `path` if it doesn't exists, it creates the file, if it's a directory throws error
	void ensureFileExists(std::string path);

	std::list<Event*> readFile(std::filesystem::path);
}
