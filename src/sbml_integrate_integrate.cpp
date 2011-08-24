// Copyright Alex Holehouse 2011
// Distributed under the terms of the GNU general public license - see COPYING.txt for more details

#include "sbml_integrate_integrate.h"
#include <sbml/SBMLTypes.h>
#include <string>
#include <iostream>

using namespace std;

// #############################################################################################
// #                                                                                           #
// #                                   INTEGRATE ELEMENT BLOCK                                 #
// #                                                                                           #
// #############################################################################################

// #############################################################################################
// CONSTRUCTOR

SBML_integrate_integrate::SBML_integrate_integrate(Model* _model_new){
  
  // set variables and build cleanup framework
  model_new = _model_new;
  cleanup_framework = new SBML_cleanup(model_new, false);
  
  return;
}

  

// #############################################################################################
// NOTHING TO INTEGRATE
//
void SBML_integrate_integrate::nothing_to_integrate(string item){
  
  cout << endl << " No " << item << " to integrate" << endl << endl;
  log_stream << "No " << item << " to intergrate" << endl;
  any_key_to_continue();
}



// #############################################################################################
// INTEGRATE_FUNCTIONDEFINITIONS
//
void SBML_integrate_integrate::integrate_functionDefinitions(SBML_confInput& input_file, Model* model_new, SBML_listpair_container<ListOfFunctionDefinitions>& listpair){
  log_stream << "functionDefinition integrate support not yet added..." << endl;
}


// #############################################################################################
// INTEGRATE_UNITDEFINITIONS
//
void SBML_integrate_integrate::integrate_unitDefinitions(SBML_confInput& input_file, Model* model_new, SBML_listpair_container<ListOfUnitDefinitions>& listpair){ 
  // support to be added - why would you want to *integrate* units?
}

// #############################################################################################
// INTEGRATE_COMPARTMENTS!
//
//
//
void SBML_integrate_integrate::integrate_compartments(SBML_confInput& input_file, Model* model_new, SBML_listpair_container<ListOfCompartments>& listpair){
  
  int AorB;

  // number of compartments to integrate, as defined by the conf file
  int num = input_file.get_num_integrate_compartments();
  
  if (num == 0){
    nothing_to_integrate("compartment");
    return;
  }
  
  // get integration lists from conf file
  ListOfCompartments* listA = input_file.get_integrateA_compartments();
  ListOfCompartments* listB = input_file.get_integrateB_compartments();
  
  Compartment* tempA;
  Compartment* tempB;
  Compartment* inNew;
  Compartment* inNew_copy;
  
  print_header("Integrate Compartments", true);
  

  // loop for each item in the two lists
  for (int i = 0 ; i < num ; i++){
    
    tempA = listA->get(i);
    tempB = listB->get(i);
    
    // if unable to find the ID, getCompartment  will return NULL
    inNew = model_new->getCompartment(tempA->getId());

    string error;
    if (inNew == NULL)
      autoAbort(((error.append("FATAL ERROR - unable to find ")).append(tempA->getId())).append(" in newModel..."));
    
    // create a deep copy to work on
    inNew_copy = inNew->clone();
    
    log_stream << operation << " Compartment integration: A(" 
	       << tempA->getId() << ") and B(" << tempB->getId() 
	       << ")" << endl;
    
    cout << "Compare " << tempA->getId() << " and " << tempB->getId() << endl;
    cout << "[Compartment " << i+1 << " of " << num << "]" << endl;
    
    // name --------------------------------------------------------------------------------
    AorB = display_framework.compare("Please select a name for the compartment", inNew->getName(), tempB->getName(), false); 
    if (AorB == 1)
      inNew_copy->setName(tempB->getName());
    // if 0 then just leave it as is!
    
    
    // spatial dimensions ------------------------------------------------------------------
    AorB = display_framework.compare("Spatial Dimensions", dtostr(inNew->getSpatialDimensions()), 
				     dtostr(tempB->getSpatialDimensions()), false); 
    if (AorB == 1)
      inNew_copy->setSpatialDimensions(tempB->getSpatialDimensions());
    // if 0 then just leave it as is!

    // size --------------------------------------------------------------------------------
    AorB = display_framework.compare("Size", dtostr(inNew->getSize()), 
				     dtostr(tempB->getSize()), false); 
    if (AorB == 1)
      inNew_copy->setSize(tempB->getSize());
    // if 0 then just leave it as is!

    // units -------------------------------------------------------------------------------
    // we use model_new for both as it's import any units defined in tempB would be referencable 
    // in the current incarnation of model_new. If they're not, perhaps you needed to import 
    // some units!
    AorB = display_framework.compare_units(inNew, tempB, model_new, model_new);
    if (AorB == 1)
      inNew_copy->setUnits(tempB->getUnits());
    // if 0 then just leave it as is!
    
    // constant ----------------------------------------------------------------------------
    AorB = display_framework.compare("Constant", dtostr(inNew->getConstant()), dtostr(tempB->getConstant()), false);     if (AorB == 1)
      inNew_copy->setConstant(tempB->getConstant());
    // if 0 then just leave it as is!
    
    // SAVE NEW COMPARTMENT ----------------------------------------------------------------
    AorB = display_framework.compare("Is this compartment", 
				     "A totally new compartment?", 
				     "Simply an improvement to an existing one which was already in modelA?", false); 
    cout << "------------------------------------------------------------------------" << endl;

    if (AorB == 0){
      new_ID_message("compartment");
      
      display_framework.list_compartments(model_new);
      
      cout << "New ID is : ";
      
      string newID;
      newID = stringGet();
      
      if (0 != inNew_copy->setId(newID))
	autoAbort("WARNING - New ID was not accepted, this was probably a formatting error due to the selected ID. Aborting...");
      logfile_add_message(model_new->addCompartment(inNew_copy), 
			  inNew_copy->getId(), 
			  "model_new compartments");
      
      // addCompartment makes a copy, so we must delete the original to avoid a memory leak
    }
    else{
      // remove and delete the original
      model_new->removeCompartment(inNew->getId());
      delete inNew;
      
      // replace by adding in the edited copy compartment, and delete the original 
      // (a copy generated and added to the model)
      logfile_add_message(model_new->addCompartment(inNew_copy), 
			  inNew_copy->getId(), 
			  "model_new compartments");
    }

    cout << "About to call replacement_list_update..., current values are: " 
	 << listpair.get_num() << endl;
    
    replacement_list_update(inNew_copy, tempB, listpair.get_listA(), listpair.get_listB(), listpair.get_num());
    
    cout << "After to call replacement_list_update..., new values are: " 
	 << listpair.get_num() << endl;
    
    delete inNew_copy;
    operation++;
  }

  display_framework.show_compartments(model_new);
}

