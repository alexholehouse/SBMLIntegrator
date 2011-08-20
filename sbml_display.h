#ifndef SBML_DISPLAY_H
#define SBML_DISPLAY_H

#include "sbml_ui_general.h"

#include <sbml/SBMLTypes.h>

class SBML_search;

// #############################################################################################
// SBML_display
// Has no attributes, but instead is a function class, encapsulating methods to display data associated with 
// a model, which is fed into the method. This design choise was taken to avoid confusion, where a model is 
// displayed here, but that same model is then changed in another class, creating an inconsistency.
// 
// We've chosen not to make this essentially a static class, but i


class SBML_display : public SBML_UI_general {
  
 public:
  
  // DISPLAY FUNCTIONS - Do what they say on the tin, take a model and display the expected information to the 
  // screen
  
  // Parent display functions
  void show_summary(const Model* inputM, std::string filename);
  void show_all(const Model* inputM);
  
  // specific display functions
  void select_components_to_show(const Model* model, std::string message);
  void show_functionDefinitions(const Model* inputM);
  void show_unitDefinitions(const Model* inputM);
  void show_compartments(const Model* inputM);
  void show_species(const Model* inputM);
  void show_parameters(const Model* inputM);
  void show_initial_assignments(const Model* inputM);
  void show_rules(const Model* inputM);
  void show_constraints(const Model* inputM);
  void show_reactions(const Model* inputM);
  void show_events(const Model* inputM);


  // list elements
  void select_components_to_list(const Model* model, std::string message);
  void list_unit_definitions(const Model* inputM);
  void list_compartments(const Model* inputM);
  void list_species(const Model* inputM);
  void list_parameters(const Model* inputM);
  void list_rules(const Model* inputM);
  void list_reactions(const Model* inputM);

  // additional display functions
  void output_reaction_formula(const Reaction* rxn);
  void output_reaction_modifiers(const Reaction* rxn);
  
  
  /*!
    \breif Function to list the species type (reactant, product or modifier) with the format [number] - ID 

    \b Preconditions: Reaction must be a valid reaction

    \b Postconditions: type must be 0 (reactants) 1 (products) or 2 (modifiers). Note that if it is not one of these three the program aborts automatically.

    */
  void list_reaction_species(int type, Reaction* rxn);
  
  
  // disclaimer set to true means a warning message regarding ID uniqueness is displayed
  int compare(std::string title, std::string A, std::string B, bool disclaimer);

  // disclaimer set to true means a warning message regarding ID uniqueness is displayed
  int compare3way(std::string title, std::string A, std::string B, std::string C, bool disclaimer);

  // the definition for this is in sbml_search.h!!!!
  template <class T> 
    int compare_units(const T compA, const T compB, const Model* modelA, const Model* modelB);
  
  
};


#endif
