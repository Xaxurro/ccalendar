#ifndef H_CALENDAR_STRINGS_UTILS
#define H_CALENDAR_STRINGS_UTILS
#include <cstdint>
#include <string>

bool str_is_blank(std::string str);
int_least16_t str_find_tag_clousure(std::string description, char opening, char closure);
bool str_has_value(std::string tag);
std::string str_trim_left(std::string str);

#endif // H_CALENDAR_STRINGS_UTILS
