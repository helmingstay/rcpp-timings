# RCPP Timings

This repo contains timing comparisons between the three ways to call C/C++ code from R. 1) using the .C interface, 2) using the .Call interface, and 3) using Rcpp.

The folders diff and nodiff contain, for all three approaches, methods to compute the minimal distance (sum of squares) between the columns of a data matrix, and the columns of a codebook vector. The difference between the code in the diff folder and the nodiff folder is that in the diff folder, a ISNAN check on the data check is included.

## About the code
In each subfolder, the glue.R file compiles the C/C++ codes, runs the comparison script, and produces two graphics: benchmark.png and timings.png. The former prints the microbenchmark results for a single data/code configuration of 10000 data objects, 100 codebook vectors, and 50 vars per object. The latter shows the timings for different numbers of objects in the data matrix.
