import numpy as np
import matplotlib.pyplot as plt

psifile = np.loadtxt("psifile.csv",delimiter=',')

x=psifile[:,0]

plt.figure(figsize=(12,7))
for n in range(6):
    plt.plot(x,psifile[:,n+1])
plt.tight_layout()
plt.savefig("psi.png",dpi=150)
plt.close()

plt.figure(figsize=(12,7))
for n in range(6):
    plt.plot(x[:-1],np.diff(psifile[:,n+1])/np.diff(x))
plt.tight_layout()
plt.savefig("psiprim.png",dpi=150)
plt.close()
