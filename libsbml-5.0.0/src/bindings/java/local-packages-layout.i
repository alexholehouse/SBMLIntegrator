#ifdef USE_LAYOUT

/**
 * Adds DownCastBase(long cPtr, boolean owner) method for package extension
 */
%typemap(javacode) LayoutExtension
%{
	public SBasePlugin DowncastSBasePlugin(long cPtr, boolean owner)
	{
		if (cPtr == 0) return null;
		
		SBasePlugin sbp = new SBasePlugin(cPtr,false);
		SBase sb = sbp.getParentSBMLObject();
		
		if (sb == null) 
		{
			return new SBasePlugin(cPtr,owner);
		}
		
		switch( sb.getTypeCode() )
		{
			case libsbmlConstants.SBML_MODEL:
				return new LayoutModelPlugin(cPtr,owner);
			case libsbmlConstants.SBML_SPECIES_REFERENCE:
			case libsbmlConstants.SBML_MODIFIER_SPECIES_REFERENCE:
				return new LayoutSpeciesReferencePlugin(cPtr,owner);
			default: 
				return new SBasePlugin(cPtr,owner);
		}
	}
	
	/**
	 * SBMLExtension derived classes must override this method
	 *
	 * @return the most specific Java object possible for the given SBase
	 */
	public SBase DowncastSBase(long cPtr, boolean owner)
	{
		if (cPtr == 0) return null;
		
		SBase sb = new SBase(cPtr,false);
		
		switch( sb.getTypeCode() )
		{
			case libsbmlConstants.SBML_LIST_OF:
				String name = sb.getElementName();
				if(name.equals("listOfCompartmentGlyphs")){
					return new ListOfCompartmentGlyphs(cPtr, owner);
				}
				else if(name.equals("listOfAdditionalGraphicalObjects")){
					return new ListOfGraphicalObjects(cPtr, owner);
				}
				else if(name.equals("listOfLayouts")){
					return new ListOfLayouts(cPtr, owner);
				}
				else if(name.equals("listOfCurveSegments")){
					return new ListOfLineSegments(cPtr, owner);
				}
				else if(name.equals("listOfSpeciesGlyphs")){
					return new ListOfSpeciesGlyphs(cPtr, owner);
				}
				else if(name.equals("listOfSpeciesReferenceGlyphs")){
					return new ListOfSpeciesReferenceGlyphs(cPtr, owner);
				}
				else if(name.equals("listOfReactionGlyphs")){
					return new ListOfReactionGlyphs(cPtr, owner);
				}
				else if(name.equals("listOfTextGlyphs")){
					return new ListOfTextGlyphs(cPtr, owner);
				}
				return new ListOf(cPtr, owner);
				
			case libsbmlConstants.SBML_LAYOUT_BOUNDINGBOX:
				return new BoundingBox(cPtr, owner);
				
			case libsbmlConstants.SBML_LAYOUT_COMPARTMENTGLYPH:
				return new CompartmentGlyph(cPtr, owner);
				
			case libsbmlConstants.SBML_LAYOUT_CUBICBEZIER:
				return new CubicBezier(cPtr, owner);
				
			case libsbmlConstants.SBML_LAYOUT_CURVE:
				return new Curve(cPtr, owner);
				
			case libsbmlConstants.SBML_LAYOUT_DIMENSIONS:
				return new Dimensions(cPtr, owner);
				
			case libsbmlConstants.SBML_LAYOUT_GRAPHICALOBJECT:
				return new GraphicalObject(cPtr, owner);
				
			case libsbmlConstants.SBML_LAYOUT_LAYOUT:
				return new Layout(cPtr, owner);
				
			case libsbmlConstants.SBML_LAYOUT_LINESEGMENT:
				return new LineSegment(cPtr, owner);
				
			case libsbmlConstants.SBML_LAYOUT_POINT:
				return new Point(cPtr, owner);
				
			case libsbmlConstants.SBML_LAYOUT_REACTIONGLYPH:
				return new ReactionGlyph(cPtr, owner);
				
			case libsbmlConstants.SBML_LAYOUT_SPECIESGLYPH:
				return new SpeciesGlyph(cPtr, owner);
				
			case libsbmlConstants.SBML_LAYOUT_SPECIESREFERENCEGLYPH:
				return new SpeciesReferenceGlyph(cPtr, owner);
				
			case libsbmlConstants.SBML_LAYOUT_TEXTGLYPH:
				return new TextGlyph(cPtr, owner);
			default:
				return new SBase(cPtr, owner);
		}
	}
	%} 


//
// Convert LineSegment objects into the most specific object possible.
//
%typemap("javaout") LineSegment*
{
	return (LineSegment) libsbml.DowncastSBase($jnicall, $owner);
}

//
// Convert LineSegment objects into the most specific object possible.
//
%typemap("javaout") GraphicalObject*
{
	return (GraphicalObject) libsbml.DowncastSBase($jnicall, $owner);
}


COVARIANT_RTYPE_CLONE(BoundingBox)
COVARIANT_RTYPE_CLONE(CompartmentGlyph)
COVARIANT_RTYPE_CLONE(CubicBezier)
COVARIANT_RTYPE_CLONE(Curve)
COVARIANT_RTYPE_CLONE(Dimensions)
COVARIANT_RTYPE_CLONE(GraphicalObject)
COVARIANT_RTYPE_CLONE(Layout)
COVARIANT_RTYPE_CLONE(LineSegment)
COVARIANT_RTYPE_CLONE(Point)
COVARIANT_RTYPE_CLONE(ReactionGlyph)
COVARIANT_RTYPE_CLONE(SpeciesGlyph)
COVARIANT_RTYPE_CLONE(SpeciesReferenceGlyph)
COVARIANT_RTYPE_CLONE(TextGlyph)
COVARIANT_RTYPE_CLONE(ListOfGraphicalObjects)
COVARIANT_RTYPE_CLONE(ListOfLayouts)
COVARIANT_RTYPE_CLONE(ListOfLineSegments)
COVARIANT_RTYPE_CLONE(ListOfReactionGlyphs)
COVARIANT_RTYPE_CLONE(ListOfSpeciesGlyphs)
COVARIANT_RTYPE_CLONE(ListOfSpeciesReferenceGlyphs)
COVARIANT_RTYPE_CLONE(ListOfTextGlyphs)
COVARIANT_RTYPE_CLONE(ListOfCompartmentGlyphs)

COVARIANT_RTYPE_LISTOF_GET_REMOVE(GraphicalObject)
COVARIANT_RTYPE_LISTOF_GET_REMOVE(Layout)
COVARIANT_RTYPE_LISTOF_GET_REMOVE(LineSegment)
COVARIANT_RTYPE_LISTOF_GET_REMOVE(ReactionGlyph)
COVARIANT_RTYPE_LISTOF_GET_REMOVE(SpeciesGlyph)
COVARIANT_RTYPE_LISTOF_GET_REMOVE(SpeciesReferenceGlyph)
COVARIANT_RTYPE_LISTOF_GET_REMOVE(TextGlyph)
COVARIANT_RTYPE_LISTOF_GET_REMOVE(CompartmentGlyph)

#endif