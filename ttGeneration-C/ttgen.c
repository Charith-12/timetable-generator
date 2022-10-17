
#include <stdio.h>
#include <string.h>
#include <stdlib.h> //for malloc

int lecWL = 8; //lecturer's max workload in hours
int breakDur = 1; //break duration in hours
int maxOpDays = 4;
int maxsSlotsPerDay = 3; // based on operating hours
//int slotsTotal = 0; // total number of timeslots required for a week for particular batch


//structure to hold each module
struct module{
  char modid[8]; //module id (tag)
  int noc; //number of credits
  char lecid[8]; //assigned lecturer's id for the module
  struct module* link;
};

// < lecterer: to keep track of the workload globally > ?

//structure to hold a batch
struct batch{
  struct module* modules; // for modules list
  int slotsTotal; // total number of timeslots required for a week, for particular batch
};

//structure to hold each time-slot in the timetable/graph
struct node{
  int filled;
  struct module* occupiedBy;
  //int data;
  struct node* link;
};

// structure to hold the timetable
struct timetable{
    int V; // number of vertices in graph = no. of total timeslots
    struct node* nodesList;
};


/////////---------------------------------------------------------------------------------------------------------

// A structure to represent an adjacency list node
struct AdjListNode {
    int dest;
    struct AdjListNode* next;
};
 
// A structure to represent an adjacency list   //TODO: is it required? may be replace it with something for a daily slots list?
struct AdjList {
    struct AdjListNode* head;
};
 
// A structure to represent a graph. A graph
// is an array of adjacency lists.
// Size of array will be V (number of vertices
// in graph)
struct Graph {
    int V;
    struct AdjList* array;
};
 
// A utility function to create a new adjacency list node
struct AdjListNode* newAdjListNode(int dest){
    struct AdjListNode* newNode = (struct AdjListNode*)malloc(sizeof(struct AdjListNode));
    newNode->dest = dest;
    newNode->next = NULL;
    return newNode;
}
 
// A utility function that creates a graph of V vertices
struct Graph* createGraph(int V){
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->V = V;
 
    // Create an array of adjacency lists.  Size of
    // array will be V
    graph->array = (struct AdjList*)malloc(
        V * sizeof(struct AdjList));
 
    // Initialize each adjacency list as empty by
    // making head as NULL
    int i;
    for (i = 0; i < V; ++i)
        graph->array[i].head = NULL;
 
    return graph;
}
 
// Adds an edge to an undirected graph
void addEdge(struct Graph* graph, int src, int dest)
{
    // Add an edge from src to dest.  A new node is
    // added to the adjacency list of src.  The node
    // is added at the beginning
    struct AdjListNode* check = NULL;
    struct AdjListNode* newNode = newAdjListNode(dest);
 
    if (graph->array[src].head == NULL) {
        newNode->next = graph->array[src].head;
        graph->array[src].head = newNode;
    }
    else {
 
        check = graph->array[src].head;
        while (check->next != NULL) {
            check = check->next;
        }
        // graph->array[src].head = newNode;
        check->next = newNode;
    }

    // newNode = newAdjListNode(src);
    // newNode->next = graph->array[dest].head;
    // graph->array[dest].head = newNode;
}
 
// function to print the adjacency list
// representation of graph
void printGraph(struct Graph* graph)
{
    int v;
    for (v = 0; v < graph->V; ++v) {
        struct AdjListNode* pCrawl = graph->array[v].head;
        printf("\n Adjacency list of vertex %d\n head ", v);
        while (pCrawl) {
            printf("-> %d", pCrawl->dest);
            pCrawl = pCrawl->next;
        }
        printf("\n");
    }
}

///////---------------------------------------------------------------------------------------------------------

struct module* insertModules(char modid2[], int noc2, char lecid2[], struct module* h); // function prototpe for inserting a new node to the modules linked list
struct batch loadBatch(char fileName[]); // function prototpe for loading modules list from a txt file to a linked list
void displayModulesLL(struct module* h); // function prototpe for displaying the modules linked list
struct node* insert(int s, struct node* h); // function prototpe for adding nodes to the linked list of nodes (tt)
struct timetable* createTimetableSlots(int V); // function prototpe for creating an empty linked list of struct nodes. Length of LL (V) = no. of total possible timeslots 
void displayTtNodesLL(struct timetable* tt); // function prototpe for displaying the nodes linked list (timetable)


