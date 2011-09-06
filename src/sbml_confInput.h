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
   \brief Configuration file API, providing easy data access to the rest of the software while dealing with all the low level filestream handling

   SBML_confInput is the class which provides an API to the data stored in the .conf file (by default called integrate.conf). The information translated from this configuration file is stored in ten SBML_integration_container objects.  These are described in more detail in their documentation, but encompasse five ListOf* objects, where * is one of the ten SBML model element types. SBML_confInpit serves as an API to these containers, allowing a single interface to get the information needed to integrate two models together.
   
 **/

class SBML_confInput : public SBML_UI_general {
  
 public:
  SBML_confInput();
  
  /*!
    
    \brief Main function - used to set all the data structures in place and import all relevant data from the .conf file as defined by conf_file parameter
    
    <b>Preconditions:</b> modelNew and modelB are valid SBML models, conf_file is the filename of a correctly formatted configuration file.
      
    <b>Postconditions:</b> Imports the data specified in the configuration file into this class. 
    Elements are stored in import, integrate and replace lists, with counters set to the number of elements in each of these lists. 

    <b>Notes: </b> The storage of elements in lists is infact an abstraction, and instead imported elements are stored on SBML_Integration_Container objects. 
    !*/

  
  bool import_data(const Model* modelNew, const Model* modelB, std::string conf_file);
  
  // test function used in debugging...
  // void test_function(const Model* modelB, const Model* modelA);
  
  //#########################################################################################
  //          HUGE list of getter functions to be used by integrate
  //#########################################################################################
  /** \brief Returns the number of functionDefinitions defined in the functionDefinition's "Import:" list in the .conf file.
   **/
  int get_num_import_functionDefinitions();
  
  /** \brief Returns the number of unitDefinitions defined in the unitDefinition's "Import:" list in the .conf file.
   **/
  int get_num_import_unitDefinitions(); 
  
  /** \brief Returns the number of compartments defined in the compartment's "Import:" list in the .conf file.
   **/
  int get_num_import_compartments();
  
  /** \brief Returns the number of species defined in the species's "Import:" list in the .conf file.
   **/
  int get_num_import_species();
  
  /** \brief Returns the number of parameters defined in the parameter's "Import:" list in the .conf file.
   **/
  int get_num_import_parameters();

  /** \brief Returns the number of initialAssigments defined in the initialAssignments's "Import:" list in the .conf file.
   **/
  int get_num_import_initialAssignments();

  /** \brief Returns the number of rules defined in the rule's "Import:" list in the .conf file.
   **/
  int get_num_import_rules();

  /** \brief Returns the number of constraints defined in the contraint's "Import:" list in the .conf file.
   **/
  int get_num_import_constraints();

  /** \brief Returns the number of reactions defined in the reaction's "Import:" list in the .conf file.
   **/
  int get_num_import_reactions();

  /** \brief Returns the number of events defined in the event's "Import:" list in the .conf file.
   **/
  int get_num_import_events();

  //#########################################################################################
  
  /** \brief Returns the number of events defined in the functionDefinitions's <b>"Replace:"</b> list in the .conf file.
    **/
  int get_num_replace_functionDefinitions();

  /** \brief Returns the number of events defined in the unitDefinition's <b>"Replace:"</b> list in the .conf file.
    **/
  int get_num_replace_unitDefinitions();

  /** \brief Returns the number of events defined in the compartment's <b>"Replace:"</b> list in the .conf file.
  **/
  int get_num_replace_compartments();

  /** \brief Returns the number of events defined in the species's <b>"Replace:"</b> list in the .conf file.
  **/
  int get_num_replace_species();

  /** \brief Returns the number of events defined in the parameter's <b>"Replace:"</b> list in the .conf file.
  **/
  int get_num_replace_parameters();

  /** \brief Returns the number of events defined in the initailAssignments's <b>"Replace:"</b> list in the .conf file.
   **/
  int get_num_replace_initialAssignments();

  /** \brief Returns the number of events defined in the rules's <b>"Replace:"</b> list in the .conf file.
   **/
  int get_num_replace_rules();

  /** \brief Returns the number of events defined in the constraints's <b>"Replace:"</b> list in the .conf file.
   **/
  int get_num_replace_constraints();

  /** \brief Returns the number of reactions defined in the constraints's <b>"Replace:"</b> list in the .conf file.
   **/
  int get_num_replace_reactions();

  /** \brief Returns the number of events defined in the constraints's <b>"Replace:"</b> list in the .conf file.
   **/
  int get_num_replace_events();
  
  //#########################################################################################

