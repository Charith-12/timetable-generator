// #include <stdio.h>
// #include <stdlib.h> //for malloc
// #include <string.h> // for strcpy
// #include <mysql/mysql.h>//for database operations

// #define MAX_LECTURERS 100 // Maximum number of lecturers

// int totalCost = 0;
// int costIncr = 10; // cost of adding one extra timeslot
// int newRoomCost = 100; //cost of adding one extra classroom.

// struct subject {
// 	char modid[8]; // module id (tag)
//   	int noc; // number of credits (hours)
//   	int batch; // batch No. which the subject belongs
// };

// struct edge {
// 	char lecid[8]; // assigned lecturer's id for the module
// 	char modid[8]; // module id (tag)
//   	int color_id; // color of the edge
//   	int batch; // batch No. which the subject belongs
//   	int timeslot; // timeslot No. which the edge will be assigned
//   	char roomid[8]; // classroom id (tag)
//   	struct edge* link;
// };

// struct classroom {
// 	char roomid[8]; // room id (tag)
//   	int roomno; // unique integer id value
//   	int capacity; 
//   	struct classroom* link;
// };

// struct lecturer {
//   char lecid[8];
//   //char name[50]; // Name of the lecturer
//   int nos; // number of teaching subjects
//   int wl; // Total degree of the lecturer's node (number of teaching subjects * credit amount of each subject) = total no. of required independant timeslots (i.e. colors)
// } lecturers[MAX_LECTURERS];

// MYSQL* connectDB(); // function prototype for connecting to the database.
// int getLecturers(); // function prototype for getting lecturers in wl descending order, returns no. of lecturers. 
// struct subject* getSubjects(char lecid[], int nos); // Dynamic version // FREE memory after use
// struct edge* addNewEdge(char lecid2[], char modid2[], int color2, int batch2, int timeslot2, char roomid2[], struct edge* h); // A function prototype for adding a new edge to the linked list of edges.
// int putEdgesLL(struct edge* edgesLL_head,  char tablename[]); // A function prototype for inserting edges Linked List into the Database
// struct edge* getSortedEdgesLL(struct edge* sortedEdgesLL_head, int maxColors); // function prototype for getting sorted linked list of edges
// void displaySortedEdgesLL(struct edge* h); // function prototype for displaying sorted edges LL
// int assignTimeSlots(struct edge* sortedEdgesLL_head, int maxColors); // A function prototype for assigning timeslot value of edges. Returns timeslots count
// int sortEdgesLLbyTs(struct edge* head); // function prototype for sorting edges LL by the timeslot.
// struct classroom* addNewClassroom(char roomid2[], int roomno2, int capacity2, struct classroom* h); // A function prototype for adding a new node to classrooms LL
// struct classroom* getClassroomData(struct classroom* classroomsLL_head); // populating clasrooms LL
// void displayClassroomsLL(struct classroom* h); // function prototype for displaying classrooms LL
// int assignClassrooms(struct edge* sortedEdgesLL_head, struct classroom* classroomsLL_head, int ts_count); // function prototype for assigning classrooms for each edge. // Returns updated total timeslots count
// struct classroom* copyLL(struct classroom* head); // function prototype for duplicating classrooms LL
// int getNoStudents(int batch); // function prototype for getting the no. of students of a batch.
// struct classroom* chooseClassroom(int student_count, struct classroom* classroomListCopy_head); // function prototype for choosing the best classromm based on capacity.
// struct classroom* removeClassroomNode(struct classroom* copyOfclassroomsLL_head, int roomno); // for romoving a node from a classrooms LL.
// void deleteLL(struct classroom** head_ref); // prototype for deleting classrooms LL copy
// //int assignClassroomsRec(struct edge* sortedEdgesLL_head, struct edge* dupli_edgesLL_head, struct classroom* classroomsLL_head, int ts_count, int firstcall);


// int main(void) {
//   int num_lecturers = 0; // Number of lecturers
//   int index = 1; // Index of the current lecturer
//   struct edge* edgesLL_head = NULL; //create the head pointer of the edges linked list.  
//   struct edge* sortedEdgesLL_head = NULL; //create the head pointer of the sorted linked list of edges (by color, then by batch)
//   struct classroom* classroomsLL_head = NULL; //create the head pointer of the classrooms linked list.  
//   //struct edge* dup_edgesLL_head = NULL; // automatically sorted by timeslot // needed if there are classroom-unallocated edges remain.
	
//   int maxColors = 0;
//   int ts_count = 0; // total timeslots count
  
//   // at this point have:
//   	// Lecturers array of struct lecturers
//   	// for each lecturer: subjects array of struct subject
//   	 // with DB >> for each mod_id got from the subject-lecturer allocation table, get subject details from modules table and add that to struct array.
  
//   num_lecturers = getLecturers(); // populating lecturers array in wl descending order. also getting the lecturers count.
//   int i = 0;
//   int j = 0;
//   int k = 0;

//   // Lecturer array should be on wl descending order.

//   // Step 4: For all lecturers Li in the array
//   for (i = 0; i < num_lecturers; i++) {
//   	// Step 4.2: Count the degree of Li
//     int numOfSubs = lecturers[i].nos; // no of teaching subjects
//     int degreeTotal = lecturers[i].wl; // no of teaching subjects times credits (hours) of each subject.
//     if(degreeTotal>maxColors) maxColors=degreeTotal; // max number of colors required after considering everythig

//     // Step 4.3: If the index is odd number, then Set 1 for ColorId (<< an initiation) Else Set the degreeTotal for ColorId
//     int color_id = (index % 2 == 1) ? 1 : degreeTotal;

// 	// Getting and setting subjects array of the lecturer // v2: dynamic 
// 	struct subject* subjects = getSubjects(lecturers[i].lecid, numOfSubs); // Delete the global fix sized subjects array when using this.
	
//     // Step 4.5: For all subjects, Si in the array
//     for (j = 0; j < numOfSubs; j++) {
//     	// Step 4.5.1: Find the number of hours of Si
//         int hours = subjects[j].noc;  // Credits = Hours

//         // Step 4.5.2: For hours of Si
//         for (k = 0; k < hours; k++) {
      	
// 	    	// Step 4.5.2.1: Create new edge for Si  // Step 4.5.2.2: Set the ColorId as the Color id of the edge
// 	    	edgesLL_head = addNewEdge(lecturers[i].lecid, subjects[j].modid, color_id, subjects[j].batch, 0, "NA", edgesLL_head);
// 	    	printf("\n one edge added!");
//             // Step 4.5.2.3: If the index is odd number, then
//               // Step 4.5.2.3.1: Set ColorId + 1 for ColorId
//             // Step 4.5.2.4: Else
//               // Step 4.5.2.4.1: Set ColorId - 1 for ColorId
//             if (index % 2 == 1){
//             	color_id++;
// 			} else color_id--;
			
// 	    }
	
// 	}
// 	// Reset the subjects array  // v2: dynamic 
// 	free(subjects);
	
// 	index++;  //1. Set index+1 for index
  
//   }
  
//   if (putEdgesLL(edgesLL_head, "edges")) printf("\n Created edges added to the database successfully! \n");
  
//   sortedEdgesLL_head = getSortedEdgesLL(sortedEdgesLL_head, maxColors);
//   printf("\n Edges list, sorted by the color and batch - \n");
//   displaySortedEdgesLL(sortedEdgesLL_head);
  
//   ts_count = assignTimeSlots(sortedEdgesLL_head, maxColors);
//   printf("\n Timeslots are allocated to the edges successfully! \n");
//   printf("\n Timeslots allocated edges list - \n");
//   displaySortedEdgesLL(sortedEdgesLL_head);
  
//   if(sortEdgesLLbyTs(sortedEdgesLL_head)) printf("\n Edges LL sorted by the timeslot successfully! \n");
//   printf("\n Edges list after sorting by timeslot - \n");
//   displaySortedEdgesLL(sortedEdgesLL_head);
  
//   classroomsLL_head = getClassroomData(classroomsLL_head);
//   printf("\n Classrooms list retrieved from the DB - \n");
//   displayClassroomsLL(classroomsLL_head);
  
// //  struct classroom* copyOfclassroomsLL_head = copyLL(classroomsLL_head);  // classrooms linked list copy.
// //  printf("\n Copy of classrooms list - \n");
// //  displayClassroomsLL(copyOfclassroomsLL_head);
  
//   ts_count = assignClassrooms(sortedEdgesLL_head, classroomsLL_head, ts_count); // assigining classrooms and updating the total timeslot count.
//   printf("\n Classrooms assignment completed successfully! \n");
//   printf("\n Edges list after allocating classrooms - \n");
//   displaySortedEdgesLL(sortedEdgesLL_head);
  
//   if (putEdgesLL(sortedEdgesLL_head, "edges")) printf("\n Created edges added to the database successfully!! \n");
  
//   printf("\n Total cost = %d \n", totalCost);
  
//   // Recursive Test:
// //  struct edge* dupli_edgesLL_head = NULL;
// //  int tsTotal = assignClassroomsRec(sortedEdgesLL_head, dupli_edgesLL_head, classroomsLL_head, ts_count, 1);
// //  printf("\n Recursive Classroom Allocation \n");
// //  displaySortedEdgesLL(sortedEdgesLL_head);
//   //
  
//   return 0;
// }
    


// // ~~ RE: DB Operations ~~
// // A function to connect to the database
// MYSQL* connectDB(){
	
// 	MYSQL* con;
	
// 	// char* server = "localhost";
// 	// char* user = "cadevs";
// 	// char* password = "P@ssword123"; /*password*/
// 	// char* database = "university";

	// char* server = "localhost";
	// // char* user = "cadevs";
	// char* user = "root";
	// char* password = "new_password"; /*password*/
	// char* database = "university";
	
// 	con = mysql_init(NULL);
	
