#include "event.h"
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

int main (int argc, char *argv[]) {
	// Default value of `filename`: $HOME/calendar.cldr
	std::string filename(getenv("HOME"));
	filename.append("/calendar.cldr");

	// Asign the $CALENDAR_FILE value to `filename` when it's present
	// TODO: Verify it's a file
	// TODO: Verify it exists
	if (const char* env_value = getenv("CALENDAR_FILE")) {
		filename = env_value;
	}

	// Create the file if it does not exists
	if (!std::filesystem::exists(filename)) {
		std::ofstream file(filename);
	}

	Event event("2024 2 29 test1 test2 test3");
	std::cout << event.toDateString() << std::endl;
	std::cout << event.getDescription() << std::endl;

	return 0;
}
