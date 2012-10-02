// Copyright Alex Holehouse 2011
// Distributed under the terms of the GNU general public license - see COPYING.txt for more details

#include "sbml_confInput.h"
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <time.h>
#include <string>
#include <cstdlib>
#include <cstring>
#include <sbml/SBMLTypes.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>

// using namespace std;

// using delclarations, bit of namespace pollution, but if you're overriding cout, cin, endl or string you've got bigger problems...
using std::cout;
using std::cin;
using std::endl;
using std::string;

// assumes we won't go above 9999 items in a list.
const int MAX_NUMBER = 4;


// #############################################################################################
// CONSTRUCTOR
// 
SBML_confInput::SBML_confInput(){

  stream_set = false;

  // set array elements to zero
  for (int i = 0 ; i < 10 ; i++){
    seek_locations[i] = 0;
  }
  
  // to indicate the fact that locations have not yet been identified
  seek_locations[0] = -3;
  
  ifstream conf_stream;
}


bool SBML_confInput::load_conf(){
  return load_conf("");
}



// #############################################################################################
// LOAD integrate configuration file into conf_stream
//
bool SBML_confInput::load_conf(std::string conf_file) 
{ 
  
  // if stream is already loaded close and prepare to open a new file
  if (stream_set){
    conf_stream.close();
    stream_set = false;
  }
  
  log_stream << endl << "---- OPENING CONF FILE ---------" << endl << endl;
  char path_c[FILENAME_MAX];

  // if no conf file specified, go for default
  if (conf_file == ""){
    conf_file.clear();
    log_stream << "Default conf file used (integrate.conf)" << endl;
    conf_file = "integrate.conf";
  }
  else
    log_stream << "User defined conf file used (" << conf_file  << ")" << endl;

  // get current directory
  if (!getcwd(path_c, sizeof(path_c)))
    autoAbort("Fatal Error (line 223 in sbml_formatter.cpp) - unable to get current directory");
  
  // set end to terminal character for proper formatting;
  path_c[sizeof(path_c) - 1] = '\0';
  
  DIR *dirp = NULL;
  dirp = opendir(path_c); 
  
  string currentDir(path_c);

  if (dirp) 
  { 
    struct dirent *dp = NULL; 
    
    log_stream << "Searching for configuration file;" << endl;
    while ( (dp = readdir( dirp )) != NULL ) 
      { 
      std::string file( dp->d_name ); 
      log_stream << "filename: " << file << endl;

	if (file == conf_file){
	  conf_stream.open(file.c_str(), ifstream::in);
	  stream_set = true;
	  	  
	  log_stream << "Conf file loaded succesfully" << endl;
	  
	  closedir(dirp); 
	  return true;
	}
	
    } 

    cout << "#######################################################" << endl;
    cerr << "ERROR - unable to find " << conf_file << " - files are;" << endl;
    log_stream << "ERROR - unable to find " << conf_file << " - files are;" << endl;

    cout << "You can explore the loaded models, but integration will not be possible" << endl;
    any_key_to_continue();
    
    closedir( dirp ); 
  } 
  
  return false;
  
}  

// #############################################################################################
// 
//
//
bool SBML_confInput::import_data(const Model* modelNew, const Model* modelB, std::string conf_file){
  
  // For now we're hardcoding in default integrate.conf - selectable filename to added
  // TODO - add in "select filename functionality"
  if (!load_conf("")){
    cerr << "ERROR - problem with importing conf file." << endl;
    log_stream << "ERROR - problem with importing conf file. Reselect conf file please" << endl;
    return false;
  }
  
  
  log_stream << "About to import data from conf_file (";
  if (conf_file != "")
    log_stream << conf_file << "). Hold onto your hat!" << endl;
  else
    log_stream << "integrate.conf). Hold onto your hat!" << endl;
  
  conf_preprocess();
  set_import_list(modelB);
  set_replace_or_integrate_list(modelNew, modelB, false);
  set_replace_or_integrate_list(modelNew, modelB, true);
  
  return true;

}



// #############################################################################################
// RESET_SEEK
// resets the seekg pointer in the loaded conf_file to the beginning, or gives a warning and
// returns false if the stream is broken
//
bool SBML_confInput::reset_seek(){
  
  if (!stream_set){
    
    cerr << "WARNING - Unlabe to reset_seek, no conf file currently loaded" << endl;
    log_stream << "WARNING - Unlabe to reset_seek, no conf file currently loaded" << endl;
    return false;
  }

  conf_stream.clear();
  conf_stream.seekg(0);
  
  return true;
}



