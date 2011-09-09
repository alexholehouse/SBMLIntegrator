// Copyright Alex Holehouse 2011
// Distributed under the terms of the GNU general public license - see COPYING.txt for more details

#include "sbml_search.h"
#include <sbml/SBMLTypes.h>
#include <iostream>
#include <stdlib.h>

using namespace std;


// Function which takes in a rule ID as a string, and searches through the  model argument
// to return a pointer to that rule, if the rule is present, or a pointer to NULL if it is
// not.
//-----------------------------------------------------------------------------------
const Rule* SBML_search::find_rule(const Model* model, string search_term){
  
  int num_rules;
  
  // set default to null
  const Rule* rule = NULL;
  
  // determine how many rules are in the model
  num_rules = model->getNumRules();
  
  for (int i = 0 ; i < num_rules ; i++){

    rule = model->getRule(i);
    if (search_term == rule->getVariable())
      return rule;
  }
  
  // if we get here rule is returned as NULL as we've not found the rule in question
  return rule;
  }


// Takes a unitID, and returns that unit's definition as a string
string SBML_search::units_lookup(const Model* model, string units_id){
  
  const UnitDefinition* unit_def;
  int num_units = model->getNumUnitDefinitions();
  
  for (int i = 0 ; i < num_units ; i++){
    
    unit_def = model->getUnitDefinition(i);
    if (unit_def->getId() == units_id)
      return (describe_units(unit_def->getListOfUnits(), unit_def->getNumUnits()));
  }
  
  return ("Undefined Units");

}



// Describes the units in a list_of_units, and return it as a string
//-----------------------------------------------------------------------------------
string SBML_search::describe_units(const ListOfUnits* list_of_units, int number){

  bool bracket_wrap = false;
  
  string return_string;
  const Unit* unit;
  for (int i = 0 ; i < number ; i++){
    
    // Get unit from the list of units
    unit = list_of_units->get(i);

    if ( (unit->isSetMultiplier() && unit->getMultiplier() != 1) 
	 || (unit->isSetScale() && unit->getScale() != 0)){
      
      // flag means we end the unit with a bracket 
      bracket_wrap = true;
      
      // add opening bracket (for clarity)      
      return_string.append("(");
    
      // If a non-default multiplier (1) is used output, otherwise ignore for clarity
      if (unit->getMultiplier() != 1){
	return_string.append(dtostr(unit->getMultiplier()));
	return_string.append(" * ");
      }
      
      // If a non-default scale factor (0) is used output, otherwise ignore for clarity
      if (unit->getScale() != 0){
	return_string.append("10^(");
	return_string.append(dtostr(unit->getScale()));
	return_string.append(") * ");
      }
    }

    // unit name
    return_string.append(unit_kind_lookup(unit->getKind()));
    
    // if bracket_wrap flag was set
    if (bracket_wrap)
      return_string.append(")");
        
    // If a non-default exponent (1) is used output, otherwise ignore for clarity
    if (unit->getExponent() != 1){
      return_string.append("^(");
      return_string.append(dtostr(unit->getExponent()));
      return_string.append(")");

      // reset for next unit
      bracket_wrap = false;
    }
    
    // Add extra * if a multi-subunit unit definition
    if (number > 1 && i+1 != number){
      return_string.append(" * ");
      continue;
    }
  }
  
  return (return_string);
}



//-----------------------------------------------------------------------------------
// Lookup which translates the unit_kind integer into a string
string SBML_search::unit_kind_lookup(int n){
  
  // +1 because I started the enumeration on 1, not 0... my bad
  switch (n+1) 
    {
    case 1: return ("ampere");
    case 2: return ("Avogadro");
    case 3: return ("becquerel");
    case 4: return ("candela");
    case 5: return ("Celsius ");
    case 6: return ("coulomb");
    case 7: return ("dimensionless");
    case 8: return ("farad");
    case 9: return ("gram");
    case 10: return ("gray");
    case 11: return ("henry");
    case 12: return ("hertz");
    case 13: return ("item");
    case 14: return ("joule");
    case 15: return ("katal");
    case 16: return ("kelvin");
    case 17: return ("kilogram");
    case 18: return ("litre");
    case 19: return ("litre");
    case 20: return ("lumen");
    case 21: return ("lux");
    case 22: return ("metre");
    case 23: return ("metre");
    case 24: return ("mole");
    case 25: return ("newton");
    case 26: return ("ohm");
    case 27: return ("pascal");
    case 28: return ("radian");
    case 29: return ("second");
    case 30: return ("siemens");
    case 31: return ("sievert")	;	    
    case 32: return ("steradian");
    case 33: return ("tesla");
    case 34: return ("volt");
    case 35: return ("watt");
    case 36: return ("weber");
    case 37: return ("INVALID");
    default: return ("ERROR - no Unit kind seleced");
    }
}

