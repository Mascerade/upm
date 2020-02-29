# Unsupervised Product Matching Using Combinations and Permutations

A product matching algorithm that groups products into clusters of similarity based on their title using combinations and permutations.

Based on the paper "Unsupervised Product Matching Using Combinations and Permutations" by Leonidas Akritidis, Athanasios Fevgas, Panayiotis Bozanis and Christos Makris
https://arxiv.org/pdf/1903.04276.pdf

# Structure of Project
`bin` - Contains the executables <br>
`build` - Contains the object files (`.o`) <br>
`include` - Contains the header files <br>
`src` - Contains the C++ code <br>
`build.bat` - Builds the project and creates the `main.exe` file in `bin` **(for Windows)** <br>
`build.sh` - Builds the project and creates the `main.exe` file in `bin` **(for Ubuntu)** <br>
\* Change the directory to the build directory `build.bat` or `build.sh` for your system


# How to Use

Simply create a Product object that takes the vendor (the retailer to which the product is associated). The vendor parameter is a **string**. The next parameter is the title of the product, which is also a **string**. See `main.cpp` to see the test code.

# How it Works

For each product, all of the combinations of the tokens (words) of the title are created up to n choose 6. Each token has its own properties, like its frequency and semantic value (item model, attribute or normal token) and based on this, they get different weights. The combinations also have their own properties, such as their Euclidean distance average and the frequency of the combination among the products. From this, using the equations outlined in the paper, each product is assigned a "dominating cluster", that is the combination that best represents what the product is. The products with the same cluster represent the same product.

# Uses

This algorithm aims to solve the issue of how to deal with discrepincies among products across different retailers. Using this algorithm, it should be able identify the correct matching product among a wide range of products.

# Reality

In contrast to the aim of this algorithm, it doesn't actually do its job. For example, running the algorithm on the set of data provided by the authors, it is very inaccurate, and it is not my implementation. I acheived similar, if not identical results using the author's algorithm, which can be found at https://github.com/lakritidis/UPM-full
