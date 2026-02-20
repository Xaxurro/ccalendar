#include "event.h"
#include "files.h"
#include <filesystem>
#include <iostream>
#include <list>

std::list<Event*> getAllEvents() {
	std::list<Event*> eventList = {};
	for (std::filesystem::path path : files::getAllFiles()) {
		for(Event* event : files::readFile(path)) eventList.push_back(event);
	}
	return eventList;
}

int main (int argc, char *argv[]) {
	files::setRootDirectory();

	files::ensureRootDirExists();
	files::ensureFileExists("color");
	files::ensureFileExists("config");

	std::list<Event*> eventList = getAllEvents();

	//TODO Implement commands

	for (Event* event : eventList) {
		delete event;
	}

	return 0;
}