// 	/* Connect to database */
// 	if (!mysql_real_connect(con, server, user, password, database, 0, NULL, 0)){
// 	    printf("Failed to connect MySQL Server %s. Error: %s\n", server, mysql_error(con));
// 	    return NULL;
// 	}
	
// 	return con;
// }

// // A function to get lecturer details from the DB, update the array in work-load descending order and returns the total number of lecturers.
// int getLecturers() {
	
//     MYSQL* conn;
// 	MYSQL_RES* res;
// 	MYSQL_ROW row;
// 	conn = connectDB();
// 	int i = 0; // array index
	
// 	//char queryStr[100]; 
// 	//sprintf(queryStr, "SELECT lec_id, no_subjects, wl FROM lecturers ORDER BY wl DESC");
// 	//printf("\n%s\n", queryStr);
	
// 	/* send SQL query */
// 	if (mysql_query(conn, "SELECT lec_id, no_subjects, wl FROM lecturers ORDER BY wl DESC")){
// 	 	printf("Failed to execute query. Error: %s\n", mysql_error(conn));
// 	  	mysql_close(conn);
// 	  	return 0;
// 	}
	
// 	res = mysql_store_result(conn);
// 	if (res == NULL){
// 		mysql_close(conn);
// 		return 0;
//     }

// 	while(row = mysql_fetch_row(res)){
		
// 		strcpy(lecturers[i].lecid, (row[0] ? row[0] : "NULL"));
//   		lecturers[i].nos = atoi(row[1]);
//   		lecturers[i].wl = atoi(row[2]);
// 		//printf("%s ", row[i] ? row[i] : "NULL");		
// 		// atoi: int converting
// 		i++;
//  	}
//  	//printf("Entries of the table lecturers are added to the array\n");

// 	mysql_free_result(res);
// 	mysql_close(conn);

//  	return i;
// }

// // A function to get the subjects list of a lecturer.
// struct subject* getSubjects(char lecid[], int nos){
	
// 	struct subject* subjects = malloc(sizeof(struct subject) * nos);
	
//     printf("\n getting subjects of the lecturer %c", lecid[3]);
	
//     MYSQL* conn;
// 	MYSQL_RES* res;
// 	MYSQL_ROW row;
// 	conn = connectDB();
// 	int i = 0; // index of the array
	
// 	char queryStr[250]; 
// 	sprintf(queryStr, "SELECT m.mod_id, m.credits, m.batch_id FROM modules m INNER JOIN lmallocations a ON m.mod_id = a.mod_id AND a.lec_id = '%s' ORDER BY credits", lecid);
// 	//printf("\n%s\n", queryStr);
	
// 	/* send SQL query */
// 	if (mysql_query(conn, queryStr)){
// 	 	printf("Failed to execute query. Error: %s\n", mysql_error(conn));
// 	  	mysql_close(conn);
// 	  	return NULL;
// 	}
	
// 	res = mysql_store_result(conn);
// 	if (res == NULL){
// 		mysql_close(conn);
// 		return NULL;
//     }

// 	while(row = mysql_fetch_row(res)){
		
// 		strcpy(subjects[i].modid, (row[0] ? row[0] : "NULL"));
//   		subjects[i].noc = atoi(row[1]);
//   		subjects[i].batch = atoi(row[2]);
// 		//printf("%s ", row[i] ? row[i] : "NULL");		
// 		// atoi: int converting
// 		i++;
//  	}
//  	//printf("Selected entries of the table modules are added to the array\n");

// 	mysql_free_result(res);
// 	mysql_close(conn);

//  	return subjects;
// }

// // A function to add edges to the linked list of edges. (alocating lecturers, conflict free)
// struct edge* addNewEdge(char lecid2[], char modid2[], int color2, int batch2, int timeslot2, char roomid2[], struct edge* h){
	
// 	//create a pointer variable to loop through the linked list
// 	struct edge* loop=NULL;
// 	//create a pointer variable to keep the end node of the linked list
// 	struct edge* prev=NULL;
	
//  	//create new pointer to point to a "new block" of memory that can hold a struct node
//     struct edge* new=malloc(sizeof(struct edge));
  
//     //set data and the link
  	
//   	// lecturer id
//   	strcpy((*new).lecid, lecid2);
//   	// module id
//   	strcpy((*new).modid, modid2);
//     (*new).color_id = color2; //printf("\nnew's color_id: %d\n", (*new).color_id);  
//     (*new).batch = batch2; //printf("\nnew's batch: %d\n", (*new).batch);
//     (*new).timeslot = timeslot2; 
//     strcpy((*new).roomid, roomid2);
//     (*new).link=NULL; //printf("\nnew's link: %p\n", (*new).link);
  
//     //check for head node(=if there are no nodes in the list)
// 	if(h==NULL){
// 		h=new; 
// 	}else{  
// 		//loop through the linked list to find the tail end
// 		loop=h;   
// 		while(loop!=NULL){
// 			prev=loop;
// 			loop=(*loop).link; //step to next node
// 		}
// 		//copy the new node's memory address to end(=tail) node's link
// 		(*prev).link=new;
// 	}
	
// 	return h;
// }

// // A function to put edges Linked List into the Database
// int putEdgesLL(struct edge* edgesLL_head, char tablename[]){
	
// 	MYSQL* conn;
// 	conn = connectDB();
// 	char queryStr[250]; 
	
// 	//
// 	// ADD DROP TABLE IF EXISTS THEN CREATE EDGES TABLE
// 	sprintf(queryStr, "DROP TABLE IF EXISTS `%s`", tablename);	
// 	if (mysql_query(conn, queryStr)){
//     	printf("\n Failed to drop edges table! \nError: %s\n", mysql_error(conn));
//     	mysql_close(conn);
//     	return 0;
//   	}
// 	sprintf(queryStr, "CREATE TABLE `%s` (`lec_id` varchar(255) NOT NULL, `mod_id` varchar(255) NOT NULL, `color_id` int NOT NULL, `batch_id` int NOT NULL, `timeslot` int NOT NULL, `room_id` varchar(255) DEFAULT NULL)", tablename);	
// 	if (mysql_query(conn, queryStr)){
//     	printf("\n Failed to create edges table! \nError: %s\n", mysql_error(conn));
//     	mysql_close(conn);
//     	return 0;
//   	}
//   	sprintf(queryStr, "ALTER TABLE `%s` ADD PRIMARY KEY (`lec_id`,`mod_id`,`color_id`)", tablename);
//   	if (mysql_query(conn, queryStr)){
//     	printf("\n Failed to set Primary keys in edges table! \nError: %s\n", mysql_error(conn));
//     	mysql_close(conn);
//     	return 0;
//   	}
// 	//
	
// 	//create a pointer variable to loop through the linked list
// 	struct edge* loop = NULL;
// 	loop = edgesLL_head;
// 	while(loop!=NULL){
// 		sprintf(queryStr, "INSERT INTO %s (lec_id, mod_id, color_id, batch_id, timeslot, room_id) VALUES('%s', '%s', %d, %d, %d, '%s')", tablename, (*loop).lecid, (*loop).modid, (*loop).color_id, (*loop).batch, (*loop).timeslot, (*loop).roomid);
		
// 		/* send SQL query */	
// 		if (mysql_query(conn, queryStr)){
// 			printf("\n Query Error! Failed to insert edge to the DB. Error: %s\n", mysql_error(conn));
// 	    	mysql_close(conn);
// 	    	return 0; 
// 		}
		
//   		loop=(*loop).link; 
// 	}
	
// 	mysql_close(conn);

//  	return 1;
// }

// // A function to get sorted linked list of edges 
// struct edge* getSortedEdgesLL(struct edge* sortedEdgesLL_head, int maxColors){
	
// 	MYSQL* conn;
// 	MYSQL_RES* res;
// 	MYSQL_ROW row;
// 	conn = connectDB();
	
// 	struct edge* head = sortedEdgesLL_head;
// 	char queryStr[200]; 
// 	int color=1;
	
// 	for(color=1; color<maxColors+1; color++){
		
// 		sprintf(queryStr, "SELECT lec_id, mod_id, color_id, batch_id, timeslot, room_id FROM edges WHERE color_id = %d ORDER BY batch_id", color);
// 		//printf("\n%s\n", queryStr);
	
// 		/* send SQL query */
// 		if (mysql_query(conn, queryStr)){
// 	 		printf("Failed to execute query. Error: %s\n", mysql_error(conn));
// 	  		mysql_close(conn);
// 	  		return NULL;
// 		}
	
// 		res = mysql_store_result(conn);
// 		if (res == NULL){
// 			mysql_close(conn);
// 		    return NULL;
//     	}

// 		while(row = mysql_fetch_row(res)){
		
// 			head = addNewEdge( (row[0] ? row[0] : "NULL"), (row[1] ? row[1] : "NULL"), atoi(row[2]), atoi(row[3]), atoi(row[4]), (row[5] ? row[5] : "NULL"), head);
// 			//printf("%s ", row[i] ? row[i] : "NULL");		
// 			// atoi: 2,3,4 int converting
   		
//  		}
//  		//printf("Entries of the table edges are added to the linked list for a 1 color\n");

// 		mysql_free_result(res);
// 	}
	
// 	mysql_close(conn);

//  	return head;
// }

// void displaySortedEdgesLL(struct edge* h){
// 	//create a pointer variable to loop through the linked list
// 	struct edge* loop = NULL;
// 	loop = h;
// 	printf("\n| Lec_id | Mod_id | Col_id | Batch_id | T-slot | Room_id |\n");
// 	while(loop!=NULL){
//   		printf("| %s, %s, %d, %d, %d, %s |", (*loop).lecid, (*loop).modid, (*loop).color_id, (*loop).batch, (*loop).timeslot, (*loop).roomid); printf("\n"); //printf(" %p |-->", (*loop).link);
//   		loop=(*loop).link; 
//     }
//   	//printf("NULL\n");
// }

