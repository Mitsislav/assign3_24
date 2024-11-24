#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symtable.h"

#define HASH_MULTIPLIER 65599
#define BUCKETS 509

/* Apply function to print key-value pairs */
void print_key_value(const char *key, void *value, void *extra) {
	printf("%s: %s\n", key, (char *)value);
}

int main(){
    	SymTable_T symTable1 = SymTable_new();
    	SymTable_T symTable2 = SymTable_new();

    	/* Test SymTable_put */
    	SymTable_put(symTable1, "key1", "value1");
    	SymTable_put(symTable1, "key2", "value2");
    	SymTable_put(symTable2, "name", "John");
    	SymTable_put(symTable2, "age", "19");

    	/* Test SymTable_getLength */
    	printf("Length of symTable1: %u\n", SymTable_getLength(symTable1));
    	printf("Length of symTable2: %u\n", SymTable_getLength(symTable2));

    	/* Test SymTable_contains */
    	printf("Does symTable1 contain key 'key1'? %d\n", SymTable_contains(symTable1, "key1"));
    	printf("Does symTable1 contain key 'name'? %d\n", SymTable_contains(symTable1, "name"));

    	/* Test SymTable_get */
    	printf("Value associated with key 'key1' in symTable1: %s\n", (char *)SymTable_get(symTable1, "key1"));
    	printf("Value associated with key 'name' in symTable2: %s\n", (char *)SymTable_get(symTable2, "name"));

    	/* Test SymTable_remove */
    	SymTable_remove(symTable1, "key1");
    	printf("After removing key 'key1', does symTable1 contain it? %d\n", SymTable_contains(symTable1, "key1"));

    	/* Test SymTable_map */
    	printf("Printing contents of symTable2:\n");
    	SymTable_map(symTable2, print_key_value, NULL);

    	/* Free memory */
    	SymTable_free(symTable1);
    	SymTable_free(symTable2);

    	return 0;
}

