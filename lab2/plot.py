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
kappa = np.loadtxt("pkt2kappa.csv",delimiter=',')
kappa = kappa.reshape(5,5,5)

N=np.arange(11,32,5)
d=np.arange(3,8,1)
beta=np.arange(0.1,0.6,0.1)

plt.figure(figsize=(8,7))
plt.pcolormesh(N,d,np.abs(dE0).T,norm=LogNorm())
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
plt.pcolormesh(N,d,np.abs(dEsum).T,norm=LogNorm())
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

# petla po beta
for idb in range(5):
    plt.figure(figsize=(12,7))
    # petla po N
    for idN in range(5):
        plt.semilogy(d,kappa[idN,:,idb],label=rf"$N={N[idN]}$")
    plt.title(rf"$\beta={beta[idb]:.1f}$")
    plt.xlabel(r"$d$ [\unit{\nano\meter}]")
    plt.ylabel(r"$\kappa(d)$")
    plt.legend()
    plt.tight_layout()
    plt.savefig(f"kb{idb}.png",dpi=150)
    plt.close()

plt.figure(figsize=(12,7))
for idN in range(5):
    plt.plot(beta,kappa[idN,0,:],label=rf'$N={N[idN]}$')
    plt.scatter(beta,kappa[idN,0,:])
plt.legend()
plt.yscale('log')
plt.grid(ls=":")
plt.xlabel(r"$\beta$")
plt.ylabel(r"$\kappa(\beta)$")
plt.tight_layout()
plt.savefig("kappa.png")
plt.close()
