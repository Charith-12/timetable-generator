
#include <stdio.h>
#include <string.h>
#include <math.h> // foe ceil
#include <stdlib.h> //for malloc
#include <time.h> //for getting the day difference

int lecWL = 8; //lecturer's max workload in hours
int breakDur = 1; //break duration in hours
int maxOpDays = 4;
int maxsSlotsPerDay = 3; // based on operating hours
char* dayOfTheWeek[] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
int starting_day;
int sem_total_days, sem_total_days_req, sem_total_weeks;
//int slotsTotal = 0; // total number of timeslots required for a week for particular batch


//structure to hold each module
struct module{
  char modid[8]; //module id (tag)
  int noc; //number of credits
  char lecid[8]; //assigned lecturer's id for the module
  struct module* link;
};

//structure to hold a batch
struct batch{
  struct module* modules; // for modules list
  int slotsTotal; // total number of timeslots required for a week, for particular batch
};

//structure to hold each time-slot in the timetable/graph
struct node{
  int filled;
  struct module* occupiedBy;
  int day;
  struct node* link;
};

// structure to hold the timetable
struct timetable{
    int V; // number of vertices in graph = no. of total timeslots
    struct node* nodesList;
};

// <<<<<<<< dou
//structure to hold each time-slot in the timetable
struct timeslot{
  int filled;
  struct module* occupiedBy;
  int day;
  int week;
  int snum;
  struct timeslot* link;
};

// structure to hold the timetable
struct slotsList{
    int V; // number of total timeslots
    struct timeslot* timeslotsList;
};
// <<<<<<<< dou

//structure to hold each time-slot in the timetable
struct time_slot{
  int filled;
  struct module* occupiedBy;
  int day;
  int week;
  int snum;
};


struct module* insertModules(char modid2[], int noc2, char lecid2[], struct module* h); // function prototype for inserting a new node to the modules linked list
struct batch loadBatch(char fileName[]); // function prototype for loading modules list from a txt file to a linked list
void displayModulesLL(struct module* h); // function prototype for displaying the modules linked list
struct node* insert(int d, int s, struct node* h); // function prototype for adding nodes to the linked list of nodes (tt)
struct timetable* createTimetableSlots(int V); // function prototype for creating an empty linked list of struct nodes. Length of LL (V) = no. of total possible timeslots 
void displayTtNodesLL(struct timetable* tt); // function prototype for displaying the nodes linked list (timetable)
int getWeekday(int d, int m, int y); // function prototype for getting the weekday of a given date. 		i- DD-MM-YYYY	o- 0=Sunday, 1=Monday...
int valid_date(int day, int mon, int year); // function prototype for checking whether a date is valid or not
int getDayDiff(int dd1, int mm1, int yyyy1, int dd2, int mm2, int yyyy2); // function prototype for calculating no. of days between two dates.
struct time_slot* createTimeslot(int w, int d, int n, int f); // function prototype for creating a timeslot.
void addEmptyTimeslots2Arrray(int sem_total_weeks, int sem_total_days, int start_day, struct time_slot* timeslotsArray[sem_total_weeks][7][24]); // function prototype for populating the 3D array with empty timeslots
int addHolidays(char fileName[], struct time_slot* timeslotsArray[sem_total_weeks][7][24], int sem_total_days, int sem_total_days_req, int sd, int sm, int sy); // function prototype for reading holidays.txt and add holidays accordingly.
void displayTimeslotsArray(struct time_slot* timeslotsArray[sem_total_weeks][7][24], int sem_total_weeks);  // function prototype for displaying the 3D array of timeslots. 


