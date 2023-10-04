#include <stdio.h>
#include <stdlib.h> //for malloc
#include <time.h>
#include <string.h> // for strcpy
#include <mysql.h> //for database operations

#define POPULATION_SIZE 100 // Maximum number of individuals in a single generation
#define GENERATIONS 100
#define MUTATION_RATE 0.01
#define CROSSOVER_RATE 0.5
#define ELITISM_COUNT 2
#define COST_OF_A_VIOLATION 1

int ARRAY_SIZE = 0; // chromosome length of each individual (individual size)
int START_TIME = 9; // daily university starting hour.
int END_TIME = 17;
int NO_OF_DAYS = 5;

// For struct array that replicates the db(to avoid excessive db calls)
// p.lec_id, p.prohibitedTimeSlot, e.timeslot from prohibetedtimes p inner join edges e on e.lec_id = p.lec_id ORDER BY e.timeslot, p.lec_id, p.prohibitedTimeSlot
struct DbRecord {
    //char lecid[8];
	int prohibitedPosID;
	int timeslot;
  	struct DbRecord* link;
};

struct Individual {
    int* genes;
    int cost;
};

MYSQL* connectDB(); // function prototype for connecting to the database.

int getTimeslotCount();

// get start, end times from the DB and set.
void setStartEndTimes();

// Function to add new DbRecord to the linked list of DbRecords.
struct DbRecord* addNewDbRecordToLL(/*char lecid2[],*/ int prohibitedPosID2, int timeslot2, struct DbRecord* h);

// Function to get and populate DbRecords linked list.
struct DbRecord* getDbRecords(struct DbRecord* dbRecordsLL_head);

// createRandomIndividual(ARRAY_SIZE, int* availablePositions)
void createRandomIndividual(struct Individual* individual, int* availablePositions, int availablePosArraySize);

// Function to compare two individuals based on cost. // For qsort()
int compareCost(const void* a, const void* b);

// Function to get violations count for a one pos_id
int getTimeViolationsCount(struct DbRecord* dbRecordsLL_head, int timeslotNum, int positionID);

// Function to calculate the cost of an individual.
int calculateIndividualCost(struct DbRecord* dbRecordsLL_head, int* individualGenes);

// Function to swap the values of two given indexes in an individual's genes array. // Swap positions in the array (index1, index2)
void swapGenes(struct Individual* individual, int index1, int index2);

// Function to perform mutation on an individual.
void mutate(struct Individual* individualToMutate);

// mutatePopulation()
// select random index of population and repalce that individual with new randomly created individual. 
// if mutation being done for a few selected individuals in the population, replace entire array with new randomly generated individual(array).

// Function to select parents for reproduction.
int selectParent(int* costs);

// A function to put optimized timeslot-positionID pairs into the database.
int putOptimizedPositionsToDB(struct Individual* leastCostIndividual, char tablename[]);


