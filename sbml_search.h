#ifndef SBML_SEARCH_H
#define SBML_SEARCH_H

#include <sbml/SBMLTypes.h>
#include "sbml_ui_general.h"
#include "sbml_display.h"

class SBML_search : public SBML_UI_general {
 
 protected:
  // #############################################################################################
  // Lookup Functions
  
  // lookup the unitKind_t and returns a string
  std::string unit_kind_lookup(int n);

  
  // #############################################################################################
  // replace_* functions
  //
  // These are dynamically bound and called by the locate_and_replace functions. If an SBML_search class
  // calls one, it simply returns true (i.e. the thing you're searching for has been found).
  // As described in SBML_cleanup, if an SBML_cleanup object calls the function then the "clean_model" data member
  // in the SBML_cleanup object has the inputA element ID replaced by the inputB ID
  
  virtual bool replace_unit(UnitDefinition* inputA, UnitDefinition* inputB, char C, int i);
  // virtual bool replace_functiondef - this doesn't exist as it's never needed
  virtual bool replace_compartment(Compartment* inputA, Compartment* inputB, char C, int i);
  virtual bool replace_species(Species* inputA, Species* inputB, char C, int i);
  virtual bool replace_parameters(Parameter* inputA, Parameter* inputB, char C, int i);
  // virtual bool replace_initial_assignments this doesn't exist as it's never needed
  // virtual bool replace_rules doesn't exist as it's never needed
  // virtual bool replace_constraints doesn't exist as it's never needed
  // virtual bool replace_reactions doesn't exist as it's never needed
  // virtual bool replace_events doesn't exist as it's never needed


  // Slightly different
  virtual bool replace_node(ASTNode* node, std::string replacement);

  //Debugging tool left in for posterity!
  void nodechecker(const ASTNode* node);


  // pimary locate_and replace functions (polymorphism for ease of use) - "replace" functionality not actually 
  // used in the SBML_search implementation of these functions, but is used in the cleanup version
  bool locate_and_replace(Model* model, FunctionDefinition* inputA, FunctionDefinition* inputB);
  bool locate_and_replace(Model* model, UnitDefinition* inputA, UnitDefinition* inputB);
  bool locate_and_replace(Model* model, Compartment* inputA, Compartment* inputB);
  bool locate_and_replace(Model* model, Species* inputA, Species* inputB);
  bool locate_and_replace(Model* model, Parameter* inputA, Parameter* inputB);
  bool locate_and_replace(Model* model, InitialAssignment* inputA, InitialAssignment* inputB);
  bool locate_and_replace(Model* model, Rule* inputA, Rule* inputB);
  bool locate_and_replace(Model* model, Constraint* inputA, Constraint* inputB);
  bool locate_and_replace(Model* model, Reaction* inputA, Reaction* inputB);
  bool locate_and_replace(Model* model, Event* inputA, Event* inputB);
  
  // locate (and replace if from SBML_cleanup) an element from any MathML structure
  bool locate_and_replace_mathML(Model* model, std::string query);
  bool locate_and_replace_mathML(Model* model, std::string queury, std::string replacement);
  bool locate_and_replace(ASTNode* node, std::string query, std::string replacement);
  
  
  
 public:
   
  // #############################################################################################
  // is_present functions - return true if a reference to the element (defined by it's ID) is present in the provided model. Essentially, it allows you to check if a specific element of the model is present through ID referencing
  
  
  // bool is_present(FunctionDefinition* 
  bool is_present(Model* model, FunctionDefinition* inputA);
  bool is_present(Model* model, UnitDefinition* inputA);
  bool is_present(Model* model, Compartment* inputA);
  bool is_present(Model* model, Species* inputA);
  bool is_present(Model* model, Parameter* inputA);
  bool is_present(Model* model, InitialAssignment* inputA);
  bool is_present(Model* model, Rule* inputA);
  bool is_present(Model* model, Constraint* inputA);
  bool is_present(Model* model, Reaction* inputA);
  bool is_present(Model* model, Event* inputA);
  

  
  // find a rule object in model based on the rule ID
  const Rule* find_rule(const Model* model, std::string search_term);
  
  // takes a ListOfUnits, and the number of units in that list, and returns the units 
  // definition as a string
  std::string describe_units(const ListOfUnits* list_of_units, int number);
  
  // Takes a unitID, and returns that unit's definition as a string 
  std::string units_lookup(const Model* model, std::string units_id);
  
  // Function to check if a unit (defined by its ID) is used in a model
  bool is_unit_used(Model* model, std::string id_string);
  
  // returns a ListOfUnitsDefinition object point, which contains all the units in
  // input model which are therein defined but not used through the model. numbered_unused is
  // a pass by reference integer which determines the number of entries in the returned list
  ListOfUnitDefinitions* unused_units_lookup(int &number_unused, Model* input_model);
  
  // returns the total number of entities defined in a model
  int total_num_entities(const Model* model);
  
  // Function which returns a string containing the formula of a reaction
  std::string get_reaction_formula(const Reaction* rxn);
  
};


// To avoid cyclic dependencies we had to put this here, as a template function it must be in the.h file but
// as with search_framework a superclass of SBML_display had to be here
// YES I know this is bad. YES this search/display structure will be refactored before Beta.
//
// 

template <class T> 
int SBML_display::compare_units(const T compA, const T compB, const Model* modelA, const Model* modelB){
  char selector = ' ';
  
  SBML_search search_framework;
  
  while(true){
    std::cout << "### Units ###" << std::endl
	      << "Ensure that if you select option B, it actually exists in the model (i.e. you set it as one of the elements to import in the .conf file. Software support to check this coming real soon, but at the moment please try and be careful!" << std::endl
	      << "  A ----- " << compA->getUnits() << " = " 
	      << search_framework.units_lookup(modelA, compA->getUnits()) << std::endl
      
	      << "  B ----- " << compB->getUnits() << " = " 
	      << search_framework.units_lookup(modelB, compB->getUnits()) << std::endl;
    
 
    std::cout << "Select A or B: ";
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
