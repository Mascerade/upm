"""
Created by Jason Acheampong
* UPM = Unsupervised Product Matching (Using Combinations and Permutations)
* UPM[x] = Unsupervised Product Matching Page X
"""

class Token():
    total_tokens = []
    def __init__(self, token, token_id, semantic):
        self.frequency = 0
        self.token = token
        self.id = token_id
        self.semantic = semantic
        
    
    def check(self):
        print(Token.total_tokens)
        for token in Token.total_tokens:
            if self.token != token.token:
                continue
            else:
                return True
        return False

    def add(self):
        if self.check() == False:
            Token.total_tokens.append(self)
            return True
        else:
            return False

token = Token("hello", 2, "A")
print(token.add())
print(Token.total_tokens)