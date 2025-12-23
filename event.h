#ifndef H_EVENT
#define H_EVENT

#include <cstdint>
#include <sstream>
#include <stdexcept>
#include <string>
class Event {
	private:
		uint_least16_t year = 2000;
		uint_fast8_t month = 1;
		uint_fast8_t day = 1;
		std::string description = "";

		void setYear(int year_new) {
			year = year_new;
		}

		void setMonth(int month_new) {
			// `month` is in range 1 - 12 (inclusive both)
			if (month_new <= 0 || month_new > 12) {
				throw std::invalid_argument("New month is in an invalid range (<= 0 || > 12)");
				month = month_new;
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
				day = day_new;
			}
			if (day_new > 30 && (month == 4 || month == 6 || month == 9 || month == 11)) {
				throw std::invalid_argument("New day is in an invalid range (== 31 && month == april, june, september, november)");
			}
			if (day_new > 28 && month == 2) {
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

		// Takes a line that defines an event
		Event(std::string event_string) {
			std::stringstream ss;

			// storing `event_string` into `stringstream`
			ss << event_string;

			// Stores a word
			std::string aux_word;
			int value_found;
			// TODO: REPLACE WITH A FOR LOOP
			int value_index = 0;
			// sets the first 3 words in the string to the object according to index. Once it reaches index 3 (The max) it stops and sets description
			while (value_index < 3) {
				// Extract word by word
				ss >> aux_word;

				if (std::stringstream(aux_word) >> value_found) {
					value_index++;
					switch (value_index) {
					case 1:
						setYear(value_found);
						break;
					case 2:
						setMonth(value_found);
						break;
					case 3:
						setDay(value_found);
						break;
					}
				}
			}
			// Set remaining contents to description and delete remaining space
			std::getline(ss, description);
			description.erase(0, 1); 
		}
};
#endif // !H_EVENT
