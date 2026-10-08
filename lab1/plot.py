import numpy as np
import matplotlib.pyplot as plt
plt.rcParams.update({
    "pgf.texsystem": "lualatex",
    "pgf.rcfonts": False,
    "font.family": "serif",
    "font.size": 20,
    "pgf.preamble": r"""
        \usepackage{amsmath}
        \usepackage{fontspec}
        \usepackage{unicode-math}
        \setmainfont{STIX Two Text}
        \setmathfont{STIX Two Math}
        \usepackage{siunitx}
    """,
})

t = np.loadtxt("tfile.csv",delimiter=',')
u = np.loadtxt("ufile.csv",delimiter=',')
n = np.loadtxt("nfile.csv",delimiter=',')
Sn = np.loadtxt("Snfile.csv",delimiter=',')
Dn = np.loadtxt("Dnfile.csv",delimiter=',')

plt.figure(figsize=(12,7))
plt.plot(n,Sn)
plt.scatter(n,Sn)
plt.grid(ls=":")
plt.xlabel(r"$n$")
plt.ylabel(r"$S_n$")
# plt.title(r"$S_n$ w funkcji $n$")
plt.tight_layout()
plt.savefig("Sn.png",dpi=150)
plt.close()

# print(u.shape)

plt.figure(figsize=(12,7))
for i in range(7):
    plt.plot(t,u[i,:],label=f"n={n[i]:.0f}")
plt.legend()
plt.title(r"$u_n(x)$ dla różnych $n$")
plt.xlabel(r"$x$")
plt.ylabel(r"$u_n(x)$")
plt.grid(ls=":")
plt.tight_layout()
plt.savefig("u.png",dpi=150)
plt.close()

plt.figure(figsize=(12,7))
plt.plot(n,u[:,u.shape[1]//2])
plt.scatter(n,u[:,u.shape[1]//2])
# plt.title(r"$u_n(0)$ w funkcji $n$")
plt.xlabel(r"$n$")
plt.ylabel(r"$u_n(0)$")
plt.grid(ls=":")
plt.tight_layout()
plt.savefig("u0.png",dpi=150)
plt.close()

plt.figure(figsize=(12,7))
plt.plot(n[1:],Dn)
plt.scatter(n[1:],Dn)
plt.yscale('log')
plt.grid(ls=":")
plt.xlabel(r"$n$")
plt.ylabel(r"$D_n$")
plt.tight_layout()
plt.savefig("Dn.png",dpi=150)
plt.close()
