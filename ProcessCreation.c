#include <stdio.h>
#include <stdlib.h>

/* Define structures and global variables, including
linked list type and PCB type */

int max_processes = 0;

struct node1 {
	int process;
	struct node1 *link; //link = next

};
typedef struct node1 linked_list_type;

struct node2{
	int parent_ID;
	linked_list_type *children;
} *pcb = NULL;
typedef struct node2 pcb_type;

 

void option1() {
	/* declare local vars */
	int i;
	printf("Enter maximum number of processes: ");
	scanf("%d" , &max_processes);

	/* allocate memory for dynamic array of PCBs */
	pcb = (pcb_type *)malloc(max_processes * sizeof(pcb_type) );
	
	/* Define PCB[0] */
	pcb[0].parent_ID = 0;
	pcb[0].children = NULL;
	/* Intitialize all other indices' parent to -1 */

    printf("\n-------------------------------\n");
    printf("%d ", pcb[0]);
	for (i=1; i <= max_processes-1; i++) {
		pcb[i].parent_ID = -1;
		printf("%d ", pcb[i]);
	}
    printf("\n-------------------------------\n");

	return;
}
void option2() {
	/* define local vars */
	int q = 1;
	int p; // variable that hold user parent index value
	linked_list_type *new_child, *next_child;
	int num_children = 0;
	/* prompt for parent process index */
	printf("Enter the parent process index: ");
	scanf("%d", &p);
	printf("%d\n",p);
	/* search for next unused process q (parent=-1), using while loop */ 
	while(pcb[q].parent_ID != -1){
		q++;
	}
	/* allocate memory for new child PCB[q], set process index and initilize link to NULL */ 
	new_child = (linked_list_type*)malloc(sizeof(linked_list_type));
	new_child->process = q;
	new_child->link = NULL;
	/* record the parent's index p in PCB[q] */
	pcb[q].parent_ID = p;
	/* initialize the list of children of PCB[q] as empty (NULL) */
	pcb[q].children = NULL;
	/* create a new link containing the child's index q and 
	appends the link to the end of the linked list of PCB[p] */
	if(pcb[p].children == NULL){
		pcb[p].children = new_child;
		num_children=1;
	}
	else{
		next_child = pcb[p].children;
		num_children = 2;
		while(next_child->link != NULL){
			next_child = next_child->link;
			num_children++;
	}
	next_child->link = new_child;
	}
	/* print message: cr[p]	creates nth child of PCB[p] at PCB[q] */
	printf("nth child: %d", num_children);
	printf("\nPCB[p]: %d ", p);
	printf("at PCB[q]: %d\n", q);
	

	for (int i=0; i <= max_processes-1; i++) {
		printf("%d ", pcb[i]);
	}

	return;
}

void option3Recursion(linked_list_type *node){
	int q;
	if(node ==NULL){
		return;
	}
	else{
		option3Recursion(node->link);
		q = node->process;
		option3Recursion(pcb[q].children);
		printf("PCB[%d] ", q);
		free(node);
		pcb[q].parent_ID = -1;
		node = NULL;
		return;
	}
}
void option3(){
	int p; 
	printf("Enter the process whose descendants are to be destroyed: ");
	scanf("%d", &p);
	printf("d\n",p);
	
	printf("de[%d]\t/* destroys all descendants of PCB[%d] which includes: ",p,p);
	option3Recursion(pcb[p].children);
	pcb[p].children = NULL;
	return;
}
void option4(){
    free(pcb);
    return;
}



int main()
{
    int userSelection;
    do{
    //printf("Value of userSelection is: %d\n", userSelection);
    printf("\nProcess creation and destruction\n");
    printf("--------------------------------\n");
    printf("1) Enter parameters\n");
    printf("2) Create a new child process\n");
    printf("3) Destroy all descendants of a process\n");
    printf("4) Quit program and free memory\n");
    
    printf("\nEnter Selection: ");
    scanf("%d", &userSelection);
    switch(userSelection){
        case 1: option1(); break;
        case 2: option2(); break;
        case 3: option3(); break;
        case 4: option4(); break;
    }

}while(userSelection != 4);
    printf("BYE BYE");
   // option1();



    return 0;
}





