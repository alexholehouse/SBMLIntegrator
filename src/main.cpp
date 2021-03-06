#include "sbml_ui_main.h"

#include <sbml/SBMLTypes.h>
#include <iostream>
#include <cstring>

using namespace std;

int main (int argc, char* argv[])
{
 
  SBML_display *display_object=NULL;
  SBMLDocument* document1=NULL;
  SBMLDocument* document2=NULL;
  
  SBML_integrate* integrate_framework=NULL;
  
  int offset = 0;
  bool integrate = false;
  bool exit = false;
  
  // output of main
  int decision;
  SBML_UI_main interface;
  
  // if no arguments provided, or only one argument provided and that argument isn't 
  // --help or --version
  if (argc == 1)
    {
      interface.print_usage();
      return 0;
    }
    
  // print usage help
  if (0 == strcmp(argv[1], "--help"))
    {
      interface.print_help();
      return 0;
    }
  
  if (0 == strcmp(argv[1], "--version")){
    interface.print_version();
    return 0;
  }
  
  if ( argc == 3 && (0 == strcmp(argv[1], argv[2])))
    {
      cerr << "Model1 and model2 cannot be the same mode" << endl;
      return 0;
    }

  if (argc == 3 && (0 == strcmp(argv[1], "-o")))
    offset = 1;

  if (argc == 3 && (0 != strcmp(argv[1], "-o")))
    integrate = true;

  if (argc == 4 && (0 != strcmp(argv[1], "-o"))){
    interface.print_usage();
    return 0;
  }

  if (argc == 4){
    offset = 1;
    integrate = true;
  }
  
  document1 = readSBML(argv[1+offset]);
  unsigned int errors1 = document1->getNumErrors();

  cout << endl;
  cout << "  filename: " << argv[1+offset] << endl;
  cout << "  error(s): " << errors1  << endl;
  cout << endl;
  
  if (errors1 > 0){
    document1->printErrors(cerr);
    cout << endl;
    interface.print_usage();
    cerr << "Exiting..." << endl;
    return 1;
  }

  display_object = new SBML_display;
  
  if (integrate){
    document2 = readSBML(argv[2+offset]);
    unsigned int errors2 = document2->getNumErrors();
    
    cout << endl;
    cout << "  filename: " << argv[2+offset] << endl;
    cout << "  error(s): " << errors2  << endl;
    cout << endl;
    
  
    if (integrate && errors2 > 0){
      document2->printErrors(cerr);
      cout << endl;
      interface.print_usage();
      cerr << "Exiting..." << endl;
      return 1;
    }
    
    integrate_framework = new SBML_integrate(document1->getModel(), document2->getModel(), argv[1+offset], argv[2+offset]);
    
  }
  
  // intro splashscreen!
  interface.print_logo();
  interface.intro();

  bool repeat_run = false;
  
  while (!exit){
    
    decision = interface.main_screen_display(integrate, repeat_run);
    
    repeat_run = true;
    
    switch (decision)
      {  
      case 1:
	if (!integrate){
	  display_object->select_components_to_show(document1->getModel(), "Model");
	}
	
	else {
	  interface.explore_models(document1->getModel(), 
				   document2->getModel(), 
				   display_object, 
				   argv[1+offset], 
				   argv[2+offset]);
	}
	break;
	
      case 2:
	display_object->show_summary(document1->getModel(), argv[1+offset]);
	if (integrate)
	  display_object->show_summary(document2->getModel(), argv[2+offset]);
	break;

      case 3:
	if (integrate)
	  integrate_framework->integration();
	else{
	  cout << "Exiting - thanks for playing!" << endl;
	  exit = true;
	}
      	break;
	
      case 4:
	cout << "Exiting - thanks for playing!" << endl;
	exit = true;
	break;
      }	
  }
  
  // exit post-amble
  delete display_object;
  //delete cleanup_object1;
  
  //if (integrate)
  //delete cleanup_object2;
  

  // last thing that should happen - closes logfile!
  interface.SBML_EXIT();
  
  cout << "Exit" << endl;
}
