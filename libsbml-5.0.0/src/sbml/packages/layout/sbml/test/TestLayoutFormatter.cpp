/**
 * Filename    : TestLayoutFormatter.cpp
 * Description : Unit tests for LayoutFormatter
 * Organization: European Media Laboratories Research gGmbH
 * Created     : 2005-05-03
 *
 * Copyright 2005 European Media Laboratories Research gGmbH
 *
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published
 * by the Free Software Foundation; either version 2.1 of the License, or
 * any later version.
 *
 * This library is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY, WITHOUT EVEN THE IMPLIED WARRANTY OF
 * MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE.  The software and
 * documentation provided hereunder is on an "as is" basis, and the
 * European Media Laboratories Research gGmbH have no obligations to
 * provide maintenance, support, updates, enhancements or modifications.
 * In no event shall the European Media Laboratories Research gGmbH be
 * liable to any party for direct, indirect, special, incidental or
 * consequential damages, including lost profits, arising out of the use of
 * this software and its documentation, even if the European Media
 * Laboratories Research gGmbH have been advised of the possibility of such
 * damage.  See the GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library; if not, write to the Free Software Foundation,
 * Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA.
 *
 * The original code contained here was initially developed by:
 *
 *     Ralph Gauges
 *     Bioinformatics Group
 *     European Media Laboratories Research gGmbH
 *     Schloss-Wolfsbrunnenweg 31c
 *     69118 Heidelberg
 *     Germany
 *
 *     http://www.eml-research.de/english/Research/BCB/
 *     mailto:ralph.gauges@eml-r.villa-bosch.de
 *
 * Contributor(s):
 */


#include <iostream>

#include <locale.h>

#include <sbml/common/common.h>

#include <sbml/packages/layout/sbml/Layout.h>
#include <sbml/packages/layout/sbml/GraphicalObject.h>
#include <sbml/packages/layout/sbml/CompartmentGlyph.h>
#include <sbml/packages/layout/sbml/SpeciesGlyph.h>
#include <sbml/packages/layout/sbml/ReactionGlyph.h>
#include <sbml/packages/layout/sbml/TextGlyph.h>
#include <sbml/packages/layout/sbml/SpeciesReferenceGlyph.h>
#include <sbml/packages/layout/sbml/LineSegment.h>
#include <sbml/packages/layout/sbml/CubicBezier.h>
#include <sbml/packages/layout/sbml/Curve.h>
#include <sbml/packages/layout/sbml/Point.h>
#include <sbml/packages/layout/sbml/Dimensions.h>

#include <check.h>

#include <sbml/xml/XMLInputStream.h>
#include <sbml/xml/XMLNode.h>
#include "utility.h"

LIBSBML_CPP_NAMESPACE_USE

BEGIN_C_DECLS

static LayoutPkgNamespaces* LNLV2;

void
LayoutFormatterTest_setup (void)
{
  LNLV2 = new LayoutPkgNamespaces(2,4);
}

void 
LayoutFormatterTest_teardown (void)
{
  delete LNLV2;
}


START_TEST (test_LayoutFormatter_Layout)
{
    const char* s = 
      "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
      "<layout id=\"layout_1\">\n"
      "  <dimensions width=\"200\" height=\"400\"/>\n" 
      "  <listOfCompartmentGlyphs>\n"
      "    <compartmentGlyph id=\"compartmentGlyph_1\">\n"
      "      <boundingBox>\n"
      "        <position x=\"0\" y=\"0\"/>\n"
      "        <dimensions width=\"0\" height=\"0\"/>\n" 
      "      </boundingBox>\n"  
      "    </compartmentGlyph>\n"
      "  </listOfCompartmentGlyphs>\n"
      "  <listOfSpeciesGlyphs>\n"
      "    <speciesGlyph id=\"speciesGlyph_1\">\n"
      "      <boundingBox>\n"
      "        <position x=\"0\" y=\"0\"/>\n"
      "        <dimensions width=\"0\" height=\"0\"/>\n" 
      "      </boundingBox>\n"  
      "    </speciesGlyph>\n"
      "  </listOfSpeciesGlyphs>\n"
      "  <listOfReactionGlyphs>\n"
      "    <reactionGlyph id=\"reactionGlyph_1\">\n"
      "      <boundingBox>\n"
      "        <position x=\"0\" y=\"0\"/>\n"
      "        <dimensions width=\"0\" height=\"0\"/>\n" 
      "      </boundingBox>\n"  
      "    </reactionGlyph>\n"
      "  </listOfReactionGlyphs>\n"
      "  <listOfTextGlyphs>\n"
      "    <textGlyph id=\"textGlyph_1\" text=\"test\">\n"
      "      <boundingBox>\n"
      "        <position x=\"0\" y=\"0\"/>\n"
      "        <dimensions width=\"0\" height=\"0\"/>\n" 
      "      </boundingBox>\n"  
      "    </textGlyph>\n"
      "  </listOfTextGlyphs>\n"
      "  <listOfAdditionalGraphicalObjects>\n"
      "    <graphicalObject id=\"graphicalObject_1\">\n"
      "      <boundingBox>\n"
      "        <position x=\"0\" y=\"0\"/>\n"
      "        <dimensions width=\"0\" height=\"0\"/>\n" 
      "      </boundingBox>\n"  
      "    </graphicalObject>\n"
      "  </listOfAdditionalGraphicalObjects>\n"
      "</layout>\n"     
    ;

    XMLInputStream stream(s,false);
    XMLNode node(stream);

    Dimensions dim=Dimensions(LNLV2,200.0,400.0);
    Layout l(LNLV2,"layout_1",&dim);
    CompartmentGlyph* cg=l.createCompartmentGlyph();
    cg->setId("compartmentGlyph_1");
    SpeciesGlyph* sg=l.createSpeciesGlyph();
    sg->setId("speciesGlyph_1");
    ReactionGlyph* rg=l.createReactionGlyph();
    rg->setId("reactionGlyph_1");
    TextGlyph* tg=l.createTextGlyph();
    tg->setId("textGlyph_1");
    tg->setText("test");
    GraphicalObject* go=l.createAdditionalGraphicalObject();
    go->setId("graphicalObject_1");

    fail_unless( node.equals(l.toXML()) );   
}
END_TEST

START_TEST (test_LayoutFormatter_Layout_notes)
{
    const char* s = 
      "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
      "<layout id=\"layout_1\">\n"
      "  <notes>\n"
      "    <body xmlns=\"http://www.w3.org/1999/xhtml\">Test note.</body>\n"
      "</notes>\n"
      "  <dimensions width=\"200\" height=\"400\"/>\n"
      "</layout>\n"     
    ;

    XMLInputStream stream(s,false);
    XMLNode node(stream);


    Dimensions dim=Dimensions(LNLV2,200.0,400.0);
    Layout l(LNLV2,"layout_1",&dim);
    XMLInputStream stream2("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<body xmlns=\"http://www.w3.org/1999/xhtml\">Test note.</body>",false);
    XMLNode notes(stream2);
    l.appendNotes(&notes);

    fail_unless( node.equals(l.toXML()) );   
    
}
END_TEST

START_TEST (test_LayoutFormatter_Layout_annotation)
{
    const char* s = 
      "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
      "<layout id=\"layout_1\">\n"
      "  <annotation>\n"
      "    <this-is-a-test/>\n"
      "  </annotation>\n"
      "  <dimensions width=\"200\" height=\"400\"/>\n" 
      "</layout>\n"     
    ;

    const char* a =
      "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
      "<annotation>\n"
      "    <this-is-a-test/>\n"
      "  </annotation>";

    XMLInputStream stream(s,false);
    XMLNode node(stream);


    Dimensions dim=Dimensions(LNLV2,200.0,400.0);
    Layout l(LNLV2,"layout_1",&dim);
    XMLInputStream stream2(a,false);
    XMLNode* annotation=new XMLNode(stream2);
    l.appendAnnotation(annotation);


    fail_unless( node.equals(l.toXML()) );   
    
}
END_TEST

