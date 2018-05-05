import numpy as np
from scipy.linalg import solve

# solve Ax = b using jacobi iteration
def jacobi_iter(A, b, init, iter_time):
    row = len(A)
    D_inv = np.diag(1.0 / np.diag(A))
    print 'D_inv:', D_inv
    R = np.eye(row) - np.dot(D_inv, A)
    g = np.dot(D_inv, b)
    x = init
    for i in xrange(iter_time):
        x = np.dot(R, x) + g
        print 'iter%d: x = ' % i, x.reshape(x.shape[0])

# solve Ax = b using Gauss-Seidel iteration
def gauss_iter(A, b, init, iter_time):
    L = np.tril(A, -1)
    D = np.diag(np.diag(A))
    U = np.triu(A, 1)
    S = np.dot(-np.linalg.inv(D + L), U)
    f = np.dot(np.linalg.inv(D + L), b)
    print L
    print D
    print U
    print S
    print f
    x = init
    for i in xrange(iter_time):
        error = x
        x = np.dot(S, x) + f
        error = max(abs(error - x))
        print 'iter%d: x = ' % i, x.reshape(x.shape[0])
        print 'error = ', error

A = np.array([5.0, -1, -1, 3, 6, 2, 1, -1, 2]).reshape((3,3))
b = np.array([16, 11, -2]).reshape((3,1))

gauss_iter(A, b, np.array([1.0,1,-1]).reshape((3,1)), 12)