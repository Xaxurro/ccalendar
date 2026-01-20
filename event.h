#ifndef H_CALENDAR_EVENT
#define H_CALENDAR_EVENT

#include <cctype>
#include <cstdint>
#include <sstream>
#include <stdexcept>
#include <string>
#include "date.h"
#include "tags.h"

class Event {
	private:
		int_least16_t year = 0;
		int_least16_t month = 0;
		int_least16_t day = 0;
		Tags tags;
		std::string description = "";

		void setYear(int_least16_t year_new) {
			if (year_new <= 0) {
				throw std::out_of_range("Year can't be negative!");
			}
			year = year_new;
		}

		void setMonth(int_least16_t month_new) {
			// `month` is in range 1 - 12 (inclusive both)
			if (month_new <= 0 || month_new > DECEMBER) {
				throw std::out_of_range("New month is in an invalid range (<= 0 || > 12)");
			}
			month = month_new;
		}

		void setDay(int_least16_t day_new) {
			// `day` min value is 1, max values are:
			// `28` in february
			// `29` if february is in a year % 4 == 0
			// `30` if is april, june, september, november
			// `31` every other number 
			if (day_new <= 0 || day_new > 31) {
				throw std::out_of_range("New day is in an invalid range (<= 0 || > 31)");
			}
			if (day_new > 30 && (month == APRIL || month == JUNE || month == SEPTEMBER || month == NOVEMBER)) {
				throw std::invalid_argument("New day is in an invalid range (== 31 && month == april, june, september, november)");
			}
			if (day_new > 28 && month == FEBRUARY) {
				// early return if year %4=0
				if (day_new == 29 && year % 4 == 0) {
					day = day_new;
					return;
				}
				throw std::invalid_argument("New day is in an invalid range (> 28 && month == february || == 29 && year % 4 != 0)");
			}
			day = day_new;
		}

	public:
		// Concatenates the dates values
		std::string toDateString() {
			std::string output = "";
			return std::to_string(year) + " " + std::to_string(month) + " " + std::to_string(day);
		}

		std::string getDescription() {
			return description;
		}

		Tags* getTags() {
			return &tags;
		}

		bool isValid() {
			return !(year == 0 && month == 0 && day == 0);
		}

		// event_string: a line that defines an event
		Event(std::string event_string) : tags() {
			std::stringstream ss;

			// storing `event_string` into `stringstream`
			ss << event_string;

			int value_found;
			// sets the first 3 words in the string to date values according to index.
			for (int index = 0; index < 3; index++) {
				if (!(ss >> value_found)) {
					throw std::invalid_argument("Event has incorrect format (correct: YYYY MM DD)");
				}
				switch (index) {
				case 0:
					setYear(value_found);
					break;
				case 1:
					setMonth(value_found);
					break;
				case 2:
					setDay(value_found);
					break;
				}
			}
			// Set remaining contents to description and delete initial trail spaces
			std::getline(ss, description);
			while (description.size() > 0 && isspace(description[0])) {
				description.erase(0, 1);
			}

			//Searches for [...] in the description and sends ... to Tag constructor
			std::size_t tagClosureIndex = description.find_first_of(']');
			if (tagClosureIndex != description.npos && description[0] == '[') {
				tags.setTags(description.substr(1, tagClosureIndex-1));
			}

			//Sets the Event Object as Invalid if no description, there should be a better way to do this
			if (description.empty()) {
				year = 0;
				month = 0;
				day = 0;
			}
		}
};
#endif // !H_CALENDAR_EVENT
