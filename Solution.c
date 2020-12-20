

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define N 100


typedef struct lifo_node{		//declaring node of a stack
	char name[51], roll[15];
	float cgpa;
	struct lifo_node *next;
}node;

typedef struct fifo{		//declaring the queue consisting of two stack pointers
	node *stack1, *stack2;
}qu;

void initializeStack(node **top){		//initializing stack
	*top=NULL;
}
void push_stack(node **top, char name[51], char roll[15], float cgpa){
	node *n=(node*)malloc(sizeof(node));
	if(n==NULL){
		printf("Stack overflow");
		exit (0);							//push function
	}
	strcpy(n->name, name);
	strcpy(n->roll, roll);
	n->cgpa=cgpa;
	n->next=*top;
	*top=n;

}

int isempty_stack(node *top){		//checking for empty stack
	if(top==NULL)
		return 1;			
	else 
		return 0;
}
node pop(node **top){		
	node record;
	node *p;
	if(isempty_stack(*top)==1){
		printf("Stack underflow\n");
		exit (0);
	}
	else{
		p=*top;
		record.cgpa=p->cgpa;
		strcpy(record.name, p->name);
		strcpy(record.roll, p->roll);
		*top=p->next;
		free(p);
		return record;
	}
}

void initializeQueue(qu **q){
	*q=(qu*)malloc(sizeof(qu));		//initializing queue
	
}

void AddQueue(qu *q, int sw1, int sw2, char name[51], char roll[15], float cgpa){ // sw1 and sw2 are acting as switches with values 0 and 1 for 
	if(sw1==0&&sw2==0&&isempty_stack(q->stack2)==1)									//accordingly redirecting the statement to be used. They are
		push_stack(&q->stack1, name, roll, cgpa);									//in relation with delete and display function. For main both sw1 and sw2 are 0.
	else if(sw1==0&&sw2==0&&isempty_stack(q->stack1)==1)
		push_stack(&q->stack2, name, roll, cgpa);		//Add queue function choses modes accordingly
	else if(sw2==1)
		push_stack(&q->stack2, name, roll, cgpa);
	else if(sw1==1)
		push_stack(&q->stack1, name, roll, cgpa);				
}

int isEmptyQueue(qu *q){
	if(isempty_stack(q->stack1)==1 && isempty_stack(q->stack2)==1)
		return 1;
	else
		return 0;
}

node* DeleteQueue(qu *q, int sw1, int sw2, int count){			
	node *record, temp;
	int i;

	record=(node*)malloc(sizeof(node));
	if(isEmptyQueue(q)==1){
		printf("\nstacks empty\n");
		return NULL;
	}
	else if(isempty_stack(q->stack2)==1 || sw2==1){			//copying to stack 2 from stack1
		while(q->stack1!=NULL){
			temp=pop(&q->stack1);
			push_stack(&q->stack2, temp.name, temp.roll, temp.cgpa);
		}
	temp=pop(&q->stack2);
														//poping top element
	record->cgpa=temp.cgpa;
	strcpy(record->name,temp.name);
	strcpy(record->roll,temp.roll);
	if(sw1==0&&sw2==0){
		while(q->stack2!=NULL){			//copying back to stack 1 fully.
			temp=pop(&q->stack2);
			push_stack(&q->stack1, temp.name, temp.roll, temp.cgpa);
		}
	}
	else{
		for(i=1; i<count; i++){			//copying back to stack 1 partially and constrained to the count used in display funtion.
			temp=pop(&q->stack2);
			push_stack(&q->stack1, temp.name, temp.roll, temp.cgpa);
		}
	}
	return record;
}
	
	else if(isempty_stack(q->stack1)==1 || sw1==1){			//copying to stack 1 from stack2
		while(q->stack2!=NULL){
			temp=pop(&q->stack2);
			push_stack(&q->stack1, temp.name, temp.roll, temp.cgpa);
		}
	temp=pop(&q->stack1);
				//poping top element
	record->cgpa=temp.cgpa;
	strcpy(record->name,temp.name);
	strcpy(record->roll,temp.roll);
	if(sw1==0&&sw2==0){
		while(q->stack1!=NULL){			//copying back to stack 2 fully.
			temp=pop(&q->stack1);
			push_stack(&q->stack2, temp.name, temp.roll, temp.cgpa);
		}
	}
	else{
		for(i=1; i<count; i++){						//copying partially
			temp=pop(&q->stack1);
			push_stack(&q->stack2, temp.name, temp.roll, temp.cgpa);
		}
	}
	return record;
	}
	
}

