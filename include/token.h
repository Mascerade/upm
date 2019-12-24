#pragma once

#include <string>
using namespace std;

class Token {
	hash<string> str_hash;
	public:
		int id;
		int frequency;
		string value;
		int semantic;
	
	Token(string value);

	void define_semantic();

	int get_id() {
		return Token::id;
	};
};
