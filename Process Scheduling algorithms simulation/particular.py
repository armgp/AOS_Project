import matplotlib.pyplot as plt
import csv

process = []
completion_time1 = []
waiting_time1 = []
turn_around_time1 = []
response_time1 = []
with open("fcfs.csv") as in_file:
	csv_reader = csv.reader(in_file,delimiter=" ")
	for line in csv_reader:
		process.append(line[0])
		waiting_time1.append(line[2])
		completion_time1.append(line[4])
		turn_around_time1.append(line[6])
		response_time1.append(line[8])

#print(waiting_time1)
#process =  [eval(i) for i in process1]
#print(process)
completion_time = [eval(i) for i in completion_time1]
#print(completion_time)
waiting_time = [eval(i) for i in waiting_time1]
#print(waiting_time)
turn_around_time = [eval(i) for i in turn_around_time1]
#print(turn_around_time)
response_time = [eval(i) for i in response_time1]

#plt.tick_params(axis='both', which='minor', labelsize=8)


plt.figure(figsize=(13,7))

plt.plot(process,turn_around_time,label='turn_around_time',linewidth=3.0,marker='o',markersize=15,markerfacecolor='blue')
plt.plot(process,completion_time,label='completion_time',linewidth=3.0,marker='o',markersize=15,markerfacecolor='orange')
plt.plot(process,waiting_time,label='waiting_time',linewidth=3.0,marker='o',markersize=15,markerfacecolor='green')
plt.plot(process,response_time,label='response_time',linewidth=3.0,marker='o',markersize=15,markerfacecolor='red')

plt.yticks(fontsize=15)
plt.xticks(fontsize=15)

plt.xlabel('process',size=20,fontweight="bold")
plt.ylabel('Time',size=20,fontweight="bold")
plt.title('FCFS', size=20,fontweight="bold")


plt.legend(prop={"size":14})
plt.savefig("graph/fcfs.png")
plt.show()

#----------------------------------------------------------------#

del process[:]
del completion_time1[:]
del waiting_time1[:]
del turn_around_time1[:]
del completion_time[:]
del waiting_time[:]
del turn_around_time[:]
del response_time1[:]
del response_time[:]

with open("sjfNp.csv") as in_file:
	csv_reader = csv.reader(in_file,delimiter=" ")
	for line in csv_reader:
		process.append(line[0])
		waiting_time1.append(line[2])
		completion_time1.append(line[4])
		turn_around_time1.append(line[6])
		response_time1.append(line[8])

#print(waiting_time1)
#process =  [eval(i) for i in process1]
#print(process)
completion_time = [eval(i) for i in completion_time1]
#print(completion_time)
waiting_time = [eval(i) for i in waiting_time1]
#print(waiting_time)
turn_around_time = [eval(i) for i in turn_around_time1]
#print(turn_around_time)
response_time = [eval(i) for i in response_time1]

#plt.tick_params(axis='both', which='minor', labelsize=8)


plt.figure(figsize=(13,7))

plt.plot(process,turn_around_time,label='turn_around_time',linewidth=3.0,marker='o',markersize=15,markerfacecolor='blue')
plt.plot(process,completion_time,label='completion_time',linewidth=3.0,marker='o',markersize=15,markerfacecolor='orange')
plt.plot(process,waiting_time,label='waiting_time',linewidth=3.0,marker='o',markersize=15,markerfacecolor='green')
plt.plot(process,response_time,label='response_time',linewidth=3.0,marker='o',markersize=15,markerfacecolor='red')


plt.yticks(fontsize=15)
plt.xticks(fontsize=15)

plt.xlabel('process',size=20,fontweight="bold")
plt.ylabel('Time',size=20,fontweight="bold")
plt.title('SJFNP', size=20,fontweight="bold")


plt.legend(prop={"size":14})
plt.savefig("graph/sjfnp.png")
plt.show()

