/**
 * @file    unsetAnnotation.java
 * @brief   Unsets annotation for each element
 * @author  Akira Funahashi (translated from libSBML C++ examples (using other Java examples provided by Nicolas Rodriguez))
 * @author  Akiya Jouraku
 *
 * $Id: unsetAnnotation.java 13594 2011-04-11 01:28:15Z mhucka $
 * $HeadURL: https://sbml.svn.sourceforge.net/svnroot/sbml/branches/libsbml-5/examples/java/unsetAnnotation.java $
 *
 * This file is part of libSBML.  Please visit http://sbml.org for more
 * information about SBML, and the latest version of libSBML.
 */


import org.sbml.libsbml.Compartment;
import org.sbml.libsbml.Constraint;
import org.sbml.libsbml.Event;
import org.sbml.libsbml.InitialAssignment;
import org.sbml.libsbml.ModifierSpeciesReference;
import org.sbml.libsbml.Parameter;
import org.sbml.libsbml.SBMLWriter;
import org.sbml.libsbml.Species;
import org.sbml.libsbml.SpeciesReference;
import org.sbml.libsbml.SpeciesType;
import org.sbml.libsbml.EventAssignment;
import org.sbml.libsbml.FunctionDefinition;
import org.sbml.libsbml.KineticLaw;
import org.sbml.libsbml.Model;
import org.sbml.libsbml.Reaction;
import org.sbml.libsbml.Rule;
import org.sbml.libsbml.SBMLDocument;
import org.sbml.libsbml.SBMLReader;
import org.sbml.libsbml.UnitDefinition;
 

public class unsetAnnotation
{
  public static void main (String[] args)
  {        
    if (args.length != 2)
    {
      println("Usage: java unsetAnnotation <input-filename> <output-filename>");
      System.exit(1);
    }

    String filename       = args[0];
    SBMLDocument document;
    SBMLReader reader     = new SBMLReader();
    SBMLWriter writer     = new SBMLWriter();

    document = reader.readSBML(filename);

    long errors = document.getNumErrors();

    if (errors > 0)
    {
      document.printErrors();
      System.exit((int)errors);
    }

    Model m = document.getModel();
    m.unsetAnnotation();

    for(int i=0; i < m.getNumReactions(); i++)
    {
      Reaction re = m.getReaction(i);
      re.unsetAnnotation();

      for(int j=0; j < re.getNumReactants(); j++)
      { 
        SpeciesReference rt = re.getReactant(j);
        rt.unsetAnnotation();
      }

      for(int j=0; j < re.getNumProducts(); j++)
      { 
        SpeciesReference rt = re.getProduct(j);
        rt.unsetAnnotation();
      }

      for(int j=0; j < re.getNumModifiers(); j++)
      { 
        ModifierSpeciesReference md = re.getModifier(j);
        md.unsetAnnotation();
      }

      if(re.isSetKineticLaw())
      { 
        KineticLaw kl = re.getKineticLaw();
        kl.unsetAnnotation();

        /* Parameter */
        for(int j=0; j < kl.getNumParameters(); j++)
        { 
          Parameter pa = kl.getParameter(j);
          pa.unsetAnnotation();
        }
      }
    }
    
    for(int i=0; i < m.getNumSpecies(); i++)
    {
      Species sp = m.getSpecies(i);
      sp.unsetAnnotation();
    }   
    
    for(int i=0; i < m.getNumCompartments(); i++)
    { 
      Compartment sp = m.getCompartment(i);
      sp.unsetAnnotation();
    }   
    
    for(int i=0; i < m.getNumFunctionDefinitions(); i++)
    {
      FunctionDefinition sp = m.getFunctionDefinition(i);
      sp.unsetAnnotation();
    }

    for(int i=0; i < m.getNumUnitDefinitions(); i++)
    {
      UnitDefinition sp = m.getUnitDefinition(i);
      sp.unsetAnnotation();
    }

    for(int i=0; i < m.getNumParameters(); i++)
    {
      Parameter sp = m.getParameter(i);
      sp.unsetAnnotation();
    }

    for(int i=0; i < m.getNumRules(); i++)
    {
      Rule sp = m.getRule(i);
      sp.unsetAnnotation();
    }
    
    for(int i=0; i < m.getNumInitialAssignments(); i++)
    {
      InitialAssignment sp = m.getInitialAssignment(i);
      sp.unsetAnnotation();
    }

    for(int i=0; i < m.getNumEvents(); i++)
    { 
      Event sp = m.getEvent(i);
      sp.unsetAnnotation();

      for(int j=0; j < sp.getNumEventAssignments(); j++)
      {
        EventAssignment ea = sp.getEventAssignment(j);
        ea.unsetAnnotation();
      }
    }
    
    for(int i=0; i < m.getNumSpeciesTypes(); i++)
    {
      SpeciesType sp = m.getSpeciesType(i);
      sp.unsetAnnotation();
    }

    for(int i=0; i < m.getNumConstraints(); i++)
    {
      Constraint sp = m.getConstraint(i);
      sp.unsetAnnotation();
    }

    writer.writeSBML(document, args[1]);
    System.exit((int)errors);
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
