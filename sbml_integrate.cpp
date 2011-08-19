#include "sbml_display.h"
#include "sbml_search.h"
#include "sbml_integrate.h"
#include "sbml_formatter.h"

#include <sbml/SBMLTypes.h>
#include <string>
#include <iostream>


// #############################################################################################
// constants and static variables
const string c_FROMB = "_fromB";
bool SBML_integrate::init_called = false;
// c_FAIL_DOUBLEGET is static variable in formatter, which for all intents and purposes is a 
// software wide global constant;

using namespace std;



// #############################################################################################
//
// Constructor
//

SBML_integrate::SBML_integrate(const Model* input_A, const Model* input_B, const char* _input_A_filename, const char* _input_B_filename)
{
  
  // init allows the user to select which of the two files should make up the base model (and
  // by implication, which will be the import model).
  if (init(_input_A_filename, _input_B_filename) == 1){
    model_A = input_A;
    model_new = input_A->clone();
    model_B = input_B->clone();
    model_B_original = input_B;

    // Adds "_fromB" to the end of all the IDs in model_B. In later editions we may offer 
    // customizability regarding this suffix, but for now it's not necessary.
    SBML_augment augmentation_framework(model_B);
    augmentation_framework.complete_model_id_rename_with_append("_fromB");
    
    // set filenames for future reference
    model_A_filename = _input_A_filename;
    model_B_filename = _input_B_filename;
  }
  
  // if not (input_B has the most components) then a copy of input_B is the clone
  else {
    model_A = input_B;
    model_new = input_B->clone();
    model_B = input_A->clone();
    model_B_original = input_A;
    
    SBML_augment augmentation_framework(model_B);
    augmentation_framework.complete_model_id_rename_with_append("_fromB");

    model_A_filename = _input_B_filename;
    model_B_filename = _input_A_filename;
  }
  
  input_file.import_data(model_A, model_B, "");
  
  cleanup_framework = new SBML_cleanup(model_new, false);

  // counter for log keeping
  operation = 0;

  // Initialize the replacement containers based on the config file.
  // Rather than keeping replacement data within the configuration data class, we import it
  // here into the SBML_integrate parent class. This is because this data is frequently updated
  // by the integration process (items added to the replacement lists).
  
  functionDefinitions_rep_container.set_listA(input_file.get_replaceA_functionDefinitions());
  functionDefinitions_rep_container.set_listB(input_file.get_replaceB_functionDefinitions());
  functionDefinitions_rep_container.set_num(input_file.get_num_replace_functionDefinitions());
  
  unitDefinitions_rep_container.set_listA(input_file.get_replaceA_unitDefinitions());
  unitDefinitions_rep_container.set_listB(input_file.get_replaceB_unitDefinitions());
  unitDefinitions_rep_container.set_num(input_file.get_num_replace_unitDefinitions());

  compartments_rep_container.set_listA(input_file.get_replaceA_compartments());
  compartments_rep_container.set_listB(input_file.get_replaceB_compartments());
  compartments_rep_container.set_num(input_file.get_num_replace_compartments());

  species_rep_container.set_listA(input_file.get_replaceA_species());
  species_rep_container.set_listB(input_file.get_replaceB_species());
  species_rep_container.set_num(input_file.get_num_replace_species());
  
  parameters_rep_container.set_listA(input_file.get_replaceA_parameters());
  parameters_rep_container.set_listB(input_file.get_replaceB_parameters());
  parameters_rep_container.set_num(input_file.get_num_replace_parameters());
  
  initialAssignments_rep_container.set_listA(input_file.get_replaceA_initialAssignments());
  initialAssignments_rep_container.set_listB(input_file.get_replaceB_initialAssignments());
  initialAssignments_rep_container.set_num(input_file.get_num_replace_initialAssignments());
 
  rules_rep_container.set_listA(input_file.get_replaceA_rules());
  rules_rep_container.set_listB(input_file.get_replaceB_rules());
  rules_rep_container.set_num(input_file.get_num_replace_rules());

  constraints_rep_container.set_listA(input_file.get_replaceA_constraints());
  constraints_rep_container.set_listB(input_file.get_replaceB_constraints());
  constraints_rep_container.set_num(input_file.get_num_replace_constraints());
  
  reactions_rep_container.set_listA(input_file.get_replaceA_reactions());
  reactions_rep_container.set_listB(input_file.get_replaceB_reactions());
  reactions_rep_container.set_num(input_file.get_num_replace_reactions());

  events_rep_container.set_listA(input_file.get_replaceA_events());
  events_rep_container.set_listB(input_file.get_replaceB_events());
  events_rep_container.set_num(input_file.get_num_replace_events());

  for (int i = 0 ; i < 10 ; i++){
    integration_done_array[i] = 0;
  }
  
}



