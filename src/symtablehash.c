#include "symtable.h"

/*
 * 	IOANNIS CHATZIANTONIOU CSD5193
 * 	ASSIGNMENT 3
 * 	symtablehash.c FILE
 */

#define HASH_MULTIPLIER 65599
#define BUCKETS 509

/* the struct of a binding */
struct binding{
	char *key;
	void *value;
	struct binding *next;
};

/* hold base address array of linked list*/
struct SymTable{
	struct binding **table;
	unsigned int buckets;
	unsigned int length;
};

/* Return a hash code for pcKey. */
static unsigned int SymTable_hash(const char *pcKey){
	size_t ui;
	unsigned int uiHash=0U;
	for(ui=0U; pcKey[ui]!='\0';ui++)
		uiHash = uiHash * HASH_MULTIPLIER + pcKey[ui];
	return uiHash;
}

/* makes a new SymTable */
SymTable_T SymTable_new(void){

	SymTable_T new=malloc(sizeof(struct SymTable*));
	
	assert(new!=NULL);

	new->table=malloc(BUCKETS*sizeof(struct binding*));
	new->length=0;
	new->buckets=509;
	return new;
}

/* free the memory of the table */
void SymTable_free(SymTable_T oSymTable){
	
	struct binding *current;
	struct binding *temp;
	int i=0;

	if(oSymTable==NULL)
		return;

	for(i=0;i<BUCKETS;i++){
		current=oSymTable->table[i];

		while(current!=NULL){
			temp=current->next;
			free(current->key);
			free(current);
			current=temp;
		}
	}
	free(oSymTable->table);
}

/* it returns the length of the table */
unsigned int SymTable_getLength(SymTable_T oSymTable){
	assert(oSymTable!=NULL);
	return oSymTable->length;
}

/* puts a new node in the table */
int SymTable_put(SymTable_T oSymTable, const char *pcKey, const void *pvValue){
	
	struct binding *current;
	struct binding *newNode;
	char *newKey;
	int exist=1;
	unsigned int pos=0;

	assert(oSymTable!=NULL && pcKey!=NULL);

	/* checks if the hash table has the element */
	current=oSymTable->table[SymTable_hash(pcKey) % 509];

	while(current!=NULL){
		exist=strcmp(current->key,pcKey);
		if(exist==0)
			return 0;
		current=current->next;
	}
	
	/* copies the pcKey inside newKey */
	newKey=(char*)malloc(strlen(pcKey)+1);	/* same job with strdub()*/
	if(newKey==NULL) return 0;
	strcpy(newKey,pcKey);


	/* allocate memory for the new binding*/
	newNode=(struct binding *)malloc(sizeof(struct binding));
	if(newNode==NULL) return 0;
	newNode->key=newKey;
	newNode->value=(void*)pvValue;


	pos=SymTable_hash(pcKey);
	pos=pos%509;
	newNode->next=oSymTable->table[pos];
	oSymTable->table[pos]=newNode;
	oSymTable->length++;

	return 1;
}

/* removes an elements if it exists returns 1 unless 0*/
int SymTable_remove(SymTable_T oSymTable,const char *pcKey){

	int pos=0;
	struct binding *current;
	struct binding *temp;

	assert(oSymTable!=NULL && pcKey!=NULL);

	pos=SymTable_hash(pcKey) % BUCKETS;
	current=oSymTable->table[pos];
	temp=NULL;

	while(current!=NULL){
		if(strcmp(pcKey,current->key)==0){
		
			if(temp==NULL){
				oSymTable->table[pos]=current->next;
			}else{
				temp->next=current->next;
			}

			free(current->key);
			free(current);
			oSymTable->length--;

			return 1;
		}

		temp=current;
		current=current->next;
	}
	return 0;

}

/* checks if the hash table has the element pcKey*/
int SymTable_contains(SymTable_T oSymTable,const char *pcKey){
	struct binding *current;
	int equals=1;
	unsigned int pos=SymTable_hash(pcKey) % BUCKETS;
	
	assert(oSymTable!=NULL && pcKey!=NULL);

	current=oSymTable->table[pos];
	while(current!=NULL){
		equals=strcmp(current->key,pcKey);

		if(equals==0)
			return 1;

		current=current->next;
	}
	return 0;
}

/* returns the value that matches to an element
 * with key value = pcKey */
void *SymTable_get(SymTable_T oSymTable,const char *pcKey){

	unsigned int pos=SymTable_hash(pcKey) % BUCKETS;
	struct binding *current;
	int found=1;

	assert(oSymTable!=NULL && pcKey!=NULL);

	current=oSymTable->table[pos];
	while(current!=NULL){
		found=strcmp(current->key,pcKey);
		
		if(found==0)
			return current->value;

		current=current->next;
	}
	return NULL;

}

/* applies the function where its pointer is pfApply 
 * to each binding of the hashtable */
void SymTable_map(SymTable_T oSymTable,void(*pfApply)(const char *pcKey,void *pvValue,void *pvExtra),const void *pvExtra){
	int i=0;
	struct binding* current;
	assert(oSymTable!=NULL && pfApply!=NULL);

	for(i=0;i<BUCKETS;i++){
		current=oSymTable->table[i];
		while(current!=NULL){
			pfApply((const char *)(current->key),current->value,(void*)pvExtra);
		       	current=current->next;
		}
	}
}

