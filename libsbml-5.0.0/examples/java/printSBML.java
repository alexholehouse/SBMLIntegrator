/**
 * @file    printSBML.java
 * @brief   Prints some information about the top-level model
 * @author  Nicolas Rodriguez (translated from libSBML C++ examples)
 * @author  Ben Bornstein
 * @author  Michael Hucka
 *
 * $Id: printSBML.java 13594 2011-04-11 01:28:15Z mhucka $
 * $HeadURL: https://sbml.svn.sourceforge.net/svnroot/sbml/branches/libsbml-5/examples/java/printSBML.java $
 *
 * This file is part of libSBML.  Please visit http://sbml.org for more
 * information about SBML, and the latest version of libSBML.
 */


import java.io.File;

import org.sbml.libsbml.Model;
import org.sbml.libsbml.SBMLDocument;
import org.sbml.libsbml.SBMLReader;


public class printSBML
{
  public static void main (String[] args)
  {
    if (args.length != 1)
    {
      println("Usage: java printSBML filename");
      System.exit(1);
    }


    String filename       = args[0];
    SBMLReader reader     = new SBMLReader();
    SBMLDocument document;
    Model model;
    int level, version;

    document     = reader.readSBML(filename);

    if (document.getNumErrors() > 0)
    {
      document.printErrors();
      println("Printing skipped.  Please correct the above problems first.");
      System.exit(1);
    }

    model = document.getModel();

    if (model == null)
    {
      println("There does not appear to be a model in this file");
      System.exit(1);
    }

    level   = (int) document.getLevel();
    version = (int) document.getVersion();

    println("File: " + filename +
            " (Level " + level + ", version " + version + ")\n");

    if (level == 1)
    {
      println("model name: " + model.getName());
    }
    else
    {
      println("  model id: " + (model.isSetId() ? model.getId() : "(empty)"));
    }

    println("functionDefinitions: " +   model.getNumFunctionDefinitions());
    println("    unitDefinitions: " +   model.getNumUnitDefinitions()    );
    println("       compartments: " +   model.getNumCompartments()       );
    println("            species: " +   model.getNumSpecies()            );
    println("         parameters: " +   model.getNumParameters()         );
    println("          reactions: " +   model.getNumReactions()          );
    println("              rules: " +   model.getNumRules()              );
    println("             events: " +   model.getNumEvents()             );
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