#-----------------------------------------------------------#

del process[:]
del completion_time1[:]
del waiting_time1[:]
del turn_around_time1[:]
del completion_time[:]
del waiting_time[:]
del turn_around_time[:]
del response_time1[:]
del response_time[:]

with open("rr.csv") as in_file:
	csv_reader = csv.reader(in_file,delimiter=" ")
	for line in csv_reader:
		process.append(line[0])
		waiting_time1.append(line[2])
		completion_time1.append(line[4])
		turn_around_time1.append(line[6])
		response_time1.append(line[8])

#print(waiting_time1)
#process =  [eval(i) for i in process1]
#print(process)
completion_time = [eval(i) for i in completion_time1]
#print(completion_time)
waiting_time = [eval(i) for i in waiting_time1]
#print(waiting_time)
turn_around_time = [eval(i) for i in turn_around_time1]
#print(turn_around_time)
response_time = [eval(i) for i in response_time1]

#plt.tick_params(axis='both', which='minor', labelsize=8)


plt.figure(figsize=(13,7))

plt.plot(process,turn_around_time,label='turn_around_time',linewidth=3.0,marker='o',markersize=15,markerfacecolor='blue')
plt.plot(process,completion_time,label='completion_time',linewidth=3.0,marker='o',markersize=15,markerfacecolor='orange')
plt.plot(process,waiting_time,label='waiting_time',linewidth=3.0,marker='o',markersize=15,markerfacecolor='green')
plt.plot(process,response_time,label='response_time',linewidth=3.0,marker='o',markersize=15,markerfacecolor='red')


plt.yticks(fontsize=15)
plt.xticks(fontsize=15)

plt.xlabel('process',size=20,fontweight="bold")
plt.ylabel('Time',size=20,fontweight="bold")
plt.title('rr', size=20,fontweight="bold")


plt.legend(prop={"size":14})
plt.savefig("graph/rr.png")
plt.show()
#-----------------------------------------------------------#

del process[:]
del completion_time1[:]
del waiting_time1[:]
del turn_around_time1[:]
del completion_time[:]
del waiting_time[:]
del turn_around_time[:]
del response_time1[:]
del response_time[:]

with open("sjfp.csv") as in_file:
	csv_reader = csv.reader(in_file,delimiter=" ")
	for line in csv_reader:
		process.append(line[0])
		waiting_time1.append(line[2])
		completion_time1.append(line[4])
		turn_around_time1.append(line[6])
		response_time1.append(line[8])

#print(waiting_time1)
#process =  [eval(i) for i in process1]
#print(process)
completion_time = [eval(i) for i in completion_time1]
#print(completion_time)
waiting_time = [eval(i) for i in waiting_time1]
#print(waiting_time)
turn_around_time = [eval(i) for i in turn_around_time1]
#print(turn_around_time)
response_time = [eval(i) for i in response_time1]

#plt.tick_params(axis='both', which='minor', labelsize=8)


plt.figure(figsize=(13,7))

plt.plot(process,turn_around_time,label='turn_around_time',linewidth=3.0,marker='o',markersize=15,markerfacecolor='blue')
plt.plot(process,completion_time,label='completion_time',linewidth=3.0,marker='o',markersize=15,markerfacecolor='orange')
plt.plot(process,waiting_time,label='waiting_time',linewidth=3.0,marker='o',markersize=15,markerfacecolor='green')
plt.plot(process,response_time,label='response_time',linewidth=3.0,marker='o',markersize=15,markerfacecolor='red')


plt.yticks(fontsize=15)
plt.xticks(fontsize=15)

plt.xlabel('process',size=20,fontweight="bold")
plt.ylabel('Time',size=20,fontweight="bold")
plt.title('SJFP', size=20,fontweight="bold")


plt.legend(prop={"size":14})
plt.savefig("graph/sjfp.png")
plt.show()


#---------------------------------------------------------------------------------------------------#