// Helper function called by above
void SBML_integrate_integrate::replacement_list_update(Compartment* inNew_copy, Compartment* tempB, ListOfCompartments* rep_compartmentsA, ListOfCompartments* rep_compartmentsB, int& rep_compartments_num ){
  
  // for_replacement enters a UI where we decided if we want to replace references to
  // tempB with references to inNew_copy
  if (1 == for_replacement_UI(inNew_copy->getId(), tempB->getId()))  
    {
      // replace any reference in the model_new to tempB with references to inNew_copy
      cleanup_framework->replace(tempB, inNew_copy);
      
      // add these values to the replacement lists for later updates
      rep_compartmentsA->append(inNew_copy);
      rep_compartmentsB->append(tempB);
      
      // update the counter
      rep_compartments_num++;
      
    }
  
}

// #############################################################################################
// INTEGRATE_SPECIES!
//
//
//
void SBML_integrate_integrate::integrate_species(SBML_confInput& input_file, Model* model_new, SBML_listpair_container<ListOfSpecies>& listpair){       
  int AorB;
  int num = input_file.get_num_integrate_species();

  if (num == 0){
    nothing_to_integrate("species");
    return;
  }
  
  ListOfSpecies* listA = input_file.get_integrateA_species();
  ListOfSpecies* listB = input_file.get_integrateB_species();
  
  Species* tempA;
  Species* tempB;
  Species* inNew;
  Species* inNew_copy;  

  print_header("Integrate species", true);
  
  for (int i = 0 ; i < num ; i++){
    tempA = listA->get(i);
    tempB = listB->get(i);

    // if unable to find the ID will return NULL
    inNew = model_new->getSpecies(tempA->getId());
    
    string error; 
    
    // if we can't find tempA in the new model then print an error message and exit 
    if (inNew == NULL)
      autoAbort(((error.append("FATAL ERROR - unable to find ")).append(tempA->getId())).append(" in newModel..."));

    // create a deep copy to work on
    inNew_copy = inNew->clone();
    
    log_stream << operation << " Species integration: A(" 
	       << tempA->getId() << ") and B(" << tempB->getId() 
	       << ")" << endl;
    
    cout << "Compare " << tempA->getId() << " and " << tempB->getId() << endl;
    cout << "[Species " << i+1 << " of " << num << "]" << endl;
    
    // name ----------------------------------------------------------------------------------
    AorB = display_framework.compare("Name", inNew->getName(), tempB->getName(), false); 
    if (AorB == 1)
      inNew_copy->setName(tempB->getName());
    
    // compartment ---------------------------------------------------------------------------
    AorB = display_framework.compare("Compartment", inNew->getCompartment(), tempB->getCompartment(), true); 
    if (AorB == 1)
      inNew_copy->setCompartment(tempB->getCompartment());
    
    // initial ammount------------------------------------------------------------------------
    AorB = display_framework.compare("Initial Amount", dtostr(inNew->getInitialAmount()), dtostr(tempB->getInitialAmount()), false); 
    if (AorB == 1)
      inNew_copy->setInitialAmount(tempB->getInitialAmount());
    
    // initial concentration------------------------------------------------------------------
    AorB = display_framework.compare("Initial Concentration", dtostr(inNew->getInitialConcentration()), dtostr(tempB->getInitialConcentration()), false); 
    if (AorB == 1)
      inNew_copy->setInitialConcentration(tempB->getInitialConcentration());
    
    // units ---------------------------------------------------------------------------------
    // we use model_new for both as it's import any units defined in tempB would be referencable in the current
    // incarnation of model_new. If they're not, perhaps you needed to import some units!
    AorB = display_framework.compare_units(inNew, tempB, model_new, model_new);
    if (AorB == 1)
      inNew_copy->setUnits(tempB->getUnits());
    
    // has only substance units---------------------------------------------------------------
    AorB = display_framework.compare("Has only substance units?", dtostr(inNew->getHasOnlySubstanceUnits()), dtostr(tempB->getHasOnlySubstanceUnits()), false); 
    if (AorB == 1)
      inNew_copy->setHasOnlySubstanceUnits(tempB->getHasOnlySubstanceUnits());
    
    // boundary conditions?-------------------------------------------------------------------
    AorB = display_framework.compare("Has boundary conditions?", dtostr(inNew->getBoundaryCondition()), dtostr(tempB->getBoundaryCondition()), false); 
    if (AorB == 1)
      inNew_copy->setBoundaryCondition(tempB->getBoundaryCondition());
    
    // constant ------------------------------------------------------------------------------
    AorB = display_framework.compare("Constant", dtostr(inNew->getConstant()), dtostr(tempB->getConstant()), false);
    if (AorB == 1)
      inNew_copy->setConstant(tempB->getConstant());

    // conversion factor ---------------------------------------------------------------------
    if (inNew->getConversionFactor() != tempB->getConversionFactor())
      cout << "NB - Conversion factor must refer to a parameterID which is *CONSTANT*" << endl;
    
    AorB = display_framework.compare("Conversion factor", inNew->getConversionFactor(), tempB->getConversionFactor(), true);
    if (AorB == 1)
      inNew_copy->setConversionFactor(tempB->getConversionFactor());
    
    // Save new species ----------------------------------------------------------------------
    AorB = display_framework.compare("Is this species", 
				     "A totally new species?", 
				     "Simply an improvement to an existing one which was already in modelA?", 
				     false); 
    if (AorB == 0){
      cout << "------------------------------------------------------------------------" << endl;
      
      new_ID_message("species");
      display_framework.list_species(model_new);
      cout << endl;
      
      cout << "New ID is : ";
      
      string newID;
      newID = stringGet();
            
      if (0 != inNew_copy->setId(newID))
	autoAbort("WARNING - New ID was not accepted, this was probably a formatting error due to the selected ID. Aborting...");
      
      // addCompartment makes a copy, so we must delete the original to avoid a memory leak 
      // (done after next else block)
      logfile_add_message(model_new->addSpecies(inNew_copy), 
			  inNew_copy->getId(), 
			  "model_new species");
    }
    else{
      // remove and delete the original
      model_new->removeSpecies(inNew->getId());
            
      // replace by adding in the edited copy compartment, and delete the original 
      // (a copy generated and added to the model)
      logfile_add_message(model_new->addSpecies(inNew_copy), 
			  inNew_copy->getId(), 
			  "model_new species");
      delete inNew;
    }
    
    replacement_list_update(inNew_copy, tempB, listpair.get_listA(), listpair.get_listB(), listpair.get_num());
    
    delete inNew_copy;
    
    operation++;
    
  }
}

