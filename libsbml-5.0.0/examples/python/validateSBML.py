#!/usr/bin/env python
##
## @file    validateSBML.py
## @brief   Validates one or more SBML files
## @author  Akiya Jouraku (translated from libSBML C++ examples)
## @author  Ben Bornstein
## @author  Michael Hucka
## 
## $Id: validateSBML.py 13595 2011-04-11 01:34:30Z mhucka $
## $HeadURL: https://sbml.svn.sourceforge.net/svnroot/sbml/branches/libsbml-5/examples/python/validateSBML.py $
##
## This file is part of libSBML.  Please visit http://sbml.org for more
## information about SBML, and the latest version of libSBML.

import sys
import os.path
import time
import libsbml

class validateSBML:
  def __init__(self, ucheck):
    self.reader    = libsbml.SBMLReader()
    self.ucheck    = ucheck
    self.numinvalid = 0

  def validate(self, file):
    if not os.path.exists(file):
      print("[Error] %s : No such file." % (infile))
      self.numinvalid += 1
      return

    start    = time.time()
    sbmlDoc  = libsbml.readSBML(file)
    stop     = time.time()
    timeRead = (stop - start)*1000
    errors   = sbmlDoc.getNumErrors()
    
    seriousErrors = False

    numReadErr  = 0
    numReadWarn = 0
    errMsgRead  = ""

    if errors > 0:
      
      for i in range(errors):
        severity = sbmlDoc.getError(i).getSeverity()
        if (severity == libsbml.LIBSBML_SEV_ERROR) or (severity == libsbml.LIBSBML_SEV_FATAL):
          seriousErrors = True
          numReadErr += 1
        else:
          numReadWarn += 1

        oss = libsbml.ostringstream()
        sbmlDoc.printErrors(oss)
        errMsgRead = oss.str()

    # If serious errors are encountered while reading an SBML document, it
    # does not make sense to go on and do full consistency checking because
    # the model may be nonsense in the first place.

    numCCErr  = 0
    numCCWarn = 0
    errMsgCC  = ""
    skipCC    = False;
    timeCC    = 0.0

    if seriousErrors:
      skipCC = True;
      errMsgRead += "Further consistency checking and validation aborted."
      self.numinvalid += 1;    
    else:
      sbmlDoc.setConsistencyChecks(libsbml.LIBSBML_CAT_UNITS_CONSISTENCY, self.ucheck)
      start    = time.time()
      failures = sbmlDoc.checkConsistency()
      stop     = time.time()
      timeCC   = (stop - start)*1000
  
 
      if failures > 0:

        isinvalid = False;
        for i in range(failures):
          severity = sbmlDoc.getError(i).getSeverity()
          if (severity == libsbml.LIBSBML_SEV_ERROR) or (severity == libsbml.LIBSBML_SEV_FATAL):
            numCCErr += 1
            isinvalid = True;
          else:
            numCCWarn += 1

        if isinvalid:
          self.numinvalid += 1;    

        oss = libsbml.ostringstream()
        sbmlDoc.printErrors(oss)
        errMsgCC = oss.str()

    #
    # print results
    #
        
    print("                 filename : %s" % (file))
    print("         file size (byte) : %d" % (os.path.getsize(file)))
    print("           read time (ms) : %f" % (timeRead))

    if not skipCC :
      print( "        c-check time (ms) : %f" % (timeCC))
    else:
      print( "        c-check time (ms) : skipped")

    print( "      validation error(s) : %d" % (numReadErr  + numCCErr))
    if not skipCC :
      print( "    (consistency error(s)): %d" % (numCCErr))
    else:
      print( "    (consistency error(s)): skipped")

    print( "    validation warning(s) : %d" % (numReadWarn + numCCWarn))
    if not skipCC :
      print( "  (consistency warning(s)): %d" % (numCCWarn))
    else:
      print( "  (consistency warning(s)): skipped")

    if errMsgRead or errMsgCC: 
      print()
      print( "===== validation error/warning messages =====\n")
      if errMsgRead : 
        print( errMsgRead)
      if errMsgCC : 
        print( "*** consistency check ***\n")
        print( errMsgCC)


def main (args):
  """usage: validateSBML.py [-u] inputfile1 [inputfile2 ...]
  -u  skips unit consistency check
  """
  if len(args) < 2:
    print( main.__doc__)
    sys.exit(1)
  elif (len(args) == 1) and (args[1] == "-u"):
    print( main.__doc__)
    sys.exit(1)

  enableUnitCCheck = True

  if args[1] == "-u":
    enableUnitCCheck = False

  validator = validateSBML(enableUnitCCheck)

  fnum = 0

  for i in range(1,len(args)):
    if args[i] == "-u":
      continue
    print( "---------------------------------------------------------------------------")
    validator.validate(args[i])
    fnum += 1

  numinvalid = validator.numinvalid

  print( "---------------------------------------------------------------------------")
  print( "Validated %d files, %d valid files, %d invalid files" % (fnum, fnum - numinvalid, numinvalid))
  if not enableUnitCCheck:
    print( "(Unit consistency checks skipped)")

  if numinvalid > 0:
    sys.exit(1)

if __name__ == '__main__':
  main(sys.argv)  
