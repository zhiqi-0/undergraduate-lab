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
        error = max(abs(delta_w))
        print 'iter %d: x = %f, y = %f, error = %f' %(iter, w[0], w[1], error)
        iter += 1
        if(iter > 100):
            print 'Oops'
            return

def f(x, y):
    return x ** 2 + y ** 2 - 1

def g(x, y):
    return x ** 3 - y

newton_multi_solve(f, g, 0.8, 0.6, 1e-5)