// Copyright Alex Holehouse 2011
// Distributed under the terms of the GNU general public license - see COPYING.txt for more details
#include "sbml_augment.h"
#include "sbml_formatter.h"

#include <sbml/SBMLTypes.h>
#include <string>
#include <iostream>

using namespace std;

SBML_augment::SBML_augment(Model* _model) : cleanup(_model, false)
{ model = _model; }

  

void SBML_augment::complete_model_id_rename_with_append(string to_append){

  int num = model->getNumFunctionDefinitions();

  SBML_cleanup cleanup(model, false);
  
  for (int i = 0 ; i < num ; i++){
    replace_reference_in_model(model->getFunctionDefinition(i), to_append);
    append_to_ID(model->getFunctionDefinition(i), to_append);
  }
  
  log_stream << "Completed augmentation of " << num << " function definitions with " << to_append << endl;
  
  num = model->getNumUnitDefinitions();

  for (int i = 0 ; i < num ; i++){
    replace_reference_in_model(model->getUnitDefinition(i), to_append);
    append_to_ID(model->getUnitDefinition(i), to_append);
  }
  
  log_stream << "Completed augmentation of " << num << " unit definitions with " << to_append << endl;
  
  num = model->getNumCompartments();
  for (int i = 0 ; i < num ; i++){
    replace_reference_in_model(model->getCompartment(i), to_append);
    append_to_ID(model->getCompartment(i), to_append);
  }

  log_stream << "Completed augmentation of " << num << " compartments with " << to_append << endl;
  
  num = model->getNumSpecies();
  for (int i = 0 ; i < num ; i++){
    replace_reference_in_model(model->getSpecies(i), to_append);
    append_to_ID(model->getSpecies(i), to_append);
  }

  log_stream << "Completed augmentation of " << num << " species with " << to_append << endl;
  
  num = model->getNumParameters();
  for (int i = 0 ; i < num ; i++){
    replace_reference_in_model(model->getParameter(i), to_append);
    append_to_ID(model->getParameter(i), to_append);
  }
  
  log_stream << "Completed augmentation of " << num << " parameters with " << to_append << endl;

  num = model->getNumInitialAssignments();

  for (int i = 0 ; i < num ; i++){
    replace_reference_in_model(model->getInitialAssignment(i), to_append);
    append_to_ID(model->getInitialAssignment(i), to_append);
  }
  
  log_stream << "Completed augmentation of " << num << "initial Assignments with " << to_append << endl;

  // rules would be here, but rules have no idea, so cannot be referenced
  

  // constraints would be here, but constrants have no ID, so cannot be referenced
  
  
  
  num = model->getNumReactions();
  for (int i = 0 ; i < num ; i++){
    replace_reference_in_model(model->getReaction(i), to_append);
    append_to_ID(model->getReaction(i), to_append);
  }

  log_stream << "Completed augmentation of " << num << " reactions  with " << to_append << endl;
  
  num = model->getNumEvents();
  for (int i = 0 ; i < num ; i++){
    replace_reference_in_model(model->getEvent(i), to_append);
    append_to_ID(model->getEvent(i), to_append);
  }

  log_stream << "Completed augmentation of " << num << " events  with " << to_append << endl;
  
}

    
