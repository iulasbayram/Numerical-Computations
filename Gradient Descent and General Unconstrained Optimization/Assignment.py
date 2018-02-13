import numpy as np
import math
import sys


def main():
    if (len(sys.argv) < 4):

        print "There must be 3 argument to compile this program."
        print "First argument has to be epsilon1."
        print "Second argument has to be epsilon2."
        print "Third argument has to be iter_max."

    else:

        argv1 = sys.argv[1]
        argv2 = sys.argv[2]
        argv3 = sys.argv[3]

        print "For vector x0: \n"

        x0 = np.array([1.2, 1.2])

        epsilon1 = argv1
        epsilon2 = argv2
        iter_max = argv3

        gradientDescentOptimization(x0, epsilon1, epsilon2, iter_max)

        print "For vector x1: \n"

        x1 = np.array([-1.2, 1.0])

        epsilon1 = argv1
        epsilon2 = argv2
        iter_max = argv3

        gradientDescentOptimization(x1, epsilon1, epsilon2, iter_max)

"""This method does gradient descent optimization using datas."""
def gradientDescentOptimization(vector, epsilon1, epsilon2, iter_max):

    t = 10.0 ** -3
    x0 = vector
    x1 = x0[0]
    x2 = x0[1]
    k = 1
    control = True

    while(k < 10000 and control):

        prev_y = 100 * (x2 - x1 * x1) ** 2.0 + (1 - x1) ** 2.0

        grad_y_x1 = 400 * x1 ** 3.0 - 400 * x1 * x2 + 2 * x1 - 2
        grad_y_x2 = 200 * x2 - 200 * x1 ** 2.0

        prev_x1 = x1
        prev_x2 = x2

        x1 = x1 - t * grad_y_x1
        x2 = x2 - t * grad_y_x2

        y = 100 * (x2 - x1 * x1) ** 2.0 + (1 - x1) ** 2.0

        if(k%100 == 0):
            
            printResults(k, x1, x2, y, grad_y_x1, grad_y_x2)

        if(abs(y - prev_y) < float(epsilon1)):
            print "Epsilon 1 stopped the iteration.\n"
            print "Final results are: \n"

            printResults(k, x1, x2, y, grad_y_x1, grad_y_x2)

            control = False

        elif(math.sqrt(grad_y_x1 * grad_y_x1 + grad_y_x2 * grad_y_x2) < float(epsilon2)):
            print "Epsilon 2 stopped the iteration.\n"
            print "Final results are: \n"

            printResults(k, x1, x2, y, grad_y_x1, grad_y_x2)

            control = False

        elif(k == int(iter_max)):
            print "The iteration reached maximum step.\n"
            print "Final results are: \n"

            printResults(k, x1, x2, y, grad_y_x1, grad_y_x2)

            control = False

        k = k + 1

"""This method prints results."""
def printResults(k, x1, x2, y, grad_y_x1, grad_y_x2):
    print "For step " , k , ", \n"
    print "x1: " , x1 , ""
    print "x2: " , x2 , "\n"
    print "f(x): " , y , "\n"
    print "Gradient for x1: " , grad_y_x1 , ""
    print "Gradient for x2: " , grad_y_x2 , "\n"

main()