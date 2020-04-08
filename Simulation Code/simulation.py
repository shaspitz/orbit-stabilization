'''
@author: Shawn Marshall-Spitzbart

UC Berkeley ME235 Final Project
'''
# importing libraries
import matplotlib
import matplotlib.pyplot as plt 
import numpy as np
import csv
import time
import serial as ser
import scipy


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

def NonLinearDynamics(x,u):
    
#     R: radius of the Earth [m]
    R=6378000
#     M: mass of the Earth [kg]
    M=5.972*(10**24)
#     m: mass of the satellite [kg]
    m=1500
#    Universal gravitation constant G [m3/(s2kg)]
    G=6.673*(10**(−11))
#     r: dist. Earth center to satellite [m]
#     phi: orbit angle of the satellite [rad]
#     Fr: radial force [N]
#     F_phi: tangential force [N]



    #Build a Nonlinear Model in state space form, such that only 1st order
    #time-derivatives appear
    #x1(t) = r, x2(t) = r', u1(t) = u_r
    #x3(t) = phi, x4(t) = phi' , u2(t) = u_phi
    f_x=np.array([[x[1]],
                  [x[0]*x[3]**2-G*M*x[0]**2+u[0]],
                  [x[3]],
                  [((-2*x[1]*x[3])/x[0])+u[1]/x[0]]])
    
    #Need r and phi to plot simulation
    #change the satellite position to Cartesian coordinates
    X_satellite=f_x[0]*np.cos(f_x[2])
    Y_satellite=f_x[0]*np.sin(f_x[2])
    
    #add new position to path array
    new_coordinates=np.array([X_satellite,Y_satellite])
    path=np.append(path, new_coordinates)
    
    return X_satellite, Y_satellite, path




def main():
    # Main code and simulation here
    X_satellite,Y_satellite,path=NonLinearDynamics(x,u)
    
    #model the satellite as a cross
    satellite = ax.plot(X_satellite, X_satellite, color='forestgreen',marker='X',markersize=3)[0]
    #model the earth as a blue sphere
    earth = ax.plot(0,0,'bo',markersize=10)
    #model the path taken
    path_history=ax.plot(path[:,0],path[:,1],'-',color='gray',linewidth=3)[0]
    
 
    #to animate the figure
    fig = plt.figure()
    ax = plt.gca()
    plt.ion()

    plt.show()
    #this is where we get the serial read??? don't know what format it comes in 
    while reading serial_data:
        
        [x,u]=received_data
        # update the satellite coordinates and the path taken data
        X_satellite,Y_satellite,path=NonLinearDynamics(x,u)
        satellite.set_data(X_satellite, Y_satellite)
        path.set_data(path[:,0], path[:,1])
        
        
        ax.relim()
        ax.autoscale_view()
        ax.axis("equal")
        fig.canvas.draw()
    
    pass


# any other functions defined here
def other():
    pass


if __name__ == '__main__':
    setup()
    main()

