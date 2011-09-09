// Copyright Alex Holehouse 2011
// Distributed under the terms of the GNU general public license - see COPYING.txt for more details

#include "sbml_display.h"
#include "sbml_search.h"

#include <string>
#include <fstream>
#include <sbml/SBMLTypes.h>
#include <iostream>

using namespace std;

// print a summary of the model to screen
//-----------------------------------------------------------------------------------
void SBML_display::show_summary(const Model* model, string filename){
  
  print_header("Display Summary", true);
  cout << "File name ---------------- " << filename << endl;
  cout << "Model ID ----------------- " << model->getId() << endl;
  cout << "Model name --------------- " << model->getName() << endl; 
  cout << "Model version ------------ " << model->getVersion() << endl;
  cout << "Model level -------------- " << model->getLevel() << endl;
  cout << "Model substance units ---- " << model->getSubstanceUnits() << endl;
  cout << "Model time units --------- " << model->getTimeUnits() << endl;
  cout << "Model volume units ------- " << model->getVolumeUnits() << endl;
  cout << "Model area units --------- " << model->getAreaUnits() << endl;
  cout << "Model length units ------- " << model->getLengthUnits() << endl;
  cout << "Model extent units ------- " << model->getExtentUnits() << endl;
  cout << "Model conversion factor -- " << model->getConversionFactor() << endl;
  
  cout << "---------------------------------" << endl;
  cout << "Summary of model components" << endl;
  cout << "---------------------------------" << endl;
  cout << "No of functions ----------- " << model->getNumFunctionDefinitions() << endl;
  cout << "No of unit definitions --- " << model->getNumUnitDefinitions() << endl;
  cout << "No of compartments ------- " << model->getNumCompartments() << endl;
  cout << "No of species ------------ " << model->getNumSpecies() << endl;
  cout << "No of parameters --------- " << model->getNumParameters() << endl;
  cout << "No of initial assignments  " << model->getNumInitialAssignments() << endl;
  cout << "No of rules -------------- " << model->getNumRules() << endl;
  cout << "No of constraints -------- " << model->getNumConstraints() << endl;
  cout << "No of reactions ---------- " << model->getNumReactions() << endl;
  cout << "No of events ------------- " << model->getNumEvents() << endl;
  cout << "----------------------------------" << endl;
  any_key_to_continue();
}

void SBML_display::select_components_to_show(const Model* model, string message){

  nullchecker(model, "SBML_display - select_components_to_show");
  
  double selector;
  string input;
  system("clear");
  cout << "---------------------------------------" << endl;
  cout << "NB: " << message << endl;
  
  while (true){
    cout << "Select components to show\n";
    cout << "---------------------------------------" << endl;
    cout << "[1] ------------ Function Definitions" << endl
	 << "[2] ------------ Unit Definitions" << endl
	 << "[3] ------------ Compartments " << endl
	 << "[4] ------------ Species " << endl
	 << "[5] ------------ Parameters" << endl
	 << "[6] ------------ Rules" << endl
	 << "[7] ------------ Initial Assignments" << endl
	 << "[8] ------------ Constraints" << endl
	 << "[9] ------------ Reactions" << endl
	 << "[10] ----------- Events" << endl
	 << "[11] ----------- Return" << endl
	 << "Select: ";
    
    selector = doubleGet_guarenteed(1,11);
    
    switch(static_cast<int>(selector))
      {
	// Unit Definitions  

      case 1:
	show_functionDefinitions(model);
	break;
	
      case 2:
	show_unitDefinitions(model);
	break;
	
	// compartments
      case 3:
	show_compartments(model);
	break;	
	
	// species
      case 4:
	show_species(model);
	break;
	  
	// Parameters
      case 5:
	show_parameters(model);
	break;
	
	// Rules
      case 6:
	show_rules(model);
	break;

      case 7:
	show_initial_assignments(model);
	break;

      case 8:
	show_constraints(model);
	break;
	  
	// Reacions
      case 9:
	show_reactions(model);
	break;

      case 10:
	show_events(model);
	break;
	
	// return to previous method
      case 11:
	return;
	
      default:
	cout << "Not a valid selection.\n";
      } // end of switch

    any_key_to_continue();
  }
}


