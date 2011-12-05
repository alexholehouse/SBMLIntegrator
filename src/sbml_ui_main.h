// Copyright Alex Holehouse 2011
// Distributed under the terms of the GNU general public license - see COPYING.txt for more details

#ifndef SBML_UI_MAIN_H
#define SBML_UI_MAIN_H

#include "sbml_ui_general.h"

class SBML_display;



  /*!
    \brief UI class for the main interaction

    User Interface class for main menu. For alpha this is remaining very simple, though in later releases we may re-factor a lot of the UI methods from SBML_formatter and any subclasses into here.
    !*/

class SBML_UI_main : public SBML_UI_general {

 private:
  
 public:

  // #############################################################################################
  /*! \b Overview: Simple class which displays the welcome to SBML screen

    \b Preconditions: None

    \b Postconditions: Display welcome version and version to standard output

    */ 
  void intro();
  
  // #############################################################################################
  /*! \b Overview: Shows the main splash screen for the software, giving users a range of options to select different activities

    \b Preconditions: Bool should be set to true if model integration is possible (i.e. two valid models have loaded) or false if not

    \b Postconditions: Returns the following value depending on the users choice;

    Integration true;\n
    1 - Explore models\n
    2 - Display model summary\n
    3 - Integrate models\n
    4 - Quit\n \n
    
    Integration false\n
    1 - Explore models\n
    2 - Display model summary\n
    3 - Quit\n\n
    
  */   
  int main_screen_display(bool integrate, bool reset);
  
  // #############################################################################################
  /// \brief Print command line help for software initialization
  void print_help();

  // #############################################################################################
  /// \brief Print command line usage instructions
  void print_usage();
  
  // #############################################################################################
  /// \brief Print version 
  void print_version();
  
  // #############################################################################################
  /// \brief Print SBMLIntegrator logo
  void print_logo();
  
  // #############################################################################################
  /** \brief select one of the input models to explore and view the internal elements of 
      
      \b Preconditions: model1 and model2 should have the corresponding filenames of model1_name and model2_name. display_framework should refer to a constructed and intialized object

      \b Postconditions: The user selects one of model1 and model2 to explore, which triggers other methods from the display_framework to cause model exploration
      
   **/
  void explore_models(Model* model1, Model* model2, SBML_display* display_framework, std::string model1_name, std::string model2_name);
  
};

#endif
  