  /** \brief Returns the number of events defined in the function definitions's <b>"Integrate:"</b> list in the .conf file.
   **/
  int get_num_integrate_functionDefinitions();

  /** \brief Returns the number of events defined in the unit definitions's <b>"Integrate:"</b> list in the .conf file.
   **/
  int get_num_integrate_unitDefinitions();

  /** \brief Returns the number of events defined in the compartments's <b>"Integrate:"</b> list in the .conf file.
   **/
  int get_num_integrate_compartments();

  /** \brief Returns the number of events defined in the species's <b>"Integrate:"</b> list in the .conf file.
   **/
  int get_num_integrate_species();

  /** \brief Returns the number of events defined in the parameter's <b>"Integrate:"</b> list in the .conf file.
   **/
  int get_num_integrate_parameters();

  /** \brief Returns the number of events defined in the initial assignment's <b>"Integrate:"</b> list in the .conf file.
   **/
  int get_num_integrate_initialAssignments();

  /** \brief Returns the number of events defined in the rules's <b>"Integrate:"</b> list in the .conf file.
   **/
  int get_num_integrate_rules();

  /** \brief Returns the number of events defined in the constraint's <b>"Integrate:"</b> list in the .conf file.
   **/
  int get_num_integrate_constraints();

  /** \brief Returns the number of events defined in the reactions's <b>"Integrate:"</b> list in the .conf file.
   **/
  int get_num_integrate_reactions();

  /** \brief Returns the number of events defined in the events's <b>"Integrate:"</b> list in the .conf file.
   **/
  int get_num_integrate_events();

  //#########################################################################################

   /** \brief Returns the list of function definitions defined by the relevant list in the .conf file. **/
  ListOfFunctionDefinitions* get_import_functionDefinitions();
   /** \brief Returns the list of function definitions defined by the relevant list in the .conf file. **/
  ListOfFunctionDefinitions* get_replaceA_functionDefinitions();
   /** \brief Returns the list of function definitions defined by the relevant list in the .conf file. **/
  ListOfFunctionDefinitions* get_replaceB_functionDefinitions();
   /** \brief Returns the list of function definitions defined by the relevant list in the .conf file. **/
  ListOfFunctionDefinitions* get_integrateA_functionDefinitions();
   /** \brief Returns the list of function definitions defined by the relevant list in the .conf file. **/
  ListOfFunctionDefinitions* get_integrateB_functionDefinitions();

   /** \brief Returns the list of unit definitions defined by the relevant list in the .conf file. **/  
  ListOfUnitDefinitions* get_import_unitDefinitions();
   /** \brief Returns the list of unit definitions defined by the relevant list in the .conf file. **/  
  ListOfUnitDefinitions* get_replaceA_unitDefinitions();
   /** \brief Returns the list of unit definitions defined by the relevant list in the .conf file. **/  
  ListOfUnitDefinitions* get_replaceB_unitDefinitions();
   /** \brief Returns the list of unit definitions defined by the relevant list in the .conf file. **/  
  ListOfUnitDefinitions* get_integrateA_unitDefinitions();
   /** \brief Returns the list of unit definitions defined by the relevant list in the .conf file. **/  
  ListOfUnitDefinitions* get_integrateB_unitDefinitions();

   /** \brief Returns the list of compartments defined by the relevant list in the .conf file. **/    
  ListOfCompartments* get_import_compartments();
   /** \brief Returns the list of compartments defined by the relevant list in the .conf file. **/    
  ListOfCompartments* get_replaceA_compartments();
   /** \brief Returns the list of compartments defined by the relevant list in the .conf file. **/    
  ListOfCompartments* get_replaceB_compartments();
   /** \brief Returns the list of compartments defined by the relevant list in the .conf file. **/    
  ListOfCompartments* get_integrateA_compartments();
   /** \brief Returns the list of compartments defined by the relevant list in the .conf file. **/    
  ListOfCompartments* get_integrateB_compartments();
  
   /** \brief Returns the list of species defined by the relevant list in the .conf file. **/    
  ListOfSpecies* get_import_species();
   /** \brief Returns the list of species defined by the relevant list in the .conf file. **/    
  ListOfSpecies* get_replaceA_species();
   /** \brief Returns the list of species defined by the relevant list in the .conf file. **/    
  ListOfSpecies* get_replaceB_species();
   /** \brief Returns the list of species defined by the relevant list in the .conf file. **/    
  ListOfSpecies* get_integrateA_species();
   /** \brief Returns the list of species defined by the relevant list in the .conf file. **/    
  ListOfSpecies* get_integrateB_species();
  
