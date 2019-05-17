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
        # Checks if a token is already in the total_tokens list
        for token in Token.total_tokens:
            if self.value != token.value:
                continue
            else:
                return token.id

        # -1 represents if the token was not found
        return -1

    # Adds a token that hasn't been seen before to the total_tokens list. Also, adds to the frequency of the tokens
    def add(self):
        result = self.check()

        # If the token is not found, append the token to the total_tokens list
        if result == -1:
            Token.total_tokens.append(self)
            
            # Return the token itself if it hasn't been encountered
            return self

        else:
            # If the token exists, add to the token's frequency and return that token
            Token.total_tokens[result].frequency += 1
            return Token.total_tokens[result]