// #############################################################################################
// CONF_PREPROCESS
// Analyses the conf_file, initializes the seek_location array (used by list_getter functions) and
// ensures file integrity is good for data read
//
void SBML_confInput::conf_preprocess(){

  log_stream << "Preprocessing..." << endl;
  
  char temp_char = ' ';
  
  // Each of the seek_location array elements sets an int, which is infact a pointer location
  // in the .conf file which specifies where a section (Species, FunctionDefinition etc) starts.
  // These locations are then used as reference points to jump to to begin importing the specific 
  // section
  
  seek_locations[0] = find_in_file("FunctionDefinitions:", true);
  log_stream << "seek_locations[0] = " << seek_locations[0] << endl;

  seek_locations[1] = find_in_file("UnitDefinitions:", true);
  log_stream << "seek_locations[1] = " << seek_locations[1] << endl;

  seek_locations[2] = find_in_file("Compartments:", true);
  log_stream << "seek_locations[2] = " << seek_locations[2] << endl;

  seek_locations[3] = find_in_file("Species:", true);
  log_stream << "seek_locations[3] = " << seek_locations[3] << endl;

  seek_locations[4] = find_in_file("Parameters:", true);
  log_stream << "seek_locations[4] = " << seek_locations[4] << endl;

  seek_locations[5] = find_in_file("InitialAssignments:", true);
  log_stream << "seek_locations[5] = " << seek_locations[5] << endl;

  seek_locations[6] = find_in_file("Rules:", true);
  log_stream << "seek_locations[6] = " << seek_locations[6] << endl;
  
  seek_locations[7] = find_in_file("Constraints:", true);
  log_stream << "seek_locations[7] = " << seek_locations[7] << endl;
  
  seek_locations[8] = find_in_file("Reactions:", true);
  log_stream << "seek_locations[8] = " << seek_locations[8] << endl;
  
  seek_locations[9] = find_in_file("Events:", true);
  log_stream << "seek_locations[9] = " << seek_locations[9] << endl;

  // checking conf stream for [], which indicates someone forgot to add data to the conf file!
  while (conf_stream.good()){
    conf_stream.get(temp_char);
    if (temp_char == '['){
      conf_stream.get(temp_char);
      if (temp_char == ']'){
	log_stream << "ERROR - in conf_preprocess() line 166, two [] back-to-back - this usually means there is missing data!" << endl;
	autoAbort("Error in .conf file - two square brackets back to back ([]) - this usually indicates missing data! - Aborting...");
      }
    }
  }

  for (int i = 0 ; i < 10 ; i++){
    
    if (seek_locations[i] == -1)
      autoAbort("Error in .conf file - unable to find one of the ten sections");
    
    if (seek_locations[i] == -2)
      autoAbort("Error in .conf file - unspecified stream error on loading file");
  }
    
  
  log_stream << "Preprocessing finished successfully" << endl;
  
}
   

// #############################################################################################
// FIND_IN_FILE
// finds the pointer location in conf_file of the defined section. 
// Returns -2 if stream is bad, and -1 if cannot be found.
//
// NB - on exit of this function, find_in_file resets the stream position and error flags to the 
// beginning. 
// However, on input it only resets if reset is true (allowing you to start searching where the 
// position pointer is currently set to. If you're just searching the whole file make sure you 
// include the reset variable to true.

int SBML_confInput::find_in_file(std::string section, bool reset){

  // avoid a previously malformed pointer location/error state to disrup the search process
  if (reset)
    reset_seek();
  
  char temp_char;
  bool matching = false;
  int position = conf_stream.tellg();
  int location = 0;
  int string_end = section.length();
  
  // if conf_stream is dead
  if (!conf_stream.good())
    return -2;

  // create cstring version of the string we've input
  char* section_c = new char[section.length() + 1];
  strcpy(section_c, section.c_str());

  while (conf_stream.good()){
    
    // reset at the start of each comparison
    matching = false;


    conf_stream.get(temp_char);

    if (temp_char == section_c[location]){
      matching = true;
      
      // if we're at the end and have fully matched the string
      if (location+1 == string_end){
	delete [] section_c;
	reset_seek();
	return position-string_end;
      }
    
      location++;
    }
    
    // if temp_char and the current positin are not matching, but location in the cstring is not 0
    // then reset to 0
    if (!matching && location>0)
      location = 0;
    
    position++;
  }
  
  // If we get here then no match in the file!
  delete [] section_c;
  reset_seek();
  return -1;
}



