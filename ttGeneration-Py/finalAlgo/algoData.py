import random
import mysql.connector



#######################################Code related to getting data for the algorithm ############################################
##################################################################################################################################

# Connect to database
conn = mysql.connector.connect(
    host='localhost',
    user='username',
    password='password',
    database= 'fypdatabase'
)

Batches = [ ]

class BatchName:
    def __init__(self,batchName,noStu):
        self.batchName = batchName
        self.noStu = noStu

class BatchMod:
    def __init__(self,batchName,module_code,bmodID):
        self.batchName = batchName
        self.module_code = module_code
        self.bmodID = bmodID
        

    

class Batch:
    def __init__(self,batchName,modules,noStudents):
        self.batchName = batchName
        self.modules = modules
        self.noStudents = noStudents
        self.tt = []

    def addTT(self,timeSlots):
        tt.append(timeSlots)


# Create cursor object
cursor = conn.cursor()

# Execute SELECT statement
cursor.execute('SELECT * FROM batches')
# Fetch all rows
rows = cursor.fetchall()

# Create objects for each row
BatchNames = []
for row in rows:
    obj = BatchName(*row)
    BatchNames.append(obj)  


# Close cursor and connection
cursor.close()

# Create cursor object
cursor = conn.cursor()

# Execute SELECT statement
cursor.execute('SELECT * FROM batch_modules')
bmrows = cursor.fetchall()

BatchMods = []
for bmrow in bmrows:
    obj = BatchMod(*bmrow)
    BatchMods.append(obj)  

for bname in BatchNames:
    modlist = []
    for bmods in BatchMods:
        if bname.batchName == bmods.batchName:
            modlist.append(bmods.module_code)
    Batches.append(Batch(bname.batchName,modlist,bname.noStu))


cursor.close()

#Adds the lecturers from sql 

class Lecturer:
    def __init__(self,lecid,lecName,maxHours,payRate):
        self.lecid = lecid
        self.lecName = lecName
        self.maxHours = maxHours
        self.payRate = payRate
        self.tt = [ ]




Lecturers = []


# Create cursor object
cursor = conn.cursor()

# Execute SELECT statement
cursor.execute('SELECT * FROM lecturers')
# Fetch all rows
lecRows = cursor.fetchall()

for row in lecRows:
    obj = Lecturer(*row)
    Lecturers.append(obj)


cursor.close()

 ##Get modules from database

class Mod:
    def __init__(self,mod_code,mod_name,credits):
        self.mod_code = mod_code
        self.mod_name = mod_name
        self.credits = credits

Mods = []


# Create cursor object
cursor = conn.cursor()

# Execute SELECT statement
cursor.execute('SELECT * FROM module')
# Fetch all rows
modRows = cursor.fetchall()

for row in modRows:
    obj = Mod(*row)
    Mods.append(obj)

cursor.close()


##get lecmod from lec_modules

class LecMod:
    def __init__(self,lec_id,module_code,modLecID):
        self.lec_id = lec_id
        self.module_code = module_code
        self.modLecID = modLecID

LecMods = []

# Create cursor object
cursor = conn.cursor()

# Execute SELECT statement
cursor.execute('SELECT * FROM lec_modules')
# Fetch all rows
lecmodRows = cursor.fetchall()

for row in lecmodRows:
    obj = LecMod(*row)
    LecMods.append(obj)


# cursor.close()


## Use lecmod and mods to assign values to lecturers list

class Module:
    def __init__(self,modcode,credits,lecturers):
        self.modcode = modcode
        self.credits = credits
        self.lecturers = lecturers
    
    #function to search the module list
    def modulelistSearcher(thelist,thevalue):
        j = 0
        while j < len(thelist):
            if(thelist[j].modcode == thevalue):
                return thelist[j]
            j = j + 1

Modules = []

for m in Mods:
    lecList = []
    LecsList = []
    for lc in LecMods:
        if lc.module_code == m.mod_code:
            lecList.append(lc.lec_id)
    for ll in lecList:
        for l in Lecturers:
            if ll == l.lecid:
                LecsList.append(l)
    Modules.append(Module(m.mod_code,m.credits,LecsList))


 
# for l in Lecturers: 
#     print("lecId: " + str( l.lecid) + " lecName: " + l.lecName)

# for r in LecsList:
#     print("lecturers in modules")
#     print(m.mod_code)
#     print(r.lecid)

for m in Modules:
    print('modules assigned with lecturer')
    print(" modules : " + m.modcode)
    for r in m.lecturers:
        print("lecturer: " )
        print(r.lecid)



       

