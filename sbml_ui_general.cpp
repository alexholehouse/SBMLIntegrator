#include <iostream>
#include <string>
#include <sbml/SBMLTypes.h>
#include "sbml_ui_general.h"
#include <cstdlib>

using namespace std;

void SBML_UI_general::any_key_to_continue(){
  cout << "Press any key to continue...";
  string input;
  getline(cin,input,'\n');
}

void SBML_UI_general::invalid_selection(){
  cout << "**** Invalid selection ****" << endl;
}

// function which prints the input string to file and screen in the standard header frame
//-----------------------------------------------------------------------------------
void SBML_UI_general::print_header(std::string _header, bool clear){
  
  int aug = 0; // aug used to agument the final for loop incase h_len is an odd number
  int border;
  int h_len = _header.length();
  
  // "new screen..."
  if (clear)
    system("clear");
  
  // if h_len is odd aug is -1
  if ((h_len/2)*2 == h_len)
    aug = -1;
 
  border = ((64-h_len)/2) - 3;

  // 54 #s!
  cout << "##############################################################" << endl;
  log_stream << "##############################################################" << endl;
  
  for (int i = 0 ; i < border ; i++){
    cout << "#";
    log_stream << "#";
  }

  cout << "   " << _header << "   ";
  log_stream << "   " << _header << "   ";
  
  for (int i = 0 ; i < (border-1+aug) ; i++){
    cout << "#";
    log_stream << "#";
  }
  
  cout << endl << "##############################################################" << endl;
  log_stream << endl << "##############################################################" << endl;
}

void SBML_UI_general::print_footer(){
  cout << "##############################################################" << endl;
  log_stream << "##############################################################" << endl;
}

