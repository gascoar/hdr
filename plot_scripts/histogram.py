import sys
import pandas as pd
import matplotlib.pyplot as plt

ifile = sys.argv[1]
df = pd.read_csv(ifile)

x = df.iloc[:, 0]
y = df.iloc[:, 1]

plt.figure()
plt.bar(x, y, width = 0.8)
plt.xlabel("Hamming Distance")
plt.ylabel("Cuentas")
plt.title("Histogram")
plt.grid()
plt.show()