class Classroom:
    def __init__(self,name,capacity):
        self.name = name
        self.capacity = capacity
        self.tt = []
        self.probabiltyDictonary = {}
    
    def printClass(self):
        print("class:" + self.name)




c1 = Classroom('c1',25)
c2 = Classroom('c2',40)
c3 = Classroom('c3',20)

Classrooms = [c1,c2,c3] 



          ######################################################################################################

costofNewHire  = 1000
costofExtendDay = 300
costofExtendWeek = 700



creditToHourRatio = 1
breakTime = 1
breakRatio = 1


beginTime = 9
closeTime = 16
opTime = closeTime - beginTime

beginDay = 0
closeDay = 5
opDays = beginDay - closeDay

                                  
                                                #######   Algorithm   #######
###########################################################################################################################
###############################################################################################################################################



##Creates Class called timeslot which store time and date information

class TimeSlot:
    def __init__(self,hour,day,number):
        self.hour = hour
        self.day = day
        self.number = number

    def printTime(self):
        print('hour: ' + str(self.hour) + 'day: ' + str(self.day) )

timeSlots = []


##Generates timeslots 
def TimeSlotsGen(startTime,endTime,startDay,endDay):
    
    i = 0
    time =  startTime
    day = startDay
    while ((day != endDay) and (time != (endTime) )):
        

        if (time == endTime):
            timeSlots.append(TimeSlot(time,day,i))
            time = startTime
            day = day + 1
        else:    
            timeSlots.append(TimeSlot(time,day,i))
            time = time + 1
        i = i + 1
    timeSlots.append(TimeSlot(endTime,endDay,i))
    
TimeSlotsGen(1,12,1,5)

# Class whcih represents a possible combination between batch, module and lecturer as well as a node.
#  The node also includes the cost of selecting it.

class moduleNode:
    def __init__(self,batchName,modCode,lecID,cost,noStudents):
        self.batchName = batchName
        self.modCode = modCode
        self.lecID = lecID
        self.cost = cost
        self.noStudents = noStudents

    def printNode(self):
        print("batchName: " + self.batchName + " module: " + self.modCode + ' lecID: ' + str(self.lecID))

    ## used to calculate which node has the lowest cost.
    def lowestCost(list,room ):
        j = 0
        
        eligbleList = []

        for l in list:
            if l.noStudents <= room.capacity:
                eligbleList.append(l)

        if(len(eligbleList) > 0):
            lowest = eligbleList[0]
            while j < len(eligbleList):
                if lowest.cost > list[j].cost and (lowest.noStudents <= room.capacity) :
                    lowest = eligbleList[j]
                j = j + 1
        else:
            lowest = 'X'
        return lowest




## Generates a list of moduleNodes using the batch list and module list.

allModuleCombos = []

def modNodeGen(batchList,moduleList):
    for batch in batchList:
        node_batchName = batch.batchName
        node_noStudents = batch.noStudents
        for module in batch.modules:
            mod = Module.modulelistSearcher(moduleList,module)
            if mod is not None:
                node_modcode =  mod.modcode
                j = 0
                while j < (creditToHourRatio * mod.credits):
                    for lec in mod.lecturers:
                        node_lec = lec.lecid
                        node_cost = lec.payRate
                        allModuleCombos.append(moduleNode(node_batchName,node_modcode,node_lec,node_cost,node_noStudents))
                    allModuleCombos.append(moduleNode(node_batchName,node_modcode,'NA',costofNewHire,node_noStudents))
                    j = j + 1
    
            
modNodeGen(Batches,Modules)


for n in allModuleCombos:
    print("modulecombo list")
    print()
    print('batchname: ' + n.batchName + " lecID: " + str(n.lecID))





def wasteMatrixGenerator(rooms,nodes):

    #create a matrix by subtracting classroom capacity from node size.
    wasteMatrix = []
    for r in rooms:
        roomWaste = []
        for n in nodes:
            waste = r.capacity - n.noStudents
            if(waste < 0 ):
                waste = 'X'
            wasteDict = [{"c":r.name,'b':n.batchName,'w':waste}]
            roomWaste.append(wasteDict)
        wasteMatrix.append(roomWaste)
    
    for row in wasteMatrix:
        print()
        for i in row:
            print(i, end=" ")
            print()
    
    return wasteMatrix

# a function for allocating the Nodes to the classroom in a way that minimizes the wastages. 

def printMatrix(iMatrix):
        for row in iMatrix:
            print(" ")
            for i in row:
                print(i, end= " ")   

def printList(List):
        for x in List:
            print(x, end= " ")   

def comboGenerator(c,b,batchlist):
    matrix = m






