"""
Functionalize a healthy DGsg_GC Morphology with experimental data:

Type 2 DGsg_GC cell (n=variable depending on the feature) 
https://neuroelectro.org/data_table/49109/
https://neuroelectro.org/data_table/49106/

Ephys:
1. Impaired firing properties of dentate granule neurons in an Alzheimer's disease animal model are rescued by PPARγ agonism
https://doi.org/10.1152/jn.00419.2014
2. Some parameters can be obtained from neuroelectro at : https://neuroelectro.org/neuron/66/


Morphologies:
See morphocurate DGsg_GC

Mod files:
Option 1: https://bbpgitlab.epfl.ch/hpc/sim/models/hippocampus
Option 2: https://bbpgitlab.epfl.ch/hpc/sim/models/mousify
Option 3 (Beining et al 2017, Cuntz, Jedlicka): https://modeldb.science/231818


Notes: 
Bluepyopt ex notebook at https://github.com/BlueBrain/BluePyOpt/blob/master/examples/simplecell/simplecell.ipynb was used to create this script

Author(s):

Kerem Kurban
Aurelian Jacquer
"""
# %matplotlib inline
import matplotlib.pyplot as plt
# %load_ext autoreload
# %autoreload\
import bluepyopt as bpop
import bluepyopt.ephys as ephys
import logging
logger = logging.getLogger()
logger.setLevel(logging.DEBUG)

# SELECT MORPH
morph_path = '1-L2-C4-N1.swc'
morph_name = morph_path.split('.')[0]
morph = ephys.morphologies.NrnFileMorphology(morph_path)

# SECTION TYPES
somatic_loc = ephys.locations.NrnSeclistLocation('somatic', seclist_name='somatic')
basal_loc = ephys.locations.NrnSeclistLocation('basal', seclist_name='basal')
apical_loc = ephys.locations.NrnSeclistLocation('apical', seclist_name='apical')
axon_loc = ephys.locations.NrnSeclistLocation('axon', seclist_name='axon')
ais_loc = ephys.locations.NrnSeclistLocation('AIS', seclist_name='ais') # TODO: check if name is true

#TODO: should we add basal, apical, AIS sectios here. I added to constrain if we see them

# MECHANISMS TO BE USED

#TODO: do we insert all mod files here that is mentioned in the readme above?
hh_mech = ephys.mechanisms.NrnMODMechanism(
        name='hh',
        suffix='hh',
        locations=[somatic_loc])

mech_list = [hh_mech]
# PARAMETERS

# TODO : need to set all params here, discuss what should be frozen and what should not

cm_param = ephys.parameters.NrnSectionParameter(
        name='cm',
        param_name='cm',
        value=1.0,
        locations=[somatic_loc],
        frozen=True)

gnabar_param = ephys.parameters.NrnSectionParameter(                                    
        name='gnabar_hh',
        param_name='gnabar_hh',
        locations=[somatic_loc],
        bounds=[0.05, 0.125],
        frozen=False)     

gkbar_param = ephys.parameters.NrnSectionParameter(
        name='gkbar_hh',
        param_name='gkbar_hh',
        bounds=[0.01, 0.075],
        locations=[somatic_loc],
        frozen=False)

params_list = [cm_param, gnabar_param, gkbar_param]

# Create Cell Template

simple_cell = ephys.models.CellModel(
        name=f'DGsg_GC__{morph_name}',
        morph=morph,
        mechs=mech_list,
        params=params_list)  

logger.info(simple_cell)


# Protocols

soma_loc = ephys.locations.NrnSeclistCompLocation(
        name='soma',
        seclist_name='somatic',
        sec_index=0,
        comp_x=0.5)

# stims in nA
# TODO: how can we add std
stims = [('step140pA', 1.4), ('step150pA', 1,5), ('step160pA', 1.6), ('step170pA', 1.7), 
         ('step180pA', 1.8), ('step190pA', 1.9), ('step200pA', 2.0), ('step210pA', 2.1), ('step220pA', 2.2)]
stim_duration = 500 # ms

# bluepyopt parameters
stim_delay = 100 # ms
post_stim_duration = 100 # ms
total_duration = stim_delay + stim_duration + post_stim_duration # ms

