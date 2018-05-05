import numpy as np

"""
Gauss 
input parameter: 
"""
def gauss(A):
    row = len(A)
    for i in xrange(row - 1):
        for j in range(i + 1, row):
            coe = A[j][i] / A[i][i]
            A[j] = A[j] - coe * A[i]

A = np.array([1,2,3,2,3,4,4,5,7]).reshape((3,3))
gauss(A)