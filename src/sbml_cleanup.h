// Copyright Alex Holehouse 2011
// Distributed under the terms of the GNU general public license - see COPYING.txt for more details

#ifndef SBML_CLEANUP_H
#define SBML_CLEANUP_H

#include "sbml_search.h"
#include <sbml/SBMLTypes.h>

/*! \brief Class for implementing the replacement of a model element through a model. 

It is highly connected to SBML_Search in the following way.
SBML_cleanup object calls "Replace(element_object)" ===> finds every instance of that element using SBML_search methods ==> runs the replacement method which is located in SBML_cleanup
SBML_search can also be used to simply find an object (by another method). SBML_cleanup implements protected inheritance from SBML_search. This is to ensure "is_present" is not accidentally called from a cleanup object. This would damage the models data integrity, and so we have chosen to implement a hard coding solution to avoid this from happening.

SBML_search also includes a consolidates units function. This is in fact not used in SBMLIntegrator (as of Alpha 0.1) but may be used as the software becomes more advanced


 *   
SBML_augment is a class for making model-wide changes. Currently it's primary role is housing the method complete_model_id_rename_with_append(string to_append), a method to append a string onto every ID in a model. In the future additional system wide functionality such as rescaling will be implemented at least through parent functions based in this class.

When working with SBML_augment it's imperative to remember this class alters the model object passed as a pointer. Therefore do not make assumptions regarding a model which are the invalidated by this classes functions.
  
 */
class SBML_cleanup : protected SBML_search {
  
 public:

  // ##################################################################################
  // #                               CONSTRUCTOR BLOCK                                #
  // ##################################################################################
  
  //-----------------------------------------------------------------------------------
  /*! \brief Constructor for the SBML_cleaup object
    \b Preconditions: input_doc should be an error free SBMLDocument
    
    \b Postconditions: creates an SBML_cleanup object, where the model we implement the 
    classes methods on is a copy of the one enclosed in the SBMLDocument
  */
  SBML_cleanup(SBMLDocument* input_doc);


  //-----------------------------------------------------------------------------------
    /*! \brief Constructor for the SBML_cleaup object
    \b Preconditions: input_model should be an error free Model
    
    \b Postconditions: creates an SBML_cleanup object, where the model we implement the 
    classes methods on is a copy of input_model
  */
  SBML_cleanup(Model* input_model);


  //-----------------------------------------------------------------------------------
    /*! \brief Constructor for the SBML_cleaup object
    \b Preconditions: input_model should be an error free Model
    
    \b Postconditions: creates an SBML_cleanup object. If copy is set to true, then the 
    cleanup object operates on a copy of input_model. However, if copy is set to false
    then cleanup object operates directly onto input_model.
    
    \b Notes: If copy is selected, ensure you're careful when carrying out future 
    work on that Model object, as the cleanup methods change the models data. 
  */
  SBML_cleanup(Model* input_model, bool copy);
  
  // ##################################################################################
  // #                                 REPLACE BLOCK                                  #
  // ##################################################################################
  
  
  //-----------------------------------------------------------------------------------
    /*! \brief Replace all references to a Function Definition with another Function Definition

    \b Preconditions: inputA and inputB should be valid Function Definition objects
    
    \b Postconditions: Any reference to FunctionDefinition inputA in the model loaded into 
    the cleanup object is replaced by a reference to inputB - inputB replaces inputA
  */
  bool replace(FunctionDefinition* inputA, FunctionDefinition* inputB);

  //-----------------------------------------------------------------------------------
    /*! \brief Replace all references to a Unit Definition with another Unit Definition

    \b Preconditions: inputA and inputB should be valid Unit Definition objects
    
    \b Postconditions: Any reference to UnitDefinition inputA in the model loaded into 
    the cleanup object is replaced by a reference to inputB - inputB replaces inputA
  */
  bool replace(UnitDefinition* inputA, UnitDefinition* inputB);



  //-----------------------------------------------------------------------------------
    /*! \brief Replace all references to a Compartment with another Compartment

    \b Preconditions: inputA and inputB should be valid Compartment objects
    
    \b Postconditions: Any reference to Compartment inputA in the model loaded into 
    the cleanup object is replaced by a reference to inputB - inputB replaces inputA
  */
  bool replace(Compartment* inputA, Compartment* inputB);

  //-----------------------------------------------------------------------------------
    /*! \brief Replace all references to a Compartment with another Compartment

    \b Preconditions: inputA and inputB should be valid Compartment objects
    
    \b Postconditions: Any reference to Compartment inputA in the model loaded into 
    the cleanup object is replaced by a reference to inputB - inputB replaces inputA
  */
  bool replace(Species* inputA, Species* inputB);

  
   //-----------------------------------------------------------------------------------
    /*! \brief Replace all references to a Parameter with another Parameter

    \b Preconditions: inputA and inputB should be valid Parameter objects
    
    \b Postconditions: Any reference to Parameter inputA in the model loaded into 
    the cleanup object is replaced by a reference to inputB - inputB replaces inputA
  */
  bool replace(Parameter* inputA, Parameter* inputB);

