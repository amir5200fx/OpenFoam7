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
		NamespaceName("MSwindows");

		//- Get last windows api error from GetLastError
		std::string getLastError();
	}

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
}

#endif // !_MSwindows_Header