int main(void) {
	srand(time(NULL)); //seeding
	
	int i = 0; int j = 0; int k = 0; int x = 0; int y = 0; int z = 0; int index = 0; int generation = 0;
  
	ARRAY_SIZE = getTimeslotCount();
	setStartEndTimes();
	if( END_TIME==0 ){
		END_TIME=24;
	} 
	
	int diff = ((END_TIME-START_TIME)*NO_OF_DAYS) - ARRAY_SIZE;
	if(diff<0) {
		printf("\n Need more operating hours to continue the algorithm.\n No. of operating hours is less than the No. of timeslots.\n");
		printf(" Required minimum open hours: %d\n A Minimum of %d more hours are required\n", ARRAY_SIZE, abs(diff));
		printf("\n\n (*) Increasing the operating hours by changing Start and End times. (*)\n");
		
		// setting new end and start times
		while( ((END_TIME-START_TIME)*NO_OF_DAYS) < ARRAY_SIZE ){
			if( (END_TIME<24) && (END_TIME>0) ){
				END_TIME++;
				printf("\n New end time: %d", END_TIME);
			}
			else if(START_TIME>=01){
				START_TIME--;
				printf("\n New start time: %d", START_TIME);
			}
			else if(NO_OF_DAYS<7){
				NO_OF_DAYS++;
				printf("\n New no of days: %d", NO_OF_DAYS);
			}	
		}
		
	}
	
//	struct Individual {
//		int genes[ARRAY_SIZE];
//    	int cost;   
//	};
	
	// Get data from DB to memory.
	struct DbRecord* dbRecordsLL_head = NULL;
	dbRecordsLL_head = getDbRecords(dbRecordsLL_head);
	
	// getting all valid timeslot-position-ids based on opening & closing time.
	int availablePosArraySize = (END_TIME-START_TIME)*NO_OF_DAYS;
	int availablePositions[availablePosArraySize];
	// populating availablePositions array. // Monday 9-10 AM -> 109, Friday 3-4 PM -> 515...
	index=0;
	for (i = 0; i < NO_OF_DAYS; i++){
		for (j = START_TIME; j<END_TIME; j++){
			availablePositions[index] = ((i+1)*100) + j;
			index++;
		}
	}
	
		// create gen-1 first population using available timeslot-position-numbers, ARRAY_SIZE, and a rondomizer. Make sure no duplicates with in an individual.
		// calculate cost of each individual(timetable slot arrangement) 
		// and sort the population in cost ascending order.
	// random parent2 selector method.
	// generation part with crossover.
		// mutation method.
	
	// send optimaum combination array to db.
	
	struct Individual population[POPULATION_SIZE];
	struct Individual* leastCostIndividual;
	
    // Initialize the population randomly and calculate costs.
    for (i = 0; i < POPULATION_SIZE; i++) {
        createRandomIndividual(&population[i], availablePositions, availablePosArraySize);
        population[i].cost = calculateIndividualCost(dbRecordsLL_head, population[i].genes);
    } 
    

    // Main loop for generations.
    for (generation = 0; generation < GENERATIONS; generation++) {
    	
    	// Sort the population and costs in ascending order of cost.
    	qsort(population, POPULATION_SIZE, sizeof(struct Individual), compareCost);
		leastCostIndividual = &population[0];
		
		printf("\n Generation: %d\n", generation+1);
		printf("  Least cost of an individual: %d\n", leastCostIndividual->cost);
		
		if(leastCostIndividual->cost == 0){
    		break;
		}
    	
        // Create a new population through selection and crossover.
        struct Individual newPopulation[POPULATION_SIZE];
        
        for (i = 0; i < POPULATION_SIZE; i++) {  // Individual
        	// if i>elitismCount??

            struct Individual parent1 = population[i]; 
        	struct Individual parent2 = population[rand() % (POPULATION_SIZE/2)]; // randomly select parent who also has less cost.
        	
        	// make a copy of parent2
        	int parent2genes[ARRAY_SIZE];
        	for (k = 0; k < ARRAY_SIZE; k++){
        		parent2genes[k] = parent2.genes[k];
			}
			
			int indexesOfDuplicates[ARRAY_SIZE];
			index = 0;
			for (k = 0; k < ARRAY_SIZE; k++){
				indexesOfDuplicates[k] = -1;
			}
			
			newPopulation[i].genes = malloc(sizeof(int) * ARRAY_SIZE);

            int crossoverPoint = ARRAY_SIZE/2; //rand() % ARRAY_SIZE;
            for (j = 0; j < ARRAY_SIZE; j++) {
                if (j < crossoverPoint /* Or rand() % 2 == 0*/) {
                    newPopulation[i].genes[j] = parent1.genes[j];                    
                } else {
                	
        			// Check if the value is already present in the child array.
        			int isDuplicate = 0;
        			for (k = 0; k < crossoverPoint; k++) {
         			   if (newPopulation[i].genes[k] == parent2genes[j]) {
         			       isDuplicate = 1;
         			       newPopulation[i].genes[j] = -2;
         			       //add index
         			       indexesOfDuplicates[index] = j;
         			       index++;
         			       break;
         			    }
       				}
                	
                	if(isDuplicate==0){
                		newPopulation[i].genes[j] = parent2genes[j]; // from parent2 modified copy.
					}
                    
                }
            }
            
            // Adding valid values to the indexes of duplicates
            k=0;
            while(indexesOfDuplicates[k] != -1){
            	// If it is a duplicate, find the next unique value from parent2.
            	int candidate = 0;
             	int isCandidateDuplicate = 0;
            	int nextUniqueValue = -1;
            	
            	for (y = 0; y < ARRAY_SIZE; y++) {
             	   candidate = parent2genes[y];
             	   isCandidateDuplicate = 0;
              	   for (z = 0; z < ARRAY_SIZE; z++) {
                	    if (newPopulation[i].genes[z] == candidate) {
                	    	isCandidateDuplicate = 1;
                       	 	break;
                    	}
                	}
                	if (!isCandidateDuplicate) {
                	    nextUniqueValue = candidate;
                	    break;
                	}
            	}

            	if (nextUniqueValue != -1) {
            	    newPopulation[i].genes[ (indexesOfDuplicates[k]) ] = nextUniqueValue;
            	} else {
            		printf("\n * error! * Not enough unique values in parent2 genes to create a valid child individual. Timeslots might overlap!\n");
				}
            	
            	k++;
			}
            
            mutate(&newPopulation[i]);
        }

        // Replace the old population with the new one.
        for (i = 0; i < POPULATION_SIZE; i++) {
            for (j = 0; j < ARRAY_SIZE; j++) {
                population[i].genes[j] = newPopulation[i].genes[j];
            }
            // new cost
            population[i].cost = calculateIndividualCost(dbRecordsLL_head, population[i].genes);
        }
        //free(newPopulation)
    }

	
    // Print the best individual and its cost.
    printf("\n Best Individual: ");
    for (i = 0; i < ARRAY_SIZE; i++) {
        printf("\n Timeslot %d -> positionID %d ", (i+1), population[0].genes[i]);
    }
    printf("\n\n Best Cost: %d\n", population[0].cost);
    
    if(putOptimizedPositionsToDB(leastCostIndividual, "optimizedpositions")) printf("\n\n ~ Optimized timeslot positions added to the database successfully! \n");
	
	return 0;
}
    


