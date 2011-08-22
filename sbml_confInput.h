// Copyright Alex Holehouse 2011
// Distributed under the terms of the GNU general public license - see COPYING.txt for more details

#ifndef SBML_CONFINPUT_H
#define SBML_CONFINPUT_H

#include "sbml_ui_general.h"
#include "sbml_integration_container.cpp"

#include <string>
#include <sbml/SBMLTypes.h>
#include <fstream>

/**
   \b <Overview>:

   SBML_confInput is the class which provides an API to the data stored in the .conf file (by default called integrate.conf). The information translated from this configuration file is stored in ten SBML_integration_container objects.  These are described in more detail in their documentation, but encompasse five ListOf* objects, where * is one of the ten SBML model element types. SBML_confInpit serves as an API to these containers, allowing a single interface to get the information needed to integrate two models together.
   
 **/

class SBML_confInput : public SBML_UI_general {
  
 public:
  SBML_confInput();
  
  /*! <b>Preconditions:</b> modelNew and modelB are valid SBML models, conf_file is the filename of a correctly formatted configuration file.
      
      <b>Postconditions:</b> Imports the data specified in the configuration file into this class. 
      Elements are stored in import, integrate and replace lists, with counters set to the number of elements in each of these lists. 

      <b>Notes: </b> The storage of elements in lists is infact an abstraction, and instead imported elements are stored on SBML_Integration_Container objects. 
      !*/
  
  
  bool import_data(const Model* modelNew, const Model* modelB, std::string conf_file);

  void test_function(const Model* modelB, const Model* modelA);
  
  // HUGE list of getter functions to be used by integrate
 

  /** Returns the number of functionDefinitions defined in the functionDefinition's "Import:" list in the .conf file.
   **/
  int get_num_import_functionDefinitions();
  
  /** Returns the number of unitDefinitions defined in the unitDefinition's "Import:" list in the .conf file.
   **/
  int get_num_import_unitDefinitions(); 
  
  /** Returns the number of compartments defined in the compartment's "Import:" list in the .conf file.
   **/
  int get_num_import_compartments();
  
  /** Returns the number of species defined in the species's "Import:" list in the .conf file.
   **/
  int get_num_import_species();
  
  /** Returns the number of parameters defined in the parameter's "Import:" list in the .conf file.
   **/
  int get_num_import_parameters();

  /** Returns the number of initialAssigments defined in the initialAssignments's "Import:" list in the .conf file.
   **/
  int get_num_import_initialAssignments();

  /** Returns the number of rules defined in the rule's "Import:" list in the .conf file.
   **/
  int get_num_import_rules();

  /** Returns the number of constraints defined in the contraint's "Import:" list in the .conf file.
   **/
  int get_num_import_constraints();

  /** Returns the number of reactions defined in the reaction's "Import:" list in the .conf file.
   **/
  int get_num_import_reactions();

  /** Returns the number of events defined in the event's "Import:" list in the .conf file.
   **/
  int get_num_import_events();

  
  
  int get_num_replace_functionDefinitions();

  int get_num_replace_unitDefinitions();

  int get_num_replace_compartments();

  int get_num_replace_species();

  int get_num_replace_parameters();

  int get_num_replace_initialAssignments();

  int get_num_replace_rules();

  int get_num_replace_constraints();

  int get_num_replace_reactions();

  int get_num_replace_events();
  
  


  int get_num_integrate_functionDefinitions();

  int get_num_integrate_unitDefinitions();

  int get_num_integrate_compartments();

  int get_num_integrate_species();

  int get_num_integrate_parameters();

  int get_num_integrate_initialAssignments();

  int get_num_integrate_rules();

  int get_num_integrate_constraints();

  int get_num_integrate_reactions();

  int get_num_integrate_events();

  // NOTE - method reciever is reponsible for deleting the object pointed to by the pointer
  ListOfFunctionDefinitions* get_import_functionDefinitions();
  ListOfFunctionDefinitions* get_replaceA_functionDefinitions();
  ListOfFunctionDefinitions* get_replaceB_functionDefinitions();
  ListOfFunctionDefinitions* get_integrateA_functionDefinitions();
  ListOfFunctionDefinitions* get_integrateB_functionDefinitions();
  
  ListOfUnitDefinitions* get_import_unitDefinitions();
  ListOfUnitDefinitions* get_replaceA_unitDefinitions();
  ListOfUnitDefinitions* get_replaceB_unitDefinitions();
  ListOfUnitDefinitions* get_integrateA_unitDefinitions();
  ListOfUnitDefinitions* get_integrateB_unitDefinitions();
  
