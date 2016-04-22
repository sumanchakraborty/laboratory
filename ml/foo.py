#!/usr/bin/python

import numpy as np
import matplotlib.pyplot as plot

class Neural_Network(object):
    def __init__(self):
        self.inputLayerSize = 2
        self.outputLayerSize = 1
        self.hiddenLayerSize = 3

        # weights
        self.W1 = np.random.randn(self.inputLayerSize, \
                                  self.hiddenLayerSize)
        self.W2 = np.random.randn(self.hiddenLayerSize, \
                                  self.outputLayerSize)

    def sigmoid(self, z):
        return 1/(1+np.exp(-z))

    def sigmoidPrime(self, z):
        return np.exp(-z)/((1+np.exp(-z))**2)

    def costPrime(self, X, Y):
        self.yHat = self.forward(X)
        delta3 = np.multiply(-(Y-self.yHat), self.sigmoidPrime(self.z3))
        dJdw2 = np.dot(self.a2.T, delta3)
        delta2 = np.dot(delta3, self.W2.T)*self.sigmoidPrime(self.z2)
        dJdw2 = np.dot(X.T, delta2)

        return dJdW1, dJdW2

    def forward(self, X):
        self.z2 = np.dot(X, self.W1)
        self.a2 = self.sigmoid(self.z2)
        self.z3 = np.dot(self.a2, self.W2)
        yHat = self.sigmoid(self.z3)
        return yHat

    def test():
        testInput = np.arange(-6,6,0.01)
        plot(testInput, sigmoid(testInput), linewidth=2)
        grid(1)


X = np.matrix('3 5; 5 1; 10 2')
Y = np.matrix('75; 82; 93')

# NN = Neural_Network()
# cost1 = NN.costPrime(X, Y)
# dJdW1, dJdW2 = NN.costPrime(X, Y)

# print yHat

plot.plot(Y)
plot.grid(1)
plot.ylabel('Cost')
plot.xlabel('Iterations')
plot.show()