// Helper function called by above
void SBML_integrate_integrate::replacement_list_update(Species* inNew_copy, Species* tempB, 
						       ListOfSpecies* rep_speciesA, 
						       ListOfSpecies* rep_speciesB, 
						       int& rep_species_num){
  
  // for_replacement enters a UI where we decided if we want to replace references to
  // tempB with references to inNew_copy
  if (1 == for_replacement_UI(inNew_copy->getId(), tempB->getId()))  
    {
      // replace any reference in the model_new to tempB with references to inNew_copy
      cleanup_framework->replace(tempB, inNew_copy);
      
      // add these values to the replacement lists for later updates
      rep_speciesA->append(tempB);
      rep_speciesB->append(inNew_copy);
      
      // update the counter
      rep_species_num++;
    }
  
}

// #############################################################################################
// INTEGRATE_PARAMETERS!
//
//
//
void SBML_integrate_integrate::integrate_parameters(SBML_confInput& input_file, Model* model_new, SBML_listpair_container<ListOfParameters>& listpair){   
  int AorB;
  int num = input_file.get_num_integrate_parameters();
  
  if (num == 0){
    nothing_to_integrate("parameters");
    return;
  }
  
  
  // used as a flag to indicate the role of this new parameter in terms of replacing the original parameters
  //
  
  ListOfParameters* listA = input_file.get_integrateA_parameters();
  ListOfParameters* listB = input_file.get_integrateB_parameters();
  
  Parameter* tempA;
  Parameter* tempB;
  Parameter* inNew;
  Parameter* inNew_copy;  

  print_header("Integrate parameters", true);
  
  for (int i = 0 ; i < num ; i++){
    tempA = listA->get(i);
    tempB = listB->get(i);

    // if unable to find the ID will return NULL
    inNew = model_new->getParameter(tempA->getId());
    
    string error;
    
    // if we can't find tempA in the new model then print an error message and exit 
    if (inNew == NULL)
      autoAbort(((error.append("FATAL ERROR - unable to find ")).append(tempA->getId())).append(" in newModel..."));

    // create a deep copy to work on
    inNew_copy = inNew->clone();
    
    log_stream << "[" << operation << "] Parameter integration: A(" 
	       << tempA->getId() << ") and B(" << tempB->getId() 
	       << ")" << endl;
    
    cout << "Compare " << tempA->getId() << " and " << tempB->getId() << endl;
    cout << "[Parameter " << i+1 << " of " << num << "]" << endl;
    // name ---------------------------------------------------------------------------------
    AorB = display_framework.compare("Name", inNew->getName(), tempB->getName(), false); 
    if (AorB == 1)
      inNew_copy->setName(tempB->getName());
       
    // value---------------------------------------------------------------------------------
    AorB = display_framework.compare("Value", dtostr(inNew->getValue()), dtostr(tempB->getValue()), false); 
    if (AorB == 1)
      inNew_copy->setValue(tempB->getValue());
    
    // units --------------------------------------------------------------------------------
    // we use model_new for both as it's import any units defined in tempB would be referencable in the current
    // incarnation of model_new. If they're not, perhaps you needed to import some units!
    AorB = display_framework.compare_units(inNew, tempB, model_new, model_new);
    if (AorB == 1)
      inNew_copy->setUnits(tempB->getUnits());
    
    // constant -----------------------------------------------------------------------------
    AorB = display_framework.compare("Constant", dtostr(inNew->getConstant()), dtostr(tempB->getConstant()), false);
    if (AorB == 1)
      inNew_copy->setConstant(tempB->getConstant());
    
    // Save new parameter -------------------------------------------------------------------
    AorB = display_framework.compare("Is this parameters", 
				     "A totally new parameters?", 
				     "Simply an improvement/replacement to an existing one which was already in modelA?", 
				     false); 
    cout << "------------------------------------------------------------------------" << endl;
    
    // This is a totally new parameter
    if (AorB == 0){
      
      new_ID_message("parameter");
      display_framework.list_parameters(model_new);
      cout << endl;
      
      cout << "New ID is : ";
      string newID;
      newID = stringGet();
      
      if (0 != inNew_copy->setId(newID))
	autoAbort("WARNING - New ID was not accepted, this was probably a formatting error due to the selected ID. Aborting...");
	
      // addParameter makes a copy, so we must delete the original (inNew_copy) to avoid a memory leak
      logfile_add_message(model_new->addParameter(inNew_copy), 
			  inNew_copy->getId(), 
			  "model_new parameters");
    }

    // This is just improving an existing parameter in newModel
    else{
      // remove and delete the original
      model_new->removeParameter(inNew->getId());
      
      // replace by adding in the edited copy compartment, and delete the original (a copy generated and added to
      // the model)
      logfile_add_message(model_new->addParameter(inNew_copy), inNew_copy->getId(), 
			  "model_new parameters");
      delete inNew;
    }
    
    replacement_list_update(inNew_copy, tempB, listpair.get_listA(), listpair.get_listB(), listpair.get_num());
        
    delete inNew_copy;
    
    operation++;
    
  }
  
}

// Helper function called by above
  void SBML_integrate_integrate::replacement_list_update(Parameter* inNew_copy, Parameter* tempB, 
							 ListOfParameters* rep_parametersA, 
							 ListOfParameters* rep_parametersB, 
							 int& rep_parameters_num){
  
  // for_replacement enters a UI where we decided if we want to replace references to
  // tempB with references to inNew_copy
  if (1 == for_replacement_UI(inNew_copy->getId(), tempB->getId()))  
    {
      // replace any reference in the model_new to tempB with references to inNew_copy
      cleanup_framework->replace(tempB, inNew_copy);
      
      // add these values to the replacement lists for later updates
      rep_parametersA->append(tempB);
      rep_parametersB->append(inNew_copy);
      
      // update the counter
      rep_parameters_num++;
    }
  
}

void SBML_integrate_integrate::integrate_initialAssignments(SBML_confInput& input_file, Model* model_new){
  
  log_stream << "initial assignment integration not yet added" << endl;
  cout << "initial assignment integration not yet added" << endl;
  
}


