#include "sbml_cleanup.h"

#include <string>
#include <fstream>
#include <sbml/SBMLTypes.h>
#include <iostream>
#include <stdlib.h>

using namespace std;

// Constructor which takes an SBML document
//-----------------------------------------------------------------------------------
SBML_cleanup::SBML_cleanup(SBMLDocument* input_doc){
  
  SBML_cleanup(input_doc->getModel(), true);
}

// Constructor which takes an SBML model
//-----------------------------------------------------------------------------------
SBML_cleanup::SBML_cleanup(Model* input_model){
  SBML_cleanup(input_model, true);
}

// Constructor which takes an SBML model
//-----------------------------------------------------------------------------------
SBML_cleanup::SBML_cleanup(Model* input_model, bool copy){
  
  if (copy)
    clean_model = input_model->clone();
    
  else 
    clean_model = input_model;
    
  
}

// Identify unused units, remove them, and select and remove duplicate units
//-----------------------------------------------------------------------------------
void SBML_cleanup::consolidate_units(){
  
  // variable declaration
  int inputAi, inputBi;
  ListOfUnitDefinitions* unused_units;
  UnitDefinition *unit_defA, *unit_defB;
  int number_unused = 0;

  // declare and initialize display frameworks and search frameworks with the clean_model
  SBML_display* display_new = new SBML_display;
  SBML_search* search_framework = new SBML_search;

  
  // get a list of unused units - number unused is passed by reference, model is the 
  // original model, retunrs a list of units not used in model
  unused_units = search_framework->unused_units_lookup(number_unused, clean_model);
  
  // ALPHA debugging output
  cout << endl << endl << "------DEBUG: unused_units:=" << number_unused << endl;
  
  // if there are no unused units carry on
  if (number_unused == 0){
    cout << "All units used";
  }
  
  // remove all unused units
  else
    remove_units(unused_units, number_unused);

  // Now we consolidate units
  //  !!  To do - safeguard against non numerical input - probably using methods 
  //  !!  defined in SBML_formatter
  while (true){
    
    // reset number_unused on each cycle through the while loop - otherwise it just builds up!
    number_unused = 0;
    
    // determine the number of unused units
    unused_units = search_framework->unused_units_lookup(number_unused, clean_model);
    if (number_unused !=0)
      remove_units(unused_units, number_unused);
    
    cout << "there are " << number_unused << " unused units" << endl;
    
    display_new->show_unitDefinitions(clean_model);
    
    // if you have 0 or 1 units left, escape this loop or you get a segfault
    if (clean_model->getNumUnitDefinitions() == 0 || clean_model->getNumUnitDefinitions() == 1){
      cout << "Only " << clean_model->getNumUnitDefinitions() << " units defined" << endl;
      break;
    }
      
    // We use the pathway_viewer's unit numbering for clarity
    cout << "Select a unit (by number) which is a duplicate of another, if no more duplicates enter 0" << endl;
    
    cin >> inputAi;
    cin.ignore();
    if (inputAi == 0)
      break;
    
    cout << "Select a the unit (by number) which you wish to replace " << inputAi << " with throughout the model " << endl;
    
    cin >> inputBi;
    cin.ignore();
    if (inputBi == 0)
      break;

    
    unit_defA = clean_model->getUnitDefinition(inputAi-1);
    unit_defB = clean_model->getUnitDefinition(inputBi-1);
    
    // this locates unitA in clean model, and replaces each entry with unitB
    locate_and_replace(clean_model, unit_defA, unit_defB);
  }
  
  bool out = write_to_file(clean_model, "new_file.xml");
  if (!out)
    log_stream << "ERROR: Problem writing to file at " << get_time() << " on " << get_date() << endl;
}


// functions that removes the "number" of units listed in toberemoved from clean_model, and 
// frees up the memory
//-----------------------------------------------------------------------------------
void SBML_cleanup::remove_units(ListOfUnitDefinitions* toberemoved, int number){
  UnitDefinition* to_delete;
  
  for (int i = 0 ; i < number ; i++){
    cout << "Deleting " << toberemoved->get(i)->getId() << " from clean model" << endl;
    to_delete = clean_model->removeUnitDefinition((toberemoved->get(i))->getId());
    delete to_delete;
  }

}

// #############################################################################################
// #                                       REPLACE BLOCK                                       #
// #############################################################################################
//
// SBML_cleanup implementation of the replace_* functions, called by SBML_search based function 
// an SBML_cleanup object is used (through dynamic binding of the virtual replace_* function
//
// #############################################################################################


// #############################################################################################
// REPLACE_NODE - Function that replaces the name of the given node with the replacement string
//-----------------------------------------------------------------------------------
bool SBML_cleanup::replace_node(ASTNode* node, string replacement){
  
  log_stream << "Replacing node name " << node->getName() << " with " << replacement << endl;
  node->setName(replacement.c_str());
  
  // always return false
  return false;
}


