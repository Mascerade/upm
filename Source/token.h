#include <string>
using namespace std;

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
		this->define_semantic();
		frequency = 0;
	}

	void define_semantic();

	int get_id() {
		return Token::id;
	};
};
