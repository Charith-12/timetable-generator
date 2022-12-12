from datetime import time
from operator import mod


# C:/Users/adith/anaconda3/python.exe c:/Users/adith/Desktop/algorithm.py

#defines a slot in the university timetable
class slot: 
    def __init__(self,month,day,time,):
        self.month = month
        self.day = day
        self.time = time
        # self.classroom = classroom


#print slots given a list of slot objects
def printSlots(slots):
    for s in slots:
        # print("month:",s.month," day:",s.day," time:",s.time," classroom:",s.classroom)
        print("month:",s.month," day:",s.day," time:",s.time)

       

#object for months with a given number of holidays
class month:
    def __init__(self,name,days,holidays):
        self.name = name
        self.days = days
        self.holidays = holidays

#defines a univerity
class university:
    def __init__(self,classrooms,batches,openingTime,closingTime,breakTime,months,openMonth,openDay,closeMonth,closeDay):
        self.classrooms = classrooms
        self.batches = batches
        self.openingTime = openingTime
        self.closingTime = closingTime
        self.breakTime = breakTime 
        self.months = months
        self.openMonth = openMonth
        self.openDay = openDay
        self.closeMonth = closeMonth
        self.closeDay = closeDay
        self.availableSlotsDay = []

   #function to generate total slot in univerity 

    def dayslotGen(self):
        openHours = self.closingTime.hour - self.openingTime.hour

        #remove months before open month in array
        i =  0
        j = len(self.months)
        while i < j :
            if (self.months[i].name == self.openMonth):
                print("open month: ",self.months[i].name)
                i = j
            else:
                print("removed month ", self.months[i].name)
                self.months.remove(self.months[i])
                j = j -1
                # i = i +1 
                
       # Adds slots to availableslotsDay list
        f = 0
        for M in self.months:
            if(f == 1):
                break
            d = 1
            while(d <=  M.days): 
                if(d == closeDay and M.name == closeMonth):
                    f = 1   
                i = 0
                while(i<=openHours):
                    self.availableSlotsDay.append(slot(M.name,d,i))
                    i = i + 1
                d = d + 1
  
        
        
       


        # removes the holidays from the list
        for M in self.months:
            for H in M.holidays:
               j = 0
               while(j<len(self.availableSlotsDay)):
                if(self.availableSlotsDay[j].month == M.name and self.availableSlotsDay[j].day == H ):
                   self.availableSlotsDay.remove(self.availableSlotsDay[j]) 
                else:
                    j = j + 1
           
  
        j  = 0

        while(j<len(self.availableSlotsDay)):
            if(self.availableSlotsDay[j].month == self.openMonth and self.availableSlotsDay[j].day < self.openDay):
                self.availableSlotsDay.remove(self.availableSlotsDay[j])
            else:
                j = j + 1


   

        #removes days after closing day on closing month
        j = 0
        x = 0
        while(j < len(self.availableSlotsDay)):
            if(self.availableSlotsDay[j].month == self.closeMonth and self.availableSlotsDay[j].day > self.closeDay ):
                print(self.availableSlotsDay[j].month)
                # print(self.availableSlotsDay[j].time)
                x = x +1
            j= j + 1
        print("this is x:", x)   
        i = 0
        while(i<x):
            self.availableSlotsDay.pop()
            i = i + 1  


        

 
        print("Total Available Slots in Uni: ")
        print("day   t   classroom")
        printSlots(self.availableSlotsDay)

                    
    
#defines a batch and includes a timetable for it.
class batch:
    def __init__(self,batchName,modules):
        self.batchName = batchName
        self.modules = modules
        self.batchTT = []

#defines the properties for a module
class module:
    def __init__(self,moduleName,credits,lectures):
        self.moduleName = moduleName
        self.credits = credits
        self.lectures = lectures


#defines the properties for a lecturer
class lectures:

#function to genreate empty timetable for a lecturer based on working hours
    def freeTimeGen(self):
        i = 0
        workHours = self.endTime.hour - self.startTime.hour
        while( i <= workHours):
             self.freeTime.append(i)
             i = i +1

    def __init__(self,name,startTime,endTime):
        self.name = name
        self.lecTT = []
        self.freeTime =[]
        self.startTime = startTime
        self.endTime = endTime
        self.freeTimeGen()


Lec1 = lectures("bob",time(hour=9),time(hour=12)) 
Module1 = module("mod1",2,[Lec1])
Module2 = module("mod2",2,[Lec1])

Jan = month("Jan",30,[12,20])
Feb = month("Feb",31,[7])
Mar = month("Mar",30,[2,26])

Batch1 = batch("B1",[Module1,Module2])      
print("Months: Jan,Feb,Mar")

startMonth = input("enter the start month")
startDay = int(input('enter the start day'))

closeMonth = input("enter the last month")
closeDay = int(input("enter the last day"))

University = university(['c1','c2'],[Batch1],time(hour= 0),time(hour=2 
 ),1,[Jan,Feb,Mar],startMonth,startDay,closeMonth,closeDay)
University.dayslotGen()





# def ttGen(uni):
#     for b in uni.batches:
#         for m in b.modules:
#             for l in m.lectures:
#                 for s in uni.availableSlotsDay:
#                     for t in l.freeTime:
#                         if t == s.time:
#                             l.freeTime.remove(t)
#                             l.lecTT.append(s)
#                             b.batchTT.append(s)
#                             uni.availableSlotsDay.remove(s)

# ttGen(University)

# print("Free Slots available in uni after creating timetable")
# printSlots(University.availableSlotsDay) 

# print("Batch 1 timetable:")
# printSlots(Batch1.batchTT)

# print("Lecture 1 timetable")
# printSlots(Lec1.lecTT)