// Function to show the all the model's entities
//-----------------------------------------------------------------------------------
void SBML_display::show_all(const Model* model){
  show_functionDefinitions(model);
  show_unitDefinitions(model);
  show_compartments(model);
  show_species(model);
  show_parameters(model);
  show_initial_assignments(model);
  show_rules(model);
  show_constraints(model);
  show_reactions(model);
  show_events(model);
}
  
// #############################################################################################
// #                                       SHOW_* BLOCK                                        #
// #############################################################################################



// #############################################################################################
// Function to show the model's functions
// 
void SBML_display::show_functionDefinitions(const Model* model){
  
  const ListOfFunctionDefinitions* list_of_function_defs;
  const FunctionDefinition* function;
  int num_functions = model->getNumFunctionDefinitions();

  print_header("Display Function", true);
  if (num_functions > 1)
    cout << "There are " << num_functions << " functions defined;" << endl;
  else if (num_functions == 1)
    cout << "There is " << num_functions << " function defined;" << endl;
  else {
    cout << "There are no functions defined" << endl;
    return;
  }

  list_of_function_defs = model->getListOfFunctionDefinitions();
  
  for (int i = 0 ; i < num_functions ; i++){

    function = list_of_function_defs->get(i);
    cout << "Function [" << i+1 << "] Name( " << function->getName() << ")" << endl
	 << "    Formula: " << SBML_formulaToString(function->getMath()) << endl;
  }
  
}



// #############################################################################################
//
// show the model's unit definition
//-----------------------------------------------------------------------------------
void SBML_display::show_unitDefinitions(const Model* model){  
  
  // number of units - calculated each time incase of model updates
  int num_units = model->getNumUnitDefinitions();
  
  // used as temporary unit definition for processing
  const UnitDefinition* unit_def; 

  print_header("Display Units", true);  
  if (num_units > 1)
    cout << "There are " << num_units << " units defined;" << endl;
  else if (num_units == 1)
    cout << "There is " << num_units << " units defined;" << endl;
  else {
    cout << "There are no units defined" << endl;
    return;
  }

  // Build the search framework
  SBML_search* search_framework = new SBML_search;
  
  // Get access to the unit definitions
  const ListOfUnitDefinitions* units_list = model->getListOfUnitDefinitions();
  
  
  // For each unit definition in the list do the following;
  for (int i = 0 ; i < num_units ; i++)
    {
      unit_def = units_list->get(i);
      cout << "Unit[" << i+1 << "] ";
      cout << "       Name = " << unit_def->getName() << endl
	   <<"        ID =   " << unit_def->getId() << endl
	   <<"        Units = " 
	   << search_framework->describe_units(unit_def->getListOfUnits(), unit_def->getNumUnits()) << endl;
    }
  cout << endl;
  

  // free up memory
  delete search_framework;
}


// #############################################################################################
// Show the compartments in a model
//
//
void SBML_display::show_compartments(const Model* model){  
  
  int num_compartments = model->getNumCompartments();
  
  // Variable declaration
  const Compartment *compartment;
  
  string units; // Strings used for output
  
  print_header("Display Compartments", true); 
  if (num_compartments > 1)
    cout << "There are " << num_compartments << " compartments defined;" << endl;
  else if (num_compartments == 1)
    cout << "There is " << num_compartments << " compartment defined;" << endl;
  else {
    cout << "There are no compartments defined" << endl;
    
    // should have compartments defined!
    log_stream << "WARNING: No compartments defined" << endl;
    return;
  }

  SBML_search* search_framework = new SBML_search;
  
  // loop for each compartment
  for (int i = 0 ; i < num_compartments ; i++)
    {
      
      compartment = model->getCompartment(i);
      units = compartment->getUnits();
      
      
      cout << "Compartment [" << i+1 << "] ID(" << compartment->getId() << ") name(" << compartment->getName() << ")" << endl;

      cout << "    Spatial Dimensions: " << compartment->getSpatialDimensions() << endl;
      cout << "    Size: " << compartment->getSize() << endl;
      
      
      if (units != "")
	cout << "    Units: " << search_framework->units_lookup(model, units) << endl;
      else
	cout << "    Units: (no units defined)" << endl;

      cout << "    Constant: " << compartment->getConstant() << endl;
    }

  delete search_framework;
}



