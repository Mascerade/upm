"""
Created by Jason Acheampong
* UPM = Unsupervised Product Matching (Using Combinations and Permutations)
* UPM[x] = Unsupervised Product Matching Page X
"""
from collections import Counter
from Token import Token
import time


class Combination():
    total_combinations = []
    # For combinations of different lengths. Just made a bunch
    dict_length = [{}, {}, {}, {},{}, {},{}, {},{}, {},{}, {},{}, {},{}, {},{}, {},{}, {}]
    temp_combinations = []

    def __init__(self, combination_id, value):
        self.frequency = 0
        self.value = value
        self.id = combination_id

    def check(self):
        # Checks if a combination is already in the total_combinations list

        # Hash the sorted tuple combination value
        hash_value = self.id
        length = len(self.value)
        if hash_value in Combination.dict_length[length].keys():
            return Combination.dict_length[length][hash_value]

        # -1 represents if the combination was not found
        return -1

    # Adds a combination that hasn't been seen before to the total_combinations list. Also, adds to the frequency of the combination
    def add(self):
        result = self.check()

        # If the combination is not found, append the combination to the combinations list
        if result == -1:
            Combination.total_combinations.append(self)
            Combination.dict_length[len(self.value)][self.id] = self
            # Return the combination itself if it hasn't been encountered
            return self

        else:
            # If the combination exists, add to the combination's frequency and return that combination
            result.frequency += 1
            return result

    @staticmethod
    def add_multiple(combinations_list):
        time1 = time.time()
        for x in combinations_list:
            id = hash(tuple(sorted(x)))
            combination = Combination(id, x)
            result = combination.add()
            Combination.temp_combinations.append(result)
        print(time.time() - time1)
