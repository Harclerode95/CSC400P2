# CSC400P2
Programming Assignment 2 - CSC400 Operating Systems

Notes:

1) Read page-reference from a given file (Each line of the file contains a page reference sequence, page ID is A-Z). So if your compiled program is named replacement, one way to run your program is replacement   pagereference.txt and your program will read the page-reference sequences from the file reference sequences, which contains three patterns: random, locality, and sequential with loop. Each line is a pattern, consisting of 1000 page references. 

Recommendation: Please use the small sequence for testing your program. When you think your program is correct, run the final sequences for submission. 
 
2) For each pattern sequence, i.e., each line in reference sequences,
  - Print out the page ID (e.g., A, B, ... Z) that has a page miss.
  - Calculate the page fault rate 
 
***Note: If you choose to have three separate .c files for the three strategies: FIFO, LRU & LFU, then each file will print missed page IDs and calculate the page fault rate for each pattern, e.g.,***


Assume that the OS maximmally will allocate 10 page frames to each page-reference sequence, i.e., #PFRAME=10. Before you run your program on the provided sequence files, try your own examples with a small sequence to verify whether your strategy works correctly. You might also want to reduce the page frame to a smaller number (e.g., 5) for testing. See this page for testing.

To run the sample random.c, type gcc random.c, and then ./a.out . 
