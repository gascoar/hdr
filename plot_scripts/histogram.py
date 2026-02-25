#!/usr/bin/env python3

import sys
import pandas as pd
import numpy as np
from scipy.optimize import curve_fit
import matplotlib.pyplot as plt
from decimal import Decimal
from pathlib import Path

def Gauss(x, A, mean, sigma):
    fx = A * np.sqrt(2 * np.pi) * np.exp(- (x - mean) * (x - mean) / (2 * sigma * sigma))

    return fx

ifile = sys.argv[1]
if not Path(ifile).is_file():
    print("Error!")
    print("El archivo:", ifile, "no existe", file=sys.stderr)
    sys.exit()

outfile = sys.argv[2]
df = pd.read_csv(ifile)

x = df.iloc[:, 0]
y = df.iloc[:, 1]
n = np.sum(y)
nexp = '%.2E' % Decimal(n / 1.0)
A0 = np.max(y)
y = y/A0

mean = np.average(x, weights = y)
std = np.sqrt(np.sum(y * (x - mean)**2) / np.sum(y))
p0 = [1, mean, std]
params, covariance = curve_fit(Gauss, x, y, p0 = p0)
A_fit, mu_fit, sigma_fit = params
y_fit = Gauss(x, *params)


end_x = mean * 2
plt.plot(x, y, 'o', label='Data')
plt.plot(x, y_fit, '-', label='Fit')
plt.xlim([0, end_x])
plt.axvline(mean, color='green', linestyle='--', linewidth=2, label=f"Mean = {mu_fit:.3f}")
plt.axvline(mu_fit + sigma_fit, color='orange', linestyle=':',
            linewidth=2, label=f"μ + σ = {mu_fit + sigma_fit:.3f}")

plt.axvline(mu_fit - sigma_fit, color='orange', linestyle=':',
            linewidth=2, label=f"μ - σ = {mu_fit - sigma_fit:.3f}")
plt.xlabel("Hamming Distance")
plt.ylabel("Tasa repeticion")
plt.title("Histograma y ajuste\n (ndh = %s)" %nexp)
plt.legend(prop={'size': 8})
plt.grid()
plt.savefig(outfile, dpi = 300)