void display(qu *q, int count){			//count is the total number of elements in queue
	node *temp;
	int boolean=0, i, sw1, sw2;
	if(isEmptyQueue(q)==1){
		printf("\nEmpty Queue\n");
	}
	else{
		
		if(isempty_stack(q->stack2)==1){		//checking for stack 2 empty
			sw1=0; sw2=1;							//setting switch values accordingly
			while(q->stack1!=NULL){
	 			temp=DeleteQueue(q, sw1, sw2, count);
	 			printf("%s, %s, %.2f\n", temp->name, temp->roll, temp->cgpa); //deleting an item, printing it and adding back
	 			AddQueue(q, sw1, sw2, temp->name, temp->roll, temp->cgpa);
				count--;													//count is decreased for constrained copying
							}
			boolean=1;							//boolean is set to 1 so that once above block is executed control doesn't executes block below
		}										//since stack 1 becomes empty after first block.
		else if(isempty_stack(q->stack1)==1 && boolean==0){
			sw2=0; sw1=1;
			while(q->stack2!=NULL){
				temp=DeleteQueue(q, sw1, sw2, count);							//same procedure done with stack 2.
				printf("%s, %s, %.2f\n", temp->name, temp->roll, temp->cgpa);
				AddQueue(q, sw1, sw2, temp->name, temp->roll, temp->cgpa);
				count--;
			}
		}
		
	}
	
}
node* FindMaxQueue(node arr[N], qu *q, int *count_arr, int count){  //the array declared is arr
	if(isEmptyQueue(q)==1){
		return NULL;
	}
	int boolean=0, i=0, sw1, sw2;
	if(isempty_stack(q->stack2)==1){
		node *p, *temp; float max;
		p=q->stack1;
		max=p->cgpa;				//finding max cgpa.
		p=p->next;
		while(p!=NULL){			
			if(p->cgpa>max)
			max=p->cgpa;
			p=p->next;
			}						
			sw1=0; sw2=1;							//setting switch values accordingly
			while(q->stack1!=NULL){
	 			temp=DeleteQueue(q, sw1, sw2, count);		//same procedure as followed in display, only data is copied if cgpa found==max
	 			if(temp->cgpa==max){
					strcpy(arr[i].name,temp->name);			//data is copied to array elements.
					strcpy(arr[i].roll,temp->roll);
					arr[i].cgpa=temp->cgpa;
					i++;
				}
	
	 			AddQueue(q, sw1, sw2, temp->name, temp->roll, temp->cgpa);
				count--;													//count is decreased for constrained copying
							}
			boolean=1;							//boolean is set to 1 so that once above block is executed control doesn't executes block below
		}										//since stack 1 becomes empty after first block.
												
	else if(isempty_stack(q->stack1)==1 && boolean==0){
		node *p, *temp; float max;									
		p=q->stack2;
		max=p->cgpa;								
		p=p->next;
			while(p!=NULL){			
				if(p->cgpa>max)
					max=p->cgpa;
				p=p->next;
				}
			sw2=0; sw1=1;
			while(q->stack2!=NULL){
				temp=DeleteQueue(q, sw1, sw2, count);							//same procedure done with stack 2.
	 			if(temp->cgpa==max){
					strcpy(arr[i].name,temp->name);			//data is copied to array elements if cgpa is found == max.
					strcpy(arr[i].roll,temp->roll);
					arr[i].cgpa=temp->cgpa;
					i++;
				}
				AddQueue(q, sw1, sw2, temp->name, temp->roll, temp->cgpa);
				count--;
			}
		}
		
	*count_arr=i;					//pointer to integer count is returned to get number of elements in array
	return(arr);
}

int main(){
	//printf("start..\n\n");
	qu *q; node *dltd_rec, *max_list, arr[N];
	
	initializeQueue(&q);
	initializeStack(&q->stack1);		//initialization of all stacks and queue.
	initializeStack(&q->stack2);
	int c, i, count_arr, count_m=0;
	char name[51], roll[15];
	float cg;
	printf("1. to insert\n2. to delete\n3. to display\n4. to print toppers\n0. to exit\n");
	
	while (1)
	{
		printf("\nEnter your Choice : ");
		scanf("%d", &c);
		

		switch (c)
		{
			case 1 : printf("Enter details:\n");
					scanf(" %[^\n] %s %f", name, roll, &cg);
					AddQueue(q, 0, 0, name, roll, cg);
					printf("Added: %s, %s, %.2f\n", name, roll, cg);
					count_m++;											//count main is increased to count number of elements
				break;													//later used to put constraints in functional uses of display and delete 
				
			case 2 : dltd_rec=DeleteQueue(q, 0, 0, count_m);
					if(dltd_rec==NULL)
						printf("Nothing to delete\n");
					else{
					printf("Deleted: %s, %s, %.2f\n", dltd_rec->name, dltd_rec->roll, dltd_rec->cgpa);
					count_m--;
					}
				break;
				
			case 3 : printf("The contents of queue are:\n");
					display(q, count_m);
				break;
				
			case 4 : printf("The list of toppers:\n");
					max_list=FindMaxQueue(arr, q, &count_arr, count_m);
					if(max_list==NULL){
						printf("\nEmpty Queue, No toppers\n");
							}
						else{
							for(i=0; i<count_arr; i++){
							printf("%s, %s, %.2f\n", arr[i].name, arr[i].roll, arr[i].cgpa);
							}
						}
				break;
				
			case 0 : printf("Program Terminated.");
					exit(0);
				
				
			default: printf("Invalid choice: Enter with given numbers\n");
				break;
	}
}
	return 0;
}