// #############################################################################################
//  SET_REPLACE_OR_INTEGRATE_LISTS
// 
// Define the import_lists (in the container member attributes) based on the data from the config file.
// 
// Takes two const model pointers, modelA should be to the model you're building, while modelB is 
// the one you're importing into modelA. So for replacement, the elements defined as modelA elemenst
// will be replaced by the modelB element defined in modelA.
//
// If replace is set, the function fills in the "replacement" lists, if not it does the integtrate
// lists
//
// ***Requires that conf_preprocess() has been run first***
// #############################################################################################
void SBML_confInput::set_replace_or_integrate_list(const Model* modelA, const Model* modelB, bool replace){
  
  int* number_array;
  int elements;
  string search_term;
  
  if (replace)
    search_term = "Replace:";
  
  else
    search_term = "Integrate:";
  
  // -3 means seek_locations array has not been set
  if (seek_locations[0] == -3)
    autoAbort("FATAL ERROR - conf_preprocess() *MUST* be run before set_replace_or_integrate_list(...)");
	      

  log_stream << endl << "--- Defining";
  if (replace)
    log_stream << " replace lists --" << endl;
  else
    log_stream << " integrate lists ---" << endl;
  
  // -- Function Definitions ----------------------------------------------------------------
  if (modelB->getNumFunctionDefinitions() > 0){
    section_set(search_term, 0);
    
    elements = get_number_list(number_array);
    even_number(elements);
      
    for (int i = 0 ; i < elements ; i=i+2){
      
      if (number_array[i] >= (int)modelA->getNumFunctionDefinitions() || number_array[i] < 0){
	log_stream << "WARNING - in loading functionDefinitions for replacement/integration from conf file, non-existant functionDef referenced (" << number_array[i] << "). Ignoring..." << endl;
	continue;
      }

      if (number_array[i+1] >= (int)modelB->getNumFunctionDefinitions() || number_array[i+1] < 0){
	log_stream << "WARNING - in loading functionDefinitions for replacement/integration from conf file, non-existant functionDef referenced (" << number_array[i+1] << "). Ignoring..." << endl;
	continue;
      }
      
      if (replace){	
	log_stream << "Putting function definitions modelA[" << number_array[i] << "] and modelB [" << number_array[i+1] << "] into replace list" << endl;
	function_container.add_to_replace(modelA->getFunctionDefinition(number_array[i]), modelB->getFunctionDefinition(number_array[i+1]));
      }
      else{
	log_stream << "Putting function definitions modelA[" << number_array[i] << "] and modelB [" << number_array[i+1] << "] into integrate list" << endl;
	function_container.add_to_integrate(modelA->getFunctionDefinition(number_array[i]), modelB->getFunctionDefinition(number_array[i+1]));
      }				    
    } 
  }
  else
    log_stream << "No function definitions in modelB" << endl;
  
  // -- Unit Definitions ----------------------------------------------------------------
  if (modelB->getNumUnitDefinitions() > 0){
    section_set(search_term, 1);
    
    elements = get_number_list(number_array);
    even_number(elements);

    for (int i = 0 ; i < elements ; i=i+2){
      
      if (number_array[i] >= (int)modelA->getNumUnitDefinitions() || number_array[i] < 0){
	log_stream << "WARNING - in loading unitDefinitions for replacement/integration from conf file, non-existant unitDef referenced (" << number_array[i] << "). Ignoring..." << endl;
	continue;
      }
      
      if (number_array[i+1] >= (int)modelB->getNumUnitDefinitions() || number_array[i+1] < 0){
	log_stream << "WARNING - in loading unitDefinitions for replacement/integration from conf file, non-existant functionDef referenced (" << number_array[i+1] << "). Ignoring..." << endl;
	continue;
      }
      
      if (replace){
	log_stream << "Putting unit definitions modelA[" << number_array[i] << "] and modelB [" << number_array[i+1] << "] into replace list" << endl;
	unit_container.add_to_replace(modelA->getUnitDefinition(number_array[i]), modelB->getUnitDefinition(number_array[i+1]));
		
      }
      else{
	log_stream << "Putting unit definitions modelA[" << number_array[i] << "] and modelB [" << number_array[i+1] << "] into integrate list" << endl;
	unit_container.add_to_integrate(modelA->getUnitDefinition(number_array[i]), modelB->getUnitDefinition(number_array[i+1]));
      }
    }
  }
  else
    log_stream << "No unit definitions in modelB" << endl;
  
  // -- Compartments ----------------------------------------------------------------
  if (modelB->getNumCompartments() > 0){
    section_set(search_term, 2);
    
    elements = get_number_list(number_array);
    even_number(elements);

    for (int i = 0 ; i < elements ; i=i+2){
      
      if (number_array[i] >= (int)modelA->getNumCompartments() || number_array[i] < 0){
	log_stream << "WARNING - in loading compartments for replacement/integration from conf file, non-existant compartment referenced (" << number_array[i] << "). Ignoring..." << endl;
	continue;
      }  
      
      if (number_array[i+1] >= (int)modelB->getNumCompartments() || number_array[i+1] < 0){
	log_stream << "WARNING - in loading compartment for replacement/integration from conf file, non-existant functionDef referenced (" << number_array[i+1] << "). Ignoring..." << endl;
	continue;
      }
      
      if (replace) {
	log_stream << "Putting compartment modelA[" << number_array[i] << "] and modelB [" << number_array[i+1] << "] into replace list" << endl;
	compartment_container.add_to_replace(modelA->getCompartment(number_array[i]), modelB->getCompartment(number_array[i+1]));
      }
      else {
	log_stream << "Putting compartment modelA[" << number_array[i] << "] and modelB [" << number_array[i+1] << "] into integrate list" << endl;
	compartment_container.add_to_integrate(modelA->getCompartment(number_array[i]), modelB->getCompartment(number_array[i+1]));
      }
    }
  }
  else
    log_stream << "No compartments in modelB" << endl;
  
  // -- Species ----------------------------------------------------------------
  if (modelB->getNumSpecies() > 0){
    section_set(search_term, 3);
    
    elements = get_number_list(number_array);
    even_number(elements);

    for (int i = 0 ; i < elements ; i=i+2){
      
      if (number_array[i] >= (int)modelA->getNumSpecies() || number_array[i] < 0){
	log_stream << "WARNING - in loading species for replacement/integration from conf file, non-existant compartment referenced (" << number_array[i] << "). Ignoring..." << endl;
	continue;
      }
      
      if (number_array[i+1] >= (int)modelB->getNumSpecies() || number_array[i+1] < 0){
	log_stream << "WARNING - in loading species for replacement/integration from conf file, non-existant functionDef referenced (" << number_array[i+1] << "). Ignoring..." << endl;
	continue;
      }
      
      if (replace){
	log_stream << "Putting species modelA[" << number_array[i] << "] and modelB [" << number_array[i+1] << "] into replace list" << endl;
	species_container.add_to_replace(modelA->getSpecies(number_array[i]), modelB->getSpecies(number_array[i+1]));
      }
      else {
	log_stream << "Putting species modelA[" << number_array[i] << "] and modelB [" << number_array[i+1] << "] into integrate list" << endl;
	species_container.add_to_integrate(modelA->getSpecies(number_array[i]), modelB->getSpecies(number_array[i+1]));
      }
    }
  }
  else
    log_stream << "No species in modelB" << endl;
  
  // -- Parameters ----------------------------------------------------------------
  if (modelB->getNumParameters() > 0){
    section_set(search_term, 4);
    
    elements = get_number_list(number_array);
    even_number(elements);

    for (int i = 0 ; i < elements ; i=i+2){
      
      if (number_array[i] >= (int)modelA->getNumParameters() || number_array[i] < 0){
	log_stream << "WARNING - in loading parameter for replacement/integration from conf file, non-existant compartment referenced (" << number_array[i] << "). Ignoring..." << endl;
	continue;
      }
      
      if (number_array[i+1] >= (int)modelB->getNumParameters() || number_array[i+1] < 0){
	log_stream << "WARNING - in loading parameter for replacement/integration from conf file, non-existant functionDef referenced (" << number_array[i+1] << "). Ignoring..." << endl;
	continue;
      }
      
      if (replace){
	log_stream << "Putting parameter modelA[" << number_array[i] << "] and modelB [" << number_array[i+1] << "] into replace list" << endl;
	parameter_container.add_to_replace(modelA->getParameter(number_array[i]), modelB->getParameter(number_array[i+1]));
      }			  
      else{
	log_stream << "Putting parameter modelA[" << number_array[i] << "] and modelB [" << number_array[i+1] << "] into integrate list" << endl;
	parameter_container.add_to_integrate(modelA->getParameter(number_array[i]), modelB->getParameter(number_array[i+1]));
      }	
    }
  }
  else
    log_stream << "No parameters in modelB" << endl;
  
  // -- Initial Assignment ----------------------------------------------------------------
  if (modelB->getNumInitialAssignments() > 0){
    section_set(search_term, 5);
    
    elements = get_number_list(number_array);
    even_number(elements);

    for (int i = 0 ; i < elements ; i=i+2){
      
      if (number_array[i] >= (int)modelA->getNumInitialAssignments() || number_array[i] < 0){
	log_stream << "WARNING - in loading  initial assignment for replacement/integration from conf file, non-existant compartment referenced (" << number_array[i] << "). Ignoring..." << endl;
	continue;
      }
      
      if (number_array[i+1] >= (int)modelB->getNumInitialAssignments() || number_array[i+1] < 0){
	log_stream << "WARNING - in loading initial assignment for replacement/integration from conf file, non-existant functionDef referenced (" << number_array[i+1] << "). Ignoring..." << endl;
	continue;
      }
      
      if (replace){
	log_stream << "Putting initial assignment modelA[" << number_array[i] << "] and modelB [" << number_array[i+1] << "] into replace list" << endl;
	initialAssignment_container.add_to_replace(modelA->getInitialAssignment(number_array[i]), modelB->getInitialAssignment(number_array[i+1]));
      }
      else{
	log_stream << "Putting initial assignment modelA[" << number_array[i] << "] and modelB [" << number_array[i+1] << "] into integrate list" << endl;
	initialAssignment_container.add_to_integrate(modelA->getInitialAssignment(number_array[i]), modelB->getInitialAssignment(number_array[i+1]));
      }
       
    }
  }
  else
    log_stream << "No initial assignments in modelB" << endl;
  
  // -- Rules ----------------------------------------------------------------
  if (modelB->getNumRules() > 0){
    section_set(search_term, 6);
    
    elements = get_number_list(number_array);
    even_number(elements);

    for (int i = 0 ; i < elements ; i=i+2){
      
      if (number_array[i] >= (int)modelA->getNumRules() || number_array[i] < 0){
	log_stream << "WARNING - in loading rule for replacement/integration from conf file, non-existant compartment referenced (" << number_array[i] << "). Ignoring..." << endl;
	continue;
      }
      
      if (number_array[i+1] >= (int)modelB->getNumRules() || number_array[i+1] < 0){
	log_stream << "WARNING - in loading rule for replacement/integration from conf file, non-existant functionDef referenced (" << number_array[i+1] << "). Ignoring..." << endl;
	continue;
      }
      
      if (replace){
	log_stream << "Putting rule modelA[" << number_array[i] << "] and modelB [" << number_array[i+1] << "] into replace list" << endl;
	rule_container.add_to_replace(modelA->getRule(number_array[i]), modelB->getRule(number_array[i+1]));
      }
      else{
	log_stream << "Putting rule modelA[" << number_array[i] << "] and modelB [" << number_array[i+1] << "] into integrate list" << endl;
	rule_container.add_to_integrate(modelA->getRule(number_array[i]), modelB->getRule(number_array[i+1]));
      }
    }
  }
  else
    log_stream << "No rules in modelB" << endl;
  

  // -- Constraints ----------------------------------------------------------------
  if (modelB->getNumConstraints() > 0){
    section_set(search_term, 7);
    elements = get_number_list(number_array);

    even_number(elements);

    for (int i = 0 ; i < elements ; i=i+2){
      
      if (number_array[i] >= (int)modelA->getNumConstraints() || number_array[i] < 0){
	log_stream << "WARNING - in loading constraint for replacement/integration from conf file, non-existant compartment referenced (" << number_array[i] << "). Ignoring..." << endl;
	continue;
      }    
      
      if (number_array[i+1] >= (int)modelB->getNumConstraints() || number_array[i+1] < 0){
	log_stream << "WARNING - in loading constraint for replacement/integration from conf file, non-existant functionDef referenced (" << number_array[i+1] << "). Ignoring..." << endl;
	continue;
      }
      
      if (replace){
	log_stream << "Putting constraint modelA[" << number_array[i] << "] and modelB [" << number_array[i+1] << "] into replace list" << endl;
	constraint_container.add_to_replace(modelA->getConstraint(number_array[i]), modelB->getConstraint(number_array[i+1]));
      }
      else{
	log_stream << "Putting constraint modelA[" << number_array[i] << "] and modelB [" << number_array[i+1] << "] into integrate list" << endl;
	constraint_container.add_to_integrate(modelA->getConstraint(number_array[i]), modelB->getConstraint(number_array[i+1]));
      }
    }
  }
  else
    log_stream << "No constraints in modelB" << endl;
  
  // -- Reaction ----------------------------------------------------------------

  if (modelB->getNumReactions() > 0){
    section_set(search_term, 8);

    elements = get_number_list(number_array);
    even_number(elements);
    
    for (int i = 0 ; i < elements ; i=i+2){
      
      if (number_array[i] >= (int)modelA->getNumReactions() || number_array[i] < 0){
	log_stream << "WARNING - in loading reaction for replacement/integration from conf file, non-existant compartment referenced (" << number_array[i] << "). Ignoring..." << endl;
	continue;
      }

      if (number_array[i+1] >= (int)modelB->getNumReactions() || number_array[i+1] < 0){
	log_stream << "WARNING - in loading reaction for replacement/integration from conf file, non-existant functionDef referenced (" << number_array[i+1] << "). Ignoring..." << endl;
	continue;
      }

      
      if (replace){
	log_stream << "Putting reaction modelA[" << number_array[i] << "] and modelB [" << number_array[i+1] << "] into replace list" << endl;
	reaction_container.add_to_replace(modelA->getReaction(number_array[i]), modelB->getReaction(number_array[i+1]));
      }      

      else{
	log_stream << "Putting reaction modelA[" << number_array[i] << "] and modelB [" << number_array[i+1] << "] into integrate list" << endl;
	reaction_container.add_to_integrate(modelA->getReaction(number_array[i]), modelB->getReaction(number_array[i+1]));
      }
    }
  }
  else
    log_stream << "No reactions in modelB" << endl;
  
  // -- Events ----------------------------------------------------------------
  if (modelB->getNumEvents() > 0){
    section_set(search_term, 9);
    
    even_number(elements);
    elements = get_number_list(number_array);
    
    for (int i = 0 ; i < elements ; i++){
      
      if (number_array[i] >= (int)modelB->getNumEvents() || number_array[i] < 0){
	log_stream << "WARNING - in loading events for replacement/integration from conf file, non-existant compartment referenced (" << number_array[i] << "). Ignoring..." << endl;
	continue;
      }
      
      if (number_array[i+1] >= (int)modelB->getNumEvents() || number_array[i+1] < 0){
	log_stream << "WARNING - in loading events for replacement/integration from conf file, non-existant functionDef referenced (" << number_array[i+1] << "). Ignoring..." << endl;
	continue;
      }
      
      if (replace){
	log_stream << "Putting events modelA[" << number_array[i] << "] and modelB [" << number_array[i+1] << "] into replace list" << endl;
	event_container.add_to_replace(modelA->getEvent(number_array[i]), modelB->getEvent(number_array[i+1]));
      }

      else{
	log_stream << "Putting events modelA[" << number_array[i] << "] and modelB [" << number_array[i+1] << "] into integrate list" << endl;
	event_container.add_to_integrate(modelA->getEvent(number_array[i]), modelB->getEvent(number_array[i+1]));
	
      }
    }
  }
  else
    log_stream << "No events in modelB" << endl;
  
  delete number_array;
}