del process[:]
del completion_time1[:]
del waiting_time1[:]
del turn_around_time1[:]
del completion_time[:]
del waiting_time[:]
del turn_around_time[:]
del response_time1[:]
del response_time[:]

with open("mlfq.csv") as in_file:
	csv_reader = csv.reader(in_file,delimiter=" ")
	for line in csv_reader:
		process.append(line[0])
		waiting_time1.append(line[2])
		completion_time1.append(line[4])
		turn_around_time1.append(line[6])
		response_time1.append(line[8])

#print(waiting_time1)
#process =  [eval(i) for i in process1]
#print(process)
completion_time = [eval(i) for i in completion_time1]
#print(completion_time)
waiting_time = [eval(i) for i in waiting_time1]
#print(waiting_time)
turn_around_time = [eval(i) for i in turn_around_time1]
#print(turn_around_time)
response_time = [eval(i) for i in response_time1]

#plt.tick_params(axis='both', which='minor', labelsize=8)


plt.figure(figsize=(13,7))
response_time1.append(line[8])
plt.plot(process,turn_around_time,label='turn_around_time',linewidth=3.0,marker='o',markersize=15,markerfacecolor='blue')
plt.plot(process,completion_time,label='completion_time',linewidth=3.0,marker='o',markersize=15,markerfacecolor='orange')
plt.plot(process,waiting_time,label='waiting_time',linewidth=3.0,marker='o',markersize=15,markerfacecolor='green')
plt.plot(process,response_time,label='response_time',linewidth=3.0,marker='o',markersize=15,markerfacecolor='red')


plt.yticks(fontsize=15)
plt.xticks(fontsize=15)

plt.xlabel('process',size=20,fontweight="bold")
plt.ylabel('Time',size=20,fontweight="bold")
plt.title('MLFQ', size=20,fontweight="bold")


plt.legend(prop={"size":14})
plt.savefig("graph/mlfq.png")
plt.show()


#--------------------------------------------------------------------------------------------------#


del process[:]
del completion_time1[:]
del waiting_time1[:]
del turn_around_time1[:]
del completion_time[:]
del waiting_time[:]
del turn_around_time[:]
del response_time1[:]
del response_time[:]

with open("mlpq.csv") as in_file:
	csv_reader = csv.reader(in_file,delimiter=" ")
	for line in csv_reader:
		process.append(line[0])
		waiting_time1.append(line[2])
		completion_time1.append(line[4])
		turn_around_time1.append(line[6])
		response_time1.append(line[8])

#print(waiting_time1)
#process =  [eval(i) for i in process1]
#print(process)
completion_time = [eval(i) for i in completion_time1]
#print(completion_time)
waiting_time = [eval(i) for i in waiting_time1]
#print(waiting_time)
turn_around_time = [eval(i) for i in turn_around_time1]
#print(turn_around_time)
response_time = [eval(i) for i in response_time1]

#plt.tick_params(axis='both', which='minor', labelsize=8)


plt.figure(figsize=(13,7))

plt.plot(process,turn_around_time,label='turn_around_time',linewidth=3.0,marker='o',markersize=15,markerfacecolor='blue')
plt.plot(process,completion_time,label='completion_time',linewidth=3.0,marker='o',markersize=15,markerfacecolor='orange')
plt.plot(process,waiting_time,label='waiting_time',linewidth=3.0,marker='o',markersize=15,markerfacecolor='green')
plt.plot(process,response_time,label='response_time',linewidth=3.0,marker='o',markersize=15,markerfacecolor='red')


plt.yticks(fontsize=15)
plt.xticks(fontsize=15)

plt.xlabel('process',size=20,fontweight="bold")
plt.ylabel('Time',size=20,fontweight="bold")
plt.title('MLPQ', size=20,fontweight="bold")


plt.legend(prop={"size":14})
plt.savefig("graph/mlpq.png")
plt.show()


