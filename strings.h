#pragma once

#include <cstdint>
#include <string>
#include "date.h"

bool str_is_blank(std::string str);
int_least16_t str_find_tag_clousure(std::string description, char opening, char closure);
bool str_has_value(std::string tag);
std::string str_trim_left(std::string str);
void str_replace(std::string strToSearch, std::string strToReplace, std::string* str);
