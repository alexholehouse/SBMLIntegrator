// Copyright Alex Holehouse 2011
// Distributed under the terms of the GNU general public license - see COPYING.txt for more details

#ifndef SBML_AUGMENT_H
#define SBML_AUGMENT_H

#include "sbml_ui_general.h"
#include "sbml_cleanup.h"
#include <sbml/SBMLTypes.h>

/*! \brief Class specifically for model-wide augmentation, and associated helper functions.
 *   
SBML_augment is a class for making model-wide changes. Currently it's primary role is housing the method complete_model_id_rename_with_append(string to_append), a method to append a string onto every ID in a model. In the future additional system wide functionality such as rescaling will be implemented at least through parent functions based in this class.

When working with SBML_augment it's imperative to remember this class alters the model object passed as a pointer. Therefore do not make assumptions regarding a model which are the invalidated by this classes functions.
  
 */

class SBML_augment : public SBML_UI_general {

 public:
  	
  /*! \brief Constructor method for SBML_augment

    \b Preconditions: model is a valid Model pointer 
    
    \b Postconditions: creates an SBML_augment object with the model argument as the classes target Model. Means any operations performed on that object will affect the model argument. SBML_augment has it's own SBML_cleanup object internally which is constructed using that same model object passed as a parameter.

  */
  SBML_augment(Model* model);
  
  
    /*!
    \brief Adds a string onto every ID into a model

    \b Preconditions: to_append must be a valid string under 100 characters (arbitrary length set, could be changed in future)

    \b Postconditions: appends the "to_append" string to every SID on every element in the model, except the model's name

    */
  void complete_model_id_rename_with_append(std::string to_append);
  

      /*!
    \brief Template function to replace a reference to some ID in a model with another ID

    \b Preconditions: T should be an SBML type where the getId() method can be used (i.e. a FunctionDefinition, UnitDefinition, Compartment, Species, Parameter, Reaction and Event). Do *NOT* pass any other type into this method.

    \b Postconditions: Appends new_ref onto the end of the elements ID, and then goes about calling the replace method from the classes SBML_cleanup object to replace every reference to the original element ID with it's new ID
    */
  template <class T> void replace_reference_in_model(T* element, std::string new_ref){

    // elcop is a cloned copy of element - note we use elcop simply as an argument for the 
    // cleanup.replace method, it is then discarded at the end of this function
    
    std::string id_var;
    T* elcop = element->clone();
    
    // get the ID value of element elcop shares the same value)
    id_var = elcop->getId();
    
    // set the ID of elcop to the original element id + the new_ref
    elcop->setId(id_var.append(new_ref));
    
    // replace requires two objects. This is to facilitate deep replacement in future 
    // implementations
    cleanup.replace(element, elcop);
  }
  
 private:

  /// SBML_cleanup object used to enact searching operations
  SBML_cleanup cleanup;

  /// Model pointer to the SBML model being augmented
  Model* model;
  
};

#endif
