import numpy as np

X     =  [[8, 4], [4, 6], [9, 0], [2., 5], [3, 4]]
y     =  [0., 1, 1, 1, 0]
X_new =  None

X, y = np.asarray(X), np.asarray(y)
if X_new is not None:
    X_new = np.asarray(X_new)

y = y.reshape(-1, 1)
if X_new is not None:
    X_new = X_new.reshape(-1, 1)

X = np.c_[np.ones(X.shape[0], dtype=X.dtype), X]
if X_new is not None:
    X_new = np.c_[np.ones(X_new.shape[0], dtype=X_new.dtype), X_new]

try:
    # Ax = b
    # x_hat = (A.T @ A)^(-1) @ A.T @ b
    w = np.linalg.pinv(X) @ y
except np.linalg.LinAlgError:
    print("X is not invertible!")
    exit(0)

print(f"Best weights : {w.ravel()}")
print(f"Best loss (on training data) : {0.5 * np.mean((y-X@w)**2)}")
print(f"Best prediction (on training data) : {(X@w).ravel()}")
if X_new is not None:
    print(f"Best prediction (on testing data) : {(X_new@w).ravel()}")
