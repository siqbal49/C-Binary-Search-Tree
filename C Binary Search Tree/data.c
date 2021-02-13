// ====== this is in data.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data.h"
// Input: ’in_name’: a string ends with ’\0’
//        ’in_id’: an integer
// Output: a pointer of type pointer to Key,
//         pointing to an allocated memory containing a Key
// Effect: dynamically allocate memory to hold a Key
//         set Key’s id to be in_id
//         dynamically allocate memory for the Key’s name
//         so that name will contain what is in ’in_name’.
// Note:   do not use strdup(), use malloc(), strlen(), and strcpy()

Key *key_construct(char *in_name, int in_id) {
	// allocate memory for the input name
	char * in_name_dest = (char*) malloc(strlen(in_name+1)*sizeof(char));

	// copy the input name into the allocated memory
	strcpy(in_name_dest, in_name);

	// allocate memory for the key
	Key * new_key = (Key *) malloc(sizeof(Key));

	// set the id to the input key 
	new_key->id = in_id; 

	// set the key name to the inputted name
	new_key->name = in_name_dest;

	return new_key;
}

// Input:  ’key1’ and ’key2’ are two pointers to Key
// Output: if return value < 0, then *key1 < *key2,
//         if return value = 0, then *key1 = *key2,
//         if return value > 0, then *key1 > *key2,
// Note:   use strcmp() to compare key1->name and key2->name
//         if key1->name == key2->name, then compare key1->id with key2->id
int key_comp(Key *key1, Key *key2) {
	
	int result;
	
	// compare the name of key1 and key2
	// if the names are different, then strcmp() will
	// return a negative or positive number 
	result = strcmp(key1->name, key2->name);

	// if the key names are the same then result would 
	// be set as 0 by strcmp()	
	if (result == 0) {
		
		// now compare key id
		// compare the int values
		// set result according to the output stated above
		if (key1->id > key2->id)
			result = 1;
		else if (key1->id < key2->id)
			result = -1;
		else 
			result = 0;
	}
	return result; 
}

// Input: ’key’: a pointer to Key
// Effect: ( key->name key->id ) is printed
void print_key(Key *key) {
	printf("( %-15s %4d )", key->name, key->id);
}

// Input: ’node’: a node
// Effect: node.key is printed and then the node.data is printed
void print_node(Node node) {
	print_key(node.key);
	printf("%8d\n", node.data);
}