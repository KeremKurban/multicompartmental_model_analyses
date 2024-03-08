from neuron import h,gui
import matplotlib.pyplot as plt

h.load_file("mosinit.hoc")
h.fig_1()
h.fig1c()

ic = h.IClamp[0]
ic.amp = 0
ns = h.NetStim()
ns.start = 50
ns.number = 10
ns.interval = 50

syn = h.ExpSyn(h.soma(0.5))
syn.tau = 3
syn.e = 0
nc = h.NetCon(ns,syn)
nc.weight[0] = 0.01
nc.delay = 0

ns.number = 200
ns.noise = True


t = h.Vector().record(h._ref_t)
v = h.Vector().record(h.soma(0.5)._ref_v)

h.finitialize(-70)
h.continuerun(1000)

plt.plot(t,v)
plt.show()

