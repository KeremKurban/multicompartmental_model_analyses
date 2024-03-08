from neuron import h, gui
h.load_file('stdlib.hoc') # Standard library for NEURON
h.load_file('import3d.hoc') # Library for importing 3D morphologies

# Step 1: Import the SWC file
cell = h.Import3d_SWC_read()
cell.input('SEU_CA1/17781_00146.swc')
i3d = h.Import3d_GUI(cell, 0)
i3d.instantiate(None)

# Define a function to set ion channels
def set_ion_channels(section, na_density, k_fast_density, k_slow_voltage_density=None, k_slow_ca_density=None):
    section.insert('na')
    section.gbar_na = na_density
    section.insert('kfast')
    section.gbar_kfast = k_fast_density
    if k_slow_voltage_density is not None:
        section.insert('kslowv')
        section.gbar_kslowv = k_slow_voltage_density
    if k_slow_ca_density is not None:
        section.insert('kslowca')
        section.gbar_kslowca = k_slow_ca_density

# Step 2: Distribute Ion Channels
for sec in h.allsec():
    if 'soma' in sec.name():
        set_ion_channels(sec, na_density=0.1, k_fast_density=0.1)  # Low density in soma
    elif 'axon' in sec.name():
        if 'axon[0]' in sec.name():  # Assuming axon[0] is the AIS
            set_ion_channels(sec, na_density=1.0, k_fast_density=1.0)  # High density in AIS
    elif 'dend' in sec.name():
        set_ion_channels(sec, na_density=0.1, k_fast_density=0.0, k_slow_voltage_density=0.1, k_slow_ca_density=0.1)  # Specified densities in dendrites