   /** \brief Returns the list of parameters defined by the relevant list in the .conf file. **/    
  ListOfParameters* get_import_parameters();
   /** \brief Returns the list of parameters defined by the relevant list in the .conf file. **/    
  ListOfParameters* get_replaceA_parameters();
   /** \brief Returns the list of parameters defined by the relevant list in the .conf file. **/    
  ListOfParameters* get_replaceB_parameters();
   /** \brief Returns the list of parameters defined by the relevant list in the .conf file. **/    
  ListOfParameters* get_integrateA_parameters();
   /** \brief Returns the list of parameters defined by the relevant list in the .conf file. **/    
  ListOfParameters* get_integrateB_parameters();
  
   /** \brief Returns the list of initial assignments defined by the relevant list in the .conf file. **/  
  ListOfInitialAssignments* get_import_initialAssignments();

   /** \brief Returns the list of initial assignments defined by the relevant list in the .conf file. **/  
  ListOfInitialAssignments* get_replaceA_initialAssignments();

   /** \brief Returns the list of initial assignments defined by the relevant list in the .conf file. **/  
  ListOfInitialAssignments* get_replaceB_initialAssignments();

   /** \brief Returns the list of initial assignments defined by the relevant list in the .conf file. **/  
  ListOfInitialAssignments* get_integrateA_initialAssignments();

   /** \brief Returns the list of initial assignments defined by the relevant list in the .conf file. **/  
  ListOfInitialAssignments* get_integrateB_initialAssignments();
  
   /** \brief Returns the list of rules defined by the relevant list in the .conf file. **/  
  ListOfRules* get_import_rules();

   /** \brief Returns the list of rules defined by the relevant list in the .conf file. **/  
  ListOfRules* get_replaceA_rules();

   /** \brief Returns the list of rules defined by the relevant list in the .conf file. **/  
  ListOfRules* get_replaceB_rules();

   /** \brief Returns the list of rules defined by the relevant list in the .conf file. **/  
  ListOfRules* get_integrateA_rules();

   /** \brief Returns the list of rules defined by the relevant list in the .conf file. **/  
  ListOfRules* get_integrateB_rules();
  

   /** \brief Returns the list of constraints defined by the relevant list in the .conf file. **/  
  ListOfConstraints* get_import_constraints();

   /** \brief Returns the list of constraints defined by the relevant list in the .conf file. **/  
  ListOfConstraints* get_replaceA_constraints();

   /** \brief Returns the list of constraints defined by the relevant list in the .conf file. **/  
  ListOfConstraints* get_replaceB_constraints();

   /** \brief Returns the list of constraints defined by the relevant list in the .conf file. **/  
  ListOfConstraints* get_integrateA_constraints();

   /** \brief Returns the list of constraints defined by the relevant list in the .conf file. **/  
  ListOfConstraints* get_integrateB_constraints();
    

   /** \brief Returns the list of reactions defined by the relevant list in the .conf file. **/  
  ListOfReactions* get_import_reactions();

   /** \brief Returns the list of reactions defined by the relevant list in the .conf file. **/  
  ListOfReactions* get_replaceA_reactions();

   /** \brief Returns the list of reactions defined by the relevant list in the .conf file. **/  
  ListOfReactions* get_replaceB_reactions();

   /** \brief Returns the list of reactions defined by the relevant list in the .conf file. **/  
  ListOfReactions* get_integrateA_reactions();

   /** \brief Returns the list of reactions defined by the relevant list in the .conf file. **/  
  ListOfReactions* get_integrateB_reactions();
    

   /** \brief Returns the list of events defined by the relevant list in the .conf file. **/  
  ListOfEvents* get_import_events();

   /** \brief Returns the list of events defined by the relevant list in the .conf file. **/  
  ListOfEvents* get_replaceA_events();

   /** \brief Returns the list of events defined by the relevant list in the .conf file. **/  
  ListOfEvents* get_replaceB_events();

   /** \brief Returns the list of events defined by the relevant list in the .conf file. **/  
  ListOfEvents* get_integrateA_events();

   /** \brief Returns the list of events defined by the relevant list in the .conf file. **/  
  ListOfEvents* get_integrateB_events();
    
 private:
  
  /** Quick test to ensure that elements is an event number **/
  void even_number(int elements);
  
  /** Calls load_conf("") - i.e. with empty string name **/
  bool load_conf();

