#pragma once
#ifndef _IFstream_Header
#define _IFstream_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2011-2019 OpenFOAM Foundation
	 \\/     M anipulation  |
-------------------------------------------------------------------------------
License
	This file is part of OpenFOAM.

	OpenFOAM is free software: you can redistribute it and/or modify it
	under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
	ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
	FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
	for more details.

	You should have received a copy of the GNU General Public License
	along with OpenFOAM.  If not, see <http://www.gnu.org/licenses/>.

Class
	tnbLib::IFstream

Description
	Input from file stream.

SourceFiles
	IFstream.C

\*---------------------------------------------------------------------------*/

#include <ISstream.hxx>
#include <fileName.hxx>
#include <className.hxx>

#include <fstream>
using std::ifstream;

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	class IFstream;

	/*---------------------------------------------------------------------------*\
						  Class IFstreamAllocator Declaration
	\*---------------------------------------------------------------------------*/

	//- A std::istream with ability to handle compressed files
	class IFstreamAllocator
	{
		friend class IFstream;

		// Private Data

		istream* ifPtr_;
		IOstream::compressionType compression_;


		// Constructors

			//- Construct from pathname
		FoamBase_EXPORT IFstreamAllocator(const fileName& pathname);


		//- Destructor
		FoamBase_EXPORT ~IFstreamAllocator();
	};


	/*---------------------------------------------------------------------------*\
							  Class IFstream Declaration
	\*---------------------------------------------------------------------------*/

	class IFstream
		:
		public IFstreamAllocator,
		public ISstream
	{
		// Private Data

		fileName pathname_;

	public:

		// Declare name of the class and its debug switch
		//ClassName("IFstream");
		static const char* typeName_() { return "IFstream"; } 
		static FoamBase_EXPORT const ::tnbLib::word typeName; 
		static FoamBase_EXPORT int debug;


		// Constructors

			//- Construct from pathname
		FoamBase_EXPORT IFstream
		(
			const fileName& pathname,
			streamFormat format = ASCII,
			versionNumber version = currentVersion
		);


		//- Destructor
		FoamBase_EXPORT ~IFstream();


		// Member Functions

			// Access

				//- Return the name of the stream
		const fileName& name() const
		{
			return pathname_;
		}

		//- Return non-const access to the name of the stream
		fileName& name()
		{
			return pathname_;
		}


		// STL stream

			//- Access to underlying std::istream
		FoamBase_EXPORT virtual istream& stdStream();

		//- Const access to underlying std::istream
		FoamBase_EXPORT virtual const istream& stdStream() const;


		// Print

			//- Print description of IOstream to Ostream
		FoamBase_EXPORT virtual void print(Ostream&) const;


		// Member Operators

			//- Return a non-const reference to const IFstream
			//  Needed for read-constructors where the stream argument is temporary:
			//  e.g. thing thisThing(IFstream("thingFileName")());
		FoamBase_EXPORT IFstream& operator()() const;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_IFstream_Header
