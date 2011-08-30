// Copyright Alex Holehouse 2011
// Distributed under the terms of the GNU general public license - see COPYING.txt for more details

#ifndef SBML_UI_MAIN_H
#define SBML_UI_MAIN_H

#include <sbml/SBMLTypes.h>
#include "sbml_ui_general.h"
#include "sbml_display.h"
#include "sbml_cleanup.h"
#include "sbml_integrate.h"
#include "sbml_confInput.h"

/*! User Interface class for main menu. For alpha this is remaining very simple, though in later releases we may refactor a lot of the UI methods from SBML_formatter and any subclasses into here.
  !*/

class SBML_UI_main : public SBML_UI_general {

 private:
  
 public:

  // #############################################################################################
  /*! \b Overview: Simple class which displays the welcome to SBML screen

    \b Preconditions: None

    \b Postconditions: Display welcome version and version to standard output

    !*/ 
  void intro();
  
  // #############################################################################################
  /*! \b Overview: Shows the main splashscreen for the software, giving users a range of options to select different activitues

    \b Preconditions: Bool should be set to true if model integration is possible (i.e. two valid models have loaded) or false if not

    \b Postconditions: Returns the following value depending on the users choice;

    Integration true;
    1 - Explore models
    2 - Display model summary
    3 - Integrate models
    4 - Quit
    
    Integration false
    1 - Explore models
    2 - Display model summary
    3 - Quit

    

    !*/   
  int main_screen_display(bool integrate, bool reset);
  
  // #############################################################################################
  void print_help();

  // #############################################################################################
  void print_usage();
  
  // #############################################################################################
  void print_version();
  
  // #############################################################################################
  void print_logo();
  
  // #############################################################################################
  void explore_models(Model* model1, Model* model2, SBML_display* display_framework, string model1_name, string model2_name);
  
};

#endif
  