// #############################################################################################
// init - UI function to determine which file acts as the base file
//
double SBML_integrate::init(const char* _input_A_filename, const char* _input_B_filename){

  double return_val;
  system("clear");
  
  if (init_called){
    autoAbort("ERROR - CANNOT call init() from the SBML_Integrate class more than once. Aborting...");
  }
  
  // set to true
  init_called = true;

  print_header("LOAD FILES", true);
  
  cout << "Which of these files should the BASE MODEL be based on? This is the model which forms the foundations of your integration model - i.e. it's copied over, and then you import, integrate and replace elements from the import model into the base model" << endl;
  
  while (true){
    cout << "[1] ------------ " << _input_A_filename << endl
	 << "[2] ------------ " << _input_B_filename << endl;
  
    cout  << "Please select: ";

    return_val = doubleGet(1,2);

    if(return_val != c_FAIL_DOUBLEGET)
      return return_val;
    
    invalid_selection();
  }
}



// #############################################################################################
// test function for debugging

void SBML_integrate::test(Model* retarded){
  
  import_elements();
  replace_elements();
  integrate_models();
}



// #############################################################################################
//
// integrate_models - main interactive integration interface 

void SBML_integrate::integrate_models(){
  
  double selector;
  SBML_integrate_integrate integration_framework(model_new);
  
  while (true){
    print_header("Integrate model", true);
    cout << endl;
    
    cout << "The software has selected that you are integrating " << model_B_filename 
	 << "(designated the impoort model, model ID " << model_B->getId() << ") into " 
	 << model_A_filename << "( designated the base mode, model ID " << model_A->getId() 
	 << "). " << endl;
    
    integrate_models_display_options();
    
    cout << "Please select an option: ";
    selector = doubleGet(1,15);

    while (selector == c_FAIL_DOUBLEGET){
      invalid_selection();
      cout << "Please reselect: ";
      selector = doubleGet(1,15);
    }
    
    switch (static_cast <int>(selector)){
      
     case 1:{
       integration_framework.integrate_functionDefinitions(input_file, model_new, 
							   functionDefinitions_rep_container);
       replace_elements();
       integration_done_array[0] = 1;
       break;
     }
      
     case 2: {
       integration_framework.integrate_unitDefinitions(input_file, model_new, 
						       unitDefinitions_rep_container);
       replace_elements();
       integration_done_array[1] = 1;
       break;
     }
      
    case 3:{
      integration_framework.integrate_compartments(input_file, model_new, 
						   compartments_rep_container);
      replace_elements();
      integration_done_array[2] = 1;
      break;
    }
      
    case 4:{
      integration_framework.integrate_species(input_file, model_new, species_rep_container);
      replace_elements();
      integration_done_array[3] = 1;
      break;
    }
      
    case 5:{
      integration_framework.integrate_parameters(input_file, model_new, parameters_rep_container);
      replace_elements();
      integration_done_array[4] = 1;
      
      break;
    }
      
    case 6:{
      integration_framework.integrate_initialAssignments(input_file, model_new);
      integration_done_array[5] = 1;
      
      break;
    }
      
    case 7:{
      integration_framework.integrate_rules(input_file, model_new);
      integration_done_array[6] = 1;
      
      break;
    }
      
    case 8:{
      integration_framework.integrate_constraints(input_file, model_new);
      integration_done_array[7] = 1;
      
      break;
    }
      
    case 9:{
      integration_framework.integrate_reactions(input_file, model_new, reactions_rep_container);
      replace_elements();
      integration_done_array[8] = 1;
      
      break;
    }
      
    case 10:{
      integration_framework.integrate_events(input_file, model_new, events_rep_container);
      replace_elements();
      integration_done_array[9] = 1;
      break;
    }
      
    case 11:
      integrate_models_explore_models();
      
      break;

    case 12:
      integrate_models_explore_parameters();
      
      break;

    case 13:
      cout << "Please enter a filename (remember the .xml extension): ";
      write_to_file(model_new, stringGet());
      break;
       
    case 14:
      replace_elements();
      
      break;      

    case 15:
      return;
      break;       
    }
  }
}



// #############################################################################################
//
// display options for integrate_elements

