from neuron import h, gui
from neuron.units import mV,ms
import plotly
import plotly.graph_objects as go
import sys
import itertools, math

h.load_file('import3d.hoc')
h.load_file('stdrun.hoc') # when you import gui, it automatically loads stdrun.hoc

print(f'analyzing {sys.argv[1]}')

class Cell:
    def __init__(self,morphology):
        self.morphology = morphology
        self.load_morphology()
        self.discretize()
        self.add_channels()

    def __str__(self) -> str:
        return self.morphology
    
    def add_channels(self):
        h.hh.insert(self.axon) #insert accepts list of sections
        h.hh.insert(self.soma)
        passive_locs = [
            sec for sec in self.all if sec not in self.axon and sec not in self.soma
            ]

        h.pas.insert(passive_locs)
        for sec in passive_locs:
            for seg in sec:
                seg.pas.g = 1e-6

    
    def discretize(self):
        freq = 100 #Hz
        d_lambda = 0.1
        for sec in self.all:
            sec.nseg = math.ceil((sec.L / (d_lambda * h.lambda_f(freq))) / 2.) * 2 + 1

    
    def load_morphology(self):
        cell = h.Import3d_SWC_read()
        cell.input(f'{self.morphology}.swc')
        i3d = h.Import3d_GUI(cell, False)
        i3d.instantiate(self)

c = Cell(sys.argv[1])

syn = h.ExpSyn(c.soma[0](0.5))
syn.e = 0 # mV
syn.tau = 2 * ms

ns = h.NetStim()
ns.number = 1
ns.start = 5 * ms

nc = h.NetCon(ns,syn)
nc.weight[0] = 0.1
nc.delay = 0

t = h.Vector().record(h._ref_t)
v = h.Vector().record(c.soma[0](0.5)._ref_v)

h.finitialize(-65 * mV)
h.continuerun(10 * ms)

ps = h.PlotShape(False)
ps.variable("v")
ps.scale(-65,20)
# add colorbar
ps.show(0)
ps.plot(plotly).show()

fig = go.Figure()
fig.add_trace(go.Scatter(x=t, y=v))
fig.update_layout({
    "title": "soma(0.5) membrane potential",
    "xaxis_title": "Time (ms)",
    "yaxis_title": "Voltage (mV)"
})
fig.show()