// // A Function to assign timeslot for the linked list of edges (and allocating batches, resolving conflicts). Returns timeslots count
// int assignTimeSlots(struct edge* sortedEdgesLL_head, int maxColors){
	
// 	struct edge* loop = NULL;
// 	loop = sortedEdgesLL_head;
// //4) Set 1 for the time slot Ts
// 	int timeslot = 1;
// 	int lastTs = 0; // id of the last timeslot in the timeslots list.
// 	int slot_jump = 0; // for adding new timeslots beyond the no. of colors (using when same batch has multiple edges with same color) 
// 	int repeat_count = 0; // for counting the times repeating the same batch inside the same color edges set.
// 	int max_repeats =0; // maximum repeats of the same batch regarding a specific color.
// 	int col_id = 0;
// 	int batch = 0;
// 	int first_item = 1;
	
// //5) For all edges Ei in E
// 	while(loop!=NULL){
		
// 		if (first_item){   //	5.1. If the edge is E1, then
// 			(*loop).timeslot = timeslot;  // 5.1.1. Set Ts(=1) for the timeslot of E1 
// 			if( (*loop).timeslot>lastTs ) lastTs=(*loop).timeslot; // updating the last timeslot
// 			col_id = (*loop).color_id;  // 5.1.2. Set Color id of E1 as ColorId
// 			//batch = (*loop).batch;  // 5.1.3. Set batch of E1 as the batch
// 		}
  		
//   		else if (col_id==(*loop).color_id) {    // 5.2. Else if the Color_id of Ei is ColorId, then
//   			if (batch==(*loop).batch) {   // 5.2.1. If the batch of Ei is batch (same batch)
//   				repeat_count++;
// 				(*loop).timeslot = maxColors+slot_jump+repeat_count;  // 5.2.1.1. Set Ts+1 for the timeslot of Ei (to avoid same batch conflicts)
// 				if( (*loop).timeslot>lastTs ) lastTs=(*loop).timeslot; // updating the last timeslot
// 				if (repeat_count>max_repeats) max_repeats = repeat_count;
// 			}
// 			else {    // 5.2.2 Else (different batch from the previous)
// 				repeat_count = 0;
// 				(*loop).timeslot = timeslot;  // 5.2.2.1.1. Set the current Ts as the timeslot of Ei
// 				if( (*loop).timeslot>lastTs ) lastTs=(*loop).timeslot; // updating the last timeslot
// 				//batch = (*loop).batch; //  5.2.2.2.2. Set batch of Ei as the batch
// 			}
// 		}
		
// 		else if (col_id!=(*loop).color_id) {   //	5.3. Else if the Color id of Ei is not the ColorId, then	
// 			slot_jump = slot_jump + max_repeats; // so the next Ts allocation for a repeating batch will be onto a new slot (since new color set)
// 			repeat_count = 0; max_repeats = 0;
// 			col_id = (*loop).color_id;  // 5.3.1. Set Color_id of Ei as ColorId
// 			timeslot++; // new color => new timeslot
// 			(*loop).timeslot = timeslot;  // 5.3.2. Set Ts as the timeslot of Ei 
// 			if( (*loop).timeslot>lastTs ) lastTs=(*loop).timeslot; // updating the last timeslot
// 			//batch = (*loop).batch; //  5.3.3. Set batch of Ei as the batch
// 		}   
		
// 		batch = (*loop).batch;  // 5.4. Set batch of Ei as the batch
  		
//   		first_item = 0;
// 		loop=(*loop).link; //1. Select the next edge and repeat step 5
//     }

// 	// 2. End	Returning the maximum timeslot id
// 	return lastTs;
// } 

// // A function to sort the edges LL by the timeslot
// int sortEdgesLLbyTs(struct edge* head) {
//     struct edge* current = NULL;
//     struct edge* index = NULL;

//     char temp_lecid[8]; // assigned lecturer's id for the module
// 	char temp_modid[8]; // module id (tag)
//   	int temp_color_id = 0;; // color of the edge
//   	int temp_batch = 0;; // batch No. which the subject belongs
//   	int temp_timeslot = 0; // timeslot No. which the edge will be assigned
//   	char temp_roomid[8]; // classroom id (tag)

//     if (head == NULL) {
//         return 0;
//     }

//     for (current = head; current->link != NULL; current = current->link) {
//         for (index = current->link; index != NULL; index = index->link) {
//             if (current->timeslot > index->timeslot) {
                
//                 strcpy(temp_lecid, current->lecid);
//                 strcpy(temp_modid, current->modid);
//                 temp_color_id = current->color_id;
//                 temp_batch = current->batch;
//                 temp_timeslot = current->timeslot;
//                 strcpy(temp_roomid, current->roomid);
                
//                 //current->data = index->data;
//                 strcpy(current->lecid, index->lecid);
//                 strcpy(current->modid, index->modid);
//                 current->color_id = index->color_id;
//                 current->batch = index->batch;
//                 current->timeslot = index->timeslot;
//                 strcpy(current->roomid, index->roomid);
                
//                 //index->data = tempData;
//                 strcpy(index->lecid, temp_lecid);
//                 strcpy(index->modid, temp_modid);
//                 index->color_id = temp_color_id;
//                 index->batch = temp_batch;
//                 index->timeslot = temp_timeslot;
//                 strcpy(index->roomid, temp_roomid);
//             }
//         }
//     }
    
//     return 1;
// }    

// // A function to add edges to the linked list of edges. (alocating lecturers, conflict free)
// struct classroom* addNewClassroom(char roomid2[], int roomno2, int capacity2, struct classroom* h){
	
// 	//create a pointer variable to loop through the linked list
// 	struct classroom* loop=NULL;
// 	//create a pointer variable to keep the end node of the linked list
// 	struct classroom* prev=NULL;
	
//  	//create new pointer to point to a "new block" of memory that can hold a struct node
//     struct classroom* new=malloc(sizeof(struct classroom));
  
//     //set data and the link    
//     strcpy((*new).roomid, roomid2);
//     (*new).roomno = roomno2; //printf("\nnew's batch: %d\n", (*new).batch);
//     (*new).capacity = capacity2; 
//     (*new).link=NULL; //printf("\nnew's link: %p\n", (*new).link);
  
//     //check for head node(=if there are no nodes in the list)
// 	if(h==NULL){
// 		h=new; 
// 	}else{  
// 		//loop through the linked list to find the tail end
// 		loop=h;   
// 		while(loop!=NULL){
// 			prev=loop;
// 			loop=(*loop).link; //step to next node
// 		}
// 		//copy the new node's memory address to end(=tail) node's link
// 		(*prev).link=new;
// 	}
	
// 	return h;
// }

// // A function to get classrom details to a linked list from DB
// struct classroom* getClassroomData(struct classroom* classroomsLL_head){
	
// 	MYSQL* conn;
// 	MYSQL_RES* res;
// 	MYSQL_ROW row;
// 	conn = connectDB();
	
// 	struct classroom* head = classroomsLL_head;
	
// 	//char queryStr[200]; 
// 	//sprintf(queryStr, "SELECT room_id, room_no, capacity FROM classrooms ORDER BY capacity");
// 	//printf("\n%s\n", queryStr);
	
// 	/* send SQL query */
// 	if (mysql_query(conn, "SELECT room_id, room_no, capacity FROM classrooms ORDER BY capacity")){
// 	 	printf("Failed to execute query. Error: %s\n", mysql_error(conn));
// 	  	mysql_close(conn);
// 	  	return NULL;
// 	}
	
// 	res = mysql_store_result(conn);
// 	if (res == NULL){
// 		mysql_close(conn);
// 		return NULL;
//     }

// 	while(row = mysql_fetch_row(res)){
		
// 		head = addNewClassroom( (row[0] ? row[0] : "NULL"), atoi(row[1]), atoi(row[2]), head);
// 		//printf("%s ", row[i] ? row[i] : "NULL");		
// 		// atoi: int converting
   		
//  	}
//  	//printf("Entries of the table classroom are added to the linked list\n");

// 	mysql_free_result(res);
// 	mysql_close(conn);

//  	return head;
// }

// void displayClassroomsLL(struct classroom* h){
// 	//create a pointer variable to loop through the linked list
// 	struct classroom* loop = NULL;
// 	loop = h;
// 	printf("\n| Room_id | Room_no (unique) | Capacity |\n");
// 	while(loop!=NULL){
//   		printf("| %s, %d, %d |", (*loop).roomid, (*loop).roomno, (*loop).capacity); printf("\n"); //printf(" %p |-->", (*loop).link);
//   		loop=(*loop).link; 
//     }
//   	//printf("NULL\n");
// }

// // A Function to assign classrooms for the linked list of edges (and allocating classrooms, conflict free)
// //int assignClassrooms(struct edge* sortedEdgesLL_head, struct classroom* classroomsLL_head){ // LL has to be sorted by the timeslot
// //	
// //	struct edge* loop = NULL;
// //	loop = sortedEdgesLL_head;
// //	
// //	struct classroom* roomsLL_head = classroomsLL_head; // original list of classrooms. cantains all.
// //	struct classroom* copyOfclassroomsLL_head = NULL;
// //	//copyOfclassroomsLL_head = copyLL(classroomsLL_head); // making a copy of entire classrooms list.
// //	
// //	int current_timeslot = -1;
// //	int student_count = 0;
// //	
// //	// For all edges
// //	while(loop!=NULL){
// //		
// //		// get the current timeslot of the edge // if its a new time slot,
// //		if( (*loop).timeslot!=current_timeslot ){ // timeslot change
// //			free(copyOfclassroomsLL_head);
// //			copyOfclassroomsLL_head = copyLL(roomsLL_head); // making a copy of entire classrooms list.
// //		}
// //		current_timeslot = (*loop).timeslot; // update current_timeslot
// //		
// //		student_count = getNoStudents( (*loop).batch ); // get the number of students of the batch from DB.
// //		struct classroom* bestRoom = chooseClassroom(student_count, copyOfclassroomsLL_head);// get the classroom id which has the just enough capacity.
// //		if (bestRoom!=NULL){ // A classroom found
// //			strcpy((*loop).roomid, (*bestRoom).roomid); // assign roomid to the edge.
// //			// remove that classroom node from the copyOfclassroomsLL.
// //			copyOfclassroomsLL_head = removeClassroomNode(copyOfclassroomsLL_head, (*bestRoom).roomno);
// //			
// //		} else strcpy((*loop).roomid, "UA");  // if there is no classrooms, assign "UA" // send to create a new timeslot // add the cost of extening hours	
// //		
// //
// //		loop=(*loop).link; //1. Select the next edge and repeat step 5
// //    }
// //
// //	free(copyOfclassroomsLL_head);
// //	return 1;
// //} 

