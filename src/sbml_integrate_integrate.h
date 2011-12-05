// Copyright Alex Holehouse 2011
// Distributed under the terms of the GNU general public license - see COPYING.txt for more details

#ifndef SBML_INTEGRATE_INTEGRATE_H
#define SBML_INTEGRATE_INTEGRATE_H

#include "sbml_integrate_helper.h"
//#include "sbml_confInput.h"
#include "sbml_display.h"
//#include "sbml_cleanup.h"
#include "sbml_listpair_container.cpp"
#include <sbml/SBMLTypes.h>

class SBML_confInput;
class SBML_cleanup;

/*!
  \brief Class which contains integration functionality, allowing users to integrate two SBML elements together
    
  Each SBML element has unique set of attribute, so each integration function is subtly different, although uses a consistent set of concepts to achieve the task. Uses function from superclasses to facilitate a consistent user interface experience.
 
*/

class SBML_integrate_integrate : SBML_integrate_helper {
  
 public:
  
  /** \brief Constructor function **/
  SBML_integrate_integrate(Model* _model_new);
  
  
  // #############################################################################################
  /*!
    \brief Interactive function definition integration based on integrate list
    
    Not yet implemented
 
  */
  void integrate_functionDefinitions(SBML_confInput& input_file, Model* model_new, 
				     SBML_listpair_container<ListOfFunctionDefinitions>& listpair);
  
  // #############################################################################################
  /*!
    \brief Interactive unit definition integration based on integrate list

    \b Preconditions: input_file must have already loaded it's data, model_new should be a valid model, list pair should be a valid SBML_listpair_container with replacement pairs

    \b Postconditions: An interactive integration between the two unit definitions occurs, giving the user the option to have this new integration element replace the original one, or be an additional element
  */
  
  void integrate_unitDefinitions(SBML_confInput& input_file, Model* model_new, 
				 SBML_listpair_container<ListOfUnitDefinitions>& listpair);

  // #############################################################################################  
  /*!
    \brief Interactive compartment integration based on integrate list

    \b Preconditions: input_file must have already loaded it's data, model_new should be a valid model, listpair should be a valid SBML_listpair_container with replacement pairs
    
    \b Postconditions: An interactive integration between the two compartments occurs, giving the user the option to have this new integration element replace the original one, or be an additional element
  */
  
  void integrate_compartments(SBML_confInput& input_file, Model* model_new, 
			      SBML_listpair_container<ListOfCompartments>& listpair);

  // #############################################################################################  
  /*!
    \brief Interactive species integration based on integrate list

    \b Preconditions: input_file must have already loaded it's data, model_new should be a valid model, listpair should be a valid SBML_listpair_container with replacement pairs

    \b Postconditions: An interactive integration between the two species occurs, giving the user the option to have this new integration element replace the original one, or be an additional element
  */
  
  void integrate_species(SBML_confInput& input_file, Model* model_new, 
			 SBML_listpair_container<ListOfSpecies>& listpair);
  
  // #############################################################################################

    /*!
    \brief Interactive parameter integration based on integrate list

    \b Preconditions: input_file must have already loaded it's data, model_new should be a valid model, listpair should be a valid SBML_listpair_container with replacement pairs

    \b Postconditions: An interactive integration between the two parameters occurs, giving the user the option to have this new integration element replace the original one, or be an additional element
  */
  
  void integrate_parameters(SBML_confInput& input_file, Model* model_new, 
			    SBML_listpair_container<ListOfParameters>& listpair);
  
  // #############################################################################################
  /*!
    \brief Interactive initial assignment integration based on integrate list
    
    Not yet implemented
 
  */
  void integrate_initialAssignments(SBML_confInput& input_file, Model* model_new);

  // #############################################################################################
  /*!
    \brief Interactive rules integration based on integrate list

    \b Preconditions: input_file must have already loaded it's data, model_new should be a valid model, listpair should be a valid SBML_listpair_container with replacement pairs

    \b Postconditions: An interactive integration between the two rules occurs, giving the user the option to have this new integration element replace the original one, or be an additional element
  */
    
  void integrate_rules(SBML_confInput& input_file, Model* model_new);
  
  
  // #############################################################################################
    // #############################################################################################
  /*!
    \brief Interactive constraint integration based on integrate list
    
    Not yet implemented
 
  */
  void integrate_constraints(SBML_confInput& input_file, Model* model_new);

  // #############################################################################################
  /*!
    \brief Interactive reaction integration based on integrate list

    \b Preconditions: input_file must have already loaded it's data, model_new should be a valid model, listpair should be a valid SBML_listpair_container with replacement pairs

    \b Postconditions: An interactive integration between the two reactions occurs, giving the user the option to have this new integration element replace the original one, or be an additional element
  */
  
  
  void integrate_reactions(SBML_confInput& input_file, Model* model_new, 
			   SBML_listpair_container<ListOfReactions>& listpair);


  
  // #############################################################################################
  // #############################################################################################
  /*!
    \brief Interactive event integration based on integrate list
    
    Not yet implemented
 
  */
  void integrate_events(SBML_confInput& input_file, Model* model_new, 
			SBML_listpair_container<ListOfEvents>& listpair);
  
