#ifndef SBML_INTEGRATE_IMPORT_H
#define SBML_INTEGRATE_IMPORT_H

#include "sbml_formatter.h"
#include "sbml_cleanup.h"
#include <iostream>
#include <sbml/SBMLTypes.h>
#include "sbml_integrate_helper.h"

class SBML_integrate_import : SBML_integrate_helper {
  
 public:
  SBML_integrate_import();
  
  void import_functionDefinitions(Model* model_new, int num, ListOfFunctionDefinitions* list);
  void import_unitDefinitions(Model* model_new, int num, ListOfUnitDefinitions* list);
  void import_compartments(Model* model_new, int num, ListOfCompartments* list);
  void import_species(Model* model_new, int num, ListOfSpecies* list);
  void import_parameters(Model* model_new, int num, ListOfParameters* list);
  void import_initialAssignments(Model* model_new, int num, ListOfInitialAssignments* list);
  void import_rules(Model* model_new, int num, ListOfRules* list);
  void import_constraints(Model* model_new, int num, ListOfConstraints* list);
  void import_reactions(Model* model_new, int num, ListOfReactions* list);
  void import_events(Model* model_new, int num, ListOfEvents* list);
  
};

#endif