// // A Function to assign classrooms for the linked list of edges (and allocating classrooms, conflict free)
// //int assignClassroomsRec(struct edge* sortedEdgesLL_head, struct edge* dupli_edgesLL_head, struct classroom* classroomsLL_head, int ts_count, int firstcall){ // LL has to be sorted by the timeslot
// //	
// //	struct edge* loop = NULL;
// //	loop = sortedEdgesLL_head;
// //	
// //	struct edge* dup_edgesLL_head = dupli_edgesLL_head;
// //	
// //	struct classroom* roomsLL_head = classroomsLL_head; // original list of classrooms. cantains all.
// //	struct classroom* copyOfclassroomsLL_head = NULL;
// //	//copyOfclassroomsLL_head = copyLL(classroomsLL_head); // making a copy of entire classrooms list.
// //	
// //	int current_timeslot = -1;
// //	int lastTs = ts_count; // current no. of timeslots
// //	int student_count = 0;
// //	
// //	// For all edges
// //	while(loop!=NULL){
// //		
// //		// get the current timeslot of the edge // if its a new time slot,
// //		if( (*loop).timeslot!=current_timeslot ){ // timeslot change
// //			deleteLL(&copyOfclassroomsLL_head);
// //			free(copyOfclassroomsLL_head);
// //			copyOfclassroomsLL_head = copyLL(roomsLL_head); // making a copy of entire classrooms list.
// //		}
// //		current_timeslot = (*loop).timeslot; // update current_timeslot
// //		
// //		student_count = getNoStudents( (*loop).batch ); // get the number of students of the batch from DB.
// //		struct classroom* bestRoom = chooseClassroom(student_count, copyOfclassroomsLL_head);// get the classroom id which has the just enough capacity.
// //		if (bestRoom!=NULL){ // A classroom found
// //			strcpy((*loop).roomid, (*bestRoom).roomid); // assign roomid to the edge.
// //			if ((*loop).timeslot>lastTs) lastTs = (*loop).timeslot;
// //			// remove that classroom node from the copyOfclassroomsLL.
// //			copyOfclassroomsLL_head = removeClassroomNode(copyOfclassroomsLL_head, (*bestRoom).roomno);
// //			
// //		} 
// //		else {
// //			strcpy((*loop).roomid, "UA");  // if there is no classrooms, assign "UA" // send to create a new timeslot // add the cost of extening hours	
// //			addNewEdge((*loop).lecid, (*loop).modid, (*loop).color_id, (*loop).batch, (lastTs + (*loop).timeslot), (*loop).roomid, dup_edgesLL_head);
// //		}
// //		
// //		
// //
// //		loop=(*loop).link; //1. Select the next edge and repeat step 5
// //    }
// //	
// //	deleteLL(&copyOfclassroomsLL_head);
// //	free(copyOfclassroomsLL_head);
// //	
// //	if (dup_edgesLL_head!=NULL){
// //		lastTs = assignClassroomsRec(dup_edgesLL_head, dup_edgesLL_head, roomsLL_head, lastTs, 0);
// //	}
// //	return lastTs;
// //} 


// // A Function to assign classrooms for the linked list of edges (and allocating classrooms, conflict free) // Returns updated total timeslots count
// int assignClassrooms(struct edge* sortedEdgesLL_head, struct classroom* classroomsLL_head, int ts_count){ // LL has to be sorted by the timeslot
	
// 	struct edge* loop = NULL;
// 	loop = sortedEdgesLL_head;
	
// 	struct classroom* roomsLL_head = classroomsLL_head; // original list of classrooms. cantains all.
// 	struct classroom* copyOfclassroomsLL_head = NULL;
// 	//copyOfclassroomsLL_head = copyLL(classroomsLL_head); // making a copy of entire classrooms list.
	
// 	int current_timeslot = -1;
// 	int lastTs = ts_count; // current no. of timeslots
// 	int student_count = 0;
	
// 	// For all edges
// 	while(loop!=NULL){
		
// 		// get the current timeslot of the edge // if its a new time slot,
// 		if( (*loop).timeslot!=current_timeslot ){ // timeslot change
// 			deleteLL(&copyOfclassroomsLL_head);
// 			free(copyOfclassroomsLL_head);
// 			copyOfclassroomsLL_head = copyLL(roomsLL_head); // making a copy of entire classrooms list.
// 		}
// 		current_timeslot = (*loop).timeslot; // update current_timeslot
		
// 		student_count = getNoStudents( (*loop).batch ); // get the number of students of the batch from DB.
// 		struct classroom* bestRoom = chooseClassroom(student_count, copyOfclassroomsLL_head); // get the classroom id which has the just enough capacity.
// 		if (bestRoom!=NULL){ // A classroom found
// 			strcpy((*loop).roomid, (*bestRoom).roomid); // assign roomid to the edge.
// 			// remove that classroom node from the copyOfclassroomsLL.
// 			copyOfclassroomsLL_head = removeClassroomNode(copyOfclassroomsLL_head, (*bestRoom).roomno);
			
// 		} else { // no classrooms available OR no classrooms with required capacity (if this the case, user must seperate the batch in to 2 from front end beforehand so at least 1 classromm has the enough capacity for the batch).
// 			bestRoom = chooseClassroom(student_count, roomsLL_head);  // get the classroom id for use with a new timeslot
// 			if (bestRoom!=NULL){  // not enough classrooms to use with the original timeslot, so new timeslot
// 				strcpy((*loop).roomid, (*bestRoom).roomid);
// 				(*loop).timeslot = lastTs+1;
// 				lastTs++;
// 				totalCost = totalCost + costIncr; // adding the cost of extening hours (extra timeslot).
// 			} 
// 			else {		// no classrooms with required capacity
// 				strcpy((*loop).roomid, "UA-NEC");  // if there is no classrooms, assign "Un-Assigned - Not Enough Capacity" 
// 				totalCost = totalCost + newRoomCost; // require additional classroom.
// 			}
			
// 			//addNewEdge((*loop).lecid, (*loop).modid, (*loop).color_id, (*loop).batch, (*loop).timeslot, (*loop).roomid[], dup_edgesLL_head);
// 		}
		

// 		loop=(*loop).link; //1. Select the next edge and repeat step 5
//     }

// 	deleteLL(&copyOfclassroomsLL_head);
// 	free(copyOfclassroomsLL_head);
// 	return lastTs;
// } 

// // A function to create a copy of a classrooms linked list
// struct classroom* copyLL(struct classroom* head){
//     if (head == NULL) {
//         return NULL;
//     }
//     else {
  
//         // Allocate the memory for new Node
//         struct classroom* newNode = (struct classroom*)malloc(sizeof(struct classroom));
  
//         //newNode->data = head->data;
//         strcpy((*newNode).roomid, (*head).roomid);
//     	(*newNode).roomno = (*head).roomno; 
//     	(*newNode).capacity = (*head).capacity;
  
//         // Recursively set the next pointer of the new Node by recurring for the remaining nodes
//         newNode->link = copyLL(head->link);
  
//         return newNode;
//     }
// }

// // A function to get the number of students of a batch from DB.
// int getNoStudents(int batch){
	
// 	MYSQL* conn;
// 	MYSQL_RES* res;
// 	MYSQL_ROW row;
// 	conn = connectDB();
	
// 	char queryStr[200]; 
// 	int studentCount = 0;
	
// 	sprintf(queryStr, "SELECT no_students FROM batches WHERE batch_id = %d", batch);
// 	//printf("\n%s\n", queryStr);
	
// 	/* send SQL query */
// 	if (mysql_query(conn, queryStr)){
// 	 	printf("Failed to execute query. Error: %s\n", mysql_error(conn));
// 	  	mysql_close(conn);
// 	  	return 0;
// 	}
	
// 	res = mysql_store_result(conn);
// 	if (res == NULL){
// 		mysql_close(conn);
// 	    return 0;
//     }

// 	while(row = mysql_fetch_row(res)){
		
// 		studentCount = atoi(row[0]);
// 		//printf("%s ", row[i] ? row[i] : "NULL");		
// 		// atoi: int converting
//  	}
//  	//printf("Number of students of the batch is retrived from the DB\n");

// 	mysql_free_result(res);
// 	mysql_close(conn);

//  	return studentCount;
// }

// // Function to choose the best classroom for a particular edge, returns a pointer to the best classroom
// struct classroom* chooseClassroom(int student_count, struct classroom* classroomListCopy_head) {
    
//     struct classroom* classroom_loop_node = NULL; 
//     classroom_loop_node = classroomListCopy_head;
// 	struct classroom* best_classroom = NULL; 
    
//     //Iterate through all classrooms sorted by the capacity in ascending order
//     while(classroom_loop_node!=NULL) {

