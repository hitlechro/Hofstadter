# What is Hofstadter?

Hofstadter is a flexible, portable, accessible and efficient program for generating and analyzing recursions. Going into more detail:

## Flexible	
Hofstadter is embedded with a robust parser for mathematical expression. 
## Portable	
Hofstadter is implemented in C++, dynamically linked with Qt development library. No extra package or software has to be pre-installed in order to have it run smoothly on Windows, Mac or Linux.
## Accessible	
Hofstadter comes with this complete reference containing rigorous definition and the methodology, allowing user to understand the results thoroughly.
## Efficient	
Hofstadter implements efficient algorithms to generate recursions and its summary statistics. It offers excellent performance with respect to runtime and memory usage. Users can enjoy state-of-the-art algorithms within reach.

# Getting Help

Any question can be directed to: 
* Robert Lech at robert.lech123@gmail.com or 
* Michael Margel at michael.margel@utoronto.ca.

# To install:

1) Install Qt 5.latest (last tested on 5.5.1) 
* Go to http://www.qt.io/download/
* Select "Open source distribution under a LGPL or GPL license" (this project is shared publicly on GitHub), "Yes", "Yes". Click "Get Started" and then "Click now".
* Use the default installation options. This includes letting Qt install MinGW as the compiler.

2) Download the source from Github repository
* This can be done from: https://github.com/robert-7/Hofstadter/

3) Import the project.
* Run Qt.
* Open Hofstadter.pro in QT and click on Projects on the left (If not already selected)
* Running the program should work!

# If you are getting problems
* Ensure MinGW is selected as a build kit.
* Click "Configure Project" -- this creates the .pro.user file for your machine.
* Build the project.
* If you get build errors, try editing the Hofstadter.pro file, saving, revert the changes, and save again. This should run the qmake and fix the problem. We currently have no fix for this.
