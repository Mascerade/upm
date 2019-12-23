#include <token.h>
#include <string.h>
#include <common.h>
using namespace std;

Token::Token(string value) {
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

void Token::define_semantic() {
    #include <vector>
    #include <string>
    #include <algorithm>
    
    // If all of the characters are number, then it most likely represents an item model (UPM[4])
    if (all_of(value.begin(), value.end(), ::isdigit)) {
        
        // Numeric but not attribute
        semantic = 4;
        Common::semantics_distribution[3]++;
        return;
    }

    // If the string has the attribute in it and the character
    // before the attribute is a digit, consider it an attribute (UPM[4])
    for (string attribute : Common::attributes){
        int found = value.find(attribute);
        if (found != value.npos) {
            if (isdigit(value[found - 1])){

                // Token represents an attribute
                semantic = 1;
                Common::semantics_distribution[0]++;
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
            // Mix of characters and numbers, but not an attribute
            if (Common::semantic2 == 0) {
                semantic = 2;
                Common::semantic2++;
                Common::semantics_distribution[1]++;
            }

            else {
                semantic = 3;
                Common::semantics_distribution[2]++;
            }

            return;
        }

    }

    // If it is neither an attribute nor an item model, consider it a normal token (UPM[4])
    semantic = 5;
    Common::semantics_distribution[4]++;
}
