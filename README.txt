	
        .-://///:`  .:/+++++/-`      .--.             `---`  `--
     -/++//:---:.`://+syyyssoo+`    ohhy`            /hhh.  -hy`
   `/++/-`       ::/ohhyyssssoss-   ohhh+           .yhhh.  .hy`          
   :++/.        `:::sysoo+++++oss.  ohoyh-         `ohoyh.  .hy`          
   ++//`        `--:/oo+///://+os:  oh//hs`        :hs.yh.  .hy`          
   /+//.       `..--:////:--:/oos.  oh/`sh/       `yh-`yh.  .hy`          
   `////:-.......---::://///++oo-   oh/ -hy.      +h+ `yh.  .hy`          
     .:///:::::--::::://///++oo:    oh/  +hs     -hy` `yh.  .hy`          
   `::-``..--::::::://osyyysoooo.   oh/  `yh:   `sh:  `yh.  .hy`          
   :o+/`      .:////oyhyyyyyyssss`  oh/   :hy`  /ho`  `yh.  .hy`          
   /oo/        .///oyysoo+++oosyy-  oh/    oho .hh.   `yh.  .hy`          
   .sso:       `+++oso+//////syyy`  oh/    .hh-oh/    `yh.  .hy`          
    :sss+-`   ./oooooo//:::+syyy.   oh/     /hhhs`    `yh.  -hy`          
     `/syssooossssssssssssyyyy/`    oh/      shh-     `yh.  -hhooooooooooo
       `-/+oso+/-.-:/osyyso/-`      -:.      .:-      `--`  `:::::::::::::
    
   8888888          888                                     888
     888            888                                     888
     888            888                                     888
     888   88888b.  888888 .d88b.   .d88b.  888d888 8888b.  888888 .d88b.  888d888
     888   888  88b 888   d8P  Y8b d88P 88b 888P        88b 888    d8888b  888P   
     888   888  888 888   88888888 888  888 888    .d888888 888   888  888 888
     888   888  888 Y88b. Y8b.     Y88b 888 888    888  888 Y88b. Y88..88P 888
   8888888 888  888  Y888   Y8888    Y88888 888    Y888888  Y888    Y88P   888
                                     888
                                Y8b d88P
                                 Y88P"