//         //Check if current classroom has just enough capacity
//         if( classroom_loop_node->capacity >= student_count) {
//             best_classroom = classroom_loop_node;
//             break;
//         }
        
//         classroom_loop_node = classroom_loop_node->link;
//     }
    
//     return best_classroom;
// }

// // A function to remove a classroom node from the classrooms LL
// struct classroom* removeClassroomNode(struct classroom* copyOfclassroomsLL_head, int roomno2){
// 	struct classroom* head = copyOfclassroomsLL_head;
// 	struct classroom* temp = copyOfclassroomsLL_head;
// 	struct classroom* prev = copyOfclassroomsLL_head;
	
//     if (temp!=NULL && temp->roomno == roomno2) { // head is removing
//         head = temp->link;
//         free(temp);
//         return head;
//     }

//     while (temp!=NULL && temp->roomno != roomno2) {
//         prev = temp;
//         temp = temp->link;
//     }

//     if (temp == NULL) return head; // no matching node found in the entire LL.
//     prev->link = temp->link;
//     free(temp);
//     return head; // head of the updated LL
// }

// void deleteLL(struct classroom** head_ref){
//    /* deref head_ref to get the real head */
//    struct classroom* current = *head_ref;
//    struct classroom* next;
 
//    while (current != NULL){
//        next = current->link;
//        free(current);
//        current = next;
//    }
   
//    /* deref head_ref to affect the real head back
//       in the caller. */
//    *head_ref = NULL;
// }

#include <stdio.h>
#include <stdlib.h> //for malloc
#include <string.h> // for strcpy
#include <mysql/mysql.h>
 //for database operations

#define MAX_LECTURERS 100 // Maximum number of lecturers

int totalCost = 0;
int costIncr = 10; // cost of adding one extra timeslot
int newRoomCost = 100; //cost of adding one extra classroom.

struct subject {
	char modid[8]; // module id (tag)
  	int noc; // number of credits (hours)
  	int batch; // batch No. which the subject belongs
};

struct edge {
	char lecid[8]; // assigned lecturer's id for the module
	char modid[8]; // module id (tag)
  	int color_id; // color of the edge
  	int batch; // batch No. which the subject belongs
  	int timeslot; // timeslot No. which the edge will be assigned
  	char roomid[8]; // classroom id (tag)
  	struct edge* link;
};

struct classroom {
	char roomid[8]; // room id (tag)
  	int roomno; // unique integer id value
  	int capacity; 
  	struct classroom* link;
};

struct lecturer {
  char lecid[8];
  //char name[50]; // Name of the lecturer
  int nos; // number of teaching subjects
  int wl; // Total degree of the lecturer's node (number of teaching subjects * credit amount of each subject) = total no. of required independant timeslots (i.e. colors)
} lecturers[MAX_LECTURERS];

MYSQL* connectDB(); // function prototype for connecting to the database.
int getLecturers(); // function prototype for getting lecturers in wl descending order, returns no. of lecturers. 
struct subject* getSubjects(char lecid[], int nos); // Dynamic version // FREE memory after use
struct edge* addNewEdge(char lecid2[], char modid2[], int color2, int batch2, int timeslot2, char roomid2[], struct edge* h); // A function prototype for adding a new edge to the linked list of edges.
int putEdgesLL(struct edge* edgesLL_head,  char tablename[]); // A function prototype for inserting edges Linked List into the Database
struct edge* getSortedEdgesLL(struct edge* sortedEdgesLL_head, int maxColors); // function prototype for getting sorted linked list of edges
void displaySortedEdgesLL(struct edge* h); // function prototype for displaying sorted edges LL
int assignTimeSlots(struct edge* sortedEdgesLL_head, int maxColors); // A function prototype for assigning timeslot value of edges. Returns timeslots count
int sortEdgesLLbyTs(struct edge* head); // function prototype for sorting edges LL by the timeslot.
struct classroom* addNewClassroom(char roomid2[], int roomno2, int capacity2, struct classroom* h); // A function prototype for adding a new node to classrooms LL
struct classroom* getClassroomData(struct classroom* classroomsLL_head); // populating clasrooms LL
void displayClassroomsLL(struct classroom* h); // function prototype for displaying classrooms LL
int assignClassrooms(struct edge* sortedEdgesLL_head, struct classroom* classroomsLL_head, int ts_count); // function prototype for assigning classrooms for each edge. // Returns updated total timeslots count
struct classroom* copyLL(struct classroom* head); // function prototype for duplicating classrooms LL
int getNoStudents(int batch); // function prototype for getting the no. of students of a batch.
struct classroom* chooseClassroom(int student_count, struct classroom* classroomListCopy_head); // function prototype for choosing the best classromm based on capacity.
struct classroom* removeClassroomNode(struct classroom* copyOfclassroomsLL_head, int roomno); // for romoving a node from a classrooms LL.
void deleteLL(struct classroom** head_ref); // prototype for deleting classrooms LL copy
//int assignClassroomsRec(struct edge* sortedEdgesLL_head, struct edge* dupli_edgesLL_head, struct classroom* classroomsLL_head, int ts_count, int firstcall);


int main(void) {
  int num_lecturers = 0; // Number of lecturers
  int index = 1; // Index of the current lecturer
  struct edge* edgesLL_head = NULL; //create the head pointer of the edges linked list.  
  struct edge* sortedEdgesLL_head = NULL; //create the head pointer of the sorted linked list of edges (by color, then by batch)
  struct classroom* classroomsLL_head = NULL; //create the head pointer of the classrooms linked list.  
  //struct edge* dup_edgesLL_head = NULL; // automatically sorted by timeslot // needed if there are classroom-unallocated edges remain.
	
  int maxColors = 0;
  int ts_count = 0; // total timeslots count
  
  // at this point have:
  	// Lecturers array of struct lecturers
  	// for each lecturer: subjects array of struct subject
  	 // with DB >> for each mod_id got from the subject-lecturer allocation table, get subject details from modules table and add that to struct array.
  
  num_lecturers = getLecturers(); // populating lecturers array in wl descending order. also getting the lecturers count.
  int i = 0;
  int j = 0;
  int k = 0;

  // Lecturer array should be on wl descending order.

  // Step 4: For all lecturers Li in the array
  for (i = 0; i < num_lecturers; i++) {
  	// Step 4.2: Count the degree of Li
    int numOfSubs = lecturers[i].nos; // no of teaching subjects
    int degreeTotal = lecturers[i].wl; // no of teaching subjects times credits (hours) of each subject.
    if(degreeTotal>maxColors) maxColors=degreeTotal; // max number of colors required after considering everythig

    // Step 4.3: If the index is odd number, then Set 1 for ColorId (<< an initiation) Else Set the degreeTotal for ColorId
    int color_id = (index % 2 == 1) ? 1 : degreeTotal;

	// Getting and setting subjects array of the lecturer // v2: dynamic 
	struct subject* subjects = getSubjects(lecturers[i].lecid, numOfSubs); // Delete the global fix sized subjects array when using this.
	
    // Step 4.5: For all subjects, Si in the array
    for (j = 0; j < numOfSubs; j++) {
    	// Step 4.5.1: Find the number of hours of Si
        int hours = subjects[j].noc;  // Credits = Hours

        // Step 4.5.2: For hours of Si
        for (k = 0; k < hours; k++) {
      	
	    	// Step 4.5.2.1: Create new edge for Si  // Step 4.5.2.2: Set the ColorId as the Color id of the edge
	    	edgesLL_head = addNewEdge(lecturers[i].lecid, subjects[j].modid, color_id, subjects[j].batch, 0, "NA", edgesLL_head);
	    	
            // Step 4.5.2.3: If the index is odd number, then
              // Step 4.5.2.3.1: Set ColorId + 1 for ColorId
            // Step 4.5.2.4: Else
              // Step 4.5.2.4.1: Set ColorId - 1 for ColorId
            if (index % 2 == 1){
            	color_id++;
			} else color_id--;
			
	    }
	
	}
	// Reset the subjects array  // v2: dynamic 
	free(subjects);
	
	index++;  //1. Set index+1 for index
  
  }
  
  if (putEdgesLL(edgesLL_head, "edges")) printf("\n Created edges added to the database successfully! \n");
  
  sortedEdgesLL_head = getSortedEdgesLL(sortedEdgesLL_head, maxColors);
  printf("\n Edges list, sorted by the color and batch - \n");
  displaySortedEdgesLL(sortedEdgesLL_head);
  
  ts_count = assignTimeSlots(sortedEdgesLL_head, maxColors);
  printf("\n Timeslots are allocated to the edges successfully! \n");
  printf("\n Timeslots allocated edges list - \n");
  displaySortedEdgesLL(sortedEdgesLL_head);
  
  if(sortEdgesLLbyTs(sortedEdgesLL_head)) printf("\n Edges LL sorted by the timeslot successfully! \n");
  printf("\n Edges list after sorting by timeslot - \n");
  displaySortedEdgesLL(sortedEdgesLL_head);
  
  classroomsLL_head = getClassroomData(classroomsLL_head);
  printf("\n Classrooms list retrieved from the DB - \n");
  displayClassroomsLL(classroomsLL_head);
  
//  struct classroom* copyOfclassroomsLL_head = copyLL(classroomsLL_head);  // classrooms linked list copy.
//  printf("\n Copy of classrooms list - \n");
//  displayClassroomsLL(copyOfclassroomsLL_head);
  
  ts_count = assignClassrooms(sortedEdgesLL_head, classroomsLL_head, ts_count); // assigining classrooms and updating the total timeslot count.
  printf("\n Classrooms assignment completed successfully! \n");
  printf("\n Edges list after allocating classrooms - \n");
  displaySortedEdgesLL(sortedEdgesLL_head);
  
  if (putEdgesLL(sortedEdgesLL_head, "edges")) printf("\n Created edges added to the database successfully!! \n");
  
  printf("\n Total cost = %d \n", totalCost);
  
  // Recursive Test:
//  struct edge* dupli_edgesLL_head = NULL;
//  int tsTotal = assignClassroomsRec(sortedEdgesLL_head, dupli_edgesLL_head, classroomsLL_head, ts_count, 1);
//  printf("\n Recursive Classroom Allocation \n");
//  displaySortedEdgesLL(sortedEdgesLL_head);
  //
  
  return 0;
}
    


