#!/usr/bin/env python

import sys
import pandas as pd
import matplotlib.pyplot as plt

if len(sys.argv) < 2:
    raise ValueError("Incorrect number of arguments")

outfile = sys.argv[1]
df_list = []
x_axes = []
y_axes = []

for i in range(2, len(sys.argv)):
    df_list.append(pd.read_csv(sys.argv[i]))

for df in df_list:
    x_axes.append(df.iloc[:,0])
    y_axes.append(df.iloc[:, 1])

plt.figure()
x = x_axes[1]
for y in y_axes:
    plt.bar(x, y, width = 0.8)
plt.xlabel("Hamming Distance")
plt.ylabel("Cuentas")
plt.title("Histogram")
plt.grid()
plt.savefig(outfile)