int main(){
	
  // ---------------------------------------------------------------------------------------------------------------------------------------------------
	{
	
//  FILE* fp1=NULL; //file with modules list
//  
//  struct batch batchOne;
//  
//  struct module* head=NULL; //create the head pointer of the modules linked list  
//    
//  //read the modules.txt
//  if((fp1=fopen("modules.txt", "r"))==NULL) printf("\nFile Error!\n");
//    
//  //assign to modules linked list
//  
//  // TODO: get all attributes from the line seperated by commas.
//  char modid[8], lecid[8], line[30];
//  int noc;
//  
//  int slotCount=0;
//
//  while(fgets(line, sizeof(line), fp1))
//  {
//      if(3 == sscanf(line, "%10s%10d%10s", modid, &noc, lecid))
//          printf("%s, %d, %s\n", modid, noc, lecid);
//          head=insert(modid, noc, lecid, head); //call insert to add a module to modules linked list 
//          slotCount = slotCount + noc;
//  }
//      	
//  fclose(fp1);
//  
//  //assign the linked list to struct module* modules of struct batch batchOne
//  batchOne.modules=head;
//  batchOne.slotsTotal=slotCount; // assign from slotCounter. can be used as the total no. of vertices in the graph. (vertice = single timeslot)
//  printf("\n Total timeslots required for batchOne : %d \n\n", slotCount);
}
  // ---------------------------------------------------------------------------------------------------------------------------------------------------
  
  struct batch batchOne = loadBatch("modules.txt"); // TODO: Handling multiple batches
  
  //displaying the modules linked list
  printf("modules.txt data loaded to a linked list.\n Modules linked list for the batch as follows,\n\n");
	displayModulesLL(batchOne.modules);
	
  // Calculating the total slot requirement for all added batches.
  int totalSlotReq = batchOne.slotsTotal; // just substituting for now 
    printf("\n Total timeslot requirement for all batches : %d \n\n", totalSlotReq);
    // TODO: IMPORTANT! we need more than 'slotsTotal' when allocating breaks inbetween. [naive sol: (batchOne.slotsTotal)*2 - 1]
    // TODO: Gets even more complicated with multiple batches where no.of breaks can be different with different slot placements.
  
  // Calculating the max possible no. of timeslots in the timetable based on constraints.
  int maxTtTimeSlots = maxOpDays*maxsSlotsPerDay;
  
  // checking whether tt generation is possible.
  if (maxTtTimeSlots < totalSlotReq) printf("\n Error!!! Total timeslot requirement exceeds the possible no. of timeslots.\n\n"); // TODO: Fix this. maybe handle this while allocating. 
  else{
  	{
//  	printf("\n\n - Creating the graph for timetable using timeslot --->\n");
//  
//  	// creating the graph 
//  	int V = totalSlotReq; // currently same as batchOne.slotsTotal
//  	struct Graph* graph = createGraph(V);

//		printf("\n\n - Creating the timetable using modules linked list for the batchOne --->\n\n");
//		  	
//		  	// count for batch's total slots
//		  	// count for modules's total slots
//		  	// count for lecturer's workload. get lecid out of the module struct and store globally.
//		  	// check if slot's occupied
//		  	// allocate breaks, check if previous slot was a break/lecture.
//		  	
//		  	addEdge(graph, 0, 1);
//		  	addEdge(graph, 0, 4);
//		  	addEdge(graph, 1, 2);
//		  	addEdge(graph, 1, 3);
//		  	addEdge(graph, 1, 4);
//		  	addEdge(graph, 2, 3);
//		  	addEdge(graph, 3, 4);
//		  	
//		  	
//		  	// print the adjacency list representation of the above graph
//		  	printGraph(graph);
}
  	
  	printf("\n\n - Creating the empty timeslots of timetable... \n");
  	
  	// creating the empty timetable 
  	int V = maxTtTimeSlots;  // TODO: IMPORTANT! we need more slots than the rquirement(and maybe even more than the max possible no.) when allocating breaks inbetween.
  	struct timetable* emptyTimetable = createTimetableSlots(V);
  	
  	//printf("\n Timeslots of the empty timetable as follows --->\n");
  	//displayTtNodesLL(emptyTimetable);
  	
  	printf("\n\n - Populating the timetable using modules linked list for the batchOne --->\n\n");
  		// count for batch's total slots - ok
	  	// count for modules's total slots - ok
	  	// count for lecturer's workload. get lecid out of the module struct and store globally.
	  	// check if slot's occupied - ok
	  	// allocate breaks, check if previous slot was a break/lecture. - ok
	  	
  	//create a pointer variables to loop through the linked list
	struct module* loopModule=NULL;
	struct node* loopNode=NULL;
	//int slotCountOfModule=0;
	int lecWLCount=0; // TODO: keeping track of workload of multiple lecturers simultaniously. how???
	int needBreak = 0; // TODO: no need to consider needBreak at the begining of a new day.
	
	loopModule=batchOne.modules;
	loopNode=(*emptyTimetable).nodesList;
	
	// going through modules list one-by-one to assign them
	while (loopModule!=NULL){
		
		int i=0;
		// allocating all required no. of slots according to the credit amout.
		for(i=0; i<((*loopModule).noc); i++){
			
			// going through timeslots list to check and assign particular module
			while (loopNode!=NULL){
				
				// if node is not already assigned:
				if((*loopNode).filled==0 && needBreak==0){
					
					
					// TODO: checking lecturer's WL & updating afterwards.
					(*loopNode).occupiedBy=loopModule;
					(*loopNode).filled=1;
					needBreak=1; // Setting next slot to be a break period
					
					loopNode=(*loopNode).link;
					// if got assigned, then breakout from here.(stop while) <>
					break;
				}
				
				needBreak=0;
				loopNode=(*loopNode).link;
			}		
		}
		//needBreak=1; // Uncomment if u want set next slot to be a break period only after one module is completted (consecutive slots for the same module)
		// don't goto the mext module unless all required slots have assigned for the module. ( when credits>1 ) <handeled with for loop>
		loopModule=(*loopModule).link;
	}
  	
  	printf("\n Timeslots after allocating modules as follows --->\n");
  	displayTtNodesLL(emptyTimetable);
  }
  
  
  /////////---------
  printf("\n************Finish*************\n\n");
  return 0;
}


