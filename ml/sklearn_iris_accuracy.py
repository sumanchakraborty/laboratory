#!/usr/bin/python

import numpy as np
from sklearn import tree
from sklearn import datasets

iris = datasets.load_iris()

X = iris.data
y = iris.target

from sklearn.cross_validation import train_test_split
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size = .5)

clf = tree.DecisionTreeClassifier()
clf = clf.fit(X_train, y_train)

predictions = clf.predict(X_test)

from sklearn.metrics import accuracy_score
print predictions
print accuracy_score(y_test, predictions)

# print test_target
# print clf.predict(test_data)
