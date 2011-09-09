// Copyright Alex Holehouse 2011
// Distributed under the terms of the GNU general public license - see COPYING.txt for more details

#ifndef SBML_UI_GENERAL_H
#define SBML_UI_GENERAL_H

#include <sbml/SBMLTypes.h>
#include "sbml_formatter.h"
/*!
  \brief General user interface class, providing generic functions used throughout the software
*/


class SBML_UI_general : public SBML_formatter {
  
 public:
  
  
  /*!
    \brief UI function which requests a user to press any key to continue
    
    \b Preconditions: none
    
    \b Postconditions: user must press any button (input is ignored) to proceed
    
  */
  void any_key_to_continue();

    /*!
    \brief UI function which displays an "invalid selection" message
    
    \b Preconditions: none
    
    \b Postconditions: outputs an invalid selection warning to STDOUT
    
  */
  void invalid_selection();
  
    /*!
    \brief UI function which requests the user to select Y(es) or N(o)
    
    \b Preconditions: none
    
    \b Postconditions: Returns 'Y' on Y or y and 'N' or N or n
    
  */
  char yes_or_no();
  
    /*!
    \brief UI function which is essentially a wrapper for getline()
    
    \b Preconditions: none
    
    \b Postconditions: Returns a string 
    
    */
  std::string stringGet();
    /*!
    \brief Get a value between lower or upper from STDIN, or c_FAILDOUBLE if incorrect value input

    */
  double doubleGet(double lower, double upper);
    /*!
    \brief Get a value between lower and upper always from STDIN
    */
  double doubleGet_guarenteed(double lower, double upper);
  /*!
    \brief Simple function to get a character pointer - \b DEPRECATED (although still used occasionally)

  */
  char* selectorGet();
    /*!
    \brief Print a standardized header border with a message

    \b Preconditions:_header should be less than 80 characters

    \b Postconditions: If clear is set the screen is cleared before the title displayed, if clear = false this doesn't happen
  */
  void print_header(const std::string _header, bool clear);  
  /*!
    \brief Print a standardized footer border
    
  */
  void print_footer();
  
 private:
 
};

#endif