  //-----------------------------------------------------------------------------------
    /*! \brief Replace all references to a Initial Assignment with another Initial Assignment

    \b Preconditions: inputA and inputB should be valid Initial Assignment objects
    
    \b Postconditions: Any reference to Initial Assignment inputA in the model loaded into 
    the cleanup object is replaced by a reference to inputB - inputB replaces inputA
  */
  bool replace(InitialAssignment* inputA, InitialAssignment* inputB);
  
  //-----------------------------------------------------------------------------------
    /*! \brief No function

    \b Preconditions: inputA and inputB should be valid Rule objects
    
    \b Postconditions: Actually does nothing - rules cannot be referenced, but for the
    sake of a consistent API we've included this functionality here for now. May be removed
    to avoid confusion in later releases, but at this stage avoiding premature optimization
    
  */
  bool replace(Rule* inputA, Rule* inputB);

  //-----------------------------------------------------------------------------------
    /*! \brief No function

    \b Preconditions: inputA and inputB should be valid Constraint objects
    
    \b Postconditions: Actually does nothing - rules cannot be referenced, but for the
    sake of a consistent API we've included this functionality here for now. May be removed
    to avoid confusion in later releases, but at this stage avoiding premature optimization
    
  */
  bool replace(Constraint* inputA, Constraint* inputB);

  // -----------------------------------------------------------------------------------
    /*! \brief Replace all references to a Reaction with another Reaction

    \b Preconditions: inputA and inputB should be valid Reaction objects
    
    \b Postconditions: Any reference to Reaction  inputA in the model loaded into 
    the cleanup object is replaced by a reference to inputB - inputB replaces inputA
  */
  bool replace(Reaction* inputA, Reaction* inputB);

  
  //-----------------------------------------------------------------------------------
    /*! \brief No function

    \b Preconditions: inputA and inputB should be valid Event objects
    
    \b Postconditions: Actually does nothing - rules cannot be referenced, but for the
    sake of a consistent API we've included this functionality here for now. May be removed
    to avoid confusion in later releases, but at this stage avoiding premature optimization
    
  */
  bool replace(Event* inputA, Event* inputB);

  // -----------------------------------------------------------------------------------
    /*! \brief Returns a pointer to the model the SBML_cleanup object is operating on
    
    \b Preconditions: None

    \b Postconditions: Returns a (non-const) pointer to the object the replace actions
    occur on
    
  */
  
  Model* get_clean_model();

  // -----------------------------------------------------------------------------------
     /*! \brief UNFINISHED - consolidates a models units to avoid duplications
    
    \b Preconditions: None

    \b Postconditions: Is functioning, but is currently not used in SBMLIntegrator. Has
    Not been checked for pathological models or its affect investigated on internal 
    data consistency. DO NOT USE until further notice (~ASH 28/08/2011)
    
  */
  void consolidate_units();
  
 private:
  
  // -----------------------------------------------------------------------------------
  /*! The clean model does not exist anywhere else unless copy is set to false in the constructor - it is initially a deep copy of the model fed into the constructor, but changes made to it via the replace functions only affect this model. As a result, it is the user's responsibility to delete this object to avoid a memory leak.

    If copy is set to false, then clean_model is set to the input_model, and cleanup operations are enacted on the input model!*/ 
  Model* clean_model;
  
  // remove the units in the list of units (number defines the number of units in the list) 

  // -----------------------------------------------------------------------------------
  /*! \brief UNFINISHED - consolidates a models units to avoid duplications
    
    \b Preconditions: None
    
    \b Postconditions: Is functioning, but is currently not used in SBMLIntegrator. Has
    Not been checked for pathological models or its affect investigated on internal 
    data consistency. DO NOT USE until further notice (~ASH 28/08/2011)
    
  */
  void remove_units(ListOfUnitDefinitions* toberemoved, int number);
  
  // Virtual counterparts to the SBML_search virtual functions. 
  // Instead of just returning bool they typically have a switch statement and replace 
  // the reference to the type in the function name from the section and position in
  // the model defined by C and i 

  // virtual bool replace_functiondef - this doesn't exist as it's never needed

  // -----------------------------------------------------------------------------------
  /*!
    \brief Function for replacing some reference to a Unit Definition in a model with another Unit Definition.

    Char C defines what is to be replaced, while int i defines it's location in the model. The possible codes C can be are as follows;

    M - Model Substance Units\n
    T - Model Time Units\n
    V - Model Volume Units\n
    A - Model Area Units\n
    L - Model Length Units\n
    E - Model Extent Units\n
    \n
    C - Compartment Units\n
    S - Species Units\n
    P - Parameter Units\n
    R - Rule Units\n
    X - Reaction Units\n

    For example, replace_unit(inputA, inputB, 'S', 5) would replace the 5th species' unit from inputA to inputB
    
    This is a virtual function, and has a polymorphic variation in SBML_search which simply returns true.

    \b Precondition: Both parameters are valid, depending on the section determined by C.\n 
                     C must be one of those 11 letters listed above (if not the function aborts). \n
                     There must be at least \b i different elements of that type in the loaded model.
    
    \b Postcondition: The reference ID held by "some element", defined by C, which previously was equal to the ID held by inputA (parameter 1) is now set to be equal to the reference ID of inputB (parameter 2). 

  */
  virtual bool replace_unit(UnitDefinition* inputA, UnitDefinition* inputB, char C, int i);
  
  
  
