import numpy as np
from sklearn.metrics import precision_score, recall_score, f1_score, accuracy_score

def accuracy(y, preds):
    return accuracy_score(y, preds)

def recall(y, preds):
    return recall_score(y, preds)

def precision(y, preds):
    return precision_score(y, preds)

def f1(y, preds):
    return f1_score(y, preds)