START_TEST (test_LayoutFormatter_Layout_skipOptional)
{
    const char* s = 
     "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
     "<layout id=\"layout_1\">\n"
      "  <dimensions width=\"200\" height=\"400\"/>\n" 
      "</layout>\n"     
    ;

    XMLInputStream stream(s,false);
    XMLNode node(stream);


    Dimensions dim=Dimensions(LNLV2,200.0,400.0);
    Layout l(LNLV2,"layout_1",&dim);

    fail_unless( node.equals(l.toXML()) );   

}
END_TEST


START_TEST (test_LayoutFormatter_CompartmentGlyph)
{
    char* s=
      "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
      "<compartmentGlyph id=\"compartmentGlyph_1\" compartment=\"compartment_1\">\n"
      "  <boundingBox>\n"
      "    <position x=\"10.3\" y=\"20\"/>\n"
      "    <dimensions width=\"200.5\" height=\"400.5\"/>\n" 
      "  </boundingBox>\n"  
      "</compartmentGlyph>\n"
    ;
    

    XMLInputStream stream(s,false);
    XMLNode node(stream);

    
    CompartmentGlyph cg=CompartmentGlyph(LNLV2);
    cg.setId("compartmentGlyph_1");
    cg.setCompartmentId("compartment_1");
    Dimensions dim=Dimensions(LNLV2,200.5,400.5);
    Point pos=Point(LNLV2,10.3,20.0);
    BoundingBox box=BoundingBox(LNLV2,"",&pos,&dim);
    cg.setBoundingBox(&box);

    fail_unless( node.equals(cg.toXML()) );   


}
END_TEST

START_TEST (test_LayoutFormatter_CompartmentGlyph_notes)
{
    char* s=
      "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
      "<compartmentGlyph id=\"compartmentGlyph_1\">\n"
      "  <notes>\n"
      "    <body xmlns=\"http://www.w3.org/1999/xhtml\">Test note.</body>\n"
      "</notes>\n"
      "  <boundingBox>\n"
      "    <position x=\"10.3\" y=\"20\"/>\n"
      "    <dimensions width=\"200.5\" height=\"400.5\"/>\n" 
      "  </boundingBox>\n"  
      "</compartmentGlyph>\n"
    ;
    

    XMLInputStream stream(s,false);
    XMLNode node(stream);

    
    CompartmentGlyph cg=CompartmentGlyph(LNLV2);
    cg.setId("compartmentGlyph_1");
    XMLInputStream stream2("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<body xmlns=\"http://www.w3.org/1999/xhtml\">Test note.</body>",false);
    XMLNode notes(stream2);
    cg.appendNotes(&notes);

    Dimensions dim=Dimensions(LNLV2,200.5,400.5);
    Point pos=Point(LNLV2,10.3,20.0);
    BoundingBox box=BoundingBox(LNLV2,"",&pos,&dim);
    cg.setBoundingBox(&box);

    fail_unless( node.equals(cg.toXML()) );   

}
END_TEST

START_TEST (test_LayoutFormatter_CompartmentGlyph_annotation)
{
    const char* a =
      "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
      "<annotation>\n"
      "    <this-is-a-test/>\n"
      "  </annotation>";

    char* s=
      "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
      "<compartmentGlyph id=\"compartmentGlyph_1\">\n"
      "  <annotation>\n"
      "    <this-is-a-test/>\n"
      "  </annotation>\n"
      "  <boundingBox>\n"
      "    <position x=\"10.3\" y=\"20\"/>\n"
      "    <dimensions width=\"200.5\" height=\"400.5\"/>\n" 
      "  </boundingBox>\n"  
      "</compartmentGlyph>\n"
    ;
    

    XMLInputStream stream(s,false);
    XMLNode node(stream);

    
    CompartmentGlyph cg=CompartmentGlyph(LNLV2);
    cg.setId("compartmentGlyph_1");
    XMLInputStream stream2(a,false);
    XMLNode* annotation=new XMLNode(stream2);
    cg.appendAnnotation(annotation);

    Dimensions dim=Dimensions(LNLV2,200.5,400.5);
    Point pos=Point(LNLV2,10.3,20.0);
    BoundingBox box=BoundingBox(LNLV2,"",&pos,&dim);
    cg.setBoundingBox(&box);

    fail_unless( node.equals(cg.toXML()) );   

}
END_TEST

START_TEST (test_LayoutFormatter_CompartmentGlyph_skipOptional)
{
    char* s=
      "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
      "<compartmentGlyph id=\"compartmentGlyph_1\">\n"
      "  <boundingBox>\n"
      "    <position x=\"10.3\" y=\"20\"/>\n"
      "    <dimensions width=\"200.5\" height=\"400.5\"/>\n" 
      "  </boundingBox>\n"  
      "</compartmentGlyph>\n"
    ;
    

    XMLInputStream stream(s,false);
    XMLNode node(stream);

    
    CompartmentGlyph cg=CompartmentGlyph(LNLV2);
    cg.setId("compartmentGlyph_1");
    Dimensions dim=Dimensions(LNLV2,200.5,400.5);
    Point pos=Point(LNLV2,10.3,20.0);
    BoundingBox box=BoundingBox(LNLV2,"",&pos,&dim);
    cg.setBoundingBox(&box);

    fail_unless( node.equals(cg.toXML()) );   

}
END_TEST

START_TEST (test_LayoutFormatter_SpeciesGlyph)
{
    char* s=
      "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
      "<speciesGlyph id=\"speciesGlyph_1\" species=\"species_1\">\n"
      "  <boundingBox>\n"
      "    <position x=\"10.3\" y=\"20\"/>\n"
      "    <dimensions width=\"200.5\" height=\"400.5\"/>\n" 
      "  </boundingBox>\n"  
      "</speciesGlyph>\n"
    ;
    

    XMLInputStream stream(s,false);
    XMLNode node(stream);

    
    SpeciesGlyph sg=SpeciesGlyph(LNLV2);
    sg.setId("speciesGlyph_1");
    sg.setSpeciesId("species_1");
    Dimensions dim=Dimensions(LNLV2,200.5,400.5);
    Point pos=Point(LNLV2,10.3,20.0);
    BoundingBox box=BoundingBox(LNLV2,"",&pos,&dim);
    sg.setBoundingBox(&box);

    fail_unless( node.equals(sg.toXML()) );   


}
END_TEST

START_TEST (test_LayoutFormatter_SpeciesGlyph_notes)
{
    char* s=
      "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
      "<speciesGlyph id=\"speciesGlyph_1\">\n"
      "  <notes>\n"
      "    <body xmlns=\"http://www.w3.org/1999/xhtml\">Test note.</body>\n"
      "</notes>\n"
      "  <boundingBox>\n"
      "    <position x=\"10.3\" y=\"20\"/>\n"
      "    <dimensions width=\"200.5\" height=\"400.5\"/>\n" 
      "  </boundingBox>\n"  
      "</speciesGlyph>\n"
    ;
    

    XMLInputStream stream(s,false);
    XMLNode node(stream);

    
    SpeciesGlyph sg=SpeciesGlyph(LNLV2);
    sg.setId("speciesGlyph_1");
    XMLInputStream stream2("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<body xmlns=\"http://www.w3.org/1999/xhtml\">Test note.</body>",false);
    XMLNode notes(stream2);
    sg.appendNotes(&notes);

    Dimensions dim=Dimensions(LNLV2,200.5,400.5);
    Point pos=Point(LNLV2,10.3,20.0);
    BoundingBox box=BoundingBox(LNLV2,"",&pos,&dim);
    sg.setBoundingBox(&box);

    fail_unless( node.equals(sg.toXML()) );   

}
END_TEST

