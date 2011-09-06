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
/** \brief Base class for all classes
   
    
   This class contains core functionality relating to SBML, type conversion, formatting and a range of other methods which may be required by multiple classes but are in no way linked to specific information. As a result, this functionality is grouped here for ease of access by other classes.
**/
class SBML_formatter {
  
 public:
  
  /// Default value used to indicate failure
  static const int c_FAIL_DOUBLEGET = -9999999;
  
  /**
     \brief Constructor function

   **/
  SBML_formatter();  

  /*! \brief Function to close the software
    
    \b Preconditions: None
    
    \b Postconditions: Closes the logstream correctly to ensure file validity
    
  */
  int SBML_EXIT();
  
  /** Returns the date in a standard format to string **/
  std::string get_date();
  /** Returns the time in a standard format to string **/
  std::string get_time();
  /** Returns the software verison in a standard format to string **/
  std::string get_version();
  
  /** Resets a c_string of size size to be empty - starts from beginning **/
  void reset_cstr(char* c_str, int size);
  
  /** Safe abort method which outouts a message to screen closes the software **/
  void autoAbort(std::string message);
  
  /** Converts a double to a string **/
  std::string dtostr(const double in);
  
  /** Converts a species to a species reference in a specific reaction, adding addToSpeciesID at the end **/
  SpeciesReference* species2SpeciesReference(const Species* species, const Reaction* rxn, std::string addToSpeciesID);
  
  /** Converts a species to a species reference in a specific reaction**/
  SpeciesReference* species2SpeciesReference(const Species* species, const Reaction* rxn);
  
  /** Converts a species to a modifier species reference in a specific reaction**/
  ModifierSpeciesReference* species2ModifierSpeciesReference(const Species* species, const Reaction* rxn);
    
  /** Writes a logfile error message - DEPRECATED DO NOT USE **/
  void logfile_add_message(int error, std::string element, std::string new_owner);
  
  /*! \brief Writes an SBML model to file as filename
    
    \b Preconditions: filename should include the .xml file extension. You should have write permission to the current working directory
    
    \b Postconditions: Writes a file in XML format with the SBML modell
    
  */
  bool write_to_file(Model* input, std::string filename);

  
  /** Checks if a pointer is set to NULL, and if so aborts with an error message rather than segfaulting **/
  template <class T> void nullchecker(T* pointer, std::string class_function){
    if (pointer == NULL){
      std::string message = "Null pointer exception in function ";
      autoAbort(message.append(class_function));
    }
  }
    

  /** 
      \brief Appends to_append onto any SBML element which can 
    
      \b Preconditions: Element must be able to have the getID() and setID() methods acted upon them
    
      \b Postconditions: Element is renamed
      
  **/
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
