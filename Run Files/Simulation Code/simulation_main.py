'''
@author: Shawn Marshall-Spitzbart

UC Berkeley ME235 Final Project

Contains the main simulation function
'''

import matplotlib.pyplot as plt
import numpy as np
import schedule
import serial
import tkinter as tk

# See accompanying Python files for the following class definitions
from Psoc_interface import Psoc_interface
from Sim_env import Sim_env
from Gui import Gui

'''
Dynamics system model from ETH Zurich:
https://ethz.ch/content/dam/ethz/special-interest/mavt/dynamic-systems-n-control/idsc-dam/Lectures/System-Modeling/Slides_HS17/Lecture12.pdf

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
        psoc = Psoc_interface(ser)

        # Simulation environment instantiation
        sim_env_instance = Sim_env(psoc, hardware_in_loop, lqg_active, x0, Ts)

        # GUI instantiation
        root = tk.Tk()
        gui_instance = Gui(root, sim_env_instance)

        '''
        Schedule periodic execution of input command tasks.
        Note that Python does not run in real time, so additional .002518
        seconds of schedule time was heuristically implemented to
        counteract Windows' latency in sending input commands to PSOC.
        Allow for +-10 ms in communication timing error.
        '''
        sec_equiv = 1.002518  # 'real' sampling time

        sim_env_instance.psoc.start_psoc()

        # schedule periodic sim/input command of system, (0sec, 1sec, etc.)
        schedule.every(1*sec_equiv).seconds.do(
            sim_env_instance.run_threaded,
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
            gui_instance.canvas_a.draw()
            gui_instance.canvas_b.draw()

    else:
        # Analysis, no serial interface
        t_end = 5.0e4  # [sec]
        sim_steps = 1000
        t_sim = np.linspace(0, t_end, sim_steps)
        Ts = t_sim[-1] / len(t_sim)

        # Simulation environment instantiation
        sim_env_instance = Sim_env(None, hardware_in_loop, lqg_active, x0, Ts)

        # Full linear and discrete simulations
        sys_sol_cont = sim_env_instance.full_sim_cont(t_sim)
        sys_sol_discrete = sim_env_instance.full_sim_discrete(t_sim)

        # Convert to 2D cartesian coordinates centered at earth's core
        x_sat_cont, y_sat_cont = sim_env_instance.convert_cartesian(
            sys_sol_cont)
        x_sat_discrete, y_sat_discrete = sim_env_instance.convert_cartesian(
            sys_sol_discrete)

        # Plotting for continuous and discrete solutions
        title = 'Satellite Path (LQG with Measurement Noise,'
        ' ZOH Process Noise)'
        sol_type = 'Continuous Model'
        sim_env_instance.plot_solution(
            x_sat_cont, y_sat_cont, title, sol_type, t_end)

        sol_type = 'Discrete Model'
        sim_env_instance.plot_solution(
            x_sat_discrete, y_sat_discrete, title, sol_type, t_end)

        plt.show()


if __name__ == '__main__':
    main()

