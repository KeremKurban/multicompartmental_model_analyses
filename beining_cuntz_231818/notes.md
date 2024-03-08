# Notes

Looking at the decision letter at elife , i see following features important for granule cells in DG.

- sensitivity analyses
- the relationship between ion channels and AP features
- changes in excitability in adult vs early born neurons. but does a newly born neuron at adult stage has the same excitability as newly born neuron in embryonic stage? im confused about the distinction. there are 4 cases. early born young stage, eb adult stage, adult born youngh stage , adult born adult stage.

characterization of the ion channel behavior (activation curves, etc), maybe a table of the ion channel kinetics (time constants, voltage of half act/inact, etc)d) 

mentions aradi and holmes 1999 model as classical DG model and shows some limitation of aradi compared to theirs.
https://modeldb.science/116740



### abGC has lower excitability coming from lesser dendritic extent, and lower spine density

"""
d) Morphology of adult-born neurons: To match physiological properties of adult-born neurons the authors have changed channel properties. However, it is well-established that maturing neurons have significantly shorter dendritic arborization and lesser spine density as well (Zhao et al., 2006). As mentioned by the authors, the lesser dendritic extent and the reduced surface area caused by the lack of spines would increase the excitability of the cell as well. The authors have accounted for spine density differences when they assess synaptic integration in the mature and immature GCs. But, why did the authors not consider matching morphological profiles of adult-born neurons at various ages to understand the physiology of adult-born neurons?
"""

Response:

"""
The reviewer is right that we have modeled (implicitly) the lower spine density in young abGCs. We have not studied morphological differences of abGCs since we focused on 4 weeks old abGCs that don’t display any further significant alterations in their dendritic morphology (see our dendrite analyses in Beining, Jungenitz et al., 2016). It would be certainly insightful to model also younger abGCs with reduced dendrite arborization and a different ion channel composition. However, since we used electrophysiology data from 4 week old cells (Mongiat et al., 2009) because these cells exhibit most interesting functional differences (e.g. higher excitability and synaptic plasticity), we restricted our modeling to this particular cell age group.
"""


so does abGCs have lesser dendritic extent and lesser spine density or early born cells have lesser dendritic extent and lesser spine density as they grow older?

gpt answer: abGCs have lesser dendritic extent and lesser spine density because they are young. the reason for lesser spine density is not clear.


### Unconstraint Granule Cells without location dependent ion channels

'''
i) Dendritic ion channels and their properties: Unlike CA1 pyramidal neurons (Magee, J Neuroscience, 1998; Hoffman et al., Nature, 1997; Colbert et al., J Neuroscience 1997; Magee and Johnston, J Physiology, 1995), the dendritic ion channel profiles of DG GC neurons are not well characterized through systematic location-dependent cell-attached recordings. This is important data because channel physiology is not just a function of the main and auxiliary subunits expressed, but is dependent on the relative expression profiles of different subunits, the phosphorylation state of the different residues on each of these subunits, and structural interactions across channels that might alter functionality (Anderson et al., Nat Neuroscience, 2010; Heath et al., J Neuroscience, 2014; An et al., Nature, 2000; Gasparini and Magee, J Physiology, 2002). Several studies that the authors have cited and have used models from also strongly emphasize the critical importance of intracellular milieu in determining the specific physiological properties, which is not directly determinable only from knowledge of the subunits expressed. Additionally it is impossible to assume that the dendritic and somatic channels have the same kinetics and voltage-dependence profiles; several channels show significant gradients in their conductances/kinetics/voltage-dependence and these properties and play important physiological roles in location-dependent input processing (Magee, J Neuroscience, 1998; Hoffman et al., Nature, 1997; Colbert et al., J Neuroscience 1997; Magee and Johnston, J Physiology, 1995; Migliore and Shepherd, Nature Reviews Neuroscience, 2002; Lai and Jan, Nature Reviews Neuroscience, 2006; Narayanan and Johnston, J Neurophysiology, 2012). Therefore, it is important that models also account for these differences and variability in channel properties and location-dependent measurements (Rathour and Narayanan, PNAS, 2014), rather than assuming that the somatic channel properties (kinetics and voltage-dependence) extend to the dendrites as well.
'''


'''
We share the concern of this reviewer about the complexities of channel modeling. We have added a brief note on these issues in Appendix 2 (subsection “Predictions of the GC model”), which discusses the details of GC models. We cite also the Rathour and Narayanan paper since it is relevant in this context.
'''

## Model Usefulness

- Granule Cell model : Adult , young , epileptic (mouse and rat)
- modeling certain conditions of circuit
- Dataset usage of Groisman et al (Schinder group): Differential Coupling of Adult-Born Granule Cells to
Parvalbumin and Somatostatin Interneurons https://www.cell.com/cell-reports/pdf/S2211-1247(19)31644-4.pdf 