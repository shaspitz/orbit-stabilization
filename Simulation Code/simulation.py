'''
@author: Shawn Marshall-Spitzbart, Muireann Spain, Anthony Yan

UC Berkeley ME235 Final Project

Dynamics system model from ETH Zurich:
https://ethz.ch/content/dam/ethz/special-interest/mavt/dynamic-systems-n-control/idsc-dam/Lectures/System-Modeling/Slides_HS17/Lecture12.pdf
'''

import matplotlib.pyplot as plt
import numpy as np
import schedule
import threading
import serial
import scipy
from scipy.integrate import solve_ivp


'''
Define the following quantities:
r: dist. Earth center to satellite [m]
phi: orbit angle of the satellite [rad]
F_rad: radial force [N]
F_tan: tangential force [N]

States:
x1(t) = r
x2(t) = d(r)/dt
x3(t) = phi
x4(t) = d(phi)/dt

Inputs:
u1(t) = F_rad/m,
u2(t) = F_tan/m
'''


class sim_env:
    '''
    Simulation environment class
    '''
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

    '''
    In space vehicles, one can find multiple sources of process disturbances,
    such as thruster misalignments, or even atmospheric drag.
    These will be represented by system's our process uncertainty, v(k).
    '''
    # Process noise covariance matrix
    V = np.array([[10e9, 0, 0, 0],
                  [0, 1, 0, 0],
                  [0, 0, 1e-12, 0],
                  [0, 0, 0, 1e-12]])

    def __init__(self, hardware_in_loop, x0, Ts):
        '''
        Constructor for instance variables
        '''
        self.t_instance = 0
        self.x0 = x0
        self.x0_step = x0
        self.Ts = Ts
        self.u = np.zeros((2, 1))  # Change later when LQG implemented

        # A and B matricies for continuous system, dx/dt = Ax + Bu + v(k)
        self.A_continuous = np.array([[0, 1, 0, 0],
                                      [3*sim_env.w0**2,
                                       0, 0, 2*sim_env.r0*sim_env.w0],
                                      [0, 0, 0, 1],
                                      [0, -2*sim_env.w0/sim_env.r0, 0, 0]])

        self.B_continuous = np.array([[0, 0],
                                      [1, 0],
                                      [0, 0],
                                      [0, 1/sim_env.r0]])

        # A and B matricies for discrete system, x(k+1) = Ax(k) + Bu(k) + v(k)
        # Note: discretized by hand using forward Euler method
        self.A_discrete = np.array([[1, Ts, 0, 0],
                                    [3*Ts*sim_env.w0**2,
                                     1, 0, 2*Ts*sim_env.r0*sim_env.w0],
                                    [0, 0, 1, Ts],
                                    [0, -2*Ts*sim_env.w0/sim_env.r0, 0, 1]])

        self.B_discrete = np.array([[0, 0],
                                    [1+Ts, 0],
                                    [0, 0],
                                    [0, (1+Ts)/sim_env.r0]])

        # Run-type
        self.hardware_in_loop = hardware_in_loop

        if self.hardware_in_loop:
            # Serial config
            self.ser = serial.Serial(port='COM5', baudrate=115200, parity='N')
            if self.ser.is_open:
                self.ser.close()
                self.ser.open()
            else:
                self.ser.open()

            self.first_sim_step = True

    def nl_dyn_cont(self, t, x, u=np.zeros(2)):
        '''
        Continuous nonlinear dynamics of satellite system (uses 1-d arrays).
        Note: ODE took too long to solve, nl dynamics are no longer used.
        '''
        x_out = np.array([x[1],
                          x[0]*x[3]**2-sim_env.G*sim_env.M*x[
                              0]**2+u[0]/sim_env.m,
                          x[3],
                          ((-2*x[1]*x[3])/x[0])+u[1]/(sim_env.m*x[0])])

        return x_out

    def lin_dyn_cont(self, t, x, u=np.zeros((2, 1))):
        '''
        Continuous linear dynamics of satellite system.
        Assumes ZOH of inputs. Note that noise is not added here,
        (see step_sim_cont)
        '''
        # ODE solver uses 1-d arrays, convert to 2-d arrays for lin alg
        x = np.array([[x[i]] for i in range(len(x))])

        # output 1-d array again
        return (self.A_continuous @ x + self.B_continuous @ u).ravel()

    def lin_dyn_discrete(self, x, Ts, u=np.zeros((2, 1))):
        '''
        Discrete dynamics using forward Euler method
        (with additive process noise)
        '''
        # ODE solver uses 1-d arrays, convert to 2-d arrays for lin alg
        x = np.array([[x[i]] for i in range(len(x))])

        # Process noise
        v = np.array([[np.random.normal(0, np.sqrt(sim_env.V[0][0]))],
                      [np.random.normal(0, np.sqrt(sim_env.V[1][1]))],
                      [np.random.normal(0, np.sqrt(sim_env.V[2][2]))],
                      [np.random.normal(0, np.sqrt(sim_env.V[3][3]))]])

        return (self.A_discrete @ x + self.B_discrete @ u + v).ravel()

    def step_sim_cont(self):
        '''
        Simulate system forward 'Ts' seconds using continuous dynamics,
        additive ZOH noise, and discrete inputs.
        Instance variable Ts is simulation length and ZOH process noise length
        '''
        # Base case: skip first sim step for hardware in loop
        if self.hardware_in_loop and self.first_sim_step:
            self.first_sim_step = False
            return 0

        # Simulate forward 'Ts' seconds (one step)
        t_sim = np.linspace(0, self.Ts, 2)

        # Evaluate solution for each timestep (only use 2nd solution)
        step_sol = solve_ivp(self.lin_dyn_cont,
                             [t_sim[0], t_sim[-1:]],
                             self.x0_step, method='RK45',
                             t_eval=t_sim, args=(self.u, ))

        # Add process noise to step_sol
        v = np.array([np.random.normal(0, np.sqrt(sim_env.V[0][0])),
                      np.random.normal(0, np.sqrt(sim_env.V[1][1])),
                      np.random.normal(0, np.sqrt(sim_env.V[2][2])),
                      np.random.normal(0, np.sqrt(sim_env.V[3][3]))])
        step_sol.y[:, -1] += v

        # reset IC for next step (no equilibrium added)
        self.x0_step = [sol[-1] for sol in step_sol.y]

        # propagate instance time forward from step simulated time
        self.t_instance += t_sim[-1]

        # add equilibrium back to solution (only second time step)
        for i in range(len(step_sol.y)):
            step_sol.y[i][-1] = step_sol.y[i][-1] + self.equil(
                self.t_instance)[i]

        if self.hardware_in_loop:
            # Real time visualization (eventually tkinter GUI)
            print('Simulation and input: ', [sol[-1] for sol in step_sol.y],
                  self.u, 'simulation time: ', self.t_instance)
        else:
            return step_sol.y[:, -1]

    def full_sim_cont(self, t_sim):
        '''
        Simulate continuous linearized system (ZOH noise)
        '''
        sys_sol_lin = np.zeros((len(self.x0), len(t_sim)))
        for k in range(len(t_sim)):
            sys_sol_lin[:, k] = self.step_sim_cont()

        return sys_sol_lin

    def full_sim_discrete(self, t_sim):
        '''
        Simulate discrete linearized system (ZOH noise)
        '''
        sys_sol_discrete = np.zeros((len(self.x0), len(t_sim)+1))
        sys_sol_discrete[:, 0] = self.x0
        for k in range(len(t_sim)):
            sys_sol_discrete[:, k+1] = self.lin_dyn_discrete(
                sys_sol_discrete[:, k], self.Ts)

        # Add equilibrium values
        for k in range(len(sys_sol_discrete[0])):
            sys_sol_discrete[:, k] = sys_sol_discrete[
                :, k] + self.equil(k*self.Ts)

        return sys_sol_discrete

    def equil(self, t):
        '''
        For adding equilibrium trajectory back to solution
        '''
        return np.array([sim_env.r0, 0, sim_env.w0*t, sim_env.w0])

    def equil_orbit(self, N):
        '''
        Generate single equilibrium orbit
        '''
        equil_orbit = np.zeros((len(self.x0), N))
        for k, t in enumerate(np.linspace(0, sim_env.t_orbital, N)):
            equil_orbit[:, k] = self.equil(t)

        return equil_orbit

    def input_command(self):
        '''
        Writes input command to PSOC and obtains corresponding control input
        '''

        # Write input command to PSOC
        self.ser.write(str.encode('u'))

        # Get input integers from PSOC
        s = self.ser.readline().decode()
        s_processed = np.array([[int(x.strip())] for x in s.split(',')])
        self.PSOC_time, self.u = s_processed[0][0], s_processed[1:3]
        print('PSOC time: ', self.PSOC_time, '\n', 'input: ', self.u)

    def start_command(self):
        '''
        Send start message to PSOC
        '''
        self.ser.write(str.encode('s'))

    @staticmethod
    def convert_cartesian(sys_sol):
        '''
        Converts from polar coordinates describing state to
        2D cartesian coordinates
        '''
        x_sol = [sys_sol[0][i]*np.cos(
            sys_sol[2][i]) for i in range(len(sys_sol[0]))]
        y_sol = [sys_sol[0][i]*np.sin(
            sys_sol[2][i]) for i in range(len(sys_sol[0]))]

        return x_sol, y_sol

    @staticmethod
    def run_threaded(job_func):
        '''
        Automatically makes daemon thread for any commanded task
        '''
        job_thread = threading.Thread(target=job_func)
        job_thread.daemon = True
        job_thread.start()


