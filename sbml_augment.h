#ifndef SBML_AUGMENT_H
#define SBML_AUGMENT_H

#include "sbml_ui_general.h"
#include "sbml_cleanup.h"
#include <sbml/SBMLTypes.h>
#include <iostream>
#include <fstream>

/*!
  Class specifically for model-wide augmentation, and associated helper functions. 
  !*/

class SBML_augment : public SBML_UI_general {

 public:
  
  SBML_augment(Model* model);
  
  
  void complete_model_id_rename_with_append(std::string to_append);
  
  template <class T> void replace_reference_in_model(T* element, std::string new_ref){
    std::string id_var;
    T* elcop = element->clone();
    
    id_var = elcop->getId();

    elcop->setId(id_var.append(new_ref));
    
    std::cout << ".";
    cleanup.replace(element, elcop);
  }
  
 private:

  SBML_cleanup cleanup;
  Model* model;
  
  /*
  void rename_all_functionDefinitions_with_append(Model* model, std::string to_append);
  void rename_all_unitDefinitions_with_append(Model* model, std::string to_append);
  void rename_all_compartments_with_append(Model* model, std::string to_append);
  void rename_all_species_with_append(Model* model, std::string to_append);
  void rename_all_parameters_with_append(Model* model, std::string to_append);
  void rename_all_initialAssignments_with_append(Model* model, std::string to_append);
  void rename_all_rules_with_append(Model* model, std::string to_append);
  void rename_all_constraints_with_append(Model* model, std::string to_append);
  void rename_all_reactions_with_append(Model* model, std::string to_append);
  void rename_all_events_with_append(Model* model, std::string to_append);
  */
};

#endif
