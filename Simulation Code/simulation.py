'''
@author: Shawn Marshall-Spitzbart, Muireann Spain, Anthony Yan

UC Berkeley ME235 Final Project

Dynamics system model from ETH Zurich:
https://ethz.ch/content/dam/ethz/special-interest/mavt/dynamic-systems-n-control/idsc-dam/Lectures/System-Modeling/Slides_HS17/Lecture12.pdf
'''

import matplotlib.pyplot as plt
import numpy as np
import csv
import time
import schedule
import threading
import serial
import scipy
from scipy.integrate import solve_ivp

# Setup global variables

# Run-type
hardware_in_loop = False

# Radius of the Earth [m]
R = 6378000

# Mass of the Earth [kg]
M = 5.972*(10**24)

# Mass of satellite [kg]
m = 1500

# Universal gravitation constant G [m3/(s2kg)]
G = 6.673*(10**(-11))

# Orbit turn rate for linearization [rad/s]
w0 = 7.2910**-5

# Orbital period [s]
t_orbital = 2*np.pi/w0

# Geostationary orbit radius for linearization [m]
r0 = 4.22*10**7

# Process noise covariance matrix
V = np.array([[10e9, 0, 0, 0],
              [0, 1, 0, 0],
              [0, 0, 1e-12, 0],
              [0, 0, 0, 1e-12]])

'''
"In space vehicles, one can find multiple
sources of disturbances, such as position or velocity measuring errors,
thruster misalignments, or even atmospheric drag"

source: https://www.sciencedirect.com/science/article/abs/pii/S0967066111001985

These things will be our process uncertainty, v(k). If we care enough to
research how much uncertainity this will correspond to numerically, we can do
that. Otherwise we can mess with the numerics.
'''

'''
How would we make a space rendevous a 2D problem? its about launch timing,
see: https://www.youtube.com/watch?v=oNXPtZDS-cg
'''

'''
Problem could be sattellite rendevous instead of just traj stabilization?
Could formulate problem as regulating the chaser sattellites orbit to be the
same as the target sattellite. Then would use "V-bar approach" to increase
radial velocity along the target orbit until proximity is reached.
'''


def nl_dyn_cont(t, x, u=np.zeros(2)):
    # Continuous nonlinear dynamics of sattellite system (uses 1-d nparrays)

    '''
    Define the following quantities:
    r: dist. Earth center to satellite [m]
    phi: orbit angle of the satellite [rad]
    F_rad: radial force [N]
    F_tan: tangential force [N]
    '''
    # States:
    # x1(t) = r,
    # x2(t) = r',
    # x3(t) = phi,
    # x4(t) = phi'

    # Input:
    # u1(t) = F_rad/m,
    # u2(t) = F_tan/m

    x_out = np.array([x[1],
                      x[0]*x[3]**2-G*M*x[0]**2+u[0]/m,
                      x[3],
                      ((-2*x[1]*x[3])/x[0])+u[1]/(m*x[0])])

    # testing
    # x_out = np.zeros(4)

    '''
    # add new position to path array
    path = np.append(path, np.array([x_sat, y_sat]))
    '''
    return x_out  # , path


def lin_dyn_cont(t, x, r0, u=np.zeros((2, 1))):
    # Continuous linear dynamics of sattellite system
    # Assumes ZOH of inputs

    # ODE solver uses 1-d arrays, convert to 2-d nparrays for lin alg
    x = np.array([[x[i]] for i in range(len(x))])

    A = np.array([[0, 1, 0, 0],
                  [3*w0**2, 0, 0, 2*r0*w0],
                  [0, 0, 0, 1],
                  [0, -2*w0/r0, 0, 0]])

    B = np.array([[0, 0],
                  [1, 0],
                  [0, 0],
                  [0, 1/r0]])

#     # Process noise from global covariance matrix (assumes ZOH)
#     v = np.array([[np.random.normal(0, np.sqrt(V[0][0]))],
#                   [np.random.normal(0, np.sqrt(V[1][1]))],
#                   [np.random.normal(0, np.sqrt(V[2][2]))],
#                   [np.random.normal(0, np.sqrt(V[3][3]))]])

    # output 1-d array again (process noise added)
    return (A @ x + B @ u).ravel() #+ v).ravel()


def KalmanFilter(x0,z,N):
    #using linearized dynamics
    A = np.array([[0, 1, 0, 0],
                  [3*w0**2, 0, 0, 2*r0*w0],
                  [0, 0, 0, 1],
                  [0, -2*w0/r0, 0, 0]])
    H=np.eye(4)


    # Initialize estimate and covariance of state (at k = 0)
    XM = x0
    Pm = np.eye(4)
    V = np.eye(4)
    W = np.eye(4)

    for k in range(N):
        # prior update
        XP = A@XM
        Pp = A@Pm@A.T + V
        # measurement update
        K = Pp@H.T @ np.linalg.inv(H@Pp@H.T + W)
        XM = XP + K@(z[k] - H@XP)
        Pm = (np.eye(4)-K@H)@Pp@(np.eye(4)-K@H).T + K@W@K.T


    # Return posterior mean and variance
    return XM, Pm