def main():

    hardware_in_loop = False

    # Initial conditions (deviation from equilibrium in polar coordinates)
    x0 = np.array([0, 0, 0, 0])

    if hardware_in_loop:
        # Simulation sample time, not 'real' sampling time
        Ts = 2

        # Simulation environment instantiation
        sim_env_instance = sim_env(hardware_in_loop, x0, Ts)

        sim_env_instance.start_command()
        '''
        Schedule periodic execution of input command tasks.
        Note that Python does not run in real time, so additional .002518
        seconds of schedule time was heuristically implemented to
        counteract Windows' latency in sending input commands to PSOC.
        Allow for +-10 ms in communication timing error.
        '''
        schedule.every(1.002518).seconds.do(sim_env_instance.run_threaded,
                                            sim_env_instance.input_command)

        # schedule periodic sim of system (lower freq than input commands)
        schedule.every(2).seconds.do(sim_env_instance.run_threaded,
                                     sim_env_instance.step_sim_cont)

        '''
        ^^^ the above involves real-time considerations because we have to
        receive the commands from the PSOC which updates our simulation
        environment instance variable 'u' before the appropriate step_sim is
        executed
        '''

        print('Entering loop')
        while True:
            schedule.run_pending()
            # Implement ping-pong Queue object here to handle inputs?

    else:
        # Analysis, no serial interface
        t_end = 10e4  # [sec]
        sim_steps = 100
        t_sim = np.linspace(0, t_end, sim_steps)
        Ts = t_sim[-1] / len(t_sim)

        # Simulation environment instantiation
        sim_env_instance = sim_env(hardware_in_loop, x0, Ts)

        # Full linear and discrete simulations
        sys_sol_cont = sim_env_instance.full_sim_cont(t_sim)
        sys_sol_discrete = sim_env_instance.full_sim_discrete(t_sim)

        # Convert to 2D cartesian coordinates centered at earth's core
        x_sat_cont, y_sat_cont = sim_env_instance.convert_cartesian(
            sys_sol_cont)
        x_sat_discrete, y_sat_discrete = sim_env_instance.convert_cartesian(
            sys_sol_discrete)

        # Generate equilibrium orbit for visualization
        equil_orbit = sim_env_instance.equil_orbit(100)
        x_equil, y_equil = sim_env_instance.convert_cartesian(equil_orbit)

        #  Plotting
        fig, ax = plt.subplots()
        circle1 = plt.Circle((0, 0), sim_env_instance.R, color='b')
        ax.add_artist(circle1)
        ax.plot(x_sat_cont, y_sat_cont, linewidth=4, color='r', linestyle='-')
        ax.plot(x_sat_discrete, y_sat_discrete, linewidth=4, color='g',
                linestyle='--')
        ax.plot(x_equil, y_equil, linewidth=2, color='m', linestyle='--')
        plt.xlabel('x')
        plt.ylabel('y')
        plt.title(r'Satellite Path (No Input With ZOH Noise)')
        plt.gca().set_aspect('equal', adjustable='box')
        plt.legend(['Continuous Linear Model', 'Discrete Linear Model',
                    'Equilibrium Orbit'], loc='lower right')
        plt.show()


if __name__ == '__main__':
    main()

