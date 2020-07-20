#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#define maxsize 10
typedef struct {
	char data[maxsize];
	int front, rear;
}sqqueue;
void init_queue(sqqueue **q);
bool empty_queue(sqqueue *q);
bool full_queue(sqqueue *q);
bool en_queue(sqqueue **q, char ch);
bool de_queue(sqqueue **q, char * ch);
int main(void)
{
	sqqueue *q;
	char ch;
	int i;
	init_queue(&q);
	if (empty_queue(q))
	{
		printf("empty\n");
	}
	if (!en_queue(&q, 'a'))
		printf("en a wrong");
	if (!en_queue(&q, 'b'))
		printf("en b wrong");
	if (!en_queue(&q, 'c'))
		printf("en c wrong");

	if (!de_queue(&q, &ch))
		printf("de wrong");
	else
		printf("%c\n", ch);

	if (!en_queue(&q, 'd'))
		printf("en a wrong");
	if (!en_queue(&q, 'e'))
		printf("en b wrong");
	if (!en_queue(&q, 'f'))
		printf("en c wrong");

	for (i = 0; i < 5; i++)
	{
		if (!de_queue(&q, &ch))
			printf("de wrong");
		else
			printf("%c", ch);

	}
	free(q);
	return 0;

}
void init_queue(sqqueue **q)
{
	(*q) = (sqqueue*)malloc(sizeof(sqqueue));
	(*q)->front = (*q)->rear = 0;
}
bool empty_queue(sqqueue *q)
{
	return(q->front == q->rear);
}
bool full_queue(sqqueue *q)
{
	return((q->rear + 1) % maxsize == q->front);
}
bool en_queue(sqqueue **q, char ch)
{
	if (full_queue(*q))
		return false;
	(*q)->rear = ((*q)->rear + 1) % maxsize;
	(*q)->data[(*q)->rear] = ch;
	return true;
}
bool de_queue(sqqueue **q, char * ch)
{
	if (empty_queue(*q))
		return false;
	(*q)->front = ((*q)->front + 1) % maxsize;
	*ch = (*q)->data[(*q)->front];
	return true;
}