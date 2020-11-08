from math import floor
import numpy as np
import matplotlib.pyplot as plt
import sys

def generate_samples(rate=1., n=100):
    return np.sort(np.random.exponential(scale=1.0, size=n))

if __name__ == "__main__":
    if len(sys.argv) > 1:
        n = int(sys.argv[1])
    else:
        n = 100
    if len(sys.argv) > 2:
        rate = float(sys.argv[2])
    else:
        rate = 1.
    print("Generating samples...")
    samples = generate_samples(rate=rate, n=n)
    print(samples)
    plt.hist(samples, bins=floor(np.sqrt(n)))
    plt.show()