// Function which returns a list of unit definitions not used in input_model as a list 
// with number_unused = number of entries in that list
//-----------------------------------------------------------------------------------
ListOfUnitDefinitions* SBML_search::unused_units_lookup(int &number_unused, Model* input_model){
  
  // create new list
  ListOfUnitDefinitions* notused_list = new ListOfUnitDefinitions(input_model->getLevel(), input_model->getVersion());
  
  ListOfUnitDefinitions* model_list = input_model->getListOfUnitDefinitions();
  UnitDefinition* unit_def;
  
  int number_of_units = input_model->getNumUnitDefinitions();
  
  // key for-loop which loops over each unit in our model's list of units. If unit is found used 
  // anywhere in the model, the unit is added to new_list, if not it is not.
  for (int i = 0 ; i < number_of_units ; i++){
    
    unit_def = model_list->get(i);
    
    if(!locate_and_replace(input_model, unit_def, unit_def)){
      notused_list->append(unit_def);
      number_unused++;
    }
  }
  
  return notused_list;
  
}


// #############################################################################################
// get_reaction_formula
// 
// Returns a string with the formula for the reaction in standard chemical notation
//
string SBML_search::get_reaction_formula(const Reaction* rxn){
  int stoich = 0;
  string ret_string;
  const SpeciesReference* species;
  int num_reactants = rxn->getNumReactants();
  int num_products = rxn->getNumProducts();

  for (int j = 0 ; j < num_reactants ; j++){
          
    species = rxn->getReactant(j);
    stoich = species->getStoichiometry();
    
    // if stoichiometry is not simply 1
    if (stoich != 1)
      ret_string.append(dtostr(stoich)).append(species->getSpecies());
    
    // if stoichiometry is 1
    else
      ret_string.append(species->getSpecies());

    // add "+" in the appropriate place between reactants for printout
    if (num_reactants > 0 && j+1 != num_reactants)
      ret_string.append(" + ");
  }

  if (rxn->isSetReversible())
    ret_string.append(" <---> ");
  else
    ret_string.append(" --> ");
  
  // Output products
  for (int j = 0 ; j < num_products ; j++){
    species = rxn->getProduct(j);
    stoich = species->getStoichiometry();
      
    // if stoichiometry is not simply 1
    if (stoich != 1)
      ret_string.append(dtostr(stoich)).append(species->getSpecies());
    
    // if stoichiometry is 1
    else
      ret_string.append(species->getSpecies());
    
    if (num_products > 0 && j+1 != num_products)
      ret_string.append(" + ");
  }

  return ret_string;
  
}

// #############################################################################################
// #                                     IS_PRESENT BLOCK                                      #
// #############################################################################################

bool SBML_search::is_present(Model* model, FunctionDefinition* inputA){
  return (locate_and_replace(model, inputA, inputA));
}

bool SBML_search::is_present(Model* model, UnitDefinition* inputA){
  return (locate_and_replace(model, inputA, inputA));
}

bool SBML_search::is_present(Model* model, Compartment* inputA){
  return (locate_and_replace(model, inputA, inputA));
}

bool SBML_search::is_present(Model* model, Species* inputA){
  return (locate_and_replace(model, inputA, inputA));
}

bool SBML_search::is_present(Model* model, Parameter* inputA){
  return (locate_and_replace(model, inputA, inputA));
}

bool SBML_search::is_present(Model* model, InitialAssignment* inputA){
  return (locate_and_replace(model, inputA, inputA));
}

