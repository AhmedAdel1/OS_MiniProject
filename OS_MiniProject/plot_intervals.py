## this is a python script to plot some processes with their working intervals

import matplotlib.pyplot as plt
import numpy as np

ids = []
intervals = []

f = open("intervals.txt", "r")
for x in f:
	ids.append(int(x.split()[0]))
	intervals.append(round(float(x.split()[1]),2))
ids.insert(0,-1)
ids.insert(0,-1)

intervals.insert(0,intervals[0])
intervals.insert(0,0)
#print(ids)
#print(intervals)


plt.figure(figsize=(20,5))
plt.yticks(np.arange(-1,max(ids)+1,1))
plt.xticks(np.arange(-1,max(intervals)+1,max(intervals)/20))
plt.plot(intervals,ids)
plt.ylabel('Process ID')
plt.xlabel('Running Time')
plt.grid(True)
plt.show()
