## this is a python script to plot some processes with their working intervals

import matplotlib.pyplot as plt
import numpy as np

ids = []
intervals = []

f = open("intervals.txt", "r")
for x in f:
	ids.append(int(x.split()[0]))
	intervals.append(x.split()[1])
	

#print(ids)
#print(intervals)


plt.figure(figsize=(20,5))
plt.yticks(np.arange(-1,max(ids)+1,1))
plt.plot(intervals,ids)
plt.ylabel('Process ID')
plt.xlabel('Running Time')
plt.show()
