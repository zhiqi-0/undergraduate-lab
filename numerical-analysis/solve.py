import numpy as np

def diff_quotient(f, x0, x1):
    return (f(x1) - f(x0)) / (x1 - x0)

def derivative(f, x0):
    h = 1e-4
    return (f(x0 + h) - f(x0 - h)) / (2 * h)

def x_partial_derivative(f, x, y0):
    h = 1e-4
    return (f(x + h, y0) - f(x - h, y0)) / (2 * h)

def y_partial_derivative(f, x0, y):
    h = 1e-4
    return (f(x0, y + h) - f(x0, y - h)) / (2 * h)

def newton_solve(f, x0, iter):
    x = x0
    for i in xrange(iter):
        x = x - f(x) / derivative(f, x)
        print 'iter %d: x = %f' % (i, x)

def newton_multi_solve(f, g, x0, y0, e):
    w = np.array([x0, y0]).reshape(2, 1)
    iter = 0
    error = 1
    while error > e:
        J = np.array([x_partial_derivative(f, w[0], w[1]), y_partial_derivative(f, w[0], w[1]),\
                 x_partial_derivative(g, w[0], w[1]), y_partial_derivative(g, w[0], w[1])]).\
                 reshape(2,2)
        b = np.array([-f(w[0], w[1]), -g(w[0],w[1])]).reshape(2, 1)
        delta_w = np.linalg.inv(J).dot(b)
        w += delta_w
        error = np.sqrt(sum(delta_w * delta_w))
        print 'iter %d: x = %f, y = %f, error = %f' %(iter, w[0], w[1], error)
        iter += 1
        if(iter > 100):
            print 'Oops'
            return


def chord(f, x0, x1, e):
    iter = 0
    while abs(x1 - x0) > e:
        x0, x1 = x1, x1 - f(x1) / diff_quotient(f, x0, x1)
        print 'iter %d: x_%d = %f' % (iter, iter + 2, x1)
        iter += 1

def f5(x):
    return x ** 5 - 9

def f7(x):
    return x ** 3 - x ** 2 - 2

def f8(x, y):
    return x ** 2 + y ** 2 - 1

def g8(x, y):
    return x ** 3 - y

newton_solve(f5, 2, 10)
chord(f7, 1, 3, 1e-3)
newton_multi_solve(f8, g8, 0.8, 0.6, 1e-3)