// #############################################################################################
// Function to display the model's species
//
//
void SBML_display::show_species(const Model* model){
  const ListOfSpecies* species_list;
  const Species* species;
  int num_species;
  
  species_list = model->getListOfSpecies();
  num_species = model->getNumSpecies();
  
  print_header("Display Species", true);
  if (num_species > 1)
    cout << "There are " << num_species << " species defined;" << endl;
  else if (num_species == 1)
    cout << "There is " << num_species << " species defined;" << endl;
  else {
    cout << "There are no species defined" << endl;
    return;
  }
  
  // for loop which runs over every species in the ListOfSpecies object
  for (int i = 0 ; i < num_species ; i++){
    // get the ith species
    species = species_list->get(i);
    
    // cout the species number, name and ID
    cout << "Species [" << i+1 << "] Name(" 
	 << species->getName() << ")"
      
	 << " ID(" << species->getId() << ")" << endl;
    
    // cout the species' compartment
    cout << "    Compartment(" << species->getCompartment() << ")" << endl;

    // if the spcies has an initial amount set, then display the initial amount, if an initial 
    // concentrtaion then display that
    
    cout << "    Initial concentration = " << species->getInitialAmount() << endl;
    
    if (species->isSetInitialAmount()){
      
      if (species->isSetInitialConcentration()){
	cout << "    Initial concentration = " << species->getInitialAmount() 
	     << " / " << species->getCompartment();
      }
      
      else{
	cout << "    Initial amount = " << species->getInitialAmount() 
	     << " " << species->getSubstanceUnits();
      }
    }
    
    // if not, then show this
    else
      cout << "    No initial concentration or amount defined";
    
    cout << endl;
    
    // show if the species' amount remains constant 
    if (species->getConstant())
      cout << "    Constant = true";
    else
      cout << "    Constant = false";

    cout << endl << endl;
  }
}



// #############################################################################################
// Function to display the model's parameters
//
//
void SBML_display::show_parameters(const Model* model){
  
  int num_parameters = model->getNumParameters();
  
  // build the search framework
  SBML_search* search_framework = new SBML_search;

  const Parameter* parameter;
  
  print_header("Display Parameters", true);

  // initial preamble
  if (num_parameters > 1)
    cout << "There are " << num_parameters << " parameters defined;" << endl;
  else if (num_parameters == 1)
    cout << "There is " << num_parameters << " parameter defined;" << endl;
  else {
    cout << "There are no parameters defined" << endl;
    return;
  }
  
  // for loop for each parameter in the model
  for (int i = 0 ; i < num_parameters ; i++){
    parameter = model->getParameter(i);
    
    cout << "Parameter [" << i+1 << "] Name(" << parameter->getName() << ") ID(" 
	 << parameter->getId() << ")" << endl;
    
    cout << "    Value =  "; 
    if (parameter->getValue() != 0)
      cout << parameter->getValue() << " " ;
    
    else
      cout << "<Param. to be determined> ";
      
    cout << search_framework->units_lookup(model, parameter->getUnits());

    cout << endl;
    
    if (parameter->getConstant())
      cout << "    Constant = true";
    else
      cout << "    Constant = false";
    
    cout << endl << endl;
  }

  delete search_framework;
} 