START_TEST (test_LayoutFormatter_SpeciesGlyph_annotation)
{
    const char* a =
      "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
      "<annotation>\n"
      "    <this-is-a-test/>\n"
      "  </annotation>";

    char* s=
      "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
      "<speciesGlyph id=\"speciesGlyph_1\">\n"
      "  <annotation>\n"
      "    <this-is-a-test/>\n"
      "  </annotation>\n"
      "  <boundingBox>\n"
      "    <position x=\"10.3\" y=\"20\"/>\n"
      "    <dimensions width=\"200.5\" height=\"400.5\"/>\n" 
      "  </boundingBox>\n"  
      "</speciesGlyph>\n"
    ;
    

    XMLInputStream stream(s,false);
    XMLNode node(stream);

    
    SpeciesGlyph sg=SpeciesGlyph(LNLV2);
    sg.setId("speciesGlyph_1");
    XMLInputStream stream2(a,false);
    XMLNode* annotation=new XMLNode(stream2);
    sg.appendAnnotation(annotation);

    Dimensions dim=Dimensions(LNLV2,200.5,400.5);
    Point pos=Point(LNLV2,10.3,20.0);
    BoundingBox box=BoundingBox(LNLV2,"",&pos,&dim);
    sg.setBoundingBox(&box);

    fail_unless( node.equals(sg.toXML()) );   

}
END_TEST

START_TEST (test_LayoutFormatter_SpeciesGlyph_skipOptional)
{
    char* s=
      "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
      "<speciesGlyph id=\"speciesGlyph_1\">\n"
      "  <boundingBox>\n"
      "    <position x=\"10.3\" y=\"20\"/>\n"
      "    <dimensions width=\"200.5\" height=\"400.5\"/>\n" 
      "  </boundingBox>\n"  
      "</speciesGlyph>\n"
    ;
    

    XMLInputStream stream(s,false);
    XMLNode node(stream);

    
    SpeciesGlyph sg=SpeciesGlyph(LNLV2);
    sg.setId("speciesGlyph_1");
    Dimensions dim=Dimensions(LNLV2,200.5,400.5);
    Point pos=Point(LNLV2,10.3,20.0);
    BoundingBox box=BoundingBox(LNLV2,"",&pos,&dim);
    sg.setBoundingBox(&box);

    fail_unless( node.equals(sg.toXML()) );   

}
END_TEST

START_TEST (test_LayoutFormatter_ReactionGlyph_Curve)
{
    char* s=
      "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
      "<annotation xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\">"
      "<reactionGlyph id=\"reactionGlyph_1\" reaction=\"reaction_1\">\n"
      "  <curve>\n"
      "    <listOfCurveSegments>\n"
      "      <curveSegment xsi:type=\"LineSegment\">\n" 
      "        <start x=\"10\" y=\"10\"/>\n" 
      "        <end x=\"20\" y=\"10\"/>\n" 
      "      </curveSegment>\n"
      "    </listOfCurveSegments>\n"
      "  </curve>\n"
      "</reactionGlyph>\n"
      "</annotation>"
    ;
    

    XMLInputStream stream(s,false);
    XMLNode node(stream);

    
    ReactionGlyph rg=ReactionGlyph(LNLV2);
    rg.setId("reactionGlyph_1");
    rg.setReactionId("reaction_1");
    LineSegment* ls=rg.createLineSegment();
    ls->setStart(10.0,10.0);
    ls->setEnd(20.0,10.0);

    fail_unless( node.getChild(0).equals(rg.toXML()) );   

}
END_TEST

START_TEST (test_LayoutFormatter_ReactionGlyph_BoundingBox)
{
    char* s=
      "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
      "<reactionGlyph id=\"reactionGlyph_1\" reaction=\"reaction_1\">\n"
      "  <boundingBox>\n"
      "    <position x=\"10.3\" y=\"20\"/>\n"
      "    <dimensions width=\"200.5\" height=\"400.5\"/>\n" 
      "  </boundingBox>\n"  
      "</reactionGlyph>\n"
    ;
    

    XMLInputStream stream(s,false);
    XMLNode node(stream);

    
    ReactionGlyph rg=ReactionGlyph(LNLV2);
    rg.setId("reactionGlyph_1");
    rg.setReactionId("reaction_1");
    Dimensions dim=Dimensions(LNLV2,200.5,400.5);
    Point pos=Point(LNLV2,10.3,20.0);
    BoundingBox box=BoundingBox(LNLV2,"",&pos,&dim);
    rg.setBoundingBox(&box);


    fail_unless( node.equals(rg.toXML()) );   

}
END_TEST

START_TEST (test_LayoutFormatter_ReactionGlyph_notes)
{
    char* s=
      "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
      "<reactionGlyph id=\"reactionGlyph_1\" reaction=\"reaction_1\">\n"
      "  <notes>\n"
      "    <body xmlns=\"http://www.w3.org/1999/xhtml\">Test note.</body>\n"
      "</notes>\n"
      "  <boundingBox>\n"
      "    <position x=\"10.3\" y=\"20\"/>\n"
      "    <dimensions width=\"200.5\" height=\"400.5\"/>\n" 
      "  </boundingBox>\n"  
      "</reactionGlyph>\n"
    ;
    

    XMLInputStream stream(s,false);
    XMLNode node(stream);

    
    ReactionGlyph rg=ReactionGlyph(LNLV2);
    rg.setId("reactionGlyph_1");
    XMLInputStream stream2("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<body xmlns=\"http://www.w3.org/1999/xhtml\">Test note.</body>",false);
    XMLNode notes(stream2);
    rg.appendNotes(&notes);

    rg.setReactionId("reaction_1");
    Dimensions dim=Dimensions(LNLV2,200.5,400.5);
    Point pos=Point(LNLV2,10.3,20.0);
    BoundingBox box=BoundingBox(LNLV2,"",&pos,&dim);
    rg.setBoundingBox(&box);

    fail_unless( node.equals(rg.toXML()) );   

}
END_TEST

START_TEST (test_LayoutFormatter_ReactionGlyph_annotation)
{
    const char* a =
      "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
      "<annotation>\n"
      "    <this-is-a-test/>\n"
      "  </annotation>";

    char* s=
      "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
      "<reactionGlyph id=\"reactionGlyph_1\" reaction=\"reaction_1\">\n"
      "  <annotation>\n"
      "    <this-is-a-test/>\n"
      "  </annotation>\n"
      "  <boundingBox>\n"
      "    <position x=\"10.3\" y=\"20\"/>\n"
      "    <dimensions width=\"200.5\" height=\"400.5\"/>\n" 
      "  </boundingBox>\n"  
      "</reactionGlyph>\n"
    ;
    

    XMLInputStream stream(s,false);
    XMLNode node(stream);

    
    ReactionGlyph rg=ReactionGlyph(LNLV2);
    rg.setId("reactionGlyph_1");
    rg.setReactionId("reaction_1");
    XMLInputStream stream2(a,false);
    XMLNode* annotation=new XMLNode(stream2);
    rg.appendAnnotation(annotation);

    Dimensions dim=Dimensions(LNLV2,200.5,400.5);
    Point pos=Point(LNLV2,10.3,20.0);
    BoundingBox box=BoundingBox(LNLV2,"",&pos,&dim);
    rg.setBoundingBox(&box);

    fail_unless( node.equals(rg.toXML()) );   

}
END_TEST

START_TEST (test_LayoutFormatter_ReactionGlyph_skipOptional)
{
    char* s=
      "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
      "<reactionGlyph id=\"reactionGlyph_1\">\n"
      "  <boundingBox>\n"
      "    <position x=\"10.3\" y=\"20\"/>\n"
      "    <dimensions width=\"200.5\" height=\"400.5\"/>\n" 
      "  </boundingBox>\n"  
      "</reactionGlyph>\n"
    ;
    

    XMLInputStream stream(s,false);
    XMLNode node(stream);

    
    ReactionGlyph rg=ReactionGlyph(LNLV2);
    rg.setId("reactionGlyph_1");
    Dimensions dim=Dimensions(LNLV2,200.5,400.5);
    Point pos=Point(LNLV2,10.3,20.0);
    BoundingBox box=BoundingBox(LNLV2,"",&pos,&dim);
    rg.setBoundingBox(&box);

    fail_unless( node.equals(rg.toXML()) );   

}
END_TEST

