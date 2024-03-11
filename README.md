# Analysis of Published mMlticompartmental Models

Several Published emodels have been analyzed to see if they can be implemented to BBP pipeline
https://modeldb.science/modellist/257

By checking this we know what are the necessary features for a successful emodel and also datasets used to tune. The github repo here tries to replicate the models and documents the results in notes.md

 

## Alle et al 2009

**Notes:** This study models the axonal mechanism and how energy consumption of Mossy Fibers are not as high as previously thought by HH assumption.
 
**useful for:**

Mossy Fiber axon modeling and parameters for conductances , amplitudes etc
Experimental traces for MF . Fig 1
 
**ModelDB**: https://modeldb.science/135838

 

## Aradi & Holmes 1999
**Notes**: According to Beining et al , this was the gold-standard model before their paper. They indicate models dont behave correctly outside tuned region. However, Beining model is also not behaving consistent. Anyway, when i checked the modeldb, it seems there are too few mod files and most channels are constructed with channel builder function of NEURON. So its not a good candidate unless those channels are exported as mod files.

**ModelDB** : https://modeldb.science/116740?tab=2

 

## Beining et al 2017
**Notes**: From Cuntz and Jedlicka Collaboration. Featuring T2N toolbox and using DGsg_GC as an examplar case. Its an improvement on Aradi & Holmes, 1999 . The detailed analyses can be found in examplar codes written in MATLAB. Since reviewers asked them to restructure the paper as a toolbox paper, they removed some extensive analysis and discussion on the GC model.

I cloned the model in a github repo, and reported my findings here.

**ModelDB**: https://modeldb.science/231818 

 

## Ferrante et al 2009
**Notes**: From Migliore and Ascoli . Analyzed FFI for IO response of DGsg_GC with MOPP cells. Used double exponential time courses AMPA, NMDA and GABAa synapses to buffer IO regime.

The code to replicate is in hoc format. I tried to convert it to python here. TODO: Needs adjustment.

**ModelDB**: https://modeldb.science/124291 


Examples :

1. example2.py : loads a morphology and analyzes dendrites over path distance. injects passive current mechanism and runs a current clamp to check signal propagation within neuron
2. example3.py : defines a cell class and imports a given SWC morphology file , plots the neuron and injects a current after inserting hh mech to the soma and axon and passive mech to the dendrites