// #############################################################################################
// Function to show the model's initial assignments
//
//
void SBML_display::show_initial_assignments(const Model* model){
  const InitialAssignment* initial_assignment;
  const UnitDefinition* unit_def;

  SBML_search* search_framework = new SBML_search;
  int num_initial_assignments = model->getNumInitialAssignments();
  
  print_header("Display Initial Assignment", true);
    if (num_initial_assignments > 1)
      cout << "There are " << num_initial_assignments << " initial assignments defined;" << endl;
    
    else if (num_initial_assignments == 1)
      cout << "There is " << num_initial_assignments << " initial assignment defined;" << endl;
    
    else {
      cout << "There are no initial assignments defined" << endl;
      return;
    }
    
    // Loop over each initial assignment
    for (int i = 0 ; i < num_initial_assignments ; i++){
      initial_assignment = model->getInitialAssignment(i);
      cout << "Initial Assignment [" << i+1 << "] ID(" << initial_assignment->getId() << ")" << endl
	   << "    Formula: " << SBML_formulaToString(initial_assignment->getMath()) << endl;
      cout << "    Units: ";
      
      // get the calculated unit definition
      unit_def = initial_assignment->getDerivedUnitDefinition();
      cout << search_framework->describe_units(unit_def->getListOfUnits(), unit_def->getNumUnits()) << endl;
    }
    
  delete search_framework;
}



// #############################################################################################
// Function to show the model's rules
//
//
void SBML_display::show_rules(const Model* model){
  
  int num_rules = model->getNumRules();
  const UnitDefinition* unit_def;
  const Rule* rule;
  print_header("Display Rules", true);
  
  if (num_rules > 1)
    cout << "There are " << num_rules << " rules defined;" << endl;
  else if (num_rules == 1)
    cout << "There is " << num_rules << " rule defined;" << endl;
  else {
    cout << "There are no rules defined" << endl;
    return;
  }
  
  SBML_search* search_framework = new SBML_search;
  
  for (int i = 0 ; i < num_rules ; i++){
    
    rule = model->getRule(i);
    cout << "Rule [" << i+1 << "] ID(" << rule->getId() << ")" << endl;
    if (rule->isAlgebraic())
      cout << "    Algebraic rule: ";
    
    if (rule->isAssignment())
      cout << "    Assignment rule: ";
    
    if (rule->isRate())
      cout << "    Rate rule: ";

    cout << rule->getFormula() << endl;
    cout << "    Units: ";
    
    unit_def = rule->getDerivedUnitDefinition();
    cout << search_framework->describe_units(unit_def->getListOfUnits(), unit_def->getNumUnits()) << endl << endl;
    
    
  }
  delete search_framework;

}



// #############################################################################################
// Function to show the model's constraints
//
//
void SBML_display::show_constraints(const Model* model){
  
  const Constraint* constraint;
  int num_constraints = model->getNumConstraints();
  
  print_header("Display Constraints", true);
  
  if (num_constraints > 1)
    cout << "There are " << num_constraints << " constraints defined;" << endl;
  else if (num_constraints == 1)
    cout << "There is " << num_constraints << " constraint defined;" << endl;
  else {
    cout << "There are no constraints defined" << endl;
    return;
  }
  

  for (int i = 0 ; i < num_constraints; i++){
    constraint = model->getConstraint(i);
    cout << "Constraint [" << i+1 << "] ID(" << constraint->getId() << ")" << endl
	 << "    Formula: " << SBML_formulaToString(constraint->getMath()) << endl
	 << "    Message: " << constraint->getMessageString() << endl;
      }
}



