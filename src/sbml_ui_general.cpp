// Copyright Alex Holehouse 2011
// Distributed under the terms of the GNU general public license - see COPYING.txt for more details

#include <iostream>
#include <string>
#include <sbml/SBMLTypes.h>
#include <cstdlib>
#include "sbml_ui_general.h"

// using declarations
using std::cin;
using std::cout;
using std::endl;
using std::string;


void SBML_UI_general::any_key_to_continue(){
  cout << " Press any key to continue...";
  string input;
  getline(cin,input,'\n');
  cout << endl;
}

void SBML_UI_general::invalid_selection(){
  cout << "**** Invalid selection ****" << endl;
}

char SBML_UI_general::yes_or_no(){
  char input;
  cout << " Please select Y/N: ";

  while (true){
    cin >> input;
    cin.ignore();
    
    if (input == 'Y'|| input == 'y')
      return 'Y';
    
    if (input == 'N' || input == 'n')
      return 'N';

    cout << " Sorry - selection (" << input << ") not recognized.\n Please select Y or N: ";
  }
}

double SBML_UI_general::doubleGet(double lower, double upper){
  
  string in;
  char temp;
  double val;
  
  in = stringGet();
  const char* in_cstr = in.c_str();

  if (in.length() == 0)
    return c_FAIL_DOUBLEGET;
  
  for (unsigned int i = 0 ; i < in.length() ; i++){
    temp = in_cstr[i];
    if (static_cast<int>(temp) < 48 || static_cast<int>(temp) > 57){
      // non 0-9 character in input, so invalid
      return c_FAIL_DOUBLEGET;
    }
  }
  
  val = atoi(in_cstr);

  if (val < lower || val > upper)
    return c_FAIL_DOUBLEGET;

  return val;
}

double SBML_UI_general::doubleGet_guarenteed(double lower, double upper){
  
  double val = doubleGet(lower, upper);
  
  while (val == c_FAIL_DOUBLEGET){
    cout << "**** Invalid selection ****" << endl;
    cout << "Please reselect :";
    val = doubleGet(lower,upper);
  }

  return val;
}

// default constructor -- called by all SBML_formatter inheriting classes
// This is a relic of a previous build, keeping it in for now but actually not necessary, just 
// use getline() inplace.
//-----------------------------------------------------------------------------------
string SBML_UI_general::stringGet(){
  string input;
  getline(cin,input,'\n');
  
  return input;
}

char* SBML_UI_general::selectorGet(){
  string input;
  const char* input_c;
  
  getline(cin, input,'\n');
  input_c = input.c_str();
  
  char* ret = new char[1];
  ret[0] = input_c[0];
  
  return ret;
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

