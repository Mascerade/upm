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

static const string attributes[] = {"bytes", "hz", "bps", "meters", "m", "gb", "mb", "tb", "kb", "km", "kilometers", "ddr4", "ddr3", "ram", "\"", "'"};
static const string punctuations = ",;:]}[{|}]()`~&!@#$%^*";
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
		vector<Token> Tokens;

		Product(string vendor, string title) {
			this->vendor = vendor;
			this->title = title;
		}

		void generate_tokens() {
			stringstream check1(this->title);
			string temp;
			while (getline(check1, temp, ' ')) {
				remove_if(temp.begin(), temp.end(), ::isspace);
				for(char character : punctuations) {
					temp.erase(remove(temp.begin(), temp.end(), character), temp.end());
				}

				transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
				tokenized_title.push_back(temp);
			}
		}

		void token_concatenator() {
			for(int i = 0; i < tokenized_title.size(); i++) {
				for(string attribute : attributes) {
					if(tokenized_title[i] == attribute) {
						tokenized_title[i - 1].append(attribute);
						tokenized_title.erase(tokenized_title.begin() + i);
					}
				}
			}
		}
};

int main() {
	Product amazon("Amazon", "ASUS VivoBook F510UA 15.6 Full HD Nanoedge Laptop, Intel Core i5-8250U Processor, 8 GB DDR4 RAM, 1 TB HDD, USB-C, Fingerprint, Windows 10 Home - F510UA-AH51, Star Gray");
	amazon.generate_tokens();
	amazon.token_concatenator();
	for(string x:amazon.tokenized_title) {
		cout << x << endl;
	}
	return 1;
}