int main(){
 
  int sd,sm,sy, ed,em,ey;
  
  // getting starting date input
  while(!valid_date(sd, sm, sy)){
  	printf("\n Please enter the semester starting date (DD-MM-YYYY): ");
  	scanf("%d-%d-%d", &sd, &sm, &sy);
  	if(!valid_date(sd, sm, sy)){
  		printf("\n Please enter a valid date!");
	  } 
  }
  printf("\n Semester starting date (DD MM YY): %d %d %d", sd, sm, sy);
  starting_day = getWeekday(sd, sm, sy); // staring day of the week
  printf("\n Semester starting day of the week: %s", dayOfTheWeek[starting_day]);
  
  // getting ending date input
  while(!valid_date(ed, em, ey)){
  	printf("\n\n Please enter the semester ending date (not including) (DD-MM-YYYY): ");
    scanf("%d-%d-%d", &ed, &em, &ey);
    if(!valid_date(ed, em, ey)){
  		printf("\n Please enter a valid date!");
	  } 
  }
  printf("\n Semester ending date (DD MM YY): %d %d %d", ed, em, ey);
  printf("\n Semester ending day of the week: %s", dayOfTheWeek[getWeekday(ed, em, ey)]);
  
  // calculating total no. of days in the semester.
  sem_total_days = getDayDiff(sd,sm,sy,ed,em,ey);
  if(sem_total_days<=0){  // if ending date < starting date
  	printf("\n\n Date error! Please enter valid starting & ending dates!"); 
  	return 0;
  }
  printf("\n\n Number of days between two days: %d", sem_total_days );
  sem_total_days_req = sem_total_days + (starting_day==0? 6: starting_day-1); // when starting day is in mid-week (not a Monday), consider that full week by adding the no. of days from the monday to that starting day.
  printf("\n Number of days to be considered: %d", sem_total_days_req );
  sem_total_weeks = ceil((sem_total_days_req/7.0f));  // calculating the no. of weeks that has to consider in the timetable. (considered the case when starting and ending dates are in mid-wwek.)
  printf("\n\n Number of weeks: %d", sem_total_weeks );
  
  // creating the array to hold timeslots
  printf("\n\n\n Creating the array to hold timeslots...");
  struct time_slot* timeslotsArray[sem_total_weeks][7][24];
  printf("\n Adding empty timeslots to the array...");
  addEmptyTimeslots2Arrray(sem_total_weeks, sem_total_days, starting_day, timeslotsArray);
  
  // Reading holidaays.txt and updating holidays
  printf("\n\n Reading holidaays.txt and updating holidays...");
  if(addHolidays("holidays.txt", timeslotsArray, sem_total_days, sem_total_days_req, sd, sm, sy)==0){
  	printf("\n Holidaays updated successfully!");
  }
  
  // Displaying the timeslots of the semester
  printf("\n\n Displaying all the timeslots...");
  displayTimeslotsArray(timeslotsArray, sem_total_weeks);

  // calculate the total no. of slots (V), weeks, days  > -- ok
  // create empty slots ll add day, week...  > -- ok
  // get holidays.txt and config those days  > -- ok
  // display ll 	with week no., day, slot 1,2...  > -- ok
	
  getchar();
  getchar();
  getchar();
  
  struct batch batchOne = loadBatch("modules.txt"); // TODO: Handling multiple batches
  
  //displaying the modules linked list
  printf("modules.txt data loaded to a linked list.\n Modules linked list for the batch as follows,\n\n");
	displayModulesLL(batchOne.modules);
	
  // Calculating the total slot requirement for all added batches.
  int totalSlotReq = batchOne.slotsTotal; // just substituting for now 
    printf("\n Total timeslot requirement for all batches : %d \n\n", totalSlotReq);
  
  // Calculating the max possible no. of timeslots in the timetable based on constraints.
  int maxTtTimeSlots = maxOpDays*maxsSlotsPerDay;
  
  // checking whether tt generation is possible.
  if (maxTtTimeSlots < totalSlotReq) printf("\n Error!!! Total timeslot requirement exceeds the possible no. of timeslots.\n\n"); // TODO: Fix this. maybe handle this while allocating. 
  else{
  	
  	printf("\n\n - Creating the empty timeslots of timetable... \n");
  	
  	// creating the empty timetable 
  	int V = maxTtTimeSlots;  // TODO: we need more slots than the requirement(and maybe even more than the max possible no.) when allocating breaks inbetween.
  	struct timetable* emptyTimetable = createTimetableSlots(V);
  	
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
	int lecWLCount=0; 
	int needBreak = 0; 
	
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
struct node* insert(int d, int s, struct node* h){
	//create a pointer variable to loop through the linked list
	struct node* loop=NULL;
	
	//create a pointer variable to keep the end node of the linked list
	struct node* prev=NULL;
	
  //create new pointer to point to a "new block" of memory that can hold a struct node
  struct node* new=malloc(sizeof(struct node));
  
  //set data and the link
  (*new).filled=s; //printf("\nnew's data: %d\n", (*new).data);  
  (*new).day=d;
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
	int d=1;
	int count=0;
	int i=0;
	for (i=0; i < V; ++i){
		count++;
		if(count>maxsSlotsPerDay){
			d++;
			count=0;
		}
		head=insert(d, 0, head);
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
	//int d=1;
	//int count=0;
	//printf("\n Monday");
	while(loop!=NULL){
		
		{
/*		count++;
		if(count>maxsSlotsPerDay){
			d++;
			count=0;
			if(d<8){
				if( d == 2 ) printf("\n Tuesday");
				if( d == 3 ) printf("\n Wednesday");
				if( d == 4 ) printf("\n Thursday");
				if( d == 5 ) printf("\n Friday");
				if( d == 6 ) printf("\n Saturday");
				if( d == 7 ) printf("\n Sunday");
			}
		}	
*/		}
				
		printf("\n Is this timeslot filled? %d. It has - ", ((*loop).filled));
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

int getWeekday(int d, int m, int y){
	
	return (d += m < 3 ? y-- : y - 2, 23*m/9 + d + 4 + y/4- y/100 + y/400)%7; 
}

// function to check whether a date is valid or not
int valid_date(int day, int mon, int year){
    int is_valid = 1, is_leap = 0;

    if (year >= 1800 && year <= 9999) 
    {

        //  check whether year is a leap year
        if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) 
        {
            is_leap = 1;
        }

        // check whether mon is between 1 and 12
        if(mon >= 1 && mon <= 12)
        {
            // check for days in feb
            if (mon == 2)
            {
                if (is_leap && day == 29) 
                {
                    is_valid = 1;
                }
                else if(day > 28) 
                {
                    is_valid = 0;
                }
            }

            // check for days in April, June, September and November
            else if (mon == 4 || mon == 6 || mon == 9 || mon == 11) 
            {
                if (day > 30)
                {
                    is_valid = 0;
                }
            }

            // check for days in rest of the months 
            // i.e Jan, Mar, May, July, Aug, Oct, Dec
            else if(day > 31)
            {            
                is_valid = 0;
            }        
        }

        else
        {
            is_valid = 0;
        }

    }
    else
    {
        is_valid = 0;
    }

    return is_valid;

}

// function to calculate no. of days between two dates.
int getDayDiff(int dd1, int mm1, int yyyy1, int dd2, int mm2, int yyyy2){
	time_t t1, t2;
	int day_diff;
  	t1 = mktime(&(struct tm){ .tm_mday=dd1, .tm_mon=mm1-1, .tm_year=yyyy1-1900 });
  	t2 = mktime(&(struct tm){ .tm_mday=dd2, .tm_mon=mm2-1, .tm_year=yyyy2-1900 });
  	day_diff = (t2 - t1) / 24 / 60 / 60;    // make days from seconds
	
	return day_diff;
}

//--   Dou <<<<<<<<<<<<<<<<<
// A function to add timeslot nodes to the linked list of timeslots
struct timeslot* insertTimeslot(int w, int d, int n, int f, struct timeslot* h){
	//create a pointer variable to loop through the linked list
	struct timeslot* loop=NULL;
	
	//create a pointer variable to keep the end node of the linked list
	struct timeslot* prev=NULL;
	
  //create new pointer to point to a "new block" of memory that can hold a struct node
  struct timeslot* new=malloc(sizeof(struct timeslot));
  
  //set data and the link
  (*new).week=w;
  (*new).day=d;
  (*new).snum=n;
  (*new).filled=f; 
  (*new).occupiedBy=NULL; 
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

// A function for creating an empty linked list of struct timeslots. Length of LL (V) = no. of total possible timeslots. 
struct slotsList* createTimeslots(int sem_days, int sem_weeks, int day){

	struct slotsList* new=malloc(sizeof(struct slotsList));
	//struct slotsList* tt = (struct slotsList*)malloc(sizeof(struct slotsList));
	
	struct timeslot* head=NULL;
	
	// creating the linked list
	int w, i, n;
	int d=day;
	
//	for (w=1; w <= sem_weeks; ++w){
//		for ()
//		count++;
//		if(count>maxsSlotsPerDay){
//			d++;
//			count=0;
//		}
//		head=insertTimeslot(w, d, n, 0, head);
//	}
//	
//	int count=0;
//	for (i=0; i < V; ++i){
//		count++;
//		if(count>maxsSlotsPerDay){
//			d++;
//			count=0;
//		}
//		head=insertTimeslot(d, 0, head);
//	}
	
	// asigining the empty linked list to the nodesList
	(*new).timeslotsList=head;
	(*new).V = sem_days*24;
	
	return new;
}
//--   Dou <<<<<<<<<<<<<<<<<<

// A function to create a timeslot.
struct time_slot* createTimeslot(int w, int d, int n, int f){
	
  //create new pointer to point to a "new block" of memory that can hold a struct node
  struct time_slot* new=malloc(sizeof(struct time_slot));
  
  //set data and the link
  (*new).week=w;
  (*new).day=d;
  (*new).snum=n;
  (*new).filled=f; 
  (*new).occupiedBy=NULL; 
	
  return new;
}

// A function to add empty timeslots to the array 
void addEmptyTimeslots2Arrray(int sem_total_weeks, int sem_total_days, int start_day, struct time_slot* timeslotsArray[sem_total_weeks][7][24]){
	
	//struct time_slot* timeslotsArray[sem_total_weeks][7][24];

	int w, d, s, daycount, skipday=0;
	
	if(start_day!=1){ // not Monday
		if(start_day==0){ // Sunday
			skipday=6;
		}else skipday=start_day-1;
	}
	
	// week
	for(w=0; w<sem_total_weeks; w++){
		// day of the week. d=0 means Monday
		for(d=0; d<7; d++){
			
			if(skipday>0){  // previous days of the week which are not relevant.
				for(s=0; s<24; s++){
					timeslotsArray[w][d][s]=NULL;
				}
				skipday--;
			}
			else if(daycount>=sem_total_days){ // left-off days of the last week
				for(s=0; s<24; s++){
					timeslotsArray[w][d][s]=NULL;
				}
			}
			else{
				// timeslots of a day (0-23)
				for(s=0; s<24; s++){
				timeslotsArray[w][d][s]=createTimeslot(w+1, (d==6? 0: d+1), s+1, 0);
				}
				daycount++;
			}	
		}
	}
	
}

// Function to read holidays.txt and modify relevent timeslots as holidays accordingly.
int addHolidays(char fileName[], struct time_slot* timeslotsArray[sem_total_weeks][7][24], int sem_total_days, int sem_total_days_req, int sd, int sm, int sy){
	FILE* fp2=NULL; //file with list of holiday dates
    
  	//read the holidays.txt
  	if((fp2=fopen(("%s", fileName), "r"))==NULL){
  		printf("\nFile Error!\n");
  		return -1;
	  } 
    
  	int dd, mm, yyyy, line[12];

  	while(fgets(line, sizeof(line), fp2)){
  		
     	if(3 == sscanf(line, "%10d%10d%10d", &dd, &mm, &yyyy))
      		printf("\n%d, %d, %d", dd, mm, yyyy);
       	   
       	if(valid_date(dd, mm, yyyy)){
       		// get the day diff. from semester starting day
       		int day_diff = getDayDiff(sd,sm,sy,dd,mm,yyyy);
       		if(0 <= day_diff <= sem_total_days){   // if diff (-) ignore, if (+), diff<sem_total_days (with in the semster's time period.)
       			
       			// calculating the week no. from days.
       			int weekno = (day_diff+(sem_total_days_req-sem_total_days))/7;  // add dummy days to the day diff
       			// getting the day of the week from the remainder.
       			int dayno = (day_diff+(sem_total_days_req-sem_total_days))%7;
       			// setting those 24 slots of the day as holiday.
       			int s;
       			for(s=0; s<24; s++){
       				(*timeslotsArray[weekno][dayno][s]).filled=2;   				
				   }
       			
			   }
		}
 	}
    	
 	fclose(fp2);
 	 
 	return 0;
}

// A function to display the 3D array of timeslots 
void displayTimeslotsArray(struct time_slot* timeslotsArray[sem_total_weeks][7][24], int sem_total_weeks){
	
	printf("\n ~ Timetable ~");
	char* slot_status[] = {"   -   ", "filled ", "Holiday"};
	int w, d, s;
	for (w=0; w<sem_total_weeks; w++){
		getchar();
		printf("\n\n Week %d", w+1);
		printf("\n--------------------------------------------------------------");
		for(d=0; d<7; d++){
			printf("\n > %s\n", (d==6? dayOfTheWeek[0] : dayOfTheWeek[d+1]));
			for(s=0; s<24; s++){
				if(timeslotsArray[w][d][s]!=NULL){
					int slotnum=(*timeslotsArray[w][d][s]).snum;
					int status=(*timeslotsArray[w][d][s]).filled;
					printf(" | (%d) - %s", slotnum, slot_status[status]);
				}
				else {
					printf(" | unavailable");
				}
			}
			printf(" |\n");
		}
	}
}
