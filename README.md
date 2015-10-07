=============================
FuzzyLogicGenerator
=============================

This Application enables you to generate out of the box usable MaxJ code in order to solve complex fuzzy logic problems.


Introduction
------------

Fuzzy Logic is used to solve many different problems. 
This Application enables you to write simple descriptions of your fuzzy logic problem and use them to generate code that can be directly used to configure an FPGA.
The Generator is provided as C++ source code and can be modified to fit your problem. Also the generated source code is auto documented to enable you to reuse generated code in your own application.


Usage
-----

To build the generator simply cd to the APP directory and type
    
    make

The name of the generator is FuzzyLogicGenerator. Usage as follows:

    ./FuzzyLogicGenerator -i <path to description> [-t <count of ticks for every input variable>]

The options are defined as follows:
* -i The input file is a description available in the .fll format. You can find more details about this format in the tech slides or on http://www.fuzzylite.com/fll-fld/
* -t This option expects a number. The generator creates some test data and CPU code to use that data by itself. The number changes how many different value are used for testing for every input variable. Please note that if you have 5 input variables and set this value to 100 100^5 different test cases get created. The standard value is 100.

The generator creates 5 files:
* The MaxJ kernel
* The MaxJ manager
* The MaxJ engine parameters
* CPU code written in c to load and execute the test cases
* an .fld file (Details at: http://www.fuzzylite.com/fll-fld/) containing the different values for every input and output variable. The output variables are set to zero and will be changed after the Code was executed at least once.

Also the generator will provide an directory with the same name as given to the engine in the fuzzy logic description file.
This directory contains all the previously mentioned files as well as a lot more files needed to actually build and run the project using MaxCompiler. It can also be imported to MaxIDE.
To start the simulation for example you first have to cd to the CPUCode directory (please notice: the APP directory within the APP directory is used as a template) and then type

    make runsim RUNRULE=Simulation

You can find more details (also on how to edit the generator) in the DOCS directory


Features
--------

* Auto generation of a full DFE application able to solve fuzzy logic problems from a simple description
* Easy to modify


To-Do
-----

* Add more different fuzzy set shapes

Reference
---------

    Juan Rada-Vilela. fuzzylite: a fuzzy logic control library, 2014. URL http://www.fuzzylite.com.