sweep_protocols = []
for protocol_name, amplitude in stims:
    stim = ephys.stimuli.NrnSquarePulse(
                step_amplitude=amplitude,
                step_delay=stim_delay,
                step_duration=stim_duration,
                location=soma_loc,
                total_duration=total_duration)
    
    rec = ephys.recordings.CompRecording(
            name='%s.soma.v' % protocol_name,
            location=soma_loc,
            variable='v')
    protocol = ephys.protocols.SweepProtocol(protocol_name, [stim], [rec])
    sweep_protocols.append(protocol)

n_step_protocol = ephys.protocols.SequenceProtocol('n_step_protocol', protocols=sweep_protocols)


# Run the protocol

nrn = ephys.simulators.NrnSimulator()

default_params = {'gnabar_hh': 0.1, 'gkbar_hh': 0.03}
responses = n_step_protocol.run(cell_model=simple_cell, param_values=default_params, sim=nrn)

# Defining eFeatures and objectives

# efel_feature_means = {'step1': {'Spikecount': 1}, 'step2': {'Spikecount': 5}}

efel_feature_means = {  'step140pA': {'Spikecount': 11.9}, 
                        'step150pA': {'Spikecount': 12.8}, 
                        'step160pA': {'Spikecount': 13.4}, 
                        'step170pA': {'Spikecount': 14},
                        'step180pA': {'Spikecount': 14.9 },
                        'step190pA': {'Spikecount': 15.1},
                        'step200pA': {'Spikecount': 15.6},
                        'step210pA': {'Spikecount': 16.4},
                        'step220pA': {'Spikecount': 17.3}
} # from https://neuroelectro.org/data_table/49109/ 
#TODO: how to add std ?

objectives = []

for protocol in sweep_protocols:
    stim_start = protocol.stimuli[0].step_delay
    stim_end = stim_start + protocol.stimuli[0].step_duration
    for efel_feature_name, mean in efel_feature_means[protocol.name].items():
        feature_name = '%s.%s' % (protocol.name, efel_feature_name)
        feature = ephys.efeatures.eFELFeature(
                    feature_name,
                    efel_feature_name=efel_feature_name,
                    recording_names={'': '%s.soma.v' % protocol.name},
                    stim_start=stim_start,
                    stim_end=stim_end,
                    exp_mean=mean,
                    exp_std=0.05 * mean)
        objective = ephys.objectives.SingletonObjective(
            feature_name,
            feature)
        objectives.append(objective)

# Cell Evaluator
score_calc = ephys.objectivescalculators.ObjectivesCalculator(objectives) 
cell_evaluator = ephys.evaluators.CellEvaluator(
        cell_model=simple_cell,
        param_names=['gnabar_hh', 'gkbar_hh'],
        fitness_protocols={n_step_protocol.name: n_step_protocol},
        fitness_calculator=score_calc,
        sim=nrn)

logger.info(cell_evaluator.evaluate_with_dicts(default_params))

optimisation = bpop.optimisations.DEAPOptimisation(
        evaluator=cell_evaluator,
        offspring_size = 10)

final_pop, hall_of_fame, logs, hist = optimisation.run(max_ngen=5)

logger.info('Hall of fame: ')

for ind in hall_of_fame:
    logger.info(ind)
    logger.info('Fitness: %f' % ind.fitness.values)

best_ind = hall_of_fame[0]
print('Best individual: ', best_ind)
print('Fitness values: ', best_ind.fitness.values)

best_ind_dict = cell_evaluator.param_dict(best_ind)
logger.info(cell_evaluator.evaluate_with_dicts(best_ind_dict))

# Plotting the results
import matplotlib.pyplot as plt
import numpy
gen_numbers = logs.select('gen')
min_fitness = logs.select('min')
max_fitness = logs.select('max')
plt.plot(gen_numbers, min_fitness, label='min fitness')
plt.xlabel('generation #')
plt.ylabel('score (# std)')
plt.legend()
plt.xlim(min(gen_numbers) - 1, max(gen_numbers) + 1) 
plt.ylim(0.9*min(min_fitness), 1.1 * max(min_fitness)) 