 private:
  

  /// display framework object for running display operations through
  SBML_display display_framework;

  /// cleanup framework for running replacements through
  SBML_cleanup* cleanup_framework;

  /// integration model pointer
  Model* model_new;
  
  // _____________________________________________________________________________________________
  // :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
  // update list functions - where an element has an ID which may need to replaced in the model 
  /** \brief Update the replacement list with a new function definition
      
      Not yet implemented
    **/


  void replacement_list_update(FunctionDefinition* inNew_copy, FunctionDefinition* tempB, 
			       ListOfFunctionDefinitions* rep_functionDefinitionsA, 
			       ListOfFunctionDefinitions* rep_functionDefinitionsB,
			       int& rep_functionDefinitions_num);

  // _____________________________________________________________________________________________
  // :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
  /** \brief Update the replacement list with a new unit definition
      
      Helper function which invokes a UI function to ascertain if the newly created unit definition should replace the previous integration model version, or simply add a new unit definition. If it is to replace the previous one we update the replacement list and run a replacement on the model
  **/
  void replacement_list_update(UnitDefinition* inNew_copy, UnitDefinition* tempB, 
			       ListOfUnitDefinitions* rep_unitDefinitionsA, 
			       ListOfUnitDefinitions* rep_unitDefinitionsB, 
			       int& rep_unitDefinitions_num);
  
  
  // _____________________________________________________________________________________________
  // :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
  /** \brief Update the replacement list with a new compartment
      
      Helper function which invokes a UI function to ascertain if the newly created compartment should replace the previous integration model version, or simply be added as a new compartment. If it is to replace the previous one we update the replacement list and run a replacement on the model
  **/
  void replacement_list_update(Compartment* inNew_copy, Compartment* tempB, 
			       ListOfCompartments* rep_compartmentsA, 
			       ListOfCompartments* rep_compartmentsB, 
			       int& rep_compartments_num);
  
  // _____________________________________________________________________________________________
  // :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
  /** \brief Update the replacement list with a new species
      
      Helper function which invokes a UI function to ascertain if the newly created species should replace the previous integration model version, or simply be added as a new species. If it is to replace the previous one we update the replacement list and run a replacement on the model
  **/
  void replacement_list_update(Species* inNew_copy, Species* tempB, 
			       ListOfSpecies* rep_speciesA, 
			       ListOfSpecies* rep_speciesB, 
			       int& rep_species_num);
  
  // _____________________________________________________________________________________________
  // :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
  /** \brief Update the replacement list with a new parameter
      
      Helper function which invokes a UI function to ascertain if the newly created parameter should replace the previous integration model version, or simply be added as a new parameter. If it is to replace the previous one we update the replacement list and run a replacement on the model
  **/
  void replacement_list_update(Parameter* inNew_copy, Parameter* tempB, 
			       ListOfParameters* rep_parametersA, 
			       ListOfParameters* rep_parametersB, 
			       int& rep_parameters_num);
  
  // _____________________________________________________________________________________________
  // :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
  /** \brief Update the replacement list with a new reaction
      
      Helper function which invokes a UI function to ascertain if the newly created reaction should replace the previous integration model version, or simply be added as a new reaction. If it is to replace the previous one we update the replacement list and run a replacement on the model
    **/
  void replacement_list_update(Reaction* inNew, Reaction* inNew_copy, Reaction* tempB, 
			       ListOfReactions* rep_reactionsA, 
			       ListOfReactions* rep_reactionsB, 
			       int& rep_reactions_num);

  // _____________________________________________________________________________________________
  // :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
  /** \brief Update the replacement list with a new unit definition
      
      Not yet implemented
    **/
  void replacement_list_update(Event* inNew_copy, Event* tempB, 
			       ListOfEvents* rep_eventsA, 
			       ListOfEvents* rep_eventsB, 
			       int& rep_events_num);
  
  // #############################################################################################
  // rules helper functions
  int rule_by_formula(Rule* search_target);

  // #############################################################################################

  // reaction helper functions
  /*!
    \brief Parent function allowing the user to integrate two reactions together

    \b Preconditions:
    inNew, inNew_copy and tempB should all be valid reactions, where inNew and inNew_copy are identical and represent the integration/base model  reactions which tempB is the import model reaction. Current represent the index of the reaction being integrated, total being the total number of reactions to be done (allowing the user to keep track of progress). Listpair is the replacement listpair container for reactions

    \b Postconditions: Through a number of helper functions the two reactions are integrated, and the new one either replaces the previous reaction of is added in addition to it.
  */
  void edit_reaction(Reaction* inNew, Reaction* inNew_copy, Reaction* tempB, int current, 
		     int total, SBML_listpair_container<ListOfReactions>& listpair);
  
