function Totalfail = testBinding(varargin)

if (nargin == 0)
  install = 0;
else
  install = 1;
end;

if (strcmp(isoctave(), '0'))
  test = 15 + 36;
else
  test = 14 + 36;
end;

if (strcmp(isoctave(), '0'))
  Totalfail = doTestRuns(install, test);
else
  Totalfail = doTestRunsOctave(install, test);
end;

disp ('************************************');
disp('Overall tests:');
disp(sprintf('Number tests: %d', test));
disp(sprintf('Number fails: %d', Totalfail));
disp(sprintf('Pass rate: %d%%\n', ((test-Totalfail)/test)*100));

if (Totalfail == 0)
    disp('MATLAB binding tests successful.');
end;

function Totalfail = doTestRuns(install, test)

Totalfail = 0;

try

  Totalfail = Totalfail + testReadFromFile1(install);
  Totalfail = Totalfail + testReadFromFile2(install);
  Totalfail = Totalfail + testReadFromFile3(install);
  Totalfail = Totalfail + testReadFromFile4(install);
  Totalfail = Totalfail + testReadFromFile5(install);
  Totalfail = Totalfail + testReadFromFile6(install);
  Totalfail = Totalfail + testReadFromFile7(install);
  Totalfail = Totalfail + testReadFromFile8(install);
  Totalfail = Totalfail + testReadFromFile9(install);
  Totalfail = Totalfail + testReadFromFile10(install);
  Totalfail = Totalfail + testReadFromFile11(install);
  Totalfail = Totalfail + testReadFromFile12(install);
  Totalfail = Totalfail + testReadFromFile13(install);
  Totalfail = Totalfail + testReadFromFile14(install);
  if (strcmp(isoctave(), '0') && install == 0)
    Totalfail = Totalfail + testReadFlags(install);
  end;

  if (install == 0)
    Totalfail = Totalfail + testOutput('Out-test1', 0);
  end;

catch exception
    disp ('Fatal Error!, tests cannot run due to')
    disp(exception.message)
    Totalfail = test;
end;

function Totalfail = doTestRunsOctave(install, test)

Totalfail = 0;

try

  Totalfail = Totalfail + testReadFromFile1(install);
  Totalfail = Totalfail + testReadFromFile2(install);
  Totalfail = Totalfail + testReadFromFile3(install);
  Totalfail = Totalfail + testReadFromFile4(install);
  Totalfail = Totalfail + testReadFromFile5(install);
  Totalfail = Totalfail + testReadFromFile6(install);
  Totalfail = Totalfail + testReadFromFile7(install);
  Totalfail = Totalfail + testReadFromFile8(install);
  Totalfail = Totalfail + testReadFromFile9(install);
  Totalfail = Totalfail + testReadFromFile10(install);
  Totalfail = Totalfail + testReadFromFile11(install);
  Totalfail = Totalfail + testReadFromFile12(install);
  Totalfail = Totalfail + testReadFromFile13(install);
  Totalfail = Totalfail + testReadFromFile14(install);
  if (strcmp(isoctave(), '0') && install == 0)
    Totalfail = Totalfail + testReadFlags(install);
  end;

  if (install == 0)
    Totalfail = Totalfail + testOutput('Out-test1', 0);
  end;

catch 
    disp ('Fatal Error!, tests cannot run due to')
    disp (lasterr)
    Totalfail = test;
end;



