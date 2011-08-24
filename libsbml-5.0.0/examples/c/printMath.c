/**
 * @file    printMath.c
 * @brief   Prints Rule, Reaction, and Event formulas in a given SBML Document
 * @author  Ben Bornstein
 *
 * $Id: printMath.c 11938 2010-09-20 02:04:23Z mhucka $
 * $HeadURL: https://sbml.svn.sourceforge.net/svnroot/sbml/branches/libsbml-5/examples/c/printMath.c $
 *
 * This file is part of libSBML.  Please visit http://sbml.org for more
 * information about SBML, and the latest version of libSBML.
 */

#include <stdio.h>
#include <stdlib.h>

#include <sbml/SBMLTypes.h>


void
printFunctionDefinition (unsigned int n, const FunctionDefinition_t *fd)
{
  const ASTNode_t *math;
  char *formula;


  if ( FunctionDefinition_isSetMath(fd) )
  {
    printf("FunctionDefinition %d, %s(", n, FunctionDefinition_getId(fd));

    math = FunctionDefinition_getMath(fd);

    /* Print function arguments. */
    if (ASTNode_getNumChildren(math) > 1)
    {
      printf("%s", ASTNode_getName( ASTNode_getLeftChild(math) ));

      for (n = 1; n < ASTNode_getNumChildren(math) - 1; ++n)
      {
        printf(", %s", ASTNode_getName( ASTNode_getChild(math, n) ));
      }
    }

    printf(") := ");

    /* Print function body. */
    if (ASTNode_getNumChildren(math) == 0)
    {
      printf("(no body defined)");
    }
    else
    {
      math    = ASTNode_getChild(math, ASTNode_getNumChildren(math) - 1);
      formula = SBML_formulaToString(math);
      printf("%s\n", formula);
      free(formula);
    }
  }
}


void
printRuleMath (unsigned int n, const Rule_t *r)
{
  char *formula;


  if ( Rule_isSetMath(r) )
  {
    formula = SBML_formulaToString( Rule_getMath(r) );
    printf("Rule %d, formula: %s\n", n, formula);
    free(formula);
  }
}


void
printReactionMath (unsigned int n, Reaction_t *r)
{
  char         *formula;
  KineticLaw_t *kl;


  if (Reaction_isSetKineticLaw(r))
  {
    kl = Reaction_getKineticLaw(r);

    if ( KineticLaw_isSetMath(kl) )
    {
      formula = SBML_formulaToString( KineticLaw_getMath(kl) );
      printf("Reaction %d, formula: %s\n", n, formula);
      free(formula);
    }
  }
}


void
printEventAssignmentMath (unsigned int n, const EventAssignment_t *ea)
{
  const char *variable;
  char       *formula;


  if ( EventAssignment_isSetMath(ea) )
  {
    variable = EventAssignment_getVariable(ea);
    formula  = SBML_formulaToString( EventAssignment_getMath(ea) );

    printf("  EventAssignment %d, trigger: %s = %s\n", n, variable, formula);

    free(formula);
  }
}


void
printEventMath (unsigned int n, Event_t *e)
{
  char         *formula;
  unsigned int i;


  if ( Event_isSetDelay(e) )
  {
    const Delay_t *delay = Event_getDelay(e);

    formula = SBML_formulaToString( Delay_getMath(delay) );
    printf("Event %d delay: %s\n", n, formula);
    free(formula);
  }

  if ( Event_isSetTrigger(e) )
  {
    const Trigger_t *trigger = Event_getTrigger(e);

    formula = SBML_formulaToString( Trigger_getMath(trigger) );
    printf("Event %d trigger: %s\n", n, formula);
    free(formula);
  }

  for (i = 0; i < Event_getNumEventAssignments(e); ++i)
  {
    printEventAssignmentMath(i + 1, Event_getEventAssignment(e, i));
  }

  printf("\n");
}


void
printMath (Model_t *m)
{
  unsigned int  n;


  for (n = 0; n < Model_getNumFunctionDefinitions(m); ++n)
  {
    printFunctionDefinition(n + 1, Model_getFunctionDefinition(m, n));
  }

  for (n = 0; n < Model_getNumRules(m); ++n)
  {
    printRuleMath(n + 1, Model_getRule(m, n));
  }

  printf("\n");

  for (n = 0; n < Model_getNumReactions(m); ++n)
  {
    printReactionMath(n + 1, Model_getReaction(m, n));
  }

  printf("\n");

  for (n = 0; n < Model_getNumEvents(m); ++n)
  {
    printEventMath(n + 1, Model_getEvent(m, n));
  }
}


int
main (int argc, char *argv[])
{
  SBMLDocument_t *d;
  Model_t        *m;


  if (argc != 2)
  {
    printf("Usage: printMath filename\n");
    return 1;
  }

  d = readSBML(argv[1]);
  m = SBMLDocument_getModel(d);

  SBMLDocument_printErrors(d, stdout);

  printMath(m);
  printf("\n");

  SBMLDocument_free(d);
  return 0;
}
