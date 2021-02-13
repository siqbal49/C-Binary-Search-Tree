// ====== this is in bst.c
#include <stdio.h>
#include <stdlib.h>
#include "bst.h"

void insert_node(int * index, BStree bst, Key *key, Data data);
void inorder(int index, BStree bst);
static int new_node(BStree bst, Key *key, Data data);
void free_help(int index, BStree bst);

// Input: ’size’: size of an array
// Output: a pointer of type BStree,
//         i.e. a pointer to an allocated memory of BStree_struct type
// Effect: dynamically allocate memory of type BStree_struct
//         allocate memory for a Node array of size+1 for member tree_nodes
//         allocate memory for an unsigned int array of size+1 for member free_nodes
//         set member size to ’size’;
//         set entry free_nodes[i] to i
//         set member top to 1;
//         set member root to 0;
BStree bstree_ini(int size) {

	// function is explained in the Effect section in the comments above

	BStree_struct * bst = (BStree_struct *) malloc(sizeof(BStree_struct));
	Node * tree_nodes = (Node *) malloc((size+1) * sizeof(Node));
	unsigned int * free_nodes = (unsigned int *) malloc((size+1) * sizeof(unsigned int));
	for (int i=0; i <size; i++)
		free_nodes[i] = i;
	
	bst->free_nodes = free_nodes;
	bst->size = size; 	
	bst->top = 1;
	bst->root = 0;
	bst->tree_nodes = tree_nodes;
	BStree result = bst;
	return result;
	
}

// Input: ’bst’: a binary search tree
//        ’key’: a pointer to Key
//        ’data’: an integer
// Effect: ’data’ with ’key’ is inserted into ’bst’
//         if ’key’ is already in ’bst’, do nothing
void bstree_insert(BStree bst, Key *key, Data data) {
	
	// call recursive function to insert the given data and 
	// key into the binary search tree
	// use the root as the starting index
	insert_node(&bst->root, bst, key, data);
}

// Input:  'index': pointer to an index in the binary search tree array
//	   'bst': a binary search tree	
//	   ’key’: a pointer to Key
//	   ’data’: an integer
// Effect: ’data’ with ’key’ is inserted into ’bst’
//         if ’key’ is already in ’bst’, do nothing
void insert_node(int * index, BStree bst, Key *key, Data data) {
	
	// if the tree is full, then output an error message and exit the function
	if (bst->top == bst->size+1) {
		printf("Error: tree is full. Cannot insert\n");
		return;
	}
	
	// base case of recursive function
	// if at a leaf node, then create a new node with the given data 
	// and insert the new node into the index of the leaf node
	if (*index == 0)
		*index = new_node(bst, key, data);
	
	
	// recursive case of the function
	else {
		// if the key is in the binary search tree, then do nothing
		if (key_comp(bst->tree_nodes[*index].key, key) == 0)
			return;

		// if the current node key is less than the key of the node you want
		// to insert, then go the the right subtree of the current node
		if (key_comp(bst->tree_nodes[*index].key, key) < 0)
			insert_node(&bst->tree_nodes[*index].right, bst, key, data);

		// if the current node key is more than the key of the node you want
		// to insert, then go the the left subtree of the current node
		else if(key_comp(bst->tree_nodes[*index].key, key) > 0)
			insert_node(&bst->tree_nodes[*index].left, bst, key, data);
	}

}

// input:  'bst': a binary search tree
//	   'key': a pointer to a key
//	   'data': an integer
// effect: create a new node with the given key and data
// 	   set the right and left child of the node as leafs
// return: the value of top before inserting, this is the index
//	   of the new node.
static int new_node(BStree bst, Key *key, Data data){
	
	// set the tree node values for the new node
	bst->tree_nodes[bst->top].key = key;
	bst->tree_nodes[bst->top].data = data;

	// set the right and left subtree to be leaves
	bst->tree_nodes[bst->top].right = 0;
	bst->tree_nodes[bst->top].left = 0;
	
	// get value of top before incrementing as result
	// and then increment and return the result
	int result = bst->top;
	bst->top++;
	return result;
	
}

// Input: ’bst’: a binary search tree
// Effect: print all the nodes in bst using in order traversal
void bstree_traversal(BStree bst) {
	
	// call to recursive function to print all nodes in inorder traversal
	inorder(bst->root, bst);
}

// Input: 'index': an integer referencing an index in the bst
//	  ’bst’: a binary search tree
// Effect: print all the nodes in bst using in order traversal
void inorder(int index, BStree bst) {
	
	// base case of recursive function.
	// if we reach a leaf, or if the tree is empty
	// then do nothing
	if (index == 0) 
		return;
	// recursive case of function
	//first explore the left subtrees
	inorder(bst->tree_nodes[index].left, bst);
	// visit the nodes and print 
	print_node(bst->tree_nodes[index]);
	
	// then explore right subtree
	inorder(bst->tree_nodes[index].right, bst);

}

// Input: ’bst’: a binary search tree
// Effect: all dynamic memory used by bst are freed
void bstree_free(BStree bst) {

	// call to recursive helper function
	free_help(bst->root, bst);
	
	// free memory allocated to free nodes
	free(bst->free_nodes);
	
	//free memory allocated to tree nodes
	free(bst->tree_nodes);
	
	// free memory for the binary search tree structure
	free(bst);
}

// Input: 'index': an integer referencing an index in the bst
//	  ’bst’: a binary search tree
// Effect: all dynamic memory used by bst for objects of type Key
void free_help(int index, BStree bst) {
	
	// base case of recursive function
	// if at a leaf then do nothing 
	if (index == 0)
		return;
	
	// recursive case of function
	// visit the left subtrees first
	free_help(bst->tree_nodes[index].left, bst);
	
	// free the memory allocated for object Key
	// memory allocated when an object of type Key is created
	free(bst->tree_nodes[index].key->name);
	free(bst->tree_nodes[index].key);

	// visit right subtrees
	free_help(bst->tree_nodes[index].right, bst);
	

}




