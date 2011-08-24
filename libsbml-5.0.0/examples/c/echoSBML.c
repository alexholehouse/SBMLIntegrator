/**
 * @file    echoSBML.c
 * @brief   Echos (and pretty prints) an SBML model.
 * @author  Ben Bornstein
 *
 * $Id: echoSBML.c 11938 2010-09-20 02:04:23Z mhucka $
 * $HeadURL: https://sbml.svn.sourceforge.net/svnroot/sbml/branches/libsbml-5/examples/c/echoSBML.c $
 *
 * This file is part of libSBML.  Please visit http://sbml.org for more
 * information about SBML, and the latest version of libSBML.
 */


#include <stdio.h>
#include <sbml/SBMLTypes.h>


int
main (int argc, char *argv[])
{
  if (argc != 3)
  {
    printf("Usage: echoSBML input-filename output-filename\n");
    return 2;
  }

  writeSBML(readSBML(argv[1]), argv[2]);
  return 0;
}
