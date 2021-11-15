# OpenFOAM 7
This is a windows port of the OpenFOAM's source code which runs on visual studio 2017. In this version you can compile any part of the code you want and use it in your projects as a library!

# What am I doing?
I’m currently working on porting the Linux version of OpenFOAM 7 source code into Windows platform under a Microsoft Visual Studio solution. This contains huge amount of intervention into the code, such as: 
*	All headers and implementation extension files have been changed from .H and .C to .hxx and .cxx, respectively.
*	Visual studio is very sensitive to macros that have been redefined. OpenFOAM uses macros, extensively and some of them are redefined constantly; so, all of them had to be replaced by equivalent codes.
*	All implementations of template functions are moved to header files.
*	All functions that are defined in cxx file have been exported to create a dynamic lib
* I had to slightly change the code in some areas such as Istream.hxx to break cycle inclusion between Istream and token.

# Installation
For compiling TnbFoamyMeh project you first need to install CGAL and GMP. For this project, you need to set the following Environment Variables:
* BOOST_INCLUDEDIR (boost headers)
* BOOST_INCLUDELIB (boost libs)
* CGAL_INCLUDEDIR (CGAL headers)
* GMP_INCLUDEDIR (headers)
* GMP_INCLUDELIB (libs)

If you don't have a plan to use this project, you just need to clone the solution and compile the projects you want!

# Warnings!
* Use ONLY Microsoft visual studio 2017 to compile the code (other versions will be supported soon).
* To avoid any issue while compiling the code, please, clone the code into the root of your directory. e.g: "`C:\OpenFOAM7\ ...`"
* Please, compile the code first in debug mode and then in release mode.