// function to load modules list to a linked list.
struct module* insertModules(char modid2[], int noc2, char lecid2[], struct module* h){	
	
	//create a pointer variable to loop through the linked list
	struct module* loop=NULL;
	
	//create a pointer variable to keep the end node of the linked list
	struct module* prev=NULL;
	
	// for looper to handle char arrays
	int i=0;
	int length=0;
	
    //create new pointer to point to a "new block" of memory that can hold a struct module
    struct module* new=malloc(sizeof(struct module));
  
	//setting the data and the link
	// module id
    length = sizeof(modid2)/sizeof(modid2[0]); 
    for (i = 0; i < length; i++) {     
          (*new).modid[i] = modid2[i];     //printf("\nnew's data: %d\n", (*new).data);
    }      
    
    // no. of credits
    (*new).noc=noc2; //printf("\nnew's data: %d\n", (*new).data);
  	
  	// lecturer id
    length = sizeof(lecid2)/sizeof(lecid2[0]); 
    for (i = 0; i < length; i++) {     
          (*new).lecid[i] = lecid2[i];     //printf("\nnew's data: %d\n", (*new).data);
    } 
	
	// link
    (*new).link=NULL; //printf("\nnew's link: %p\n", (*new).link);
  
    //check for head node(=if there are no nodes in the list)
	if(h==NULL){
		h=new; //printf("\nhead's data: %d\n", (*head).data); printf("\nhead's link: %p\n", (*head).link);
	}else{  
		//loop through the linked list to find the tail end
		loop=h;   
		while(loop!=NULL){
			prev=loop;
			loop=(*loop).link; //step to next node
		}
		//copy the new node's memory address to end(=tail) node's link
		(*prev).link=new;
	}
	
	return h;
}

// A function to loading modules list from a txt file to a linked list.
struct batch loadBatch(char fileName[]){
	FILE* fp1=NULL; //file with modules list
  
  	struct batch newBatch;
  