  ListOfCompartments* get_import_compartments();
  ListOfCompartments* get_replaceA_compartments();
  ListOfCompartments* get_replaceB_compartments();
  ListOfCompartments* get_integrateA_compartments();
  ListOfCompartments* get_integrateB_compartments();
  
  ListOfSpecies* get_import_species();
  ListOfSpecies* get_replaceA_species();
  ListOfSpecies* get_replaceB_species();
  ListOfSpecies* get_integrateA_species();
  ListOfSpecies* get_integrateB_species();
  
  ListOfParameters* get_import_parameters();
  ListOfParameters* get_replaceA_parameters();
  ListOfParameters* get_replaceB_parameters();
  ListOfParameters* get_integrateA_parameters();
  ListOfParameters* get_integrateB_parameters();
  
  ListOfInitialAssignments* get_import_initialAssignments();
  ListOfInitialAssignments* get_replaceA_initialAssignments();
  ListOfInitialAssignments* get_replaceB_initialAssignments();
  ListOfInitialAssignments* get_integrateA_initialAssignments();
  ListOfInitialAssignments* get_integrateB_initialAssignments();
  
  ListOfRules* get_import_rules();
  ListOfRules* get_replaceA_rules();
  ListOfRules* get_replaceB_rules();
  ListOfRules* get_integrateA_rules();
  ListOfRules* get_integrateB_rules();
  
  ListOfConstraints* get_import_constraints();
  ListOfConstraints* get_replaceA_constraints();
  ListOfConstraints* get_replaceB_constraints();
  ListOfConstraints* get_integrateA_constraints();
  ListOfConstraints* get_integrateB_constraints();
    
  ListOfReactions* get_import_reactions();
  ListOfReactions* get_replaceA_reactions();
  ListOfReactions* get_replaceB_reactions();
  ListOfReactions* get_integrateA_reactions();
  ListOfReactions* get_integrateB_reactions();
    
  ListOfEvents* get_import_events();
  ListOfEvents* get_replaceA_events();
  ListOfEvents* get_replaceB_events();
  ListOfEvents* get_integrateA_events();
  ListOfEvents* get_integrateB_events();
    
 private:
  

  // inline function
  void even_number(int elements);
  bool load_conf();
  bool load_conf(std::string conf_file);
  void conf_preprocess();
  
  
  void set_import_list(const Model* modelB);
  void set_replace_or_integrate_list(const Model* modelA, const Model* modelB, bool replace);
   
  int get_number_list(int*& number_array);

  void section_set(std::string section, int element);

  

  
  // resets the input seek pointer and error flags in one method. Location can be any of {beg, end, functions, units, compartments, species, parameters, ia, rules, constraints, reactions, events}
  bool reset_seek();
  
  ListOfFunctionDefinitions* get_functionDefinitions_list(); 
  ListOfUnitDefinitions* get_unitDefinitions_list();
  ListOfCompartments* get_compartments_list();
  ListOfSpecies* get_species_list();
  ListOfParameters* get_parameter_list();
  ListOfInitialAssignments* get_initialAssignments_list();
  ListOfRules* get_rules_list();
  ListOfConstraints* get_constraints_list();
  ListOfReactions* get_reactions_list();
  ListOfEvents* get_events_list();

  int find_in_file(std::string section, bool reset);
  int number_import(int position);
  int number_replace(int position);
  int number_remove(int position);
  
  // data members which define locations in the conf file for seekg and number of elements at each position
  int seek_locations[10];
  int replacements_pairs[10];
  int import_elements[10];
  int delete_elements[10];

  // conf_stream variables
  bool stream_set;
  std::ifstream conf_stream;

  // containers
  SBML_integration_container<ListOfFunctionDefinitions, const FunctionDefinition*> function_container;
  SBML_integration_container<ListOfUnitDefinitions, const UnitDefinition*> unit_container;
  SBML_integration_container<ListOfCompartments, const Compartment*> compartment_container;
  SBML_integration_container<ListOfSpecies, const Species*> species_container;
  SBML_integration_container<ListOfParameters, const Parameter*> parameter_container;
  SBML_integration_container<ListOfInitialAssignments, const InitialAssignment*> initialAssignment_container;
  SBML_integration_container<ListOfRules, const Rule*>  rule_container;
  SBML_integration_container<ListOfConstraints, const Constraint*> constraint_container;
  SBML_integration_container<ListOfReactions, const Reaction*> reaction_container;
  SBML_integration_container<ListOfEvents, const Event*> event_container;

};

#endif
