Hi! Thanks for helping out with this project.

To install:

Install Qt 5.latest (last tested on 5.4.1) (http://qt-project.org/)
-- Use the default installation options. This includes letting Qt install MinGW as the compiler.

Download the source from Github repository (https://github.com/hitlechro/Hofstadter/)
Open Hofstadter.pro in QT and click on Projects on the left (If not already selected)
Running the program should work!

If you are getting problems:
--Ensure MinGW is selected as a build kit.
--Click "Configure Project" -- this creates the .pro.user file for your machine.
--Build the project.
--If you get build errors, try editing the Hofstadter.pro file, saving, revert the changes, and save again. This should run the qmake and fix the problem. We currently have no fix for this.
