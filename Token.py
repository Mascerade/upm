"""
Created by Jason Acheampong
* UPM = Unsupervised Product Matching (Using Combinations and Permutations)
* UPM[x] = Unsupervised Product Matching Page X
"""

class Token():
    def __init__(self, semantic):
        self.frequency = 0
        self.semantic = semantic