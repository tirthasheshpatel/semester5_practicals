import numpy as np
from sklearn.metrics import precision_score, recall_score

y      = None
y_pred = None
metric = accuracy

def accuracy(y, preds):
    return (1.0 / y.shape[0]) * np.sum(y == (preds > 0.5))

def recall(y, preds):
    tp = np.sum((y == 1) & ((preds > 0.5) == 1))
    fn = np.sum((y != 0) & ((preds > 0.5) == 0))
    return tp / (tp + fn)

def pre(y, preds):
    tp = np.sum((y == 1) & ((preds > 0.5) == 1))
    fp = np.sum((y != 1) & ((preds > 0.5) == 1))
    return tp / (tp + fp)

def f1(y, preds):
    rec = recall(y, preds)
    prec = pre(y, preds)
    return 2.0 * rec * prec / (rec + prec)


print(f"{metric(y, y_pred)}")