def lin_dyn_discrete(x, r0, Ts, u=np.zeros((2, 1))):
    '''
    Discrete dynamics using forward Euler method (with additive process noise)
    '''
    # ODE solver uses 1-d arrays, convert to 2-d nparrays for lin alg
    x = np.array([[x[i]] for i in range(len(x))])

#     dx = lin_dyn_cont(t=None, x=x, r0=r0, u=u)
#     xnext = x + Ts*dx

    A = np.array([[1, Ts, 0, 0],
                  [3*Ts*w0**2, 1, 0, 2*Ts*r0*w0],
                  [0, 0, 1, Ts],
                  [0, -2*Ts*w0/r0, 0, 1]])

    # Process noise from global covariance matrix
    v = np.array([[np.random.normal(0, np.sqrt(V[0][0]))],
                  [np.random.normal(0, np.sqrt(V[1][1]))],
                  [np.random.normal(0, np.sqrt(V[2][2]))],
                  [np.random.normal(0, np.sqrt(V[3][3]))]])

    xnext = A @ x + v
    return xnext.ravel()


def equil(t):
    '''
    For adding equil trajectory back to solution
    '''
    return np.array([r0, 0, w0*t, w0])


def input_command():
    '''
    Writes input command to PSOC and obtains corresponding control input
    '''
    # We manipulate u
    global u

    # Write input command to PSOC
    ser.write(str.encode('u'))

    # Get input integers from PSOC
    s = ser.readline().decode()
    s_processed = np.array([[int(x.strip())] for x in s.split(',')])
    t, u = s_processed[0][0], s_processed[1:3]
    print('time: ', t, '\n', 'input: ', u)


def simulate_system(Ts):
    '''
    Simulate system using continuous dynamics and discrete inputs
    given from PSOC
    '''
    # We manipulate x0_step, and t_global
    global x0_step, t_global

    # Simulate forward 2 seconds (eventually make bigger, like 20000 sec)
    t_sim = np.linspace(0, Ts, 2)

    # Evaluate solution for each timestep (only use 2nd solution)
    step_sol = solve_ivp(lin_dyn_cont,
                         [t_sim[0], t_sim[-1:]],
                         x0_step, method='RK45',
                         t_eval=t_sim, args=(r0, u))

    # Add process noise to step_sol
    v = np.array([np.random.normal(0, np.sqrt(V[0][0])),
                  np.random.normal(0, np.sqrt(V[1][1])),
                  np.random.normal(0, np.sqrt(V[2][2])),
                  np.random.normal(0, np.sqrt(V[3][3]))])
    step_sol.y[:, -1] += v

    # reset IC for next step (no equilibrium added)
    x0_step = [sol[-1] for sol in step_sol.y]

    # propogate t_global forward from simulated time
    t_global += t_sim[-1]

    # add equilibrium back to solution (only second timestep)
    for i in range(len(step_sol.y)):
        step_sol.y[i][-1] = step_sol.y[i][-1] + equil(t_global)[i]

    if hardware_in_loop:
        # Real time visualization (eventually tkinter GUI)
        print('Simulation and input: ', [sol[-1] for sol in step_sol.y], u, t_global)

    else:
        return step_sol.y[:, -1]


def run_threaded(job_func):
    '''
    Automatically makes thread for any commanded task
    '''
    job_thread = threading.Thread(target=job_func)
    job_thread.daemon = True
    job_thread.start()


def main():

    # Manipulated global variables within main
    global x0_step, u, t_global, ser

    if hardware_in_loop:
        # Serial interfacing

        # Intialize ode solver
        t_global = 0
        x0_step = [0, 0, 0, 0]
        u = np.zeros((2, 1))
        Ts = 2

        # Serial config
        ser = serial.Serial(port='COM5', baudrate=115200, parity='N')
        if ser.is_open:
            ser.close()
            ser.open()
        else:
            ser.open()

        # Send start message
        ser.write(str.encode('s'))

        '''
        Schedule periodic execution of input command tasks.
        Note that Python does not run in real time, so additional .002518
        seconds of schedule time was hueristically implemented to
        counteract Windows' latency in sending input commands to PSOC.
        Allow for +-10 ms in communication timing error.
        '''
        schedule.every(1.002518).seconds.do(run_threaded, input_command)

        # schedule periodic sim of system (lower freq than input commands)
        schedule.every(2).seconds.do(run_threaded, simulate_system)

        print('About to enter loop')

        while True:
            schedule.run_pending()

            # Implement ping-pong Queue object here to handle inputs?

        '''
        Psuedocode:

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
        '''
    else:
        # Simulations

        # Intial conditions, deviation from equil in polar coordinates
        x0 = [0, 0, 0, 0]

        # Simulate continuous linearized system
        t_sim = np.linspace(0, 100000, 100)
        Ts = t_sim[-1] / len(t_sim)
        u = np.zeros((2, 1))

        # Intialize ode solver for continuous simulation with ZOH process noise
        t_global = 0
        x0_step = x0

        sys_sol_lin = np.zeros((4, len(t_sim)))
        for k in range(len(t_sim)):
            sys_sol_lin[:, k] = simulate_system(Ts)


