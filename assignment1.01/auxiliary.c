#include "auxiliary.h"

int length(){
	int length = 0;
	struct Xpair* curr;
	for(curr = head; curr != NULL; curr = curr->next)
		length++;

	return length;
}

int isListEmpty(){
	if(head == NULL)
		return 1;
	return 0;
}
void insert(double v, struct pair p){
	struct Xpair* link = (struct Xpair*)malloc(sizeof(struct Xpair));
	link->p = p;
	link->v = v;
	link->next = head;

	head = link;
}
struct pair pop(struct stack *pt){
	if(isEmpty(pt)){
		exit(EXIT_FAILURE);
	}
	return pt->items[pt->top--];
}

struct pair peek(struct stack *pt){
	if(!isEmpty(pt)){
		return pt->items[pt->top];
		
	}
	else{
		exit(EXIT_FAILURE);
	}
}

int isFull(struct stack *pt){
	return pt->top == pt->max - 1;
}

void push(struct stack *pt, struct pair point){
	if(isFull(pt)){
		exit(EXIT_FAILURE);
	}
	pt->items[++pt->top] = point;
}

int isEmpty(struct stack *pt){
	return pt->top == -1;
}

int size(struct stack *pt){
	return pt->top + 1;
}

struct stack* newStack(int capacity){
	struct stack *pt = (struct stack*)malloc(sizeof(struct stack));
	pt->max = capacity;
	pt->top = -1;
	pt->items = (struct pair*)malloc(sizeof(struct pair) * capacity);
	return pt;
}

double calculateH(int row, int col, struct pair dest){
	return ((double)sqrt(pow((row - dest.x),2) +
				pow((col - dest.y),2)));
}


// find path from source to dest
// YOU NEED TO TAKE THE DOOR VALUES AND TURN IT INTO A PAIR FOR DESTINATION
int isDest(int row, int col, struct pair dest){
	if(row == dest.x && col == dest.y)
		return 1;
	return 0;
}

int isNotBlocked(char m[][Y], int row, int col){
	if(m[row][col] != '%')
		return 1;
	return 0;
}

//return 1 if valid, 0 if not
int isValid(int row, int col){
	if(row >= 0 && row < X && col >= 0 && col < Y)
		return 1;
	return 0;
}



