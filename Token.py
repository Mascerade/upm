"""
Created by Jason Acheampong
* UPM = Unsupervised Product Matching (Using Combinations and Permutations)
* UPM[x] = Unsupervised Product Matching Page X
"""

class Token():
    total_tokens = []
    def __init__(self, value, token_id, semantic):
        self.frequency = 0
        self.value = value
        self.id = token_id
        self.semantic = semantic
        
    
    def check(self):
        for token in Token.total_tokens:
            if self.value != token.value:
                continue
            else:
                return token.id
        return -1

    def add(self):
        result = self.check()
        if result == -1:
            Token.total_tokens.append(self)
            return self.id
        else:
            return result
