#include "common.h"

// The attributes that are used to determine if a specific token is an attribute
const string Common::attributes[] = {"bytes", "hz", "bps", "meters","gb", "mb", "tb", "kb", "km", "kilometers", "w", "\"", "'"};

const string Common::useless_tokens[] = {"with", "for", "of", "it"};

// Punctuation to remove
const string Common::punctuations = ",;:]}[{|}]()`~&!@#$%^*";

// Maximum allowed tokens for each title
int const Common::MAX_TOKENS = 20;

// All the token hashes
vector<int> Common::token_hashes;

// Stores the token objects without duplicates
vector<Token> Common::all_tokens;

// Stores EVERY SINGLE combination made
vector<Combination> Common::all_combinations;

// Stores all the combinations with their hash as their identifier
unordered_map<int, Combination*> Common::combo_hash_map;

// Total length of titles
int Common::lt = 0;

// Average length of titles
double Common::lt_avg = 0.0;

// Average length of combinations
double Common::lc_avg = 0.0;

// Number of products
int Common::lprod = 0;

// Value of K for combinations
int Common::K;

// Array of the distribution of semantics 
int Common::semantics_distribution[] = {0, 0, 0, 0, 0};

// Array of the weights of the semantics distribution
double Common::semantics_weights[5];

// Constant a in the algorithm
double const Common::A = 1.0;

// Constant b in the algorithm
double const Common::b = 1.0;

// Used to determine which tokens are semantic 2
int Common::semantic2 = 0;

// Returns the factorial of num (num!)
long long int Common::factorial(int num) {
	// Takes a number and return !num
	long long int number = 1;
	for (int x = num; x > 0; x--) {
		number *= num;
	}
	return number;
}

// Returns the nCr of n and r (the number of combinations between n and r)
long long int Common::n_combinations(int n, int r) {
	// Returns nCr
	return Common::factorial(n) / (Common::factorial(r) * Common::factorial(n - r));
}
