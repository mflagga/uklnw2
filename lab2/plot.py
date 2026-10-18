import numpy as np
import matplotlib.pyplot as plt
from matplotlib.colors import LogNorm
plt.rcParams.update({
    "text.usetex": True,
    "font.family": "serif",
    "font.serif": ["Computer Modern Roman"],
    "font.size": 20,
    "text.latex.preamble": r"""
        \usepackage{siunitx}
    """,
})

Ek = np.loadtxt("pkt1Ek.csv",delimiter=',')
Ek = Ek.reshape(5,5,5)
dE0 = np.loadtxt("pkt1dE0.csv",delimiter=',')
dE0 = dE0.reshape(5,5)
dEsum = np.loadtxt("pkt1dEsum.csv",delimiter=',')
dEsum = dEsum.reshape(5,5)

N=np.arange(11,32,5)
d=np.arange(3,8,1)

plt.figure(figsize=(8,7))
plt.pcolormesh(N,d,np.abs(dE0),norm=LogNorm())
plt.xlabel(r"$N$")
plt.ylabel(r"$d$ [\unit{\nano\meter}]")
plt.xticks(N)
plt.yticks(d)
plt.title(r"$\Delta E_0(N,d)$")
plt.colorbar()
plt.tight_layout()
plt.savefig("pkt1dE0.png",dpi=150)
plt.close()

plt.figure(figsize=(8,7))
plt.pcolormesh(N,d,np.abs(dEsum),norm=LogNorm())
plt.xlabel(r"$N$")
plt.ylabel(r"$d$ [\unit{\nano\meter}]")
plt.xticks(N)
plt.yticks(d)
plt.title(r"$\Delta E_{sum}(N,d)$")
plt.colorbar()
plt.tight_layout()
plt.savefig("pkt1dEsum.png",dpi=150)
plt.close()

# petla po k
for idk in range(5):
    plt.figure(figsize=(12,7))
    # petla po N
    for idN in range(5):
        plt.plot(d,Ek[idN,:,idk],label=rf"$N={N[idN]}$")
        plt.scatter(d,Ek[idN,:,idk])
    plt.xlabel(r"$d$ [\unit{\nano\meter}]")
    plt.ylabel(r"$E_k$ [\unit{\milli\electronvolt}]")
    plt.legend()
    plt.title(rf"$k={idk}$")
    plt.grid(ls=":")
    plt.tight_layout()
    plt.savefig(f"Ek{idk}.png",dpi=150)
    plt.close()