// ~~ RE: DB Operations ~~
// A function to connect to the database
MYSQL* connectDB(){
	
	MYSQL* con;
	
	char* server = "localhost";
	char* user = "cadevs";
	char* password = "P@ssword123"; /*password*/
	char* database = "university";
	
	con = mysql_init(NULL);
	
	/* Connect to database */
	if (!mysql_real_connect(con, server, user, password, database, 0, NULL, 0)){
	    printf("Failed to connect MySQL Server %s. Error: %s\n", server, mysql_error(con));
	    return NULL;
	}
	
	return con;
}

int getTimeslotCount(){
	
	MYSQL* conn;
	MYSQL_RES* res;
	MYSQL_ROW row;
	conn = connectDB();
	
	int timeslotCount = 0;
	//char queryStr[200];
	//sprintf(queryStr, "SELECT MAX(timeslot) FROM edges");
	//printf("\n%s\n", queryStr);
	
	/* send SQL query */
	if (mysql_query(conn, "SELECT MAX(timeslot) FROM edges")){
	 	printf("Failed to execute query to get timeslots count. Error: %s\n", mysql_error(conn));
	  	mysql_close(conn);
	  	return 0;
	}
	
	res = mysql_store_result(conn);
	if (res == NULL){
		mysql_close(conn);
	    return 0;
    }

	while(row = mysql_fetch_row(res)){
		
		timeslotCount = row[0] ? atoi(row[0]) : 0;	// atoi: int converting
 	}
 	//printf("Number of timeslots retrived from the DB\n");

	mysql_free_result(res);
	mysql_close(conn);

 	return timeslotCount;
}

// get start, end times from the DB and set.
void setStartEndTimes(){

	MYSQL* conn;
	MYSQL_RES* res;
	MYSQL_ROW row;
	conn = connectDB();
	
	//char queryStr[200];
	//sprintf(queryStr, "SELECT start_time, end_time FROM constraints");
	//printf("\n%s\n", queryStr);
	
	/* send SQL query */
	if (mysql_query(conn, "SELECT start_time, end_time, no_of_days FROM constraints")){
	 	printf("Failed to execute query to get start & end times. Error: %s\n", mysql_error(conn));
	  	mysql_close(conn);
	  	return;
	}
	
	res = mysql_store_result(conn);
	if (res == NULL){
		mysql_close(conn);
	    return;
    }

	while(row = mysql_fetch_row(res)){
		START_TIME = row[0] ? atoi(row[0]) : 9;
		END_TIME = row[1] ? atoi(row[1]) : 17;
		NO_OF_DAYS = row[2] ? atoi(row[2]) : 5;
 	}
 	printf("\n + Start & End times retrived from the DB\n");

	mysql_free_result(res);
	mysql_close(conn);

 	return;
}