# def  randomComboGenerator(m):
    
    
#     #genrate random combos of classrooms from the matrix
#     # matrix = wasteMatrixGenerator(rooms,nodes)

#     # noRows = len(matrix)
#     # noColumns = len(matrix[0])

#     # matrix = [[7,9,8],[3,8,2],[4,3,5]]

#     matrix = m

    
#     duplicate_matrix = matrix[:]
#     noRows = len(duplicate_matrix)
#     noColumns = len(duplicate_matrix[0])


#     printMatrix(matrix)
#     print()
#     randomCombo = []
#     while(noColumns > 1):
   
#         # randomCombo.append(matrix[0][random.randint(0,noColumns-1)])
        

#         #selects a random element from the first row
#         randColumn = random.randint(0,noColumns-1)
#         randomCombo.append(duplicate_matrix[0][randColumn])

#         # remove the first row and selected column(random Column) from the matrix  and saves to a new matrix
#         newMatrix = []
#         for r in range(noRows):
#             if (r != 0):
#                 newRow = []

#                 for c in range(noColumns):

#                     if(c != randColumn):
#                         newRow.append(duplicate_matrix[r][c])

#                 newMatrix.append(newRow)
        
    
#         printMatrix(duplicate_matrix)
#         print()
#         print ("removed column: " +  str(randColumn))
#         printMatrix(newMatrix)
#         print()
    
#         duplicate_matrix = newMatrix[:]
#         noRows = len(duplicate_matrix)
#         noColumns = len(duplicate_matrix[0])
#             # duplicate_matrix = newMatrix[:]
#             # noRows = len(duplicate_matrix)
#             # noColumns = len(duplicate_matrix[0])
#     randomCombo.append(duplicate_matrix[0][0])
    
#     #sum all the weights in random combo 
#     t = 0
#     for i in randomCombo:
#         for j in i:
#          if isinstance(j['w'],int):
#             t = t + j['w']
#             print(j['w'])
        

#     # randomCombo['sumWaste'] = t
    
#     randomComboWeight = {'randomCombo':randomCombo, 'weight': t}
#     print("randomCombo: ")   
     
#     print(randomComboWeight)
#     return randomComboWeight
    

# def dictionaryGenerator(m):
    
#     matrix = m
#     noRows =  len(matrix)

#     combos = []
    
#     for i in range(noRows):
#         combos.append(randomComboGenerator(m))

    
#     sortedCombos = sorted(combos, key = lambda x: x['weight'])

#     print()
#     print("Combos in ascending order:")
#     print()
#     for c in sortedCombos:
#         print(c) 
    
#     i = 0
#     while ( i < len(sortedCombos)):
#         if (sortedCombos[i]['weight'] == sortedCombos[i-1]['weight']) and i:
#             sortedCombos[i]['prob'] = i
#             i = i + 1
#         else:
#             sortedCombos[i]['prob'] = i+1
#             i = i + 1

#     print()
#     print("combos sorted in ascending order with probility(bias) added")
#     print()
#     for c in sortedCombos:
#         print(c) 
    
#     for combo in sortedCombos:
#         list = combo['randomCombo']
#         prob = combo['prob']
#         for l in list:
#             for ll in l:
#                 cl = ll['c']
#                 b = ll['b']
#                 for c in Classrooms:
#                     if c.name == cl:
#                         if b in c.probabiltyDictonary:
#                             prob = c.probabiltyDictonary[b] + prob
#                             c.probabiltyDictonary.update({b:prob})
#                         c.probabiltyDictonary.update({b:prob})
    
#     print()
#     print("Probilty(Bias) of a batch being present in a classroom")
#     print()
#     for c in Classrooms:
#         print(f"{c.name}: {c.probabiltyDictonary}")
#     print()



# class which represents a combination of hour, room , a Modulenode. This will be the node that will be used bby the algorithm.

class ttSlot():
    def __init__(self,time,room,node):
        self.time = time
        self.room = room
        self.node = node

    def printTTSlot(self):
        self.time.printTime()
        self.room.printClass()
        self.node.printNode()
    

tt = []


availablemodNodes = allModuleCombos[:]
tslotClassroom = Classrooms[:]
tSlotmodNodes = availablemodNodes[:]




#code to check if there are batches which are bigger than existing classroom size and removes it.
## Further on this code could be modified so it either display a notification to webapp that its too big or it splits batches in two.

sortClassroom =sorted(Classrooms, key= lambda x: x.capacity)

for b in Batches:
    if sortClassroom[-1].capacity < b.noStudents:
        Batches.remove(b)




