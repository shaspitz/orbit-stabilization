'''
@author: Shawn Marshall-Spitzbart

UC Berkeley ME235 Final Project
'''

import serial as ser


def setup():
    # Simulation setup here

    # Added some comments below about things we should think about

	'''
	"In space vehicles, one can find multiple
	sources of disturbances, such as position or velocity measuring errors,
	thruster misalignments, or even atmospheric drag"

	source: https://www.sciencedirect.com/science/article/abs/pii/S0967066111001985

	These things will be our process uncertainty, v(k). If we care enough to research
	how much uncertainity this will correspond to numerically, we can do that. Otherwise
	we can mess with the numerics.
	'''

	'''
	How would we make a space rendevous a 2D problem? its about launch timing, see: https://www.youtube.com/watch?v=oNXPtZDS-cg
	'''

	'''
	Problem could be sattellite rendevous instead of just traj stabilization? Could formulate problem as regulating the chaser
	sattellites orbit to be the same as the target sattellite. Then would use "V-bar approach" to increase radial velocity along
	 the target orbit until proximity is reached.
	'''
    pass


def main():
    # Main code and simulation here
    pass


# any other functions defined here
def other():
    pass


if __name__ == '__main__':
    setup()
    main()