void SBML_integrate::integrate_models_display_options(){
  cout << "[1] ------------ Integrate Function Definitions (" 
       << input_file.get_num_integrate_functionDefinitions() << ")";
  if (integration_done_array[0])
    cout << " (DONE)";
  cout << endl;
  
  cout << "[2] ------------ Integrate Unit Definitions ("
       << input_file.get_num_integrate_unitDefinitions() << ")    ";
  if (integration_done_array[1])
    cout << " (DONE)";
  cout << endl;
  
  cout << "[3] ------------ Integrate Compartments ("
       << input_file.get_num_integrate_compartments()<< ")        ";
  if (integration_done_array[2])
    cout << " (DONE)";
  cout << endl;
  
  cout << "[4] ------------ Integrate Species ("
       << input_file.get_num_integrate_species()<< ")             ";
  if (integration_done_array[3])
    cout << " (DONE)";
  cout << endl;
  
  cout << "[5] ------------ Integrate Parameters ("
       << input_file.get_num_integrate_parameters()<< ")          ";
  if (integration_done_array[4])
    cout << " (DONE)";
  cout << endl;
  
  cout << "[6] ------------ Integrate Initial Assignments ("
       << input_file.get_num_integrate_initialAssignments()<< ") ";
  if (integration_done_array[5])
    cout << " (DONE)";
  cout << endl;
  
  cout << "[7] ------------ Integrate Rules ("
       << input_file.get_num_integrate_rules() << ")               ";
  if (integration_done_array[6])
    cout << " (DONE)";
  cout << endl;
  
  
  cout << "[8] ------------ Integrate Constraints ("
       << input_file.get_num_integrate_constraints() << ")         ";
  if (integration_done_array[7])
    cout << " (DONE)";
  cout << endl;
  
  cout << "[9] ------------ Integrate Reactions ("
       << input_file.get_num_integrate_reactions() << ")           ";
  if (integration_done_array[8])
    cout << " (DONE)";
  cout << endl;
  
  cout << "[10] ----------- Integrate Events ("
       << input_file.get_num_integrate_events() << ")              ";
  if (integration_done_array[9])
    cout << " (DONE)";
  cout << endl;
  
  cout << "[11] ----------- Explore models" << endl;
  cout << "[12] ----------- Explore replacement, import and integration parameters " << endl;
  cout << "[13] ----------- Write Integrated Model" << endl;
  cout << "[14] ----------- Run replacementl" << endl;
  cout << "[15] ----------- Return to main menu " << endl;
}



// #############################################################################################
//
// Function to select a model to implement the display_model function on

void SBML_integrate::integrate_models_explore_models(){
  int AorBorC;
  
  system("clear");
  
  cout << "There are three models we can look at in this system. The two you've selected to\nload into the program, and the integrated model you're creating.The integrated model\nis based on the bigger of the two models you're going to integrate, from here-on\nout called the 'base model." << endl << endl;

  cout << "------- Models and filenames -------------" << endl;
  cout << "Base model --------- " << model_A_filename << endl;
  cout << "Import model ------- " << model_B_filename << endl << endl;
  
  AorBorC = display_framework.compare3way("Please select a model to explore", "Base model", "Import model", "Integration model", false);
	
  if (AorBorC == 0)
    display_framework.select_components_to_list(model_A, "Base model - loaded model which the integration model is based on");
    
  if (AorBorC == 1)
    display_framework.select_components_to_list(model_B, "Import model - model being integrated into the base model to create the integration model");
  
  if (AorBorC == 2)
    display_framework.select_components_to_list(model_new, "Integration model - model being created");
  
}



// #############################################################################################
//
// Display the import, replacement and integration parameters

