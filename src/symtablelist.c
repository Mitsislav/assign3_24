#include "symtable.h"

/*
 *	IOANNIS CHATZIANTONIOU CSD5193
 *	ASSIGNMENT 3
 *	symtablelist.c FILE
 */

/* the struct of a binding */
struct binding{
	char *key;
	void *value;
	struct binding *next;
};

/* the struct of the list with bindings */
struct SymTable{
	struct binding *head;
	unsigned int length;
};

/* it returns a new list with bindings (empty) */
SymTable_T SymTable_new(void){
	SymTable_T newTable= (SymTable_T)malloc(sizeof(struct SymTable));

	assert(newTable!=NULL);

	newTable->length=0;
	newTable->head=NULL;

	return newTable;
}

/* free the memory that is used by oSymTable ,
 * if oSymTable is null then return */
void SymTable_free(SymTable_T oSymTable){

	struct binding *temp;
	struct binding *tempnext;

	if(oSymTable==NULL){
		return;
	}

	temp=oSymTable->head;

	while(temp!=NULL){
		tempnext=temp->next;
		free(temp->key);
		free(temp);
		temp=tempnext;
	}

	free(oSymTable);

}

/* getter of the oSymTable's length */
unsigned int SymTable_getLength(SymTable_T oSymTable){
	assert(oSymTable!=NULL);
	return oSymTable->length;
}

/* puts a new binding in the list if that element does not exist */
int SymTable_put(SymTable_T oSymTable, const char *pcKey, const void *pvValue){

	struct binding *new;
	int exist=1;

	struct binding *current;

	assert(oSymTable!=NULL && pcKey!=NULL);

	/* check if this binding exists in this list */

	current=oSymTable->head;
	
	while(current!=NULL){
		exist=strcmp(current->key,pcKey);
		if(exist==0)
			return 0;
		current=current->next;
	}

	/* allocates memory for the new binding */

	new=(struct binding*) malloc(sizeof(struct binding));
	new->key=(char*)malloc(strlen(pcKey)+1);
	
	if(new->key==NULL){
		return 0;
	}

	/* copy the pcKey to the new->key */
	strcpy(new->key,pcKey);

	new->value=(void*)pvValue;
	new->next=oSymTable->head;
	oSymTable->head=new;
	oSymTable->length++;
	
	return 1;
}

/* removes an existing binding in the linked list */
int SymTable_remove(SymTable_T oSymTable, const char *pcKey){
	
	struct binding *current;
	struct binding *prev;	
	
	assert(oSymTable!=NULL && pcKey!=NULL);
 
	current=oSymTable->head;
	prev=NULL;

	while(current!=NULL){
		
		if((strcmp(current->key,pcKey))==0)
			break;

		prev=current;
		current=current->next;
	}

	/* case that binding does not exist */
	if(current==NULL)
		return 0;

	/* case that binding we want to remove
	 * is the header of the linked list */
	if (prev==NULL){
		oSymTable->head=oSymTable->head->next;
	}else{
		prev->next=current->next;
	}
	
	free(current->key);
	free(current);
	oSymTable->length--;

	return 1;
}

/* checks if a binding with pcKey value exists in the list */
int SymTable_contains(SymTable_T oSymTable,const char *pcKey){
	struct binding * current;
	int exist=1;

	assert(oSymTable!=NULL && pcKey!=NULL);

	current=oSymTable->head;
	while(current!=NULL){
		exist=strcmp(current->key,pcKey);
		
		/* binding with pcKey value exists */
		if(exist==0)
			return 1;
		current=current->next;
	}
	
	/* binding with pcKey value does not exist */
	if(current==NULL)
		return 0;

	return 0;		
}

/* returns the (void*) value of a binding if there is inside 
 * the linked list .It endepends that by pcKey value*/
void *SymTable_get(SymTable_T oSymTable, const char *pcKey){
	struct binding *current;
	int exist=1;
	
	assert(oSymTable!=NULL && pcKey!=NULL);

	current=oSymTable->head;

	while(current!=NULL){
		exist=strcmp(current->key,pcKey);
		
		/* binding with pcKey value exists */
		if(exist==0)
			return current->value;

		current=current->next;
	}
	/* binding with pcKey value does nott exist */
	return NULL;
}

/* applying the pfApply (pointer to a function) for
 * each binding inside the linked list*/
void SymTable_map(SymTable_T oSymTable,void (*pfApply)(const char *pcKey,void *pvValue,void *pvExtra),const void *pvExtra){
		
	struct binding *current;

	assert(oSymTable!=NULL && pfApply!=NULL);

	current=oSymTable->head;
	
	while(current!=NULL){
		pfApply((const char*)(current->key),current->value,(void*)pvExtra);
		current=current->next;
	}

}

