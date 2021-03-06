# -*- perl -*-
# generated by perlify.pl from libsbml/src/annotation/test/TestModelHistory.c
# followed by little human processing to fix syntactic specialties
# perify.pl is unable to handle right now =;) xtof
use Test::More;
BEGIN { plan tests => 152 };

use LibSBML;
use strict;
#########################

test_Date_create();
test_Date_createFromString();
test_Date_setters();
test_Date_getDateAsString();
test_ModelCreator_create();
test_ModelCreator_setters();
test_ModelHistory_create();
test_ModelHistory_addCreator();
test_ModelHistory_setCreatedDate();
test_ModelHistory_setModifiedDate();
test_ModelHistory_addModifiedDate();
# scalar/list context test for functions returning a List*
test_ModelHistory_getListModifiedDates();
test_ModelHistory_getCreators();

#---
sub test_Date_create {
 my $date = new LibSBML::Date(2005, 12, 30, 12, 15, 45, 1, 2, 0);
 ok( defined $date );
 ok( $date->getYear() == 2005 );
 ok( $date->getMonth() == 12 );
 ok( $date->getDay() == 30 );
 ok( $date->getHour() == 12 );
 ok( $date->getMinute() == 15 );
 ok( $date->getSecond() == 45 );
 ok( $date->getSignOffset() == 1 );
 ok( $date->getHoursOffset() == 2 );
 ok( $date->getMinutesOffset() == 0 );
}

#---
sub test_Date_createFromString {
 my $dd = '2012-12-02T14:56:11Z';
 my $date = new LibSBML::Date($dd);
 ok( defined $date );
 ok( $date->getDateAsString() eq '2012-12-02T14:56:11Z' );
 ok( $date->getYear() == 2012 );
 ok( $date->getMonth() == 12 );
 ok( $date->getDay() == 2 );
 ok( $date->getHour() == 14 );
 ok( $date->getMinute() == 56 );
 ok( $date->getSecond() == 11 );
 ok( $date->getSignOffset() == 0 );
 ok( $date->getHoursOffset() == 0 );
 ok( $date->getMinutesOffset() == 0 );
}

#---
sub test_Date_setters {
 my $date = new LibSBML::Date(2005, 12, 30, 12, 15, 45, 1, 2, 0);
 ok( defined $date );
 $date->setYear(2012);
 $date->setMonth(3);
 $date->setDay(28);
 $date->setHour(23);
 $date->setMinute(4);
 $date->setSecond(32);
 $date->setSignOffset(1);
 $date->setHoursOffset(2);
 $date->setMinutesOffset(32);
 ok( $date->getYear() == 2012 );
 ok( $date->getMonth() == 3 );
 ok( $date->getDay() == 28 );
 ok( $date->getHour() == 23 );
 ok( $date->getMinute() == 4 );
 ok( $date->getSecond() == 32 );
 ok( $date->getSignOffset() == 1 );
 ok( $date->getHoursOffset() == 2 );
 ok( $date->getMinutesOffset() == 32 );
 ok( $date->getDateAsString() eq '2012-03-28T23:04:32+02:32' );
}

#---
sub test_Date_getDateAsString {
 my $dd = '2005-02-02T14:56:11Z';
 my $date = new LibSBML::Date($dd);
 ok( defined $date );
 ok( $date->getYear() == 2005 );
 ok( $date->getMonth() == 2 );
 ok( $date->getDay() == 2 );
 ok( $date->getHour() == 14 );
 ok( $date->getMinute() == 56 );
 ok( $date->getSecond() == 11 );
 ok( $date->getSignOffset() == 0 );
 ok( $date->getHoursOffset() == 0 );
 ok( $date->getMinutesOffset() == 0 );
 $date->setYear(2012);
 $date->setMonth(3);
 $date->setDay(28);
 $date->setHour(23);
 $date->setMinute(4);
 $date->setSecond(32);
 $date->setSignOffset(1);
 $date->setHoursOffset(2);
 $date->setMinutesOffset(32);
 ok( $date->getDateAsString() eq '2012-03-28T23:04:32+02:32' );
}

#---
sub test_ModelCreator_create {
 my $mc = new LibSBML::ModelCreator();
 ok( defined $mc );
}

