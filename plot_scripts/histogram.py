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

def normalize(mu, sigma):
    s = 0
    for k in range(0, 161):
        s = s + np.exp(- (k - mu) * (k - mu) / (2 * sigma * sigma))

    return s

ifile = sys.argv[1]
if not Path(ifile).is_file():
    print("Error!")
    print("El archivo:", ifile, "no existe", file=sys.stderr)
    sys.exit()

# TODO: check output dir
outfile = sys.argv[2]
# TODO: check args
alen = sys.argv[3]
repo = sys.argv[4]

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
y_fit = Gauss(x, *params) / normalize(mu_fit, sigma_fit)

textstr = '\n'.join((
    'alen = $%s$' % (alen, ),
    'Nro DH = $%.2E$' % (Decimal(n / 1.0), ),
    "".join(['Repo: ', repo])))

props = dict(boxstyle = 'round', facecolor = 'azure', edgecolor = 'grey', alpha = 0.5)

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
plt.title("Histograma")
plt.legend(prop={'size': 8})
plt.text(0.70, 0.85, textstr, fontsize = 9, bbox = props)
plt.grid()
plt.savefig(outfile, dpi = 300)


p = Gauss(0, A_fit, mu_fit, sigma_fit) / normalize(mu_fit, sigma_fit)
print("prob:", p)
ncom = 1/p
print("nro M commits: ", ncom/1000000)
alpha = 0.95
N = np.log(1 - alpha) / np.log(1 - p)
print("nro commits con 95% confianza: ", N / 1000000)