// Function to add new DbRecord to the linked list of DbRecords.
struct DbRecord* addNewDbRecordToLL(/*char lecid2[],*/ int prohibitedPosID2, int timeslot2, struct DbRecord* h){
	
	struct DbRecord* loop=NULL;
	struct DbRecord* prev=NULL;
	
 	//create new pointer to point to a "new block" of memory.
    struct DbRecord* new=malloc(sizeof(struct DbRecord));
  
    //set data and the link

  	//strcpy((*new).lecid, lecid2);	// lecturer id
    (*new).prohibitedPosID = prohibitedPosID2; 
    (*new).timeslot = timeslot2;
    (*new).link=NULL;
  
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

// Function to get and populate DbRecords linked list.
struct DbRecord* getDbRecords(struct DbRecord* dbRecordsLL_head){
	
	MYSQL* conn;
	MYSQL_RES* res;
	MYSQL_ROW row;
	conn = connectDB();
	
	struct DbRecord* head = dbRecordsLL_head;
	
	//char queryStr[200]; 
	//sprintf(queryStr, "SELECT u.lec_id, u.pos_id, e.timeslot from lecunavailabletimes u INNER JOIN edges e ON e.lec_id = u.lec_id ORDER BY e.timeslot, u.lec_id, u.pos_id");
	//printf("\n%s\n", queryStr);
	
	/* send SQL query */
	if (mysql_query(conn, "SELECT u.lec_id, u.pos_id, e.timeslot from lecunavailabletimes u INNER JOIN edges e ON e.lec_id = u.lec_id ORDER BY e.timeslot, u.lec_id, u.pos_id")){
	 	printf("Failed to execute query to get unavailable times. Error: %s\n", mysql_error(conn));
	  	mysql_close(conn);
	  	return NULL;
	}
	
	res = mysql_store_result(conn);
	if (res == NULL){
		mysql_close(conn);
		return NULL;
    }

	while(row = mysql_fetch_row(res)){
		
		head = addNewDbRecordToLL( /*(row[0] ? row[0] : "NULL"),*/ atoi(row[1]), atoi(row[2]), head);  // atoi: int converting
   		
 	}
 	printf("\n + DB records retrived and added to the linked list\n");

	mysql_free_result(res);
	mysql_close(conn);