#code to check if there are nodes which are can be merged to one. different batches have same module 


                        




def TTGenerator(timeslots):

    previousTime = None
    evenpreviousTime = None




    for t in timeslots:

        selectionNodes = availablemodNodes[:]
        selectionClassrooms = Classrooms[:]
        
        anotherClasslist = []
        anotherNodelist = []

        for c in Classrooms: 

            # selects a classroom randomly from list and removes it from that list
            randClassroom = random.choice(selectionClassrooms)
            selectionClassrooms.remove(randClassroom)

                ## Give breaks to batches
                ## if the last node in a batch is the one immeadiatly before the the current time. Then it can be
                ## selected only by the same classroom . That too  if  only b.tt[-2].t != t-2. 
                 
            for b in Batches:
                templist = selectionNodes[:]
                addbacklist = []
                if len(b.tt) > 0:
                    if len(b.tt) > 2 and b.tt[-1].time == previousTime and b.tt[-2].time == evenpreviousTime:
                        for s in templist:
                            if(s.batchName == b.tt[-1].node.batchName):
                                selectionNodes.remove(s)  
                    elif b.tt[-1].time == previousTime and b.tt[-1].room != randClassroom:
                        for s in templist:
                                if(s.batchName == b.tt[-1].node.batchName):
                                    addbacklist.append(s)
                                    selectionNodes.remove(s)


            if(len(selectionNodes)>0):


                # selects the cheapest node from the nodes list
       
                cheapNode = moduleNode.lowestCost(selectionNodes,randClassroom)
                #cheapnode of x is returned if there are no nodes which have a size bigger than the classroom.
                if(cheapNode != 'X'):
                    anotherClasslist.append(randClassroom)
                    anotherNodelist.append(cheapNode)


            

                    


                #This code block code be replaced with machine learning code as it deals with how the selected batch  is arranged
                # 
                #  
                #Adds the selected nodes to the tt properties in classromm tt , main tt, and batch tt,lecturer tt
                if(cheapNode != 'X'):


                    # tt.append(ttSlot(t,randClassroom,cheapNode))
                    # randClassroom.tt.append(ttSlot(t,randClassroom,cheapNode))
                    # for b in Batches:
                    #     if(b.batchName == cheapNode.batchName):
                    #         b.tt.append(ttSlot(t,randClassroom,cheapNode))
                    # for l in Lecturers:
                    #     if(l.lecid == cheapNode.lecID):
                    #         l.tt.append(ttSlot(t,randClassroom,cheapNode))    

                    #removes it from availablenodes list and selection list
                    availablemodNodes.remove(cheapNode)
                    selectionNodes.remove(cheapNode)
                    replictSlot = selectionNodes[:]

                    #remove slots with the same batch or lecturer so other classroom cant select them at same time
                    for n in replictSlot:
                        if (n.batchName == cheapNode.batchName or n.lecID == cheapNode.lecID):
                            selectionNodes.remove(n)
                    

                    #remove nodes with different lecturer but same batch and module as selected(cheapest) node from available nodes
                    removList = availablemodNodes[:]
                    for n in removList:
                        if( (n.batchName == cheapNode.batchName) and (n.modCode == cheapNode.modCode) and (n.lecID !=  cheapNode.lecID)):
                            availablemodNodes.remove(n)

                    
                    #add back nodes which are meant to be on break and classroom is differnrt from currnet one
                    selectionNodes.extend(addbacklist)



                    # print('batch: ' + n.batchName)


        # This code matches the smallest classroom with the smallest selected node so it minimizes the wastage of resources.

        anotherClasslist = sorted(anotherClasslist, key= lambda x: x.capacity )
        anotherNodelist = sorted(anotherNodelist, key = lambda x: x.noStudents)

        for i in range(len(anotherClasslist)):

            tt.append(ttSlot(t,anotherClasslist[i],anotherNodelist[i]))
            randClassroom.tt.append(ttSlot(t,anotherClasslist[i],anotherNodelist[i]))
            for b in Batches:
                if(b.batchName == anotherNodelist[i].batchName):
                    b.tt.append(ttSlot(t,anotherClasslist[i],anotherNodelist[i]))
            for l in Lecturers:
                if(l.lecid == anotherNodelist[i].lecID):
                    l.tt.append(ttSlot(t,anotherClasslist[i],anotherNodelist[i])) 

            

            

        # for c in Classrooms: 

        #     # selects a classroom randomly from list and removes it from that list
        #     randClassroom = random.choice(selectionClassrooms)
        #     selectionClassrooms.remove(randClassroom)

        #         ## Give breaks to batches
        #         ## if the last node in a batch is the one immeadiatly before the the current time. Then it can be
        #         ## selected only by the same classroom . That too  if  only b.tt[-2].t != t-2. 
                 
        #     for b in Batches:
        #         templist = selectionNodes[:]
        #         addbacklist = []
        #         if len(b.tt) > 0:
        #             if len(b.tt) > 2 and b.tt[-1].time == previousTime and b.tt[-2].time == evenpreviousTime:
        #                 for s in templist:
        #                     if(s.batchName == b.tt[-1].node.batchName):
        #                         selectionNodes.remove(s)  
        #             elif b.tt[-1].time == previousTime and b.tt[-1].room != randClassroom:
        #                 for s in templist:
        #                         if(s.batchName == b.tt[-1].node.batchName):
        #                             addbacklist.append(s)
        #                             selectionNodes.remove(s)


        #     if(len(selectionNodes)>0):


        #         # selects the cheapest node from the nodes list and adds it to tt list

        #         cheapNode = moduleNode.lowestCost(selectionNodes)
        #         tt.append(ttSlot(t,randClassroom,cheapNode))
        #         randClassroom.tt.append(ttSlot(t,randClassroom,cheapNode))
        #         for b in Batches:
        #             if(b.batchName == cheapNode.batchName):
        #                 b.tt.append(ttSlot(t,randClassroom,cheapNode))
        #         for l in Lecturers:
        #             if(l.lecid == cheapNode.lecID):
        #                 l.tt.append(ttSlot(t,randClassroom,cheapNode))    

        #         #removes it from availablenodes list and selection list
        #         availablemodNodes.remove(cheapNode)
        #         selectionNodes.remove(cheapNode)
        #         replictSlot = selectionNodes[:]

        #         #remove slots with the same batch or lecturer so other classroom cant select them at same time
        #         for n in replictSlot:
        #             if (n.batchName == cheapNode.batchName or n.lecID == cheapNode.lecID):
        #                 selectionNodes.remove(n)
                

        #         #remove nodes with different lecturer but same batch and module as selected(cheapest) node from available nodes
        #         removList = availablemodNodes[:]
        #         for n in removList:
        #             if( (n.batchName == cheapNode.batchName) and (n.modCode == cheapNode.modCode) and (n.lecID !=  cheapNode.lecID)):
        #                 availablemodNodes.remove(n)

                
        #         #add back nodes which are meant to be on break and classroom is differnrt from currnet one
        #         selectionNodes.extend(addbacklist)

    
        evenpreviousTime = previousTime
        previousTime = t    
        selectionClassrooms = Classrooms[:]
 


