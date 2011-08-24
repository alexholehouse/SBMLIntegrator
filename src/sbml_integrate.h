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

class SBML_integrate : public SBML_UI_general {
  
 public:
  SBML_integrate(const Model* input_A, const Model* input_B, const char* input_A_filename, const char* input_B_filename);

  void integration();
  
  void integrate_models();
  bool read_config_file();
  void test(Model* model);
  
 protected:
  
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

    !*/
  void integrate_models_display_options();
  void integrate_models_explore_models(bool quick);
  void integrate_models_explore_parameters();
  
  // #############################################################################################
  //Three stages of model integration are done by the three parent functions below
  

  // based on the import_lists extracted and presented by inputConf, we import the chosen
  // elements from const model_B into our integrated model, model_A
  void import_elements();
  
  // based on the import_lists extracted and presented by inputConf, we interactivly combine any
  // elements which require integration. IDs which originated from model_B are added with corresponding
  // replacement IDs to appropriate replacement lists
  void integrate_elements();

  void replace_elements();
  
  
  // #############################################################################################
  
  // model_A is the larger model, which we integrate model_B into section by section
  
  Model* model_new;
  Model* model_B;
  
  // model_A is used as a reference model, as model new is constantly being changed
  const Model* model_A;
  const Model* model_B_original;
  
  string model_A_filename;
  string model_B_filename;

  /// Stops the init() method being called more than once. Set to false be default.
  static bool init_called;

  // framework objects
  SBML_display display_framework;
  SBML_search search_framework;
  SBML_cleanup* cleanup_framework;
  
  // input_file object (parses a .conf file)
  SBML_confInput input_file;
  
  // reference counter...
  int operation;

  void inteligent_replacement();

  SBML_listpair_container<ListOfFunctionDefinitions> functionDefinitions_rep_container;
  SBML_listpair_container<ListOfUnitDefinitions> unitDefinitions_rep_container;
  SBML_listpair_container<ListOfCompartments> compartments_rep_container;
  SBML_listpair_container<ListOfSpecies> species_rep_container;
  SBML_listpair_container<ListOfParameters> parameters_rep_container;
  SBML_listpair_container<ListOfInitialAssignments> initialAssignments_rep_container;
  SBML_listpair_container<ListOfRules> rules_rep_container;
  SBML_listpair_container<ListOfConstraints> constraints_rep_container;
  SBML_listpair_container<ListOfReactions> reactions_rep_container;
  SBML_listpair_container<ListOfEvents> events_rep_container;

  int integration_done_array[10];
  

  // Other functions (best to ignore)
  void unretarding_the_pfizer_model(Model* retarded_model);
  const ASTNode* retarded_rules(Model* model, string formula);
  
};

#endif
