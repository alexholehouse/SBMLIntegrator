// Copyright Alex Holehouse 2011
// Distributed under the terms of the GNU general public license - see COPYING.txt for more details

/*! \mainpage SBMLIntegrator
 
  SBMLIntegrator is a a simple to use tool for Linux which allows for the integration of two SBML models into one single model. The purpose of this functionality is to facilitate model integration to propel the investigation of crosstalk between separately defined but biologically connected pathways.

  Included here is a documentation of the software generate through Doxygen. It gives an overview of classes and functions to provide a pseudo-interactive guide to the code generated. The purpose of this is twofold.

  1) It provides a means to describe and explain the code justification for future optimisation, enhancement and development. The code is well commented throughout, so this documentation provides
  an overview to the architecture. If more detailed is required, the source code can be examined.

  2) For this dissertation, rather than describing the code in detail in the report, code implementation can be viewed here, with both code comments in the code and a code overview provided by this documentation. This gives a much more natural way to interpret the code, as well as avoiding the formatting issues and long-winded descriptions needed to "describe" code, rather than simply referring to it.
  
  
  \b How to use SBMLIntegrator: \n
1. Foreword\n
2. Installation	\n  
3. User Guide  \n
\n\n

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

However, to ensure a complete software package, this functionality 
will be added for the beta release (which has a tentative release date
of September 30th 2011).

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

SBMLIntegrator integrates two models based on a configuration file.

A configuration file defines what elements of one model (the import model)
are brought into the other model (the integration model) . SBML files are 
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
  in the import model) with references to species 7 as defined in the BASE 
  model. Similarly, references to species 2 in the import model are replaced 
  by references to species 9 in the base model

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
aren't given the choice to chose one or the other (as they're identical).

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

   
*/


#ifndef SBML_FORMATTER_H
#define SBML_FORMATTER_H


#include <iostream>
#include <fstream>
#include <sbml/SBMLTypes.h>
/** \brief Base class for all classes
   
    
   This class contains core functionality relating to SBML, type conversion, formatting and a range of other methods which may be required by multiple classes but are in no way linked to specific information. As a result, this functionality is grouped here for ease of access by other classes.
**/
class SBML_formatter {
  
 public:
  
  /// Default value used to indicate failure
  static const int c_FAIL_DOUBLEGET = -9999999;
  
  /**
     \brief Constructor function

   **/
  SBML_formatter();  

  /*! \brief Function to close the software
    
    \b Preconditions: None
    
    \b Postconditions: Closes the logstream correctly to ensure file validity
    
  */
  int SBML_EXIT();
  
  /** Returns the date in a standard format to string **/
  std::string get_date();
  /** Returns the time in a standard format to string **/
  std::string get_time();
  /** Returns the software verison in a standard format to string **/
  std::string get_version();
  
  /** Resets a c_string of size size to be empty - starts from beginning **/
  void reset_cstr(char* c_str, int size);
  
  /** Safe abort method which outouts a message to screen closes the software **/
  void autoAbort(std::string message);
  
  /** Converts a double to a string **/
  std::string dtostr(const double in);
  
  /** Converts a species to a species reference in a specific reaction, adding addToSpeciesID at the end **/
  SpeciesReference* species2SpeciesReference(const Species* species, const Reaction* rxn, std::string addToSpeciesID);
  
  /** Converts a species to a species reference in a specific reaction**/
  SpeciesReference* species2SpeciesReference(const Species* species, const Reaction* rxn);
  
  /** Converts a species to a modifier species reference in a specific reaction**/
  ModifierSpeciesReference* species2ModifierSpeciesReference(const Species* species, const Reaction* rxn);
    
  /** Writes a logfile error message - DEPRECATED DO NOT USE **/
  void logfile_add_message(int error, std::string element, std::string new_owner);
  
  /*! \brief Writes an SBML model to file as file name
    
    \b Preconditions: filename should include the .xml file extension. You should have write permission to the current working directory
    
    \b Postconditions: Writes a file in XML format with the SBML modell
    
  */
  bool write_to_file(Model* input, std::string filename);

  
  /** Checks if a pointer is set to NULL, and if so aborts with an error message rather than segfaulting **/
  template <class T> void nullchecker(T* pointer, std::string class_function){
    if (pointer == NULL){
      std::string message = "Null pointer exception in function ";
      autoAbort(message.append(class_function));
    }
  }
    

  /** 
      \brief Appends to_append onto any SBML element which can 
    
      \b Preconditions: Element must be able to have the getID() and setID() methods acted upon them
    
      \b Postconditions: Element is renamed
      
  **/
  template <class T> void append_to_ID(T* element, std::string to_append){
    
    // for diagnostics only (although worth keeping)
    log_stream << "Template function append_to_ID. If this fails likely the type passed to append_to_ID does not have an ID memnber variable!" << std::endl;
    
    std::string newID = element->getId();
    std::string error;
    newID.append(to_append);
    if (element->setId(newID) !=0)
      autoAbort(	
		(
		 (
		  (
		   (
		    (error
		     .append("Error, setting Id "))
		    .append(newID))
		   .append(" in element "))
		  .append(element->getId()))
		 .append(" in element "))
		.append(element->getId()));

    else 
      return;    
  }
  
  
 protected:
  /// Filestream which outputs logging information
  static std::ofstream log_stream;

  /// Ensures the logfile is essentially a singleton logfile
  static bool logfile_set;

  /// Used to generate model-wide unique IDs
  static int unique;
  
  
};

#endif
