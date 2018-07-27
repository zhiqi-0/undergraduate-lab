import numpy as np

# solve Ax = b using Gauss-Seidel iteration
def gauss_iter(A, b, init, iter_time):
    L = np.tril(A, -1)
    D = np.diag(np.diag(A))
    U = np.triu(A, 1)
    S = np.dot(-np.linalg.inv(D + L), U)
    f = np.dot(np.linalg.inv(D + L), b)
    x = init
    for i in xrange(iter_time):
        error = x
        x = np.dot(S, x) + f
        error = max(abs(error - x))
        print 'iter%d: x = ' % i, x.reshape(x.shape[0])
        print 'error = ', error

"""A = np.array([5.0, -1, -1, 3, 6, 2, 1, -1, 2]).reshape((3,3))
b = np.array([16, 11, -2]).reshape((3,1))

gauss_iter(A, b, np.array([1.0,1,-1]).reshape((3,1)), 12)"""

# get matrix dim
str_in = input('please put rows of A: ')
n = int(str_in)

# get matrix A
matA = []
for line in xrange(n):
    str_in = raw_input('please put matrx A line by line: ')
    temp = [float(num) for num in str_in.split()]
    if len(temp) != n:
        print 'error: number lengthnot equal to %d. Retry' % line
    matA.append(temp)

# get matrix B
matB = []
for line in xrange(n):
    str_in = raw_input('please put matrx b line by line: ')
    temp = [float(num) for num in str_in.split()]
    if len(temp) != 1:
        print 'error: number length not equal to 1. Retry'
    matB.append(temp)

# change to nparray
A = np.array(matA)
b = np.array(matB)
init = np.array([0. for _ in xrange(n)]).reshape((n, 1))
step = 10

# cal
gauss_iter(A, b, init, step)