/* 
Created by: Jason Acheampong
* UPM = Unsupervised Product Matching (Using Combinations and Permutations)
* UPM[x] = Unsupervised Product Matching Page X
*/

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <sstream>
#include <functional>
using namespace std;

class Token;

static const string attributes[] = {"bytes", "hz", "bps", "meters", "m", "gb", "mb", "tb", "kb", "km", "kilometers", "\"", "”", "'"};
vector<Token> all_tokens;

class Token {
	hash<string> str_hash;
	public:
		int id;
		int frequency;
		string value;
		int semantic;
	
	Token(string value) {
		this->value = value;
		this->id = str_hash(value);
	}

	/* 
	Type Semantics Identification Rule/s - As defined by UPM[4]
	Attribute: (1) Numeric tokens followed by measurement units, or (2) mixed tokens ending in a measurement unit
	
	Model: The first mixed token in the title which does not represent an attribute
	
	Model: All the rest mixed tokens in the title which do not represent an attribute
	
	Model: A numeric token which is not followed by a measurement unit
	
	Normal: All the other tokens of the title
	*/

	void define_semantic() {
		
	}


};

class Product {
	
	public:
		// The retailer
		string vendor;

		string title;
		
		// The tokenized title
		vector<string> tokenized_title;

		// Object Token pointers
		vector<Token> Token;

		Product(string vendor, string title) {
			this->vendor = vendor;
			this->title = title;
		}

		void token_concatenizer() {
			for(string x:this->tokenized_title) {
				cout << x << endl;
			}
		}

		void generate_tokens() {
			stringstream check1(this->title);
			string temp;
			while (getline(check1, temp, ' ')) {
				tokenized_title.push_back(temp);
			}
		}

};

int main() {
	Product amazon("Amazon", "Asus Viviobook");
	amazon.generate_tokens();
	amazon.token_concatenizer();
	return 1;
}
