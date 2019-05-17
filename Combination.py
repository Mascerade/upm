"""
Created by Jason Acheampong
* UPM = Unsupervised Product Matching (Using Combinations and Permutations)
* UPM[x] = Unsupervised Product Matching Page X
"""
from collections import Counter

class Combination():
    total_combinations = []
    def __init__(self, combination_id, value):
        self.frequency = 0
        self.value = value
        self.id = combination_id

    def check(self):
        # Checks if a combination is already in the total_combinations list
        for combination in Combination.total_combinations:
            if Counter(combination.value) == Counter(self.value):
                return combination.id 

        # -1 represents if the combination was not found
        return -1

    # Adds a combination that hasn't been seen before to the total_combinations list. Also, adds to the frequency of the combination
    def add(self):
        result = self.check()

        # If the combination is not found, append the combination to the combinations list
        if result == -1:
            Combination.total_combinations.append(self)
            
            # Return the combination itself if it hasn't been encountered
            return self

        else:
            # If the combination exists, add to the combination's frequency and return that combination
            Combination.total_combinations[result].frequency += 1
            return Combination.total_combinations[result]
