#include "files.h"
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <string>

#define CALENDAR_EXTENSION ".cldr"
#define DIRECTORY_DEFAULT "$HOME/calendar"
#define DIRECTORY_ENV "CALENDAR_DIRECTORY"

namespace files {
	std::filesystem::path rootDirectory;

	void setRootDirectory() {
		setenv(DIRECTORY_ENV, DIRECTORY_DEFAULT, 0);
		rootDirectory = getenv(DIRECTORY_ENV);
	}
	
	//Returns all the `.cldr` files under $CALENDAR_DIRECTORY
	std::list<std::filesystem::path> getAllFiles() {
		std::list<std::filesystem::path> files = {};
		for (std::filesystem::path path : std::filesystem::recursive_directory_iterator(rootDirectory)) {
			if (path.extension() == CALENDAR_EXTENSION) files.push_back(path);
		}
		return files;
	}

	//Returns the path to the "$CALENDAR_DIRECTORY/colors" file
	std::filesystem::path getFileColors() {
		return rootDirectory / "colors";
	}

	//Returns the path to the "$CALENDAR_DIRECTORY/colors" file
	std::filesystem::path getFileConfig() {
		return rootDirectory / "config";
	}

	//Given the relative `path` if it doesn't exists, it creates the directory, if it's a file throws error
	void ensureRootDirExists() {
		if (std::filesystem::exists(rootDirectory)) {
			if (std::filesystem::is_regular_file(rootDirectory)) throw std::filesystem::filesystem_error("root directory is a file", std::error_code());
			return;
		}
		std::filesystem::create_directory(rootDirectory);
	}

	//Given the relative `path` if it doesn't exists, it creates the file, if it's a directory throws error
	void ensureFileExists(std::string path) {
		if (std::filesystem::exists(rootDirectory/path)) {
			if (std::filesystem::is_directory(rootDirectory/path)) throw std::filesystem::filesystem_error(path + " is a directory", std::error_code());
			return;
		}
		std::ofstream(rootDirectory/path);
	}

	std::list<Event*> readFile(std::filesystem::path path) {
		std::list<Event*> events = {};
		std::ifstream eventFile(path);
		std::string line;
		while (std::getline(eventFile, line)) {
			if (line.substr(0, 1) == "#") continue;
			events.push_back(new Event(line));
		}
		return events;
	}
}
