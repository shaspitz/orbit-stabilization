'''
Created on May 14, 2020

@author: Muireann Spain, Shawn Marshall-Spitzbart

Contains the Gui class
'''
import matplotlib.pyplot as plt
import numpy as np
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg
from matplotlib.offsetbox import OffsetImage, AnnotationBbox
import matplotlib.image as mpimg
from tkinter import *


class Gui:
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

        self.name_label = Label(self.master, text="Incoming States",
                                font=("Helvetica", 14))
        self.name_label.pack(side=BOTTOM)
        self.name_label.configure(background="forestgreen", fg="white", width=1000)
        spaces = "                        "
        self.values_label = Label(self.master,
                                  text='R'+spaces+'Rdot'+spaces+
                                  'Phi'+spaces+'Phidot', font=("Helvetica", 14))
        self.values_label.pack(side=BOTTOM)
        self.values_label.configure(background="forestgreen", fg="white",
                                    width=1000)
        self.data_label = Label(self.master, fg="white",
                                text=str(self.state_display), font=("Helvetica", 14))
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
                                    text="Time Elapsed Since Entering Orbit:",
                                    font=("Helvetica", 14))
        self.timestep_label.pack(side=TOP)
        self.time_label = Label(self.master, text=str(self.sim_env.t_instance),
                                font=("Helvetica", 14))
        self.time_label.pack(side=TOP)

        # Equilibrium orbit
        self.eq_orbit = self.sim_env.equil_orbit(1000)
        self.x_eq, self.y_eq = self.sim_env.convert_cartesian(self.eq_orbit)

        # "STOP" button to terminate process
        button = Button(master=self.master, text="EXIT ORBIT",
                        fg="red", font=("Helvetica", 14),
                        command=self.master.destroy)
        button.pack(side=TOP)

        # Figure 1
        self.fig1 = plt.Figure()
        self.a = self.fig1.add_subplot(1, 1, 1)
        earth = mpimg.imread('earth.png')
        imagebox = OffsetImage(earth, zoom=0.13)
        earth_img = AnnotationBbox(imagebox, (0.3, 0.3), frameon=False)
        self.a.add_artist(earth_img)
        self.a.plot(self.x_eq, self.y_eq, linewidth=1, color='r',
                    linestyle='--', label='Equilibrium Orbit')
        self.a.plot(self.x_input, self.y_input, linewidth=3,
                    color='g', linestyle='--', label='Real-Time Orbit')
        self.fig1.legend(loc=1, fontsize="small")
        self.a.set_title('Satellite Path With Control Input')

        # Figure 2
        self.fig2 = plt.Figure()
        self.b = self.fig2.add_subplot(1, 1, 1)
        earth = mpimg.imread('earth.png')
        imagebox = OffsetImage(earth, zoom=0.13)
        earth_img = AnnotationBbox(imagebox, (0.3, 0.3), frameon=False)
        self.b.add_artist(earth_img)
        self.b.plot(self.x_eq, self.y_eq, linewidth=1, color='r',
                    linestyle='--', label='Equilibrium Orbit')
        self.b.plot(self.x_no_input, self.y_no_input, linewidth=3,
                    color='g', linestyle='--', label='Real-Time Orbit')
        self.fig2.legend(loc=1, fontsize="small")
        self.b.set_title('Satellite Path Without Control Input')

        # Init plots
        Gui.canvas_a = FigureCanvasTkAgg(self.fig1, master=self.master)
        Gui.canvas_a.get_tk_widget().pack(side=LEFT)
        Gui.canvas_b = FigureCanvasTkAgg(self.fig2, master=self.master)
        Gui.canvas_b.get_tk_widget().pack(side=RIGHT)
        Gui.canvas_a.draw()
        Gui.canvas_b.draw()

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
                    color='g', linestyle='--', label='Real-Time Orbit')

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
