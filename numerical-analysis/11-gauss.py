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

def det(A):
    gauss(A)
    row = len(A)
    res = 1.
    for i in xrange(row):
        res = res * A[i][i]
    return res

def det_check(A):
    return np.linalg.det(A)


# get matrix
str_in = input('please put dim: ')
n = int(str_in)
mat = []
for line in xrange(n):
    str_in = raw_input('please put matrix line: ')
    temp = [float(num) for num in str_in.split()]
    if len(temp) != n:
        print 'error: number not equal to %d. Retry' % line
    mat.append(temp)

# set up np array
A = np.array(mat)

# check det
check_det = det_check(A)
print 'check det:', check_det

# cal det
cal_det = det(A)
print 'cal det:', cal_det

# print gauss result
print A