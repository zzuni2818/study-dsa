#include <stdio.h>
#include <stdbool.h>

#define STACK_SIZE 10

int top;
int stack[STACK_SIZE];

void init_stack();
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


	printf("*****Push Test When Full*****\n");
	for(int i = 0; i < STACK_SIZE; i++) {
		push(i);
	}
	if(!push(STACK_SIZE)) {
		printf("[OK]\n");
	} else {
		printf("[Fail]\n");
	}

	printf("*****Pop Test When Empty*****\n");
	clear_stack();
	if(!pop(&data)) {
		printf("[OK]\n");
	} else {
		printf("[ERROR]\n");
	}

	return 0;
}

void init_stack()
{
	top = -1;
}
bool push(int data)
{
	if(is_full()) {
		return false;
	}

	stack[++top] = data;
	return true;
}
bool pop(int *pdata)
{
	if(is_empty()) {
		return false;
	}

	*pdata = stack[top--];
	return true;
}
bool is_full()
{
	return top == STACK_SIZE - 1;
}
bool is_empty()
{
	return top == -1;
}
void clear_stack()
{
	top = -1;
}
void print_stack()
{
	int data;

	printf("stack(top -> bottom): ");
	if(is_empty()) {
		printf("empty");
	} else {
		for(int i = top; i >= 0; i--) {
			printf("%d ", stack[i]);
		}
	}
	printf("\n");
}
