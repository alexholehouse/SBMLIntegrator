// Copyright Alex Holehouse 2011
// Distributed under the terms of the GNU general public license - see COPYING.txt for more details

#ifndef SBML_UI_GENERAL_H
#define SBML_UI_GENERAL_H

#include <sbml/SBMLTypes.h>
#include "sbml_formatter.h"

class SBML_UI_general : public SBML_formatter {
  
 public:
  
  
  /*!
    \breif UI function which requests a user to press any key to continue
    
    \b Preconditions: none
    
    \b Postconditions: user must press any button (input is ignored) to proceed
    
  */
  void any_key_to_continue();

    /*!
    \breif UI function which displays an "invalid selection" message
    
    \b Preconditions: none
    
    \b Postconditions: outputs an invalid selection warning to STDOUT
    
  */
  void invalid_selection();
  
    /*!
    \breif UI function which requests the user to select Y(es) or N(o)
    
    \b Preconditions: none
    
    \b Postconditions: Returns 'Y' on Y or y and 'N' or N or n
    
  */
  char yes_or_no();
  
    /*!
    \breif UI function which is essentially a wrapper for getline()
    
    \b Preconditions: none
    
    \b Postconditions: Returns a string 
    
    */
  std::string stringGet();
  
  double doubleGet(double lower, double upper);
  
  double doubleGet_guarenteed(double lower, double upper);

  char* selectorGet();
  
  void print_header(const std::string _header, bool clear);
  void print_footer();
  
 private:
 
};

#endif