#---
sub test_ModelCreator_setters {
 my $mc = new LibSBML::ModelCreator();
 ok( defined $mc );
 ok( $mc->isSetFamilyName() == 0 );
 ok( $mc->isSetGivenName() == 0 );
 ok( $mc->isSetEmail() == 0 );
 ok( $mc->isSetOrganisation() == 0 );
 $mc->setFamilyName('Keating');
 $mc->setGivenName('Sarah');
 $mc->setEmail('sbml-team@caltech.edu');
 $mc->setOrganisation('UH');
 ok( $mc->getFamilyName() eq 'Keating' );
 ok( $mc->getGivenName() eq 'Sarah' );
 ok( $mc->getEmail() eq 'sbml-team@caltech.edu' );
 ok( $mc->getOrganisation() eq 'UH' );
 ok( $mc->isSetFamilyName() == 1 );
 ok( $mc->isSetGivenName() == 1 );
 ok( $mc->isSetEmail() == 1 );
 ok( $mc->isSetOrganisation() == 1 );
 $mc->unsetFamilyName();
 $mc->unsetGivenName();
 $mc->unsetEmail();
 $mc->unsetOrganisation();
 ok( $mc->getFamilyName() eq '' );
 ok( $mc->getGivenName() eq '' );
 ok( $mc->getEmail() eq '' );
 ok( $mc->getOrganisation() eq '' );
 ok( $mc->isSetFamilyName() == 0 );
 ok( $mc->isSetGivenName() == 0 );
 ok( $mc->isSetEmail() == 0 );
 ok( $mc->isSetOrganisation() == 0 );
 # test alternate spelling functions;
 ok( $mc->isSetOrganization() == 0 );
 $mc->setOrganization('UH');
 ok( $mc->getOrganization() eq 'UH' );
 ok( $mc->isSetOrganization() == 1 );
 $mc->unsetOrganisation();
 ok( $mc->getOrganization() eq '' );
 ok( $mc->isSetOrganization() == 0 );
}

#---
sub test_ModelHistory_create {
 my $history = new LibSBML::ModelHistory();
 ok( defined $history );
 ok( !defined $history->getCreator(0) );
# ok( !defined $history->getListCreators()->get(0) );
 ok( !defined $history->getCreatedDate() );
 ok( !defined $history->getModifiedDate() );
}

#---
sub test_ModelHistory_addCreator {
 my $history = new LibSBML::ModelHistory();
 ok( $history->getNumCreators() == 0 );
 ok( defined $history );
 my $mc = new LibSBML::ModelCreator();
 ok( defined $mc );
 $mc->setFamilyName('Keating');
 $mc->setGivenName('Sarah');
 $mc->setEmail('sbml-team@caltech.edu');
 $mc->setOrganisation('UH');
 $history->addCreator($mc);
 ok( $history->getNumCreators() == 1 );
 my $newMC = $history->getCreator(0);
# my $newMC = $history->getListCreators()->get(0);
 ok( defined $newMC );
 ok( $newMC->getFamilyName() eq 'Keating' );
 ok( $newMC->getGivenName() eq 'Sarah' );
 ok( $newMC->getEmail() eq 'sbml-team@caltech.edu' );
 ok( $newMC->getOrganisation() eq 'UH' );
}

#---
sub test_ModelHistory_setCreatedDate {
 my $history = new LibSBML::ModelHistory();
 ok( defined $history );
 ok( $history->isSetCreatedDate() == 0 );
 my $date = new LibSBML::Date(2005, 12, 30, 12, 15, 45, 1, 2, 0);
 $history->setCreatedDate($date);
 ok( $history->isSetCreatedDate() == 1 );
 my $newdate = $history->getCreatedDate();
 ok( $newdate->getYear() == 2005 );
 ok( $newdate->getMonth() == 12 );
 ok( $newdate->getDay() == 30 );
 ok( $newdate->getHour() == 12 );
 ok( $newdate->getMinute() == 15 );
 ok( $newdate->getSecond() == 45 );
 ok( $newdate->getSignOffset() == 1 );
 ok( $newdate->getHoursOffset() == 2 );
 ok( $newdate->getMinutesOffset() == 0 );
}

#---
sub test_ModelHistory_setModifiedDate {
 my $history = new LibSBML::ModelHistory();
 ok( defined $history );
 ok( $history->isSetModifiedDate() == 0 );
 my $date = new LibSBML::Date(2005, 12, 30, 12, 15, 45, 1, 2, 0);
 $history->setModifiedDate($date);
 ok( $history->isSetModifiedDate() == 1 );
 my $newdate = $history->getModifiedDate();
 ok( $newdate->getYear() == 2005 );
 ok( $newdate->getMonth() == 12 );
 ok( $newdate->getDay() == 30 );
 ok( $newdate->getHour() == 12 );
 ok( $newdate->getMinute() == 15 );
 ok( $newdate->getSecond() == 45 );
 ok( $newdate->getSignOffset() == 1 );
 ok( $newdate->getHoursOffset() == 2 );
 ok( $newdate->getMinutesOffset() == 0 );
}

