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
#include <math.h>
#include "common.h"
#include "token.h"
#include "combination.h"
#include "product.h"

using namespace std;


int main() {
	// Reserving 500 "spots" of memory so that it doesn't change the position of the values for 500 values
	auto start = chrono::high_resolution_clock::now();
	Common::all_tokens.reserve(500);

	// 920000 is a function of the max number of combos for each product * the number of products
	Common::all_combinations.reserve(920000);

	Product amazon("Amazon", "LG Electronics OLED65C8P 65-Inch 4K Ultra HD Smart OLED TV (2018 Model)");
	Product newegg("Newegg", "LG C8 65\" OLED 4K HDR Dolby Atmos Smart TV with AI ThinQ OLED65C8PUA");
	Product walmart("Walmart", "Recertified LG 65\" Class OLED C8 Series 4K (2160P) HDR Smart TV w/AI ThinQ - (OLED65C8PUA)");
	Product bh("B&H", "LG C9PUA 65\" Class HDR 4K UHD Smart OLED TV");
	Product ebay1("Ebay", "LG OLED65C8P 65\" HDR UHD Smart OLED TV");
	Product ebay2("Ebay", "LG OLED65C8P 65\" 2018 OLED 4K UHD HDR Smart TV ThinQ New");

	amazon.execute();
	newegg.execute();
	walmart.execute();
	bh.execute();
	ebay1.execute();
	ebay2.execute();
	// a.execute();
	// c.execute();
	// d.execute();
	for (int i = 0; i < 5; i++) {
		Common::semantics_weights[i] = (double) Common::all_tokens.size() / Common::semantics_distribution[i];
		//cout << semantics_weights[i] << endl;
	}

	Common::lc_avg = (double) Common::lc_avg / Common::Common::all_combinations.size();

	amazon.cluster_creation();
	newegg.cluster_creation();
	walmart.cluster_creation();
	bh.cluster_creation();
	ebay1.cluster_creation();
	ebay2.cluster_creation();
	// a.cluster_creation();
	// c.cluster_creation();
	// d.cluster_creation();

	cout << endl;
	amazon.display();
	newegg.display();
	walmart.display();
	bh.display();
	ebay1.display();
	ebay2.display();
	// a.display();
	// c.display();
	// d.display();

	cout << "__________________" << endl;

	auto stop = chrono::high_resolution_clock::now();
	auto duration = chrono::duration_cast<chrono::milliseconds>(stop - start);
	cout << duration.count() << endl;
	cout << Common::K << endl;
	
	return 1;
}
