// Copyright Alex Holehouse 2011
// Distributed under the terms of the GNU general public license - see COPYING.txt for more details

#include "sbml_integrate_import.h"
#include <sbml/SBMLTypes.h>
#include <string>
#include <iostream>

using std::cout;
using std::endl;


SBML_integrate_import::SBML_integrate_import(){
  cout << "OK..." << endl;
}


void SBML_integrate_import::import_functionDefinitions(Model* model_new, int num, ListOfFunctionDefinitions* list){

  log_stream << "functionDefinition support not yet added..." << endl; 

}

void SBML_integrate_import::import_unitDefinitions(Model* model_new, int num, ListOfUnitDefinitions* list){
  
  if (num == 0){
    log_stream << "No unitDefinition to import" << endl;
    return;
  }
  
  UnitDefinition* temp;
  
  for (int i = 0 ; i < num ; i++){
    temp = list->get(i);
    log_stream << "[" << operation << "] - Importing unitDefinition " << temp->getId() 
	       << " into new model" << endl;
    
    // adds _fromB to the end of temp's ID variable
    
    model_new->addUnitDefinition(temp);
    operation++;
  }

}

void SBML_integrate_import::import_compartments(Model* model_new, int num, ListOfCompartments* list){
  
  if (num == 0){
    log_stream << "No compartments to import" << endl;
    return;
  }
  
  Compartment* temp;
  
  for (int i = 0 ; i < num ; i++){
    temp = list->get(i);
    log_stream << "[" << operation << "] - Importing compartment " << temp->getId() 
	       << " into new model" << endl;
    
    model_new->addCompartment(temp);
    operation++;
  }

}


void SBML_integrate_import::import_species(Model* model_new, int num, ListOfSpecies* list){
  
  if (num == 0){
    log_stream << "No species to import" << endl;
    return;
  }
  
  Species* temp;
  
  for (int i = 0 ; i < num ; i++){
    temp = list->get(i);
    log_stream << "[" << operation << "] - Importing species " << temp->getId() 
	       << " into new model" << endl;
    
    model_new->addSpecies(temp);
    operation++;
  }
}

void SBML_integrate_import::import_parameters(Model* model_new, int num, ListOfParameters* list){
  
  if (num == 0){
    log_stream << "No parameters to import" << endl;
  }
  
  Parameter* temp;
  
  for (int i = 0 ; i < num ; i++){
    temp = list->get(i);
    log_stream << "[" << operation << "] - Importing parameter " << temp->getId() 
	       << " into new model" << endl;
    
    model_new->addParameter(temp);
    operation++;
  }
}

void SBML_integrate_import::import_initialAssignments(Model* model_new, int num, ListOfInitialAssignments* list){
  
  //if (num == 0){
  //  log_stream << "No initialAssignments to import" << endl;
  //  return;
  // }
   // InitialAssignment* temp;
  
  // for (int i = 0 ; i < num ; i++){
  //  temp = list->get(i);
  //  log_stream << "[" << operation << "] - Importing initialAssignment " 
  //             << temp->getId() << " into new model" << endl;

  // append_to_ID<InitialAssignment>(temp, "_fromB");
  //  model_new->addInitialAssignment(temp);
  //  operation++;
  //  }
  
  log_stream << "initialAssignment support not yet added..." << endl;
}

void SBML_integrate_import::import_rules(Model* model_new, int num, ListOfRules* list){
  
  if (num == 0){
    log_stream << "No rules to import" << endl;
    return;
  }
 
  Rule* temp;
  
  for (int i = 0 ; i < num ; i++){
    temp = list->get(i);
    log_stream << "[" << operation << "] - Importing rule " << temp->getId() 
	       << " into new model" << endl;
    
    model_new->addRule(temp);
    operation++;
  }
}

void SBML_integrate_import::import_constraints(Model* model_new, int num, ListOfConstraints* list){
  log_stream << "constraint support not yet added..." << endl;
}

void SBML_integrate_import::import_reactions(Model* model_new, int num, ListOfReactions* list){
  
  if (num == 0){
    log_stream << "No reactions to import" << endl;
    return;
  }
 
  Reaction* temp;
  
  for (int i = 0 ; i < num ; i++){
    temp = list->get(i);
    log_stream << "[" << operation << "] - Importing reaction " << temp->getId() 
	       << " into new model" << endl;
    
    model_new->addReaction(temp);
    operation++;
  }
}


void SBML_integrate_import::import_events(Model* model_new, int num, ListOfEvents* list){
  log_stream << "event import support not yet added..." << endl;
}