START_TEST (test_LayoutFormatter_SpeciesReferenceGlyph_Curve)
{
    char* s=
      "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
      "<annotation xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\">"
      "<speciesReferenceGlyph id=\"speciesReferenceGlyph_1\" speciesReference=\"speciesReference_1\" speciesGlyph=\"speciesGlyph_1\" role=\"modifier\">\n"
      "  <curve>\n"
      "    <listOfCurveSegments>\n"
      "      <curveSegment xsi:type=\"LineSegment\">\n" 
      "        <start x=\"10\" y=\"10\"/>\n" 
      "        <end x=\"20\" y=\"10\"/>\n" 
      "      </curveSegment>\n"
      "    </listOfCurveSegments>\n"
      "  </curve>\n"
      "</speciesReferenceGlyph>\n"
      "</annotation>"
    ;
    

    XMLInputStream stream(s,false);
    XMLNode node(stream);

    
    SpeciesReferenceGlyph srg=SpeciesReferenceGlyph(LNLV2);
    srg.setId("speciesReferenceGlyph_1");
    srg.setSpeciesGlyphId("speciesGlyph_1");
    srg.setSpeciesReferenceId("speciesReference_1");
    srg.setRole(SPECIES_ROLE_MODIFIER);
    LineSegment* ls=srg.createLineSegment();
    ls->setStart(10.0,10.0);
    ls->setEnd(20.0,10.0);

    fail_unless( node.getChild(0).equals(srg.toXML()) );   


}
END_TEST

START_TEST (test_LayoutFormatter_SpeciesReferenceGlyph_BoundingBox)
{
    char* s=
      "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
      "<speciesReferenceGlyph id=\"speciesReferenceGlyph_1\" speciesReference=\"speciesReference_1\" speciesGlyph=\"speciesGlyph_1\" role=\"modifier\">\n"
      "  <boundingBox>\n"
      "    <position x=\"10.3\" y=\"20\"/>\n"
      "    <dimensions width=\"200.5\" height=\"400.5\"/>\n" 
      "  </boundingBox>\n"  
      "</speciesReferenceGlyph>\n"
    ;
    

    XMLInputStream stream(s,false);
    XMLNode node(stream);

    
    SpeciesReferenceGlyph srg=SpeciesReferenceGlyph(LNLV2);
    srg.setId("speciesReferenceGlyph_1");
    srg.setSpeciesGlyphId("speciesGlyph_1");
    srg.setSpeciesReferenceId("speciesReference_1");
    srg.setRole(SPECIES_ROLE_MODIFIER);
    Dimensions dim=Dimensions(LNLV2,200.5,400.5);
    Point pos=Point(LNLV2,10.3,20.0);
    BoundingBox box=BoundingBox(LNLV2,"",&pos,&dim);
    srg.setBoundingBox(&box);


    fail_unless( node.equals(srg.toXML()) );   

}
END_TEST

START_TEST (test_LayoutFormatter_SpeciesReferenceGlyph_notes)
{
    char* s=
      "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
      "<speciesReferenceGlyph id=\"speciesReferenceGlyph_1\" role=\"modifier\">\n"
      "  <notes>\n"
      "    <body xmlns=\"http://www.w3.org/1999/xhtml\">Test note.</body>\n"
      "</notes>\n"
      "  <boundingBox>\n"
      "    <position x=\"10.3\" y=\"20\"/>\n"
      "    <dimensions width=\"200.5\" height=\"400.5\"/>\n" 
      "  </boundingBox>\n"  
      "</speciesReferenceGlyph>\n"
    ;
    

    XMLInputStream stream(s,false);
    XMLNode node(stream);

    
    SpeciesReferenceGlyph srg=SpeciesReferenceGlyph(LNLV2);
    XMLInputStream stream2("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<body xmlns=\"http://www.w3.org/1999/xhtml\">Test note.</body>",false);
    XMLNode notes(stream2);
    srg.appendNotes(&notes);

    srg.setId("speciesReferenceGlyph_1");
    srg.setRole(SPECIES_ROLE_MODIFIER);
    Dimensions dim=Dimensions(LNLV2,200.5,400.5);
    Point pos=Point(LNLV2,10.3,20.0);
    BoundingBox box=BoundingBox(LNLV2,"",&pos,&dim);
    srg.setBoundingBox(&box);

    fail_unless( node.equals(srg.toXML()) );   

}
END_TEST

START_TEST (test_LayoutFormatter_SpeciesReferenceGlyph_annotation)
{
    const char* a =
      "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
      "<annotation>\n"
      "    <this-is-a-test/>\n"
      "  </annotation>";

    char* s=
      "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
      "<speciesReferenceGlyph id=\"speciesReferenceGlyph_1\" role=\"modifier\">\n"
      "  <annotation>\n"
      "    <this-is-a-test/>\n"
      "  </annotation>\n"
      "  <boundingBox>\n"
      "    <position x=\"10.3\" y=\"20\"/>\n"
      "    <dimensions width=\"200.5\" height=\"400.5\"/>\n" 
      "  </boundingBox>\n"  
      "</speciesReferenceGlyph>\n"
    ;
    

    XMLInputStream stream(s,false);
    XMLNode node(stream);

    
    SpeciesReferenceGlyph srg=SpeciesReferenceGlyph(LNLV2);
    srg.setId("speciesReferenceGlyph_1");
    srg.setRole(SPECIES_ROLE_MODIFIER);
    XMLInputStream stream2(a,false);
    XMLNode* annotation=new XMLNode(stream2);
    srg.appendAnnotation(annotation);

    Dimensions dim=Dimensions(LNLV2,200.5,400.5);
    Point pos=Point(LNLV2,10.3,20.0);
    BoundingBox box=BoundingBox(LNLV2,"",&pos,&dim);
    srg.setBoundingBox(&box);

    fail_unless( node.equals(srg.toXML()) );   

}
END_TEST

START_TEST (test_LayoutFormatter_SpeciesReferenceGlyph_skipOptional)
{
    char* s=
      "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
      "<speciesReferenceGlyph id=\"speciesReferenceGlyph_1\">\n"
      "  <boundingBox>\n"
      "    <position x=\"10.3\" y=\"20\"/>\n"
      "    <dimensions width=\"200.5\" height=\"400.5\"/>\n" 
      "  </boundingBox>\n"  
      "</speciesReferenceGlyph>\n"
    ;
    

    XMLInputStream stream(s,false);
    XMLNode node(stream);

    
    SpeciesReferenceGlyph srg=SpeciesReferenceGlyph(LNLV2);
    srg.setId("speciesReferenceGlyph_1");
    Dimensions dim=Dimensions(LNLV2,200.5,400.5);
    Point pos=Point(LNLV2,10.3,20.0);
    BoundingBox box=BoundingBox(LNLV2,"",&pos,&dim);
    srg.setBoundingBox(&box);

    fail_unless( node.equals(srg.toXML()) );   

}
END_TEST

START_TEST (test_LayoutFormatter_TextGlyph_text)
{
    char* s=
      "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
      "<textGlyph id=\"textGlyph_1\" graphicalObject=\"speciesGlyph_1\" text=\"test text\">\n"
      "  <boundingBox>\n"
      "    <position x=\"10.3\" y=\"20\"/>\n"
      "    <dimensions width=\"200.5\" height=\"400.5\"/>\n" 
      "  </boundingBox>\n"  
      "</textGlyph>\n"
    ;
    

    XMLInputStream stream(s,false);
    XMLNode node(stream);

    
    TextGlyph tg=TextGlyph(LNLV2);
    tg.setId("textGlyph_1");
    tg.setGraphicalObjectId("speciesGlyph_1");
    tg.setText("test text");	
    Dimensions dim=Dimensions(LNLV2,200.5,400.5);
    Point pos=Point(LNLV2,10.3,20.0);
    BoundingBox box=BoundingBox(LNLV2,"",&pos,&dim);
    tg.setBoundingBox(&box);

    fail_unless( node.equals(tg.toXML()) );   

}
END_TEST

