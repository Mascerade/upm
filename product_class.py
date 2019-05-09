"""
Created by Jason Acheampong
* UPM = Unsupervised Product Matching (Using Combinations and Permutations)
"""

class Product():
    def __init__(self, retailer, title):
        self.retailer = retailer
        self.title = title

        # Essentially each word in a product's title
        self.tokens = []
        
        # For each token, have the semantics of the token based on UPM[4]
        """
        Type Semantics Identification Rule/s
        Attribute: (1) Numeric tokens followed by measurement units, or (2) mixed tokens ending in a measure-
        ment unit
        
        Model: The first mixed token in the title which does not represent an attribute
        
        Model: All the rest mixed tokens in the title which do not represent an attribute
         
        Model: A numeric token which is not followed by a measurement unit
        
        Normal: All the other tokens of the title
        """
        # For this part of organizing data, if we already have the item model, then we can just search the

        self.semantics = {}

        # Going to have each combination and then a list of the attributes for each combination
        # Each combination should have its signature, frequency of the combination, and the distance accumulator 
        self.combinations = {}
