#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

struct StackNode {
	int data;
	struct StackNode *next;
};

struct StackNode *head, *tail;

void init_stack();
void destroy_stack();
bool push(int data);
bool pop(int *pdata);
bool is_full();
bool is_empty();
void clear_stack();
void print_stack();

int main()
{
	int data;

	init_stack();

	//push: 2 5 8 4
	data = 2;
	if(push(data)) {
		printf("pushed: %d\n", data);
	}
	data = 5;
	if(push(data)) {
		printf("pushed: %d\n", data);
	}
	data = 8;
	if(push(data)) {
		printf("pushed: %d\n", data);
	}
	data = 4;
	if(push(data)) {
		printf("pushed: %d\n", data);
	}
	printf("expect: 4 8 5 2\n");
	print_stack();

	//pop: 4 8
	if(pop(&data)) {
		printf("poped: %d\n", data);
	}
	if(pop(&data)) {
		printf("poped: %d\n", data);
	}
	printf("expect: 5 2\n");
	print_stack();

	//clear
	clear_stack();

	printf("expect: empty\n");
	print_stack();


	printf("*****Pop Test When Empty*****\n");
	clear_stack();
	if(!pop(&data)) {
		printf("[OK]\n");
	} else {
		printf("[ERROR]\n");
	}

	destroy_stack();

	return 0;
}

void init_stack()
{
	head = (struct StackNode*) malloc(sizeof(struct StackNode));
	tail = (struct StackNode*) malloc(sizeof(struct StackNode));

	head->next = tail;
	tail->next = NULL;
}
void destroy_stack()
{
	if(head) {
		free(head);
		head = NULL;
	}
	if(tail) {
		free(tail);
		tail = NULL;
	}
}
bool push(int data)
{
	struct StackNode *nd;

	if((nd = (struct StackNode*) malloc(sizeof(struct StackNode))) == NULL) {
		return false;
	}
	
	nd->data = data;
	nd->next = head->next;
	head->next = nd;

	return true;
}
bool pop(int *pdata)
{
	struct StackNode *nd;

	if(is_empty()) {
		return false;
	}

	nd = head->next;
	head->next = nd->next;

	*pdata = nd->data;

	free(nd);

	return true;
}
bool is_full()
{
	return true;
}
bool is_empty()
{
	return head->next == tail;
}
void clear_stack()
{
	struct StackNode *tmp, *cur;
	
	cur = head->next;
	while(cur != tail) {
		tmp = cur;
		cur = cur->next;
		free(tmp);
	}
	head->next = tail;
}

void print_stack()
{
	struct StackNode *cur;

	printf("stack(top -> bottom): ");
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
