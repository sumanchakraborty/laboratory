#!/usr/bin/python

from keras.models import Sequential
from keras.layers.core import Dense, Dropout, Activation
import numpy as np
import pandas as pd

df = pd.read_csv("keras_sequence.train.data.csv")
inputs = df[['S1','S2','S3']].as_matrix()
outputs = df[['R']].as_matrix()

# test data
test_csv = pd.read_csv("keras_sequence.test.data.csv")
tests = test_csv[['S1','S2','S3']].as_matrix()

model = Sequential()
model.add(Dense(4, input_dim=3, activation="sigmoid"))
model.add(Dense(4, activation="sigmoid"))
model.add(Dense(1, activation="sigmoid"))

model.compile(loss="mse", optimizer="rmsprop")
model.fit(inputs, outputs, nb_epoch=10000)

print model.summary()
print "Model loss: %4f" % model.evaluate(inputs, outputs)

# check
print test_csv
for index, row in df.iterrows():
    print "ROWs ~= %4f" % model.predict(tests[index,:].reshape(1,3))

