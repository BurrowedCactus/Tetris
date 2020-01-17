#ifndef _INTERPRETER_H_
#define _INTERPRETER_H_

#include "autocomplete.h"
#include "quadris.h"
#include <string>
#include <sstream>
#include <vector>

class Interpreter {
	std::unique_ptr<TrieNode> node;
	std::string stack;
public:
	Interpreter();
	bool isValid(const std::string& command);
	bool validMultiply(const std::string& command);
	void processCommand(const std::string& command, Quadris *q);
};

#endif

