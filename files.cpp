#include "files.h"
#include "colors.h"
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <regex>
#include <string>

namespace files {
	std::filesystem::path rootDirectory;

	void setRootDirectory() {
		std::string homeDir = std::string(getenv("HOME"));
		setenv(DIRECTORY_ENV, (homeDir + std::string(DIRECTORY_DEFAULT)).c_str(), 0);
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
	std::filesystem::path getColorsFile() {
		return rootDirectory / "colors";
	}

	//Returns the path to the "$CALENDAR_DIRECTORY/colors" file
	std::filesystem::path getFileConfig() {
		return rootDirectory / "config";
	}

	void ensureFilesExists() {
		files::ensureRootDirExists();
		files::ensureFileExists("colors");
		files::ensureFileExists("config");
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
			if (line.substr(0, 2) == "//") continue;
			if (line.size() == 0) continue;
			events.push_back(new Event(line));
		}
		return events;
	}

	void readColorsFile() {
		std::ifstream colorFile(getColorsFile());
		std::string line;
		while (std::getline(colorFile, line)) {
			std::regex rgbRegex(COLOR_RGB_REGEX);
			std::smatch match;
			if (std::regex_match(line, match, rgbRegex)) {
				std::array<int_least16_t, 3> rgb = {(int_least16_t)std::stoi(match[2]), (int_least16_t)std::stoi(match[3]), (int_least16_t)std::stoi(match[4])};
				Colors::add(match[1], rgb);
				continue;
			}
			std::regex hexRegex(COLOR_HEX_REGEX);
			if (std::regex_match(line, match, hexRegex)) {
				std::array<int_least16_t, 3> rgb = {Colors::hexToRgb(match[2]), Colors::hexToRgb(match[3]), Colors::hexToRgb(match[4])};
				Colors::add(match[1], rgb);
				continue;
			}
			std::cout << line << std::endl;
		}
	}
}