// #############################################################################################
// SET_IMPORT_LIST
// define the import_lists (in the container member attributes) based on the data from the config file.
// ***Requires that conf_preprocess() has been run first***
//
//// #############################################################################################
void SBML_confInput::set_import_list(const Model* modelB){
  
  int* number_array;
  int elements;
 
  log_stream << endl << "--- Defining import_list ---" << endl;
  
  // -3 implies seek_locations array has not been set
  if (seek_locations[0] == -3)
    autoAbort("FATAL ERROR - conf_preprocess() *MUST* be run before set_import_list(...)");

  log_stream << "Defining import_lists..." << endl << endl;
  
  // -- Function Definitions ----------------------------------------------------------------
  if (modelB->getNumFunctionDefinitions() > 0){
    section_set("Import:", 0);
    
    int num_function = modelB->getNumFunctionDefinitions();
    
    log_stream << "num = " << num_function << endl;

    elements = get_number_list(number_array);
    
    for (int i = 0 ; i < elements ; i++){
      
      if (number_array[i] >= (int)modelB->getNumFunctionDefinitions() || number_array[i] < 0){
	log_stream << "WARNING - in loading functionDefinitions for import from conf file, non-existant functionDef referenced (" << number_array[i] << "). Ignoring..." << endl;
	continue;
      }
      
      log_stream << "Putting function definition [" << number_array[i] << "] into import list" << endl;
      function_container.add_to_import( modelB->getFunctionDefinition(number_array[i]));
    } 
  }
  else
    log_stream << "No function definitions in modelB" << endl;
  
  
  // -- Unit Definitions ----------------------------------------------------------------
  if (modelB->getNumUnitDefinitions() > 0){
    section_set("Import:", 1);
    
    elements = get_number_list(number_array);
    
    for (int i = 0 ; i < elements ; i++){
      
      if (number_array[i] >= (int)modelB->getNumUnitDefinitions() || number_array[i] < 0){
	log_stream << "WARNING - in loading unitDefinitions for import from conf file, non-existant unitDef referenced (" << number_array[i] << "). Ignoring..." << endl;
	continue;
      }

      log_stream << "Putting unit definition [" << number_array[i] << "] into import list" << endl;
      unit_container.add_to_import( modelB->getUnitDefinition(number_array[i]));
    }
  }
  else
    log_stream << "No unit definitions in modelB" << endl;
  
    // -- Compartments ----------------------------------------------------------------
  if (modelB->getNumCompartments() > 0){
    section_set("Import:", 2);
    
    elements = get_number_list(number_array);
    
    for (int i = 0 ; i < elements ; i++){
      
      if (number_array[i] >= (int)modelB->getNumCompartments() || number_array[i] < 0){
	log_stream << "WARNING - in loading compartments for import from conf file, non-existant compartment referenced (" << number_array[i] << "). Ignoring..." << endl;
	continue;
      }
      
      log_stream << "Putting compartment [" << number_array[i] << "] into import list" << endl;
      compartment_container.add_to_import( modelB->getCompartment(number_array[i]));
    }
  }
  else
    log_stream << "No compartments in modelB (WARNING - Suggests corrupt model)" << endl;
  
  // -- Species ----------------------------------------------------------------
  if (modelB->getNumSpecies() > 0){
    section_set("Import:", 3);
    
    elements = get_number_list(number_array);
    
    for (int i = 0 ; i < elements ; i++){
      
      if (number_array[i] >= (int)modelB->getNumSpecies() || number_array[i] < 0){
	log_stream << "WARNING - in loading compartments for import from conf file, non-existant compartment referenced (" << number_array[i] << "). Ignoring..." << endl;
	continue;
      }

      log_stream << "Putting species [" << number_array[i] << "] into import list" << endl;
      species_container.add_to_import( modelB->getSpecies(number_array[i]));
    }
  }
  else
    log_stream << "No species in modelB" << endl;

  // -- Parameters ----------------------------------------------------------------
  if (modelB->getNumParameters() > 0){
    section_set("Import:", 4);
    
    elements = get_number_list(number_array);
    
    for (int i = 0 ; i < elements ; i++){
      
      if (number_array[i] >= (int)modelB->getNumParameters() || number_array[i] < 0){
	log_stream << "WARNING - in loading parameter for import from conf file, non-existant compartment referenced (" << number_array[i] << "). Ignoring..." << endl;
	continue;
      }

      log_stream << "Putting parameter [" << number_array[i] << "] into import list" << endl;
      parameter_container.add_to_import(modelB->getParameter(number_array[i]));
    }
  }
  else
    log_stream << "No parameters in modelB" << endl;

  // -- Initial Assignment ----------------------------------------------------------------
  if (modelB->getNumInitialAssignments() > 0){
    section_set("Import:", 5);
    
    elements = get_number_list(number_array);
    
    for (int i = 0 ; i < elements ; i++){
      
      if (number_array[i] >= (int)modelB->getNumInitialAssignments() || number_array[i] < 0){
	log_stream << "WARNING - in loading  assignment for import from conf file, non-existant compartment referenced (" << number_array[i] << "). Ignoring..." << endl;
	continue;
      }

      log_stream << "Putting initial assignment [" << number_array[i] << "] into import list" << endl;
      initialAssignment_container.add_to_import(modelB->getInitialAssignment(number_array[i]));
    }
  }
  else
    log_stream << "No initial assignments in modelB" << endl;

  // -- Rules ----------------------------------------------------------------
  if (modelB->getNumRules() > 0){
    section_set("Import:", 6);
    
    elements = get_number_list(number_array);
    
    for (int i = 0 ; i < elements ; i++){
      
      if (number_array[i] >= (int)modelB->getNumRules() || number_array[i] < 0){
	log_stream << "WARNING - in loading rule for import from conf file, non-existant compartment referenced (" << number_array[i] << "). Ignoring..." << endl;
	continue;
      }

      log_stream << "Putting rule [" << number_array[i] << "] into import list" << endl;
      rule_container.add_to_import(modelB->getRule(number_array[i]));
    }
  }
  else
    log_stream << "No rules in modelB" << endl;

  // -- Constraints ----------------------------------------------------------------
  if (modelB->getNumConstraints() > 0){
    section_set("Import:", 7);
    elements = get_number_list(number_array);
    
    for (int i = 0 ; i < elements ; i++){
      
      if (number_array[i] >= (int)modelB->getNumConstraints() || number_array[i] < 0){
	log_stream << "WARNING - in loading constraint for import from conf file, non-existant compartment referenced (" << number_array[i] << "). Ignoring..." << endl;
	continue;
      }

      log_stream << "Putting constraint [" << number_array[i] << "] into import list" << endl;
      constraint_container.add_to_import(modelB->getConstraint(number_array[i]));
    }
  } 
  else
    log_stream << "No constraints in modelB" << endl;

  // -- Reaction ----------------------------------------------------------------
  if (modelB->getNumReactions() > 0){
    section_set("Import:", 8);
    elements = get_number_list(number_array);
    
    for (int i = 0 ; i < elements ; i++){
      
      if (number_array[i] >= (int)modelB->getNumReactions() || number_array[i] < 0){
	log_stream << "WARNING - in loading reaction for import from conf file, non-existant compartment referenced (" << number_array[i] << "). Ignoring..." << endl;
	continue;
      }

      log_stream << "Putting reaction [" << number_array[i] << "] into import list" << endl;
      reaction_container.add_to_import(modelB->getReaction(number_array[i]));
    }
  }
  else
    log_stream << "No reactions in modelB" << endl;

  // -- Events ----------------------------------------------------------------
  if (modelB->getNumEvents() > 0){
    
    section_set("Import:", 9);
    elements = get_number_list(number_array);
    
    for (int i = 0 ; i < elements ; i++){
      
      if (number_array[i] >= (int)modelB->getNumEvents() || number_array[i] < 0){
	log_stream << "WARNING - in loading events for import from conf file, non-existant compartment referenced (" << number_array[i] << "). Ignoring..." << endl;
	continue;
      }
      
      log_stream << "Putting event [" << number_array[i] << "] into import list" << endl;
      event_container.add_to_import(modelB->getEvent(number_array[i]));
    }
  }
  else
    log_stream << "No events in modelB" << endl;
  
  delete number_array;
}