// #############################################################################################
// INTEGRATE_RULES
//
// There are some *CRITICAL* semantic/dependency issues here, that are worth understanding.
// Rules do not actually have an ID attribute (checkout the SBML specification) but the getId()
// function instead returns the variable attribute. This works just fine - rules allow us to 
// define a dynamic way of assigning or determining another element, be it species, speciesRef
// compartment or parameter. HOWEVER, clearly in terms of model replacements this can 
// ruin everything. 
//
// Example - we lookup a rule using it's ID, which is actually a variable. What this means is we
// *must* not remove any of model_new's IDs, because we're actually using them to lookup rules. 
// Currently this doens't happen - we rename modelB ids, but never remove a model_new ID - if a
// new parameter is added it's a copy, and if we edit an existing parameter we can't change
// it's ID.
// 
//
//
void SBML_integrate_integrate::integrate_rules(SBML_confInput& input_file, Model* model_new){   

  int AorB;
  int num = input_file.get_num_integrate_rules();
  
  if (num == 0){
    nothing_to_integrate("rules");
    return;
  }

  ListOfRules* listA = input_file.get_integrateA_rules();
  ListOfRules* listB = input_file.get_integrateB_rules();
  
  // for the MathML formula modification
  string message;
  
  Rule* tempA;
  Rule* tempB;
  Rule* inNew;
  Rule* inNew_copy;  
  int location;

  print_header("Integrate rules", true);
  
  for (int i = 0 ; i < num ; i++){
    tempA = listA->get(i);
    tempB = listB->get(i);
    
    // if unable to find the rule in our new_model the functions below return NULL
    
    // if the rule is algebraic we cannot use the getId() method, so must use a user defined 
    // rule_by_formula lookup
    if (tempA->isAlgebraic()){
      location = rule_by_formula(tempA);
      if (location == -1)
	inNew = NULL;
      else
	inNew = model_new->getRule(location);
    }
    // however, if it is not algebraic, we can use getId to act as a lookup
    else
      inNew = model_new->getRule(tempA->getId());
    
    
    string error;
    
    // if we can't find tempA in the new model then print an error message and exit 
    if (inNew == NULL)
      autoAbort(((error.append("FATAL ERROR - unable to find ")).append(tempA->getId())).append(" in newModel..."));
    
    // create a deep copy to work on
    inNew_copy = inNew->clone();
    
    log_stream << "[" << operation << "] Rule integration: A(";
    if (!tempA->isAlgebraic())
      log_stream << tempA->getId() << ") and B(" << tempB->getId() << ")" << endl;
    else
      log_stream << tempA->getFormula() << ") and B(" << tempB->getFormula() << ")" << endl;
    
    if (!tempA->isAlgebraic())
      cout << "Compare " << tempA->getId() << " and " << tempB->getId() << endl;
    else
      cout << "Compare " << tempA->getFormula() << " and " << tempB->getFormula() << endl;
    
    cout << "[Rule " << i+1 << " of " << num << "]" << endl;
    
    // Variable ----------------------------------------------------------------------------
    
    // Assignment and rate rules have a "variable" attribute, while allgebraiec rules do not...
    if (inNew->isAssignment() || inNew->isRate()){
      AorB = display_framework.compare("Variable", inNew->getVariable(), tempB->getVariable(), true); 
      if (AorB == 1)
	inNew_copy->setName(tempB->getName());
    }
    
    // math formula
    
    message = "\nThis rule is ";
    if (inNew->isAlgebraic())
      message.append("an algabraic rule. Such a rule is in effect at all times, and it is up to the user to ensure such a rule is not overdetermined, and additionally reaction rates cannot be determined by algebraic rules.\n "); 
    
    if (inNew->isAssignment()){
      message.append("an assignment rule. \n\nSuch a rule is used to determine the value of a variable, where the left hand side (variable)\nattribute may be a species, speciesReference (a species in a reaction), compartment or parameter, but *not* a reaction, and is in effect at all times during the reaction. A breif overview of the constraints is as follows;\n\n- Species\n Formula generates the concentration/amount of the species, and the units generated by the formula must equal the 'units' attribute of the species. A speciesReference with it's 'species' attribute set by an AssignmentRule variable must have its boundaryCondition attribute set to true\n\n- SpeciesReference\nFormula determines the stoichiometric value of the speciesReference.\n\n- Compartment\n Formula determines the compartment's size\n\n- Parameter\n Formula determines the parameter's value, where derived formula units must be equal to parameter units.\n\n");
    }
    
    if (inNew->isRate()){(((message.append("a rate rule. Such a rule determines the rate of change of a variable (the left hand side), where that variable is  a species, speciesReference, parameter or compartment, but *not* a reaction.A breif overview of the constraints is as follows;\n\n- Species\nFormula determines the rate of change of a species, where units derived from this equation should be equal to the units of the species over the model default time units (")).append(model_new->getTimeUnits())).append(" in this model).A speciesReference with it's 'species' attribute set by an AssignmentRule variable must have its boundaryCondition attribute set to true\n\n- SpeciesReference\n Formula determines the rate of change of the stoichiometric value of the speciesReference.\n\n - Compartment\nFormula determines the rate of change of the compartment's size, where derived formula units must equal to the cmpartment's defined units/time. \n\n- Parameter\n Formula determines the rate of change of the parameter's value, where derived formula units must be equal to parameter's defined units/time.\n\n"));
	}
    
    message.append("For more details regarding semantics of rules please consult the appropriate papers (namely the language specification document. ");
    
    compare_and_edit_maths("Rules formula", inNew_copy, tempB,  message); 

    // This block here is unique to rules
    // If the current rule is algebraic we can't lookup it's ID
    // because rules do not define anything, they simply give a dynamic way to calculate a 
    // predefined thing we don't do any replacement through the model. However, the user may want 
    // to "replace" the current rule with the new one they've created, or just add the rule as a
    // new rule, and they can do either as an option here.
    
    // if the rule is algebraic and it's changed (no point if it hasn't changed)
    if ( (inNew->isAlgebraic() ) && (inNew->getFormula() != inNew_copy->getFormula()) ){
      
      cout << "Do you want this new rule to replace the original one? i.e. replace " << endl
 	   << inNew->getFormula() << endl << " ---- with ---- " << endl 
	   << inNew_copy->getFormula() << ")?" << endl;
      
      if ('Y' == yes_or_no()){

	// remove* functions remove an item from the mode, and return a pointer. It's then our
	// responsibility to delete it to avoid memory leaks
	Rule* toDel = model_new->removeRule(location);
	delete toDel;
      }
      
      // either way, we add inNew_copy to the
      model_new->addRule(inNew_copy);
    }
    
    // if the rule is not algebrai
    else {
      
      cout << "Do you want this new rule to replace the original one? i.e. replace " << endl
 	   << inNew->getFormula() << endl << " ---- with ---- " << endl 
	   << inNew_copy->getFormula() << ")?" << endl;
      
      if ('Y' == yes_or_no()){
	Rule* toDel = model_new->removeRule(location);
	delete toDel;
      }
      
      model_new->addRule(inNew_copy);
    }
    
    // we delete this because the 
    delete inNew_copy;
  
    
    operation++;
  }
 
}

