#!/usr/bin/env python

import sys
import pandas as pd
import matplotlib.pyplot as plt

def uso():
    print("multi_hist: <output file> <input file1> <label1> <input file2> <label2> <input file3> <label3>")


arglen = len(sys.argv)
if arglen < 2 or (arglen % 2):
    uso()
    raise ValueError("Incorrect number of arguments")

outfile = sys.argv[1]
l = []

for i in range(2, len(sys.argv), 2):
    df = pd.read_csv(sys.argv[i])
    label = sys.argv[i + 1]
    l.append((df, label))

plt.figure()
for t in l:
    x = t[0].iloc[:, 0]
    y = t[0].iloc[:, 1]
    plt.bar(x, y, label = t[1], width = 0.8)
    plt.legend(loc = 'best')
plt.xlim([0, 60])
plt.xlabel("Hamming Distance")
plt.ylabel("Cuentas")
plt.title("Histogram")
plt.grid()
plt.savefig(outfile)

