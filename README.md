# OpenFoam 7
This is a windows port of the OpenFoam's source code which runs on visual studio 2017

# What am I doing?
I’m currently working on porting the Linux version of OpenFoam 7 source code into Windows platform under a Microsoft Visual Studio solution. This contains huge amount of intervention into the code, such as: 
*	All headers and implementation extension files have been changed from .H and .C to .hxx and .cxx, respectively.
*	Visual studio is very sensitive to macros that have been redefined. OpenFoam uses macros, extensively and some of them are redefined constantly; so, all of them had to be replaced by equivalent codes.
*	All implementations of template functions are moved to header files.
*	All functions that are defined in cxx file have been exported to create a dynamic lib
* I had to slightly change the code in some areas such as Istream.hxx to break cycle inclusion between Istream and token
