import matplotlib.pyplot as plt
import numpy as np
import csv

algorithm = ['a','b','c','d','e','f','g','h']
turn_around_time1 = []
completion_time1 = []
waiting_time1 = []
response_time1 = []

with open("data.csv") as in_file:
	csv_reader = csv.reader(in_file,delimiter=" ")
	for line in csv_reader:
		waiting_time1.append(line[0])
		completion_time1.append(line[2])
		turn_around_time1.append(line[4])
		response_time1.append(line[6])
        
avg_completion_time = [eval(i) for i in completion_time1]
print(avg_completion_time)
avg_waiting_time = [eval(i) for i in waiting_time1]
print(avg_waiting_time)
avg_turn_around_time = [eval(i) for i in turn_around_time1]
print(avg_turn_around_time)
avg_response_time = [eval(i) for i in response_time1]
print(avg_response_time)

barWidth = 0.1
fig = plt.subplots(figsize = (16,11))
# Set position of bar on X axis
br1 = np.arange(len(avg_waiting_time))
br2 = [x + barWidth for x in br1]
br3 = [x + barWidth for x in br2]
br4 = [x + barWidth for x in br3]
 
# Make the plot
plt.bar(br1, avg_waiting_time, color ='r', width = barWidth,
        edgecolor ='grey', label ='avg_waiting_time')
plt.bar(br2, avg_waiting_time, color ='g', width = barWidth,
        edgecolor ='grey', label ='avg_completion_time')
plt.bar(br3, avg_turn_around_time, color ='b', width = barWidth,
        edgecolor ='grey', label ='avg_turn_around_time')
plt.bar(br4, avg_response_time, color ='orange', width = barWidth,
        edgecolor ='grey', label ='avg_response_time')
 
# Adding Xticks
plt.yticks(fontsize=20)
plt.xlabel('Algorithms', fontweight ='bold', fontsize = 15)
plt.ylabel('time', fontweight ='bold', fontsize = 15)
plt.xticks([r + barWidth for r in range(len(avg_waiting_time))],
        ['fcfs','sjfNp','sjfP','rr','mlfq','mlpq','pNp','pP'],fontsize=25)
 
plt.title("Avg time comparison")
plt.legend()
plt.savefig("graph/comparison.png")
plt.show()