#---------------------------------------------------------------------------------------------#


del process[:]
del completion_time1[:]
del waiting_time1[:]
del turn_around_time1[:]
del completion_time[:]
del waiting_time[:]
del turn_around_time[:]
del response_time1[:]
del response_time[:]

with open("pNp.csv") as in_file:
	csv_reader = csv.reader(in_file,delimiter=" ")
	for line in csv_reader:
		process.append(line[0])
		waiting_time1.append(line[2])
		completion_time1.append(line[4])
		turn_around_time1.append(line[6])
		response_time1.append(line[8])

#print(waiting_time1)
#process =  [eval(i) for i in process1]
#print(process)
completion_time = [eval(i) for i in completion_time1]
#print(completion_time)
waiting_time = [eval(i) for i in waiting_time1]
#print(waiting_time)
turn_around_time = [eval(i) for i in turn_around_time1]
#print(turn_around_time)
response_time = [eval(i) for i in response_time1]

#plt.tick_params(axis='both', which='minor', labelsize=8)


plt.figure(figsize=(13,7))

plt.plot(process,turn_around_time,label='turn_around_time',linewidth=3.0,marker='o',markersize=15,markerfacecolor='blue')
plt.plot(process,completion_time,label='completion_time',linewidth=3.0,marker='o',markersize=15,markerfacecolor='orange')
plt.plot(process,waiting_time,label='waiting_time',linewidth=3.0,marker='o',markersize=15,markerfacecolor='green')
plt.plot(process,response_time,label='response_time',linewidth=3.0,marker='o',markersize=15,markerfacecolor='red')


plt.yticks(fontsize=15)
plt.xticks(fontsize=15)

plt.xlabel('process',size=20,fontweight="bold")
plt.ylabel('Time',size=20,fontweight="bold")
plt.title('pNp', size=20,fontweight="bold")


plt.legend(prop={"size":14})
plt.savefig("graph/pnp.png")
plt.show()


#-------------------------------------------------------------------------------------------------#


del process[:]
del completion_time1[:]
del waiting_time1[:]
del turn_around_time1[:]
del completion_time[:]
del waiting_time[:]
del turn_around_time[:]
del response_time1[:]
del response_time[:]
with open("pP.csv") as in_file:
	csv_reader = csv.reader(in_file,delimiter=" ")
	for line in csv_reader:
		process.append(line[0])
		waiting_time1.append(line[2])
		completion_time1.append(line[4])
		turn_around_time1.append(line[6])
		response_time1.append(line[8])

#print(waiting_time1)
#process =  [eval(i) for i in process1]
#print(process)
completion_time = [eval(i) for i in completion_time1]
#print(completion_time)
waiting_time = [eval(i) for i in waiting_time1]
#print(waiting_time)
turn_around_time = [eval(i) for i in turn_around_time1]
#print(turn_around_time)
response_time = [eval(i) for i in response_time1]

#plt.tick_params(axis='both', which='minor', labelsize=8)


plt.figure(figsize=(13,7))

plt.plot(process,turn_around_time,label='turn_around_time',linewidth=3.0,marker='o',markersize=15,markerfacecolor='blue')
plt.plot(process,completion_time,label='completion_time',linewidth=3.0,marker='o',markersize=15,markerfacecolor='orange')
plt.plot(process,waiting_time,label='waiting_time',linewidth=3.0,marker='o',markersize=15,markerfacecolor='green')
plt.plot(process,response_time,label='response_time',linewidth=3.0,marker='o',markersize=15,markerfacecolor='red')


plt.yticks(fontsize=15)
plt.xticks(fontsize=15)

plt.xlabel('process',size=20,fontweight="bold")
plt.ylabel('Time',size=20,fontweight="bold")
plt.title('pP', size=20,fontweight="bold")


plt.legend(prop={"size":14})
plt.savefig("graph/pP.png")
plt.show()
