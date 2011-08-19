#include "sbml_augment.h"
#include "sbml_formatter.h"

#include <sbml/SBMLTypes.h>
#include <string>
#include <iostream>

using namespace std;

SBML_augment::SBML_augment(Model* _model) : cleanup(_model, false)
{

  model = _model;
  cout << "right" << endl;
}

  

void SBML_augment::complete_model_id_rename_with_append(string to_append){

  int num = model->getNumFunctionDefinitions();

  SBML_cleanup cleanup(model, false);

  cout << "Renaming functionDefinitions, num = " << num << endl;
  
  for (int i = 0 ; i < num ; i++){
    replace_reference_in_model(model->getFunctionDefinition(i), to_append);
    append_to_ID(model->getFunctionDefinition(i), to_append);
  }
  
  num = model->getNumUnitDefinitions();
  cout << "Renaming unitDef, num = " << num << endl;
  for (int i = 0 ; i < num ; i++){
    replace_reference_in_model(model->getUnitDefinition(i), to_append);
    append_to_ID(model->getUnitDefinition(i), to_append);
  }
  
  num = model->getNumCompartments();
 cout << "Renaming comps, num = " << num << endl; 
  for (int i = 0 ; i < num ; i++){
    replace_reference_in_model(model->getCompartment(i), to_append);
    append_to_ID(model->getCompartment(i), to_append);
  }

  num = model->getNumSpecies();
cout << "Renaming species, num = " << num << endl;
  for (int i = 0 ; i < num ; i++){
    replace_reference_in_model(model->getSpecies(i), to_append);
    append_to_ID(model->getSpecies(i), to_append);
  }

  num = model->getNumParameters();
cout << "Renaming PARAMS, num = " << num << endl;
  for (int i = 0 ; i < num ; i++){
    replace_reference_in_model(model->getParameter(i), to_append);
    append_to_ID(model->getParameter(i), to_append);
  }

  num = model->getNumInitialAssignments();

  for (int i = 0 ; i < num ; i++){
    replace_reference_in_model(model->getInitialAssignment(i), to_append);
    append_to_ID(model->getInitialAssignment(i), to_append);
  }


  // rules would be here, but constraints have no idea, so cannot be referenced
  

  // constraints would be here, but constrants have no ID, so cannot be referenced
  
  num = model->getNumReactions();
  for (int i = 0 ; i < num ; i++){
    replace_reference_in_model(model->getReaction(i), to_append);
    append_to_ID(model->getReaction(i), to_append);
  }
  
  num = model->getNumEvents();
  for (int i = 0 ; i < num ; i++){
    replace_reference_in_model(model->getEvent(i), to_append);
    append_to_ID(model->getEvent(i), to_append);
  }
  
}

    
