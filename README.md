# C Programming Assignment 1

_data structures and pointers in the C language_

### Contributors
- Teo Price-Broncucia
- Aaron Roberts
* * * 

## I/O
The input file is retrieved based off of a provided command line argument and is read word by word into a buffer, from which the binary tree is built. The output file generates its name based on the input file's name and is written to line-by-line during the tree traversal function.

## Data structures - Unbalanced Binary Tree
The key data structure used in this project is an unbalanced binary tree. It's made up of nodes which contain pointers to the parent and child nodes, the word (i.e. the node's value), and the number of times that word occurred in the input file.
The memory for the word values of the nodes is dynamically allocated. Additionally, the memory for the node structure itself is dynamically allocated. This memory is freed recursively later by the destroyTree function.

### Building the binary tree
This is done by recursively checking which case a new word falls into, starting at the root node:
1. The new word is equal: the count of the current node is incremented
2. The new word is lesser: the function is called recursively on the left child
3. The new word is greater: the function is called recursively on the right child

Assuming case 2 or 3, memory for a new node is allocated and initialized.

### Traversing the binary tree
This is a simple in-order traversal function, though it does also take in a pointer to a filestream to incrementally write the results line by line.