//
// Returns the number corresponding to the rule defined by the search_target's formula in the 
// model_new. Is essentially a rule lookup where, instead of ID, the formula is used, which is 
// critical as algebraic rules don't have an ID
// the int can be used by getRule and removeRule
//
int SBML_integrate_integrate::rule_by_formula(Rule* search_target){
  int i = 0, num = model_new->getNumRules();
  
  Rule* temp;
  
  for (;i < num;i++){

    temp = model_new->getRule(i);
    
    if (temp->getFormula() == search_target->getFormula())
      return i;
  }
  
  return -1;
}


// #############################################################################################
// INTEGRATE_CONSTRAINTS



void SBML_integrate_integrate::integrate_constraints(SBML_confInput& input_file, Model* model_new){    
  // not for now
}



// #############################################################################################
// INTEGRATE_REACTIONS

void SBML_integrate_integrate::integrate_reactions(SBML_confInput& input_file, Model* model_new, SBML_listpair_container<ListOfReactions>& listpair){    
  
  // reactions are a far more complicated structure than the other components, 
  // so we need a different approach for replacement

  int num = input_file.get_num_integrate_reactions();

  if (num == 0){
    nothing_to_integrate("reactions");
    return;
  }

  ListOfReactions* listA = input_file.get_integrateA_reactions();
  ListOfReactions* listB = input_file.get_integrateB_reactions();
  
  // for the MathML formula modification
  string message, output_string;
  
  // error string used where autoAbort method is called
  string error;
  string input_string;
    
  message.clear();
  
  Reaction* tempA;
  Reaction* tempB;
  Reaction* inNew;
  Reaction* inNew_copy;  
  
  print_header("Integrate reactions", true);
  cout  << "You are about to enter the integrate reactions loop. This is more indepth than other\nintegrate functions, as we have kinetic laws, names and formulas to edit/integrate,\nwhich may involve other species or parameters.\n\nPress enter to proceed" << endl;
  cin.ignore();

  
  for (int i = 0 ; i < num ; i++){
    tempA = listA->get(i);
    tempB = listB->get(i);
    
    inNew = model_new->getReaction(tempA->getId());
    
    // if we can't find tempA in the new model then print an error message and exit 
    if (inNew == NULL)
      autoAbort(((error.append("FATAL ERROR - unable to find ")).append(tempA->getId())).append(" in newModel..."));

    // create a deep copy to work on
    inNew_copy = inNew->clone();
    
    // Allows you to edit/select the key bits from inNewCopy and tempB
    edit_reaction(inNew, inNew_copy, tempB, i+1, num, listpair);
    
  }// end of for loop
  
  
}// end of method

// INTEGRATE_REACTIONS - helper function 
// ----------------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------------
//
// edit_reaction
//

void SBML_integrate_integrate::edit_reaction(Reaction* inNew, Reaction* inNew_copy, Reaction* tempB, int current, int total, SBML_listpair_container<ListOfReactions>& listpair){
  bool done = false;
  int AorBorC;
  char selector;
  string input_string, message;
  
  while (!done){
    system("clear");
  
    // This block displays an overview of the two reactions
    reaction_seperator(inNew_copy, tempB);
    cout << "[Reaction " << current << " of " << total << "]" << endl << endl;
    cout << "Reaction in model: " << endl;
    reactions_overview(inNew_copy);
    cout << "----------------------------------------" << endl;
    cout << "Reaction we're integrating into that model:" << endl;;
    reactions_overview(tempB);
    cout << "----------------------------------------" << endl;
    
    selector = edit_reaction_ui();
    
    // goes to main selection splashscreen
    
    switch(selector)
      {
	
	// Edit Name
      case '1':
	{
	  display_framework.list_reactions(model_new);
	  cout << "List of current reactions above;" << endl;

	  // Function which selects to either keep the name as it is, set it to the value
	  // of tempB, or create a new name entirly
	  AorBorC = display_framework.compare3way("Please select a new name", inNew_copy->getName(), tempB->getName(), "New name", false);
	      
	  if (AorBorC == 0){
	    // do nothing
	  }
	  
	  // set to tempB
	  if (AorBorC == 1){
	    inNew_copy->setName(tempB->getName());
	  }
	  
	  if (AorBorC == 2){
	    cout << "Please enter the new name for the reaction: ";
	    input_string = stringGet();
	    inNew_copy->setName(input_string);
	  }
	}
	
	break;
	
	// Edit formula
      case '2':
	{
	  edit_reaction_formula(inNew_copy, tempB);
	}
	break;
	
	// Edit Stoichiometry
      case '3':
	{
	  edit_stoichiometry(inNew_copy);
	}
	break;
	
	// Edit Modifiers
      case '4':
	{
	  edit_reaction_modifiers(inNew_copy);
	}
	break;
	
	// Edit kinetic law
      case '5':
	{
	  // To use template function must create pointer variables as opposed to
	  // just passing pointers directly - template type is T&, not T*
	  KineticLaw* inNew_copy_KL = inNew_copy->getKineticLaw();
	  KineticLaw* tempB_KL = tempB->getKineticLaw();
	    
	  message.clear();
	  message.append("Please consult the SBML documentation regarding allowed KineticLaw semantics.\n");
	  compare_and_edit_maths("Edit kinetic law", inNew_copy_KL , tempB_KL,  message); 
	}
	break;
	
	// get model info
      case '6':
	{
	  string message = "This does not include any changes done on this reaction,\nas they are not yet saved to the model";
	  display_framework.select_components_to_list(model_new, message);
	}
	break;
	
	// Save and continue with this reaction
      case '7':
	{
	  replacement_list_update(inNew, inNew_copy, tempB, listpair.get_listA(), listpair.get_listB(), listpair.get_num());
	  done = true;
	}
	  
      } // end of switch
    
        // reloop unless done==true
  }
  
  // exit
}

// INTEGRATE_REACTIONS - helper function 
// ----------------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------------
//
// edit_reaction_ui
//

char SBML_integrate_integrate::edit_reaction_ui(){
  char* selector;
  string line;
  
  
  cout << endl << " Please select an option" << endl;
  cout << "[1] ----------- Edit Name\n[2] ----------- Edit Formula\n[3] ----------- Edit Stoichiometry\n[4] ----------- Edit Modifiers\n[5] ----------- Edit Kinetic Law\n[6] ----------- Get model Information\n[7] ----------- Continue " << endl;
  
  cout << "Select: ";
  
  while (true){
    
    selector = selectorGet();
    
    cout << "Selector is " << selector[0] << endl;
    
    switch (selector[0]){
    case ('1'):
      delete selector;
      return '1';
      
    case ('2'):
      delete selector;
      return '2';
      
    case ('3'):
      delete selector;
      return '3';
      
    case ('4'):
      delete selector;
      return '4';  
      
    case ('5'):
      delete selector;
      return '5';
      
    case ('6'):
      delete selector;
      return '6';   

    case ('7'):
      delete selector;
      return '7';   
      
    default:
      cout << "Not a valid selection, please select again: ";
    }
  }
}

  
// INTEGRATE_REACTIONS - helper function 
// ----------------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------------
//
// reaction_seperator
//

