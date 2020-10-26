#pragma once
#ifndef _MSwindows_Header
#define _MSwindows_Header

#include <string>

#include <className.hxx>

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	namespace MSwindows
	{
		//- Declare name of the class and it's debug switch
		//NamespaceName("MSwindows");
		inline const char* typeName_() { return "MSwindows"; }
		FoamBase_EXPORT extern const ::tnbLib::word typeName; 
		FoamBase_EXPORT extern int debug;

		//- Get last windows api error from GetLastError
		FoamBase_EXPORT std::string getLastError();
	}

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
}

#endif // !_MSwindows_Header