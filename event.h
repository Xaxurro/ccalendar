#ifndef H_CALENDAR_EVENT
#define H_CALENDAR_EVENT

#include <cstdint>
#include <sstream>
#include <stdexcept>
#include <string>
#include "date.h"
class Event {
	private:
		uint_least16_t year = 2000;
		uint_fast8_t month = JANUARY;
		uint_fast8_t day = 1;
		std::string description = "";

		void setYear(int year_new) {
			year = year_new;
		}

		void setMonth(int month_new) {
			// `month` is in range 1 - 12 (inclusive both)
			if (month_new <= 0 || month_new > DECEMBER) {
				throw std::invalid_argument("New month is in an invalid range (<= 0 || > 12)");
			}
			month = month_new;
		}

		void setDay(int day_new) {
			// `day` min value is 1, max values are:
			// `28` in february
			// `29` if february is in a year % 4 == 0
			// `30` if is april, june, september, november
			// `31` every other number 
			if (day_new <= 0 || day_new > 31) {
				throw std::invalid_argument("New day is in an invalid range (<= 0 || > 31)");
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

		// event_string: a line that defines an event
		Event(std::string event_string) {
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
			// Set remaining contents to description and delete trail space
			std::getline(ss, description);
			description.erase(0, 1); 
		}
};
#endif // !H_CALENDAR_EVENT
