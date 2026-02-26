#pragma once
#include "rule.h"
#include <cstdint>

class RuleList: public Rule {
	private:
		std::list<Rule*> rulesList = {};
	public:
		RuleList();
		~RuleList();

        	bool isValidIn(const Date* date);
        	std::list<Rule*>* getRulesList() { return &rulesList; };
		void addRule(Rule* newRule);
};
