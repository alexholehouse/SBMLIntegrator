/**
 * @file    validateSBML.java
 * @brief   Validates an SBML file against the appropriate schema
 * @author  Nicolas Rodriguez (translated from libSBML C++ examples)
 * @author  Ben Bornstein
 * @author  Michael Hucka
 *
 * $Id: validateSBML.java 13594 2011-04-11 01:28:15Z mhucka $
 * $HeadURL: https://sbml.svn.sourceforge.net/svnroot/sbml/branches/libsbml-5/examples/java/validateSBML.java $
 *
 * This file is part of libSBML.  Please visit http://sbml.org for more
 * information about SBML, and the latest version of libSBML.
 */


import java.io.File;

import org.sbml.libsbml.SBMLDocument;
import org.sbml.libsbml.SBMLReader;
import org.sbml.libsbml.Model;


public class validateSBML
{
  public static void main (String[] args)
  {
    if (args.length != 1)
    {
      System.out.println("Usage: java validateSBML filename");
      System.exit(1);
    }

    String filename       = args[0];
    SBMLReader reader     = new SBMLReader();
    SBMLDocument document;
    long start, stop;

    start    = System.currentTimeMillis();
    document = reader.readSBML(filename);
    stop     = System.currentTimeMillis();

    if (document.getNumErrors() > 0)
    {
      print("Encountered the following errors while reading the SBML file:\n");
      document.printErrors();
      print("\nFurther consistency checking and validation aborted.\n");
      System.exit(1);
    }
    else
    {
      long errors = document.checkConsistency();
      long size   = new File(filename).length();

      println("            filename: " + filename);
      println("           file size: " + size);
      println("      read time (ms): " + (stop - start));
      println(" validation error(s): " + errors);

      if (errors > 0)
      {
	document.printErrors();
	System.exit(1);
      }
    }
  }


  static void print (String msg)
  {
    System.out.print(msg);
  }

  static void println (String msg)
  {
    System.out.println(msg);
  }


  /**
   * Loads the SWIG-generated libSBML Java module when this class is
   * loaded, or reports a sensible diagnostic message about why it failed.
   */
  static
  {
    String varname;
    String shlibname;

    if (System.getProperty("os.name").startsWith("Mac OS"))
    {
      varname = "DYLD_LIBRARY_PATH";    // We're on a Mac.
      shlibname = "'libsbmlj.jnilib'";
    }
    else
    {
      varname = "LD_LIBRARY_PATH";      // We're not on a Mac.
      shlibname = "'libsbmlj.so' and/or 'libsbml.so'";
    }

    try
    {
      System.loadLibrary("sbmlj");
      // For extra safety, check that the jar file is in the classpath.
      Class.forName("org.sbml.libsbml.libsbml");
    }
    catch (UnsatisfiedLinkError e)
    {
      System.err.println("Error encountered while attempting to load libSBML:");
      e.printStackTrace();
      System.err.println("Please check the value of your " + varname +
                         " environment variable and/or" +
                         " your 'java.library.path' system property" +
                         " (depending on which one you are using) to" +
                         " make sure it list the directories needed to" +
                         " find the " + shlibname + " library file and the" +
                         " libraries it depends upon (e.g., the XML parser).");
      System.exit(1);
    }
    catch (ClassNotFoundException e)
    {
      System.err.println("Error: unable to load the file 'libsbmlj.jar'." +
                         " It is likely that your -classpath command line " +
                         " setting or your CLASSPATH environment variable " +
                         " do not include the file 'libsbmlj.jar'.");
      System.exit(1);
    }
    catch (SecurityException e)
    {
      System.err.println("Error encountered while attempting to load libSBML:");
      e.printStackTrace();
      System.err.println("Could not load the libSBML library files due to a"+
                         " security exception.\n");
      System.exit(1);
    }
  }
}
