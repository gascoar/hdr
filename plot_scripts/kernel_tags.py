#!/usr/bin/env python3

import sys
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.dates as mdates
from pathlib import Path
from datetime import datetime

ifile = sys.argv[1]
if not Path(ifile).is_file():
    print("Error!")
    print("El archivo:", ifile, "no existe", file=sys.stderr)
    sys.exit()

# TODO: check output dir
outfile = sys.argv[2]
# TODO: check args

df = pd.read_csv(ifile)

label = df.iloc[:, 0]
commits = df.iloc[:, 1] / 1000
dates_str = df.iloc[:, 2]
dates = []

for d in dates_str:
    dates.append(datetime.strptime(d, "%d-%m-%Y").date())

plt.plot(dates, commits, linestyle = '--', marker = 'o')
#for d, c, l in zip(dates, commits, label):
#    plt.text(d, c, l)
plt.annotate(
    label[0],
    xy = (mdates.date2num(dates[0]), commits[0]), xycoords = 'data',
    xytext = (-10, 40), textcoords = 'offset points',
    arrowprops = dict(arrowstyle = "-|>")
)
plt.annotate(
    label[10],
    xy = (mdates.date2num(dates[10]), commits[10]), xycoords = 'data',
    xytext = (-75, 0), textcoords = 'offset points',
    arrowprops = dict(arrowstyle = "-|>")
)
plt.annotate(
    label[9],
    xy = (mdates.date2num(dates[9]), commits[9]), xycoords = 'data',
    xytext = (-75, 0), textcoords = 'offset points',
    arrowprops = dict(arrowstyle = "-|>")
)
plt.annotate(
    label[8],
    xy = (mdates.date2num(dates[8]), commits[8]), xycoords = 'data',
    xytext = (-50, 0), textcoords = 'offset points',
    arrowprops = dict(arrowstyle = "-|>")
)
plt.annotate(
    label[7],
    xy = (mdates.date2num(dates[7]), commits[7]), xycoords = 'data',
    xytext = (-50, 0), textcoords = 'offset points',
    arrowprops = dict(arrowstyle = "-|>")
)
plt.annotate(
    label[6],
    xy = (mdates.date2num(dates[6]), commits[6]), xycoords = 'data',
    xytext = (-50, 0), textcoords = 'offset points',
    arrowprops = dict(arrowstyle = "-|>")
)
plt.annotate(
    label[5],
    xy = (mdates.date2num(dates[5]), commits[5]), xycoords = 'data',
    xytext = (50, 0), textcoords = 'offset points',
    arrowprops = dict(arrowstyle = "-|>")
)
plt.annotate(
    label[4],
    xy = (mdates.date2num(dates[4]), commits[4]), xycoords = 'data',
    xytext = (40, -10), textcoords = 'offset points',
    arrowprops = dict(arrowstyle = "-|>")
)
plt.grid()
plt.xlabel("Fecha")
plt.ylabel("Nro commits (miles)")
plt.title("Numero de commits (miles) vs años")
plt.savefig(outfile, dpi = 300)

delta = dates[9] - dates[7]
dcommits = commits[9] - commits[7]
m = dcommits/delta.days * 1000
print("delta:", delta)
print("celta commits:", dcommits)
print("pendiente:", m)
