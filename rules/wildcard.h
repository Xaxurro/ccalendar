#include "rule.h"

#define REGEX_WILDCARD "\\*"
class RuleWildcard: public Rule {
	public:
          const bool isValidIn(Date* date);
};