// #############################################################################################
// Function to display the reactions in the model
//
//
void SBML_display::show_reactions(const Model* model){
  
  const ListOfReactions* rxn_list;
  const KineticLaw* rate_law;
  int num_mods, location;
  const Reaction* rxn;
  string string_var;
  bool rulelookup;
  int num_rxns = model->getNumReactions();
  
  // Construct the search framework
  SBML_search* search_framework = new SBML_search;
  
  // get the list of reactions in the model
  rxn_list= model->getListOfReactions();
  
  // get the number of reactions in the model (i.e. number of items in rxn_list)
  num_rxns = model->getNumReactions();
  
  print_header("Display Reaction", true);

  if (num_rxns > 1)
    cout << "There are " << num_rxns << " reactions defined;" << endl;
  else if (num_rxns == 1)
    cout << "There is " << num_rxns << " reaction defined;" << endl;
  else {
    cout << "There are no reactions defined" << endl;
    return;
  }
   
  for (int i = 0 ; i < num_rxns ; i++){
    
    rulelookup = false;
    
    // get pointer to reaction i
    rxn = rxn_list->get(i);

    // get number of reactants, products and modifiers
    num_mods = rxn->getNumModifiers();
    
    cout << "Reaction [" << i+1 << "] Name(" << rxn->getName() <<") ID(" 
	 << rxn->getId() << ")" << endl;

    cout << "    ";

    output_reaction_formula(rxn);
    cout << endl << "    Modifiers: ";
    output_reaction_modifiers(rxn);
    
    // Output modifiers


    
    // display a kinetic law - this is fiddly, because we check both the reactions kineticLaw 
    // variable and then search in rules for referenced kinetic laws
    if (rxn->isSetKineticLaw()){
      rate_law = rxn->getKineticLaw();
      cout << endl << "    Rate law: ";

      // get the formula of the rate law
      string_var = rate_law->getFormula();
      
      // BELOW is primarily an artefact of an model we worked on where the rate law was
      // defined as a rule with the format RULENAME(). By removing the "()" we could
      // then find what the rule's value was, and display that here. Don't worry about
      // it too much...
      
      // Cut terminal () if necessary - MathML adds a () to the end of kineticLaws which 
      // reference somewhere else. This cuts off that terminal (). NOTE this could be a 
      // source of error if a mal-formatted rule is cleaved
      location = string_var.rfind("()");
      if (location != -1)
	{
	  if (static_cast <unsigned int> (location) + 2 == string_var.size()){
	    // send this text output log, not cout!
	    log_stream << "Reaction [" << i << "] WARNING: String reformatting done to remove () for referenced kineticLaw searching, line 255 in sbml_display.cpp. Prior to formatting string was " << string_var;
	    
	    // chop off () at end by resizing string
	    string_var.resize(string_var.size() - 2);
	    
	    log_stream << " however, after formatting, string is " << string_var << endl << endl;
	  }
	  
	  rulelookup = true;
	}
      
      cout << string_var << endl << "      Local parameters: " 
	   << rate_law->getNumLocalParameters() << endl << "      Global parameters: " 
	   << rate_law->getNumParameters() << endl;

      if (rate_law->getNumLocalParameters() > 1){
	cout << "ERROR - At this stage, version " << get_version() << " cannot deal with local parameters in reactions. A workaround will be added, but currently this is not critical, so to avoid serious problems we're aborting the process. Sozzle." << endl;
	log_stream << "ERROR - At this stage, version " << get_version() << " cannot deal with local parameters in reactions. A workaround will be added, but currently this is not critical, so to avoid serious problems we're aborting the process. Sozzle." << endl;
	autoAbort("Aborting..");
      }
      
      // using the search framework we identify if the rule defined here is actually 
      // referencing a previously defined rule
      const Rule* rule = NULL;
      
      if (rulelookup)
	rule = search_framework->find_rule(model, string_var);

      // rule == NULL if no rule was found
      if (rule != NULL){
	cout << "      Referenced rule: " << rule->getFormula() << endl;
	if (rule->isSetUnits())
	  cout << "      Units = " << rule->getUnits();
      }
    }
    cout << endl << endl;
  }

  // free up mem
  delete search_framework;
}

// #############################################################################################
//
//

