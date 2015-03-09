# Comparing Trees
Using and comparing performance of a basic BST with an AVL tree, as well as lazy vs. non-lazy deletion for AVL trees

**Date Created:** February 21, 2015

**Last Modified:** March 9, 2015

## Compiling the Program
While in the working directory, type into terminal

- `make`: to compile both programs
- `make queryTrees`: to make only the queryTrees program
- `make testTrees`: to make only the testTrees program


## Running the program
To run the queryTrees program, while in the working directory, type into the
terminal: 
> `./queryTrees <database file name> <flag>`

To run the testTrees program, while in the working directory, type into the
terminal: 
> `./testTrees <database file name> <queries file name> <flag>`

`<flag>`should be “BST” for binary search tree, “AVL” for AVL tree, and
“LazyAVL” for AVL with lazy deletion.

Flag name is case insensitive but file names/paths are case sensitive.