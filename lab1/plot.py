import numpy as np
import matplotlib.pyplot as plt

t = np.loadtxt("tfile.csv",delimiter=',')
u = np.loadtxt("ufile.csv",delimiter=',')
n = np.loadtxt("nfile.csv",delimiter=',')
Sn = np.loadtxt("Snfile.csv",delimiter=',')

plt.figure(figsize=(12,7))
plt.plot(n,Sn)
plt.title("S_n w funkcji n")
plt.tight_layout()
plt.savefig("Sn.png",dpi=150)
plt.close()

# print(u.shape)

plt.figure(figsize=(12,7))
for i in range(7):
    plt.plot(t,u[i,:],label=f"n={n[i]:.0f}")
plt.legend()
plt.title("u_n(x) dla roznych n")
plt.tight_layout()
plt.savefig("u.png",dpi=150)
plt.close()

plt.figure(figsize=(12,7))
plt.plot(n,u[:,u.shape[1]//2])
plt.title("u_n(0) w funkcji n")
plt.tight_layout()
plt.savefig("u0.png",dpi=150)
plt.close()