void SBML_display::output_reaction_formula(const Reaction* rxn){
  int stoich = 0;
  const SpeciesReference* species;
  int num_reactants = rxn->getNumReactants();
  int num_products = rxn->getNumProducts();
  
  for (int j = 0 ; j < num_reactants ; j++){
          
    species = rxn->getReactant(j);
    stoich = species->getStoichiometry();
    
    // if stoichiometry is not simply 1
    if (stoich != 1)
      cout << stoich << species->getSpecies();
    // if stoichiometry is 1
    else
      cout << species->getSpecies();

    // add "+" in the appropriate place between reactants for printout
    if (num_reactants > 0 && j+1 != num_reactants)
      cout << " + ";
  }

  if (rxn->isSetReversible())
    cout << " <---> ";
  else
    cout << " -->";
    
  // Output products
  for (int j = 0 ; j < num_products ; j++){
    species = rxn->getProduct(j);
    stoich = species->getStoichiometry();
      
    // if stoichiometry is not simply 1
    if (stoich != 1)
      cout << stoich << species->getSpecies();
      
    // if stoichiometry is 1
    else
      cout << species->getSpecies();
    if (num_products > 0 && j+1 != num_products)
      cout << " + ";
  }
}

// #############################################################################################
//
// 
void SBML_display::output_reaction_modifiers(const Reaction* rxn){
  
  int num_mods = rxn->getNumModifiers();
  const ModifierSpeciesReference* mod;
  
  if (num_mods ==0) // if no modifiers then just print none
    cout << "<none>";
  
  // otherwise cycle through them
  else { 
    for (int j = 0 ; j < num_mods ; j++){
      mod = rxn->getModifier(j);
      cout << mod->getSpecies();
      if (num_mods > 0 && j+1 != num_mods)
	cout << " + ";
    }
  }
}

// #############################################################################################
// 
// list_reaction_species
// 
//

void SBML_display::list_reaction_species(int type, Reaction* rxn){
  
  int num;
  string type_string;
  
  if (type == 0){
    type_string = "Reactants";
    num = rxn->getNumReactants();
  }
  
  else if (type == 1){
    type_string = "Products";
    num = rxn->getNumProducts();
  }

  else if (type == 2){
    type_string = "Modifiers"; 
    num = rxn->getNumModifiers();
  }
  
  else{
    autoAbort("Invalid type selected in list_reaction_species method call, must be 0,1 or 2");
  }
  
  cout << "---- List of reaction " << type_string << " ----" << endl;
  cout << type_string << " in reaction " << rxn->getId() << " are;" << endl;
  
  if (num == 0)
    cout << "None found" << endl;
  
  for (int i = 0 ; i < num ;i++){
    cout << "[" << i << "]" << " - ";
    if (type == 0)
      cout << (rxn->getReactant(i))->getSpecies() << endl;

    if (type == 1)
      cout << (rxn->getProduct(i))->getSpecies() << endl;

    if (type == 2)
      cout << (rxn->getModifier(i))->getSpecies() << endl;
    
    cout << endl;
  }

}

// #############################################################################################
// #############################################################################################
// Function to display the events in the model
//
//
void SBML_display::show_events(const Model* model) {
  
  const Event* event;
  const EventAssignment* event_assignment;
  
  int num_events = model->getNumEvents();
  int num_event_assignments;
  
  if (num_events > 1)
    cout << "There are " << num_events << " events defined;" << endl;
  else if (num_events == 1)
    cout << "There is " << num_events << " event defined;" << endl;
  else {
    cout << "There are no events defined" << endl;
    return;
  }
  
  print_header("Display Events", true);

  
  for (int i = 0 ; i < num_events; i++){
    event = model->getEvent(i);
    cout << "Event [" << i+1 << "] ID(" << event->getId() << "), Name(" << event->getName()
	 << " ) " << endl;
    

    // dispay if event uses values from trigger time
    cout << "    Use values from trigger time: ";
    if (event->getUseValuesFromTriggerTime())
      cout << "true" << endl;
    else
      cout << "false" << endl;

    // ---- display trigger info ----
    
    if (event->isSetTrigger()){
      const Trigger* trigger = event->getTrigger();
	
      cout << "    Trigger: Initial value = ";
      
      if (trigger->isSetInitialValue())
	cout << "true";
      else 
	cout << "false";
      
      cout << " and persistent = ";

      if (trigger->isSetPersistent())
	cout << "true" << endl;
      else 
	cout << "false" << endl;
      
      cout << "       Formula: ";
      if (trigger->isSetMath())
	cout << SBML_formulaToString(trigger->getMath()) << endl;
      else
	cout << "<none defined>" << endl;
    }

    // ---- display priority info ----
    
    if (event->isSetPriority()){
      const Priority* priority = event->getPriority();
      
            
      cout << "     Priority: " << endl << "      Formula: ";
      if (priority->isSetMath())
	cout << SBML_formulaToString(priority->getMath()) << endl;
      else
	cout << "<none defined>" << endl;
    }
      
    // ---- display delay info ----
    
    if (event->isSetDelay()){
      const Delay* delay = event->getDelay();
      
            
      cout << "     Delay: " << endl << "      Formula: ";
      if (delay->isSetMath())
	cout << SBML_formulaToString(delay->getMath()) << endl;
      else
	cout << "<none defined>" << endl;
    }

    // ---- display Event assignment info ----

    num_event_assignments = event->getNumEventAssignments();

    cout << "    Event Assignments:" << endl;
    
    // for each event assignment in the event entity
    for (int i = 0 ; i < num_event_assignments ; i++){
      
      event_assignment = event->getEventAssignment(i);
      
      cout << "       Event assignment {" << i << "} Variable(" <<event_assignment->getVariable()
	   << ") " << endl;
      cout << "       Formula: " << SBML_formulaToString(event_assignment->getMath()) << endl;
      
    }
  }
}