TTGenerator(timeSlots)
 

## If the available timeslots are not enough then the reminig modules are assingned by first extending the day
#  then the week.

xTime = closeTime   
xDay = beginDay 

while (len(availablemodNodes) > 0 and xDay <= 7): 
    timeSlots = []  
    TimeSlotsGen(xTime,xTime + 1,xDay,xDay)
    TTGenerator(timeSlots)
    xTime = xTime + 1
    if(xTime == 24):
        xDay = xDay + 1
        xTime == 0



i = 0
for slot in tt:
    
    print("slot no: " + str(i))
    i = i + 1
    slot.printTTSlot()
    print(" ")

# wasteMatrixGenerator(tslotClassroom,tSlotmodNodes)
#  

# comboGenerator(wasteMatrixGenerator(tslotClassroom,addnodes))
# dictionaryGenerator(wasteMatrixGenerator(tslotClassroom,addnodes))



 
                                        ## upload to the SQL backend ##
################################################################################################################################
############################################################################################################################


for b in Batches:
    batch = b.batchName 
    for slot in b.tt:
        slot_module = slot.node.modCode
        slot_lecturer = str(slot.node.lecID)
        slot_classroom = slot.room.name
        slot_hour = str(slot.time.hour) 
        slot_day = str(slot.time.day)
         # print(batch + " " + slot_module + " " + slot_lecturer + " " + slot_classroom + " " + slot_hour + "  " + slot_day)
        # Create a cursor object
        cursor = conn.cursor()

        # Insert data into the database
        sql = "INSERT INTO master_tt (batch,module,lecturer,hour,day,classroom) VALUES (%s, %s, %s, %s, %s, %s)"
        val = (batch, slot_module, slot_lecturer,slot_hour,slot_day,slot_classroom)
        cursor.execute(sql, val)

        # Commit changes to the database
        conn.commit()

        # Close the cursor and connection
        cursor.close()

#close the connection with the database
conn.close()
        

        
















            




        


       
        
        


       
        

    



