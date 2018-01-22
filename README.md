# C Programming Assignment 1

_data structures and pointers in the C language_

### Contributors
- Teo Price-Broncucia
- Aaron Roberts
* * * 
## I/O
The input file is read word by word into a buffer, from which the binary tree is built. The output file is written to by way of appending the file; this is performed at the end of the recursive in-order tree traversal function.

## Data structures - Unbalanced Binary Tree
The key data structure used in this project is an unbalanced binary tree. It's made up of nodes which contain pointers to the parent and child nodes, the word (i.e. the node's value), and the number of times that word occurred in the input file.
The memory for the word values of the nodes is dynamically allocated. Additionally, the memory for the node structure itself is dynamically allocated. This memory is freed recursively later by the destroyTree function.

### Building the binary tree
TODO