"""
Created by Jason Acheampong
* UPM = Unsupervised Product Matching (Using Combinations and Permutations)
* UPM[x] = Unsupervised Product Matching Page X
"""

""" Local Imports """
from Token import Token
from itertools import combinations
import time
class Product():
    tokens_lexicon = []
    combinations_lexicon = []
    def __init__(self, retailer, title):
        self.retailer = retailer
        self.title = title

        # Essentially each word in a product's title
        self.tokens = []

        # List of Token Objects
        self.Token_Objects = []
        
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

        # Measurement lexicon for determining if token is a unit of measurement
        self.attribute_lexicon = ["bytes", "hz", "bps", "meters", "m", "gb", "mb", "tb", "kb", "km", "kilometers", '"', '”', "'"]

        # For this part of organizing data, if we already have the item model, then we can just search the
        self.semantics_list = []
        self.semantics_lexicon = {}

        # Going to have each combination and then a list of the attributes for each combination
        # Each combination should have its signature, frequency of the combination, and the distance accumulator 
        self.combinations = []

        # Punctuations to get rid of
        self.punctuations = ";:]}[{|}]()`~&!@#$%^*"
        self.execute()

    # Needed step as defined on UPM[4]
    # Aids in helping the similarity equations to be more accurate
    def puncuation_removal(self, word):
        word_list = list(word)
        for index, char in enumerate(word_list):
            if char in self.punctuations:
                del(word_list[index])
        return "".join(word_list)

    # Just appends each individual word to the list of tokens from the title. UPM[4]
    def generate_tokens(self):
        self.tokens = self.title.lower().split(" ")
        for index, token in enumerate(self.tokens):
            if token in self.punctuations + "_-":
                del(self.tokens[index])
        self.token_concatenater()

    # Combines tokens that are part of the attribute to get better results in the similitary formula
    def token_concatenater(self):
        for index, token in enumerate(self.tokens):
            if token in self.attribute_lexicon:
                self.tokens[index - 1:index + 1] = ["".join(self.tokens[index - 1:index + 1])]

    # Used to determine whether or not a token is classified as an item_model
    def item_model_identifier(self, token, item_model = None):
        if item_model is None:
            if self.attribute_identifier(token):
                return False

            if token.isdigit():
                return True
            else:
                digit_counter = 0
                for x in token:
                    try:
                        digit_counter += int(x)
                    except:
                        pass
                if digit_counter > 0:
                    return True
                
                else:
                    return False

    # Used to determine whether or not
    def attribute_identifier(self, token):
        for attribute in self.attribute_lexicon:
            if attribute in token:
                return True
        return False

    # Semantics are used to add weights to each individual token. UPM[4]
    def semantics(self):
        item_model_counter = 1
        for index, token in enumerate(self.tokens):
            self.semantics_list.append("")
            if self.attribute_identifier(token):
                self.semantics_list[index] = "A"
            
            elif self.item_model_identifier(token):
                self.semantics_list[index] = "I" + str(item_model_counter)
                item_model_counter += 1
            
            else:
                self.semantics_list[index] = "N"

        self.semantics_lexicon = dict(zip(self.tokens, self.semantics_list))

    # Generate token objects based on the semantics_lexicon
    def token_object_generater(self):
        for key, value in self.semantics_lexicon.items():
            id = 0
            if len(Token.total_tokens) > 0:
                id = Token.total_tokens[len(Token.total_tokens) - 1].id + 1
            token = Token(key, id, value)
            result = token.add()
            self.Token_Objects.append(result)

    # Generates a unique signature for a combination
    def combination_signature_generater(self):
        pass

    # Generate all the possible combinations of the token lexicon from 2 to 5
    def combinations_generator(self, lexicon):
        length = len(lexicon)
        combinations_lexicon = []
        for x in range(length):
            if x < 6:
                for combination in combinations(lexicon, x + 1):
                    combinations_lexicon.append(combination)
        return combinations_lexicon

    # Executes all of the necessary methods in order to generate the semantics and the necessary data types for the product
    def execute(self):
        self.title = self.puncuation_removal(self.title)
        self.generate_tokens()
        self.semantics()
        self.token_object_generater()
        self.combinations = self.combinations_generator(self.tokens)

time1 = time.time()
product = Product("Amazon", "ASUS VivoBook F510UA 15.6” Full HD Nanoedge Laptop, Intel Core i5-8250U Processor, 8 GB DDR4 RAM, 1 TB HDD, USB-C, Fingerprint, Windows 10 Home - F510UA-AH51, Star Gray")
product2 = Product("Newegg", "ASUS VivoBook F510UA-AH55 Laptop Notebook Thin and Lightweight FHD WideView Laptop, 8th Gen Intel Core i5-8250U, 8GB DDR4 RAM, 128GB SSD+1TB HDD, USB Type-C, ASUS NanoEdge Display, Fingerprint Reader,")
product3 = Product("Newegg", "ASUS VivoBook Ultrabook: Core i5-7200U, 8GB RAM, 1TB HDD, 15.6” Full HD, Windows 10")
product4 = Product("Newegg", "2018 ASUS VivoBook F510UA Full HD Ultra-Narrow Laptop | Intel Core i5-8250U | 8GB RAM | 1TB HDD | USB-C | NanoEdge anti-glare Display | Fingerprint | HDMI | Windows 10 | Star Gray")
product5 = Product("Newegg", "ASUS VivoBook F510UA Thin and Lightweight FHD WideView Laptop, 8th Gen Intel Core i5-8250U, 8GB DDR4 RAM, 128GB SSD+1TB HDD, USB Type-C, ASUS NanoEdge Display, Fingerprint Reader, Windows 10")
product6 = Product("Newegg", "ASUS VivoBook F510UA Thin and Lightweight FHD WideView Laptop, 8th Gen Intel ...")
print(time.time() - time1)
print(product.Token_Objects)
print(product2.Token_Objects)
