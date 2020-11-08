import sys
import time

import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D


X = np.array([
    [0, 0],
    [0, 1],
    [1, 0],
    [1, 1.]
])
y = np.array([
    [0.],
    [0.],
    [0.],
    [1.]
])


num_epochs  = 10
num_neurons = 1
α           = 0.01


w = np.random.randn(num_neurons, X.shape[1])
b = np.random.randn(num_neurons, 1)


for _ in range(1, num_epochs+1):
    for i in range(X.shape[0]):
        y = w @ X[i][:, None] + b
        a = 1.*(y>=0) # promote the datatype to at least float
        e = a - y
        w = w + α * e * X[i]
        b = b + α * e
    sys.stdout.write(f"\rEpoch {_}: w = {w}, b = {b}")
    time.sleep(0.5)


x = np.linspace(0., 1., num=100)
z = np.linspace(0., 1., num=100)
grid = np.meshgrid(x, z)


grid = np.asarray(grid).reshape(100, 100, 2, 1)
y_grid = w @ grid + b


fig = plt.figure(figsize=(10, 9))
ax = fig.add_subplot(111, projection='3d')
ax.scatter(X[:, 0], X[:, 1], y)
ax.plot_surface(grid[:, :, 0, 0], grid[:, :, 1, 0], y_grid[:, :, 0, 0])
plt.show()

