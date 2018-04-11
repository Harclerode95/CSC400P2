# CSC400P2
Programming Assignment 2 - CSC400 Operating Systems

Notes:

Project Description: Start from this given sample that implements the random replacement strategy, implement the other three strategies First In First Out (FIFO), Least Recently Used (LRU), and Least Frequently Used (LFU) to simulate the OS page replacements using each strategy for a particular page-reference sequence (It is OK to have three separate source files, each for one strategy). Your assignments:


1) Read page-reference from a given file (Each line of the file contains a page reference sequence, page ID is A-Z). So if your compiled program is named replacement, one way to run your program is replacement   pagereference.txt and your program will read the page-reference sequences from the file reference sequences, which contains three patterns: random, locality, and sequential with loop. Each line is a pattern, consisting of 1000 page references. 

Recommendation: Please use the small sequence for testing your program. When you think your program is correct, run the final sequences for submission. 
 
2) For each pattern sequence, i.e., each line in reference sequences,
  - Print out the page ID (e.g., A, B, ... Z) that has a page miss.
  - Calculate the page fault rate 
 
***Note: If you choose to have three separate .c files for the three strategies: FIFO, LRU & LFU, then each file will print missed page IDs and calculate the page fault rate for each pattern, e.g.,***


Assume that the OS maximmally will allocate 10 page frames to each page-reference sequence, i.e., #PFRAME=10. Before you run your program on the provided sequence files, try your own examples with a small sequence to verify whether your strategy works correctly. You might also want to reduce the page frame to a smaller number (e.g., 5) for testing. See this page for testing.

To run the sample random.c, type gcc random.c, and then ./a.out . 



**For testing: ** http://students.calu.edu/calupa/chen/csc400/pa2/testing.html



**Programming Guidelines:

The following are some points to keep in mind for this and other projects for this course (if not for the rest of your coding career).

All source code files must have a "program header comment" including your name, email address, course number and name, program title, date, compilation instructions and an overall description of the file.
All code submitted as your work must be originally written by you, except that you may use and modify any sample given in class or from the text as long as you include proper credit for the source.
Your program should be well modularized into small (<50 lines), well-defined functions.
main() should be like the executive of a company - it should only call other functions to do the work instead of doing the work itself.
Each function should be preceded by a comment describing what it does and any special I/O parameter considerations (side effects, etc).
Return values from all system & library calls should be checked and have suitable error handling. Neglecting to do this is an open invitation for trouble, which I typically find.
You need not comment every line; however, you should use in-line comments for any complicated code or unusual conditions and non-obvious variable effects.
Functions and variables should have meaningful names, but single letter variables (like i) for loop counters and local temporaries are OK.
Minimize the number of global variables.
Do not use gotos - negative points will be awarded for use of goto.  :-)


**Scoring rubric:

http://students.calu.edu/calupa/chen/csc400/pa2/rubricpa2.html


FIFO: replace page that has been in the system the longest
LRU:  replace the page that has spent the longest time in mem w/0 being referenced
LFU:  replace the least intensively referenced page

**LRU & LFU use intuition
