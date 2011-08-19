#ifndef SBML_INTEGRATE_HELPER_H
#define SBML_INTEGRATE_HELPER_H

#include "sbml_ui_general.h"

class SBML_integrate_helper : public SBML_UI_general {
 
 protected:
  static int operation;

 public:
  template <class T> 
    void compare_and_edit_maths(std::string title, T& inNew_copy, T& tempB, std::string message){
    
    char selector;
    bool exit;
    system("clear");
    std::cout << "### " << title << " ###" << std::endl;
    std::cout << "Ensure that if you select option B or C, parameters/species/compartments referenced by the rule actually exist or will exist.\nSoftware support to check this coming real soon, but at the moment please try and be careful!" << std::endl;
    
    std::cout << message << std::endl;
    std::cout << "    A ----- "; 
    if (inNew_copy->getFormula() == "")
      std::cout << " [NONE DEFINED]" << std::endl;
    else
      std::cout << inNew_copy->getFormula() << std::endl;
	
    std::cout << "    B ----- ";
    if (tempB->getFormula() == "")
      std::cout << " [NONE DEFINED]" << std::endl;
    else
      std::cout << tempB->getFormula() << std::endl;
    
    std::cout << "    C ----- Define your own formula!" << std::endl << std::endl;
    
    std::cout << "    Select (A, B or C): ";
    
    std::cin >> selector;
    std::cin.ignore();
    while (exit == false){
      switch (selector) {
	
	
      case 'A':
	// nothing to do
	exit = true;
	break;
      
      
      case 'B':
	inNew_copy->setMath(tempB->getMath());
	exit = true;
	break;
      
      case 'C':
	formula_editor(inNew_copy);
	exit = true;
	break;

      default:
	std::cout << "Please select A,B or C: " << std::endl;
	std::cin >> selector;
        std::cin.ignore(); 
      }
    }

      return;
  }
  
  template <class T> void formula_editor(T*& inNew_copy){
    bool escape = false;
    print_header("Editing Formula", true);
    std::cout << "Previously, formula was: " << inNew_copy->getFormula() << std::endl << std::endl;
    std::cout << "**REMEBER** \nIf you have a non operator/numeric reference (i.e. a name) it must reference something which exists in the model! For a detailed description of the SBML mathML syntax used please see appropriate documentation. \n\nBelow is a breif overview " << std::endl;

    std::cout 
      << " TOKEN       OPERATION            CLASS    PRECEDENCE    ASSOCIATES" << std::endl
      << " name        symbol reference     operand      6            n/a    " << std::endl
      << " (expression expression grouping  operand      6            n/a    " << std::endl
      << " f(...)      function call        prefix       6            left   " << std::endl
      << " -           negation             unary        5            right  " << std::endl
      << " ^           power                binary       4            left   " << std::endl
      << " *           multiplication       binary       3            left   " << std::endl
      << " /           division             binary       3            left   " << std::endl
      << " +           addition             binary       2            left   " << std::endl
      << " -           subtraction          binary       2            left   " << std::endl
      << " ,           argument deliminter  binary       1            left   " << std::endl
      << std::endl
      << "Example formula"  << std::endl
      << "1)  0.10 * k4^2"  << std::endl
      << "2) (vm * s1)/(km + s1)"  << std::endl
      << "If you need to check something relating to the model just enter anything here, save it\nand go back to previous screen, where you can get \nmodel information" << std::endl
      << std::endl << std::endl;
    
    while (escape == false){
      std::cout << "Please enter a new formula: ";
      std::string new_node = stringGet();

      if (new_node == "Q")
	autoAbort("Aborting...");
      if (new_node == "")
	std::cout << "Cannot have an empty formula - please try again. To abort press Q" << std::endl;
      else if (0 == inNew_copy->setFormula(new_node.c_str()))
	escape = true;
      else {
	std::cout << "Sorry, the node formula" << new_node 
		  << " doesn't work. \nPlease try again, or if this is broken and you want to "
		  << "abort please enter Q: ";
      }
      
    }
    
  }

  
};

#endif