// #############################################################################################
//                                    LIST_* BLOCK                                            #
// #############################################################################################
//
// Functions that list the IDs of a named group in a model
//

void SBML_display::select_components_to_list(const Model* model, string message){
  double selector;
  string input;
  system("clear");
  cout << "---------------------------------------" << endl;
  cout << "NB: " << message << endl;
  
  while (true){
    cout << "Select components to list\n";
    cout << "---------------------------------------" << endl;
    cout << "[1] ----------- Unit Definitions\n[2] ----------- Compartments \n[3] ----------- Species \n[4] ----------- Parameters\n[5] ----------- Rules\n[6] ----------- Reactions\n[7] ----------- Return\n" << endl;
    cout << "Select: ";
    
    selector = doubleGet_guarenteed(1,7);
    
    switch(static_cast<int>(selector))
      {
	// Unit Definitions  
      case 1:
	list_unit_definitions(model);
	break;
	
	// compartments
      case 2:
	list_compartments(model);
	break;	
	
	// species
      case 3:
	list_species(model);
	break;
	  
	// Parameters
      case 4:
	list_parameters(model);
	break;
	
	// Rules
      case 5:
	list_rules(model);
	break;
	  
	// Reacions
      case 6:
	list_reactions(model);
	break;
	
	// return to previous method
      case 7:
	return;
	
      default:
	cout << "Not a valid selection.\n";
      } // end of switch

    any_key_to_continue();
  }
}

void SBML_display::list_unit_definitions(const Model* inputM){
  int num = inputM->getNumUnitDefinitions();
  SBML_search search;
  const UnitDefinition* udef;
  
  cout << "---- List of Unit Definitions ----" << endl;
  cout << "[No] <UnitDef ID> (<Unit description>)" << endl;
  for (int i = 0 ; i < num ; i++){
    udef = inputM->getUnitDefinition(i);
    cout << "[" << i+1 << "] " << udef->getId() << " (" 
	 << search.units_lookup(inputM, udef->getId()) << ")" << endl;
  }
}

void SBML_display::list_compartments(const Model* inputM){
  int num = inputM->getNumCompartments();
  cout << "---- List of Compartments ----" << endl;
  cout << "[No] <Compartment ID>" << endl;
  for (int i = 0 ; i < num ; i++)
    cout << "[" << i+1 << "] " << (inputM->getCompartment(i))->getId() << endl;
}

void SBML_display::list_species(const Model* inputM){
  cout << "---- List of Species ----" << endl;
  cout << "[No] <Species ID>" << endl;
  int num = inputM->getNumSpecies();
   for (int i = 0 ; i < num ; i++)
    cout << "[" << i+1 << "] " << (inputM->getSpecies(i))->getId() << endl;
}

