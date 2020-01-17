#include "autocomplete.h"

using namespace std;

TrieNode::TrieNode():isWord{false}, numContained{0} {
	for (int i = 0; i < ALPHABET; ++i){
		ltrs.emplace_back(unique_ptr<TrieNode>());
	}
}

string TrieNode::match(const string &w){
	if ('A' <= w[0] && w[0] <= 'Z'){
		return w;
	}
	string s;
	try{
		s = find(w);
	} catch(...){}
	return s;
}

string TrieNode::find(const string &w) {
	
	//ending 1
	if (isWord && w.length() == 0) {
		return w;
	}
	if (numContained >= 2 && w.length() == 0){
		throw "duplicated found";
	} else if (numContained >= 2){
		for (int i = 0; i < ALPHABET; ++i) {
			if (ltrs[i] && (char)(i + 'a') == w[0]){
				try{
					string rest = ltrs[i]->find(w.substr(1));
					string zero;
					return zero + (char)(i+'a') + rest;
				} catch(...){
					continue;		
				
				}
			}
		}
		throw "all wrong, not found";
	} else {//numContained <= 1
		for (int i = 0; i < ALPHABET; ++i) {
                        if (ltrs[i] && (w.length() == 0 || (char)(i + 'a') == w[0])){
                                try{
                                        string rest = (w.length() == 0)? ltrs[i]->find(w): ltrs[i]->find(w.substr(1));
                                        string zero;
                                        return zero + (char)(i+'a') + rest;
                                } catch(...){
					throw "the one is wrong, not found";

                                }
                        }
                }
	}
	throw "for safety, not found";
}

void TrieNode::insert(const string &w) {
	if (w.length() == 0) {
		isWord = true;
		return;
	}
	const string next = w.substr(1);
	if (ltrs[((int)(w[0]-'a'))]){
		(*ltrs[(int)(w[0]-'a')]).numContained += 1;
		ltrs[(int)(w[0]-'a')]->insert(next);
	} else {
		ltrs[(int)(w[0]-'a')] = make_unique<TrieNode>();
		(*ltrs[(int)(w[0]-'a')]).numContained += 1;
		ltrs[(int)(w[0]-'a')]->insert(next);
	}
}