bool SBML_search::is_present(Model* model, Rule* inputA){
  return (locate_and_replace(model, inputA, inputA));
}

bool SBML_search::is_present(Model* model, Constraint* inputA){
  return (locate_and_replace(model, inputA, inputA));
}

bool SBML_search::is_present(Model* model, Reaction* inputA){
  return (locate_and_replace(model, inputA, inputA));
}

bool SBML_search::is_present(Model* model, Event* inputA){
  return (locate_and_replace(model, inputA, inputA));
}

// #############################################################################################
// #                                 LOCATE_AND_REPLACE BLOCK                                  #
// #############################################################################################
//
// For each function we evaluate where the entity type (as defined by the input) could be in each
// of the ten entity types (FunctionDefinition, UnitDefinition, Compartment, Species, Parameter, 
// InitialAssignment, Rule, Contraint, Reactions and Events) except the type we're dealing with.
//

// LOCATE_AND_REPLACE_ASTNode
// Depth first search recursive ASTNode locate_and_replace
// If *any* replace_node functions return true overall is set to true and remains true, 
// irrespective of later events
// #############################################################################################

bool SBML_search::locate_and_replace(ASTNode* node, string query, string replacement){
  
  bool end = false;
  ASTNode* temp_node;
  
  int num_children = node->getNumChildren();
  
  if (node->isName()){
    string name = node->getName();
    
        if (strcmp(query.c_str(), name.c_str()) == 0){
	  end = replace_node(node, replacement);
	  if (end)
	    return true;
	}
  }
  
  // if more then one child
  for (int i = 0 ; i < num_children ; i++){
    
    // get child i, then recursivly locate_and_replace child
    temp_node = node->getChild(i);
    end = locate_and_replace(temp_node, query, replacement); 
    if (end)
      return true;
  }

  return end;
}

// #############################################################################################
// LOCATE_AND_REPLACE_mathML
// This rather complicated function takes a model, and a query string, (and a replacement string if necessary).
// It's a common public function implemented by SBML_search, and can be run on SBML_search objects and 
// SBML_cleanup objects, although the result differes depending on which of these two classes you call the
// function through;
// 
// SBML_search - here we simply discover if the query string is located in the model MathML structures anywhere,
// return true if it is or false if not
//
// SBML_cleanup - here, we not only find any instances where that query is located, but also replace it with
// the replacement string when found. Returns true if any replacements are made, or false if none are made
//
// For clarity, we can also call locate_and_replace with just a model and a query string, as obiously
// if we're using the SBML_search version a replacement string is redundant. A bit ugly, but gives a nice interface
// to users of the class.
//
//
// It's worth noting the reason we create a new ASTNode structure and re-assign it to the model is because
// getMath() returns a ASTNode const * type, so you are unable to modify the root node. Very unhelpful. 
//
// #############################################################################################

// version which only takes a query string, if used elsewhere, for clarity if nothing else. If you accidentally
// call this version from a cleanup object, the model remains unchanged - good safety feature
bool SBML_search::locate_and_replace_mathML(Model* model, std::string query){
  return (locate_and_replace_mathML(model, query, query));
}


