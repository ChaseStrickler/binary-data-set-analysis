# binary-data-set-analysis

This program reads a .txt file data set of size 100 x 100. Each element in the data set is either a 0 or 1. 

The program first reduces the data set down to a 10x10 matrix based on if a column meets the specific threshold, in this case, five. 

After this, it finds, and prints, the maximal sets within the matrix, and keeps track of how many total maximal sets exist.

I was in charge of input and output as well as reducing the matrix down to a 10x10 based on the threshold. Looking back, I should have created functions for the input, output, and reduction instead of write all of it in the main function.

There are quite a few structural flaws and the code isn't well documented. I may go back and clean up the code and make it expandable for different inputs, however I will likely move on to other projects instead.