 	return head;
}

// createRandomIndividual(ARRAY_SIZE, int* availablePositions)
void createRandomIndividual(struct Individual* individual, int* availablePositions, int availablePosArraySize){
	
	int i = 0; int j = 0;
	/*
	if (availablePosArraySize < ARRAY_SIZE) {
        // Handle the case where there are not enough unique values in availablePositions.
        printf("Not enough unique values in availablePositions.\n");
        return;
    }*/
    
    // Shuffle the availablePositions array randomly.
    for (i = availablePosArraySize - 1; i > 0; i--) {
        j = rand() % (i + 1);
        // Swap numPool[i] and numPool[j]
        int temp = availablePositions[i];
        availablePositions[i] = availablePositions[j];
        availablePositions[j] = temp;
    }
	
	// Copy the first ARRAY_SIZE values from the shuffled availablePositions array to the individual's gene.
	individual->genes = malloc(sizeof(int) * ARRAY_SIZE);
    for (i = 0; i < ARRAY_SIZE; i++) {
        individual->genes[i] = availablePositions[i];
    }
}

// Function to compare two individuals based on cost. // For qsort()
int compareCost(const void* a, const void* b) {
    int costA = ((struct Individual*)a)->cost;
    int costB = ((struct Individual*)b)->cost;
    return costA - costB;
}

// Function to get violations count for a one pos_id
int getTimeViolationsCount(struct DbRecord* dbRecordsLL_head, int timeslotNum, int positionID){
	// count how many by going though the DbRecords LL
	struct DbRecord* loop = NULL;
	loop = dbRecordsLL_head;
	int timeslotFound = 0;
	int violationsCount = 0;
	
	while(loop!=NULL){
		
		if((timeslotFound==1) && ((*loop).timeslot!=timeslotNum)){ // only works if the ll is sorted by timeslot.
			break;
		}
		
		if( (*loop).timeslot==timeslotNum ){
			timeslotFound = 1;
			
			if( (*loop).prohibitedPosID==positionID ){
				violationsCount++;
			}
		}
  		
  		loop=(*loop).link; 
    }
    return violationsCount;
}

// Function to calculate the cost of an individual.
int calculateIndividualCost(struct DbRecord* dbRecordsLL_head, int* individualGenes) {
    // the cost is calculated as the sum of squared values. based on how many violations of lecturer's prohibited times.
    int count = 0; int i = 0;
    for (i = 0; i < ARRAY_SIZE; i++) {
    	count = count + getTimeViolationsCount(dbRecordsLL_head, (i+1), individualGenes[i]);
    }
    return count * COST_OF_A_VIOLATION;
}

// Function to swap the values of two given indexes in an individual's genes array. // Swap positions in the array (index1, index2)
void swapGenes(struct Individual* individual, int index1, int index2) {
    if (index1 < 0 || index1 >= ARRAY_SIZE || index2 < 0 || index2 >= ARRAY_SIZE) {
        // Handle invalid indexes.
        printf("\n ERROR! Invalid index(es) for swapping.\n");
        return;
    }

    // Swap the values at index1 and index2.
    int temp = individual->genes[index1];
    individual->genes[index1] = individual->genes[index2];
    individual->genes[index2] = temp;
}

// Function to perform mutation on an individual.
void mutate(struct Individual* individualToMutate) {
	int i = 0;
    for (i = 0; i < ARRAY_SIZE; i++) {
        if ((double)rand() / RAND_MAX < MUTATION_RATE) {
        	// Mutate by swapping positions.
        	swapGenes(individualToMutate, i, (rand() % ARRAY_SIZE)); 
        }
    }
}

// mutatePopulation()
// select random index of population and repalce that individual with new randomly created individual. 
// if mutation being done for a few selected individuals in the population, replace entire array with new randomly generated individual(array).

// Function to select parents for reproduction. UNUSED
int selectParent(int* costs) {
    int minCost = costs[0]; int i = 0;
    for (i = 1; i < POPULATION_SIZE; i++) {
        if (costs[i] < minCost) {
            minCost = costs[i];
        }
    }

    int totalCost = 0;
    for (i = 0; i < POPULATION_SIZE; i++) {
        totalCost += (minCost - costs[i]); // Increase probability for lower-cost individuals
    }

    int r = rand() % totalCost;
    int sum = 0;
    for (i = 0; i < POPULATION_SIZE; i++) {
        sum += (minCost - costs[i]);
        if (r < sum) {
            return i; // Return the index of the selected parent
        }
    }
    return 0;
}

// A function to put optimized timeslot-positionID pairs into the database.
int putOptimizedPositionsToDB(struct Individual* leastCostIndividual, char tablename[]){
	
	MYSQL* conn;
	conn = connectDB();
	char queryStr[250]; 
	int idx = 0;
	
	//
	// ADD DROP TABLE IF EXISTS THEN CREATE TABLE
	sprintf(queryStr, "DROP TABLE IF EXISTS `%s`", tablename);	
	if (mysql_query(conn, queryStr)){
    	printf("\n Failed to drop %s table! \nError: %s\n", tablename, mysql_error(conn));
    	mysql_close(conn);
    	return 0;
  	}
	sprintf(queryStr, "CREATE TABLE `%s` (`timeslot` int NOT NULL, `pos_id` int NOT NULL)", tablename);	
	if (mysql_query(conn, queryStr)){
    	printf("\n Failed to create %s table! \nError: %s\n", tablename, mysql_error(conn));
    	mysql_close(conn);
    	return 0;
  	}
  	sprintf(queryStr, "ALTER TABLE `%s` ADD PRIMARY KEY (`timeslot`, `pos_id`)", tablename);
  	if (mysql_query(conn, queryStr)){
    	printf("\n Failed to set Primary key in %s table! \nError: %s\n", tablename, mysql_error(conn));
    	mysql_close(conn);
    	return 0;
  	}
	//
	for (idx = 0; idx < ARRAY_SIZE; idx++) {
        
		//printf("\n Timeslot %d -> positionID %d ", (i+1), leastCostIndividual->genes[i]);
        sprintf(queryStr, "INSERT INTO %s (timeslot, pos_id) VALUES('%d', '%d')", tablename, (idx+1), leastCostIndividual->genes[idx] );
		
		/* send SQL query */	
		if (mysql_query(conn, queryStr)){
			printf("\n Query Error! Failed to insert timeslot-positionID pair to the DB. Error: %s\n", mysql_error(conn));
	    	mysql_close(conn);
	    	return 0; 
		}
    }
	
	mysql_close(conn);

 	return 1;
}