// full version which takes both query and replacement
bool SBML_search::locate_and_replace_mathML(Model* model, std::string query, std::string replacement){

  bool end = false;
  int num_elements;
  int num_EA;
  
  FunctionDefinition* temp_func;
  InitialAssignment* temp_IA;
  Rule* temp_rule;
  Constraint* temp_con;
  
  Reaction* temp_rxn;
  KineticLaw* temp_klaw;
  
  Event* temp_event;
  Trigger* temp_trig;
  Priority* temp_pri;
  Delay* temp_delay;
  EventAssignment* temp_EA;

  
  ASTNode* new_node_p;
  
  // FUNCTION DEFINITIONS ---------------------------------------------
  num_elements = model->getNumFunctionDefinitions();
  for (int i = 0 ; i < num_elements ; i++){
    
    // get temporary function
    temp_func = model->getFunctionDefinition(i);
    
    // create ASTNode tree structure using the copy constructor
    ASTNode new_node(*(temp_func->getMath()));
    
    // set new_node_p pointer to the newly copied node - 
    // this gives us a root node pointer which is *not* 
    // const - this is problem with getMath() function
    new_node_p = &new_node;
    
    end = locate_and_replace(new_node_p, query, replacement);
    
    // end will only be ever true if we're searching, not replacing
    // saves us searching after we've found one instance!
    if (end)
      return true;

    temp_func->setMath(new_node_p);
  }

  // INITIAL ASSIGNMENT ---------------------------------------------
  num_elements = model->getNumInitialAssignments();
  for (int i = 0 ; i < num_elements ; i++){
    
    // get temporary InitialAssignment
    temp_IA = model->getInitialAssignment(i);
    
    // same logic as in FUNCTION section
    ASTNode new_node(*(temp_IA->getMath()));
    new_node_p = &new_node;
    
    end = locate_and_replace(new_node_p, query, replacement);
    
    // end will only be ever true if we're searching, not replacing
    // saves us searching after we've found one instance!
    if (end)
      return true;
    
    temp_IA->setMath(new_node_p);
  }
  
  // RULES ---------------------------------------------
  num_elements = model->getNumRules();
  
  for (int i = 0 ; i < num_elements ; i++){
    
    // get temporary rule
    temp_rule = model->getRule(i);
    
    // same logic as in FUNCTION section
    ASTNode new_node(*(temp_rule->getMath()));
    new_node_p = &new_node;
    
    //log_stream << "RULE: " << temp_rule->getId() << endl;
    end = locate_and_replace(new_node_p, query, replacement);
   
    // end will only be ever true if we're searching, not replacing
    // saves us searching after we've found one instance!
    if (end)
      return true;
    
    temp_rule->setMath(new_node_p);
    
  }
  
  // CONSTRAINT ---------------------------------------------
  num_elements = model->getNumConstraints();
  for (int i = 0 ; i < num_elements ; i++){
    
    temp_con = model->getConstraint(i);
    // same logic as FUNCTION section
    
    ASTNode new_node(*(temp_con->getMath()));
    new_node_p = &new_node;

    end = locate_and_replace(new_node_p, query, replacement);
    
    // end will only be ever true if we're searching, not replacing
    // saves us searching after we've found one instance!
    if (end)
      return true;
    
    temp_con->setMath(new_node_p);
  }
  
  // REACTIONS ---------------------------------------------
  num_elements = model->getNumReactions();
  for (int i = 0 ; i < num_elements ; i++){
    
    temp_rxn = model->getReaction(i);
    temp_klaw = temp_rxn->getKineticLaw();
    
    ASTNode new_node(*(temp_klaw->getMath()));
    new_node_p = &new_node;
    
    end = locate_and_replace(new_node_p, query, replacement);
    
    // end will only be ever true if we're searching, not replacing
    // saves us searching after we've found one instance!
    if (end)
      return true;
    
    temp_klaw->setMath(new_node_p);
  }

  // EVENTS ---------------------------------------------
  num_elements = model->getNumEvents();
  for (int i = 0 ; i < num_elements ; i++){

    temp_event = model->getEvent(i);
      
    // search trigger object
    temp_trig = temp_event->getTrigger();
    
    ASTNode new_node(*(temp_trig->getMath()));
    new_node_p = &new_node;

    end = locate_and_replace(new_node_p, query, replacement);
    
    if (end)
      return true;
    
    temp_trig->setMath(new_node_p);

    // Search priority object, if it exists
    if (temp_event->isSetPriority()){
      temp_pri = temp_event->getPriority();
      
      ASTNode new_node(*(temp_pri->getMath()));
      new_node_p = &new_node;

      end = locate_and_replace(new_node_p, query, replacement);
	
      if (end)
	return true;

      temp_pri->setMath(new_node_p);
    }
      
    // search delay object, if it exists
    if (temp_event->isSetDelay()){
      temp_delay = temp_event->getDelay();
      
      ASTNode new_node(*(temp_delay->getMath()));
      new_node_p = &new_node;

      end = locate_and_replace(new_node_p, query, replacement);
	
      if (end)
	return true;
    }

    // search event assignments
    num_EA = temp_event->getNumEventAssignments();
    for (int j = 0 ; j < num_EA ; j++){
      temp_EA = temp_event->getEventAssignment(j);
      
      ASTNode new_node(*(temp_EA->getMath()));
      new_node_p = &new_node;

      end = locate_and_replace(new_node_p, query, replacement);
	
      if (end)
	return true;
    }
    
  }
  return end;
}


