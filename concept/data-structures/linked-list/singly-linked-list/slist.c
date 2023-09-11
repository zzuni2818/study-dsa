#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct _node {
	int key;
	struct _node *next;
} node;

node *head, *tail;

void init_list();
node *insert_front(int k);
node *insert_after(int k, node *nd);
bool delete_front();
bool delete_next(node *nd);
node *find_node(int k);
bool delete_node(int k);
node *delete_all();
void print_list();

int main()
{
	node *nd;

	init_list();

	//insert 1, 7, 5, 9
	insert_front(1);
	insert_front(7);
	nd = insert_front(5);
	insert_front(9);
	printf("print list, expect 9 5 7 1.\n");
	print_list();

	//insert 8 after 5
	nd = insert_after(8, nd);
	//insert 2 after 8
	insert_after(2, nd);
	printf("print list, expect 9 5 8 2 7 1.\n");
	print_list();
	
	//remove 5
	nd = find_node(9);
	if(delete_next(nd)) {
		printf("5 has been removed.\n");
	}
	printf("print list, expect 9 8 2 7 1.\n");
	print_list();

	//remove 7
	if(delete_node(7)) {
		printf("7 has been removed.\n");
	}
	printf("print list, expect 9 8 2 1.\n");
	print_list();

	//remove 9
	if(delete_front()) {
		printf("9 has been removed.\n");
	}
	printf("print list, expect 8 2 1.\n");
	print_list();

	//remove 8
	if(delete_front()) {
		printf("8 has been removed.\n");
	}
	printf("print list, expect 2 1.\n");
	print_list();

	//remove all
	delete_all();
	printf("removed all.\n");
	printf("print list, expect empty.\n");
	print_list();
	
	return 0;
}

void init_list()
{
	head = (node *) malloc(sizeof(node));
	tail = (node *) malloc(sizeof(node));

	head->next = tail;
	tail->next = tail;
}

node *insert_front(int k)
{
	node *new_nd = (node *) malloc(sizeof(node));
	if(new_nd == NULL) {
		printf("Failed to allocate memory.\n");
		return NULL;
	}

	new_nd->key = k;
	new_nd->next = head->next;
	head->next = new_nd;

	return new_nd;
}
node *insert_after(int k, node *nd)
{
	node *new_nd = (node *) malloc(sizeof(node));
	if(new_nd == NULL) {
		printf("Failed to allocate memory.\n");
		return NULL;
	}
	
	new_nd->key = k;
	new_nd->next = nd->next;
	nd->next = new_nd;
	
	return new_nd;
}
bool delete_front()
{
	node *cur = head->next;
	if(cur == tail) {
		return false;
	}
	head->next = cur->next;
	free(cur);

	return true;
}

bool delete_next(node *nd)
{
	if(nd->next == tail) {
		return false;
	}

	node *tmp_nd = nd->next;
	nd->next = nd->next->next;
	free(tmp_nd);

	return true;
}
node *find_node(int k)
{
	//if failed to find key, return tail
	node *cur = head->next;

	while(cur->key != k && cur != tail) {
		cur = cur->next;
	}

	return cur;
}
bool delete_node(int k)
{
	node *prev = head;
	node *cur = head->next;

	while(cur->key != k && cur != tail) {
		prev = cur;
		cur = cur->next;
	}

	//if fail to find node, return false
	if(cur == tail) {
		return false;
	}

	prev->next = cur->next;
	free(cur);

	return true;
}
node *delete_all()
{	
	node *tmp;
	node *cur = head->next;
	while(cur != tail) {
		tmp = cur;
		cur = cur->next;
		free(tmp);
	}

	head->next = tail;

	return head;
}
void print_list()
{
	node *cur = head->next;
	while(cur != tail) {
		printf("%-8d ", cur->key);
		cur = cur->next;
	}
	printf("\n");
}