START_TEST (test_LayoutFormatter_TextGlyph_originOfText)
{
    char* s=
      "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
      "<textGlyph id=\"textGlyph_1\" graphicalObject=\"speciesGlyph_1\" originOfText=\"reactionGlyph_1\">\n"
      "  <boundingBox>\n"
      "    <position x=\"10.3\" y=\"20\"/>\n"
      "    <dimensions width=\"200.5\" height=\"400.5\"/>\n" 
      "  </boundingBox>\n"  
      "</textGlyph>\n"
    ;
    

    XMLInputStream stream(s,false);
    XMLNode node(stream);

    
    TextGlyph tg=TextGlyph(LNLV2);
    tg.setId("textGlyph_1");
    tg.setOriginOfTextId("reactionGlyph_1");
    tg.setGraphicalObjectId("speciesGlyph_1");
    Dimensions dim=Dimensions(LNLV2,200.5,400.5);
    Point pos=Point(LNLV2,10.3,20.0);
    BoundingBox box=BoundingBox(LNLV2,"",&pos,&dim);
    tg.setBoundingBox(&box);


    fail_unless( node.equals(tg.toXML()) );   

}
END_TEST

START_TEST (test_LayoutFormatter_TextGlyph_notes)
{
    char* s=
      "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
      "<textGlyph id=\"textGlyph_1\" graphicalObject=\"speciesGlyph_1\" originOfText=\"reactionGlyph_1\">\n"
      "  <notes>\n"
      "    <body xmlns=\"http://www.w3.org/1999/xhtml\">Test note.</body>\n"
      "</notes>\n"
      "  <boundingBox>\n"
      "    <position x=\"10.3\" y=\"20\"/>\n"
      "    <dimensions width=\"200.5\" height=\"400.5\"/>\n" 
      "  </boundingBox>\n"  
      "</textGlyph>\n"
    ;
    

    XMLInputStream stream(s,false);
    XMLNode node(stream);

    
    TextGlyph tg=TextGlyph(LNLV2);
    tg.setId("textGlyph_1");
    XMLInputStream stream2("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<body xmlns=\"http://www.w3.org/1999/xhtml\">Test note.</body>",false);
    XMLNode notes(stream2);
    tg.appendNotes(&notes);

    tg.setOriginOfTextId("reactionGlyph_1");
    tg.setGraphicalObjectId("speciesGlyph_1");
    Dimensions dim=Dimensions(LNLV2,200.5,400.5);
    Point pos=Point(LNLV2,10.3,20.0);
    BoundingBox box=BoundingBox(LNLV2,"",&pos,&dim);
    tg.setBoundingBox(&box);


    fail_unless( node.equals(tg.toXML()) );   

}
END_TEST

START_TEST (test_LayoutFormatter_TextGlyph_annotation)
{
    const char* a =
      "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
      "<annotation>\n"
      "    <this-is-a-test/>\n"
      "  </annotation>";

    char* s=
      "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
      "<textGlyph id=\"textGlyph_1\" graphicalObject=\"speciesGlyph_1\" originOfText=\"reactionGlyph_1\">\n"
      "  <annotation>\n"
      "    <this-is-a-test/>\n"
      "  </annotation>\n"
      "  <boundingBox>\n"
      "    <position x=\"10.3\" y=\"20\"/>\n"
      "    <dimensions width=\"200.5\" height=\"400.5\"/>\n" 
      "  </boundingBox>\n"  
      "</textGlyph>\n"
    ;
    

    XMLInputStream stream(s,false);
    XMLNode node(stream);

    
    TextGlyph tg=TextGlyph(LNLV2);
    tg.setId("textGlyph_1");
    tg.setOriginOfTextId("reactionGlyph_1");
    tg.setGraphicalObjectId("speciesGlyph_1");
    XMLInputStream stream2(a,false);
    XMLNode* annotation=new XMLNode(stream2);
    tg.appendAnnotation(annotation);

    Dimensions dim=Dimensions(LNLV2,200.5,400.5);
    Point pos=Point(LNLV2,10.3,20.0);
    BoundingBox box=BoundingBox(LNLV2,"",&pos,&dim);
    tg.setBoundingBox(&box);


    fail_unless( node.equals(tg.toXML()) );   

}
END_TEST

START_TEST (test_LayoutFormatter_TextGlyph_skipOptional)
{
    char* s=
      "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
      "<textGlyph id=\"textGlyph_1\">\n"
      "  <boundingBox>\n"
      "    <position x=\"10.3\" y=\"20\"/>\n"
      "    <dimensions width=\"200.5\" height=\"400.5\"/>\n" 
      "  </boundingBox>\n"  
      "</textGlyph>\n"
    ;
    

    XMLInputStream stream(s,false);
    XMLNode node(stream);

    
    TextGlyph tg=TextGlyph(LNLV2);
    tg.setId("textGlyph_1");
    Dimensions dim=Dimensions(LNLV2,200.5,400.5);
    Point pos=Point(LNLV2,10.3,20.0);
    BoundingBox box=BoundingBox(LNLV2,"",&pos,&dim);
    tg.setBoundingBox(&box);


    fail_unless( node.equals(tg.toXML()) );   

}
END_TEST

START_TEST (test_LayoutFormatter_GraphicalObject)
{
    char* s=
      "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
      "<graphicalObject id=\"graphicalObject_1\">\n"
      "  <boundingBox>\n"
      "    <position x=\"10.3\" y=\"20\"/>\n"
      "    <dimensions width=\"200.5\" height=\"400.5\"/>\n" 
      "  </boundingBox>\n"  
      "</graphicalObject>\n"
    ;
    

    XMLInputStream stream(s,false);
    XMLNode node(stream);

    
    GraphicalObject go=GraphicalObject(LNLV2);
    go.setId("graphicalObject_1");
    Dimensions dim=Dimensions(LNLV2,200.5,400.5);
    Point pos=Point(LNLV2,10.3,20.0);
    BoundingBox box=BoundingBox(LNLV2,"",&pos,&dim);
    go.setBoundingBox(&box);


    fail_unless( node.equals(go.toXML()) );   

}
END_TEST

START_TEST (test_LayoutFormatter_GraphicalObject_notes)
{
    char* s=
      "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
      "<graphicalObject id=\"graphicalObject_1\">\n"
      "  <notes>\n"
      "    <body xmlns=\"http://www.w3.org/1999/xhtml\">Test note.</body>\n"
      "</notes>\n"
      "  <boundingBox>\n"
      "    <position x=\"10.3\" y=\"20\"/>\n"
      "    <dimensions width=\"200.5\" height=\"400.5\"/>\n" 
      "  </boundingBox>\n"  
      "</graphicalObject>\n"
    ;
    

    XMLInputStream stream(s,false);
    XMLNode node(stream);

    
    GraphicalObject go=GraphicalObject(LNLV2);
    XMLInputStream stream2("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<body xmlns=\"http://www.w3.org/1999/xhtml\">Test note.</body>",false);
    XMLNode notes(stream2);
    go.appendNotes(&notes);

    go.setId("graphicalObject_1");
    Dimensions dim=Dimensions(LNLV2,200.5,400.5);
    Point pos=Point(LNLV2,10.3,20.0);
    BoundingBox box=BoundingBox(LNLV2,"",&pos,&dim);
    go.setBoundingBox(&box);


    fail_unless( node.equals(go.toXML()) );   

}
END_TEST

START_TEST (test_LayoutFormatter_GraphicalObject_annotation)
{
    const char* a =
      "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
      "<annotation>\n"
      "    <this-is-a-test/>\n"
      "  </annotation>";

    char* s=
      "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
      "<graphicalObject id=\"graphicalObject_1\">\n"
      "  <annotation>\n"
      "    <this-is-a-test/>\n"
      "  </annotation>\n"
      "  <boundingBox>\n"
      "    <position x=\"10.3\" y=\"20\"/>\n"
      "    <dimensions width=\"200.5\" height=\"400.5\"/>\n" 
      "  </boundingBox>\n"  
      "</graphicalObject>\n"
    ;
    

    XMLInputStream stream(s,false);
    XMLNode node(stream);

    
    GraphicalObject go=GraphicalObject(LNLV2);
    XMLInputStream stream2(a,false);
    XMLNode* annotation=new XMLNode(stream2);
    go.appendAnnotation(annotation);

    go.setId("graphicalObject_1");
    Dimensions dim=Dimensions(LNLV2,200.5,400.5);
    Point pos=Point(LNLV2,10.3,20.0);
    BoundingBox box=BoundingBox(LNLV2,"",&pos,&dim);
    go.setBoundingBox(&box);

    fail_unless( node.equals(go.toXML()) );   


}
END_TEST