// #############################################################################################
// LOCATE_AND_REPLACE_FUNCTION
//
//
bool SBML_search::locate_and_replace(Model* model, FunctionDefinition* inputA, FunctionDefinition* inputB){
  // -- Function defition - don't replace ID, as we use this to then remove the function as it becomes
  // an unused function, simply replace any occurence in the MathML object

  bool end = false;

  // Replace all appearances in any MathML structure in the model
  end = locate_and_replace_mathML(model, inputA->getId(), inputB->getId());
  
  // FUNCIONS - done in mathML

  // UNITS - functions not used 
  
  // COMPARTMENTS - functions not used

  // SPECIES - functions not used

  // PARAMETERS - functions not used
  
  // EVENTS - functions not used
  
  return end;
  
}


// #############################################################################################
// LOCATE_AND_REPLACE_UNITS
// 
//
bool SBML_search::locate_and_replace(Model* model, UnitDefinition* inputA, UnitDefinition* inputB){
  
  // set default exit condition to false
  bool end = false;
  
  // Model substanceUnits value - default value for units if not explicity set can be given in the model as the
  // substanceUnits attribute
  
  if (inputA->getId() == model->getSubstanceUnits()){
    end = replace_unit(inputA, inputB, 'M', 0); 
    if (end)
      return true;
  }
  
   // Model timeUnits value - define how time is measured in the model
  if (inputA->getId() == model->getTimeUnits()){
    end = replace_unit(inputA, inputB, 'T', 0); 
    if (end)
      return true;
  }

  // Model volumeUnitss value - default volume unit (3D)
  if (inputA->getId() == model->getVolumeUnits()){
    end = replace_unit(inputA, inputB, 'V', 0); 
    if (end)
      return true;
  }

  // Model areaUnits value - default area unit (2D)
  if (inputA->getId() == model->getAreaUnits()){
    end = replace_unit(inputA, inputB, 'A', 0); 
    if (end)
      return true;
  }
  // Model lengthUnit value - default length unit (1D)
  if (inputA->getId() == model->getLengthUnits()){
    end = replace_unit(inputA, inputB, 'L', 0); 
    if (end)
      return true;
  }

  // Model extentUnits value - default progression unit
  if (inputA->getId() == model->getExtentUnits()){
    end = replace_unit(inputA, inputB, 'E', 0); 
    if (end)
      return true;
  }

  // --- no units in the function definition
  
  // --- find unit in compartments
  int num_compartments = model->getNumCompartments();
  
  if (num_compartments != 0){
    
    // loop over each compartment
    for (int i = 0 ; i < num_compartments ;  i++){
      
      Compartment* compartment = model->getCompartment(i);
      
      // if that compartments units = those of input
      if (compartment->getUnits() == inputA->getId()){
	// uses dynamic binding to access the sbml_searc or sbml_cleanup 
	// version of replace respectivly
	end = replace_unit(inputA, inputB, 'C', i); 
	if (end)
	  return true;
      }
    }
  }
  
  // locate unit in species
  int num_species = model->getNumSpecies();
  
  if (num_species != 0){
    
    // loop over each species
    for (int i = 0 ; i < num_species ;  i++){
      
      Species* species = model->getSpecies(i);
      
      // if that species units = those of inputA
      if (species->getUnits() == inputA->getId()){
	end = this->replace_unit(inputA, inputB, 'S', i);
	if (end)
	  return true;
      }
    }
  }
  
  // locate unit in parameters
  int num_params = model->getNumParameters();
  
  if (num_params != 0){
    
    // loop over each species
    for (int i = 0 ; i < num_params ;  i++){
      
      Parameter* parameter = model->getParameter(i);
      
      // if that species units = those of inputA
      if (parameter->getUnits() == inputA->getId()){
	end = this->replace_unit(inputA, inputB, 'P', i);
	if (end)
	  return true;
      }
    }
  }

  //--- Units in initial assignment are calculated based on the components
  
  // locate unit in rules
  int num_rules = model->getNumRules();
  
  // loop over each species
  for (int i = 0 ; i < num_rules ;  i++){
    
    Rule* rule = model->getRule(i);
    
    // if that species units = those of inputA
    if (rule->getUnits() == inputA->getId()){
      end = this->replace_unit(inputA, inputB, 'R', i);
      if (end)
	return true;
    }
  }
  
  // replace units in constraints - none!

  // replace unit in reactions
  int num_rxns = model->getNumReactions();
  int num_local_params;

  for (int i = 0 ; i < num_rxns ; i++){

    Reaction* rxn = model->getReaction(i);
    KineticLaw* klaw = rxn->getKineticLaw();
    
    num_local_params = klaw->getNumLocalParameters();
    
    for (int j = 0 ; j < num_local_params ; j++){
      Parameter* local_param = klaw->getParameter(j);

      if (local_param->getUnits() == inputA->getId()){
	end = this->replace_unit(inputA, inputB, 'X', i);
	if (end)
	  return true;
      }
    }
  }  
  
  // no units in events
  
  return false;
}


