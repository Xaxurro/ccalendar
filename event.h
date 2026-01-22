#ifndef H_CALENDAR_EVENT
#define H_CALENDAR_EVENT

#include <cctype>
#include <sstream>
#include <stdexcept>
#include <string>
#include "date.h"
#include "strings.h"
#include "tags.h"

class Event {
	private:
		Date date;
		Tags tags;
		std::string description = "";

	public:
		std::string getDescription() { return description; }
		Date* getDate() { return &date; }
		Tags* getTags() { return &tags; }

		bool isInvalid() { return date.isInvalid() || str_is_blank(description); }

		// event_string: a line that defines an event
		Event(std::string event_string);
};
#endif // !H_CALENDAR_EVENT
