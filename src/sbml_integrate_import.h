// Copyright Alex Holehouse 2011
// Distributed under the terms of the GNU general public license - see COPYING.txt for more details

#ifndef SBML_INTEGRATE_IMPORT_H
#define SBML_INTEGRATE_IMPORT_H

#include <sbml/SBMLTypes.h>
#include "sbml_integrate_helper.h"

/*!
  \brief Class to hold and carry out import functionality

  Each of the ten methods is passed the integration model, the number of elements to be imported, and a list of those elements to be imported. They then go about carrying out that importation.
*/

class SBML_integrate_import : SBML_integrate_helper {
  
 public:
  SBML_integrate_import();
  
  /// Import function definitions into the integration model
  void import_functionDefinitions(Model* model_new, int num, ListOfFunctionDefinitions* list);
  /// Import unit definitions into the integration modle
  void import_unitDefinitions(Model* model_new, int num, ListOfUnitDefinitions* list);
  /// Import compartments  into the integration model
  void import_compartments(Model* model_new, int num, ListOfCompartments* list);
  /// Import species into the integration model
  void import_species(Model* model_new, int num, ListOfSpecies* list);
  /// Import parameters into the integration model
  void import_parameters(Model* model_new, int num, ListOfParameters* list);
  /// Import initial assignments into the integration model
  void import_initialAssignments(Model* model_new, int num, ListOfInitialAssignments* list);
  /// Import rules into the integration model
  void import_rules(Model* model_new, int num, ListOfRules* list);
  /// Import constraints into the integration model
  void import_constraints(Model* model_new, int num, ListOfConstraints* list);
  /// Import reactions into the integration model
  void import_reactions(Model* model_new, int num, ListOfReactions* list);
  /// Import events  assignments into the integration model
  void import_events(Model* model_new, int num, ListOfEvents* list);
  
};

#endif
