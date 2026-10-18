import numpy as np
import matplotlib.pyplot as plt
from matplotlib.colors import LogNorm

Ek = np.loadtxt("pkt1Ek.csv",delimiter=',')
Ek = Ek.reshape(5,5,5)
dE0 = np.loadtxt("pkt1dE0.csv",delimiter=',')
dE0 = dE0.reshape(5,5)
dEsum = np.loadtxt("pkt1dEsum.csv",delimiter=',')
dEsum = dEsum.reshape(5,5)

plt.figure(figsize=(12,7))
plt.imshow(dE0,norm=LogNorm(),origin='lower')
plt.xlabel("N")
plt.ylabel("d")
plt.title(r"$\Delta E_0(N,d)$" + "\nzły podpis osi - poprawie w domu")
plt.colorbar()
plt.tight_layout()
plt.savefig("pkt1dE0.png")
plt.close()

plt.figure(figsize=(12,7))
plt.imshow(dEsum,norm=LogNorm(),origin='lower')
plt.xlabel("N")
plt.ylabel("d")
plt.title(r"$\Delta E_{sum}(N,d)$" + "\nzły podpis osi - poprawie w domu")
plt.colorbar()
plt.tight_layout()
plt.savefig("pkt1dEsum.png")
plt.close()

for i in range(5):
    plt.figure(figsize=(12,7))
    for j in range(5):
        plt.plot(Ek[i][j],label=rf"d_i={j}")
        # plt.scatter()
    plt.xlabel("k")
    plt.ylabel("E")
    plt.legend()
    plt.title(rf"N_i={i}")
    plt.tight_layout()
    plt.savefig(f"Ek_N{i}.png")
    plt.close()
