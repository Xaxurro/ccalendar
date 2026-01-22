#ifndef H_CALENDAR_STRINGS_UTILS
#define H_CALENDAR_STRINGS_UTILS
#include <cstdint>
#include <string>

bool str_is_blank(std::string str);
int_least16_t str_find_tag_clousure(std::string description);
bool str_has_value(std::string tag);

#endif // H_CALENDAR_STRINGS_UTILS