  /*! \brief Parent function that loads data from the .conf file

    \b Preconditions: SBML_confInput object should have been constructed correctly, conf_file should be a valid string (even an empty one), where if it defines a filename it must include the extension .conf (i.e. testing.conf)
    
    \b Postconditions: With a large number of safety checks, we parse the data from the \<name> file where \<name> = conf_file_name.conf.
    If \<name> is an empty string we use the default integrate.conf. Data is loaded into the container objects within the SBML_confInput 
    object
  */
  bool load_conf(std::string conf_file);

  /*! \brief Analyses the configuration file, checks for errors and initializes import settings

    \b Preconditions: SBML_confInput object should have been constructed correctly, conf_file should be a valid string (even an empty one), where if it defines a filename it must include the extension .conf (i.e. testing.conf)
    
    \b Postconditions: Sets all the seek locations, will abort if there is a serious problem with the configuration file, or write a warning to logfile if there is a minor one
  */
  void conf_preprocess();
  
   /*! \brief Imports the specified elements as defined by Import: list in the .conf file into the import containers

    \b Preconditions: Must run preprocess first to ensure file is good and set seek locations, modelB should be the import model
    
    \b Postconditions: Imports the defined elements into the import_lists in the SBML_integration_container elements

   */
  void set_import_list(const Model* modelB);
  
  /*! \brief Imports the specified elements as defined by the Replace: or Integrate: lists in the .conf file into the replace or integrate containers

    \b Preconditions: Must run preprocess first to ensure file is good and set seek locations, modelB should be the import model, model A the base model or the virgin integration model (which are the same thing). If replace is true we search and load the repaclement lists, if false the integration lists.
    
    \b Postconditions: Imports the defined elements into the replacement_list or integration_list in the SBML_integration_container elements

   */
  void set_replace_or_integrate_list(const Model* modelA, const Model* modelB, bool replace);
  


    /*! \brief Sets the seek location pointer to the section (Import:, Replace: or Integrate:) and element (1-10) which index each of the SBML element types 

      \b Preconditions: Must run preprocess first to ensure file is good and set seek locations
    
    \b Postconditions: List moves the underlying seek pointer on the open conf_stream, so operates on the C++ filestream level, 
    not on the coding level presented
   */
  void section_set(std::string section, int element);
  

  /*! \brief Returns the array (i.e. the Import:, Replace: or Integrate: list) defined at the current seek pointer location

    \b Preconditions: To read an array use section_set to move the pointer to the correction location. Number array is in fact an output parameter and returns the array.
      
    \b Postconditions: Returns an array of integers through number_array, which is [return_value] elements long
    */
  int get_number_list(int*& number_array);
  
  /** \brief Resets the input seek pointer and error flags in one method. **/
  bool reset_seek();
  

  /*! \brief Find the defined section in the file
    
    \b Preconditions: Section should be a valid string, reset is true if after finding the string you wish to reset the seek pointer

    \b Postconditions: Returns the seek pointer value as an int, which can be used as a file-location index for quick access
    */
  int find_in_file(std::string section, bool reset);

  
  // #############################################################################################
  //                                         class attributes                
  // #############################################################################################
  // data members which define locations in the conf file for seekg and number of elements at each position

  /// array of file pointer locations for each of the 10 SBML elements in the .conf file
  int seek_locations[10];

  // conf_stream variables
  /// maintains the stream state
  bool stream_set;

  /// .conf filestream
  std::ifstream conf_stream;

  // containers
  
  /// Function definition import, replacement and integration lists container
  SBML_integration_container<ListOfFunctionDefinitions, const FunctionDefinition*> function_container;
  /// Unit definition import, replacement and integration lists container
  SBML_integration_container<ListOfUnitDefinitions, const UnitDefinition*> unit_container;
  /// Compartment import, replacement and integration lists container
  SBML_integration_container<ListOfCompartments, const Compartment*> compartment_container;
  /// Species import, replacement and integration lists container
  SBML_integration_container<ListOfSpecies, const Species*> species_container;
  /// Parameter import, replacement and integration lists container
  SBML_integration_container<ListOfParameters, const Parameter*> parameter_container;
  /// Initial assignment import, replacement and integration lists container
  SBML_integration_container<ListOfInitialAssignments, const InitialAssignment*> initialAssignment_container;
  /// Rule import, replacement and integration lists container
  SBML_integration_container<ListOfRules, const Rule*>  rule_container;
  /// Constraint import, replacement and integration lists container
  SBML_integration_container<ListOfConstraints, const Constraint*> constraint_container;
  /// Reaction import, replacement and integration lists container
  SBML_integration_container<ListOfReactions, const Reaction*> reaction_container;
  /// Event import, replacement and integration lists container
  SBML_integration_container<ListOfEvents, const Event*> event_container;
  
};

#endif
