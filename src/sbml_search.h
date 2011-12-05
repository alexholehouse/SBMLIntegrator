// Copyright Alex Holehouse 2011
// Distributed under the terms of the GNU general public license - see COPYING.txt for more details

#ifndef SBML_SEARCH_H
#define SBML_SEARCH_H

#include "sbml_ui_general.h"
#include "sbml_display.h"

/*!
  \brief Class which contains search and lookup functionality for the model
  
  Includes functions to lookup model elements by ID, unit lookups and even determine the presence or absence of an ID in a complete, model wide manner. In this implementation acts primarily as a parent class to give functionality to SBML_cleanup
    
*/

class SBML_search : public SBML_UI_general {
 
 public:
   
  // #############################################################################################
  // is_present functions - return true if a reference to the element (defined by it's ID) is present in the provided model. Essentially, it allows you to check if a specific element of the model is present through ID referencing
  
  
  /// \brief Return true if inputA is present in model, else false
  bool is_present(Model* model, FunctionDefinition* inputA);
  /// \brief Return true if inputA is present in model, else false
  bool is_present(Model* model, UnitDefinition* inputA);
  /// \brief Return true if inputA is present in model, else false
  bool is_present(Model* model, Compartment* inputA);
  /// \brief Return true if inputA is present in model, else false
  bool is_present(Model* model, Species* inputA);
  /// \brief Return true if inputA is present in model, else false
  bool is_present(Model* model, Parameter* inputA);
  /// \brief Return true if inputA is present in model, else false
  bool is_present(Model* model, InitialAssignment* inputA);
  /// \brief Return true if inputA is present in model, else false
  bool is_present(Model* model, Rule* inputA);
  /// \brief Return true if inputA is present in model, else false
  bool is_present(Model* model, Constraint* inputA);
  /// \brief Return true if inputA is present in model, else false
  bool is_present(Model* model, Reaction* inputA);
  /// \brief Return true if inputA is present in model, else false
  bool is_present(Model* model, Event* inputA);
  
  
  /// \brief Find a rule object in model based on the rule ID
  const Rule* find_rule(const Model* model, std::string search_term);
  
  /*!
    \brief Get a string of units defined by a listOfUnits
    
    \b Preconditions: takes a ListOfUnits, and the number of units in that list

    \b Postconditions: returns the units definition as a string

  **/
  std::string describe_units(const ListOfUnits* list_of_units, int number);
  
  // Takes a unitID, and returns that unit's definition as a string   
  
  /*!
    \brief Return a verbose unit definition based on it's ID
    
    \b Preconditions: model is a valid model

    \b Postconditions: Searches through model for the unit defined by units_id, then uses that definition to return a verbose units string. If the unit_id cannot be found returns an appropriate warning.

  **/
  std::string units_lookup(const Model* model, std::string units_id);
  
  /// Function to check if a unit (defined by its ID) is used in a model - not currently used
  bool is_unit_used(Model* model, std::string id_string);
  
  /** returns a ListOfUnitsDefinition object point, which contains all the units in
  input model which are therein defined but not used through the model. numbered_unused is
  a pass by reference integer which determines the number of entries in the returned list - not currently used**/
  ListOfUnitDefinitions* unused_units_lookup(int &number_unused, Model* input_model);
  
  /// \brief Returns the total number of entities defined in a model
  int total_num_entities(const Model* model);
  
  /// \brief Function which returns a string containing the formula of a reaction
  std::string get_reaction_formula(const Reaction* rxn);

 protected:
  // #############################################################################################
  // Lookup Functions
  
  // lookup the unitKind_t and returns a string
  /*!
    \brief Lookup unit name based on UnitKind_t value defined in SBML **/
  
  std::string unit_kind_lookup(int n);

  
  // #############################################################################################
  // replace_* functions
  //
  // These are dynamically bound and called by the locate_and_replace functions. If an SBML_search class
  // calls one, it simply returns true (i.e. the thing you're searching for has been found).
  // As described in SBML_cleanup, if an SBML_cleanup object calls the function then the "clean_model" data member
  // in the SBML_cleanup object has the inputA element ID replaced by the inputB ID
  
  /*!
    \brief Dynamically bound functions used search and cleanup objects to find/replace unit definitions

    \b Preconditions: inputA and inputB are valid elements. See SBML_cleanup::replace_unit for more details

    \b Postconditions: Returns true if caller is an SBML_search object and target is found, otherwise false
  */
  
  virtual bool replace_unit(UnitDefinition* inputA, UnitDefinition* inputB, char C, int i);
  // virtual bool replace_functiondef - this doesn't exist as it's never needed
  /*!
    \brief Dynamically bound functions used search and cleanup objects to find/replace compartments

    \b Preconditions: inputA and inputB are valid elements. See SBML_cleanup::replace_unit for more details

    \b Postconditions: Returns true if caller is an SBML_search object and target is found, otherwise false
  */
  virtual bool replace_compartment(Compartment* inputA, Compartment* inputB, char C, int i);
  /*!
    \brief Dynamically bound functions used search and cleanup objects to find/replace species

    \b Preconditions: inputA and inputB are valid elements. See SBML_cleanup::replace_unit for more details

    \b Postconditions: Returns true if caller is an SBML_search object and target is found, otherwise false
  */
  virtual bool replace_species(Species* inputA, Species* inputB, char C, int i);
  /*!
    \brief Dynamically bound functions used search and cleanup object to find/replace parameters

    \b Preconditions: inputA and inputB are valid elements. See SBML_cleanup::replace_unit for more details

    \b Postconditions: Returns true if caller is an SBML_search object and target is found, otherwise false
  */
  virtual bool replace_parameters(Parameter* inputA, Parameter* inputB, char C, int i);
  // virtual bool replace_initial_assignments this doesn't exist as it's never needed
  // virtual bool replace_rules doesn't exist as it's never needed
  // virtual bool replace_constraints doesn't exist as it's never needed
  // virtual bool replace_reactions doesn't exist as it's never needed
  // virtual bool replace_events doesn't exist as it's never needed


