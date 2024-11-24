#ifndef __SYMTABLE_H__

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

/*
 *	IOANNIS CHATZIANTONIOU CSD5193
 *	ASSIGNMENT 3
 *	symtable.h FILE
 */

typedef struct SymTable *SymTable_T;


SymTable_T SymTable_new(void);

void SymTable_free(SymTable_T oSymTable);

unsigned int SymTable_getLength(SymTable_T oSymTable);

int SymTable_put(SymTable_T oSymTable, const char *pcKey,const void *pvValue);

int SymTable_remove(SymTable_T oSymTable, const char *pcKey);

int SymTable_contains(SymTable_T oSymTable, const char *pcKey);

void *SymTable_get(SymTable_T oSymTable, const char *pcKey);

void SymTable_map(SymTable_T oSymTable, void (*pfApply)
		(const char *pcKey, void *pvValue, void *pvExtra),
		const void *pvExtra);

#define __SYMTABLE_H__
#endif
