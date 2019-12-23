#include"combination.h"
#include "token.h"
#include <vector>
using namespace std;

Combination::Combination(vector<Token*> vec, int hash, int length_of_combo) {
    tokens = vec;
    id = hash;
    frequency = 1;
    lc = length_of_combo;
}
