import numpy as np

def mse(X, X_new):
    return np.linalg.norm(X-X_new, axis=-1)

def cosine(X, X_new):
    return np.sum(X * X_new, axis=-1) / (np.linalg.norm(X, axis=-1) * np.linalg.norm(X_new))

X         =  [[85, 85], [75, 50], [60, 80], [72., 3]]
y         =  [0, 0, 1, 1, 1]
X_new     =  [72, 75]
k         =  3
dist_func = cosine
ordering  = "decending" # use decending for cosine similarities

X, y, X_new = map(np.asarray, [X, y, X_new])

if k%2 == 0:
    print("k can't be even!")
    exit(0)

dist = dist_func(X, X_new)
if ordering == "assending":
    print(f"Top {k} neighbors    : {(dist[np.argsort(dist)])[:k]}")
    print(f"Top {k} class label  : {(y[np.argsort(dist)])[:k]}")
    print(f"Predicted label      : {np.argmax([np.sum((y[np.argsort(dist)])[:k] == 0), np.sum((y[np.argsort(dist)])[:k] == 1)])}")
else:
    print(f"Top {k} neighbors    : {(dist[np.argsort(dist)])[-k:][::-1]}")
    print(f"Top {k} class label  : {(y[np.argsort(dist)])[-k:][::-1]}")
    print(f"Predicted label      : {np.argmax([np.sum((y[np.argsort(dist)])[-k:][::-1] == 0), np.sum((y[np.argsort(dist)])[-k:][::-1] == 1)])}")

