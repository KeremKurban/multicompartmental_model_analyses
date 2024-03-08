Reconstitution of action potentials in a model of a hippocampal mossy
fiber from action potential-evoked sodium, potassium and calcium
current waveforms as described in

Henrik Alle, Arnd Roth and J. R. P. Geiger, Energy-efficient action
potentials in hippocampal mossy fibers, Science 325, 1405-1408
(2009). doi: 10.1126/science.1174331


This directory contains mod and hoc files for the NEURON simulator, as
well as dat files representing the conductance waveforms which are
read in via the stepforce() function in GNa.mod, GK.mod and
GCa.mod.

To run the simulations, follow these steps:

1. compile the mod files using nrnivmodl under Mac OS X and Linux, or
mknrndll under Windows

2. run reconstitution.hoc in NEURON. This performs the simulation
shown in Fig. 2A and B of the paper and plots the results using
NEURON's graphical user interface.

3. if desired you can perform an automated fit of the measured action
potential waveform by running fit_th1.hoc. This writes results to
three files: parameters1.txt, measuredAP1.txt, and modelAP1.txt and
may take several hours.


If you have questions please contact

henrik.alle@charite.de
arnd.roth@ucl.ac.uk