  	struct module* head=NULL; //create the head pointer of the modules linked list  
    
  	//read the modules.txt
  	if((fp1=fopen(("%s", fileName), "r"))==NULL) printf("\nFile Error!\n");
    
  	//assign to modules linked list
  
  	// TODO: get all attributes from the line seperated by commas.
  	char modid[8], lecid[8], line[30];
  	int noc;
  
  	int slotCount=0;

  	while(fgets(line, sizeof(line), fp1))
  	{
     	 if(3 == sscanf(line, "%10s%10d%10s", modid, &noc, lecid))
      	    printf("%s, %d, %s\n", modid, noc, lecid);
       	   head=insertModules(modid, noc, lecid, head); //call insert to add a module to modules linked list 
       	   slotCount = slotCount + noc;
 	}
    
	//free(modid);  free(lecid); free(line); 	
 	fclose(fp1);
  
 	//assign the linked list to struct module* modules of struct batch batchOne
 	newBatch.modules=head;
	newBatch.slotsTotal=slotCount; // assign from slotCounter. can be used as the total no. of vertices in the graph. (vertice = single timeslot)
 	printf("\n Total timeslots required for this batch : %d \n\n", slotCount);
 	
 		//free(head); //free malloc data as appropriate TODO
 	 
 	return newBatch;
}

void displayModulesLL(struct module* h){
	//create a pointer variable to loop through the linked list
	struct module* loop=NULL;
	loop=h;
	while(loop!=NULL){
  	printf("| %s, %d, %s |", (*loop).modid, (*loop).noc, (*loop).lecid); printf("-->"); //printf(" %p |-->", (*loop).link);
  	loop=(*loop).link; 
  }
  printf("NULL\n");
}

// A function to add nodes to the linked list of nodes
struct node* insert(int s, struct node* h){	
	//create a pointer variable to loop through the linked list
	struct node* loop=NULL;
	
	//create a pointer variable to keep the end node of the linked list
	struct node* prev=NULL;
	
  //create new pointer to point to a "new block" of memory that can hold a struct node
  struct node* new=malloc(sizeof(struct node));
  
  //set data and the link
  (*new).filled=s; //printf("\nnew's data: %d\n", (*new).data);
  (*new).occupiedBy=NULL; //printf("\nnew's data: %d\n", (*new).data);
  (*new).link=NULL; //printf("\nnew's link: %p\n", (*new).link);
  
  //check for head node(=if there are no nodes in the list)
	if(h==NULL){
		h=new; //printf("\nhead's data: %d\n", (*head).data); printf("\nhead's link: %p\n", (*head).link);
	}else{  
		//loop through the linked list to find the tail end
		loop=h;   
		while(loop!=NULL){
			prev=loop;
			loop=(*loop).link; //step to next node
		}
		//copy the new node's memory address to end(=tail) node's link
		(*prev).link=new;
	}
	
	return h;
}

// A function for creating an empty linked list of struct nodes. Length of LL (V) = no. of total possible timeslots 
struct timetable* createTimetableSlots(int V){
	
	struct timetable* new=malloc(sizeof(struct timetable));
	//struct timetable* tt = (struct timetable*)malloc(sizeof(struct timetable));
	
	struct node* head=NULL;
	
	// creating the linked list
	int i=0;
	for (i=0; i < V; ++i){
		head=insert(0, head);
	}
	
	// asigining the empty linked list to the nodesList
	(*new).nodesList=head;
	(*new).V = V;
	
	return new;
}

void displayTtNodesLL(struct timetable* tt){ // TODO: seperate by days
	//create a pointer variable to loop through the linked list
	struct node* loop=NULL;
	loop=((*tt).nodesList);
	while(loop!=NULL){
		printf("\n Is this Node filled? %d. It has - ", ((*loop).filled));
		if((*loop).occupiedBy!=NULL){
			struct module* currentOccupiedModule = (*loop).occupiedBy;
	  		printf("| %s, %d, %s |", (*currentOccupiedModule).modid, (*currentOccupiedModule).noc, (*currentOccupiedModule).lecid); printf("-->"); //printf(" %p |-->", (*loop).link);
		}
		else {
			printf("NULL");
		}
		loop=(*loop).link; 
	}
	printf("\n");
}