  // -----------------------------------------------------------------------------------
  /*!
    \brief Function for replacing some reference to a Compartment in a model with another Compartment.

    Char C defines what is to be replaced, while int i defines it's location in the model. The possible codes C can be are as follows;
    
    S - Species Compartment\n
    I - Initial Assignment Compartment (Where the assignment variable of an Initial Assignment is a Compartment) \n
    R - Rule Compartment (Where a rule variable is a Compartment)\n
    X - Reaction Compartment\n
    E - Event Assignment Compartment (when one or more assignments in an event assign a Compartment)

    For example, replace_compartment(inputA, inputB, 'S', 5) would replace the 5th Species' Compartment from inputA to inputB
    
    This is a virtual function, and has a polymorphic variation in SBML_search which simply returns true.

    \b Precondition: Both parameters are valid, depending on the section determined by C.\n 
                     C must be one of those 5 letters listed above (if not the function aborts). \n
                     There must be at least \b i different elements of that type in the loaded model.
    
    \b Postcondition: The reference ID held by "some element", defined by C, which previously was equal to the ID held by inputA (parameter 1) is now set to be equal to the reference ID of inputB (parameter 2). 

  */
  virtual bool replace_compartment(Compartment* inputA, Compartment* inputB, char C, int i);

  // -----------------------------------------------------------------------------------
  /*!
    \brief Function for replacing some reference to a Species in a model with another Species.

    Char C defines what is to be replaced, while int i defines it's location in the model. The possible codes C can be are as follows;
      
    I - Initial Assignment Species (Where the assignment variable of an Initial Assignment is a Species) \n
    R - Rule Species (Where a rule variable is a Species)\n
    r - Reaction Reactant\n
    p - Reaction Product\n
    m - Reaction Modifier\n
    E - Event Assignment Species (when one or more assignments in an event assign a Compartment)

    For example, replace_species(inputA, inputB, 'p', 5) would replace a species which 
    is one of the products on the 5th reaction from inputA to inputB
    
    This is a virtual function, and has a polymorphic variation in SBML_search which simply returns true.

    \b Precondition: Both parameters are valid, depending on the section determined by C.\n 
    C must be one of those 6 letters listed above (if not the function aborts). \n
    There must be at least \b i different elements of that type in the loaded model.
		     
    \b Postcondition: The reference ID held by "some element", defined by C, which previously was equal to the ID held by inputA (parameter 1) is now set to be equal to the reference ID of inputB (parameter 2). 

  */
  virtual bool replace_species(Species* inputA, Species* inputB, char C, int i);  

  
  // -----------------------------------------------------------------------------------
  /*!
    \brief Function for replacing some reference to a Parameter in a model with another Parameter.

    Char C defines what is to be replaced, while int i defines it's location in the model. The possible codes C can be are as follows;
      
    S - Species' conversion factor parameter
    I - Initial Assignment symbol value
    R - Rule variable value
    E - Event Assignment variable value

    For example, replace_parameter(inputA, inputB, 'R', 5) would replace the 5th Rule's variable from inputA to inputB
    
    This is a virtual function, and has a polymorphic variation in SBML_search which simply returns true.

    \b Precondition: Both parameters are valid, depending on the section determined by C.\n 
    C must be one of those 4 letters listed above (if not the function aborts). \n
    There must be at least \b i different elements of that type in the loaded model.
    
    \b Postcondition: The reference ID held by "some element", defined by C, which previously was equal to the ID held by inputA (parameter 1) is now set to be equal to the reference ID of inputB (parameter 2). 

  */
  virtual bool replace_parameters(Parameter* inputA, Parameter* inputB, char C, int i);
  


  // virtual bool replace_initial_assignments this doesn't exist as it's never needed
  // virtual bool replace_rules doesn't exist as it's never needed
  // virtual bool replace_constraints doesn't exist as it's never needed
  // virtual bool replace_reactions doesn't exist as it's never needed
  // virtual bool replace_events doesn't exist as it's never needed


// -----------------------------------------------------------------------------------
  /*!
    \brief Function for replacing some variable which is found in an ASTNode with a string value. 


    This is a helper function for replacing data in a MathML structure.

    \b Precondition: ASTNode must be a valid node, and should be of type AST_NAME
    
    \b Postcondition: the name attribute of node (parameter 1) is set to the value of replacement (parameter 2). 

    \b Notes replace_node(node, replacement) means parameter 2 replaces an aspect of parameter 1
    
  */
  virtual bool replace_node(ASTNode* node, std::string replacement);
  

  
};

#endif

  
  