void SBML_display::list_parameters(const Model* inputM){
  int num = inputM->getNumParameters();
  cout << "---- List of Parameters ----" << endl;
  cout << "[No] <Parameter ID>" << endl;
  for (int i = 0 ; i < num ; i++)
    cout << "[" << i+1 << "] " << (inputM->getParameter(i))->getId() << endl;
}

void SBML_display::list_rules(const Model* inputM){
  int num = inputM->getNumRules();
  const Rule* rule;
  
  cout << "---- List of Rules ----" << endl;
  cout << "[No] <Rule ID> <Rule description>" << endl;
  for (int i = 0 ; i < num ; i++){
    rule = inputM->getRule(i);
    
    if (rule->isAlgebraic())
      cout << "[" << i+1 << "] " << endl << "  Formula: " << rule->getFormula() << endl << endl;
    else
      cout << "[" << i+1 << "] " << rule->getId() << endl << "  Formula: " 
	   << rule->getFormula()  << endl << endl;
  }
}
void SBML_display::list_reactions(const Model* inputM){
  int num = inputM->getNumReactions();
  
  cout << "---- List of Reactions ----" << endl;
  cout << "\n[No] <Reaction ID> (<Reaction Name>)" << endl;
  for (int i = 0 ; i < num ; i++)
    cout << "[" << i+1 << "] " << (inputM->getReaction(i))->getId() 
	 << " name (" << (inputM->getReaction(i))->getName() << ")" << endl;
}
 
int SBML_display::compare(string title, string A, string B, bool disclaimer){
  
  char selector = ' ';

  // if both are the same no need to change!
  if (A == B){
    
    cout << "Both values of the '" << title << "' attributes have the same value (" << A << ")" << endl;
    any_key_to_continue();
    
    return 0;
  }
  
  while(true){
    cout << "### " << title << " ###" << endl;
    if (disclaimer){
      cout << "Ensure that if you select option B, it actually exists in the model\n(i.e. you set it as one of the elements to import in the .conf file.\nSoftware support to check this coming real soon, but at the moment\nplease try and be careful!)" << endl;
    }
    
    cout << " A ----- "; 
    if (A == "")
      cout << " [NONE DEFINED]" << endl;
    else
      cout << A << endl;
    
    cout << " B ----- ";
    if (B == "")
      cout << " [NONE DEFINED]" << endl;
    else
      cout << B << endl;

    cout << endl << " Select (A or B): ";
    // take in A or B
    cin >> selector;
    cin.ignore();	

    cout << endl;
    if (selector == 'A')
      return 0;
    
    if (selector == 'B')
      return 1;
    
    cout << "**** Invalid Selection ****" << endl;
  }

}

int SBML_display::compare3way(string title, string A, string B, string C, bool disclaimer){
  
  char* selector;

  // if both are the same no need to change!c
  if (A == B)
    return 0;
  
  while(true){
    cout << "### " << title << " ###" << endl;
    if (disclaimer){
      cout << "Ensure that if you select option B, it actually exists in the model\n(i.e. you set it as one of the elements to import in the .conf file.\nSoftware support to check this coming real soon, but at the moment\nplease try and be careful!)" << endl;
    }
    
    cout << " A ----- "; 
    if (A == "")
      cout << " [NONE DEFINED]" << endl;
    else
      cout << A << endl;
    
    cout << " B ----- ";
    if (B == "")
      cout << " [NONE DEFINED]" << endl;
    else
      cout << B << endl;
    
    cout << " C ----- ";
    if (C == "")
      cout << " [NONE DEFINED]" << endl;
    else
      cout << C << endl;
    
    cout << endl << "Select (A, B or C): ";
    
    // take in A, B or C
    selector = selectorGet();

    cout << endl;
    if (selector[0] == 'A')
      return 0;
    
    if (selector[0] == 'B')
      return 1;
    
    if (selector[0] == 'C')
      return 2;
    cout << "**** Invalid Selection ****" << endl;
  }

}


