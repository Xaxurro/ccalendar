#pragma once

#include <array>
#include <cstdint>
#include <map>
#include <regex>
#include <stdexcept>
#include <string>

#define COLOR_NAME_REGEX "^[a-zA-Z0-9]+$"
class Colors {
	private:
		inline static std::regex colorNameRegex = std::regex(COLOR_NAME_REGEX);
		inline static std::map<std::string, std::array<int_least16_t, 3>> colors {
			{"white", {255	, 255	, 255	}},
			{"red"	, {255	, 0	, 0	}},
			{"green", {0	, 255	, 0	}},
			{"blue"	, {0	, 0	, 255	}}
		};

	public:
		static void add(std::string colorName, std::array<int_least16_t, 3> rgb) {
			if (rgb[0] > 255 || rgb[1] > 255 || rgb[2] > 255 || rgb[0]  < 0 || rgb[1]  < 0 || rgb[2]  < 0) throw std::invalid_argument("RGB values range from 0 - 255 " + std::to_string(rgb[0]) + " " + std::to_string(rgb[1]) + " " +  std::to_string(rgb[2]) + " (" + colorName + ")");
			if (!std::regex_search(colorName, colorNameRegex)) throw std::invalid_argument("colorName: " + colorName + " must match regex " + COLOR_NAME_REGEX);
			colors[colorName] = rgb;
		}

		static std::array<int_least16_t, 3>* get(std::string colorName) {
			if (colors.find(colorName) == colors.end()) return get("white");
			return &colors[colorName];
		}
};