// #############################################################################################
// REPLACE_UNIT - Function that replaces reference to inputA in clean with the a reference to 
// inputB based on C and i to define what is being replaced
//-----------------------------------------------------------------------------------
bool SBML_cleanup::replace_unit(UnitDefinition* inputA, UnitDefinition* inputB, char C, int i){
 
  switch (C){
    
    // For a compartment unit
  case 'M':{
    log_stream << "Model has substanceUnits " << clean_model->getSubstanceUnits()
	 << " which we are replacing with " << inputB->getId() << endl;
    clean_model->setSubstanceUnits(inputB->getId());
  }
    break;
    
    // For timeUnits
  case 'T':{
    log_stream << "Model has timeUnits " << clean_model->getTimeUnits()
    << " which we are replacing with " << inputB->getId() << endl;
    clean_model->setTimeUnits(inputB->getId());
  }
    break; 
    
    // for volumeUnits
  case 'V':{
    log_stream << "Model has volumeUnits " << clean_model->getVolumeUnits()
    << " which we are replacing with " << inputB->getId() << endl;
    clean_model->setVolumeUnits(inputB->getId());
  }
    break;
    
    
    //for areaUnits
  case 'A':{
    log_stream << "Model has areaUnits " << clean_model->getAreaUnits()
    << " which we are replacing with " << inputB->getId() << endl;
    clean_model->setAreaUnits(inputB->getId());
  }
    break; 

    
    // for lengthUnits
  case 'L':{
    log_stream << "Model has lengthUnits " << clean_model->getLengthUnits()
    << " which we are replacing with " << inputB->getId() << endl;
    clean_model->setLengthUnits(inputB->getId());
  }
    break;
    
    // for extent units
  case 'E':{
    log_stream << "Model has extentUnits " << clean_model->getExtentUnits()
    << " which we are replacing with " << inputB->getId() << endl;
    clean_model->setExtentUnits(inputB->getId());
  }
    break; 

    
    // for compartment units
  case 'C':{
    Compartment* compartment = clean_model->getCompartment(i);
    log_stream << "Compartment " << compartment->getName() << " has units " << inputA->getId()
	 << " which we are replacing with " << inputB->getId() << endl;
    compartment->setUnits(inputB->getId());}
    break;
    
    
    // For a species unit
  case 'S':{
    Species* species = clean_model->getSpecies(i);
    log_stream << "Species " << species->getName() << " has units " << inputA->getId()
	 << " which we are replacing with " << inputB->getId() << endl;
    species->setUnits(inputB->getId());}
    break;
    
    
    // For a parameter unit
  case 'P':{
    Parameter* parameter = clean_model->getParameter(i);
    log_stream << "Parameter " << parameter->getName() << " has units " << inputA->getId()
	 << " which we are replacing with " << inputB->getId() << endl;
    parameter->setUnits(inputB->getId());}
    break;
      
    
    // For a rule unit
  case 'R':{
    Rule* rule = clean_model->getRule(i);
    log_stream << "Rule " << rule->getName() << " has units " << inputA->getId()
	 << " which we are replacing with " << inputB->getId() << endl;
    rule->setUnits(inputB->getId());}
    break;
      
    
    // For a reaction unit
  case 'X':{
    Reaction* rxn = clean_model->getReaction(i);
    KineticLaw* klaw = rxn->getKineticLaw();
      
    int num_local_params = klaw->getNumLocalParameters();
    
    for (int j = 0 ; j < num_local_params ; j++){
      Parameter* local_param = klaw->getParameter(j);
	
      if (local_param->getUnits() == inputA->getId()){
	local_param->setUnits(inputB->getId());
      }
    }
      
  }
    break;
    
  default:
    
    cerr << "FATAL ERROR - undetermined case statement (line 210, sbml_cleanup.cpp). This should never happen - Exiting..." << endl;
    exit(1);

  }    
  
  return false;
}

