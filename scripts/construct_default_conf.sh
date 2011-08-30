#! /bin/bash

echo "// configuration file for pathway_viewer - input file to define model integration
//
// Guidelines for use
// This skeleton defines the necessary structure for the config file. The structure of each of
// the components is critical, as the parser expects. Additionally, avoid using any
// of the keywords such as FunctionDefinition, Import etc with a ":" at the end. This would
// break everything.
//
// For the import list used [1,2,...n]
// For replace list do [n,n] [n+1,n+1]
// For integrate list do [n,n] [n+1,n+1]

FunctionDefinitions:
	Import: 
	Replace: 
	Integrate: 

UnitDefinitions:                                                                                                                                                                                                                               
	Import: 
	Replace: 
	Integrate: 

Compartments:
	Import: 
	Replace: 
	Integrate:

Species:
	Import: 
	Replace:
	Integrate: 

Parameters:
	Import: 
	Replace: 
	Integrate: 

InitialAssignments:
	Import: 	
	Replace: 
	Integrate: 

Rules:
	Import: 	
	Replace: 
	Integrate: 

Constraints:
	Import:	
	Replace: 
	Integrate: 

Reactions:
	Import:
	Replace: 
	Integrate: 

Events:
	Import:
	Replace: 
	Integrate: " > integrate.conf
echo "Empty configuration file (integrate.conf) has been constructed"
