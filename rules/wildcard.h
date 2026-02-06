#include "rule.h"
class RuleWildcard: public Rule {
	public:
          RuleWildcard() {}

          bool isValidIn(Date date);
};
