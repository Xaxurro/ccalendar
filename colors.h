#ifndef H_CALENDAR_COLOR
#define H_CALENDAR_COLOR


#include <array>
#include <map>
#include <string>
class Colors {
	private:
		inline static std::map<std::string, std::array<int, 3>> colors {
			{"white", {255	, 255	, 255	}},
			{"red"	, {255	, 0	, 0	}},
			{"green", {0	, 255	, 0	}},
			{"blue"	, {0	, 0	, 255	}}
		};

	public:
		static void add(std::string colorName, std::array<int, 3> rgb) {
			colors[colorName] = rgb;
		}

		static std::array<int, 3>* get(std::string colorName) {
			if (colors.find(colorName) == colors.end()) return get("white");
			return &colors[colorName];
		}
};
#endif // H_CALENDAR_COLOR
