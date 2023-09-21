#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

/*
	queue based doubly-linked-list
*/

struct qnode {
	int data;
	
	struct qnode *prev;
	struct qnode *next;
};

struct qnode *head, *tail;

void init_queue();
void clear_queue();
void destroy_queue();
bool is_empty();
bool enqueue(int data);
bool dequeue(int *pdata);
void print_queue();

int main()
{
	int i, data;

	init_queue();

	//enqueue: 2 5 8 4
	data = 2;
	if(enqueue(data)) {
		printf("enqueue: %d\n", data);
	}
	data = 5;
	if(enqueue(data)) {
		printf("enqueue: %d\n", data);
	}
	data = 8;
	if(enqueue(data)) {
		printf("enqueue: %d\n", data);
	}
	data = 4;
	if(enqueue(data)) {
		printf("enqueue: %d\n", data);
	}
	printf("expect: 2 5 8 4\n");
	print_queue();

	//dequeue: 2 5
	if(dequeue(&data)) {
		printf("dequeue: %d\n", data);
	}
	if(dequeue(&data)) {
		printf("dequeue: %d\n", data);
	}
	printf("expect: 8 4\n");
	print_queue();

	//clear
	clear_queue();

	printf("expect: empty\n");
	print_queue();


	printf("\n");
	printf("*****Dequeue Test When Empty*****\n");
	if(!dequeue(&data)) {
		printf("[OK]\n");
	} else {
		printf("[ERROR]\n");
	}

	return 0;
}

void init_queue()
{
	head = (struct qnode*) malloc(sizeof(struct qnode));
	tail = (struct qnode*) malloc(sizeof(struct qnode));

	head->prev = NULL;
	head->next = tail;
	
	tail->prev = head;
	tail->next = NULL;
}
void clear_queue()
{
	struct qnode *cur, *tmp;

	if(is_empty()) {
		return;
	}

	cur = head->next;
	while(cur != tail) {
		tmp = cur;
		cur = cur->next;
		free(tmp);
	}

	head->next = tail;
	tail->prev = head;
}
void destroy_queue()
{
	clear_queue();

	if(head) {
		free(head);
		head = NULL;
	}
	if(tail) {
		free(tail);
		tail = NULL;
	}
}
bool is_empty()
{
	return head->next == tail;
}
bool enqueue(int data)
{
	struct qnode *new_nd = (struct qnode*) malloc(sizeof(struct qnode));
	if(!new_nd){
		return false;
	}

	new_nd->data = data;

	tail->prev->next = new_nd;
	new_nd->prev = tail->prev;
	new_nd->next = tail;
	tail->prev = new_nd;

	return true;
}
bool dequeue(int *pdata)
{
	struct qnode *nd;

	if(is_empty()) {
		return false;
	}

	nd = head->next;

	head->next = nd->next;
	nd->next->prev = head;

	*pdata = nd->data;

	free(nd);

	return true;
}

void print_queue()
{
	struct qnode *cur;

	printf("queue(front -> rear): ");
	if(is_empty()) {
		printf("empty");
	} else {
		cur = head->next;
		while(cur != tail) {
			printf("%d ", cur->data);

			cur = cur->next;
		}
	}
	printf("\n");
}
