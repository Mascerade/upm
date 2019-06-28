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
#include <unordered_map>
#include <chrono>
using namespace std;

long long int factorial(int);
long long int n_combinations(int, int);

class Token;
class Combination;
Token* add_token(string);
static const string attributes[] = {"bytes", "hz", "bps", "meters","gb", "mb", "tb", "kb", "km", "kilometers", "\"", "'"};
static const string punctuations = ",;:]}[{|}]()`~&!@#$%^*";

vector<int> token_hashes;
vector<Token> all_tokens;
vector<Combination> all_combinations;


class Combination {
	// Stores the attributes that a combination has according to UPM[4 - 5]
	public:
		int id; // The hash of the combination
		int frequency; // The amount of times the combination occurs throughout all the product titles
		vector<Token*> tokens; // The vecotr of Tokens that the combination contains
		int dacc; 

		Combination(vector<Token*> vec) {
			tokens = vec;
			frequency = 1;
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
		this->define_semantic();
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

	int get_id() {
		return this->id;
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

		// Hash Map of Tokens for Easy Lookup
		unordered_map<int, Token*> token_map;

		// Combinations
		vector<Combination> Combinations;

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
			int added = 0;
			// Goes through each token and gets rid of the punctuation from the token
			while (getline(check1, temp, ' ') && added < 100) {
				added++;
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
			}

			while (Tokens.size() > 20) {
				for (int i = Tokens.size() - 1; i >= 0; i--) {
					if (Tokens[i]->semantic == 'N') {
						Tokens.erase(Tokens.begin() + i);
						break;
					}
				}
			}
		}

		Token* add_token(string token_value) {
			// TODO: Use Hash Map instead of vector to store tokens
			Token token(token_value);
			// If the token is already found in the vector of Tokens, increase the freqency and return the token to be added into the Tokens vector of the product
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

		void generate_token_map() {
			// Generates the Token hash map (called token_map)
			for (int i = 0; i < Tokens.size(); i++) {
				token_map.insert({i, Tokens[i]});
			}
		}

		void generate_combinations(int k) {
			// Generates up to x choose 7 combinations
			hash<string> str_hash;
			int comb_id;
			int num_tokens = Tokens.size();
			if (k >= 3) {
				vector<Token*> toks(3);
				string sorted_sig = "";
				sorted_sig.reserve(5);
				for (int i = 0; i < num_tokens; i++) {
					for (int j = i + 1; j < num_tokens; j++) {
						for (int l = j + 1; l < num_tokens; l++) {
							toks[0] = Tokens[i];
							toks[1] = Tokens[j];
							toks[2] = Tokens[l];
							sort(toks.begin(), toks.end());

							sorted_sig = "";
							sorted_sig += toks[0]->get_id();
							sorted_sig += " ";
							sorted_sig += toks[1]->get_id();
							sorted_sig += " ";
							sorted_sig += toks[2]->get_id();

							comb_id = str_hash(sorted_sig);
							Combination comb(toks);
							Combinations.push_back(comb);
						}
					}
				}
			}

			if (k >= 4) {
				vector<Token*> toks(4);
				string sorted_sig = "";
				sorted_sig.reserve(7);

				for (int i = 0; i < num_tokens; i++) {
					for (int j = i + 1; j < num_tokens; j++) {
						for (int l = j + 1; l < num_tokens; l++) {
							for (int m = l + 1; m < num_tokens; m++) {
								toks[0] = Tokens[i];
								toks[1] = Tokens[j];
								toks[2] = Tokens[l];
								toks[3] = Tokens[m];
								sort(toks.begin(), toks.end());

								sorted_sig = "";
								sorted_sig += toks[0]->get_id();
								sorted_sig += " ";
								sorted_sig += toks[1]->get_id();
								sorted_sig += " ";
								sorted_sig += toks[2]->get_id();
								sorted_sig += " ";
								sorted_sig += toks[3]->get_id();

								comb_id = str_hash(sorted_sig);
								Combination comb(toks);
								Combinations.push_back(comb);
							}
						}
					}
				}
			}

			if (k >= 5) {
				vector<Token*> toks(5);
				string sorted_sig = "";
				sorted_sig.reserve(9);
				for (int i = 0; i < num_tokens; i++) {
					for (int j = i + 1; j < num_tokens; j++) {
						for (int l = j + 1; l < num_tokens; l++) {
							for (int m = l + 1; m < num_tokens; m++) {
								for (int n = m + 1; n < num_tokens; n++) {
									toks[0] = Tokens[i];
									toks[1] = Tokens[j];
									toks[2] = Tokens[l];
									toks[3] = Tokens[m];
									toks[4] = Tokens[n];

									sort(toks.begin(), toks.end());
									
									sorted_sig = "";
									sorted_sig += toks[0]->get_id();
									sorted_sig += " ";
									sorted_sig += toks[1]->get_id();
									sorted_sig += " ";
									sorted_sig += toks[2]->get_id();
									sorted_sig += " ";
									sorted_sig += toks[3]->get_id();
									sorted_sig += " ";
									sorted_sig += toks[4]->get_id();

									comb_id = str_hash(sorted_sig);
									Combination comb(toks);
									Combinations.push_back(comb);
								}
							}
						}
					}
				}
			}

			if (k >= 6) {
				vector<Token*> toks(6);
				string sorted_sig = "";
				sorted_sig.reserve(11);
				for (int i = 0; i < num_tokens; i++) {
					for (int j = i + 1; j < num_tokens; j++) {
						for (int l = j + 1; l < num_tokens; l++) {
							for (int m = l + 1; m < num_tokens; m++) {
								for (int n = m + 1; n < num_tokens; n++) {
									for (int o = n + 1; o < num_tokens; o++) {
										toks[0] = Tokens[i];
										toks[1] = Tokens[j];
										toks[2] = Tokens[l];
										toks[3] = Tokens[m];
										toks[4] = Tokens[n];
										toks[5] = Tokens[o];

										sort(toks.begin(), toks.end());

										sorted_sig = "";
										sorted_sig += toks[0]->get_id();
										sorted_sig += " ";
										sorted_sig += toks[1]->get_id();
										sorted_sig += " ";
										sorted_sig += toks[2]->get_id();
										sorted_sig += " ";
										sorted_sig += toks[3]->get_id();
										sorted_sig += " ";
										sorted_sig += toks[4]->get_id();
										sorted_sig += " ";
										sorted_sig += toks[5]->get_id();

										comb_id = str_hash(sorted_sig);
										Combination comb(toks);
										Combinations.push_back(comb);
									}
								}
							}
						}
					}
				}
			}

			if (k >= 7) {
				vector<Token*> toks(7);
				string sorted_sig = "";
				sorted_sig.reserve(13);
				for (int i = 0; i < num_tokens; i++) {
					for (int j = i + 1; j < num_tokens; j++) {
						for (int l = j + 1; l < num_tokens; l++) {
							for (int m = l + 1; m < num_tokens; m++) {
								for (int n = m + 1; n < num_tokens; n++) {
									for (int o = n + 1; o < num_tokens; o++) {
										for (int p = o + 1; p < num_tokens; p++) {
											vector<Token*> toks;
											toks[0] = Tokens[i];
											toks[1] = Tokens[j];
											toks[2] = Tokens[l];
											toks[3] = Tokens[m];
											toks[4] = Tokens[n];
											toks[5] = Tokens[o];
											toks[6] = Tokens[p];

											sort(toks.begin(), toks.end());

											sorted_sig = "";
											sorted_sig += toks[0]->get_id();
											sorted_sig += " ";
											sorted_sig += toks[1]->get_id();
											sorted_sig += " ";
											sorted_sig += toks[2]->get_id();
											sorted_sig += " ";
											sorted_sig += toks[3]->get_id();
											sorted_sig += " ";
											sorted_sig += toks[4]->get_id();
											sorted_sig += " ";
											sorted_sig += toks[5]->get_id();
											sorted_sig += " ";
											sorted_sig += toks[6]->get_id();

											comb_id = str_hash(sorted_sig);
											Combination comb(toks);
											Combinations.push_back(comb);
										}
									}
								}
							}
						}
					}
				}
			}
		}

		void execute() {
			// Runs the necessary functions to generate tokens and correctly format them according to UPM 
			generate_tokens();
			token_concatenator();
			generate_token_objects();
			generate_token_map();
			generate_combinations(6);
		}
};

long long int factorial(int num) {
	// Takes a number and return !num
	long long int number = 1;
	for (int x = num; x > 0; x--) {
		number *= num;
	}
	return number;
}

long long int n_combinations(int n, int r) {
	// Returns nCr
	return factorial(n) / (factorial(r) * factorial(n - r));
}



int main() {
	// Reserving 500 "spots" of memory so that it doesn't change the position of the values for 500 values
	auto start = chrono::high_resolution_clock::now();
	all_tokens.reserve(500);
	Product amazon("Amazon", "ASUS VivoBook F510UA 15.6 Full HD Nanoedge Laptop, Intel Core i5-8250U Processor, 8 GB DDR4 RAM, 1 TB HDD, USB-C, Fingerprint, Windows 10 Home - F510UA-AH51, Star Gray");
	Product newegg("Newegg", "ASUS VivoBook F510UA-AH55 Laptop Notebook Thin and Lightweight FHD WideView Laptop, 8th Gen Intel Core i5-8250U, 8GB DDR4 RAM, 128GB SSD+1TB HDD, USB Type-C, ASUS NanoEdge Display, Fingerprint Reader,");
	Product newegg2("Newegg", "ASUS VivoBook F510UA-AH55 Laptop Notebook Thin and Lightweight FHD WideView Laptop, 8th Gen Intel Core i5-8250U, 8GB DDR4 RAM, 128GB SSD+1TB HDD, USB Type-C, ASUS NanoEdge Display, Fingerprint Reader,");
	Product newegg3("Newegg", "ASUS VivoBook F510UA-AH55 Laptop Notebook Thin and Lightweight FHD WideView Laptop, 8th Gen Intel Core i5-8250U, 8GB DDR4 RAM, 128GB SSD+1TB HDD, USB Type-C, ASUS NanoEdge Display, Fingerprint Reader,");
	Product newegg4("Newegg", "ASUS VivoBook F510UA-AH55 Laptop Notebook Thin and Lightweight FHD WideView Laptop, 8th Gen Intel Core i5-8250U, 8GB DDR4 RAM, 128GB SSD+1TB HDD, USB Type-C, ASUS NanoEdge Display, Fingerprint Reader,");
	Product newegg5("Newegg", "ASUS VivoBook F510UA-AH55 Laptop Notebook Thin and Lightweight FHD WideView Laptop, 8th Gen Intel Core i5-8250U, 8GB DDR4 RAM, 128GB SSD+1TB HDD, USB Type-C, ASUS NanoEdge Display, Fingerprint Reader,");
	Product newegg6("Newegg", "ASUS VivoBook F510UA-AH55 Laptop Notebook Thin and Lightweight FHD WideView Laptop, 8th Gen Intel Core i5-8250U, 8GB DDR4 RAM, 128GB SSD+1TB HDD, USB Type-C, ASUS NanoEdge Display, Fingerprint Reader,");
	Product newegg7("Newegg", "ASUS VivoBook F510UA-AH55 Laptop Notebook Thin and Lightweight FHD WideView Laptop, 8th Gen Intel Core i5-8250U, 8GB DDR4 RAM, 128GB SSD+1TB HDD, USB Type-C, ASUS NanoEdge Display, Fingerprint Reader,");
	Product newegg8("Newegg", "ASUS VivoBook F510UA-AH55 Laptop Notebook Thin and Lightweight FHD WideView Laptop, 8th Gen Intel Core i5-8250U, 8GB DDR4 RAM, 128GB SSD+1TB HDD, USB Type-C, ASUS NanoEdge Display, Fingerprint Reader,");
	Product newegg9("Newegg", "ASUS VivoBook F510UA-AH55 Laptop Notebook Thin and Lightweight FHD WideView Laptop, 8th Gen Intel Core i5-8250U, 8GB DDR4 RAM, 128GB SSD+1TB HDD, USB Type-C, ASUS NanoEdge Display, Fingerprint Reader,");
	Product newegg10("Newegg", "ASUS VivoBook F510UA-AH55 Laptop Notebook Thin and Lightweight FHD WideView Laptop, 8th Gen Intel Core i5-8250U, 8GB DDR4 RAM, 128GB SSD+1TB HDD, USB Type-C, ASUS NanoEdge Display, Fingerprint Reader,");
	Product newegg11("Newegg", "ASUS VivoBook F510UA-AH55 Laptop Notebook Thin and Lightweight FHD WideView Laptop, 8th Gen Intel Core i5-8250U, 8GB DDR4 RAM, 128GB SSD+1TB HDD, USB Type-C, ASUS NanoEdge Display, Fingerprint Reader,");
	Product newegg12("Newegg", "ASUS VivoBook F510UA-AH55 Laptop Notebook Thin and Lightweight FHD WideView Laptop, 8th Gen Intel Core i5-8250U, 8GB DDR4 RAM, 128GB SSD+1TB HDD, USB Type-C, ASUS NanoEdge Display, Fingerprint Reader,");
	Product newegg13("Newegg", "ASUS VivoBook F510UA-AH55 Laptop Notebook Thin and Lightweight FHD WideView Laptop, 8th Gen Intel Core i5-8250U, 8GB DDR4 RAM, 128GB SSD+1TB HDD, USB Type-C, ASUS NanoEdge Display, Fingerprint Reader,");
	Product newegg14("Newegg", "ASUS VivoBook F510UA-AH55 Laptop Notebook Thin and Lightweight FHD WideView Laptop, 8th Gen Intel Core i5-8250U, 8GB DDR4 RAM, 128GB SSD+1TB HDD, USB Type-C, ASUS NanoEdge Display, Fingerprint Reader,");

	amazon.execute();
	newegg.execute();
	newegg2.execute();
	newegg3.execute();
	newegg4.execute();
	newegg5.execute();
	newegg6.execute();
	newegg7.execute();
	newegg8.execute();
	newegg9.execute();
	newegg10.execute();
	newegg11.execute();
	newegg12.execute();
	newegg13.execute();
	newegg14.execute();
	auto stop = chrono::high_resolution_clock::now();
	auto duration = chrono::duration_cast<chrono::milliseconds>(stop - start);
	cout << duration.count() << endl;
	return 1;
}
