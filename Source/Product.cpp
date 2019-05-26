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
class Combination;
Token* add_token(string);
static const string attributes[] = {"bytes", "hz", "bps", "meters","gb", "mb", "tb", "kb", "km", "kilometers", "\"", "'"};
static const string punctuations = ",;:]}[{|}]()`~&!@#$%^*";

vector<int> token_hashes;
vector<Token> all_tokens;

class Combination {
	public:
		int id;
		int frequency;
		vector<Token*> tokens;
		int dacc;

		Combination(vector<Token*> vec) {
			tokens = vec;
		}
};

class Token {
	hash<string> str_hash;
	public:
		int id;
		int frequency;
		string value;
		char semantic;
	
	Token(string value) {
		this->value = value;
		this->id = str_hash(value);
		frequency = 0;
	}

	/* 
	Type Semantics Identification Rule/s - As defined by UPM[4]
	* The numbers in parenthesis represent 
	Attribute: (1) Numeric tokens followed by measurement units, or mixed tokens ending in a measurement unit
	
	Model: (2) The first mixed token in the title which does not represent an attribute
	
	Model: (3) All the rest mixed tokens in the title which do not represent an attribute
	
	Model: (4) A numeric token which is not followed by a measurement unit
	
	Normal: (5) All the other tokens of the title
	*/

	void define_semantic() {
		
		// If all of the characters are number, then it most likely represents an item model (UPM[4])
		if (all_of(value.begin(), value.end(), ::isdigit)) {
			semantic = 'I';
			return;
		}

		// If the string has the attribute in it and the character
		// before the attribute is a digit, consider it an attribute (UPM[4])
		for (string attribute : attributes){
			int found = value.find(attribute);
			if (found != value.npos) {
				if (isdigit(value[found - 1])){
					semantic = 'A';
					return;
				}
			}
		}

		// If its not an attribute, but it has a combination
		// of both numbers and characters, consider it an item model (UPM[4])
		for (char character : value) {
			int digits = 0;
			if (isdigit(character)) {
				digits += 1;
			}

			if (digits > 0) {
				semantic = 'I';
				return;
			}

		}

		// If it is neither an attribute nor an item model, consider it a normal token (UPM[4])
		semantic = 'N';
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
		vector<Token*> Tokens;

		Product(string vendor, string title) {
			// Set the attributes of of the product
			this->vendor = vendor;
			this->title = title;
		}

		void generate_tokens() {
			// Appends the tokens tokenized_title vector

			// Check1 is used to parse the string by space 
			stringstream check1(this->title);
			string temp;

			// Goes through each token and gets rid of the punctuation from the token
			while (getline(check1, temp, ' ')) {
				remove_if(temp.begin(), temp.end(), ::isspace);
				for(char character : punctuations) {
					temp.erase(remove(temp.begin(), temp.end(), character), temp.end());
				}

				// Converts the token to lower case letters
				transform(temp.begin(), temp.end(), temp.begin(), ::tolower);

				// Makes sure no duplicates are added to the title
				if (tokenized_title.size() != 0) {
					
					// If add is true, add the token to the tokenized_title
					bool add = true;
					for (string x : tokenized_title) {
						
						// If the same token is found, set add to false and don't add it to the tokenized_title
						if(temp == x) {
							add = false;
							break;
						}
					}

					// Add to the tokenized_title if add is true
					if (add)
						tokenized_title.push_back(temp);
				}

				else {
					// For the first word in title add it to the tokenized_title
					tokenized_title.push_back(temp);
				}

			}
		}

		void token_concatenator() {
			// Makes sure that attributes that are "alone" are appended to the previous value
			for(int i = 0; i < tokenized_title.size(); i++) {
				for(string attribute : attributes) {
					if(tokenized_title[i] == attribute) {
						tokenized_title[i - 1].append(attribute);
						tokenized_title.erase(tokenized_title.begin() + i);
					}
				}
			}
		}

		void generate_token_objects() {
			// For every string token in the tokenized_title, send it to add and put the return value in Tokens
			for (string token_value : tokenized_title) {
				Tokens.push_back(add_token(token_value));
				// CURRENT ISSUE: The pointer does return the correct values.
			}
		}

		void execute() {
			// Runs the necessary functions to generate tokens and correctly format them according to UPM 
			generate_tokens();
			token_concatenator();
			generate_token_objects();
		}
};

Token* add_token(string token_value) {
	// TODO: Use Hash Map instead of vector to store tokens
	Token token(token_value);
	
	for (int i = 0; i < token_hashes.size(); i++) {
		if (token_hashes[i] == token.id) {
			all_tokens[i].frequency++;
			return &all_tokens[i];
		}
	}

	token.frequency++;
	token_hashes.push_back(token.id);
	Token* ptr = all_tokens.data();
	all_tokens.push_back(token);
	ptr++;
	return &all_tokens[all_tokens.size() - 1];
}

int main() {
	all_tokens.reserve(500);
	Product amazon("Amazon", "ASUS VivoBook F510UA 15.6 Full HD Nanoedge Laptop, Intel Core i5-8250U Processor, 8 GB DDR4 RAM, 1 TB HDD, USB-C, Fingerprint, Windows 10 Home - F510UA-AH51, Star Gray");
	Product newegg("Newegg", "ASUS VivoBook F510UA-AH55 Laptop Notebook Thin and Lightweight FHD WideView Laptop, 8th Gen Intel Core i5-8250U, 8GB DDR4 RAM, 128GB SSD+1TB HDD, USB Type-C, ASUS NanoEdge Display, Fingerprint Reader,");
	amazon.execute();
	newegg.execute();
	return 1;
}