// ~~ RE: DB Operations ~~
// A function to connect to the database
MYSQL* connectDB(){
	
	MYSQL* con;
	
	// char* server = "localhost";
	// char* user = "cadevs";
	// char* password = "P@ssword123"; /*password*/
	// char* database = "university";

    char* server = "localhost";
	// char* user = "cadevs";
	char* user = "root";
	char* password = "new_password"; /*password*/
	char* database = "university";
	

	// char* server = "localhost";
	// // char* user = "cadevs";
	// char* user = "root";
	// char* password = "adithya1"; /*password*/
	// char* database = "university";
	
	con = mysql_init(NULL);
	
	/* Connect to database */
	if (!mysql_real_connect(con, server, user, password, database, 0, NULL, 0)){
	    printf("Failed to connect MySQL Server %s. Error: %s\n", server, mysql_error(con));
	    return NULL;
	}
	
	return con;
}

// A function to get lecturer details from the DB, update the array in work-load descending order and returns the total number of lecturers.
int getLecturers() {
	
    MYSQL* conn;
	MYSQL_RES* res;
	MYSQL_ROW row;
	conn = connectDB();
	int i = 0; // array index
	
	char queryStr[250]; 
	sprintf(queryStr, "SELECT a.lec_id, COUNT(a.mod_id), SUM(m.credits) FROM lmallocations a INNER JOIN modules m ON m.mod_id = a.mod_id GROUP BY a.lec_id ORDER BY SUM(m.credits) DESC");
	//printf("\n%s\n", queryStr);
	
	/* send SQL query */
	if (mysql_query(conn, queryStr)){
	 	printf("Failed to execute query. Error: %s\n", mysql_error(conn));
	  	mysql_close(conn);
	  	return 0;
	}
	
	res = mysql_store_result(conn);
	if (res == NULL){
		mysql_close(conn);
		return 0;
    }

	while(row = mysql_fetch_row(res)){
		
		strcpy(lecturers[i].lecid, (row[0] ? row[0] : "NULL")); //printf("%s ", row[0] ? row[0] : "NULL");	
  		lecturers[i].nos = (row[1] ? atoi(row[1]) : 0); //printf("%d ", row[1] ? atoi(row[1]) : 0);
  		lecturers[i].wl = (row[2] ? atoi(row[2]) : 0);	//printf("%d ", row[2] ? atoi(row[2]) : 0);
		// atoi: int converting
		i++;
 	}
 	//printf("Entries of the table lecturers are added to the array\n");

	mysql_free_result(res);
	mysql_close(conn);

 	return i;
}

// A function to get the subjects list of a lecturer.
struct subject* getSubjects(char lecid[], int nos){
	
	struct subject* subjects = malloc(sizeof(struct subject) * nos);
	
    printf("\n getting subjects of the lecturer %c", lecid[3]);
	
    MYSQL* conn;
	MYSQL_RES* res;
	MYSQL_ROW row;
	conn = connectDB();
	int i = 0; // index of the array
	
	char queryStr[250]; 
	sprintf(queryStr, "SELECT m.mod_id, m.credits, b.batch_id FROM modules m INNER JOIN bmallocations b ON m.mod_id = b.mod_id INNER JOIN lmallocations a ON m.mod_id = a.mod_id AND a.lec_id = '%s' ORDER BY credits", lecid);
	//printf("\n%s\n", queryStr);
	
	/* send SQL query */
	if (mysql_query(conn, queryStr)){
	 	printf("Failed to execute query. Error: %s\n", mysql_error(conn));
	  	mysql_close(conn);
	  	return NULL;
	}
	
	res = mysql_store_result(conn);
	if (res == NULL){
		mysql_close(conn);
		return NULL;
    }

	while(row = mysql_fetch_row(res)){
		
		strcpy(subjects[i].modid, (row[0] ? row[0] : "NULL"));
  		subjects[i].noc = atoi(row[1]);
  		subjects[i].batch = atoi(row[2]);
		//printf("%s ", row[i] ? row[i] : "NULL");		
		// atoi: int converting
		i++;
 	}
 	//printf("Selected entries of the table modules are added to the array\n");

	mysql_free_result(res);
	mysql_close(conn);

 	return subjects;
}

// A function to add edges to the linked list of edges. (alocating lecturers, conflict free)
struct edge* addNewEdge(char lecid2[], char modid2[], int color2, int batch2, int timeslot2, char roomid2[], struct edge* h){
	
	//create a pointer variable to loop through the linked list
	struct edge* loop=NULL;
	//create a pointer variable to keep the end node of the linked list
	struct edge* prev=NULL;
	
 	//create new pointer to point to a "new block" of memory that can hold a struct node
    struct edge* new=malloc(sizeof(struct edge));
  
    //set data and the link
  	
  	// lecturer id
  	strcpy((*new).lecid, lecid2);
  	// module id
  	strcpy((*new).modid, modid2);
    (*new).color_id = color2; //printf("\nnew's color_id: %d\n", (*new).color_id);  
    (*new).batch = batch2; //printf("\nnew's batch: %d\n", (*new).batch);
    (*new).timeslot = timeslot2; 
    strcpy((*new).roomid, roomid2);
    (*new).link=NULL; //printf("\nnew's link: %p\n", (*new).link);
  