// #############################################################################################
// LOCATE_AND_REPLACE COMPARTMENT
// Goes through the model you feed in and replaces any references to inputA with references to inputB
// Obviously, you should try and make sure inputB is actually in the model, as this does not add inputB to
// model!
bool SBML_search::locate_and_replace(Model* model, Compartment* inputA, Compartment* inputB){
  
  bool end = false;

  // mathML replacement
  end = locate_and_replace_mathML(model, inputA->getId(), inputB->getId());
  
  // find compartments in functions - none!

  // find compartments in units - none!

  // find compartments in species

  int num_elements = model->getNumSpecies();
  Species* species;
  
  for (int i = 0 ; i < num_elements ; i++){
    
    species = model->getSpecies(i);
    
    if (species->getCompartment() == inputA->getId()){
      end = replace_compartment(inputA, inputB, 'S', i);
      if (end)
	return true;
    }
  }
  
  // find compartments in parameters - none!

  // find compartments in initial assignments
  num_elements = model->getNumInitialAssignments();
  InitialAssignment* initas;
  
  for (int i = 0 ; i < num_elements ; i++){
    
    initas = model->getInitialAssignment(i);
    
    if (initas->getSymbol() == inputA->getId()){
      end = replace_compartment(inputA, inputB, 'I', i);
      if (end)
	return true;
    }
  }
  
  // find compartments in rules
  num_elements = model->getNumRules();
  Rule* rule;
  
  for (int i = 0 ; i < num_elements ; i++){
    
    rule = model->getRule(i);
    
    if (rule->isAssignment() || rule->isRate()){
      
      if (rule->getVariable() == inputA->getId()){
	end = replace_compartment(inputA, inputB, 'R', i);
	if (end)
	  return true;
      }
    }
  }

  // find compartments in constraints - none!
  
  // find compartments in reactions 
  num_elements = model->getNumReactions();
  Reaction* rxn;
  
  for (int i = 0 ; i < num_elements ; i++){
    
    rxn = model->getReaction(i);
    
    if (rxn->getCompartment() == inputA->getId()){
      end = this->replace_compartment(inputA, inputB, 'X', i);
      if (end)
	return true;
    }
  }

  // find compartments in events - located in event assignments (Event sub-element)
  num_elements = model->getNumEvents();
  int num_eventAs;
  Event* event;
  EventAssignment* eventAs;
    
  for (int i = 0 ; i < num_elements ; i++){
    
    event = model->getEvent(i);
    num_eventAs = event->getNumEventAssignments();
    
    for (int j = 0 ; j < num_eventAs ; j++){
      
      eventAs = event->getEventAssignment(j);
      
      if (eventAs->getVariable() == inputA->getId()){
	end = this->replace_compartment(inputA, inputB, 'E', i);
	if (end)
	  return true;
      }
    }
  }
  
  return end;
  
}


