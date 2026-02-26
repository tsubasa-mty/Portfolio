import matplotlib.pyplot as plt
import numpy as np
plt.rcParams["axes.unicode_minus"] = False  # マイナス記号が文字化けする場合の対策

#初期条件
k1 = 0.3
k_1 = 0.4
a = 5
A = a*k1/k_1
x0_list = [0, 0.01, 0.5, 1.5, A, 5.0]


t0 = 0
t_end = 10
h = 0.1 # ステップサイズ
# 時間配列と解の初期化
t_values = np.arange(t0, t_end + h, h)

def f(x, k1, a, k_1):
    return k1*a*x - k_1*x*x

def R4(x,f,h):
    l1 = f(x, k1, a, k_1)*h
    l2 = f(x + l1/2, k1, a, k_1)*h
    l3 = f(x + l2/2, k1, a, k_1)*h
    l4 = f(x + l3, k1, a, k_1)*h
    x_next = x + (l1 + 2*l2 + 2*l3 + l4)/6
    return x_next

fig,ax = plt.subplots()
for x0 in x0_list:
    x = x0
    x_values = [x0]

    for t in t_values[:-1]:
        x = R4(x,f,h)
        x_values.append(x)

    ax.plot(t_values, x_values, label = f"x0 = {x0}")
    ax.set_xlabel("t")
    ax.set_ylabel("x(t)")
    ax.set_title("Trajectory of RK4 Method in Autocatalytic Reaction")
    ax.set_xlabel("t")
    ax.legend()
    ax.grid(True)

plt.savefig("rk4_simulation.png", dpi=300)
print("Graph saved as rk4_simulation.png")