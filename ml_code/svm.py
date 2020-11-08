from pprint import pprint

import numpy as np
from sklearn.svm import SVC

X = [[1, 2], [0, 1], [1, 1], [2, 1], [3, 1]]
y = [1, 0, 0, 1, 1]
X_new = None

X, y = np.asarray(X, dtype=np.float_), np.asarray(y, dtype=np.float_)

model = SVC(kernel='linear')

model.fit(X, y)

pprint(model.support_vectors_)


