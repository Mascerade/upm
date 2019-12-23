#include <vector>
#include "token.h"
#include "combination.h"
#include <unordered_map>
using namespace std;


class Common {
    public:
        // The attributes that are used to determine if a specific token is an attribute
        static const string attributes[13];

        static const string useless_tokens[];

        // Punctuation to remove
        static const string punctuations;

        // Maximum allowed tokens for each title
        static int const MAX_TOKENS;

        // All the token hashes
        static vector<int> token_hashes;

        // Stores the token objects without duplicates
        static vector<Token> all_tokens;

        // Stores EVERY SINGLE combination made
        static vector<Combination> all_combinations;

        // Stores all the combinations with their hash as their identifier
        static unordered_map<int, Combination*> combo_hash_map;

        // Total length of titles
        static int lt;

        // Average length of titles
        static double lt_avg;

        // Average length of combinations
        static double lc_avg;

        // Number of products
        static int lprod;

        // Value of K for combinations
        static int K;

        // Array of the distribution of semantics 
        static int semantics_distribution[];

        // Array of the weights of the semantics distribution
        static double semantics_weights[5];

        // Constant a in the algorithm
        static double const A;

        // Constant b in the algorithm
        static double const b;

        // Used to determine which tokens are semantic 2
        static int semantic2;

};
