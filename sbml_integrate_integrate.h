#ifndef SBML_INTEGRATE_INTEGRATE_H
#define SBML_INTEGRATE_INTEGRATE_H

#include "sbml_integrate_helper.h"
#include "sbml_confInput.h"
#include "sbml_display.h"
#include "sbml_cleanup.h"
#include "sbml_listpair_container.cpp"
#include <iostream>
#include <sbml/SBMLTypes.h>


class SBML_integrate_integrate : SBML_integrate_helper {
  
 public:
  
  SBML_integrate_integrate(Model* _model_new);
  
  // #############################################################################################
  void integrate_functionDefinitions(SBML_confInput& input_file, Model* model_new, 
				     SBML_listpair_container<ListOfFunctionDefinitions>& listpair);
  
  // #############################################################################################
  void integrate_unitDefinitions(SBML_confInput& input_file, Model* model_new, 
				 SBML_listpair_container<ListOfUnitDefinitions>& listpair);

  // #############################################################################################
  void integrate_compartments(SBML_confInput& input_file, Model* model_new, 
			      SBML_listpair_container<ListOfCompartments>& listpair);

  // #############################################################################################
  void integrate_species(SBML_confInput& input_file, Model* model_new, 
			 SBML_listpair_container<ListOfSpecies>& listpair);
  
  // #############################################################################################
  void integrate_parameters(SBML_confInput& input_file, Model* model_new, 
			    SBML_listpair_container<ListOfParameters>& listpair);
  
  // #############################################################################################
  void integrate_initialAssignments(SBML_confInput& input_file, Model* model_new);

  // #############################################################################################
  void integrate_rules(SBML_confInput& input_file, Model* model_new);
  
  
  // #############################################################################################
  void integrate_constraints(SBML_confInput& input_file, Model* model_new);

  // #############################################################################################
  void integrate_reactions(SBML_confInput& input_file, Model* model_new, 
			   SBML_listpair_container<ListOfReactions>& listpair);


  
  // #############################################################################################
  void integrate_events(SBML_confInput& input_file, Model* model_new, 
			SBML_listpair_container<ListOfEvents>& listpair);
  
 private:
  
  SBML_display display_framework;
  SBML_cleanup* cleanup_framework;
  Model* model_new;
  
  // _____________________________________________________________________________________________
  // :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
  // update list functions - where an element has an ID which may need to replaced in the model 
  void replacement_list_update(FunctionDefinition* inNew_copy, FunctionDefinition* tempB, 
			       ListOfFunctionDefinitions* rep_functionDefinitionsA, 
			       ListOfFunctionDefinitions* rep_functionDefinitionsB,
			       int& rep_functionDefinitions_num);

  // _____________________________________________________________________________________________
  // :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
  void replacement_list_update(UnitDefinition* inNew_copy, UnitDefinition* tempB, 
			       ListOfUnitDefinitions* rep_unitDefinitionsA, 
			       ListOfUnitDefinitions* rep_unitDefinitionsB, 
			       int& rep_unitDefinitions_num);
  
  
  // _____________________________________________________________________________________________
  // :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
  void replacement_list_update(Compartment* inNew_copy, Compartment* tempB, 
			       ListOfCompartments* rep_compartmentsA, 
			       ListOfCompartments* rep_compartmentsB, 
			       int& rep_compartments_num);
  
  // _____________________________________________________________________________________________
  // :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
  void replacement_list_update(Species* inNew_copy, Species* tempB, 
			       ListOfSpecies* rep_speciesA, 
			       ListOfSpecies* rep_speciesB, 
			       int& rep_species_num);
  
  // _____________________________________________________________________________________________
  // :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
  void replacement_list_update(Parameter* inNew_copy, Parameter* tempB, 
			       ListOfParameters* rep_parametersA, 
			       ListOfParameters* rep_parametersB, 
			       int& rep_parameters_num);
  
  // _____________________________________________________________________________________________
  // :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
  void replacement_list_update(Reaction* inNew, Reaction* inNew_copy, Reaction* tempB, 
			       ListOfReactions* rep_reactionsA, 
			       ListOfReactions* rep_reactionsB, 
			       int& rep_reactions_num);

  // _____________________________________________________________________________________________
  // :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
  void replacement_list_update(Event* inNew_copy, Event* tempB, 
			       ListOfEvents* rep_eventsA, 
			       ListOfEvents* rep_eventsB, 
			       int& rep_events_num);
  
  // #############################################################################################
  // rules helper functions
  int rule_by_formula(Rule* search_target);

  // #############################################################################################

  // reaction helper functions
  void edit_reaction(Reaction* inNew, Reaction* inNew_copy, Reaction* tempB, int current, 
		     int total, SBML_listpair_container<ListOfReactions>& listpair);
  
  // _____________________________________________________________________________________________
  // :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
  char edit_reaction_ui();
  
  // _____________________________________________________________________________________________
  // :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
  void reactions_overview(const Reaction* reaction);
  
  // _____________________________________________________________________________________________
  // :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
  void reaction_seperator(const Reaction* tempA, const Reaction* tempB);
  
  // _____________________________________________________________________________________________
  // :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
  void edit_reaction_formula(Reaction* inNew_copy, Reaction* tempB);
  
  // _____________________________________________________________________________________________
  // :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
  void edit_reaction_formula_reactants(Reaction* inNew_copy, Reaction* tempB);
  
  // _____________________________________________________________________________________________
  // :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
  void edit_reaction_formula_products(Reaction* inNew_copy, Reaction* tempB);
  
  // _____________________________________________________________________________________________
  // :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
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
  
  
};

#endif