// #############################################################################################
// SECTION_SET
// Sets the seekg pointer in conf_file to the position after element [0-9] defined by the string
// (typically "Import:", "Replace:" or "Integrate:"
//
void SBML_confInput::section_set(std::string section, int element){
  reset_seek();
  conf_stream.seekg(seek_locations[element]);
  conf_stream.seekg(find_in_file(section.c_str(), false));
 }



// #############################################################################################
// GET_NUMBER_LIST
// Build an array of values from the conf_file based on where the seekg pointer is currently located,
// with the caveat that 
// a) Paired values are [1,2] [3,4] ... [n-1, n]
// b) List values are [1,2,3 ... n]
// (NB, the values are irrelevant, as is their order, this is simply to demonstrate structure
int SBML_confInput::get_number_list(int*& number_array){
  
  int ret_val = 0, array_pos = 0, ref_num, input_pos = 0;
  int original_seekpos = conf_stream.tellg();
  char input[MAX_NUMBER];
  char temp_char = ' ';

  // set input_array to all ' '
  reset_cstr(input, MAX_NUMBER);
  
  while (temp_char != '\n'){
    conf_stream.get(temp_char);
    if (temp_char == ',' || temp_char == ']')
      ret_val++;
  }
  
  // numer_array is an array of ints which is the size of the number of
  // values we're importing from the conf file
  number_array = new int[ret_val];
  
  // reset the stream and temp_char so we're back where we were on function entry
  conf_stream.clear();
  conf_stream.seekg(original_seekpos);
  temp_char = ' ';
  
  while (temp_char != '\n'){
    conf_stream.get(temp_char);
    
    // entering the list of inport numbers
    if (temp_char == '['){

      // while you're not at the end of the list
      while (temp_char != '\n'){
	
	// get a character
	conf_stream.get(temp_char);
	
	// if we hit a comma or a ] we're at the end of a number
	if (temp_char == ','|| temp_char == ']'){
	  ref_num = atoi(input);
	  
	  // ref_num-1 as conf file indexes from 1 but all internal data
	  // structures reference from zero...
	  number_array[array_pos] = ref_num-1;
	  // increment the array position
	  array_pos++;
	  
	  // reset input_array amd input_array position
	  reset_cstr(input, MAX_NUMBER);
	  input_pos = 0;
	}
	
	// else take the value and insert it into the input array
	else if( static_cast<int>(temp_char) >= 48 &&  static_cast<int>(temp_char) <= 57){
	  input[input_pos] = temp_char;
	  input_pos++;
	}
      }
    }
  }
   
  // used for debugging/analysis - left in for future work...
  if (false){ 
    log_stream << "Input array is : " ;
    for (int i = 0; i < ret_val ;i++)
      cout << number_array[i] << " ";
    
    cout << endl;
  }
  
  return ret_val;
}

