import numpy as np

X = np.array([
  [1.1, 1.7, 1.8],
  [0.0, 0.0, 0.0],
  [0.0, 0.5, 1.5],
  [1.0, 0.0, 0.0],
  [0.5, 0.5, 0.5],
  [1.0, 1.0, 1.0]
])

w = np.array([
  [0.2, 0.7, 0.3],
  [0.1, 0.1, 0.9],
  [1.0, 1.0, 1.0]
])

eta    = 0.5
epochs = 2

for _ in range(1, epochs+1):
  print(f"Epoch: {_}")
  print(50*"-")
  for i in range(X.shape[0]):
    a = 1./np.linalg.norm(w - X[i][None, :], axis=1)
    a = a.ravel()
    print(f"a: {a}")
    winner = np.argmax(a)
    print(f"Winner neuron: {winner+1}")
    w[winner] += eta * (X[i] - w[winner])
    print(f"Updated weights of the neuron: {w[winner]}")
  print(50*"-")