// #############################################################################################
// LOCATE_AND_REPLACE SPECIES
bool SBML_search::locate_and_replace(Model* model, Species* inputA, Species* inputB){ 
  bool end = false;

  // mathML replacement
  locate_and_replace_mathML(model, inputA->getId(), inputB->getId());
  
  // find Species in functions - none!

  // find Species in units - none!

  // find species in parameter - none!

  // find Species in initial assignment
  int num_elements = model->getNumInitialAssignments();
  InitialAssignment* initas;
  
  for (int i = 0 ; i < num_elements ; i++){
    
    initas = model->getInitialAssignment(i);
    
    if (initas->getSymbol() == inputA->getId()){
      end = replace_species(inputA, inputB, 'I', i);
      if (end)
	return true;
    }
  }

  // find species in rules
  num_elements = model->getNumRules();
  Rule* rule;
  
  for (int i = 0 ; i < num_elements ; i++){
    
    rule = model->getRule(i);
    
    if (rule->isAssignment() || rule->isRate()){
      
      if (rule->getVariable() == inputA->getId()){
	end = replace_species(inputA, inputB, 'R', i);
	if (end)
	  return true;
      }
    }
  }
  
  // find species in reactions 
  int num_species;
  SpeciesReference* SR;
  ModifierSpeciesReference* MSR;
  num_elements = model->getNumReactions();
  Reaction* rxn;
  
  for (int i = 0 ; i < num_elements ; i++){
    
    rxn = model->getReaction(i);
    num_species = rxn->getNumReactants();
    
    for (int j = 0 ; j < num_species ; j++){
      SR = rxn->getReactant(j);
      if(SR->getSpecies() == inputA->getId()){
	end = replace_species(inputA, inputB, 'r', i);
	if (end)
	  return true;
      }
    }
    
    num_species = rxn->getNumProducts();
    for (int j = 0 ; j < num_species ; j++){
      SR = rxn->getProduct(j);
      if(SR->getSpecies() == inputA->getId()){
	end = replace_species(inputA, inputB, 'p', i);
	if (end)
	  return true;
      }
    }
      
    num_species = rxn->getNumModifiers();
    for (int j = 0 ; j < num_species ; j++){
      MSR = rxn->getModifier(j);
      if(SR->getSpecies() == inputA->getId()){
	end = replace_species(inputA, inputB, 'm', i);
	if (end)
	  return true;
      }
    }
  }
    
  // find species in events - located in event assignments (Event sub-element)
  num_elements = model->getNumEvents();
  int num_eventAs;
  Event* event;
  EventAssignment* eventAs;
    
  for (int i = 0 ; i < num_elements ; i++){
    
    event = model->getEvent(i);
    num_eventAs = event->getNumEventAssignments();
    
    for (int j = 0 ; j < num_eventAs ; j++){
      
      eventAs = event->getEventAssignment(j);
      
      if (eventAs->getVariable() == inputA->getId()){
	end = replace_species(inputA, inputB, 'E', i);
	if (end)
	  return true;
      }
    }
  }

  return end;
}
bool SBML_search::locate_and_replace(Model* model, Parameter* inputA, Parameter* inputB){ 
  bool end = false;
  int num_elements;
   // mathML replacement
  end = locate_and_replace_mathML(model, inputA->getId(), inputB->getId());

  // find parameter reference in function definition - none!
  // find parameter reference in unit definition - none!
  // find parameter reference in comparment - none!
  
  // find parameter reference in parameter (conversion factor)
  num_elements = model->getNumSpecies();
  Species* species;
    
  for (int i = 0 ; i < num_elements ; i++){
    
    species = model->getSpecies(i);
    
    if (species->getConversionFactor() == inputA->getId()){
      end = replace_parameters(inputA, inputB, 'S', i);
      if (end)
	return true;
    }
  }
  
  // find parameter in initial assignment
  InitialAssignment* initas;
  num_elements = model->getNumInitialAssignments();
  
  for (int i = 0 ; i < num_elements ; i++){
    
    initas = model->getInitialAssignment(i);
    
    if (initas->getSymbol() == inputA->getId()){
      end = replace_parameters(inputA, inputB, 'I', i);
      if (end)
	return true;
    }  
  }
    
  // find parameters in rules
  num_elements = model->getNumRules();
  Rule* rule;
  
  for (int i = 0 ; i < num_elements ; i++){
    
    rule = model->getRule(i);
    
    if (rule->isAssignment() || rule->isRate()){
      
      if (rule->getVariable() == inputA->getId()){
	end = replace_parameters(inputA, inputB, 'R', i);
	if (end)
	  return true;
      }
    }
  }

  // find parameters in reactions - no global ones other than in XML - however, localParameters exist in reaction
  // list. For now we're ignoring them and asserting models must have 0 local parameters (due to namespace clashes).
  // This can be rectified by making localParameters unqique, but is not currently a priority

    // find parameter in events - located in evenAssignments object (Event sub-element)
  num_elements = model->getNumEvents();
  int num_eventAs;
  Event* event;
  EventAssignment* eventAs;
    
  for (int i = 0 ; i < num_elements ; i++){
    
    event = model->getEvent(i);
    num_eventAs = event->getNumEventAssignments();
    
    for (int j = 0 ; j < num_eventAs ; j++){
      
      eventAs = event->getEventAssignment(j);
      
      if (eventAs->getVariable() == inputA->getId()){
	end = replace_parameters(inputA, inputB, 'E', i);
	if (end)
	  return true;
      }
    }
  }
  
  return end;
}
bool SBML_search::locate_and_replace(Model* model, InitialAssignment* inputA, InitialAssignment* inputB){ 
  
  bool end = false;
  
  // mathML replacement - may not be necessary, but keeping in for now in alpha 0.1
  
  // none for any other element

  end = locate_and_replace_mathML(model, inputA->getId(), inputB->getId());
  
  return end;
}