// i.e. move into .h file
void SBML_confInput::even_number(int elements){
  if (2*(elements/2) != elements)
    autoAbort("Fatal error - problem with conf_file formatting of pairs of elements for replacement or integration. Aborting");
}

// #############################################################################################
// #############################################################################################
// ##                                    conf_file API (getters)                              ##
// #############################################################################################
// #############################################################################################
// While verbose, the below functioins provide an API for dealing with pathway viewer configuration
// files. The idea being that by defining two models and a file name, the user can then use these
// functions to get any information relating to the config file they may want, without dealing
// with any of the underlying logic, containers, file parsing or anything else. Return values are
// standard types (defined by the SBML documentation, or ints
//
int SBML_confInput::get_num_import_functionDefinitions(){ return (function_container.get_num_imports());}
int SBML_confInput::get_num_replace_functionDefinitions(){ return (function_container.get_num_replacements());}
int SBML_confInput::get_num_integrate_functionDefinitions() { return (function_container.get_num_integrates());}
ListOfFunctionDefinitions* SBML_confInput::get_import_functionDefinitions()
{return function_container.get_import_list();}
ListOfFunctionDefinitions* SBML_confInput::get_replaceA_functionDefinitions()
{return function_container.get_replace_A_list();}
ListOfFunctionDefinitions* SBML_confInput::get_replaceB_functionDefinitions()
{return function_container.get_replace_B_list(); }
 ListOfFunctionDefinitions* SBML_confInput::get_integrateA_functionDefinitions()
 {return function_container.get_integrate_A_list(); }
 ListOfFunctionDefinitions* SBML_confInput::get_integrateB_functionDefinitions()
 {return function_container.get_integrate_B_list(); }

 int SBML_confInput::get_num_import_unitDefinitions(){ return (unit_container.get_num_imports());}
 int SBML_confInput::get_num_replace_unitDefinitions(){ return (unit_container.get_num_replacements());}
 int SBML_confInput::get_num_integrate_unitDefinitions(){ return (unit_container.get_num_integrates());}
 ListOfUnitDefinitions* SBML_confInput::get_import_unitDefinitions()
 {return unit_container.get_import_list();}
 ListOfUnitDefinitions* SBML_confInput::get_replaceA_unitDefinitions()
 {return unit_container.get_replace_A_list();}
 ListOfUnitDefinitions* SBML_confInput::get_replaceB_unitDefinitions()
 {return unit_container.get_replace_B_list(); }
 ListOfUnitDefinitions* SBML_confInput::get_integrateA_unitDefinitions()
 {return unit_container.get_integrate_A_list(); }
 ListOfUnitDefinitions* SBML_confInput::get_integrateB_unitDefinitions()
 {return unit_container.get_integrate_B_list(); }

 int SBML_confInput::get_num_import_compartments(){ return (compartment_container.get_num_imports());}
 int SBML_confInput::get_num_replace_compartments(){ return (compartment_container.get_num_replacements());}
 int SBML_confInput::get_num_integrate_compartments(){ return (compartment_container.get_num_integrates());}
 ListOfCompartments* SBML_confInput::get_import_compartments()
 {return compartment_container.get_import_list();}
 ListOfCompartments* SBML_confInput::get_replaceA_compartments()
 {return compartment_container.get_replace_A_list();}
 ListOfCompartments* SBML_confInput::get_replaceB_compartments()
 {return compartment_container.get_replace_B_list(); }
 ListOfCompartments* SBML_confInput::get_integrateA_compartments()
 {return compartment_container.get_integrate_A_list(); }
 ListOfCompartments* SBML_confInput::get_integrateB_compartments()
 {return compartment_container.get_integrate_B_list(); }

 int SBML_confInput::get_num_import_species(){ return (species_container.get_num_imports());}
 int SBML_confInput::get_num_replace_species(){ return (species_container.get_num_replacements());}
 int SBML_confInput::get_num_integrate_species(){ return (species_container.get_num_integrates());}
 ListOfSpecies* SBML_confInput::get_import_species()
 {return species_container.get_import_list();}
 ListOfSpecies* SBML_confInput::get_replaceA_species()
 {return species_container.get_replace_A_list();}
 ListOfSpecies* SBML_confInput::get_replaceB_species()
 {return species_container.get_replace_B_list(); }
 ListOfSpecies* SBML_confInput::get_integrateA_species()
 {return species_container.get_integrate_A_list(); }
 ListOfSpecies* SBML_confInput::get_integrateB_species()
 {return species_container.get_integrate_B_list(); }


 int SBML_confInput::get_num_import_parameters(){ return (parameter_container.get_num_imports());}
 int SBML_confInput::get_num_replace_parameters(){ return (parameter_container.get_num_replacements());}
 int SBML_confInput::get_num_integrate_parameters(){ return (parameter_container.get_num_integrates());}
 ListOfParameters* SBML_confInput::get_import_parameters()
 {return parameter_container.get_import_list();}
 ListOfParameters* SBML_confInput::get_replaceA_parameters()
 {return parameter_container.get_replace_A_list();}
 ListOfParameters* SBML_confInput::get_replaceB_parameters()
 {return parameter_container.get_replace_B_list(); }
 ListOfParameters* SBML_confInput::get_integrateA_parameters()
 {return parameter_container.get_integrate_A_list(); }
 ListOfParameters* SBML_confInput::get_integrateB_parameters()
 {return parameter_container.get_integrate_B_list(); }


 int SBML_confInput::get_num_import_initialAssignments(){ return (initialAssignment_container.get_num_imports());}
 int SBML_confInput::get_num_replace_initialAssignments(){ return (initialAssignment_container.get_num_replacements());}
 int SBML_confInput::get_num_integrate_initialAssignments(){ return (initialAssignment_container.get_num_integrates());}
 ListOfInitialAssignments* SBML_confInput::get_import_initialAssignments()
 {return initialAssignment_container.get_import_list();}
 ListOfInitialAssignments* SBML_confInput::get_replaceA_initialAssignments()
 {return initialAssignment_container.get_replace_A_list();}
 ListOfInitialAssignments* SBML_confInput::get_replaceB_initialAssignments()
 {return initialAssignment_container.get_replace_B_list(); }
 ListOfInitialAssignments* SBML_confInput::get_integrateA_initialAssignments()
 {return initialAssignment_container.get_integrate_A_list(); }
 ListOfInitialAssignments* SBML_confInput::get_integrateB_initialAssignments()
 {return initialAssignment_container.get_integrate_B_list(); }


 int SBML_confInput::get_num_import_rules(){ return (rule_container.get_num_imports());}
 int SBML_confInput::get_num_replace_rules(){ return (rule_container.get_num_replacements());}
 int SBML_confInput::get_num_integrate_rules(){ return (rule_container.get_num_integrates());}
 ListOfRules* SBML_confInput::get_import_rules()
 {return rule_container.get_import_list();}
 ListOfRules* SBML_confInput::get_replaceA_rules()
 {return rule_container.get_replace_A_list();}
 ListOfRules* SBML_confInput::get_replaceB_rules()
 {return rule_container.get_replace_B_list(); }
 ListOfRules* SBML_confInput::get_integrateA_rules()
 {return rule_container.get_integrate_A_list(); }
 ListOfRules* SBML_confInput::get_integrateB_rules()
 {return rule_container.get_integrate_B_list(); }


 int SBML_confInput::get_num_import_constraints(){ return ( constraint_container.get_num_imports());}
 int SBML_confInput::get_num_replace_constraints(){ return (constraint_container.get_num_replacements());}
 int SBML_confInput::get_num_integrate_constraints(){ return (constraint_container.get_num_integrates());}
 ListOfConstraints* SBML_confInput::get_import_constraints()
 {return constraint_container.get_import_list();}
 ListOfConstraints* SBML_confInput::get_replaceA_constraints()
 {return constraint_container.get_replace_A_list();}
 ListOfConstraints* SBML_confInput::get_replaceB_constraints()
 {return constraint_container.get_replace_B_list(); }
 ListOfConstraints* SBML_confInput::get_integrateA_constraints()
 {return constraint_container.get_integrate_A_list(); }
 ListOfConstraints* SBML_confInput::get_integrateB_constraints()
 {return constraint_container.get_integrate_B_list(); }


 int SBML_confInput::get_num_import_reactions(){ return (reaction_container.get_num_imports());}
 int SBML_confInput::get_num_replace_reactions(){ return (reaction_container.get_num_replacements());}
 int SBML_confInput::get_num_integrate_reactions(){ return (reaction_container.get_num_integrates());}
 ListOfReactions* SBML_confInput::get_import_reactions()
 {return reaction_container.get_import_list();}
 ListOfReactions* SBML_confInput::get_replaceA_reactions()
 {return reaction_container.get_replace_A_list();}
 ListOfReactions* SBML_confInput::get_replaceB_reactions()
 {return reaction_container.get_replace_B_list(); }
 ListOfReactions* SBML_confInput::get_integrateA_reactions()
 {return reaction_container.get_integrate_A_list(); }
 ListOfReactions* SBML_confInput::get_integrateB_reactions()
 {return reaction_container.get_integrate_B_list(); }


 int SBML_confInput::get_num_import_events(){ return (event_container.get_num_imports());}
 int SBML_confInput::get_num_replace_events(){ return (event_container.get_num_replacements());}
 int SBML_confInput::get_num_integrate_events(){ return (event_container.get_num_integrates());}
 ListOfEvents* SBML_confInput::get_import_events()
 {return event_container.get_import_list();}
 ListOfEvents* SBML_confInput::get_replaceA_events()
 {return event_container.get_replace_A_list();}
 ListOfEvents* SBML_confInput::get_replaceB_events()
 {return event_container.get_replace_B_list(); }
 ListOfEvents* SBML_confInput::get_integrateA_events()
 {return event_container.get_integrate_A_list(); }
 ListOfEvents* SBML_confInput::get_integrateB_events()
 {return event_container.get_integrate_B_list(); }
