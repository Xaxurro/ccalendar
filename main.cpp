#include "event.h"
#include "files.h"
#include "strings.h"
#include <array>
#include <cctype>
#include <cstdint>
#include <filesystem>
#include <iostream>
#include <list>
#include <string>
#include <vector>

#define VERSION "0.1-alpha"

std::list<Event*> getAllEvents() {
	std::list<Event*> eventList = {};
	for (std::filesystem::path path : files::getAllFiles()) {
		for(Event* event : files::readFile(path)) eventList.push_back(event);
	}
	return eventList;
}

void printVersion() {
	std::cout << "VERSION:" << std::endl;
	std::cout << "\t" VERSION << std::endl;
	exit(0);
}
void printHelp() {
	std::cout << "USAGE:" << std::endl;
	std::cout << "\t-h / --help\t\tPrints this message" << std::endl;
	std::cout << "\t-v / --version\t\tPrints ccalendar version" << std::endl;
	std::cout << "\t-b / --before <int>\tDays Before Today" << std::endl;
	std::cout << "\t-a / --after <int>\tDays After Today" << std::endl;
	std::cout << "\t-l / --label <string>\tHas Labels, separated by ','" << std::endl;
	std::cout << "\t-t / --today\tprints today's date" << std::endl;
	printVersion();
}

void printToday() {
	std::cout << Date::today().toString() << std::endl;
}

struct {
	int_least16_t daysBefore = 0;
	int_least16_t daysAfter = 0;
	std::list<std::string> labelsToSearch = {};
} options;

int_least16_t toInt(std::string str) {
	for (char c : str) if (!isdigit(c)) printHelp();
	return std::stoi(str);
}

// void parseConfig() {
// }

void parseColors() {
	
}

void parseArguments(int argc, std::vector<std::string> args) {
	for (int i = 0; i < argc; i++) {
		std::string arg = args[i];

		if (arg == "-h" || arg == "--help") printHelp();
		if (arg == "-v" || arg == "--version") printVersion();
		if (arg == "-t" || arg == "--today") printToday();

		if (i+1 == argc) continue;

		std::string argNext = args[i+1];

		if (arg == "-b" || arg == "--before") options.daysBefore = toInt(argNext);
		if (arg == "-a" || arg == "--after") options.daysAfter = toInt(argNext);
		if (arg == "-l" || arg == "--label") {
			options.labelsToSearch = str::split(",", &argNext);
		}
	}
}

int main (int argc, char *argv[]) {
	//Parse char*[] to vector<string>
	std::vector<std::string> args;
	for (int i = 0; i < argc; i++) {
		args.push_back(argv[i]);
	}

	// parseConfig();
	parseColors();
	parseArguments(argc, args);

	files::setRootDirectory();

	files::ensureRootDirExists();
	files::ensureFileExists("color");
	files::ensureFileExists("config");

	std::list<Event*> eventList = getAllEvents();

	//TODO Implement commands
	//only query by default
	
	Date today = Date::today();
	bool printedTodayBanner = false;
	//change `pointer` name
	for (Date pointer = today - options.daysBefore; pointer != today + options.daysAfter; pointer = pointer + 1) {
		for (Event* event : eventList) {
			//TODO IMPLEMENT SEARCH BY LABEL
			if (options.labelsToSearch.empty()) {
				if (event->isValidIn(&pointer)) {
					if (pointer >= today && !printedTodayBanner) {
						std::cout << "TODAY" << std::endl;
						printedTodayBanner = true;
					}
					event->print(&pointer);
				}
			} else {
				for (std::string label : options.labelsToSearch) {
					if (event->hasLabel(label) && event->isValidIn(&pointer)) {
						if (pointer >= today && !printedTodayBanner) {
							std::cout << "TODAY" << std::endl;
							printedTodayBanner = true;
						}
						event->print(&pointer);
					}
				}
			}
		}
	}

	for (Event* event : eventList) {
		delete event;
	}

	return 0;
}
