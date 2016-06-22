#!/usr/bin/python

import numpy as np
import seaborn as sns
from sklearn.datasets import load_iris
from sklearn import tree

iris = sns.load_dataset("iris")

sns_plot = sns.pairplot(iris, hue='species', size=2.5)
sns_plot.savefig("output.png")