// #############################################################################################
// REPLACE_COMPARTMENT - Function that replaces reference to inputA in clean_model with the a reference to inputB
// based on C and i to define what is being replaced
bool SBML_cleanup::replace_compartment(Compartment* inputA, Compartment* inputB, char C, int i){
  
  switch (C){
    
    // For a species compartment 
  case 'S':{
    Species* species = clean_model->getSpecies(i);   
    log_stream << "Replacing compartent " << inputA->getId() << " in species  with " 
	       << inputB->getId() << endl;
    species->setCompartment(inputB->getId());}
    break;
    
    // For a parameter compartment 
  case 'I':{
    InitialAssignment* initAs = clean_model->getInitialAssignment(i);    
    log_stream << "Replacing compartent " << inputA->getId() << " in initial assignment  with " 
	       << inputB->getId() << endl;
    initAs->setSymbol(inputB->getId());}
    break;
    
    // For a reaction compartment
  case 'R':{
    Rule* rule = clean_model->getRule(i); 
    log_stream << "Replacing compartent " << inputA->getId() << " in rule  with " 
	       << inputB->getId() << endl;
    rule->setVariable(inputB->getId());}
    break;
      
    // For a reaction compartment
  case 'X':{
    Reaction* rxn = clean_model->getReaction(i);	
    log_stream << "Replacing compartent " << inputA->getId() << " in reaction with " 
	       << inputB->getId() << endl;
    rxn->setCompartment(inputB->getId());}
    break;
      
    // For a event compartment
  case 'E':{

    Event* event = clean_model->getEvent(i);
    int num_eventAs = event->getNumEventAssignments();
    EventAssignment* eventAs;
    
    for (int j = 0 ; j < num_eventAs ; j++){

      eventAs = event->getEventAssignment(j);
      
      if (eventAs->getVariable() == inputA->getId())
	log_stream << "Replacing compartent " << inputA->getId() << " in Event with " 
		   << inputB->getId() << endl;
	eventAs->setVariable(inputB->getId());
    }
  }
    break;
    
  default:
    cerr << "FATAL ERROR - undetermined case statement (line 272, sbml_cleanup.cpp). This should never happen - Exiting..." << endl;
    exit(1);
    
  }    
  return false;
}



// #############################################################################################
// REPLACE_SPECIES - Function that replaces reference to inputA in clean_model with the a reference to inputB
bool SBML_cleanup::replace_species(Species* inputA, Species* inputB, char C, int i){ 

  int num_species;
  SpeciesReference* SR;
  
  switch (C){
    
    // For a species compartment 
  case 'I':{
    InitialAssignment* initAs = clean_model->getInitialAssignment(i);    
    log_stream << "Replacing species " << inputA->getId() << " in initial assignment  with " 
	       << inputB->getId() << endl;
    initAs->setSymbol(inputB->getId());
  }
    break;
    
  case 'R':{
    Rule* rule = clean_model->getRule(i); 
    log_stream << "Replacing species " << inputA->getId() << " in rule with " 
	       << inputB->getId() << endl;
    rule->setVariable(inputB->getId());
  }
    break;
    
  case 'r':{
    Reaction* rxn = clean_model->getReaction(i);	
    log_stream << "Replacing species " << inputA->getId() << " in reaction " << rxn->getId() 
      	       << " reactant list with " << inputB->getId() << endl;
   
    num_species = rxn->getNumReactants();
    for (int j = 0 ; j < num_species ; j++){
      SR = rxn->getReactant(j);
      if (SR->getSpecies() == inputA->getId())
	SR->setSpecies(inputB->getId());
    }
  }
    break;
    
  case 'p':{
    Reaction* rxn = clean_model->getReaction(i);	
    log_stream << "Replacing species " << inputA->getId() << " in reaction " << rxn->getId() 
	       << " product list with "  << inputB->getId() << endl;
    
    num_species = rxn->getNumProducts();
    for (int j = 0 ; j < num_species ; j++){
      SR = rxn->getProduct(j);
      if (SR->getSpecies() == inputA->getId())
	SR->setSpecies(inputB->getId());
    }
  }
    break;

  case 'm':{
    ModifierSpeciesReference* MSR;
    Reaction* rxn = clean_model->getReaction(i);	
    log_stream << "Replacing species " << inputA->getId() << " in reaction " << rxn->getId() 
	       << " modifier list with "  << inputB->getId() << endl;
    
    num_species = rxn->getNumModifiers();
    for (int j = 0 ; j < num_species ; j++){
      MSR = rxn->getModifier(j);
      if (MSR->getSpecies() == inputA->getId())
	MSR->setSpecies(inputB->getId());
    }
  }
    break;
    

    //
  case 'E':{

    Event* event = clean_model->getEvent(i);
    int num_eventAs = event->getNumEventAssignments();
    EventAssignment* eventAs;
    
    for (int j = 0 ; j < num_eventAs ; j++){

      eventAs = event->getEventAssignment(j);
      
      if (eventAs->getVariable() == inputA->getId())
	log_stream << "Replacing species " << inputA->getId() << " in Event with " 
		   << inputB->getId() << endl;
      eventAs->setVariable(inputB->getId());
    }
  }
    break;
    
  default:
    cerr << "FATAL ERROR - undetermined case statement (line 428, sbml_cleanup.cpp). This should never happen - Exiting..." << endl;
    exit(1);


  }
  return false;
  
}