START_TEST (test_LayoutFormatter_Curve)
{
    char* s=
      "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
      "<annotation xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\">"
      "<curve>\n"
      "  <listOfCurveSegments>\n"
      "    <curveSegment xsi:type=\"LineSegment\">\n" 
      "      <start x=\"10\" y=\"10\"/>\n" 
      "      <end x=\"20\" y=\"10\"/>\n" 
      "    </curveSegment>\n"
      "  </listOfCurveSegments>\n"
      "</curve>\n"
      "</annotation>"
    ;

    XMLInputStream stream(s,false);
    XMLNode node(stream);


    Curve c=Curve(LNLV2);
    LineSegment* ls=c.createLineSegment();
    ls->setStart(10.0,10.0);
    ls->setEnd(20.0,10.0);
    

    fail_unless( node.getChild(0).equals(c.toXML()) );   
    
}
END_TEST

START_TEST (test_LayoutFormatter_Curve_notes)
{
    char* s=
      "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
      "<annotation xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\">"
      "<curve>\n"
      "  <notes>\n"
      "    <body xmlns=\"http://www.w3.org/1999/xhtml\">Test note.</body>\n"
      "</notes>\n"
      "  <listOfCurveSegments>\n"
      "    <curveSegment xsi:type=\"LineSegment\">\n" 
      "      <start x=\"10\" y=\"10\"/>\n" 
      "      <end x=\"20\" y=\"10\"/>\n" 
      "    </curveSegment>\n"
      "  </listOfCurveSegments>\n"
      "</curve>\n"
      "</annotation>"
    ;

    XMLInputStream stream(s,false);
    XMLNode node(stream);


    Curve c=Curve(LNLV2);
    XMLInputStream stream2("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<body xmlns=\"http://www.w3.org/1999/xhtml\">Test note.</body>",false);
    XMLNode notes(stream2);
    c.appendNotes(&notes);

    LineSegment* ls=c.createLineSegment();
    ls->setStart(10.0,10.0);
    ls->setEnd(20.0,10.0);
    

    fail_unless( node.getChild(0).equals(c.toXML()) );   
    
 }
END_TEST

START_TEST (test_LayoutFormatter_Curve_annotation)
{
    const char* a =
      "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
      "<annotation>\n"
      "    <this-is-a-test/>\n"
      "  </annotation>";

    char* s=
      "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
      "<annotation xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\">"
      "<curve>\n"
      "  <annotation>\n"
      "    <this-is-a-test/>\n"
      "  </annotation>\n"
      "  <listOfCurveSegments>\n"
      "    <curveSegment xsi:type=\"LineSegment\">\n" 
      "      <start x=\"10\" y=\"10\"/>\n" 
      "      <end x=\"20\" y=\"10\"/>\n" 
      "    </curveSegment>\n"
      "  </listOfCurveSegments>\n"
      "</curve>\n"
      "</annotation>"
    ;

    XMLInputStream stream(s,false);
    XMLNode node(stream);


    Curve c=Curve(LNLV2);
    XMLInputStream stream2(a,false);
    XMLNode* annotation=new XMLNode(stream2);
    c.appendAnnotation(annotation);

    LineSegment* ls=c.createLineSegment();
    ls->setStart(10.0,10.0);
    ls->setEnd(20.0,10.0);
 
    fail_unless( node.getChild(0).equals(c.toXML()) );   
   
 }
END_TEST

START_TEST (test_LayoutFormatter_Curve_skipOptional)
{
    char* s=
      "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
      "<curve>\n"
      "</curve>\n"
    ;


    XMLInputStream stream(s,false);
    XMLNode node(stream);

    Curve c=Curve(LNLV2);

    fail_unless( node.equals(c.toXML()) );   
    
 }
END_TEST

START_TEST (test_LayoutFormatter_LineSegment)
{
    char* s=
      "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
      "<annotation xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\">"
      "<curveSegment xsi:type=\"LineSegment\">\n" 
      "  <start x=\"10\" y=\"10\"/>\n" 
      "  <end x=\"20\" y=\"10\"/>\n" 
      "</curveSegment>\n"
      "</annotation>"
    ;

    XMLInputStream stream(s,false);
    XMLNode node(stream);


    LineSegment ls=LineSegment(LNLV2);
    ls.setStart(10.0,10.0);
    ls.setEnd(20.0,10.0);

    fail_unless( node.getChild(0).equals(ls.toXML()) );   
    
}
END_TEST

START_TEST (test_LayoutFormatter_LineSegment_notes)
{
    char* s=
      "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
      "<annotation xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\">"
      "<curveSegment xsi:type=\"LineSegment\">\n" 
      "  <notes>\n"
      "    <body xmlns=\"http://www.w3.org/1999/xhtml\">Test note.</body>\n"
      "</notes>\n"
      "  <start x=\"10\" y=\"10\"/>\n" 
      "  <end x=\"20\" y=\"10\"/>\n" 
      "</curveSegment>\n"
      "</annotation>"
      ;


    XMLInputStream stream(s,false);
    XMLNode node(stream);

    LineSegment ls=LineSegment(LNLV2);
    ls.setStart(10.0,10.0);
    ls.setEnd(20.0,10.0);
    XMLInputStream stream2("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<body xmlns=\"http://www.w3.org/1999/xhtml\">Test note.</body>",false);
    XMLNode notes(stream2);
    ls.appendNotes(&notes);


    fail_unless( node.getChild(0).equals(ls.toXML()) );   
    
}
END_TEST

START_TEST (test_LayoutFormatter_LineSegment_annotation)
{
    const char* a =
      "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
      "<annotation>\n"
      "    <this-is-a-test/>\n"
      "  </annotation>";

    char* s=
      "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
      "<annotation xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\">"
      "<curveSegment xsi:type=\"LineSegment\">\n" 
      "  <annotation>\n"
      "    <this-is-a-test/>\n"
      "  </annotation>\n"
      "  <start x=\"10\" y=\"10\"/>\n" 
      "  <end x=\"20\" y=\"10\"/>\n" 
      "</curveSegment>\n"
      "</annotation>"
    ;


    XMLInputStream stream(s,false);
    XMLNode node(stream);

    LineSegment ls=LineSegment(LNLV2);
    ls.setStart(10.0,10.0);
    ls.setEnd(20.0,10.0);
    XMLInputStream stream2(a,false);
    XMLNode* annotation=new XMLNode(stream2);
    ls.appendAnnotation(annotation);


    fail_unless( node.getChild(0).equals(ls.toXML()) );   
    
}
END_TEST

START_TEST (test_LayoutFormatter_CubicBezier)
{
    char* s=
      "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
      "<annotation xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\">"
      "<curveSegment xsi:type=\"CubicBezier\">\n" 
      "  <start x=\"10\" y=\"10\"/>\n" 
      "  <end x=\"20\" y=\"10\"/>\n" 
      "  <basePoint1 x=\"15\" y=\"5\"/>\n" 
      "  <basePoint2 x=\"15\" y=\"15\"/>\n" 
      "</curveSegment>\n"
      "</annotation>"
     ;


    XMLInputStream stream(s,false);
    XMLNode node(stream);

    CubicBezier cb=CubicBezier(LNLV2);
    cb.setStart(10.0,10.0);
    cb.setEnd(20.0,10.0);
    cb.setBasePoint1(15.0,5.0);
    cb.setBasePoint2(15.0,15.0);

    fail_unless( node.getChild(0).equals(cb.toXML()) );   
    
}
END_TEST

