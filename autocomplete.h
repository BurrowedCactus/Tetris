#ifndef AUTOCOMPLETE_H
#define AUTOCOMPLETE_H
#include <string>
#include <vector>
#include <memory>
#include "constants.h"

class TrieNode {
public:
	bool isWord;
	int numContained;
	std::vector<std::unique_ptr<TrieNode>> ltrs;

	TrieNode();
	std::string find(const std::string&);
	std::string match(const std::string&);
	void insert(const std::string&);
};
#endif 