#         sys_sol_lin = solve_ivp(lin_dyn_cont, [t_sim[0], t_sim[-1:]], x0,
#                                 method='RK45', t_eval=t_sim, args=(r0, u))

        # Add equilibrium values for continous system
#         for i in range(len(sys_sol_lin.y)):
#             sys_sol_lin.y[i] = np.array(
#                 [sys_sol_lin.y[i][j]
#                  + equil(t_sim[j])[i] for j in range(len(t_sim))])

        # Simulate continuous nonlinear system (yes it does run, not quickly)
        '''
        t_sim = np.linspace(0, 10, 100)
        x0 = [r0, 1, w0, 1]
        sys_sol_nl = solve_ivp(nl_dyn_cont, [t_sim[0], t_sim[-1:]], x0,
                            method='RK45', t_eval=t_sim)
        '''
        # kalman filter
#         XM,Pm=KalmanFilter(x0,[5,5,5.5,6,5.6,7,6.5,5.4,6,5.6],10)
        # solution will be sys_sol.y with [0:3] being arrays of state

        # Simulate discrete nonlinear system
        x_discrete = np.zeros((4, len(t_sim)+1))
        x_discrete[:, 0] = x0
        for k in range(len(t_sim)):
            x_discrete[:, k+1] = lin_dyn_discrete(x_discrete[:, k], r0, Ts)

        # Add equilibrium values for discrete system
        for k in range(len(x_discrete[0])):
            x_discrete[:, k] = x_discrete[:, k] + equil(k*Ts)

        # Convert to 2D cartesian coordinates centered at earth's core
        x_sat_lin = [sys_sol_lin[0][i]*np.cos(sys_sol_lin[2][i]) for i in range(len(t_sim))]
        y_sat_lin = [sys_sol_lin[0][i]*np.sin(sys_sol_lin[2][i]) for i in range(len(t_sim))]
        # x_sat_nl = [sys_sol_nl.y[0][i]*np.cos(sys_sol_nl.y[2][i]) for i in range(len(t_sim))]
        # y_sat_nl = [sys_sol_nl.y[0][i]*np.sin(sys_sol_nl.y[2][i]) for i in range(len(t_sim))]
        x_sat_lin_discrete = [x_discrete[0][k]*np.cos(x_discrete[2][k]) for k in range(len(x_discrete[0]))]
        y_sat_lin_discrete = [x_discrete[0][k]*np.sin(x_discrete[2][k]) for k in range(len(x_discrete[0]))]

        # Generate equilibrium orbit for visualization
        equil_orbit = np.zeros((4, 100))
        for k, t in enumerate(np.linspace(0, t_orbital, 100)):
            equil_orbit[:, k] = equil(t)
        x_equil = [equil_orbit[0][k]*np.cos(equil_orbit[2][k]) for k in range(len(equil_orbit[0]))]
        y_equil = [equil_orbit[0][k]*np.sin(equil_orbit[2][k]) for k in range(len(equil_orbit[0]))]

        #  Plotting
        fig, ax = plt.subplots()
        circle1 = plt.Circle((0, 0), R, color='b')
        ax.add_artist(circle1)
        ax.plot(x_sat_lin, y_sat_lin, linewidth=4, color='r', linestyle='-')
        ax.plot(x_sat_lin_discrete, y_sat_lin_discrete, linewidth=4, color='g',
                linestyle='--')
        ax.plot(x_equil, y_equil, linewidth=2, color='m', linestyle='--')
        # plt.plot(x_sat_nl, y_sat_nl, linewidth=2)
        plt.xlabel('x')
        plt.ylabel('y')
        plt.title(r'Satellite Path')
        plt.gca().set_aspect('equal', adjustable='box')
        plt.legend(['Continuos Linear Model', 'Discrete Linear Model', 'Equilibrium Orbit'],
                   loc='lower right')
        plt.show()


if __name__ == '__main__':
    main()

