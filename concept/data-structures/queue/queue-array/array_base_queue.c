#include <stdio.h>
#include <stdbool.h>

/*
	circular-queue based array
*/

#define QUEUE_SIZE 10

int queue[QUEUE_SIZE];
int front, rear;

void init_queue();
void clear_queue();
bool is_empty();
bool is_full();
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
	printf("*****Enqueue Test When Full*****\n");
	for(i = 0; i < QUEUE_SIZE; i++) {
		enqueue(i);
	}
	if(!enqueue(i)) {
		printf("[OK]\n");
	} else {
		printf("[ERROR]\n");
	}
	clear_queue();

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
	front = rear = 0;
}
void clear_queue()
{
	front = rear;
}
bool is_empty()
{
	return front == rear;
}
bool is_full()
{
	return ((rear + 1) % QUEUE_SIZE) == front;
}
bool enqueue(int data)
{
	if(is_full()) {
		return false;
	}

	queue[rear] = data;

	rear = (rear + 1) % QUEUE_SIZE;
	
	return true;
}
bool dequeue(int *pdata)
{
	if(is_empty()) {
		return false;
	}

	*pdata = queue[front];

	front = (front + 1) % QUEUE_SIZE;

	return true;
}

void print_queue()
{
	printf("queue(front -> rear): ");
	if(is_empty()) {
		printf("empty");
	} else {
		for(int i = front; i < rear; i++) {
			printf("%d ", queue[i]);
		}
	}
	printf("\n");
}