void SBML_integrate_integrate::reaction_seperator(const Reaction* tempA, const Reaction* tempB){
  string message, output_string;
  
  message.clear();
  output_string.clear();
  
  // preamble, defining operation number to log_stream 
  log_stream << "[" << operation << "] Reaction integration: A(";
  log_stream << tempA->getId() << ") and B(" << tempB->getId() << ")" << endl;
    
  // Build a header string
  (((message.append("Comparing ")).append(tempA->getId())).append( " and ")).append(tempB->getId());
  
  cout << output_string.append(message.length(), '#') << endl;
  cout << message << endl;
}



// INTEGRATE_REACTIONS - helper function 
// ----------------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------------
//
// reactions_overview
//

void SBML_integrate_integrate::reactions_overview(const Reaction* reaction){

  const KineticLaw* klaw;
  klaw = reaction->getKineticLaw();
  
  
  cout << "ID: " << reaction->getId() << endl;
  
  cout << "    Name:          ";
  if (reaction->getName() != ""){
    cout << reaction->getName()  << endl;
  }
  
  else{
    cout << "[NONE DEFINED]" << endl;
  }
  
  // Display formula
  cout << "    Formula:       ";
  display_framework.output_reaction_formula(reaction);
  cout << endl;
  
  // Display modifers
  cout << "    Rxn modifiers: ";
  display_framework.output_reaction_modifiers(reaction);
  cout << endl;
  
  // display kinetic law
  cout << "    Kinetic Law:   " << klaw->getFormula() << endl;
  
  // warn if local parameters are used!
  if (klaw->getNumLocalParameters() > 0){
    cout << "WARNING - This reaction uses local parameters! This is currently not supported!\nPlease refactor your model so these become global parameters" << endl;
    log_stream << "WARNING - This reaction uses local parameters! This is currently not supported!\nPlease refactor your model so these become global parameters" << endl;
  }
  
}


// INTEGRATE_REACTIONS - helper function 
// ----------------------------------------------------------------------------------------
//
// edit_reaction_formula
//

void SBML_integrate_integrate::edit_reaction_formula(Reaction* inNew_copy, Reaction* tempB){
  
  int AorB;
  
  // compare ensures AorB will be 0 or 1 only!
  AorB = display_framework.compare("Reactants or Products?", "Edit Reactants","Edit Products", false); 

  if (AorB == 0)
    edit_reaction_formula_reactants(inNew_copy, tempB);
  else
    edit_reaction_formula_products(inNew_copy, tempB);
  
}

// INTEGRATE_REACTIONS - helper function 
// ----------------------------------------------------------------------------------------
//
// edit_reaction_formula_reactants
//

void SBML_integrate_integrate::edit_reaction_formula_reactants(Reaction* inNew_copy, Reaction* tempB){
  
  char selector = 'Y';
  bool first = true;
  
  // clear the screen!
  system("clear");
  
  cout << "##### EDIT REACTANTS #####" << endl;
  cout << "Reaction in current model is " << inNew_copy->getId() 
       << ", while you are integrating " << tempB->getId() << " into this model" << endl;
  while (true){

    // Display the reactants in each of the reactions
    display_framework.list_reaction_species(0, inNew_copy);
    display_framework.list_reaction_species(0, tempB);
    
    // if it's not the first run through the loop
    if (!first){
      cout << "Do you wish to finish editing reactants?" << endl;
      selector = yes_or_no();
      if (selector == 'Y')
	break;
      else
	selector = 'N';
    }

    // if this is the first run through then we ensure future loops are recognized as not
    // the first
    else
      first = false;
    
    while (selector == 'Y'){
      cout << "Do you wish to add a reactant?" << endl;
      selector = yes_or_no();
      if (selector == 'Y')
	add_speciesRef(inNew_copy, tempB, true);
    }
    
    // reset selector
    selector = 'Y';
    
    while (selector == 'Y'){
      cout << "Do you wish to remove a reactant?" << endl;
      selector = yes_or_no();
      if (selector == 'Y')
	remove_speciesRef(inNew_copy, true);
    }
  }
  
}

// INTEGRATE_REACTIONS - helper function 
// ----------------------------------------------------------------------------------------
//
// edit_reaction_formula_products
//

void SBML_integrate_integrate::edit_reaction_formula_products(Reaction* inNew_copy, Reaction* tempB){
  
  char selector = 'Y';
  bool first = true;
  
  // clear the screen!
  system("clear");
  
  cout << "##### EDIT PRODUCTS #####" << endl;
  cout << "Reaction in current model is " << inNew_copy->getId() 
       << ", while you are integrating " << tempB->getId() << " into this model" << endl;
  while (true){

    // Display the products in each of the reactions
    display_framework.list_reaction_species(1, inNew_copy);
    display_framework.list_reaction_species(1, tempB);
    
    // if it's not the first run through the loop
    if (!first){
      cout << "Do you wish to finish editing products?" << endl;
      selector = yes_or_no();
      if (selector == 'Y')
	break; // exit the while loop
      else
	selector = 'Y'; // reset so we enter the add product while loop bellow
    }
    else
      first = false;
    
    // add product while loop
    while (selector == 'Y'){
      cout << "Do you wish to add a product?" << endl;
      selector = yes_or_no();
      if (selector == 'Y')
	add_speciesRef(inNew_copy, tempB, false);
    }
    
    // reset selector to enter product while loop below
    selector = 'Y';
    
    // remove product while loop
    while (selector == 'Y'){
      cout << "Do you wish to remove a product?" << endl;
      selector = yes_or_no();
      if (selector == 'Y')
	remove_speciesRef(inNew_copy, false);
    }
  }
}



// INTEGRATE_REACTIONS - helper function 
// ----------------------------------------------------------------------------------------
//
// add_speciesRef
//

