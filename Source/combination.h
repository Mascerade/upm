#pragma once

#include "token.h"
#include <vector>

class Combination {
	// Stores the attributes that a combination has according to UPM[4 - 5]
	public:
		int id; // The hash of the combination
		int frequency; // The amount of times the combination occurs throughout all the product titles
		vector<Token*> tokens; // The vecotr of Tokens that the combination contains
		double dacc; 
		double dacc_avg;
		int lc;

		Combination(vector<Token*> vec, int hash, int length_of_combo);
};