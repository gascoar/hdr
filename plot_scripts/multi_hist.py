import sys
import pandas as pd
import matplotlib.pyplot as plt

if sys.argv.len() < 2:


ifile1 = sys.argv[1]
ifile2 = sys.argv[2]
ifile3 = sys.argv[3]
ifile4 = sys.argv[4]
outfile = sys.argv[5]

df1 = pd.read_csv(ifile1)
df2 = pd.read_csv(ifile2)
df3 = pd.read_csv(ifile3)
df4 = pd.read_csv(ifile4)

x = df1.iloc[:, 0]
y1 = df1.iloc[:, 1]
y2 = df2.iloc[:, 1]
y3 = df3.iloc[:, 1]
y4 = df4.iloc[:, 1]

plt.figure()
plt.bar(x, y1, width = 0.8)
plt.bar(x, y2, width = 0.8)
plt.bar(x, y3, width = 0.8)
plt.bar(x, y4, width = 0.8)
plt.xlabel("Hamming Distance")
plt.ylabel("Cuentas")
plt.title("Histogram")
plt.grid()
plt.savefig(outfile)
