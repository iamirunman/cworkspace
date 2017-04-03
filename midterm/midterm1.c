/*
 * @author Pablo Escarcega
 */
#include <stdlib.h>
#include <stdio.h>

//nodes to be pushed/popped in the stack, contain data
typedef struct Node{
    int value;
    struct Node* next;
} stacknode;

//the actual stack
typedef struct Stack{
    stacknode *top;
    int size;
} stack;


//============================================================================== NEED
// initializes a new stack
stack *initializeStack(){
    stack *s = malloc(sizeof(stack));
    s->top = NULL;
    s->size = 0;
    return s;
}//end of initializeStack()


//============================================================================== NEED
// pushes a value onto the stack
int push(stack *s, int value){
    if(s == NULL)
        return 0;
        
    stacknode *p = malloc(sizeof(stacknode));	//making node
    
    if(p == NULL)
        return 0;
        
    p->value = value;
    p->next = s->top;
    s->top = p;
    s->size += 1;
    return 1;
}//end of push()


//============================================================================== NEED
// pops the end(top) of list(stack)
int pop(stack *s){
    if(s == NULL || s->top == NULL)
        return 0;
    
    stacknode *topElement = s->top;
    s->top = s->top->next;
    s->size -= 1;
    free(topElement);
    return 1;
}//end of pop()


//============================================================================== NEED
int top(stack *s){
	if(s->top == NULL){
		printf("The list is empty.\n");
		return -1;
	}
	return s->top->value;
}//end of top()


//============================================================================== NEED
//checks if stack is empty by looking at top element and returns 1 if it is empty
int isEmpty(stack *s){
	if(s->top == NULL){
		return 1;	//empty
	}
	return 0;		//not empty
}//end of isEmpty()


//==============================================================================
int main(){
	stack* even = initializeStack();
	stack* odd = initializeStack();
	stack* multipleOfThree = initializeStack();
	
	int userInput;
	
	printf("Enter values followed by pressing the return key (enter)\n\n");
    while (userInput >= 0){
        scanf(" %d", &userInput);
        if(userInput % 2 == 0){
        	push(even, userInput);
        }
        if(userInput % 2 == 1){
        	push(odd, userInput);
        }
        if(userInput % 3 == 0){
        	push(multipleOfThree, userInput);
        }
        
     }
	
	int data;
	
	int counter = 0;
	printf("\nEven values in reverse order:\n");
	while(isEmpty(even) == 0){
		counter++;
		data = top(even);
		printf("%d ", data);
		if(counter % 8 == 0 && counter != 0){
			printf("\n");
		}
		pop(even);
	}
	
	printf("\n");
	
	counter = 0;
	printf("\nOdd values in reverse order:\n");
	while(isEmpty(odd) == 0){
		counter++;
		data = top(odd);
		printf("%d ", data);
		if(counter % 8 == 0 && counter != 0){
			printf("\n");
		}
		pop(odd);
	}
	
	printf("\n");
	
	counter = 0;
	printf("\nThe multiples of 3 in reverse order:\n");
	while(isEmpty(multipleOfThree) == 0){
		counter++;
		data = top(multipleOfThree);
		printf("%d ", data);
		
		if(counter % 8 == 0 && counter!= 0){
			printf("\n");
		}
		pop(multipleOfThree);
	}
	
	printf("\n");
	
	return 0;
}//end of main
	