Updated 09/09/2011
alex.holehouse@gmail.com

   ,---------------------------------------------------------------.
  | Table of contents                                               |
  | 1. Foreword                                                     |
  | 2. Installation		                                    |
  | 3. User Guide                       		            |
  | 4. Code Documentation		                            |
  |                                                                 |
   `---------------------------------------------------------------'


_____________________________________________________________________

1. Forward
_____________________________________________________________________

1.1 Overview

SBMLIntegrator is a a simple to use tool for Linux which allows for 
the integration of two SBML models into one single model. The purpose
of this functionality is to facilitate model integration to propel
the investigation of crosstalk between separately defined but biologically
connected pathways.

SBML is an ideal format for defining signalling pathways, but those
pathways are not small, discrete systems, and are instead fragments of
a complex, cellular signalling network. By integrating these isolated
pathways into a single larger pathway, we create a more biologically
relevant picture of the pathways by contextualizing them. This then
provides an additional dimension of analysis for model checking, as well
as the investigation of the impact of antagonistic and agonistic pathways.

The object of SBMLIntegrator is ease of use. The software should be 
intuitive, simple and concise, reducing difficulties to the biological
complexity as opposed to SBML related problems. The SBML format relies
heavily on internal dependencies, making manual model integration complex
convoluted and error prone. This software is designed to automate this
process, reducing this significant barrier to researchers.

This software is distributed under the GPL licence, and was developed
wholly and exclusively by Alex Holehouse as part of his dissertation 
project. This project is to be submitted in partial fulfilment of the 
requirements for the MSc Degree in Computing Science for the 2010-
2011 academic year. Any questions should be addressed to 
alex.holehouse@gmail.com.

1.2 Missing Elements

This software is currently in alpha. Therefore, at this stage, the 
following functionality is not yet present. 

- Integration of Function Definitions
- Integration of Constraints
- Integration of Initial Assignments
- Integration of Events

These functionalities have not been completed yet, as they are
invalid in the SimBiology MATLAB package (with which our integrated
models are simulated) and because they were not present in the models
we used.

A more widespread issue is that both models must be L2V1. Multi-level
support will be introduced ASAP, but for now, L2V1 represents an 
easily accesible common denominator.

_____________________________________________________________________

2. Installation
_____________________________________________________________________

SBMLIntegrator requires a Linux machine for installation. Built in C++,
we hope to add a GUI layer using the QT framework, which would facilitate
installation and use in both Windows and Linux based environments (see 
section 4 for more details).

In keeping with the idea of keeping it simple, to install just run

bash INSTALL.sh

in the SBMLIntegrator folder.

Once this is done you should add the new complete libsbml/lib path to 
the $LD_PATH variable. To do this you add an export command to your 
.basrc (normally found in your home directory as a hidden file, use 
ls -a to check it out).

We use export as follows;

export LD_LIBRARY_PATH=<lib directory path>:$LD_LIBRARY_PATH

where lib directory path is the full path where you've now 
installled LibSBML.

For example, if I'd run INSTALL.sh from 

	/home/john/Documents/SBMLIntegrator

the export command would be be

export LD_LIBRARY_PATH=/home/john/Documents/SBMLIntegrator/libsbml/lib:$LD_LIBRARY_PATH

What this is doing is ADDING this new location to the LD_LIBRARY_PATH variable,
the colon means we add it to the front of the variable.

This line should be included anywhere in the .bashrc file, meaning
everytime we start a terminal the variable is set (it resets itself
on each session).

If you're using csh, do the equvalent using setenv

setenv LD_LIBRARY_PATH <lib directory path>

If you're still confused try 
http://sbml.org/Software/libSBML/docs/cpp-api/libsbml-accessing.html

To check this has been done, use

echo $LD_LIBRARY_PATH
You should see the libsbml/lib directory there. If you don't see
this you need to restart your shell for the new changes to take
effect.


//////////////////////////////////////////////////////////////////////
_____________________________________________________________________

3. User guide
_____________________________________________________________________

To run the program simple use ./SBMLIntegrator

SBMLIntegrator has been written with the idea that the user should have
a reasonable knowledge of SBML in terms of how it works, but not in terms
of the file format or indeed the SBMLIntegrator software. Instead, options
should be intuitive and expected. The software is not complicated to use - 
the complexity associated with the model integration is hidden from the user.

//////////////////////////////////////////////////////////////////////
3.1 Conceptual overview

For integration, there are three models

- The integration model
  This is the new model you create, it starts off life as one of your
  two models loaded from file, and is then built up by integrating elements
  from the other model into it.

- The base model
  This is the model we begin with for the integration model. It is not used
  once it has been copied to form the starting point for the integration model

- The import model
  This is the other model, from which elements are imported and integrated into
  the integration model. Typically, you'd want the larger of the two models 
  to be the base model (and as a result the base of the integration model)

SBMLIntegrator integrates two models based on a configuration file, named

integrate.conf

A configuration file defines what elements of one model (the import model)
are brought into the other model (the integration model). SBML files are 
based on lists of ten elements shown below;

- Function Definitions
- Unit Definitions
- Compartments
- Species
- Parameters
- Initial Assignments
- Rules
- Constraints
- Reactions
- Events

Each of these lists holds 0 or more elements. For integration, the .conf 
file defines which of these elements from the import model should be

- Imported into the integration model
- Integrated into the integration model
- Replaced by elements in the integration model

This is easier explained with an example;

---------------------------------------------------------------------
// Section from integrate.conf
...
Species:
	Import: [0,12,15]	
	Replace: [7,1] [9,2] [11,3]
	Integrate: [13,14]
...
---------------------------------------------------------------------

This section defines the following;

- Species 0, 12 and 15 are to be imported from the import model into the 
  integration model

- In the integration model, replace references to species 1 (as defined 
  in the import model) with references to species the import species 7 
  as defined in the BASE model. Similarly, references to species 2 
  in the import model are replaced by references to species 9 in the 
  base model, and references to species 3 --> species 11.

- In the integration model, integrate species 13 from the base model and 14
  from the import mode together in an interactive manner, allowing you to 
  combine elements of both to form either a new species in addition to 
  species 13, or to restructure species 13 in the integration model

By using replacement, import and integration functionality, we can combine
two models together. This is the basic premise of how the software works.

SBMLIntegrator essentially operates in two modes;

//////////////////////////////////////////////////////////////////////
3.2 - One model loaded

If one model is loaded (e.g. ./SBMLIntegrator my_first_model.xml) we're
presented with the following options;

---------------------------------------------------------------------
   Select an option from below:

 [1] ------------ Explore Models  
 [2] ------------ Display Model Summary  
 [3] ------------ Quit 

 Select: 
---------------------------------------------------------------------

From here you can explore the model (view the components), get a summary
of the model, or quit. These are all self explanatory.


//////////////////////////////////////////////////////////////////////

3.3 - Two models loaded

If two models are loaded (e.g. ./SBMLIntegrator my_first_model.xml 
my_second_model.xml) then initially you'll be asked to select a base
model - the significance of this is explained below

---------------------------------------------------------------------
##############################################################
########################   LOAD FILES   ######################
##############################################################

Which of these files should the BASE MODEL be based on? This is the model 
which forms the foundations of your integration model - i.e. it's copied 
into the software, and then you import, integrate and replace elements 
from the other model (from here on called the IMPORT MODEL) into the 
base model;

 [1] ------------ my_first_model.xml
 [2] ------------ my_second_model.xml

 Please select: 
---------------------------------------------------------------------


After selecting a base model, you're greeted with a similar main menu;


---------------------------------------------------------------------
   Select an option from below:

 [1] ------------ Explore Models  
 [2] ------------ Display Model Summary  
 [3] ------------ Integrate models 
 [4] ------------ Quit 

 Select:
---------------------------------------------------------------------

Options 1 and 2 are the same as if a single model is loaded, except
you're given a choice of which model you want to explore. Option 3 is
where we do the real work of integrating the model. Once you select 3
we run the initial import and replacement based on the configuration
file, as discussed previously. After this initial run of the import and
replace (in that order) we are greeted with the following screen;

---------------------------------------------------------------------
Import model is: my_second_model.xml
 --> Model ID [model ID for my first model]

Base model is: my_first_model.xml
 --> Model ID [model ID for my second model]

 [1] ------------ Integrate Function Definitions (0)
 [2] ------------ Integrate Unit Definitions (0)    
 [3] ------------ Integrate Compartments (1)        
 [4] ------------ Integrate Species (1)             
 [5] ------------ Integrate Parameters (1)          
 [6] ------------ Integrate Initial Assignments (0) 
 [7] ------------ Integrate Rules (2)               
 [8] ------------ Integrate Constraints (0)         
 [9] ------------ Integrate Reactions (2)           
 [10] ----------- Integrate Events (0)              
 [11] ----------- Explore models
 [12] ----------- Explore replacement, import and integration parameters 
 [13] ----------- Write Integrated Model
 [14] ----------- Run replacement
 [15] ----------- Return to main menu 
 Please select an option: 
---------------------------------------------------------------------

Options 1 to 10 allow the user to interactively integrate the named elements.
The numbers in brackets represent the number of elements to be integrated,
and once elements have been integrated, a "DONE" message is displayed after
the selection. The interactive integration process is clearly described with
help messages and should be self explanatory. As an example, we'll later go through
the process of integrating two species.

Option 11 allows the user to display the elements for the base, import or 
integration models in a detailed or non-detailed manner

Option 12 displays parameters relating to the number of elements to replace,
import and integrate

Option 13 allows you to write the integration model to file, giving the
user the option to define a file name. NB the .xml extension should be added

Option 14 allows the user to re-run the replacement sequence based on the 
configuration file and any updates to it which might have been made during
the integration. For example, if you are integrating two species together,
say SpecA and SpecB, you may want all future references to SpecB to in fact
refer to SpecA. This replacement is run automatically on the initial 
integration, but if later you integrate SpecC and SpecD, and SpecC refers
to SpecB then you can re-run replacement with this newly updated rule to
change SpecC so it refers to SpecA instead.

Option 15 allows you to return to the main menu.


//////////////////////////////////////////////////////////////////////

3.4 - Brief tutorial on integrating two species

Below we have a quick run-through on how to integrate two species

1
---------------------------------------------------------------------
Compare SpecA_ID and SpecB_ID
[Species 1 of 1]
### Name ###
    A ----- SpecA
    B ----- SpecB
    Select (A or B): 
---------------------------------------------------------------------

SpecA_ID an SpecB_ID are the IDs of the two species. Initially the user
chooses which of the two names they want the newly integrated species to
have.

2
---------------------------------------------------------------------
### Compartment ###
Ensure that if you select option B, it actually exists in the model 
(i.e. you set it as one of the elements to import in the .conf file. 
Software support to check this coming real soon, but at the moment 
please try and be careful!)
    A ----- cytosol
    B ----- nucleus
    Select (A or B): 
---------------------------------------------------------------------

Next you select the compartment that this species will reside in

3
---------------------------------------------------------------------
### Units ###
Ensure that if you select option B, it actually exists in the model (i.e. 
you set it as one of the elements to import in the .conf file. Software 
support to check this coming real soon, but at the moment please try and 
be careful!)
  A ----- mole
  B ----- molar
---------------------------------------------------------------------

Next, the unit the species is to be described in. From here we're offered
other options too. If both species have the same value for an option we
aren't't given the choice to chose one or the other (as they're identical).

Finally, once all the options have been selected, we're presented with
the following;

---------------------------------------------------------------------
### Is this species ###
 A ----- A totally new species?
 B ----- Simply an improvement to an existing one which was already in modelA?

 Select (A or B): 
---------------------------------------------------------------------

If you select A, then SpecA will remain as is, and you'll create a new species
with the same name (SpecA) but with a different ID (which you are the prompted
to enter). This is arguably most relevant (for species) where you're importing 
a species which exists in a new compartment, but has the same units as an
existing species.

If you select B, then these updates affect SpecA. 

After this, we're greeted with the final screen;

---------------------------------------------------------------------
### Change references? ###
Would you like references to SpecB_ID, the ID of the element
just integrated into SpecA_ID to be replaced by
the newly updated/created species? (SpecA_ID)

 Please select Y/N: 
---------------------------------------------------------------------

As described, if you select yes, this adds the pairing 
[SpecA_ID, SpecB_ID] to the replacement list, as if it were defined
in the .conf file.


_____________________________________________________________________

4. Code documentation
_____________________________________________________________________
To access the code documentation use any browser to open index.html, 
found in the docs folder. This provides an indepth overview of the code.

The source code itself is also heavily commented.