START_TEST (test_LayoutFormatter_CubicBezier_notes)
{
    char* s=
      "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
      "<annotation xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\">"
      "<curveSegment xsi:type=\"CubicBezier\">\n" 
      "  <notes>\n"
      "    <body xmlns=\"http://www.w3.org/1999/xhtml\">Test note.</body>\n"
      "</notes>\n"
      "  <start x=\"10\" y=\"10\"/>\n" 
      "  <end x=\"20\" y=\"10\"/>\n" 
      "  <basePoint1 x=\"15\" y=\"5\"/>\n" 
      "  <basePoint2 x=\"15\" y=\"15\"/>\n" 
      "</curveSegment>\n"
      "</annotation>"
    ;


    XMLInputStream stream(s,false);
    XMLNode node(stream);

    CubicBezier cb=CubicBezier(LNLV2);
    cb.setStart(10.0,10.0);
    cb.setEnd(20.0,10.0);
    cb.setBasePoint1(15.0,5.0);
    cb.setBasePoint2(15.0,15.0);
    XMLInputStream stream2("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<body xmlns=\"http://www.w3.org/1999/xhtml\">Test note.</body>",false);
    XMLNode notes(stream2);
    cb.appendNotes(&notes);


    fail_unless( node.getChild(0).equals(cb.toXML()) );   
    
}
END_TEST

START_TEST (test_LayoutFormatter_CubicBezier_annotation)
{
    const char* a =
      "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
      "<annotation>\n"
      "    <this-is-a-test/>\n"
      "  </annotation>";

    char* s=
      "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
      "<annotation xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\">"
      "<curveSegment xsi:type=\"CubicBezier\">\n" 
      "  <annotation>\n"
      "    <this-is-a-test/>\n"
      "  </annotation>\n"
      "  <start x=\"10\" y=\"10\"/>\n" 
      "  <end x=\"20\" y=\"10\"/>\n" 
      "  <basePoint1 x=\"15\" y=\"5\"/>\n" 
      "  <basePoint2 x=\"15\" y=\"15\"/>\n" 
      "</curveSegment>\n"
      "</annotation>"
    ;


    XMLInputStream stream(s,false);
    XMLNode node(stream);

    CubicBezier cb=CubicBezier(LNLV2);
    cb.setStart(10.0,10.0);
    cb.setEnd(20.0,10.0);
    cb.setBasePoint1(15.0,5.0);
    cb.setBasePoint2(15.0,15.0);
    XMLInputStream stream2(a,false);
    XMLNode* annotation=new XMLNode(stream2);
    cb.appendAnnotation(annotation);


    fail_unless( node.getChild(0).equals(cb.toXML()) );   
    
}
END_TEST

START_TEST (test_LayoutFormatter_Point)
{
    char* s=
      "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
      "<point x=\"200.5\" y=\"400.5\" z=\"455.2\"/>\n" 
    ;


    XMLInputStream stream(s,false);
    XMLNode node(stream);

    Point p=Point(LNLV2,200.5,400.5,455.2);

    fail_unless( node.equals(p.toXML("point")) );   

}
END_TEST

START_TEST (test_LayoutFormatter_Point_notes)
{
    char* s=
      "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
      "<point x=\"200.5\" y=\"400.5\" z=\"455.2\">\n" 
      "  <notes>\n"
      "    <body xmlns=\"http://www.w3.org/1999/xhtml\">Test note.</body>\n"
      "</notes>\n"
      "</point>\n"
    ;


    XMLInputStream stream(s,false);
    XMLNode node(stream);

    Point p=Point(LNLV2,200.5,400.5,455.2);
    XMLInputStream stream2("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<body xmlns=\"http://www.w3.org/1999/xhtml\">Test note.</body>",false);
    XMLNode notes(stream2);
    p.appendNotes(&notes);


    fail_unless( node.equals(p.toXML("point")) );   

}
END_TEST

START_TEST (test_LayoutFormatter_Point_annotation)
{
    const char* a =
      "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
      "<annotation>\n"
      "    <this-is-a-test/>\n"
      "  </annotation>";

    char* s=
      "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
      "<point x=\"200.5\" y=\"400.5\" z=\"455.2\">\n" 
      "  <annotation>\n"
      "    <this-is-a-test/>\n"
      "  </annotation>\n"
      "</point>\n"
    ;


    XMLInputStream stream(s,false);
    XMLNode node(stream);

    Point p=Point(LNLV2,200.5,400.5,455.2);
    XMLInputStream stream2(a,false);
    XMLNode* annotation=new XMLNode(stream2);
    p.appendAnnotation(annotation);


    fail_unless( node.equals(p.toXML("point")) );   

}
END_TEST

START_TEST (test_LayoutFormatter_Point_skipOptional)
{
    char* s=
      "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
      "<point x=\"200.5\" y=\"400.5\"/>\n" 
    ;


    XMLInputStream stream(s,false);
    XMLNode node(stream);

    Point p=Point(LNLV2,200.5,400.5);

    fail_unless( node.equals(p.toXML("point")) );   

}
END_TEST

START_TEST (test_LayoutFormatter_Dimensions)
{
    char* s=
      "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
      "<dimensions width=\"200.5\" height=\"400.5\" depth=\"455.2\"/>\n" 
    ;


    XMLInputStream stream(s,false);
    XMLNode node(stream);

    Dimensions dim=Dimensions(LNLV2,200.5,400.5,455.2);

    fail_unless( node.equals(dim.toXML()) );   

}
END_TEST

START_TEST (test_LayoutFormatter_Dimensions_notes)
{
    char* s=
      "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
      "<dimensions width=\"200.5\" height=\"400.5\" depth=\"455.2\">\n" 
      "  <notes>\n"
      "    <body xmlns=\"http://www.w3.org/1999/xhtml\">Test note.</body>\n"
      "</notes>\n"
      "</dimensions>\n"
    ;


    XMLInputStream stream(s,false);
    XMLNode node(stream);

    Dimensions dim=Dimensions(LNLV2,200.5,400.5,455.2);
    XMLInputStream stream2("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<body xmlns=\"http://www.w3.org/1999/xhtml\">Test note.</body>",false);
    XMLNode notes(stream2);
    dim.appendNotes(&notes);


    fail_unless( node.equals(dim.toXML()) );   

}
END_TEST

START_TEST (test_LayoutFormatter_Dimensions_annotation)
{
    const char* a =
      "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
      "<annotation>\n"
      "    <this-is-a-test/>\n"
      "  </annotation>";

    char* s=
      "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
      "<dimensions width=\"200.5\" height=\"400.5\" depth=\"455.2\">\n" 
      "  <annotation>\n"
      "    <this-is-a-test/>\n"
      "  </annotation>\n"
      "</dimensions>\n"
    ;


    XMLInputStream stream(s,false);
    XMLNode node(stream);

    Dimensions dim=Dimensions(LNLV2,200.5,400.5,455.2);
    XMLInputStream stream2(a,false);
    XMLNode* annotation=new XMLNode(stream2);
    dim.appendAnnotation(annotation);


    fail_unless( node.equals(dim.toXML()) );   

}
END_TEST

START_TEST (test_LayoutFormatter_Dimensions_skipOptional)
{
    char* s=
      "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
      "<dimensions width=\"200.5\" height=\"400.5\"/>\n" 
    ;


    XMLInputStream stream(s,false);
    XMLNode node(stream);

    Dimensions dim=Dimensions(LNLV2,200.5,400.5);

    fail_unless( node.equals(dim.toXML()) );   

}
END_TEST


START_TEST (test_LayoutFormatter_BoundingBox)
{
    char* s=
      "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
      "<boundingBox id=\"boundingBox_1\">\n"
      "  <position x=\"10.3\" y=\"20\"/>\n"
      "  <dimensions width=\"200.5\" height=\"400.5\"/>\n" 
      "</boundingBox>\n"  
    ;


    XMLInputStream stream(s,false);
    XMLNode node(stream);

    Dimensions dim=Dimensions(LNLV2,200.5,400.5);
    Point pos=Point(LNLV2,10.3,20.0);
    BoundingBox box=BoundingBox(LNLV2,"boundingBox_1",&pos,&dim);

    fail_unless( node.equals(box.toXML()) );   


}
END_TEST