void SBML_integrate::integrate_models_explore_parameters(){
  system("clear");

  // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
  cout << "------- Number of items to replace -------" << endl;
  cout << " The folowing data shows the number of items defined the in the integrate.conf\nfile which are to be replaced in the integrated model" << endl;
  cout << "Function definitions = " << functionDefinitions_rep_container.get_num() << endl;
  cout << "Unit definitions = " << unitDefinitions_rep_container.get_num() << endl;
  cout << "Compartments = " << compartments_rep_container.get_num() << endl;
  cout << "Species = " << species_rep_container.get_num() << endl;
  cout << "Parameters = " << parameters_rep_container.get_num() << endl;
  cout << "Initial assignments = " << initialAssignments_rep_container.get_num() << endl;
  cout << "Rules = " << rules_rep_container.get_num() << endl;
  cout << "Constraints = " << constraints_rep_container.get_num() << endl;
  cout << "Reactions = " << reactions_rep_container.get_num()  << endl;
  cout << "Events = " << events_rep_container.get_num() << endl;
  cout << "------------------------------------------------" << endl;

  any_key_to_continue();
  system("clear");
  
  // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
  cout << "------- Number of items to import -------" << endl;
  cout << " The folowing data shows the number of items defined the in the integrate.conf\nfile which are to be imported into the integrated model" << endl;
  cout << "Function definitions = " 
       << input_file.get_num_import_functionDefinitions() << endl;
  cout << "Unit definitions = " 
       << input_file.get_num_import_unitDefinitions() << endl;
  cout << "Compartments = " 
       << input_file.get_num_import_compartments() << endl;
  cout << "Species = " 
       << input_file.get_num_import_species() << endl;
  cout << "Parameters = " 
       << input_file.get_num_import_parameters() << endl;
  cout << "Initial assignments = " 
       << input_file.get_num_import_initialAssignments() << endl;
  cout << "Rules = " 
       << input_file.get_num_import_rules() << endl;
  cout << "Constraints = " 
       << input_file.get_num_import_constraints() << endl;
  cout << "Reactions = " 
       << input_file.get_num_import_reactions() << endl;
  cout << "Events = " 
       << input_file.get_num_import_events() << endl;
  cout << "------------------------------------------------" << endl;
  
  any_key_to_continue();
  system("clear");
  cout << endl;
   
  cout << "------- Number of items to integrate -------" << endl;
  cout << " The folowing data shows the number of items defined the in the integrate.conf\nfile which are to be integrated from the imort model into the integrated model" << endl;
  cout << "Function definitions = " 
       << input_file.get_num_integrate_functionDefinitions() << endl;
  cout << "Unit definitions = " 
       << input_file.get_num_integrate_unitDefinitions() << endl;
  cout << "Compartments = " 
       << input_file.get_num_integrate_compartments() << endl;
  cout << "Species = " 
       << input_file.get_num_integrate_species() << endl;
  cout << "Parameters = " 
       << input_file.get_num_integrate_parameters() << endl;
  cout << "Initial assignments = " 
       << input_file.get_num_integrate_initialAssignments() << endl;
  cout << "Rules = " 
       << input_file.get_num_integrate_rules() << endl;
  cout << "Constraints = " 
       << input_file.get_num_integrate_constraints() << endl;
  cout << "Reactions = " 
       << input_file.get_num_integrate_reactions() << endl;
  cout << "Events = " 
       << input_file.get_num_integrate_events() << endl;
  cout << "------------------------------------------------" << endl;
  
  any_key_to_continue();
  system("clear");
}



// #############################################################################################
//
// Parent function that calls replacement functions for each of the ten lists from the 
// integrate_replace class
// 

void SBML_integrate::replace_elements(){
  log_stream << endl << "REPLACING OPERATIONS" << endl;
  
  SBML_integrate_replace replacement_framework;
  
  // Function Definitions
  replacement_framework.replace_elements<SBML_listpair_container<ListOfFunctionDefinitions>, ListOfFunctionDefinitions>(model_new, functionDefinitions_rep_container, 0);

  // Unit Definitions
  replacement_framework.replace_elements<SBML_listpair_container<ListOfUnitDefinitions>, ListOfUnitDefinitions>(model_new, unitDefinitions_rep_container, 0);
  
  // Compartment
  replacement_framework.replace_elements<SBML_listpair_container<ListOfCompartments>, ListOfCompartments>(model_new, compartments_rep_container, 0);
  
  // Species
  replacement_framework.replace_elements<SBML_listpair_container<ListOfSpecies>, ListOfSpecies>(model_new, species_rep_container, 0);

  // Parameters
  replacement_framework.replace_elements<SBML_listpair_container<ListOfParameters>, ListOfParameters>(model_new, parameters_rep_container, 0);

  // InitialAssignment
  replacement_framework.replace_elements<SBML_listpair_container<ListOfInitialAssignments>, ListOfInitialAssignments>(model_new, initialAssignments_rep_container, 0);
  
  // Rules
  replacement_framework.replace_elements<SBML_listpair_container<ListOfRules>, ListOfRules>(model_new, rules_rep_container, 0);
  
  // Constraints
  replacement_framework.replace_elements<SBML_listpair_container<ListOfConstraints>, ListOfConstraints>(model_new, constraints_rep_container, 0);
  
  // Reactions
  replacement_framework.replace_elements<SBML_listpair_container<ListOfReactions>, ListOfReactions>(model_new, reactions_rep_container, 0);
  
  // Events
  replacement_framework.replace_elements<SBML_listpair_container<ListOfEvents>, ListOfEvents>(model_new, events_rep_container, 0);
}