  // _____________________________________________________________________________________________
  // :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

  /*!
    \brief User interface for the reaction integration process

    Provides the following interface, returning one of the values listed as a char;\n

    Please select an option\n
    [1] ----------- Edit Name\n
    [2] ----------- Edit Formula\n
    [3] ----------- Edit Stoichiometry\n
    [4] ----------- Edit Modifiers\n
    [5] ----------- Edit Kinetic Law\n
    [6] ----------- Get model Information\n
    [7] ----------- Continue \n
    Select: \n
    \n
  */
  char edit_reaction_ui();
  
  // _____________________________________________________________________________________________
  // :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
  
  /*!
    \brief UI function to display a summary of the reaction
    
    Outputs;
    Comparing  and \n
    [Reaction 1 of 1]\n\n


    Reaction we're integrating into that model:\n
    ID: \n
    Name:        \n
    Formula:     \n
    Rxn modifiers:\n
    Kinetic Law:  \n
    ----------------------------------------\n\n

  */
  
  void reactions_overview(const Reaction* reaction);
  
  // _____________________________________________________________________________________________
  // :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

  /**
     \brief Reaction description header output to STDOUT
     
   **/
  void reaction_seperator(const Reaction* tempA, const Reaction* tempB);
  
  // _____________________________________________________________________________________________
  // :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
  /**
     \brief UI function to select if you are to edit a reactions reactants or products
     
     \b Preconditions: Both must be valid reactions

    \b Postconditions: User chooses to edit reactants or products, which invokes another interaction screen
    
   **/
  void edit_reaction_formula(Reaction* inNew_copy, Reaction* tempB);
  
  // _____________________________________________________________________________________________
  // :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
  /**
     \brief UI function to add or remove reactants fom a reaction
  **/
  void edit_reaction_formula_reactants(Reaction* inNew_copy, Reaction* tempB);
  
  // _____________________________________________________________________________________________
  // :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
  /**
     \brief UI function to add or remove reactants fom a reaction
  **/
  void edit_reaction_formula_products(Reaction* inNew_copy, Reaction* tempB);
  
  // _____________________________________________________________________________________________
  // :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
  
    /**
       \brief UI function to add or remove modifiers fom a reaction
    **/
  void edit_reaction_modifiers(Reaction* inNew_copy);
  
  // _____________________________________________________________________________________________
  // :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
  void edit_stoichiometry(Reaction* inNew_copy);
  
  // _____________________________________________________________________________________________
  // :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
  /*! Add a species reference (reactant or product) to inNew_copy
    
    \b<Preconditions>: inNew_copy and tempB must be valid reactions, with the same SBML level and SBML version, and inNew_copy should be a reaction which has originated from model_new in this class.
    \b<Postconditions>: An additional species is added to either the reactants list or the products list of inNew_copy. Which depends if the "reactant" flag is set to true (reactant added) or false (product added). 

    \b<Notes>: Initially the user can select if they wish to take a species reference from the corresponding list of tempB - i.e. if they're adding a reactant, initially they are faced with a list of reactants in tempB and asked if they wish to import any of these. If not, the entire list of species are offered to add, and Species are converted into SpeciesReferences using SBML_formatter::species2SpeciesReference(...). To ensure data consistency, we only allow the addition of species which exist in the model taht inNew_copy originates from (model_new) at the time of this alteration. !*/
  void add_speciesRef(Reaction* inNew_copy, Reaction* tempB, bool reactant);
  
  // _____________________________________________________________________________________________
  // :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
  /*! Remove a species reference (reactant or product) to inNew_copy
    
    \b<Preconditions>: inNew_copy and tempB must be valid reactions, with the same SBML level and SBML version, and inNew_copy should be a reaction which has originated from model_new in this class.
    \b<Postconditions>: An speciesRefernece is removed from either the reactants list or the products list of inNew_copy. Which depends if the "reactant" flag is set to true (reactant added) or false (product added). 

    \b<Notes>: The user is shown the contents of the reactions product list, and they are then asked to select which product(s) to remove from this list. These reaction species are removed from the list and the underlying object destroyed (though not the Species which the speciesReference is referring to !*/
  void remove_speciesRef(Reaction* rxn, bool reactant);
  
  // returns 0 if new element ID is not to replace anything in the model
  // return 1 if the new element ID is to replace references to Bs ID
  // returns if the new elememnt is to to replace reference to As 
  int for_replacement_UI(std::string newID, std::string oldBID);

  // prints a message to STDOUT relating to selecting a new ID for an element
  void new_ID_message(std::string item);
  
  // standard message if nothing to integrate exists
  void nothing_to_integrate(string item);
};

#endif