    //check for head node(=if there are no nodes in the list)
	if(h==NULL){
		h=new; 
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

// A function to put edges Linked List into the Database
int putEdgesLL(struct edge* edgesLL_head, char tablename[]){
	
	MYSQL* conn;
	conn = connectDB();
	char queryStr[250]; 
	
	//
	// ADD DROP TABLE IF EXISTS THEN CREATE EDGES TABLE
	sprintf(queryStr, "DROP TABLE IF EXISTS `%s`", tablename);	
	if (mysql_query(conn, queryStr)){
    	printf("\n Failed to drop edges table! \nError: %s\n", mysql_error(conn));
    	mysql_close(conn);
    	return 0;
  	}
	sprintf(queryStr, "CREATE TABLE `%s` (`lec_id` varchar(255) NOT NULL, `mod_id` varchar(255) NOT NULL, `color_id` int NOT NULL, `batch_id` int NOT NULL, `timeslot` int NOT NULL, `room_id` varchar(255) DEFAULT NULL)", tablename);	
	if (mysql_query(conn, queryStr)){
    	printf("\n Failed to create edges table! \nError: %s\n", mysql_error(conn));
    	mysql_close(conn);
    	return 0;
  	}
  	sprintf(queryStr, "ALTER TABLE `%s` ADD PRIMARY KEY (`lec_id`,`mod_id`,`color_id`)", tablename);
  	if (mysql_query(conn, queryStr)){
    	printf("\n Failed to set Primary keys in edges table! \nError: %s\n", mysql_error(conn));
    	mysql_close(conn);
    	return 0;
  	}
	//
	
	//create a pointer variable to loop through the linked list
	struct edge* loop = NULL;
	loop = edgesLL_head;
	while(loop!=NULL){
		sprintf(queryStr, "INSERT INTO %s (lec_id, mod_id, color_id, batch_id, timeslot, room_id) VALUES('%s', '%s', %d, %d, %d, '%s')", tablename, (*loop).lecid, (*loop).modid, (*loop).color_id, (*loop).batch, (*loop).timeslot, (*loop).roomid);
		
		/* send SQL query */	
		if (mysql_query(conn, queryStr)){
			printf("\n Query Error! Failed to insert edge to the DB. Error: %s\n", mysql_error(conn));
	    	mysql_close(conn);
	    	return 0; 
		}
		
  		loop=(*loop).link; 
	}
	
	mysql_close(conn);

 	return 1;
}

// A function to get sorted linked list of edges 
struct edge* getSortedEdgesLL(struct edge* sortedEdgesLL_head, int maxColors){
	
	MYSQL* conn;
	MYSQL_RES* res;
	MYSQL_ROW row;
	conn = connectDB();
	
	struct edge* head = sortedEdgesLL_head;
	char queryStr[200]; 
	int color=1;
	
	for(color=1; color<maxColors+1; color++){
		
		sprintf(queryStr, "SELECT lec_id, mod_id, color_id, batch_id, timeslot, room_id FROM edges WHERE color_id = %d ORDER BY batch_id", color);
		//printf("\n%s\n", queryStr);
	
		/* send SQL query */
		if (mysql_query(conn, queryStr)){
	 		printf("Failed to execute query. Error: %s\n", mysql_error(conn));
	  		mysql_close(conn);
	  		return NULL;
		}
	
		res = mysql_store_result(conn);
		if (res == NULL){
			mysql_close(conn);
		    return NULL;
    	}

		while(row = mysql_fetch_row(res)){
		
			head = addNewEdge( (row[0] ? row[0] : "NULL"), (row[1] ? row[1] : "NULL"), atoi(row[2]), atoi(row[3]), atoi(row[4]), (row[5] ? row[5] : "NULL"), head);
			//printf("%s ", row[i] ? row[i] : "NULL");		
			// atoi: 2,3,4 int converting
   		
 		}
 		//printf("Entries of the table edges are added to the linked list for a 1 color\n");

		mysql_free_result(res);
	}
	
	mysql_close(conn);

 	return head;
}

void displaySortedEdgesLL(struct edge* h){
	//create a pointer variable to loop through the linked list
	struct edge* loop = NULL;
	loop = h;
	printf("\n| Lec_id | Mod_id | Col_id | Batch_id | T-slot | Room_id |\n");
	while(loop!=NULL){
  		printf("| %s, %s, %d, %d, %d, %s |", (*loop).lecid, (*loop).modid, (*loop).color_id, (*loop).batch, (*loop).timeslot, (*loop).roomid); printf("\n"); //printf(" %p |-->", (*loop).link);
  		loop=(*loop).link; 
    }
  	//printf("NULL\n");
}

// A Function to assign timeslot for the linked list of edges (and allocating batches, resolving conflicts). Returns timeslots count
int assignTimeSlots(struct edge* sortedEdgesLL_head, int maxColors){
	
	struct edge* loop = NULL;
	loop = sortedEdgesLL_head;
//4) Set 1 for the time slot Ts
	int timeslot = 1;
	int lastTs = 0; // id of the last timeslot in the timeslots list.
	int slot_jump = 0; // for adding new timeslots beyond the no. of colors (using when same batch has multiple edges with same color) 
	int repeat_count = 0; // for counting the times repeating the same batch inside the same color edges set.
	int max_repeats =0; // maximum repeats of the same batch regarding a specific color.
	int col_id = 0;
	int batch = 0;
	int first_item = 1;
	
//5) For all edges Ei in E
	while(loop!=NULL){
		
		if (first_item){   //	5.1. If the edge is E1, then
			(*loop).timeslot = timeslot;  // 5.1.1. Set Ts(=1) for the timeslot of E1 
			if( (*loop).timeslot>lastTs ) lastTs=(*loop).timeslot; // updating the last timeslot
			col_id = (*loop).color_id;  // 5.1.2. Set Color id of E1 as ColorId
			//batch = (*loop).batch;  // 5.1.3. Set batch of E1 as the batch
		}
  		
  		else if (col_id==(*loop).color_id) {    // 5.2. Else if the Color_id of Ei is ColorId, then
  			if (batch==(*loop).batch) {   // 5.2.1. If the batch of Ei is batch (same batch)
  				repeat_count++;
				(*loop).timeslot = maxColors+slot_jump+repeat_count;  // 5.2.1.1. Set Ts+1 for the timeslot of Ei (to avoid same batch conflicts)
				if( (*loop).timeslot>lastTs ) lastTs=(*loop).timeslot; // updating the last timeslot
				if (repeat_count>max_repeats) max_repeats = repeat_count;
			}
			else {    // 5.2.2 Else (different batch from the previous)
				repeat_count = 0;
				(*loop).timeslot = timeslot;  // 5.2.2.1.1. Set the current Ts as the timeslot of Ei
				if( (*loop).timeslot>lastTs ) lastTs=(*loop).timeslot; // updating the last timeslot
				//batch = (*loop).batch; //  5.2.2.2.2. Set batch of Ei as the batch
			}
		}
		
		else if (col_id!=(*loop).color_id) {   //	5.3. Else if the Color id of Ei is not the ColorId, then	
			slot_jump = slot_jump + max_repeats; // so the next Ts allocation for a repeating batch will be onto a new slot (since new color set)
			repeat_count = 0; max_repeats = 0;
			col_id = (*loop).color_id;  // 5.3.1. Set Color_id of Ei as ColorId
			timeslot++; // new color => new timeslot
			(*loop).timeslot = timeslot;  // 5.3.2. Set Ts as the timeslot of Ei 
			if( (*loop).timeslot>lastTs ) lastTs=(*loop).timeslot; // updating the last timeslot
			//batch = (*loop).batch; //  5.3.3. Set batch of Ei as the batch
		}   
		
		batch = (*loop).batch;  // 5.4. Set batch of Ei as the batch
  		
  		first_item = 0;
		loop=(*loop).link; //1. Select the next edge and repeat step 5
    }

	// 2. End	Returning the maximum timeslot id
	return lastTs;
} 

// A function to sort the edges LL by the timeslot
int sortEdgesLLbyTs(struct edge* head) {
    struct edge* current = NULL;
    struct edge* index = NULL;

    char temp_lecid[8]; // assigned lecturer's id for the module
	char temp_modid[8]; // module id (tag)
  	int temp_color_id = 0;; // color of the edge
  	int temp_batch = 0;; // batch No. which the subject belongs
  	int temp_timeslot = 0; // timeslot No. which the edge will be assigned
  	char temp_roomid[8]; // classroom id (tag)

    if (head == NULL) {
        return 0;
    }

    for (current = head; current->link != NULL; current = current->link) {
        for (index = current->link; index != NULL; index = index->link) {
            if (current->timeslot > index->timeslot) {
                
                strcpy(temp_lecid, current->lecid);
                strcpy(temp_modid, current->modid);
                temp_color_id = current->color_id;
                temp_batch = current->batch;
                temp_timeslot = current->timeslot;
                strcpy(temp_roomid, current->roomid);
                
                //current->data = index->data;
                strcpy(current->lecid, index->lecid);
                strcpy(current->modid, index->modid);
                current->color_id = index->color_id;
                current->batch = index->batch;
                current->timeslot = index->timeslot;
                strcpy(current->roomid, index->roomid);
                
                //index->data = tempData;
                strcpy(index->lecid, temp_lecid);
                strcpy(index->modid, temp_modid);
                index->color_id = temp_color_id;
                index->batch = temp_batch;
                index->timeslot = temp_timeslot;
                strcpy(index->roomid, temp_roomid);
            }
        }
    }
    
    return 1;
}    

// A function to add edges to the linked list of edges. (alocating lecturers, conflict free)
struct classroom* addNewClassroom(char roomid2[], int roomno2, int capacity2, struct classroom* h){
	
	//create a pointer variable to loop through the linked list
	struct classroom* loop=NULL;
	//create a pointer variable to keep the end node of the linked list
	struct classroom* prev=NULL;
	
 	//create new pointer to point to a "new block" of memory that can hold a struct node
    struct classroom* new=malloc(sizeof(struct classroom));
  
    //set data and the link    
    strcpy((*new).roomid, roomid2);
    (*new).roomno = roomno2; //printf("\nnew's batch: %d\n", (*new).batch);
    (*new).capacity = capacity2; 
    (*new).link=NULL; //printf("\nnew's link: %p\n", (*new).link);
  
    //check for head node(=if there are no nodes in the list)
	if(h==NULL){
		h=new; 
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

// A function to get classrom details to a linked list from DB
struct classroom* getClassroomData(struct classroom* classroomsLL_head){
	
	MYSQL* conn;
	MYSQL_RES* res;
	MYSQL_ROW row;
	conn = connectDB();
	
	struct classroom* head = classroomsLL_head;
	
	//char queryStr[200]; 
	//sprintf(queryStr, "SELECT room_id, room_no, capacity FROM classrooms ORDER BY capacity");
	//printf("\n%s\n", queryStr);
	
	/* send SQL query */
	if (mysql_query(conn, "SELECT room_id, room_no, capacity FROM classrooms ORDER BY capacity")){
	 	printf("Failed to execute query. Error: %s\n", mysql_error(conn));
	  	mysql_close(conn);
	  	return NULL;
	}
	
	res = mysql_store_result(conn);
	if (res == NULL){
		mysql_close(conn);
		return NULL;
    }

	while(row = mysql_fetch_row(res)){
		
		head = addNewClassroom( (row[0] ? row[0] : "NULL"), atoi(row[1]), atoi(row[2]), head);
		//printf("%s ", row[i] ? row[i] : "NULL");		
		// atoi: int converting
   		
 	}
 	//printf("Entries of the table classroom are added to the linked list\n");

	mysql_free_result(res);
	mysql_close(conn);

 	return head;
}

void displayClassroomsLL(struct classroom* h){
	//create a pointer variable to loop through the linked list
	struct classroom* loop = NULL;
	loop = h;
	printf("\n| Room_id | Room_no (unique) | Capacity |\n");
	while(loop!=NULL){
  		printf("| %s, %d, %d |", (*loop).roomid, (*loop).roomno, (*loop).capacity); printf("\n"); //printf(" %p |-->", (*loop).link);
  		loop=(*loop).link; 
    }
  	//printf("NULL\n");
}

// A Function to assign classrooms for the linked list of edges (and allocating classrooms, conflict free)
//int assignClassrooms(struct edge* sortedEdgesLL_head, struct classroom* classroomsLL_head){ // LL has to be sorted by the timeslot
//	
//	struct edge* loop = NULL;
//	loop = sortedEdgesLL_head;
//	
//	struct classroom* roomsLL_head = classroomsLL_head; // original list of classrooms. cantains all.
//	struct classroom* copyOfclassroomsLL_head = NULL;
//	//copyOfclassroomsLL_head = copyLL(classroomsLL_head); // making a copy of entire classrooms list.
//	
//	int current_timeslot = -1;
//	int student_count = 0;
//	
//	// For all edges
//	while(loop!=NULL){
//		
//		// get the current timeslot of the edge // if its a new time slot,
//		if( (*loop).timeslot!=current_timeslot ){ // timeslot change
//			free(copyOfclassroomsLL_head);
//			copyOfclassroomsLL_head = copyLL(roomsLL_head); // making a copy of entire classrooms list.
//		}
//		current_timeslot = (*loop).timeslot; // update current_timeslot
//		
//		student_count = getNoStudents( (*loop).batch ); // get the number of students of the batch from DB.
//		struct classroom* bestRoom = chooseClassroom(student_count, copyOfclassroomsLL_head);// get the classroom id which has the just enough capacity.
//		if (bestRoom!=NULL){ // A classroom found
//			strcpy((*loop).roomid, (*bestRoom).roomid); // assign roomid to the edge.
//			// remove that classroom node from the copyOfclassroomsLL.
//			copyOfclassroomsLL_head = removeClassroomNode(copyOfclassroomsLL_head, (*bestRoom).roomno);
//			
//		} else strcpy((*loop).roomid, "UA");  // if there is no classrooms, assign "UA" // send to create a new timeslot // add the cost of extening hours	
//		
//
//		loop=(*loop).link; //1. Select the next edge and repeat step 5
//    }
//
//	free(copyOfclassroomsLL_head);
//	return 1;
//} 

// A Function to assign classrooms for the linked list of edges (and allocating classrooms, conflict free)
//int assignClassroomsRec(struct edge* sortedEdgesLL_head, struct edge* dupli_edgesLL_head, struct classroom* classroomsLL_head, int ts_count, int firstcall){ // LL has to be sorted by the timeslot
//	
//	struct edge* loop = NULL;
//	loop = sortedEdgesLL_head;
//	
//	struct edge* dup_edgesLL_head = dupli_edgesLL_head;
//	
//	struct classroom* roomsLL_head = classroomsLL_head; // original list of classrooms. cantains all.
//	struct classroom* copyOfclassroomsLL_head = NULL;
//	//copyOfclassroomsLL_head = copyLL(classroomsLL_head); // making a copy of entire classrooms list.
//	
//	int current_timeslot = -1;
//	int lastTs = ts_count; // current no. of timeslots
//	int student_count = 0;
//	
//	// For all edges
//	while(loop!=NULL){
//		
//		// get the current timeslot of the edge // if its a new time slot,
//		if( (*loop).timeslot!=current_timeslot ){ // timeslot change
//			deleteLL(&copyOfclassroomsLL_head);
//			free(copyOfclassroomsLL_head);
//			copyOfclassroomsLL_head = copyLL(roomsLL_head); // making a copy of entire classrooms list.
//		}
//		current_timeslot = (*loop).timeslot; // update current_timeslot
//		
//		student_count = getNoStudents( (*loop).batch ); // get the number of students of the batch from DB.
//		struct classroom* bestRoom = chooseClassroom(student_count, copyOfclassroomsLL_head);// get the classroom id which has the just enough capacity.
//		if (bestRoom!=NULL){ // A classroom found
//			strcpy((*loop).roomid, (*bestRoom).roomid); // assign roomid to the edge.
//			if ((*loop).timeslot>lastTs) lastTs = (*loop).timeslot;
//			// remove that classroom node from the copyOfclassroomsLL.
//			copyOfclassroomsLL_head = removeClassroomNode(copyOfclassroomsLL_head, (*bestRoom).roomno);
//			
//		} 
//		else {
//			strcpy((*loop).roomid, "UA");  // if there is no classrooms, assign "UA" // send to create a new timeslot // add the cost of extening hours	
//			addNewEdge((*loop).lecid, (*loop).modid, (*loop).color_id, (*loop).batch, (lastTs + (*loop).timeslot), (*loop).roomid, dup_edgesLL_head);
//		}
//		
//		
//
//		loop=(*loop).link; //1. Select the next edge and repeat step 5
//    }
//	
//	deleteLL(&copyOfclassroomsLL_head);
//	free(copyOfclassroomsLL_head);
//	
//	if (dup_edgesLL_head!=NULL){
//		lastTs = assignClassroomsRec(dup_edgesLL_head, dup_edgesLL_head, roomsLL_head, lastTs, 0);
//	}
//	return lastTs;
//} 


// A Function to assign classrooms for the linked list of edges (and allocating classrooms, conflict free) // Returns updated total timeslots count
int assignClassrooms(struct edge* sortedEdgesLL_head, struct classroom* classroomsLL_head, int ts_count){ // LL has to be sorted by the timeslot
	
	struct edge* loop = NULL;
	loop = sortedEdgesLL_head;
	
	struct classroom* roomsLL_head = classroomsLL_head; // original list of classrooms. cantains all.
	struct classroom* copyOfclassroomsLL_head = NULL;
	//copyOfclassroomsLL_head = copyLL(classroomsLL_head); // making a copy of entire classrooms list.
	
	int current_timeslot = -1;
	int lastTs = ts_count; // current no. of timeslots
	int student_count = 0;
	
	// For all edges
	while(loop!=NULL){
		
		// get the current timeslot of the edge // if its a new time slot,
		if( (*loop).timeslot!=current_timeslot ){ // timeslot change
			deleteLL(&copyOfclassroomsLL_head);
			free(copyOfclassroomsLL_head);
			copyOfclassroomsLL_head = copyLL(roomsLL_head); // making a copy of entire classrooms list.
		}
		current_timeslot = (*loop).timeslot; // update current_timeslot
		
		student_count = getNoStudents( (*loop).batch ); // get the number of students of the batch from DB.
		struct classroom* bestRoom = chooseClassroom(student_count, copyOfclassroomsLL_head); // get the classroom id which has the just enough capacity.
		if (bestRoom!=NULL){ // A classroom found
			strcpy((*loop).roomid, (*bestRoom).roomid); // assign roomid to the edge.
			// remove that classroom node from the copyOfclassroomsLL.
			copyOfclassroomsLL_head = removeClassroomNode(copyOfclassroomsLL_head, (*bestRoom).roomno);
			
		} else { // no classrooms available OR no classrooms with required capacity (if this the case, user must seperate the batch in to 2 from front end beforehand so at least 1 classromm has the enough capacity for the batch).
			bestRoom = chooseClassroom(student_count, roomsLL_head);  // get the classroom id for use with a new timeslot
			if (bestRoom!=NULL){  // not enough classrooms to use with the original timeslot, so new timeslot
				strcpy((*loop).roomid, (*bestRoom).roomid);
				(*loop).timeslot = lastTs+1;
				lastTs++;
				totalCost = totalCost + costIncr; // adding the cost of extening hours (extra timeslot).
			} 
			else {		// no classrooms with required capacity
				strcpy((*loop).roomid, "UA-NEC");  // if there is no classrooms, assign "Un-Assigned - Not Enough Capacity" 
				totalCost = totalCost + newRoomCost; // require additional classroom.
			}
			
			//addNewEdge((*loop).lecid, (*loop).modid, (*loop).color_id, (*loop).batch, (*loop).timeslot, (*loop).roomid[], dup_edgesLL_head);
		}
		

		loop=(*loop).link; //1. Select the next edge and repeat step 5
    }

	deleteLL(&copyOfclassroomsLL_head);
	free(copyOfclassroomsLL_head);
	return lastTs;
} 

// A function to create a copy of a classrooms linked list
struct classroom* copyLL(struct classroom* head){
    if (head == NULL) {
        return NULL;
    }
    else {
  
        // Allocate the memory for new Node
        struct classroom* newNode = (struct classroom*)malloc(sizeof(struct classroom));
  
        //newNode->data = head->data;
        strcpy((*newNode).roomid, (*head).roomid);
    	(*newNode).roomno = (*head).roomno; 
    	(*newNode).capacity = (*head).capacity;
  
        // Recursively set the next pointer of the new Node by recurring for the remaining nodes
        newNode->link = copyLL(head->link);
  
        return newNode;
    }
}

// A function to get the number of students of a batch from DB.
int getNoStudents(int batch){
	
	MYSQL* conn;
	MYSQL_RES* res;
	MYSQL_ROW row;
	conn = connectDB();
	
	char queryStr[200]; 
	int studentCount = 0;
	
	sprintf(queryStr, "SELECT no_students FROM batches WHERE batch_id = %d", batch);
	//printf("\n%s\n", queryStr);
	
	/* send SQL query */
	if (mysql_query(conn, queryStr)){
	 	printf("Failed to execute query. Error: %s\n", mysql_error(conn));
	  	mysql_close(conn);
	  	return 0;
	}
	
	res = mysql_store_result(conn);
	if (res == NULL){
		mysql_close(conn);
	    return 0;
    }

	while(row = mysql_fetch_row(res)){
		
		studentCount = atoi(row[0]);
		//printf("%s ", row[i] ? row[i] : "NULL");		
		// atoi: int converting
 	}
 	//printf("Number of students of the batch is retrived from the DB\n");

	mysql_free_result(res);
	mysql_close(conn);

 	return studentCount;
}

// Function to choose the best classroom for a particular edge, returns a pointer to the best classroom
struct classroom* chooseClassroom(int student_count, struct classroom* classroomListCopy_head) {
    
    struct classroom* classroom_loop_node = NULL; 
    classroom_loop_node = classroomListCopy_head;
	struct classroom* best_classroom = NULL; 
    
    //Iterate through all classrooms sorted by the capacity in ascending order
    while(classroom_loop_node!=NULL) {

        //Check if current classroom has just enough capacity
        if( classroom_loop_node->capacity >= student_count) {
            best_classroom = classroom_loop_node;
            break;
        }
        
        classroom_loop_node = classroom_loop_node->link;
    }
    
    return best_classroom;
}

// A function to remove a classroom node from the classrooms LL
struct classroom* removeClassroomNode(struct classroom* copyOfclassroomsLL_head, int roomno2){
	struct classroom* head = copyOfclassroomsLL_head;
	struct classroom* temp = copyOfclassroomsLL_head;
	struct classroom* prev = copyOfclassroomsLL_head;
	
    if (temp!=NULL && temp->roomno == roomno2) { // head is removing
        head = temp->link;
        free(temp);
        return head;
    }

    while (temp!=NULL && temp->roomno != roomno2) {
        prev = temp;
        temp = temp->link;
    }

    if (temp == NULL) return head; // no matching node found in the entire LL.
    prev->link = temp->link;
    free(temp);
    return head; // head of the updated LL
}

void deleteLL(struct classroom** head_ref){
   /* deref head_ref to get the real head */
   struct classroom* current = *head_ref;
   struct classroom* next;
 
   while (current != NULL){
       next = current->link;
       free(current);
       current = next;
   }
   
   /* deref head_ref to affect the real head back
      in the caller. */
   *head_ref = NULL;
}