#---
sub test_ModelHistory_addModifiedDate {
 my $history = new LibSBML::ModelHistory();
 ok( defined $history );
 ok( $history->isSetModifiedDate() == 0 );
 ok( $history->getNumModifiedDates() == 0 );
 my $date = new LibSBML::Date(2005, 12, 30, 12, 15, 45, 1, 2, 0);
 $history->addModifiedDate($date);
 ok( $history->getNumModifiedDates() == 1 );
 ok( $history->isSetModifiedDate() == 1 );
 my $newdate = $history->getModifiedDate(0);
# my $newdate = $history->getListModifiedDates()->get(0);
 ok( $newdate->getYear() == 2005 );
 ok( $newdate->getMonth() == 12 );
 ok( $newdate->getDay() == 30 );
 ok( $newdate->getHour() == 12 );
 ok( $newdate->getMinute() == 15 );
 ok( $newdate->getSecond() == 45 );
 ok( $newdate->getSignOffset() == 1 );
 ok( $newdate->getHoursOffset() == 2 );
 ok( $newdate->getMinutesOffset() == 0 );
 my $date1 = new LibSBML::Date(2008, 11, 2, 16, 42, 40, 1, 2, 0);
 $history->addModifiedDate($date1);
 ok( $history->getNumModifiedDates() == 2 );
 ok( $history->isSetModifiedDate() == 1 );
 my $newdate1 = $history->getModifiedDate(1);
# my $newdate1 = $history->getListModifiedDates()->get(1);
 ok( $newdate1->getYear() == 2008 );
 ok( $newdate1->getMonth() == 11 );
 ok( $newdate1->getDay() == 2 );
 ok( $newdate1->getHour() == 16 );
 ok( $newdate1->getMinute() == 42 );
 ok( $newdate1->getSecond() == 40 );
 ok( $newdate1->getSignOffset() == 1 );
 ok( $newdate1->getHoursOffset() == 2 );
 ok( $newdate1->getMinutesOffset() == 0 );
}

#---
sub test_ModelHistory_getListModifiedDates {
  my $history = new LibSBML::ModelHistory();
  my $date1 = new LibSBML::Date(2005, 12, 30, 12, 15, 45, 1, 2, 0);
  $history->addModifiedDate($date1);  
  my $date2 = new LibSBML::Date(2008, 11, 2, 16, 42, 40, 1, 2, 0);
  $history->addModifiedDate($date2);

  SKIP : {
    eval '$history->getListModifiedDates()';
    skip("ModelHistory::getListModifiedDates is not wrapped.",4) if $@;

    # list context
    my $i = 0;
    foreach my $date4 ($history->getListModifiedDates()) {
      $date4 = $date4->getDateAsString();
      my $date3 = ($i==0) ? $date1->getDateAsString() : $date2->getDateAsString();
      ok( $date4 eq $date3 );
      $i++
    }

    # scalar context
    for $i (0, 1) {
      my $d4 = $history->getListModifiedDates()->get($i)->getDateAsString();
      my $d3 = ($i==0) ? $date1->getDateAsString() : $date2->getDateAsString();
      ok( $d4 eq $d3 );
    }
  }
}

#---
sub test_ModelHistory_getCreators {
  my $xtofA = 'Flamm';
  my $xtofB = 'Christoph';
  my $xtofC = 'xtof@tbi.univie.ac.at';
  my $uni = 'University of Vienna';
  my $raimA = 'Machne';
  my $raimB = 'Rainer';
  my $raimC = 'raim@tbi.univie.ac.at';  
  my $history = new LibSBML::ModelHistory();
  # creator xtof  
  my $mc = new LibSBML::ModelCreator();
  $mc->setFamilyName($xtofA);
  $mc->setGivenName($xtofB);
  $mc->setEmail($xtofC);
  $mc->setOrganisation($uni);
  $history->addCreator($mc);
  # creator raim
  $mc = new LibSBML::ModelCreator();
  $mc->setFamilyName($raimA);
  $mc->setGivenName($raimB);
  $mc->setEmail($raimC);
  $mc->setOrganisation($uni);
  $history->addCreator($mc);  

  SKIP : {
    eval '$history->getListCreators()';
    skip("ModelHistory::getListCreators() is not wrapped.",16) if $@;

    my $i = 0;
    foreach my $newmc ($history->getListCreators()) {
      if ($i++ == 0) { # check creator xtof
        ok( $newmc->getFamilyName() eq $xtofA );
        ok( $newmc->getGivenName() eq $xtofB );
        ok( $newmc->getEmail() eq $xtofC );
        ok( $newmc->getOrganisation() eq $uni );
      }
      else { # check creator raim
        ok( $newmc->getFamilyName() eq $raimA );
        ok( $newmc->getGivenName() eq $raimB );
        ok( $newmc->getEmail() eq $raimC );
        ok( $newmc->getOrganisation() eq $uni ); 
      }
    }

    for $i (0, 1) {
      my $newmc = $history->getListCreators()->get($i);
      if ($i == 0) { # check creator xtof
        ok( $newmc->getFamilyName() eq $xtofA );
        ok( $newmc->getGivenName() eq $xtofB );
        ok( $newmc->getEmail() eq $xtofC );
        ok( $newmc->getOrganisation() eq $uni );
      }
      else { # check creator raim
        ok( $newmc->getFamilyName() eq $raimA );
        ok( $newmc->getGivenName() eq $raimB );
        ok( $newmc->getEmail() eq $raimC );
        ok( $newmc->getOrganisation() eq $uni ); 
      }  
    }
  }
}
