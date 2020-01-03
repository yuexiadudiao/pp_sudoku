#!/usr/local/bin/python3
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

#param
isnormalize = False


#read data from txt file  
a = pd.read_table('./dlx_timelog.txt')
b = pd.read_table('./pp_timelog.txt')
c = pd.read_table('./bf_timelog.txt')
#set labels
bins = [0,0.1,1,10,100,1000,10000]
labels = ['0-0.1','0.1-1','1-10','10-100','100-1000','1000-10000']
#cut data with label
mha = pd.cut(a.dlx_time, bins, labels=labels)
mhb = pd.cut(b.pp_time, bins, labels=labels)
mhc = pd.cut(c.bf_time, bins, labels=labels)
#count for series
s1 = mha.value_counts(sort=False,normalize=isnormalize)
s2 = mhb.value_counts(sort=False,normalize=isnormalize)
s3 = mhc.value_counts(sort=False,normalize=isnormalize)
#create dataframe with series
e = pd.DataFrame([s1,s2,s3])
#rotate dataframe and plot bar
e.T.plot.bar()
#show it
plt.legend()
plt.xlabel('time(ms)')
plt.ylabel('counts')
plt.subplots_adjust(bottom=0.25)
plt.show()
