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
model.add(Dense(1, activation="sigmoid"))
model.compile(loss="mse", optimizer="rmsprop")
model.fit(inputs, outputs, nb_epoch=10000)

print "Model loss: %4f" % model.evaluate(inputs, outputs)

# check
print tests
print "MODEL(0) ~= %4f" % model.predict(tests[0,:].reshape(1,3))
print "MODEL(1) ~= %4f" % model.predict(tests[1,:].reshape(1,3))
print "MODEL(2) ~= %4f" % model.predict(tests[2,:].reshape(1,3))
print "MODEL(3) ~= %4f" % model.predict(tests[3,:].reshape(1,3))
print "MODEL(4) ~= %4f" % model.predict(tests[4,:].reshape(1,3))
print "MODEL(5) ~= %4f" % model.predict(tests[5,:].reshape(1,3))
print "MODEL(6) ~= %4f" % model.predict(tests[6,:].reshape(1,3))