bool SBML_cleanup::replace_parameters(Parameter* inputA, Parameter* inputB, char C, int i){
  switch (C){
    
    // For a species' conversion factor parameter
  case 'S':{
    Species* species = clean_model->getSpecies(i);    
    log_stream << "Replacing species conversion factor " << inputA->getId() << " with " 
	       << inputB->getId() << endl;
    species->setConversionFactor(inputB->getId());
  }
    break;
    
    // For a initialAssignment symbol values
  case 'I':{
    InitialAssignment* initAs = clean_model->getInitialAssignment(i);    
    log_stream << "Replacing parameter " << inputA->getId() << " in initial assignment  with " 
	       << inputB->getId() << endl;
    initAs->setSymbol(inputB->getId());
  }
    break;  
  
    // for rule variable value
  case 'R':{
    Rule* rule = clean_model->getRule(i); 
    log_stream << "Replacing species " << inputA->getId() << " in rule with " 
	       << inputB->getId() << endl;
    rule->setVariable(inputB->getId());
  }
    break;
    
    // for eventAssignmnt variable value
  case 'E':{

    Event* event = clean_model->getEvent(i);
    int num_eventAs = event->getNumEventAssignments();
    EventAssignment* eventAs;
    
    for (int j = 0 ; j < num_eventAs ; j++){

      eventAs = event->getEventAssignment(j);
      
      if (eventAs->getVariable() == inputA->getId())
	log_stream << "Replacing species " << inputA->getId() << " in Event with " 
		   << inputB->getId() << endl;
      eventAs->setVariable(inputB->getId());
    }
  }
    break;
    
  default:
    cerr << "FATAL ERROR - undetermined case statement (line 484, sbml_cleanup.cpp). This should never happen - Exiting..." << endl;
    exit(1);
  }
  
  return false;
  
}
      

// #############################################################################################
// #                                  REPLACE BLOCK                                            #
// #############################################################################################
// This is just a nice interface, packaging up the complexitys of the behind-the-scenes system

bool SBML_cleanup::replace(UnitDefinition* inputA, UnitDefinition* inputB){
  log_stream << "-#-#-#-#-#-# Replacing Unit Definitions -#-#-#-#-#-#" << endl;
  return(locate_and_replace(clean_model, inputA, inputB));
}

bool SBML_cleanup::replace(FunctionDefinition* inputA, FunctionDefinition* inputB){
  log_stream << "-#-#-#-#-#-# Replacing Function Definitions -#-#-#-#-#-#" << endl;
  return(locate_and_replace(clean_model, inputA, inputB));
}

bool SBML_cleanup::replace(Compartment* inputA, Compartment* inputB){
  log_stream << "-#-#-#-#-#-# Replacing Compartments -#-#-#-#-#-#" << endl;
  return(locate_and_replace(clean_model, inputA, inputB));
}

bool SBML_cleanup::replace(Species* inputA, Species* inputB){
  log_stream << "-#-#-#-#-#-# Replacing Species -#-#-#-#-#-#" << endl;
  return(locate_and_replace(clean_model, inputA, inputB));
}

bool SBML_cleanup::replace(Parameter* inputA, Parameter* inputB){
  log_stream << "-#-#-#-#-#-# Replacing Parameter -#-#-#-#-#-#" << endl;
  return(locate_and_replace(clean_model, inputA, inputB));
}

bool SBML_cleanup::replace(InitialAssignment* inputA, InitialAssignment* inputB){
  log_stream << "-#-#-#-#-#-# Replacing Initial Assignment -#-#-#-#-#-#" << endl;
  return(locate_and_replace(clean_model, inputA, inputB));
}

bool SBML_cleanup::replace(Rule* inputA, Rule* inputB){
  log_stream << "-#-#-#-#-#-# Replacing Rule -#-#-#-#-#-#" << endl;
  return(locate_and_replace(clean_model, inputA, inputB));
}

bool SBML_cleanup::replace(Constraint* inputA, Constraint* inputB){
  log_stream << "-#-#-#-#-#-# Replacing Constraint -#-#-#-#-#-#" << endl;
  return(locate_and_replace(clean_model, inputA, inputB));
}

bool SBML_cleanup::replace(Reaction* inputA, Reaction* inputB){
  log_stream << "-#-#-#-#-#-# Replacing Reaction -#-#-#-#-#-#" << endl;
  return(locate_and_replace(clean_model, inputA, inputB));
}

bool SBML_cleanup::replace(Event* inputA, Event* inputB){
  log_stream << "-#-#-#-#-#-# Replacing Event -#-#-#-#-#-#" << endl;
  return(locate_and_replace(clean_model, inputA, inputB));
}



// get the a pointer to the clean model stored in this SBML_cleanup object
//-----------------------------------------------------------------------------------
Model* SBML_cleanup::get_clean_model(){
  return clean_model;
}
