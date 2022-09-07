struct pair{
	int x;
	int y;
};	

struct Xpair{
	double v;
	struct pair p;
	struct Xpair *next;
};

struct cell{
	int parent_i;
	int parent_j;
	double f,g,h;
};

struct stack{
	int max;
	int top;
	struct pair* items;
};


struct Xpair* head = NULL;
struct Xpair* curr = NULL;


//functions for linked list, helps A*
void insert(double v, struct pair p);

//returns 1 if head is NULL showing it as empty, 0 if not
int isListEmpty();

//returns length by passing through
int length();



//Try to design an A* and place the points
void aStar(char m[][Y], struct pair src, struct pair dest);

int isValid(int row, int col);

//return 1 if not blocked, 0 if blocked
int isNotBlocked(char m[][Y], int row, int col);

//return 1 if destination door, 0 if not
int isDest(int row, int col, struct pair dest);

double calculateH(int row, int col, struct pair dest);

//UTIL, init stack
struct stack* newStack(int capacity);

//Count the size of stack
int size(struct stack *pt);

// returns 1 if true, 0 if not
int isEmpty(struct stack *pt);

// push a new element into stack
void push(struct stack *pt, struct pair point);

//returns 1 if true, 0 if not
int isFull(struct stack *pt);

//return top element
struct pair peek(struct stack *pt);

//pop a top element from the stack
struct pair pop(struct stack *pt);

