// Copyright Alex Holehouse 2011
// Distributed under the terms of the GNU general public license - see COPYING.txt for more details

#include "sbml_formatter.h"
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
#include <math.h>
#include <sys/stat.h>

using namespace std;


// initial default values;
int SBML_formatter::unique = rand()% 1000;
bool SBML_formatter::logfile_set = false;
ofstream SBML_formatter::log_stream;

// function which takes a double and returns it as a string
//-----------------------------------------------------------------------------------
string SBML_formatter::dtostr(double in){

  ostringstream string_stream;
  string return_string;

  string_stream << in;
  return_string = string_stream.str();
  
  return (return_string);
}




    

// #######################################################################
SpeciesReference* SBML_formatter::species2SpeciesReference(const Species* species, const Reaction* rxn){
  return (species2SpeciesReference(species, rxn, ""));
}

// #######################################################################
SpeciesReference* SBML_formatter::species2SpeciesReference(const Species* species, const Reaction* rxn, string addToSpeciesID){
  string value = species->getId(); 
  
  SpeciesReference* SR = new SpeciesReference(species->getLevel(), species->getVersion());
  
  value = species->getId();

  if (addToSpeciesID != ""){
    // sets the species name, as 
    value.append(addToSpeciesID);
  }
  
  SR->setSpecies(value);
  
  SR->setStoichiometry(1);
  SR->setId((value.append("_ref_")).append(dtostr(unique)));
  value.clear();
  value.append(species->getId());
  SR->setName((value.append("_in_rxn_")).append(rxn->getId()));
  // unique is a static variable which allows anything that needs a modelwide unique value to get
  // one;
  unique++;

  return SR;
}

// #######################################################################
ModifierSpeciesReference* SBML_formatter::species2ModifierSpeciesReference(const Species* species, const Reaction* rxn) {
  
  string value;
  
  ModifierSpeciesReference* MSR = new ModifierSpeciesReference(species->getLevel(), species->getVersion());
  
  value = species->getId();

  MSR->setSpecies(value);
  
  MSR->setId((value.append("_ref_")).append(dtostr(unique)));
  value.clear();
  value.append(species->getId());
  MSR->setName((value.append("_in_rxn_")).append(rxn->getId()));
  // unique is a static variable which allows anything that needs a modelwide unique value to get
  // one;
  unique++;

  return MSR;
}

// #######################################################################
void SBML_formatter::reset_cstr(char c_str[], int size){
  for (int i = 0 ; i < size ;i++)
    c_str[i] = ' ';
}



// #######################################################################
// Autoabort
void SBML_formatter::autoAbort(string message){
  cout << message << endl;
  log_stream << message << endl;
  SBML_EXIT();
  exit(1);
}

// default constructor -- called by all SBML_formatter inheriting classes
//-----------------------------------------------------------------------------------
SBML_formatter::SBML_formatter(){

  // If this is the first time a file with an SBML_formatter base is created you generate 
  // new logfile, which is then used throughout
  
  if (!logfile_set){
    
    
    // if logsfile not already present make one, if it is skip this
    struct stat st;
    if(stat("logs",&st) != 0)
      system("mkdir logs\0");
    
    // build logfile name
    string name = "logs/";
    name.append("logat_");
    name.append(get_time());
    name.append(".txt");
    
    char* output = (char*)name.c_str();
    
    log_stream.open(output);
    
    log_stream << "PathwayViewer version " << get_version() << " logfile for " << get_time() << " on " << get_date() << endl;
    
    // set logfile so initial logfile message isn't printed again!
    logfile_set=true;
  }
}



// Should be the last thing main calls - closes the static log_stream. This is critical!
//-----------------------------------------------------------------------------------
int SBML_formatter::SBML_EXIT(){
  log_stream.close();
  // TODO - close conf_file logstream
  return 0;
}



// Function which returns the current date as "DD_MM_YYYY"
//-----------------------------------------------------------------------------------
string SBML_formatter::get_date(){
  time_t now;
  char the_date[12];
  
  the_date[0] = '\0';
  
  now = time(NULL);
  
  if (now != -1){
    strftime(the_date, 12, "%d_%m_%Y", gmtime(&now));
  }
  
  return string(the_date);
}



// function which returns the current time as HH_MM_SS
//-----------------------------------------------------------------------------------
string SBML_formatter::get_time(){
  time_t now;
  char the_time[9];
  
  the_time[0] = '\0';
  
  now = time(NULL);
  
  if (now != -1){
    strftime(the_time, 12, "%H_%M_%S", gmtime(&now));
  }
  
  return string(the_time);
}


// function which returns the current pathway_viewer version
//-----------------------------------------------------------------------------------
string SBML_formatter::get_version(){
  return "0.1 (alpha)";
}





void SBML_formatter::logfile_add_message(int error, std::string element, std::string new_owner){
  if (error !=0)
    log_stream << "WARNING - error " << error << " adding " << element << " to " << new_owner << endl;
}
 

//-----------------------------------------------------------------------------------
bool SBML_formatter::write_to_file(Model* input, string filename){
  
  ofstream SBMLDoc_out;
  
  SBMLDoc_out.open(filename.c_str());

  log_stream << "Writing to " << filename << " in PWD" << endl;
  
  SBMLDocument*  document = new SBMLDocument(input->getLevel(), input->getVersion());
  document->setModel(input);

  SBMLWriter* writer = new SBMLWriter;
  
  writer->writeSBML(document, SBMLDoc_out);
  
  if(SBMLDoc_out.fail() || SBMLDoc_out.bad())
    return false;

  else
    return true;
}