START_TEST (test_LayoutFormatter_BoundingBox_notes)
{
    char* s=
      "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
      "<boundingBox>\n"
      "  <notes>\n"
      "    <body xmlns=\"http://www.w3.org/1999/xhtml\">Test note.</body>\n"
      "</notes>\n"
      "  <position x=\"10.3\" y=\"20\"/>\n"
      "  <dimensions width=\"200.5\" height=\"400.5\"/>\n" 
      "</boundingBox>\n"  
    ;


    XMLInputStream stream(s,false);
    XMLNode node(stream);

    Dimensions dim=Dimensions(LNLV2,200.5,400.5);
    Point pos=Point(LNLV2,10.3,20.0);
    BoundingBox box=BoundingBox(LNLV2,"",&pos,&dim);
    XMLInputStream stream2("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<body xmlns=\"http://www.w3.org/1999/xhtml\">Test note.</body>",false);
    XMLNode notes(stream2);
    box.appendNotes(&notes);


    fail_unless( node.equals(box.toXML()) );   

}
END_TEST

START_TEST (test_LayoutFormatter_BoundingBox_annotation)
{
    const char* a =
      "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
      "<annotation>\n"
      "    <this-is-a-test/>\n"
      "  </annotation>";

    char* s=
      "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
      "<boundingBox>\n"
      "  <annotation>\n"
      "    <this-is-a-test/>\n"
      "  </annotation>\n"
      "  <position x=\"10.3\" y=\"20\"/>\n"
      "  <dimensions width=\"200.5\" height=\"400.5\"/>\n" 
      "</boundingBox>\n"  
    ;


    XMLInputStream stream(s,false);
    XMLNode node(stream);

    Dimensions dim=Dimensions(LNLV2,200.5,400.5);
    Point pos=Point(LNLV2,10.3,20.0);
    BoundingBox box=BoundingBox(LNLV2,"",&pos,&dim);

    XMLInputStream stream2(a,false);
    XMLNode* annotation=new XMLNode(stream2);
    box.appendAnnotation(annotation);



    fail_unless( node.equals(box.toXML()) );   


}
END_TEST

START_TEST (test_LayoutFormatter_BoundingBox_skipOptional)
{
    char* s=
      "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
      "<boundingBox>\n"
      "  <position x=\"10.3\" y=\"20\"/>\n"
      "  <dimensions width=\"200.5\" height=\"400.5\"/>\n" 
      "</boundingBox>\n"  
    ;


    XMLInputStream stream(s,false);
    XMLNode node(stream);

    Dimensions dim=Dimensions(LNLV2,200.5,400.5);
    Point pos=Point(LNLV2,10.3,20.0);
    BoundingBox box=BoundingBox(LNLV2,"",&pos,&dim);

    fail_unless( node.equals(box.toXML()) );   


}
END_TEST


START_TEST (test_LayoutFormatter_locale)
{
  const char* s =       "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<dimensions width=\"1.2\" height=\"3.4\"/>\n";


  setlocale(LC_NUMERIC, "de_DE");

  Dimensions d(LNLV2,1.2,3.4);

  XMLInputStream stream(s,false);
  XMLNode node(stream);

  fail_unless( node.equals(d.toXML()) );

  setlocale(LC_NUMERIC, "C");
}
END_TEST

Suite *
create_suite_LayoutFormatter (void)
{
  Suite *suite = suite_create("LayoutFormatter");
  TCase *tcase = tcase_create("LayoutFormatter");

  tcase_add_checked_fixture( tcase,
                             LayoutFormatterTest_setup,
                             LayoutFormatterTest_teardown );


  tcase_add_test( tcase, test_LayoutFormatter_Layout                            );
  tcase_add_test( tcase, test_LayoutFormatter_Layout_notes                      );
  tcase_add_test( tcase, test_LayoutFormatter_Layout_annotation                 );
  tcase_add_test( tcase, test_LayoutFormatter_Layout_skipOptional               );
  tcase_add_test( tcase, test_LayoutFormatter_CompartmentGlyph                  );
  tcase_add_test( tcase, test_LayoutFormatter_CompartmentGlyph_notes            );
  tcase_add_test( tcase, test_LayoutFormatter_CompartmentGlyph_annotation       );
  tcase_add_test( tcase, test_LayoutFormatter_CompartmentGlyph_skipOptional     );
  tcase_add_test( tcase, test_LayoutFormatter_SpeciesGlyph                      );
  tcase_add_test( tcase, test_LayoutFormatter_SpeciesGlyph_notes                );
  tcase_add_test( tcase, test_LayoutFormatter_SpeciesGlyph_annotation           );
  tcase_add_test( tcase, test_LayoutFormatter_SpeciesGlyph_skipOptional         );
  tcase_add_test( tcase, test_LayoutFormatter_ReactionGlyph_Curve               );
  tcase_add_test( tcase, test_LayoutFormatter_ReactionGlyph_BoundingBox         );
  tcase_add_test( tcase, test_LayoutFormatter_ReactionGlyph_notes               );
  tcase_add_test( tcase, test_LayoutFormatter_ReactionGlyph_annotation          );
  tcase_add_test( tcase, test_LayoutFormatter_ReactionGlyph_skipOptional        );
  tcase_add_test( tcase, test_LayoutFormatter_SpeciesReferenceGlyph_Curve       );
  tcase_add_test( tcase, test_LayoutFormatter_SpeciesReferenceGlyph_BoundingBox );
  tcase_add_test( tcase, test_LayoutFormatter_SpeciesReferenceGlyph_notes       );
  tcase_add_test( tcase, test_LayoutFormatter_SpeciesReferenceGlyph_annotation  );
  tcase_add_test( tcase, test_LayoutFormatter_SpeciesReferenceGlyph_skipOptional);
  tcase_add_test( tcase, test_LayoutFormatter_TextGlyph_text                    );
  tcase_add_test( tcase, test_LayoutFormatter_TextGlyph_notes                   );
  tcase_add_test( tcase, test_LayoutFormatter_TextGlyph_annotation              );
  tcase_add_test( tcase, test_LayoutFormatter_TextGlyph_originOfText            );
  tcase_add_test( tcase, test_LayoutFormatter_TextGlyph_skipOptional            );
  tcase_add_test( tcase, test_LayoutFormatter_GraphicalObject                   );
  tcase_add_test( tcase, test_LayoutFormatter_GraphicalObject_notes             );
  tcase_add_test( tcase, test_LayoutFormatter_GraphicalObject_annotation        );
  tcase_add_test( tcase, test_LayoutFormatter_Curve                             );
  tcase_add_test( tcase, test_LayoutFormatter_Curve_notes                       );
  tcase_add_test( tcase, test_LayoutFormatter_Curve_annotation                  );
  tcase_add_test( tcase, test_LayoutFormatter_Curve_skipOptional                );
  tcase_add_test( tcase, test_LayoutFormatter_LineSegment                       );
  tcase_add_test( tcase, test_LayoutFormatter_LineSegment_notes                 );
  tcase_add_test( tcase, test_LayoutFormatter_LineSegment_annotation            );
  tcase_add_test( tcase, test_LayoutFormatter_CubicBezier                       );
  tcase_add_test( tcase, test_LayoutFormatter_CubicBezier_notes                 );
  tcase_add_test( tcase, test_LayoutFormatter_CubicBezier_annotation            );
  tcase_add_test( tcase, test_LayoutFormatter_Point                             );
  tcase_add_test( tcase, test_LayoutFormatter_Point_notes                       );
  tcase_add_test( tcase, test_LayoutFormatter_Point_annotation                  );
  tcase_add_test( tcase, test_LayoutFormatter_Point_skipOptional                );
  tcase_add_test( tcase, test_LayoutFormatter_Dimensions                        );
  tcase_add_test( tcase, test_LayoutFormatter_Dimensions_notes                  );
  tcase_add_test( tcase, test_LayoutFormatter_Dimensions_annotation             );
  tcase_add_test( tcase, test_LayoutFormatter_Dimensions_skipOptional           );
  tcase_add_test( tcase, test_LayoutFormatter_BoundingBox                       );
  tcase_add_test( tcase, test_LayoutFormatter_BoundingBox_notes                 );
  tcase_add_test( tcase, test_LayoutFormatter_BoundingBox_annotation            );
  tcase_add_test( tcase, test_LayoutFormatter_BoundingBox_skipOptional          );
  tcase_add_test( tcase, test_LayoutFormatter_locale                            );
  suite_add_tcase(suite, tcase);

  return suite;
}



END_C_DECLS
