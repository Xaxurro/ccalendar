#pragma once

#include <array>
#include <cctype>
#include <cstdint>
#include <map>
#include <regex>
#include <stdexcept>
#include <string>

#define COLOR_WHITESPACE_REGEX "[ \t.:,;-_]"
#define COLOR_NAME_REGEX "[a-zA-Z0-9_-]+"
#define COLOR_RGB_REGEX "(" COLOR_NAME_REGEX ")" COLOR_WHITESPACE_REGEX "+(\\d{1,3})" COLOR_WHITESPACE_REGEX "+(\\d{1,3})" COLOR_WHITESPACE_REGEX "+(\\d{1,3})"
#define COLOR_HEX_REGEX "(" COLOR_NAME_REGEX ")" COLOR_WHITESPACE_REGEX "+#([a-fA-F0-9]{2})([a-fA-F0-9]{2})([a-fA-F0-9]{2})"
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
		//Transforms 2 HEX chars to RGB, example:
		//"FF" returns 255
		static int_least16_t hexToRgb(std::string hex) {
			int_least16_t value = 0;
			if (isdigit(hex[1])) value += hex[1] - '0';
			if (tolower(hex[1]) >= 'a' && tolower(hex[1]) <= 'f') value += (tolower(hex[1]) - 'a') + 10;
			if (isdigit(hex[0])) value += (hex[0] - '0') * 16;
			if (tolower(hex[0]) >= 'a' && tolower(hex[0]) <= 'f') value += ((tolower(hex[0]) - 'a') + 10) * 16;
			return value;
		}

		static void add(std::string colorName, std::array<int_least16_t, 3> rgb) {
			if (rgb[0] > 255 || rgb[1] > 255 || rgb[2] > 255 || rgb[0]  < 0 || rgb[1]  < 0 || rgb[2]  < 0) throw std::invalid_argument("RGB values range from 0 - 255 " + std::to_string(rgb[0]) + " " + std::to_string(rgb[1]) + " " +  std::to_string(rgb[2]) + " (" + colorName + ")");
			if (!std::regex_match(colorName, colorNameRegex)) throw std::invalid_argument("colorName: " + colorName + " must match regex " + COLOR_NAME_REGEX);
			colors[colorName] = rgb;
		}

		static std::array<int_least16_t, 3>* get(std::string colorName) {
			if (colors.find(colorName) == colors.end()) return get("white");
			return &colors[colorName];
		}
};
