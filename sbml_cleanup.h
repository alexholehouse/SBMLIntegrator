#ifndef SBML_CLEANUP_H
#define SBML_CLEANUP_H

#include "sbml_formatter.h"
#include "sbml_search.h"

#include <sbml/SBMLTypes.h>
#include <iostream>
#include <fstream>


class SBML_cleanup : protected SBML_search {

  // by defining the inheritance as protected we ensure we don't accidentally call the 
  // "is_present" method from the cleanup object, which would initialize the cleanup 
  // virtual functions and risk damaging the clean_model's consistency.

  // The only functions you can call on the SBML_search object are the public ones in this class
  
   public:
  
  SBML_cleanup(SBMLDocument* input_doc);
  SBML_cleanup(Model* input_model);
  SBML_cleanup(Model* input_model, bool copy);
  
  // NB this means replace throughout the model [inputB replaces inputA]
  bool replace(UnitDefinition* inputA, UnitDefinition* inputb);
  bool replace(FunctionDefinition* inputA, FunctionDefinition* inputB);
  bool replace(Compartment* inputA, Compartment* inputB);
  bool replace(Species* inputA, Species* inputB);
  bool replace(Parameter* inputA, Parameter* inputB);
  bool replace(InitialAssignment* inputA, InitialAssignment* inputB);
  bool replace(Rule* inputA, Rule* inputB);
  bool replace(Constraint* inputA, Constraint* inputB);
  bool replace(Reaction* inputA, Reaction* inputB);
  bool replace(Event* inputA, Event* inputB);
  
  // returns a pointer to the clean model for searching/displaying or whatnot.
  Model* get_clean_model();
  
  void consolidate_units();
  
 private:
  
  /*! The clean model *does not exist anywhere else unless copy is set to false in the constructor* - it is initially a deep copy of the model fed into the constructor, but changes made to it via the replace functions only affect this model. As a result, it is the user;s responsibility to delete this object to avoid a memory leak.

    If copy is set to false, then clean_model is set to the input_model, and cleanup operations are enacted on the input model!*/ 
  Model* clean_model;
  
  // remove the units in the list of units (number defines the number of units in the list)
  void remove_units(ListOfUnitDefinitions* toberemoved, int number);
  
  // Virtual counterparts to the SBML_search virtual functions. 
  // Instead of just returning bool they typically have a switch statement and replace 
  // the reference to the type in the function name from the section and position in
  // the model defined by C and i 
  
  virtual bool replace_unit(UnitDefinition* inputA, UnitDefinition* inputB, char C, int i);
  // virtual bool replace_functiondef - this doesn't exist as it's never needed
  virtual bool replace_compartment(Compartment* inputA, Compartment* inputB, char C, int i);
  virtual bool replace_species(Species* inputA, Species* inputB, char C, int i);  

  
  /*!Funcion for replacing some reference to a parameter in a model. Char C defines what is to be replaced, while int i defines it's location in the model. This is a virtual function, and has a polymorphic variation in SBML_search which simply returns true.

    \b Precondition: Both parameters are valid, depending on the section determined by C, there must be at least i different elemenst of that type in the loaded model.
    
    \b Postcondition: the reference ID held by "some element", defined by C, which previously was equal to the ID held by inputA (parameter 1) is now set to be equal to the reference ID of inputB (parameter 2). 

    \b Notes N/A
    !*/
  virtual bool replace_parameters(Parameter* inputA, Parameter* inputB, char C, int i);
  


// virtual bool replace_initial_assignmentss this doesn't exist as it's never needed
  // virtual bool replace_rules doesn't exist as it's never needed
  // virtual bool replace_constraints doesn't exist as it's never needed
  // virtual bool replace_reactions doesn't exist as it's never needed
  // virtual bool replace_events doesn't exist as it's never needed
  
  // helper function for replacing a refernece in an ASTNode with a different reference
  
  /*!Helper function for replacing a reference in an ASTNode

    \b Precondition: ASTNode must be a valid node, and should be of type AST_NAME

    \b Postcondition: the name attribute of node (parameter 1) is set to the value of replacement (parameter 2). 

    \b Notes replace_node(node, replacement) means parameter 2 replaces an aspect of parameter 1
    !*/
  virtual bool replace_node(ASTNode* node, std::string replacement);
  

  
};

#endif

  
  
