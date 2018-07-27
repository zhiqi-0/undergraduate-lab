import numpy as np

def runge1(f, start, end, h, y_start):
    yn = y_start
    x = start
    for step in xrange(int((end - start) / h)):
        k1 = f(x, yn)
        k2 = f(x + 0.5 * h, yn + 0.5 * h * k1)
        k3 = f(x + 0.5 * h, yn + 0.5 * h * k2)
        k4 = f(x + h, yn + h * k3)
        yn = yn + (k1 + 2 * k2 + 2 * k3 + k4) * h / 6
        print 'step %d: k1:%f k2:%f k3:%f k4:%f yn:%f' % \
              (step + 1, k1, k2, k3, k4, yn)
        x += h

def f(x, y):
    return x / y

runge1(f, 2.0, 2.6, 0.2, 1)