// #############################################################################################
//
// Parent function that calls import functions for each of the ten lists from the 
// integrate_import class
// 

void SBML_integrate::import_elements(){
  log_stream << endl << "IMPORTING OPERATIONS" << endl;
    
  SBML_integrate_import import_framework;

  import_framework.import_unitDefinitions(model_new, 
					  input_file.get_num_import_unitDefinitions(), 
					  input_file.get_import_unitDefinitions());
  
  import_framework.import_functionDefinitions(model_new, 
					      input_file.get_num_import_functionDefinitions(), 
					      input_file.get_import_functionDefinitions());
  
  import_framework.import_compartments(model_new, 
				       input_file.get_num_import_compartments(), 
				       input_file.get_import_compartments());
  
  import_framework.import_species(model_new, 
				  input_file.get_num_import_species(), 
				  input_file.get_import_species());
  
  import_framework.import_parameters(model_new, 
				     input_file.get_num_import_parameters(), 
				     input_file.get_import_parameters());
  
  import_framework.import_initialAssignments(model_new, 
					     input_file.get_num_import_initialAssignments(), 
					     input_file.get_import_initialAssignments());
  
  import_framework.import_rules(model_new, 
				input_file.get_num_import_rules(), 
				input_file.get_import_rules());

  import_framework.import_constraints(model_new, 
				      input_file.get_num_import_constraints(), 
				      input_file.get_import_constraints());

  import_framework.import_reactions(model_new, 
				    input_file.get_num_import_reactions(), 
				    input_file.get_import_reactions());
  
  import_framework.import_events(model_new, 
				 input_file.get_num_import_events(), 
				 input_file.get_import_events());

}












     
// #############################################################################################
// UNRETARDING_THE_PFIZER_MODEL 
//
//
// The kids at Pfizer made their p38 model in a really bizzare way, whereby instead of directly 
// defining a kinetic law in the aptly named "kinetic law" MathML structure, they reference a 
// parameter, which is defined by an assignment rule. While this *is* legal, COPASI, for example,
// doesn't let you do this for its import, and I suspect MATLAB might not appreciate it. 
// It also makes about half the model redundant - not sure if they were being paid by LOC for 
// the model, but whatever, it's arse.

//
// This function is a quickfix that doesn't actually remove the redundancy from the file, but 
// does from the model's logic, by moving the doubly-referenced assignment rule into the 
// kinetic parameter bit.
// 
// Cool.
// Note, this method is not related to this class (or this software!) in any way, I just needed 
// somewhere appropriate to put it and was working on this class at the time.

//Returns an unretarded version of the pfizer model
void SBML_integrate::unretarding_the_pfizer_model(Model* retarded_model){

  const ASTNode* formulanode;
  
  int num_rxns = retarded_model->getNumReactions();
  Reaction* temp_rxn;
  KineticLaw* klaw;
  string formula;
  
  
  for (int i = 0 ; i < num_rxns ;i++){
    temp_rxn = retarded_model->getReaction(i);
    klaw = temp_rxn->getKineticLaw();
    formula = klaw->getFormula();

    formula.resize(formula.length()-2);

    cout << "On reaction " << temp_rxn->getId() << " looking for " << formula << "..." << endl;

    formulanode = retarded_rules(retarded_model, formula);
    if (formulanode == NULL){
      autoAbort("Well this isn't good...");
    }
    
    klaw->setMath(formulanode);
  }

  
  SBMLDocument document(retarded_model->getLevel(), retarded_model->getVersion());

  document.setModel(retarded_model);

  const SBMLDocument* document_p = &document;
  
  SBMLWriter writer;

  cout << "Writing return value = " << writer.writeSBML(document_p,"p38_alex.xml" ) << endl;
  autoAbort("DONE");
  
}

const ASTNode* SBML_integrate::retarded_rules(Model* model, string formula){
  int num_rules = model->getNumRules();
  Rule* temp_rule;
  
  for (int i = 0 ; i<num_rules ; i++){
    temp_rule = model->getRule(i);
    
    if (temp_rule->getVariable() == formula)
      return temp_rule->getMath();
  }

  return NULL;
  
}
