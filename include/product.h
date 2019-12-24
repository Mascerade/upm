#include "token.h"
#include "combination.h"
#include <unordered_map>

class Product {

	public:

		// The retailer
		string vendor;

        // Title of the product
		string title;
		
		// The tokenized title
		vector<string> tokenized_title;
		
		// Object Token pointers
		vector<Token*> Tokens;

		// Hash Map of Tokens for Easy Lookup
		unordered_map<int, Token*> token_map;

		// Combinations
		vector<Combination*> Combinations;

		// The highest scoring Combination's hash
		int high_combo_hash;

		// The highest scoring Combination
		Combination *high_combo;

		// Highest score
		double high_score = -1.0;

        // Constructor for Product
    	Product(string vendor, string title);

        void preparation();

        void execute();

        void generate_tokens();

        void token_concatenator();

        void generate_token_objects();

        Token* add_token(string token_value);

        void generate_token_map();

        void generate_combinations(int k);

		Combination* add_combination(int hash, Combination* combo, double distance);

        double yc(Combination* c);

        void display();

        void cluster_creation();
};