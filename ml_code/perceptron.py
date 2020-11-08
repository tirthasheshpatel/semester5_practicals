import numpy as np

def fun(n):
    a = [int(i>=0) for i in n]
    return a

X         = [1.]
y         = [0.]
w         = [8.]
b         = [-3.]

epochs    = 1
alpha     = 1


X, y, w, b= np.asarray(X), np.asarray(y), np.asarray(w), np.asarray(b)

for i in range(1, epochs+1):
    print(f"Epoch {i}")
    print(32*"-")
    n = X*w + b
    a = fun(n)
    e = a - y
    
    w = w + alpha*e*X
    b = b + alpha*e
    
    print(f"n : {n}")
    print(f"a : {a}")
    print(f"e : {e}")
    print(f"w_new : {w.ravel()}")
    print(f"b_new : {b.ravel()}")
   
    print(32*"-")
