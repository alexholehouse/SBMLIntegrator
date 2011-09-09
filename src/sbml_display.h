// Copyright Alex Holehouse 2011
// Distributed under the terms of the GNU general public license - see COPYING.txt for more details

#ifndef SBML_DISPLAY_H
#define SBML_DISPLAY_H

#include "sbml_ui_general.h"


#include <sbml/SBMLTypes.h>

// included as a forward class declarition to avoid cyclic dependencies
class SBML_search;

/*! \brief Class for outputting and describing components and lists to the standard output
 *   
SBML_display is a class for printing lists or individual elements to the standard output. Inheriting from the UI_general class and using SBML_search object instances for lookup purposes, it is a standalone class with no attributes, instead requiring Model* for each display function. This ensures that any call will display a specific element, and not one pre-loaded which may or may not have changed depending on what has happened to the underlying data structure.

*/

class SBML_display : public SBML_UI_general {
  
 public:
  
  // DISPLAY FUNCTIONS - Do what they say on the tin, take a model and display the expected information to the 
  // screen
  
  // Parent display functions
  /** \brief Displays a summary of the models parameters

      Shows a basic summary of the model in the format \n

      File name ---------------- \n
      Model ID ----------------- \n
      Model name --------------- \n
      Model version ------------ \n
      Model level -------------- \n
      Model substance units ---- \n
      Model time units --------- \n
      Model volume units ------- \n
      Model area units --------- \n
      Model length units ------- \n
      Model extent units ------- \n
      Model conversion factor -- \n
      ---------------------------------\n
      Summary of model components\n
      ---------------------------------\n
      No of functions ----------- \n
      No of unit definitions --- \n
      No of compartments ------- \n
      No of species ------------ \n
      No of parameters --------- \n
      No of initial assignments  \n
      No of rules -------------- \n
      No of constraints -------- \n
      No of reactions ---------- \n
      No of events ------------- \n
      ----------------------------------\n
  **/
  void show_summary(const Model* inputM, std::string filename);

  /** \brief Runs through and displays all the elements from a model be sequentially calling the show_* functions **/
  void show_all(const Model* inputM);
  
  // specific display functions
  /** \brief Interactive command line selector to chose which list of elements you wish to show **/
  void select_components_to_show(const Model* model, std::string message);
  
  /** \brief Displays a models function definitions **/
  void show_functionDefinitions(const Model* inputM);
  
  /** \brief Displays a models unit definitions **/
  void show_unitDefinitions(const Model* inputM);
  
  /** \brief Displays a models compartment **/
  void show_compartments(const Model* inputM);

  /** \brief Displays a models species **/
  void show_species(const Model* inputM);

  /** \brief Displays a models parameters **/
  void show_parameters(const Model* inputM);

  /** \brief Displays a models initial assignments **/
  void show_initial_assignments(const Model* inputM);

  /** \brief Displays a models rules **/
  void show_rules(const Model* inputM);

  /** \brief Displays a models constraints**/
  void show_constraints(const Model* inputM);

  /** \brief Displays a models reactions**/
  void show_reactions(const Model* inputM);

  /** \brief Displays a models events **/
  void show_events(const Model* inputM);


  // list elements
  /** \brief Interactive command line selector to chose which list of elements you wish to list **/
  void select_components_to_list(const Model* model, std::string message);

  /** \brief Lists a models unit definitions**/
  void list_unit_definitions(const Model* inputM);
  
  /** \brief Lists a models compartments**/
  void list_compartments(const Model* inputM);
  
  /** \brief Lists a models species**/
  void list_species(const Model* inputM);

  /** \brief Lists a models parameters**/
  void list_parameters(const Model* inputM);

  /** \brief Lists a models rules**/
  void list_rules(const Model* inputM);
  
  /** \brief Lists a models reactions**/
  void list_reactions(const Model* inputM);

  // additional display functions

  /** \brief Displays a reactions formula in a standard chemical manner (A + B <--> C) **/
  void output_reaction_formula(const Reaction* rxn);
  
  /** \brief Displays a reaction's modifier species **/
  void output_reaction_modifiers(const Reaction* rxn);
  
  
  /*!
    \brief Function to list the species type (reactant, product or modifier)
  */
  void list_reaction_species(int type, Reaction* rxn);
  
  /** \brief Function to display a standard message asking the user to select between A and B.

      \b Preconditions: A and B should be valid option in a [CHOSE "A" or CHOSE "B"] context.
      \b Postconditions: If disclaimer is true, the output includes a disclaimer message on data integrity. Returns 0 for A and 1 for B

   **/
  int compare(std::string title, std::string A, std::string B, bool disclaimer);

  /** \brief Function to display a standard message asking the user to select between A, B or C

      \b Preconditions:  A and B should be valid option in a [CHOSE "A" or CHOSE "B" or CHOSE "C"] context.

      \b Postconditions: If disclaimer is true, the output includes a disclaimer message on data integrity. Returns 0 for A, 1 for B and 2 for C

   **/
  int compare3way(std::string title, std::string A, std::string B, std::string C, bool disclaimer);

    /** \brief Function to chose between two elements' units

      \b Preconditions:  compA and compB should both allow for the getUnit() function on them. 

      \b Postconditions:  Allows the user to select between the two unit definitions, return 0 for compAs and 1 for compBs

      \b Notes: Definition is in sbml_search.h as it uses the unit lookup functions in the sbml_search class. 

   **/
  template <class T> 
    int compare_units(const T compA, const T compB, const Model* modelA, const Model* modelB);
  
  
};


#endif