  // Slightly different  
  /*!
    \brief Depth first search based search function for a specific ASTNode in a MathML structure
    
    \b Preconditions: node is a valid ASTNode, replacement is valid string
    
    \b Postconditions: Returns true if caller is an SBML_search object and target is found, otherwise false. If caller is SBML_cleanup object will return false, and replace the value in ASTNode with replacement.
  */
  virtual bool replace_node(ASTNode* node, std::string replacement);

  // Debugging tool left in for posterity!
  // void nodechecker(const ASTNode* node);


  // pimary locate_and replace functions (polymorphism for ease of use) - "replace" functionality not actually 
  // used in the SBML_search implementation of these functions, but is used in the cleanup version

  
  /// \brief Search model for input A and replace it with inputB if called from an SBML_cleanup object
  bool locate_and_replace(Model* model, FunctionDefinition* inputA, FunctionDefinition* inputB);
  /// \brief Search model for input A and replace it with inputB if called from an SBML_cleanup object
  bool locate_and_replace(Model* model, UnitDefinition* inputA, UnitDefinition* inputB);
  /// \brief Search model for input A and replace it with inputB if called from an SBML_cleanup object
  bool locate_and_replace(Model* model, Compartment* inputA, Compartment* inputB);
  /// \brief Search model for input A and replace it with inputB if called from an SBML_cleanup object
  bool locate_and_replace(Model* model, Species* inputA, Species* inputB);
  /// \brief Search model for input A and replace it with inputB if called from an SBML_cleanup object
  bool locate_and_replace(Model* model, Parameter* inputA, Parameter* inputB);
  /// \brief Search model for input A and replace it with inputB if called from an SBML_cleanup object
  bool locate_and_replace(Model* model, InitialAssignment* inputA, InitialAssignment* inputB);
  /// \brief Search model for input A and replace it with inputB if called from an SBML_cleanup object
  bool locate_and_replace(Model* model, Rule* inputA, Rule* inputB);
  /// \brief Search model for input A and replace it with inputB if called from an SBML_cleanup object
  bool locate_and_replace(Model* model, Constraint* inputA, Constraint* inputB);
  /// \brief Search model for input A and replace it with inputB if called from an SBML_cleanup object
  bool locate_and_replace(Model* model, Reaction* inputA, Reaction* inputB);
  /// \brief Search model for input A and replace it with inputB if called from an SBML_cleanup object
  bool locate_and_replace(Model* model, Event* inputA, Event* inputB);
  
  // locate (and replace if from SBML_cleanup) an element from any MathML structure

  
  /// \brief Search model for query in all MathML structures
  bool locate_and_replace_mathML(Model* model, std::string query);
  /// \brief Search model for query in all MathML structures and replace it with replacement
  bool locate_and_replace_mathML(Model* model, std::string queury, std::string replacement);
  /// \brief Search model for query in all MathML structures
  bool locate_and_replace(ASTNode* node, std::string query, std::string replacement);
    
};


// To avoid cyclic dependencies we had to put this here, as a template function it must be in 
// the.h file but as with search_framework a superclass of SBML_display had to be here
// This is bad. I know. I'm sorry. We all make mistakes, and if I had more time I'd restructure the system to change the inheritance. But I don't, so here we are. But yeah, sozzle.

template <class T> 
int SBML_display::compare_units(const T compA, const T compB, const Model* modelA, const Model* modelB){
  char selector = ' ';
  
  //SBML_search search_framework;
  SBML_search search_framework;
  
  while(true){
    
    std::string unitsA = compA->getUnits();
    std::string unitsB = compB->getUnits();
    
    std::cout << "### Units ###" << std::endl;
    std::cout << "Ensure that if you select option B, it actually exists in the model" << std::endl << "(i.e. you set it as one of the elements to import in the .conf file." << std::endl << "Software support to check this coming real soon, but at the moment" << std::endl << "please try and be careful!)" << std::endl << std::endl;
    
    std::cout << " A ----- ";
    if (unitsA != "")
      std::cout << unitsA;
    else
      std::cout << "[None Defined]";

    std::cout << " = " << search_framework.units_lookup(modelA, compA->getUnits()) << std::endl; 
    
    std::cout << " B ----- ";
    if (unitsB != "")
      std::cout << unitsB;
    else
      std::cout << "[None Defined]";

    std::cout << " = " << search_framework.units_lookup(modelB, compB->getUnits()) << std::endl; 
    
    std::cout << std::endl << " Select A or B: ";
    std::cin >> selector;
    std::cin.ignore();
    std::cout << std::endl;
  
    if (selector =='A')
      return 0;

    if (selector == 'B')
      return 1;  
  }
}
#endif
