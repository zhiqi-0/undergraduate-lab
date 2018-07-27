import numpy as np

def romberg(f, low, high, epsilon):
    h = float(high - low)
    old = [float((f(low) + f(high)) * h / 2)]
    iter_max = 15
    for k in range(1, iter_max + 1):
        new = [0.0]
        h = h / 2
        sum1 = sum([f(low + (2 * i - 1) * h) for i in range(1, int(2 ** (k - 1)) + 1)])
        new[0] = (old[0] + h * 2 * sum1) / 2
        for j in range(1, k + 1):
            new += [new[j - 1] + (new[j - 1] - old[j - 1]) / (4 ** j - 1)]
            if abs(new[j] - old[j - 1]) < epsilon:
                print 'iter: %d' % k
                print new
                return new[j]
        print 'iter: %d' % k
        print new
        old = new

def f(x):
    return x ** 7

print romberg(f, 1, 2, 1e-4)