void SBML_integrate_integrate::add_speciesRef(Reaction* inNew_copy, Reaction* tempB, bool reactant){
  
  Species* test;
  double input;
  //string name; 
  
  // Add from tempB's  list?
  cout << "Add from " << tempB->getId() << " list?" << endl;

  // Adding from tempB's list
  if ('Y' == yes_or_no()){
    
    cout << "Which number in the list?: ";
    
    if (reactant)
      input = doubleGet(0, tempB->getNumReactants());
    
    else 
      input = doubleGet(0, tempB->getNumProducts()-1);
    
    // check for input value (defensive programming)
    if (input == c_FAIL_DOUBLEGET){
      cout << "**** Invalid input ***" << endl;
      return;
    }
    
    // add reacant
    if (reactant){
      
      // Check that the species defined in tempB is actually present in the model
      
      test = model_new->getSpecies(tempB->getReactant(input)->getSpecies());
      
      if (test == NULL){
	cout << "This species is not present in the model. Please select it for import, or select another species." << endl;
	log_stream << "Tried to import " << (tempB->getReactant(input))->getSpecies() << " into reaction " << inNew_copy->getId() << ", but that species is not found in model_new" << endl;
	return;
      }
      
      // if we get here it's all good
      inNew_copy->addReactant(tempB->getReactant(input));
      
      cout << "Added reactant: " << tempB->getReactant(input)->getSpecies() << endl;
    }
    
    // add product
    else {
      
      // Check that the species defined in tempB is actually present in the model
      Species* test = model_new->getSpecies((tempB->getReactant(input))->getSpecies() );
      
      if (test == NULL){
	cout << "This species is not present in the model. Please select it for import, or select another species." << endl;
	log_stream << "Tried to import " << (tempB->getProduct(input))->getSpecies() << " into reaction " << inNew_copy->getId() << ", but that species is not found in model_new" << endl;
	return;
      }
      
      // if we get here it's all good
      inNew_copy->addProduct(tempB->getProduct(input));
      cout << "Added product: " << (tempB->getReactant(input))->getSpecies() << endl;
    }
    return;
  }
  // If we get here, means we're importing a species from model_new's list of species into
  // the reactant/product list of inNew_copy
  
  else {
    cout << "--------------------------------------------------------------"  << endl
	 << "--------------------------------------------------------------" << endl;
    
    // display all the possible species we could chose to add
    display_framework.list_species(model_new);
    cout << "Above is a list of species, please select a number from the list to add to the";
    if (reactant)
      cout << "reactants list: ";
    else
      cout << "products list: ";

    input = doubleGet(0, model_new->getNumSpecies());
    if (input == c_FAIL_DOUBLEGET){
      cout << "**** Invalid input **** - Failed to add reactant" << endl;
      return;
    }
    
    if (reactant){
      inNew_copy->addReactant(species2SpeciesReference((model_new->getSpecies(input)), inNew_copy));
      cout << "Added reactant: " << (model_new->getSpecies(input))->getId() << endl;
    }
    
    else {
      inNew_copy->addProduct(species2SpeciesReference((model_new->getSpecies(input)),inNew_copy));
      cout << "Added product: " << (model_new->getSpecies(input))->getId() << endl;
    }
  }
  
}

// INTEGRATE_REACTIONS - helper function 
// ----------------------------------------------------------------------------------------
//
// remove_speciesRef
//

void SBML_integrate_integrate::remove_speciesRef(Reaction* rxn, bool reactant){
  double input;
  SpeciesReference* reactant_p;
  
  if (reactant) {
    display_framework.list_reaction_species(0, rxn);
    cout << "Select the reaction (number) you wish to remove): ";
    input = doubleGet(0, rxn->getNumReactants());
  }
  else {
    display_framework.list_reaction_species(1, rxn);
    cout << "Select the product (number) you wish to remove): ";
    input = doubleGet(0, rxn->getNumProducts());
  }
  
  // check input
  if (input == c_FAIL_DOUBLEGET){
    cout << "**** Invalid input ****" << endl;
    return;
  }
  
  // remove reactant
  if (reactant){
    reactant_p = rxn->removeReactant(input);
    cout << "Removed reactant: " << reactant_p->getSpecies() << endl;
  }
  
  // remove product
  else{
    reactant_p = rxn->removeProduct(input);
    cout << "Removed product: " << reactant_p->getSpecies() << endl;
  }
  
  // delete data pointed to by reactant_p
  delete reactant_p;
}

// INTEGRATE_REACTIONS - helper function 
// ----------------------------------------------------------------------------------------
//
// edit_reaction_modifiers
//

void SBML_integrate_integrate::edit_reaction_modifiers(Reaction* inNew_copy){
  
  int AorB;
  double input;
  
  display_framework.list_reaction_species(2, inNew_copy);
  
  AorB = display_framework.compare("Add or remove modifiers", "Add modifier","Remove Modifier", false); 
  
  if (AorB == 0){
    
    // list all the possible specices you could add
    display_framework.list_species(model_new);
    
    while (true) {
      
      cout << "Select a species to add as a modifier: ";
      input = doubleGet(0, model_new->getNumSpecies()-1);
      
      if (0 == inNew_copy->addModifier(species2ModifierSpeciesReference(model_new->getSpecies(input), inNew_copy))){
	cout << "Do you wish to add another modifier?" << endl;
	if ('N' == yes_or_no())
	  break;
      }
      
      else
	cout << "Please reselect: ";
      
    }
  }
 
  else {
    display_framework.list_reaction_species(2, inNew_copy);
    if (inNew_copy->getNumModifiers() == 0){
      cout << "No modifiers to remove. Press enter to proceed.";
      cin.get();
      cin.ignore(100, '\n');
      
      return;
    }
      
    while (true){
      cout << "Select a species to remove as a modifier: ";
      input = doubleGet(0, inNew_copy->getNumModifiers()-1);
      ModifierSpeciesReference* toDelete = inNew_copy->removeModifier(input);
      
      if (toDelete != NULL){
	cout << "Removed modifier " << toDelete->getSpecies() << " from reaction " 
	     << inNew_copy->getId() << endl;
	
	delete toDelete;
	cout << "Do you wish to remove another modifier?" << endl;
	if ('N' == yes_or_no())
	  break;
      }
      else {
	cout << "**** Invalid selection ****" << endl;
	cout << "Do you wish to remove another modifier?" << endl;
	if ('N' == yes_or_no())
	  break;
	cout << "Please reselect: ";
      }
    }
  }
}

// INTEGRATE_REACTIONS - helper function 
// ----------------------------------------------------------------------------------------
//
// edit_reaction_modifiers
//