bool SBML_search::locate_and_replace(Model* model, Rule* inputA, Rule* inputB){ 
  
  // Rules are used to associate other components together, so they themselves cannot be 
  // referenced. A species, speciesReferemce, parameter or compartment  is defined, and then 
  // a rule references that parameter  and defines kinetic law  or relation, including 
  // (potentially) other parameters, species  and anything else in the MathML fo that rule. 
  // However, they would be dealt with by the parameter replacement.

  
  return false;
  
}
bool SBML_search::locate_and_replace(Model* model, Constraint* inputA, Constraint* inputB){ 
  // Constraints are used to define a model assumption, and cannot be referenced
  
return false;
}

bool SBML_search::locate_and_replace(Model* model, Reaction* inputA, Reaction* inputB){ 

  bool end;
  
  // other than being reffered to in mathML structure (maybe, unclear?) reaction IDs aren't
  // referenced anywehre else
  end = locate_and_replace_mathML(model, inputA->getId(), inputB->getId());
  
  return end;
}
bool SBML_search::locate_and_replace(Model* model, Event* inputA, Event* inputB){ 
  
  // Events are used to define a model assumption constraints, and cannot be referenced
  return false;
}


// #############################################################################################
// #                                      REPLACE_* BLOCK                                      #
// #############################################################################################
// The SBML_search implementation of the search simply returns true! These are used to implement
// inheritance based polymorphism 


bool SBML_search::replace_node(ASTNode* node, std::string replacement){
  return true;
}

bool SBML_search::replace_unit(UnitDefinition* inputA, UnitDefinition* inputB, char C, int i){
  return true;
}

bool SBML_search::replace_compartment(Compartment* inputA, Compartment* inputB, char C, int i){
  return true;
}

bool SBML_search::replace_species(Species* inputA, Species* inputB, char C, int i){
  return true;
}

bool SBML_search::replace_parameters(Parameter* inputA, Parameter* inputB, char C, int i){
  return true;
}


// #############################################################################################
// Return the 
int SBML_search::total_num_entities(const Model* inputM){
  
  int total = 0;

  total += inputM->getNumFunctionDefinitions();
  total += inputM->getNumUnitDefinitions();
  total += inputM->getNumCompartments();
  total += inputM->getNumSpecies();
  total += inputM->getNumParameters();
  total += inputM->getNumInitialAssignments();
  total += inputM->getNumRules();
  total += inputM->getNumConstraints();
  total += inputM->getNumReactions();
  total += inputM->getNumEvents();

  return total;
  
}
