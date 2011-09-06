// Copyright Alex Holehouse 2011
// Distributed under the terms of the GNU general public license - see COPYING.txt for more details

#ifndef SBML_INTEGRATE_H
#define SBML_INTEGRATE_H

#include "sbml_confInput.h"
#include "sbml_ui_general.h"
#include "sbml_cleanup.h"
#include "sbml_integrate_import.h"
#include "sbml_integrate_replace.h"
#include "sbml_integrate_integrate.h"
#include "sbml_augment.h"
#include <sbml/SBMLTypes.h>
#include <iostream>
#include <fstream>
/*!
  \brief Parent coordinator class, which provides the UI and structure to the IRI integration process

  From the SBML_integrate class we call the import functions from the SBML_integrate_import class, replacement functions from the SBML_integrate_replace and integration functions friom SBML_integrate_integrate. 
*/

class SBML_integrate : public SBML_UI_general {
  
 public:      
  
  /*!
    \brief Class constructor

    \b Preconditions: All input should be valid. Models should be L2V1, and should not require function definition, constraint, inital assignment or event integration

    \b Postconditions: Creates an integration model, runs initial import and replacement, and then leads to an interactive environment where users can integrate any elements, explore the models or write the new integration model to disk
  */
  SBML_integrate(const Model* input_A, const Model* input_B, const char* input_A_filename, const char* input_B_filename);

  /*! \brief Run integration operations

    Runs import, replacement and integrate functions in that order */
  void integration();
  
  /*!
    \brief Driver function for the interactive integration process. 

    Takes the decisions made by the (seperate) user interface function and acts on them appropriately
    
  */  
  void integrate_models();
  // void test(Model* model);
  
 private:
  
  // -------------------------------------------------------------------------------------------
  /*! 
    Initializer which gives the user the option to select which of the two files they're importing into the constructor whill be the base model, and which will be the import model. The integration model is based on the base model.

    \b Preconditions: This must only be called from the constructor, which is why we have an init_called variable. fileA and fileB are the filenames as taken by the SBML_integrate constructor, and mean the user only needs to know the filename to select which model they want to be the base and which they want to be the import.

    \b Postconditions: Depending on the user selection, it returns a 1 if fileA is to be modelA, or a 2 if fileB is to be modeA. The method can \a only return a 1 or a 2

    !*/
  double init(const char* fileA, const char* fileB);
  
  // #############################################################################################
  // Helper functions for the integrate model UI 

  /*!
    UI method which gives the user a selection of integration options. These are as follows

    !*/  /*! 
    \brief UI function for selection.

    Provides the user with the following selection;
    
    Import model is: \n
    --> Model ID []\n\n

    Base model is: \n
    --> Model ID [ ]\n

    [1] ------------ Integrate Function Definitions (0)\n
    [2] ------------ Integrate Unit Definitions (0)    \n
    [3] ------------ Integrate Compartments (0)        \n
    [4] ------------ Integrate Species (0)             \n
    [5] ------------ Integrate Parameters (0)          \n
    [6] ------------ Integrate Initial Assignments (0) \n
    [7] ------------ Integrate Rules (0)               \n
    [8] ------------ Integrate Constraints (0)         \n
    [9] ------------ Integrate Reactions (0)           \n
    [10] ----------- Integrate Events (0)              \n
    [11] ----------- Explore models\n
    [12] ----------- Explore replacement, import and integration parameters \n
    [13] ----------- Write integrated model\n
    [14] ----------- Re-run replacement\n
    [15] ----------- Return to main menu \n
    Please select an option: \n

  */
  void integrate_models_display_options();  
  
  /*!\brief Interactive display of model elements */
  void integrate_models_explore_models(bool quick);  
 
  /*!\brief Display integration parameters    */
  void integrate_models_explore_parameters();
  
  // #############################################################################################
  //Three stages of model integration are done by the three parent functions below
  // #############################################################################################
  

  // based on the import_lists extracted and presented by inputConf, we import the chosen
  // elements from const model_B into our integrated model, model_A  
  /*!
    \brief Run import operation
    
    Using an SBML_integrate_import object run all import operations for the models
  */
  void import_elements();

  /*!
    \brief Run replacement operation
    
    Using an SBML_integrate_replace object run all replacement operations for the models
  */
  void replace_elements();
  
  
  // #############################################################################################
  
  // model_A is the larger model, which we integrate model_B into section by section
  
  /// integration model
  Model* model_new;

  /// import model
  Model* model_B;
  
  /// base model
  const Model* model_A;

  /// original import model
  const Model* model_B_original;
  
  /// base model filename
  string model_A_filename;

  /// import model filename
  string model_B_filename;

  /// Stops the init() method being called more than once. Set to false be default.
  static bool init_called;

  // framework objects

  /// display framework object
  SBML_display display_framework;

  /// search framework object
  SBML_search search_framework;

  /// cleanup framework
  SBML_cleanup* cleanup_framework;
  
  // input_file object (parses a .conf file)
  SBML_confInput input_file;
  
  /// listpair object for function definition replacement lists
  SBML_listpair_container<ListOfFunctionDefinitions> functionDefinitions_rep_container;
  /// listpair object for unit replacement lists
  SBML_listpair_container<ListOfUnitDefinitions> unitDefinitions_rep_container;
  /// listpair object for compartment replacement lists
  SBML_listpair_container<ListOfCompartments> compartments_rep_container;
  /// listpair object for species replacement lists
  SBML_listpair_container<ListOfSpecies> species_rep_container;
  /// listpair object for parameter replacement lists
  SBML_listpair_container<ListOfParameters> parameters_rep_container;
  /// listpair object for initial assignment  replacement lists
  SBML_listpair_container<ListOfInitialAssignments> initialAssignments_rep_container;
  /// listpair object for rules  replacement lists
  SBML_listpair_container<ListOfRules> rules_rep_container;
  /// listpair object for constraints  replacement lists
  SBML_listpair_container<ListOfConstraints> constraints_rep_container;
  /// listpair object for reactions  replacement lists
  SBML_listpair_container<ListOfReactions> reactions_rep_container;
  /// listpair object for event  replacement lists
  SBML_listpair_container<ListOfEvents> events_rep_container;

  /// array showing if integration has been completed for each element type (treat as bitmap)
  int integration_done_array[10];
  

};

#endif
