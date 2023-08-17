import numpy as np
import matplotlib.pyplot as plt

def differentiator(tau, deltat):
    y1 = 3*(tau)**2 + 5*(tau) + 7
    y2 = 3*(tau+deltat)**2 + 5*(tau+deltat) + 7

    deriv = (y2-y1)/(deltat)
    return deriv

if __name__ == "__main__":
    print('Hello World')
    solution = differentiator(2, 0.5)
    print(solution)
    