import sys
import time

import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D


X = np.array([
    [0.0],
    [0.17],
    [0.33],
    [0.50],
    [0.67],
    [0.83],
    [1.0]
])
y = np.array([
    0.,
    0.,
    0.,
    0.,
    1.,
    1.,
    1.
])


num_epochs  = 2
num_neurons = 1
α           = 0.1


w = np.asarray([-0.36])
b = np.asarray(-0.1)


for _ in range(1, num_epochs+1):
    print(f"Epoch {_}")
    print(30*"-")
    for i in range(X.shape[0]):
        a = np.sum(w * X[i]) + b
        a = 1.*(a>=0) # promote the datatype to at least float
        e = a - y[i]
        w = w + α * e * X[i]
        b = b + α * e
        print(f"Training Example {i}: w = {w}, b = {b}, error : {e}")
    print(30*"-")


