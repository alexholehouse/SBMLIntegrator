#############################################################################################
#                           SBMLIntegrator - PATHWAY VIWER                                  #
#############################################################################################

~ASH(alex.holehouse@gmail.com) - 27/07/2011 

#############################################################################################
Things we need to add;

+ Reaction local parameter support
+ Testing framework
+ Code coverage (ESPECIALLY for relevance of locate_and_replace_MathML function calls)
+ Redo UI classes
+ Full blown restructuring - maybe recode some regions? Avoid static methods though.
	For more details on good practice here check out Google good practice notes
+ Logic to ensure a value defined in the conf file is not defined in two or more of import/replace/integrate lists
+ Logic to ensure all the elements in modelB are defined SOMEWHERE in the conf file
+ When the user defines a new ID, make sure it's unique through the software 
+ Integration
	+ Suggest that if a unit is not corretly defined it may need to be imported?
	+ FAR more choice in terms of what you can customize on integration - rather than just selecting one of the two options from
	  the integratees (as is in alpha) input your own values, which lookup functions for SID based parameters!

+ More in-depth logfile reporting


#############################################################################################
Necessary assumptions we have for the alpha version;

+ BOTH MODELS ARE THE SAME LEVEL AND VERSION - NOTE this will probably be the case for the BETA too!
  - Look at writing some upgrade level/version software :-)

+ Model attributes (shown below) are the same for both models
	substanceUnits: UnitSIdRef 
	timeUnits: UnitsSIdRef 
	volumeUnits: UnitSIdRef 
	areaUnits: UnitsSIdRef 
	lengthUnits: UnitsSIdRef 
	extentUnits: UnitsSIdRef 
	conversionactor: SIdRef 
  - This is important, as has model wide implications if they're different, requiring model wide conversion and scaling.
    This should probably be something we add, although is a fairly major undertaking. To do after project!

+ Reactions cannot have local parameters - this is critical for the MATLAB integration too, so we should add support to translate local prameters into global ones if need be

+ At this current stage, we're not supporting integration of 
	-Constraints
	-Events
	-Initial assignments
	 
  - The MATLAB support for these is limited	

  - The majority of the functionality associated with the inetgration for these elements has already
    been coded. However, in the interest of getting a fully developed alpha version which operates on our specific
    and immediate goals, complete implementation of these additional is currently paused. Obviously, this will be
    an absolute priority/requirement for a beta launch.


In beta these shortcomings will be rectified.

#############################################################################################
END


