#ifndef SBML_UI_GENERAL_H
#define SBML_UI_GENERAL_H

#include <sbml/SBMLTypes.h>
#include "sbml_formatter.h"

class SBML_UI_general : public SBML_formatter {
  
 public:
  void any_key_to_continue();
  void invalid_selection();
  void print_header(const std::string _header, bool clear);
  void print_footer();
  
  
 private:
  

};

#endif



