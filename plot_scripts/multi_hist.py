#!/usr/bin/env python

import sys
import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
from scipy.optimize import curve_fit
from gauss import gauss, normalize

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
    y = t[0].iloc[:, 1] / t[0].iloc[:, 1].max()
    y = y/np.max(y)
    mean = np.average(x, weights = y)
    std = np.sqrt(np.sum(y * (x - mean)**2) / np.sum(y))
    p0 = [1, mean, std]
    params, covariance = curve_fit(gauss, x, y, p0 = p0)
    A_fit, mu_fit, sigma_fit = params
    y_fit = gauss(x, *params)
    plt.plot(x, y_fit, '-')#, label = "Fit " + t[1])
    plt.plot(x, y, 'o', label = t[1])
    plt.axvline(mean, color = 'black', linestyle='--', linewidth = 1, label = f"Mean = {mu_fit:.3f}")
    plt.legend(loc = 'best', prop = {'size': 8})

plt.xlim([0, 40])
plt.xlabel("Hamming Distance")
plt.ylabel("Cuentas")
plt.title("Histograma y ajuste gaussiano")
plt.grid()
plt.savefig(outfile, dpi = 300)