void SBML_integrate_integrate::edit_stoichiometry(Reaction* inNew_copy){
  int items = inNew_copy->getNumReactants() + inNew_copy->getNumProducts();
  int num_reactants = inNew_copy->getNumReactants();
  int num_products = inNew_copy->getNumProducts();
  int counter = 0;
  double selector, new_val;
  SpeciesReference* temp;
  
  cout << "Reactants ------" << endl;
  for (int i = 0 ; i < num_reactants ; i++){
    
    temp = inNew_copy->getReactant(i);
    
    cout << "[" << counter << "] " << temp->getStoichiometry() << "-" << temp->getSpecies() << endl;
    counter++;
  }
  
  cout << "Products  ------" << endl;
  for (int i = 0 ; i < num_products ; i++){

    temp = inNew_copy->getProduct(i);
    
    cout << "[" << counter << "] " << temp->getStoichiometry() << "-" << temp->getSpecies() << endl;
    counter++;
  }
  
  while (true){
    
    cout << "Please select a number for a species you wish to alter to stoichiometry of: ";
    selector = doubleGet(0, items);

    if (selector == c_FAIL_DOUBLEGET){
      cout << "**** Invalid selection ****\nDo you wish to reselect another element?" << endl;
      if ('N' == yes_or_no())
	return;
      cout << "Please reselect a value: ";
    }
  
    else if (selector >= num_reactants){
      cout << "What would you like to edit the stoichiometry of " << inNew_copy->getProduct(selector-num_reactants)->getSpecies() << " to?: ";
      
      new_val = doubleGet(0,100);
      if (new_val == c_FAIL_DOUBLEGET){
	cout << "**** Invalid Selection ****\n"<< new_val << " is invalid (if you require over 100 then sozzle...)" << endl;
      }
      else{
	(inNew_copy->getProduct(selector-num_reactants))->setStoichiometry(new_val);
	cout << "Edit another species?" << endl;;
	if ('N' == yes_or_no())
	  return;	  
      }
    }
      
    else {
      cout << "What would you like to edit the stoichiometry of " << inNew_copy->getReactant(selector)->getSpecies() << " to?: ";
      
      // get number
      new_val = doubleGet(0,100);
      
      if (new_val == c_FAIL_DOUBLEGET){
	cout << "**** Invalid Selection ****\n"<< new_val << " is invalid (if you require over 100 then sozzle...)" << endl;
      }
      
      else{
	(inNew_copy->getReactant(selector))->setStoichiometry(new_val);
	cout << "Edit another species?" << endl;
	if ('N' == yes_or_no())
	  return;
      }
    }
  }
}


// INTEGRATE_REACTIONS - helper function 
// ----------------------------------------------------------------------------------------
//
// replacement_list_update
//

void SBML_integrate_integrate::replacement_list_update(Reaction* inNew, Reaction* inNew_copy, 
						       Reaction* tempB, 
						       ListOfReactions* rep_reactionsA, 
						       ListOfReactions* rep_reactionsB, 
						       int& rep_reactions_num){
  
  int AorB;
  
  AorB = display_framework.compare("Is this reaction", "A totally new reaction?","Simply an improvement to an existing one which was already in modelA?", false); 

  // IF - this is a totally new reaction -----------------------------------------
  if (AorB == 0){
    
    new_ID_message("reaction");
    display_framework.list_reactions(model_new);
    cout << endl;
      
    cout << "New ID is : ";
    string newID;
    newID = stringGet();
      
    if (0 != inNew_copy->setId(newID))
      autoAbort("WARNING - New ID was not accepted, this was probably a formatting error due to the selected ID. Aborting...");
	
    // addReaction (used below) makes a copy, so we must delete the original 
    // (inNew_copy) to avoid a memory leak. Do this at the end of the method.
    logfile_add_message(model_new->addReaction(inNew_copy), 
			inNew_copy->getId(), 
			"model_new reactions");
  }
  
  // ELSE - this is just improving an existing parameter in newModel -------------------
  else {
    // remove the original from the model
    model_new->removeReaction(inNew->getId());
      
    // replace by adding in the inNew_copy, and delete the original inNew_copy
    // (a copy generated and added to the model)
    logfile_add_message(model_new->addReaction(inNew_copy), inNew_copy->getId(), "model_new reactions");
    
    // delete original (memory management) - removeReaction returns a pointer to the removed
    // element, though obviously in this case we already have a pointer in inNew
    delete inNew;
  }
  
  // used in logstream
  operation++;
  
  // for_replacement enters a UI where we decided if we want to replace references to
  // tempB with references to inNew_copy
  if (1 == for_replacement_UI(inNew_copy->getId(), tempB->getId()))  
    {
      
      // replace any reference in the model_new to tempB with references to inNew_copy
      cleanup_framework->replace(tempB, inNew_copy);
      
      // add these values to the replacement lists for later updates
      rep_reactionsA->append(tempB);
      rep_reactionsB->append(inNew_copy);
      
      // update the counter
      rep_reactions_num++;
      
    }
  
  // now we can finally delete inNew_copy
  delete inNew_copy;
}
  


// #############################################################################################
// INTEGRATE_EVENTS

void SBML_integrate_integrate::integrate_events(SBML_confInput& input_file, Model* model_new, SBML_listpair_container<ListOfEvents>& listpair){           
  // not for now
}

// Helper function called by above
void SBML_integrate_integrate::replacement_list_update(Event* inNew_copy, Event* tempB, 
							 ListOfEvents* rep_eventsA, 
						       ListOfEvents* rep_eventsB, 
							 int& rep_events_num){
  
  // for_replacement enters a UI where we decided if we want to replace references to
  // tempB with references to inNew_copy
  if (1 == for_replacement_UI(inNew_copy->getId(), tempB->getId()))  
    {
      // replace any reference in the model_new to tempB with references to inNew_copy
      cleanup_framework->replace(tempB, inNew_copy);
      
      // add these values to the replacement lists for later updates
      rep_eventsA->append(tempB);
      rep_eventsB->append(inNew_copy);
      
      // update the counter
      rep_events_num++;
    }
  
}


// #############################################################################################
// NEW_ID_MESSAGE
// Prints a standard message regarding selecting a newID
//
void SBML_integrate_integrate::new_ID_message(std::string item){
  
  cout << "Unless you specifically add things in these integrations, nothing in the model will refer to this (" 
       << item << ") because it is brand new to both models!" << endl;
      
  cout << "Please define an ID for it! This ID needs to be globally unique, so to test if it's \nunique please check in the .xml file. An automated software fix for this is *JUST* \naround the corner! Sorry about this" << endl 
       << "Currently, the existing " << item << " IDs are:" << endl;
  
}

// #############################################################################################
// FOR_REPLACEMENT
//
// General UI function which gives the user the option to remove references throughout the model
// to the element originating from modelB and replace those references with those to the newly
// created element (be-it a brand new element, or an update to an existing one).
// 
// This update is done by the replacement_list_update function, which is specific to each element
// type and so can be found below the integrate_* methods above.
// 
int SBML_integrate_integrate::for_replacement_UI(string newID, string oldBID){
  
  char decision;
  cout << endl << "### Change references? ###" << endl;
  cout << "Would you like references to " << oldBID 
       << ", the ID of the element\njust integrated into " 
       << newID << " to be replaced by\nthe newly updated/created species? (" 
       << newID << ")" << endl << endl;

  decision = yes_or_no();

  if (decision == 'Y')
    return 1;
  else
    return 0;
}




