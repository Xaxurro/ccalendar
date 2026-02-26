#include "list.h"

RuleList::RuleList() {
}

RuleList::~RuleList() {
	for (Rule* rule : rulesList) delete rule;
	rulesList.clear();
}

bool RuleList::isValidIn(const Date* date) {
	for (Rule* rule : rulesList) if (rule->isValidIn(date)) return true;
	return false;
}

void RuleList::addRule(Rule* newRule) {
	rulesList.push_back(newRule);
}
