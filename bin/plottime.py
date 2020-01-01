#!/usr/local/bin/python3
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
  
a = pd.read_table('./time_log.txt')
bins = [0,1,10,100,1000,10000]
labels = ['0-1','1-10','10-100','100-1000','1000-10000']
mh = pd.cut(a.time, bins, labels=labels)
print(mh.value_counts(sort=False))

#not sort bar
mh.value_counts(sort=False).plot.bar()
#show it
plt.xlabel('time(ms)')
plt.ylabel('counts')
plt.subplots_adjust(bottom=0.25)
plt.show()
