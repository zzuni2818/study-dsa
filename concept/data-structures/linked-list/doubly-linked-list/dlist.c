#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

/*
	struct DLList
		head -> dummy
		tail -> dummy
*/

typedef int Data;

typedef struct DLNode {
	Data data;
	struct DLNode *prev;
	struct DLNode *next;
} Node;

typedef struct DLList {
	Node *head;
	Node *tail;

	Node *cur;
	
	size_t num_data;
} DList;

void DLInit(DList *plist);
void DLDestroy(DList *plist);
void DLInsertFront(DList *plist, Data data);
void DLInsertBack(DList *plist, Data data);

bool DLFirst(DList *plist, Data *pdata);
bool DLNext(DList *plist, Data *pdata);
bool DLPrevious(DList *plist, Data *pdata);
Data DLRemove(DList *plist);
size_t DLCount(DList *plist);

void DLPrintAll(DList *plist);

int main()
{
	DList list;
	int data, i;
	size_t count;

	DLInit(&list);
	
	//insert 5 7 9 2 3 1
	DLInsertFront(&list, 5);
	DLInsertFront(&list, 7);
	DLInsertFront(&list, 9);

	DLInsertBack(&list, 2);
	DLInsertBack(&list, 3);
	DLInsertBack(&list, 1);

	printf("Inserted 5, 7, 9, 2, 3, 1. Expect: 9 7 5 2 3 1\n");
	DLPrintAll(&list);

	//remove 5 2 3
	count = DLCount(&list);
	if(DLFirst(&list, &data)) {
		if(data == 5 || data == 2 || data == 3) {
			DLRemove(&list);
		}
		for(i = 1; i < count; i++) {
			if(DLNext(&list, &data)) {
				if(data == 5 || data == 2 || data == 3) {
					DLRemove(&list);
				}
			}
		}
	}

	printf("Removed 5, 2, 3. Expect: 9 7 1\n");
	DLPrintAll(&list);

	//remove all
	count = DLCount(&list);
	//remove all
	if(DLFirst(&list, &data)) {
		DLRemove(&list);
		for(i = 1; i < count; i++) {
			if(DLNext(&list, &data)) {
				DLRemove(&list);
			}
		}
	}

	printf("Removed all. Expect: Empty\n");
	DLPrintAll(&list);

	DLDestroy(&list);

	return 0;
}

void DLInit(DList *plist)
{
	//init dummy node
	plist->head = (Node*) malloc(sizeof(Node));
	plist->tail = (Node*) malloc(sizeof(Node));
	
	plist->head->prev = NULL;
	plist->head->next = plist->tail;

	plist->tail->prev = plist->head;
	plist->tail->next = NULL;

	plist->cur = NULL;
	plist->num_data = 0;
}
void DLDestroy(DList *plist)
{
	Data data;

	const size_t count = DLCount(plist);
	if(DLFirst(plist, &data)) {
		DLRemove(plist);
		for(int i = 1; i < count; i++) {
			if(DLNext(plist, &data)) {
				DLRemove(plist);
			}
		}
	}
	plist->cur = NULL;
	plist->num_data = 0;

	//destroy dummy node
	if(plist->head) {
		free(plist->head);
	}
	if(plist->tail) {
		free(plist->tail);
	}
}

void DLInsertFront(DList *plist, Data data)
{
	Node *new_nd = (Node*) malloc(sizeof(Node));
	new_nd->data = data;

	new_nd->prev = plist->head;
	new_nd->next = plist->head->next;
	plist->head->next->prev = new_nd;
	plist->head->next = new_nd;
	
	(plist->num_data)++;
}
void DLInsertBack(DList *plist, Data data)
{
	Node *new_nd = (Node*) malloc(sizeof(Node));
	new_nd->data = data;

	new_nd->prev = plist->tail->prev;
	new_nd->next = plist->tail;
	plist->tail->prev->next = new_nd;
	plist->tail->prev = new_nd;

	(plist->num_data)++;
}

bool DLFirst(DList *plist, Data *pdata)
{
	if(plist->head->next == plist->tail) {
		return false;
	}

	plist->cur = plist->head->next;

	*pdata = plist->cur->data;

	return true;
}
bool DLNext(DList *plist, Data *pdata)
{
	if(plist->cur->next == plist->tail) {
		return false;
	}

	plist->cur = plist->cur->next;

	*pdata = plist->cur->data;

	return true;
}
bool DLPrevious(DList *plist, Data *pdata)
{
	if(plist->cur->prev == plist->head) {
		return false;
	}

	plist->cur = plist->cur->prev;

	*pdata = plist->cur->data;

	return true;
}
Data DLRemove(DList *plist)
{
	Node *removed_nd = plist->cur;
	Data removed_data = plist->cur->data;

	removed_nd->prev->next = removed_nd->next;
	removed_nd->next->prev = removed_nd->prev;

	plist->cur = plist->cur->prev;

	free(removed_nd);
	(plist->num_data)--;

	return removed_data;
}
size_t DLCount(DList *plist)
{
	return plist->num_data;
}

void DLPrintAll(DList *plist)
{
	const size_t count = plist->num_data;
	Data data;

	if(count == 0) {
		printf("Empty\n");
		return;
	}

	if(DLFirst(plist, &data)) {
		printf("%d ", data);

		for(int i = 1; i < count; i++) {
			if(DLNext(plist, &data)) {
				printf("%d ", data);
			}
		}
		printf("\n");
	}
}
