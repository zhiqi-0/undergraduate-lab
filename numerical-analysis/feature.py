import numpy as np
import numpy

def max_power(A, X, step_num):
    X_old = X
    for step in xrange(step_num):
        X_new = np.dot(A, X_old)
        print 'step %d:' %(step + 1), X_new.flatten()
        print 'lambda: ', (X_new / X_old).flatten()
        print 'feature vector1: ', (X_new + (X_new / X_old)[len(X_old) - 1] * X_old).flatten()
        print 'feature vector2: ', (X_new - (X_new / X_old)[len(X_old) - 1] * X_old).flatten()
        X_old = X_new

def min_power(A, X, step_num):
    Ainv = np.linalg.inv(A)
    print Ainv
    X_old = X
    for step in xrange(step_num):
        X_new = np.dot(Ainv, X_old)
        print 'step %d:' %(step + 1)
        print 'Yk:', X_old.flatten()
        print 'Xk+1', X_new.flatten()
        #print 'feature vector1: ', (X_new + (X_new / X_new)[len(X_old) - 1] * X_old).flatten()
        #print 'feature vector2: ', (X_new - (X_new / X_old)[len(X_old) - 1] * X_old).flatten()
        X_old = X_new / max(X_new)
"""
A = np.array([5., -3., -6., -2.]).reshape((2,2))
X = np.array([1.,1.]).reshape((2,1))
max_power(A, X, 20)
"""
A = np.array([5.,3.,-2.,0.]).reshape((2,2))
X = np.array([1,1]).reshape((2,1))
min_power(A, X, 20)