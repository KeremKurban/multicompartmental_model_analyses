from neuron import h, gui
from neuron.units import mV,ms
import plotly.graph_objects as go
import sys
import itertools

h.load_file('import3d.hoc')
h.load_file('stdrun.hoc') # when you import gui, it automatically loads stdrun.hoc

print(f'analyzing {sys.argv[1]}')

class Cell:
    def __init__(self,morphology):
        self.morphology = morphology
        self.load_morphology()
        self.discretize()

    def __str__(self) -> str:
        return self.morphology
    
    def discretize(self):
        # guarantees odd number of segments
        for sec in self.all:
            sec.nseg = int(sec.L) + 1
            if sec.nseg % 2 != 0:
                sec.nseg += 1
    
    def load_morphology(self):
        cell = h.Import3d_SWC_read()
        cell.input(f'{self.morphology}.swc')
        i3d = h.Import3d_GUI(cell, False)
        i3d.instantiate(self)

c = Cell(sys.argv[1])

all_diams = list(itertools.chain.from_iterable(
    [[sec.diam3d(i) for i in range(sec.n3d())] for sec in h.allsec()]
))

print(f'Minimum diameter is {min(all_diams)} um')
print(f'Maximum diameter is {max(all_diams)} um')


fig = go.Figure()
for sec in c.all:
    rvp = h.RangeVarPlot('diam', c.soma[0](0.5), sec(1)) #plotting diameter not diam3d
    rvp.plot(fig,marker_color='black')

fig.update_layout({
    "title": sys.argv[1],
    "xaxis_title": "Distance from the soma (um)",
    "yaxis_title": "Diameter (um)"
})

fig.show()

h.pas.insert(c.all)
for sec in c.all:
    for seg in sec:
        seg.pas.g = 1e-8

ic = h.IClamp(c.soma[0](0.5))
ic.amp = 1 #nA
ic.delay = 0 # ns
ic.dur = 100 # ms

# t = h.Vector().record(h._ref_t)
# v = h.Vector().record(c.soma[0](0.5)._ref_v)

ps = h.PlotShape()
ps.variable("v")
ps.scale(-80,60)
ps.exec_menu("Shape Plot")

h.flush_list.append(ps)

h.finitialize(-65 * mV)
h.continuerun(50 * ms)