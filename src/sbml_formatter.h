// Copyright Alex Holehouse 2011
// Distributed under the terms of the GNU general public license - see COPYING.txt for more details

/*! \mainpage SBMLIntegrator
 
  SBMLIntegrator is a a simple to use tool for Linux which allows for the integration of two SBML models into one single model. The purpose of this functionality is to faciliate model integration to propel the investigation of crosstalk between seperatly defined but biologically connected pathways.

  Included here is a documentation of the software generate through doxygen. It gives an overview of classes and functions to provide a pseudo-interactive guide to the code generated. The purpose of this is twofold.

  1) It provides a means to describe and explain the code justification for future optimisation, enhancement and development. The code is well commented throughout, so this documentation provides
  an overview to the architechture. If more detailed is required, the source code can be examined.

  2) For this dissertation, rather than describing the code in detail in the report, code implementation can be viewed here, with both code comments in the code and a code overview provided by this documentation. This gives a much more natural way to interpret the code, as well as avoiding the formatting issues and longwinded descriptions needed to "describe" code, rather than simply referring to it.

   
 !*/


#ifndef SBML_FORMATTER_H
#define SBML_FORMATTER_H

#include <string>
#include <iostream>
#include <fstream>
#include <sbml/SBMLTypes.h>
 /**
     Base object for all classes. This class contains core functionality relating to SBML, type conversion, formatting and a range of other methods which may be required by multiple classes but are in no way linked to specific information. As a result, this functionality is grouped here for ease of access by other classes.
 **/
class SBML_formatter {
 

  
 public:

  static const int c_FAIL_DOUBLEGET = -9999999;
  
  SBML_formatter();
  int SBML_EXIT();
  
  std::string get_date();
  std::string get_time();
  std::string get_version();
  
  // resets a c_string to all spaces
  void reset_cstr(char* c_str, int size);
  
  // safe abort that closes the log_streams and prints message to stdout and log_stream
  void autoAbort(std::string message);
  
  std::string dtostr(const double in);
  
  SpeciesReference* species2SpeciesReference(const Species* species, const Reaction* rxn, std::string addToSpeciesID);
  
  SpeciesReference* species2SpeciesReference(const Species* species, const Reaction* rxn);
  
  ModifierSpeciesReference* species2ModifierSpeciesReference(const Species* species, const Reaction* rxn);
    
  void logfile_add_message(int error, std::string element, std::string new_owner);
  
  void append_to_modelID(Model* input, const std::string to_append); // INCOMPLETE - probably move to integrator no?

  bool write_to_file(Model* input, std::string filename);

  // import_* helper functions ------------------------------------------------------------
  // template function needs to be in header file
  template <class T> void append_to_ID(T* element, std::string to_append){
    
    // for diagnostics only (although worth keeping)
    log_stream << "Template function append_to_ID. If this fails likely the type passed to append_to_ID does not have an ID memnber variable!" << std::endl;
    
    std::string newID = element->getId();
    std::string error;
    newID.append(to_append);
    if (element->setId(newID) !=0)
      autoAbort(	
		(
		 (
		  (
		   (
		    (error
		     .append("Error, setting Id "))
		    .append(newID))
		   .append(" in element "))
		  .append(element->getId()))
		 .append(" in element "))
		.append(element->getId()));

    else 
      return;    
  }
  
  
 protected:
  /// Filestream which outputs logging information
  static std::ofstream log_stream;

  /// Ensures the logfile is essentially a singleton logfile
  static bool logfile_set;

  /// Used to generate model-wide unique IDs
  static int unique;
  
  
};

#endif
