#!/bin/python

import sys
import numpy as np
import pandas as pd
from scipy.optimize import curve_fit
from gauss import gauss, normalize
from pathlib import Path
import matplotlib.pyplot as plt

ifile = sys.argv[1]
if not Path(ifile).is_file():
    print("Error!")
    print("El archivo:", ifile, "no existe", file=sys.stderr)
    sys.exit()

df = pd.read_csv(ifile)

x = df.iloc[:, 0]
y = df.iloc[:, 1]
n = np.sum(y)
A0 = np.max(y)
y = y/n

mean = np.average(x, weights = y)
std = np.sqrt(np.sum(y * (x - mean)**2) / np.sum(y))
p0 = [1, mean, std]
params, covariance = curve_fit(gauss, x, y, p0 = p0)
A_fit, mu_fit, sigma_fit = params
#y_fit = gauss(x, *params) / normalize(mu_fit, sigma_fit)
y_fit = gauss(x, *params)


# total hist
S = 0
for k in y:
    S = S + k
print("- Total prob hist:", S)
# just a check
s = 0.0
for i in range(0, len(y_fit)):
    s = s + y_fit[i]
print("- Total prob fit:", s)

prob0 = y_fit[0]
print("prob:", prob0)
ndh = 1 / prob0
print("nro DH (millones): ", ndh/1000000)
n = 2 * np.sqrt(ndh)
print("Nro commits estimado:", n)
alpha = 0.95
ndh95 = np.log(1 - alpha) / np.log(1 - prob0)
print("nro DH con 95% confianza: ", ndh95)
n95 = 2 * np.sqrt(ndh95)
print("nro commits con 95% confianza: ", n95)
