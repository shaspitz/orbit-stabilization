'''
@author: Shawn Marshall-Spitzbart, Muireann Spain, Anthony Yan

UC Berkeley ME235 Final Project

Dynamics system model from ETH Zurich:
https://ethz.ch/content/dam/ethz/special-interest/mavt/dynamic-systems-n-control/idsc-dam/Lectures/System-Modeling/Slides_HS17/Lecture12.pdf

Presentation slide:
https://docs.google.com/presentation/d/1Rhr5aofIPFaC-z4hrk5cZNBMRoIGt4HtfMeYdc_Dp0o/edit#slide=id.g546b429d19_3_0
'''

import matplotlib.pyplot as plt
import numpy as np
import schedule
import threading
import time
import serial
import struct
from scipy.integrate import solve_ivp
from scipy.linalg import solve_discrete_are
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg
from matplotlib.offsetbox import TextArea, DrawingArea, OffsetImage, AnnotationBbox
import matplotlib.image as mpimg
import tkinter as tk
from tkinter import Tk, Label, Button, filedialog
from tkinter import *
import tkinter.messagebox


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


class psoc_interface:
    '''
    Class for communicating with psoc micrcontroller
    '''
    def __init__(self, ser):
        self.ser = ser

    def relay_double(self, double):
        '''
        Sends and receives a double to and from psoc
        (for testing)
        '''
        command = 1
        buffer = struct.pack('d', double)
        packet_size = len(buffer) + 2

        # Transmit byte array
        transmit_packet = bytes([packet_size])
        transmit_packet += bytes([command])
        transmit_packet += buffer
        self.ser.write(transmit_packet)

        # Receive byte array
        packet_size = int.from_bytes(self.ser.read(), byteorder='little')
        command = int.from_bytes(self.ser.read(), byteorder='little')
        if command == 1 and packet_size == 10:
            buffer = self.ser.read(packet_size-2)
            double = struct.unpack('d', buffer)[0]

            return double
        else:
            print('Error!')

    def send_sim_env_info(self, Kinf, Finf, Ts=None):
        '''
        Initializes psoc interface with parameters for
        simulation, estimation and control
        Ts   -> scalar
        Kinf -> 4x4 array
        Finf -> 2x4 array
        '''
        # Construct packet containing Kinf
        command = 2

        buffer = bytes()
        for row in range(len(Kinf)):
            for col in range(len(Kinf[0])):
                buffer += struct.pack('d', Kinf[row][col])

        packet_size = len(buffer)+2

        # Transmit packet for Kinf
        transmit_packet = bytes([packet_size])
        transmit_packet += bytes([command])
        transmit_packet += buffer
        self.ser.write(transmit_packet)

        # Receive relayed byte array and confirm Kinf was receieved
        packet_size_return = int.from_bytes(self.ser.read(), byteorder='little')
        command_return = int.from_bytes(self.ser.read(), byteorder='little')

        if packet_size_return == 2 and command_return == command:
            print('Kinf received')

        # Construct packet containing Ts and Finf
        command = 3

        if Ts is None:
            Ts = 1

        buffer = bytes([int(Ts)])
        for row in range(len(Finf)):
            for col in range(len(Finf[0])):
                buffer += struct.pack('d', Finf[row][col])

        packet_size = len(buffer)+2

        # Transmit packet for Ts and Finf
        transmit_packet = bytes([packet_size])
        transmit_packet += bytes([command])
        transmit_packet += buffer
        self.ser.write(transmit_packet)

        # Receive relayed byte array and confirm Ts and Finf were receieved
        packet_size_return = int.from_bytes(self.ser.read(), byteorder='little')
        command_return = int.from_bytes(self.ser.read(), byteorder='little')

        if packet_size_return == 2 and command_return == command:
            print('Ts and Finf received')

    def start_psoc(self):
        '''
        Constructs and sends packet containing command to start psoc timer
        and activate flag enabling all other commands
        '''
        command = 4
        packet_size = 2

        # Transmit byte array
        transmit_packet = bytes([packet_size])
        transmit_packet += bytes([command])
        self.ser.write(transmit_packet)

        # Receive relayed byte array and confirm psoc started
        packet_size_return = int.from_bytes(self.ser.read(), byteorder='little')
        command_return = int.from_bytes(self.ser.read(), byteorder='little')

        if packet_size_return == packet_size and command_return == command:
            print('psoc timing started')

        elif packet_size_return == packet_size and command_return == 44:
            print('psoc timing already started, possible error')

    def request_input(self):
        '''
        Receives two double precision floats from PSOC
        (for getting inputs)
        '''
        command = 5
        packet_size = 2

        # Transmit byte array with command
        transmit_packet = bytes([packet_size])
        transmit_packet += bytes([command])
        self.ser.write(transmit_packet)

        # Receive byte array with inputs
        packet_size_return = int.from_bytes(self.ser.read(),
                                            byteorder='little')
        command_return = int.from_bytes(self.ser.read(), byteorder='little')

        if packet_size_return == packet_size+20 and command_return == command:
            buffer = self.ser.read(packet_size_return-2)
            input_1 = struct.unpack('d', buffer[:8])[0]
            input_2 = struct.unpack('d', buffer[8:16])[0]
            psoc_time = struct.unpack('I', buffer[16:20])[0]

            return input_1, input_2, psoc_time
        else:
            print('Error! Printing incorrect command or packet size.')
            print('Command:', command_return, 'Packet size:',
                  packet_size_return)

    def send_measurement(self, meas):
        '''
        Sends current measurement of the satellite state to psoc
        Note that input is a 1d numpy array
        '''
        command = 6

        buffer = bytes()
        for state in range(len(meas)):
            buffer += struct.pack('d', meas[state])

        packet_size = len(buffer)+2

        # Transmit packet with measurement
        transmit_packet = bytes([packet_size])
        transmit_packet += bytes([command])
        transmit_packet += buffer
        self.ser.write(transmit_packet)

        # Receive byte array confirming measurement was obtained
        packet_size_return = int.from_bytes(self.ser.read(), byteorder='little')
        command_return = int.from_bytes(self.ser.read(), byteorder='little')

        if packet_size_return == 2 and command_return == command:
            print('Measurement processed by psoc')
        else:
            print('Error! Printing incorrect command or packet size.')
            print('Command:', command_return, 'Packet size:',
                  packet_size_return)


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
    Noise is assumed unbiased and Gaussian. Below the system's process noise
    covariance matrix is defined.
    '''
    V = np.array([[5e9/2, 0, 0, 0],
                  [0, 10e-3, 0, 0],
                  [0, 0, 10e-10, 0],
                  [0, 0, 0, 10e-20]])

    '''
    Measurement noise covariance matrix is define below. The measurement
    assumes unbiased and Gaussian noise. Assumed that
    we receive a measurement for every state.
    '''
    W = np.array([[10e7, 0, 0, 0],
                  [0, 10, 0, 0],
                  [0, 0, 10e-5, 0],
                  [0, 0, 0, 10e-10]])

    # Uncomment for more realistic noise
#     W = np.array([[10e2, 0, 0, 0],
#                   [0, 10e-8, 0, 0],
#                   [0, 0, 10e-18, 0],
#                   [0, 0, 0, 10e-25]])

    H = np.array([[1, 0, 0, 0],
                  [0, 1, 0, 0],
                  [0, 0, 1, 0],
                  [0, 0, 0, 1]])

    def __init__(self, psoc, hardware_in_loop, lqg_active, x0, Ts):
        '''
        Constructor for instance variables
        '''
        self.psoc = psoc
        if psoc is not None:
            self.ser = psoc.ser
        self.t_instance = 0
        self.x0 = x0
        self.x_step = x0
        self.x_step_no_input = x0
        self.gui_state = x0 + self.equil(self.t_instance)
        self.gui_state_no_input = x0 + self.equil(self.t_instance)
        self.Ts = Ts
        self.u = np.zeros((2, 1))

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

        # Run-types
        self.lqg_active = lqg_active

        if self.lqg_active:

            # Implement steady-state LQG (KF and LQR)

            # Initialize x_est with 2D array of x0
            self.x_est = np.array([[self.x0[i]] for i in range(len(self.x0))])
            self.R_m = np.eye(2)
            self.Q_m = 2*np.array([[1, 0, 0, 0],
                                   [0, 1, 0, 0],
                                   [0, 0, 1, 0],
                                   [0, 0, 0, 1]])
            self.Pinf = solve_discrete_are(
                self.A_discrete.T, self.H.T, sim_env.V, sim_env.W)
            self.Kinf = self.Pinf @ (self.H.T) @ (np.linalg.inv(
                self.H @self.Pinf @self.H.T + sim_env.W))
            self.Uinf = solve_discrete_are(
                self.A_discrete, self.B_discrete, self.Q_m, self.R_m)
            self.Finf = np.linalg.inv(
                self.R + self.B_discrete.T @ self.Uinf @ self.B_discrete
                ) @ self.B_discrete.T @ self.Uinf @ self.A_discrete

        self.hardware_in_loop = hardware_in_loop

        if self.hardware_in_loop:

            # Variable for checking if PSOC misses input timing
            self.last_input = None

            # Send system matricies to psoc for input computation
            psoc.send_sim_env_info(self.Kinf, self.Finf, None)

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

        # output 1-d array with ravel method
        if self.lqg_active and not self.hardware_in_loop:
            xdot = (self.A_continuous @ x + self.B_continuous
                    @ (-self.Finf @ x)).ravel()
        else:
            xdot = (self.A_continuous @ x + self.B_continuous @ u).ravel()

        return xdot

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

        if self.lqg_active:
            # Obtain measurement
            zk = self.gen_measurement()

            # Kalman filter estimate
            self.x_est = (self.A_discrete @ self.x_est -
                          self.B_discrete @ self.Finf @ self.x_est + self.Kinf @ zk)

            # Uncomment this if you want LQR only (perfect state knowledge)
            # self.x_est = x

            # Estimate error
#             print('Estimate Error, e(k): ', x - self.x_est)

            # Apply linear feedback LQR policy accordingly
            x_next = (self.A_discrete @ x - self.B_discrete @
                      self.Finf @ self.x_est + v).ravel()
        else:
            x_next = (self.A_discrete @ x + self.B_discrete @ u + v).ravel()

        # Update x_step for measurement
        self.x_step = x_next

        return x_next

    def gen_measurement(self):
        '''
        Generates full state measurement
        '''
        wk = np.array([[np.random.normal(0, np.sqrt(sim_env.W[0][0]))],
                      [np.random.normal(0, np.sqrt(sim_env.W[1][1]))],
                      [np.random.normal(0, np.sqrt(sim_env.W[2][2]))],
                      [np.random.normal(0, np.sqrt(sim_env.W[3][3]))]])

        # Convert to 2-d array for lin alg
        xk = np.array([[self.x_step[i]] for i in range(len(self.x_step))])

        # Add generated measurement noise onto true state
        zk = self.H @ xk + wk

        return zk

    def step_sim_cont(self):
        '''
        Simulate system forward 'Ts' seconds using continuous dynamics,
        additive ZOH noise, and discrete inputs.
        Instance variable Ts is simulation length and ZOH process noise length
        '''

        if self.hardware_in_loop:
            # Immediately check if we received a new input from PSOC
            if (self.u == self.last_input).all():
                print('Missed Timing or no new input')

        # Simulate forward 'Ts' seconds (one step)
        t_sim = np.linspace(0, self.Ts, 2)

        # Evaluate solution for each time step (only use 2nd solution)
        step_sol = solve_ivp(self.lin_dyn_cont,
                             [t_sim[0], t_sim[-1:]],
                             self.x_step, method='RK45',
                             t_eval=t_sim, args=(self.u, ))

        # Evaluate same solution with no input
        step_sol_no_input = solve_ivp(self.lin_dyn_cont,
                                      [t_sim[0], t_sim[-1:]],
                                      self.x_step_no_input, method='RK45',
                                      t_eval=t_sim, args=(np.zeros((2, 1)), ))

        # Add process noise to step_sol
        v = np.array([np.random.normal(0, np.sqrt(sim_env.V[0][0])),
                      np.random.normal(0, np.sqrt(sim_env.V[1][1])),
                      np.random.normal(0, np.sqrt(sim_env.V[2][2])),
                      np.random.normal(0, np.sqrt(sim_env.V[3][3]))])
        step_sol.y[:, -1] += v
        step_sol_no_input.y[:, -1] += v

        # reset IC for next step (no equilibrium added)
        self.x_step = np.array([sol[-1] for sol in step_sol.y])
        self.x_step_no_input = np.array([sol[-1]
                                         for sol in step_sol_no_input.y])

        # propagate instance time forward from step simulated time
        self.t_instance += t_sim[-1]

        # add equilibrium back to both solutions (only second time step)
        for i in range(len(step_sol.y)):
            step_sol.y[i][-1] = step_sol.y[i][-1] + self.equil(
                self.t_instance)[i]
        for i in range(len(step_sol_no_input.y)):
            step_sol_no_input.y[i][-1] = step_sol_no_input.y[i][-1] + self.equil(
                self.t_instance)[i]

        # Update last input
        self.last_input = self.u

        if self.hardware_in_loop:
            # Store state for GUI
            self.gui_state = step_sol.y[:, -1]
            self.gui_state_no_input = step_sol_no_input.y[:, -1]
            print('input: ', self.gui_state)
            print('no input: ', self.gui_state_no_input)
        else:
            return step_sol.y[:, -1]

    def full_sim_cont(self, t_sim):
        '''
        Simulate continuous linearized system (ZOH noise)
        '''
        self.x_step = self.x0

        sys_sol_lin = np.zeros((len(self.x0), len(t_sim)))
        for k in range(len(t_sim)):
            sys_sol_lin[:, k] = self.step_sim_cont()

        return sys_sol_lin

    def full_sim_discrete(self, t_sim):
        '''
        Simulate discrete linearized system (ZOH noise)
        '''
        self.x_step = self.x0

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

    def equil_orbit(self, N, t_end=None):
        '''
        Generate single equilibrium orbit
        '''
        equil_orbit = np.zeros((len(self.x0), N))
        if t_end is None:
            for k, t in enumerate(np.linspace(0, sim_env.t_orbital, N)):
                equil_orbit[:, k] = self.equil(t)
        else:
            for k, t in enumerate(np.linspace(0, t_end, N)):
                equil_orbit[:, k] = self.equil(t)

        return equil_orbit

    def scheduler_function(self):
        '''
        Command scheduler function that gets called
        at start of every 'real' time step
        '''
        # Simulate system forward at start of every second
        self.step_sim_cont()

        # Sleep for 0.8 seconds so simulation can finish
        time.sleep(0.8)

        # Send simulated measurement to PSOC for LQG computation
        self.psoc.send_measurement(self.x_step)

        # Sleep for 0.1 seconds before requesting input
        time.sleep(0.1)

        print('Input @ this timestep: ', self.u)

        '''
        Input commands applied to next time step,
        ie. x(k+1) = x(k) + u(k-1)
        input commands are sent at intervals of (0.9sec, 1.9sec, 2.9sec, etc.)
        This timing scheme assumes that u(0) = 0
        '''
        input_1, input_2, psoc_time = self.psoc.request_input()
        self.u = np.array([[input_1],
                           [input_2]])

        print('Current psoc time: ', psoc_time)

    def plot_solution(self, x_sol, y_sol, title, sol_type, t_end):
        '''
        Repeatable plotting
        '''
        # Generate equilibrium orbit for visualization
        if t_end is None:
            equil_orbit = self.equil_orbit(100)
            x_equil, y_equil = sim_env.convert_cartesian(equil_orbit)
        else:
            equil_orbit = self.equil_orbit(100, t_end)
            x_equil, y_equil = sim_env.convert_cartesian(equil_orbit)

        # Plotting
        fig, ax = plt.subplots()
        circle = plt.Circle((0, 0), sim_env.R, color='b')
        ax.add_artist(circle)
        ax.plot(x_sol, y_sol, linewidth=4, color='g', linestyle='--')
        ax.plot(x_equil, y_equil, linewidth=2, color='r', linestyle='--')
        plt.xlabel('x')
        plt.ylabel('y')
        plt.title(title)
        plt.gca().set_aspect('equal', adjustable='box')
        plt.legend([sol_type, 'Equilibrium Orbit'], loc='lower right')

    @staticmethod
    def convert_cartesian(sys_sol):
        '''
        Converts from polar coordinates describing state to
        2D cartesian coordinates.
        (For 1D arrays only)
        '''
        x_sol = sys_sol[0]*np.cos(sys_sol[2])
        y_sol = sys_sol[0]*np.sin(sys_sol[2])

        return x_sol, y_sol

    @staticmethod
    def run_threaded(job_func):
        '''
        Automatically makes daemon thread for any commanded task
        '''
        job_thread = threading.Thread(target=job_func)
        job_thread.daemon = True
        job_thread.start()


class gui:
    '''
    Graphical user interface class
    '''
    def __init__(self, master, sim_env):
        self.master = master
        self.sim_env = sim_env

        # GUI title
        self.master.wm_title("Real Time Satellite Visualization")

        # Initialize state display
        self.state_display = sim_env.x0

        self.name_label = Label(self.master, text="Incoming States",font=("Helvetica", 14))
        self.name_label.pack(side=BOTTOM)
        self.name_label.configure(background="forestgreen",fg="white", width=1000)
        spaces=str("                        ")
        self.values_label = Label(self.master,
                                  text='R'+spaces+'Rdot'+spaces+'Phi'+spaces+'Phidot',font=("Helvetica", 14))
        self.values_label.pack(side=BOTTOM)
        self.values_label.configure(background="forestgreen",fg="white", width=1000)
        self.data_label = Label(self.master, fg="white",text=str(self.state_display),font=("Helvetica", 14))
        self.data_label.pack(side=BOTTOM)
        self.data_label.configure(background="forestgreen", width=1000)

        # Init arrays for plotting
        x, y = self.sim_env.convert_cartesian(self.sim_env.gui_state)
        self.x_input = np.array([x])
        self.y_input = np.array([y])

        x, y = self.sim_env.convert_cartesian(self.sim_env.gui_state_no_input)
        self.x_no_input = np.array([x])
        self.y_no_input = np.array([y])

        # Add in label with time step
        self.timestep_label = Label(self.master,
                                    text="Time Elapsed Since Entering Orbit:",font=("Helvetica", 14))
        self.timestep_label.pack(side=TOP)
        self.time_label = Label(self.master, text=str(self.sim_env.t_instance),font=("Helvetica", 14))
        self.time_label.pack(side=TOP)

        # Equilibrium orbit
        self.eq_orbit = self.sim_env.equil_orbit(1000)
        self.x_eq, self.y_eq = self.sim_env.convert_cartesian(self.eq_orbit)

        # "STOP" button to terminate process
        button = tkinter.Button(master=self.master, text="EXIT ORBIT",fg="red",font=("Helvetica", 14),
                                command=self.master.destroy)
        button.pack(side=TOP)

        # Figure 1
        self.fig1 = plt.Figure()
        self.a = self.fig1.add_subplot(1, 1, 1)
        earth = mpimg.imread('earth.png')
        imagebox = OffsetImage(earth, zoom=0.13)
        earth_img = AnnotationBbox(imagebox,(0.3, 0.3),frameon=False)
        self.a.add_artist(earth_img)
#         circle = plt.Circle((0, 0), self.sim_env.R, color='b')
#         self.a.add_artist(circle)
        self.a.plot(self.x_eq, self.y_eq, linewidth=1, color='r',
                    linestyle='--',label='Equilibrium Orbit')
        self.a.plot(self.x_input, self.y_input, linewidth=3,
                    color='g', linestyle='--',label='Real-Time Orbit')
        self.fig1.legend(loc=1,fontsize="small")
        self.a.set_title('Satellite Path With Control Input')

        # Figure 2
        self.fig2 = plt.Figure()
        self.b = self.fig2.add_subplot(1, 1, 1)
        #circle = plt.Circle((0, 0), self.sim_env.R, color='b')
        #self.b.add_artist(circle)
        earth = mpimg.imread('earth.png')
        imagebox = OffsetImage(earth, zoom=0.13)
        earth_img = AnnotationBbox(imagebox,(0.3, 0.3),frameon=False)
        self.b.add_artist(earth_img)
        self.b.plot(self.x_eq, self.y_eq, linewidth=1, color='r',
                    linestyle='--',label='Equilibrium Orbit')
        self.b.plot(self.x_no_input, self.y_no_input, linewidth=3,
                    color='g', linestyle='--',label='Real-Time Orbit')
        self.fig2.legend(loc=1,fontsize="small")
        self.b.set_title('Satellite Path Without Control Input')

        # Init plots
        gui.canvas_a = FigureCanvasTkAgg(self.fig1, master=self.master)
        gui.canvas_a.get_tk_widget().pack(side=LEFT)
        gui.canvas_b = FigureCanvasTkAgg(self.fig2, master=self.master)
        gui.canvas_b.get_tk_widget().pack(side=RIGHT)
        gui.canvas_a.draw()
        gui.canvas_b.draw()

    def updateGraphs(self):

        # Update state display window
        self.data_label['text'] = self.sim_env.gui_state
        self.time_label['text'] = self.sim_env.t_instance

        # Convert gui state to cartesian coordinates for plotting
        x, y = self.sim_env.convert_cartesian(self.sim_env.gui_state)

        # append data to array if new solution exists
        if x != self.x_input[-1] and y != self.y_input[-1]:
            self.x_input = np.append(self.x_input, x)
            self.y_input = np.append(self.y_input, y)

        # Do same for state without input
        x, y = self.sim_env.convert_cartesian(self.sim_env.gui_state_no_input)

        # append data to array if new solution exists
        if x != self.x_no_input[-1] and y != self.y_no_input[-1]:
            self.x_no_input = np.append(self.x_no_input, x)
            self.y_no_input = np.append(self.y_no_input, y)

        # Update plots
        self.a.set_xlim(-1*(10**7), 4.5*(10**7))
        self.a.set_ylim(-1*(10**7), 4.5*(10**7))
        self.a.set_aspect('equal', adjustable='box')
        self.a.plot(self.x_input, self.y_input, linewidth=3,
                    color='g', linestyle='--',label='Real-Time Orbit')

        self.b.set_xlim(-1*(10**7), 4.5*(10**7))
        self.b.set_ylim(-1*(10**7), 4.5*(10**7))
        self.b.set_aspect('equal', adjustable='box')
        self.b.plot(self.x_no_input, self.y_no_input, linewidth=3,
                    color='g', linestyle='--')

    # Stop Button
    def _quit(self):
        '''
        Stops mainloop. This is necessary on Windows to prevent
        Fatal Python Error: PyEval_RestoreThread: NULL state
        '''
        self.master.quit()
        self.master.destroy()


def main():

    hardware_in_loop = True
    lqg_active = True

    # Initial conditions (deviation from equilibrium in polar coordinates)
    x0 = np.array([10e5, 0, 0, 0])

    if hardware_in_loop:

        # Simulation sample time, not 'real' sampling time
        Ts = 100

        # Serial configuration
        ser = serial.Serial(port='COM5', baudrate=115200, parity='N')
        if ser.is_open:
            ser.close()
            ser.open()
        else:
            ser.open()

        # Psoc interface instantiation
        psoc = psoc_interface(ser)

        # Simulation environment instantiation
        sim_env_instance = sim_env(psoc, hardware_in_loop, lqg_active, x0, Ts)

        # GUI instantiation
        root = tk.Tk()
        gui_instance = gui(root, sim_env_instance)

        '''
        Schedule periodic execution of input command tasks.
        Note that Python does not run in real time, so additional .002518
        seconds of schedule time was heuristically implemented to
        counteract Windows' latency in sending input commands to PSOC.
        Allow for +-10 ms in communication timing error.
        '''
        sec_equiv = 1.002518  # 'real' sampling time

        sim_env_instance.psoc.start_psoc()

        # schedule periodic sim/input command of system, (0sec, 1sec, 2sec, etc.)
        schedule.every(1*sec_equiv).seconds.do(sim_env_instance.run_threaded,
                                               sim_env_instance.scheduler_function)

        '''
        ^^^ the above involves real-time considerations because we have to
        receive the commands from the PSOC which updates our simulation
        environment instance variable 'u' before the appropriate step_sim is
        executed
        '''

        print('Entering main loop')
        while True:
            # Threading
            schedule.run_pending()

            # GUI
            root.update_idletasks()
            root.update()
            gui_instance.updateGraphs()
            gui.canvas_a.draw()
            gui.canvas_b.draw()

    else:
        # Analysis, no serial interface
        t_end = 5.0e4  # [sec]
        sim_steps = 1000
        t_sim = np.linspace(0, t_end, sim_steps)
        Ts = t_sim[-1] / len(t_sim)

        # Simulation environment instantiation
        sim_env_instance = sim_env(None, hardware_in_loop, lqg_active, x0, Ts)

        # Full linear and discrete simulations
        sys_sol_cont = sim_env_instance.full_sim_cont(t_sim)
        sys_sol_discrete = sim_env_instance.full_sim_discrete(t_sim)

        # Convert to 2D cartesian coordinates centered at earth's core
        x_sat_cont, y_sat_cont = sim_env_instance.convert_cartesian(
            sys_sol_cont)
        x_sat_discrete, y_sat_discrete = sim_env_instance.convert_cartesian(
            sys_sol_discrete)

        # Plotting for continuous and discrete solutions
        title = 'Satellite Path (LQG with Measurement Noise, ZOH Process Noise)'
        sol_type = 'Continuous Model'
        sim_env_instance.plot_solution(
            x_sat_cont, y_sat_cont, title, sol_type, t_end)

        sol_type = 'Discrete Model'
        sim_env_instance.plot_solution(
            x_sat_discrete, y_sat_discrete, title, sol_type, t_end)

        plt.show()


if __name__ == '__main__':
    main()

