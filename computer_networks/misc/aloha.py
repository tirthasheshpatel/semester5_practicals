import numpy as np
import matplotlib.pyplot as plt
from scipy.stats import poisson


def simulate_aloha(max_G: int = 5) -> None:
    G = np.linspace(0.1, max_G, num=100)
    S = G * np.exp(-2 * G)
    dist = poisson(2 * G)
    rvs = dist.rvs(size=(1000, 100))
    plt.scatter(
        G, np.sum(rvs == 1, axis=0) / 2000, label="ALOHA random samples", alpha=0.5
    )
    plt.plot(G, S, label="ALOHA Throughput")
    plt.vlines(
        G[np.argmax(S)],
        0,
        np.max(S),
        label="Maximum ALOHA Throughput",
        linestyles="dashed",
        alpha=0.5,
    )
    plt.xticks(ticks=np.arange(0, max_G + 0.5, step=0.5))
    plt.yticks(ticks=np.linspace(0, np.max(S), num=10, endpoint=True))
    plt.title("$S = Ge^{-2G}$")
    plt.text(
        G[np.argmax(S)] + 0.05,
        np.max(S) + 0.01,
        f"ALOHA's Maximum Throughtput : {np.max(S):.2f}",
        fontdict={"size": 18},
    )
    plt.xlabel("frames/frame-time")
    plt.ylabel("Throughput")
    plt.legend()


def simulate_slotted_aloha(max_G: int = 5) -> None:
    G = np.linspace(0.1, max_G, num=100)
    S = G * np.exp(-G)
    dist = poisson(G)
    rvs = dist.rvs(size=(1000, 100))
    plt.scatter(
        G,
        np.sum(rvs == 1, axis=0) / 1000,
        label="Slotted ALOHA random samples",
        alpha=0.5,
    )
    plt.plot(G, S, label="Slotted ALOHA Throughput")
    plt.vlines(
        G[np.argmax(S)],
        0,
        np.max(S),
        label="Maximum Slotted ALOHA Throughput",
        linestyles="dashed",
        alpha=0.5,
    )
    plt.yticks(ticks=np.linspace(0, np.max(S), num=10, endpoint=True))
    plt.title("$S = Ge^{-G}$")
    plt.text(
        G[np.argmax(S)] + 0.05,
        np.max(S) + 0.01,
        f"Slotted ALOHA's Maximum Throughtput : {np.max(S):.2f}",
        fontdict={"size": 18},
    )
    plt.xlabel("frames/frame-time")
    plt.ylabel("Throughput")
    plt.legend()


if __name__ == "__main__":
    simulate_aloha()
    simulate_slotted_aloha()
    plt.show()
