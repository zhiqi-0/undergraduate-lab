import numpy as np

def complex_simpson(ytable, h):
    sum1 = 0
    sum2 = 0
    for i in range(1, len(ytable) - 1):
        if i % 2 == 1:
            sum1 += ytable[i]
        else:
            sum2 += ytable[i]
    sum1 = sum1 * 4
    sum2 = sum2 * 2
    return h / 3 * (ytable[0] + ytable[len(ytable) - 1] + sum1 + sum2)

def trapezoid(ytable, h):
    sum1 = sum(ytable) - 0.5 * ytable[0] - 0.5 * ytable[len(ytable) - 1]
    return h * sum1


xtable = [0.6, 0.8, 1.0, 1.2, 1.4, 1.6, 1.8]
ytable = [5.7, 4.6, 3.5, 3.7, 4.9, 5.2, 5.5]
# print trapezoid(ytable, 0.2)
print complex_simpson(ytable, 0.2)
