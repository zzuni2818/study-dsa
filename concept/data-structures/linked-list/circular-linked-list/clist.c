#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef int Data;

typedef struct CLNode {
	Data data;
	struct CLNode *next;
} Node;

typedef struct CLList {
	Node *tail;

	Node *prev;
	Node *cur;
	
	size_t num_data;
} CList;

void CLInit(CList *plist);
void CLInsertFront(CList *plist, Data data);
void CLInsertBack(CList *plist, Data data);

bool CLFirst(CList *plist, Data *pdata);
bool CLNext(CList *plist, Data *pdata);
Data CLRemove(CList *plist);
size_t CLCount(CList *plist);

void CLPrintAll(CList *plist);

int main()
{
	CList list;
	int data, i;
	size_t count;

	CLInit(&list);
	
	//insert 5 7 9 2 3 1
	CLInsertFront(&list, 5);
	CLInsertFront(&list, 7);
	CLInsertFront(&list, 9);

	CLInsertBack(&list, 2);
	CLInsertBack(&list, 3);
	CLInsertBack(&list, 1);

	printf("Inserted 5, 7, 9, 2, 3, 1. Expect: 9 7 5 2 3 1\n");
	CLPrintAll(&list);

	//remove 5 2 3
	count = CLCount(&list);
	if(CLFirst(&list, &data)) {
		if(data == 5 || data == 2 || data == 3) {
			CLRemove(&list);
		}
		for(i = 1; i < count; i++) {
			if(CLNext(&list, &data)) {
				if(data == 5 || data == 2 || data == 3) {
					CLRemove(&list);
				}
			}
		}
	}

	printf("Removed 5, 2, 3. Expect: 9 7 1\n");
	CLPrintAll(&list);

	//remove all
	count = CLCount(&list);
	if(CLFirst(&list, &data)) {
		CLRemove(&list);
		for(i = 1; i < count; i++) {
			if(CLNext(&list, &data)) {
				CLRemove(&list);
			}
		}
	}

	printf("Removed all. Expect: Empty\n");
	CLPrintAll(&list);

	return 0;
}

void CLInit(CList *plist)
{
	plist->tail = NULL;
	plist->prev = NULL;
	plist->cur = NULL;
	plist->num_data = 0;
}
void CLInsertFront(CList *plist, Data data)
{
	Node *new_nd = (Node*) malloc(sizeof(Node));
	new_nd->data = data;

	if(plist->tail == NULL) {
		plist->tail = new_nd;
		new_nd->next = new_nd;
	} else {
		new_nd->next = plist->tail->next;
		plist->tail->next = new_nd;
	}
	(plist->num_data)++;
}
void CLInsertBack(CList *plist, Data data)
{
	Node *new_nd = (Node*) malloc(sizeof(Node));
	new_nd->data = data;

	if(plist->tail == NULL) {
		plist->tail = new_nd;
		new_nd->next = new_nd;
	} else {
		new_nd->next = plist->tail->next;
		plist->tail->next = new_nd;
		plist->tail = new_nd;
	}

	(plist->num_data)++;
}

bool CLFirst(CList *plist, Data *pdata)
{
	if(plist->tail == NULL) {
		return false;
	}

	plist->prev = plist->tail;
	plist->cur = plist->tail->next;

	*pdata = plist->cur->data;

	return true;
}
bool CLNext(CList *plist, Data *pdata)
{
	if(plist->tail == NULL) {
		return false;
	}

	plist->prev = plist->cur;
	plist->cur = plist->cur->next;

	*pdata = plist->cur->data;

	return true;
}
Data CLRemove(CList *plist)
{
	Node *removed_nd = plist->cur;
	Data removed_data = plist->cur->data;

	if(removed_nd == plist->tail) {
		if(plist->tail == plist->tail->next) {
			plist->tail = NULL;
		} else {
			plist->tail = plist->prev;
		}
	}

	plist->prev->next = plist->cur->next;
	plist->cur = plist->prev;

	free(removed_nd);
	(plist->num_data)--;

	return removed_data;
}
size_t CLCount(CList *plist)
{
	return plist->num_data;
}

void CLPrintAll(CList *plist)
{
	const size_t count = plist->num_data;
	Data data;

	if(count == 0) {
		printf("Empty\n");
		return;
	}

	if(CLFirst(plist, &data)) {
		printf("%d ", data);

		for(int i = 1; i < count; i++) {
			if(CLNext(plist, &data)) {
				printf("%d ", data);
			}
		}
		printf("\n");
	}
}
