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

architecture = [1, 0, 2]
def eta(t)   :
               if t <= 6  : return 0.5
               if t <= 12 : return 0.25
               else       : return 0.1
epochs       = 3
def D(t)     : return 1 if t <= 6 else 0

t = 1
for _ in range(1, epochs+1):
  print(f"Epoch: {_}")
  print(50*"-")
  for i in range(X.shape[0]):
    print(f"At time t = {t}")
    a = 1./np.linalg.norm(w - X[i][None, :], axis=1)
    a = a.ravel()
    print(f"a: {a}")
    winner = np.argmax(a)
    print(f"Winner neuron: {winner+1}")
    num_updates = D(t)
    neighbors = [winner]
    if num_updates > 0:
      j = architecture.index(winner)
      k = 1
      while k <= num_updates:
        if j+k >= 0 and j+k < len(architecture): neighbors.append(architecture[j+k])
        if j-k >= 0 and j-k < len(architecture): neighbors.append(architecture[j-k])
        k += 1
    print(f"Neurons to be updated: {list(n+1 for n in neighbors)}")
    for neuron in neighbors:
    	w[neuron] += eta(t) * (X[i] - w[neuron])
    print(f"Updated weights:")
    print(f"{w=}")
    t += 1
  print(50*"-")
