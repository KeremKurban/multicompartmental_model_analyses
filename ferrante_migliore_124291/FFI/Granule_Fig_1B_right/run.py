# Import NEURON modules for simulation and GUI
from neuron import h, gui
import matplotlib.pyplot as plt

# Load standard GUI library for NEURON
h.load_file("nrngui.hoc")

# Deactivate variable time step solver
h.cvode_active(0)

# Set resting membrane potential
Vrest = -74

# Set the simulation time step
h.dt = 0.1
# Sodium and potassium maximum conductances (S/cm2)
gna = 0.2
gk = 0.06

# Set simulation temperature (not implemented changes)
h.celsius = 22.0

# Membrane resistance, capacitance, and axial resistances
Rm = 6000
Cm = 2.5
RaAll = 200
RaAx = 50

# Load morphology and segmentation scripts
h.xopen("n500-axon.hoc")
h.xopen("fixnseg.hoc")

# Create an IClamp object at the middle of the first soma
stim = h.IClamp(h.soma[1](0.5))
stim.delay = 100  # Start time of the current injection
stim.dur = 2000  # Duration of the current injection
stim.amp = 0.05   # Amplitude of the current injection, set as needed

# Set the stop time of the simulation
tstop = 3000

# Create an APCount object to count action potentials
apc = h.APCount(h.soma[1](0.5))
apc.thresh = -20  # Threshold voltage for detecting AP

# Create a Vector to record times of action potentials
tempo = h.Vector()

# # Use the soma[1] section, set up a NetCon to record AP times
# h.soma[1].push()
# apct = h.NetCon(h._ref_v, None, sec=h.soma[1])
# apct.record(tempo)
# h.pop_section()  # Leave the soma[1] section context

# Correct approach to record action potential times in Python
# Here we directly link the APCount object's detection to the Vector
apc.record(tempo)


# Function to calculate and print the total number of segments
def geom_nseg():
    tot = 0
    for sec in h.allsec():
        tot += sec.nseg
    print("Total number of segments:", tot)

geom_nseg()  # Call the function to print total segments

# Function to insert channels and set properties for all sections
def insert_channels():
    for sec in h.allsec():
        sec.insert('pas')  # Insert passive channel
        sec.e_pas = Vrest  # Set reversal potential for passive channel
        sec.g_pas = 1 / Rm  # Set conductance for passive channel
        sec.cm = Cm  # Set membrane capacitance
        if 'axon' in sec.name():
            sec.Ra = RaAx  # Set axial resistance for axon
        else:
            sec.Ra = RaAll  # Set axial resistance for other sections
        sec.insert('ichan2')  # Insert custom channel 'ichan2'
        sec.gnatbar_ichan2 = gna  # Set maximal conductance for Na+
        sec.gkfbar_ichan2 = gk   # Set maximal conductance for Kf
        sec.gl_ichan2 = 0.0  # Set leak conductance (example, set to 0)
        if 'dend' in sec.name():
            sec.gnatbar_ichan2 = gna / 3  # Reduce Na+ conductance in dendrites

insert_channels()  # Call the function to insert channels and set properties




# Function to initialize the simulation (setting initial conditions)
def init():
    h.finitialize(Vrest)  # Initialize membrane potential
    for sec in h.allsec():
        sec.enat = 55  # Set reversal potential for Na+
        sec.ekf = -90  # Set reversal potential for Kf
        sec.eks = -90  # Set reversal potential for Ks (example)
        sec.v = Vrest  # Initialize sections' membrane potential to Vrest
    h.fcurrent()  # Update currents at initial state

# Note: GUI-related code in the original HOC script needs adaptation or replacement with Python GUI/plotting libraries
# ps = h.PlotShape()
# ps.variable('v')
# ps.scale(-80,60)
# ps.exec_menu('Shape Plot')

# h.flush_list.append(ps)


# Setup for PlotShape
ps = h.PlotShape()  # False for a light background if preferred, True or omit for default
ps.variable('v')
ps.scale(-80, 60)
ps.exec_menu('Shape Plot')


# Add to flush_list for automatic updates
h.flush_list.append(ps)

# Setup vectors for recording time and voltage at a specific location (e.g., soma[0](0.5))
time = h.Vector().record(h._ref_t)
voltage = h.Vector().record(h.soma[0](0.5)._ref_v)

def plot_voltage():
    plt.figure(figsize=(8, 4))
    plt.plot(time, voltage, label='Membrane Potential')
    plt.xlabel('Time (ms)')
    plt.ylabel('Voltage (mV)')
    plt.title('Membrane Potential Over Time')
    plt.legend()
    plt.show()


# Finally, call the run_simulation function to start the simulation
    
# Function to run the simulation
def run_simulation():
    h.finitialize(Vrest)  # Initialize the simulation to resting potential
    h.continuerun(tstop)  # Run the simulation until tstop
    plot_voltage()  # Plot the recorded voltage over time

run_simulation()
# Print simulation results, specifically the stimulation amplitude and calculated frequency
if tempo.size() > 9:
    frequency = (tempo.size() - 9) * (1000 / (tempo.x[tempo.size() - 1] - tempo.x[9]))
    print("Stimulation amplitude:", stim.amp, "nA ==> Frequency:", frequency, "Hz")
else:
    print("Stimulation amplitude:", stim.amp, "nA ==> Insufficient action potentials to calculate frequency.")
