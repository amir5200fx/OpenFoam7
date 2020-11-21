#pragma once
#ifndef _codedFunctionObject_Header
#define _codedFunctionObject_Header

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
	tnbLib::codedFunctionObject

Description
	Provides a general interface to enable dynamic code compilation.

	The entries are:
	\plaintable
	   codeInclude | include files
	   codeOptions | include paths; inserted into EXE_INC in Make/options
	   codeLibs    | link line; inserted into LIB_LIBS in Make/options
	   codeData    | c++; local member data (null constructed);
	   localCode   | c++; local static functions;
	   codeRead    | c++; upon functionObject::read();
	   codeExecute | c++; upon functionObject::execute();
	   codeWrite   | c++; upon functionObject::write()
	   codeEnd     | c++; upon functionObject::end();
	\endplaintable

	Example of function object specification:
	\verbatim
	difference
	{
		libs        ("libutilityFunctionObjects.so");

		type coded;
		// Name of on-the-fly generated functionObject
		name writeMagU;
		codeWrite
		#{
			// Lookup U
			const volVectorField& U = mesh().lookupObject<volVectorField>("U");
			// Write
			mag(U)().write();
		#};
	}
	\endverbatim

See also
	tnbLib::functionObject
	tnbLib::codedBase

SourceFiles
	codedFunctionObject.C

\*---------------------------------------------------------------------------*/

#include <functionObject.hxx>
#include <codedBase.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
						 Class codedFunctionObject Declaration
	\*---------------------------------------------------------------------------*/

	class codedFunctionObject
		:
		public functionObject,
		public codedBase
	{
	protected:

		// Protected static data

			//- The keywords associated with source code
		static FoamFunctionObjects_EXPORT const wordList codeKeys_;


		// Protected data

			//- Reference to the time database
		const Time& time_;

		//- Input dictionary
		dictionary dict_;

		//- The name
		word name_;

		//- Underlying functionObject
		mutable autoPtr<functionObject> redirectFunctionObjectPtr_;


		// Protected Member Functions

			//- Get the loaded dynamic libraries
		FoamFunctionObjects_EXPORT virtual dlLibraryTable& libs() const;

		//- Adapt the context for the current object
		FoamFunctionObjects_EXPORT virtual void prepare(dynamicCode&, const dynamicCodeContext&) const;

		//- Return a description (type + name) for the output
		FoamFunctionObjects_EXPORT virtual string description() const;

		//- Clear any redirected objects
		FoamFunctionObjects_EXPORT virtual void clearRedirect() const;

		//- Get the dictionary to initialize the codeContext
		FoamFunctionObjects_EXPORT virtual const dictionary& codeDict() const;

		//- Get the keywords associated with source code
		FoamFunctionObjects_EXPORT virtual const wordList& codeKeys() const;


	public:

		//- Runtime type information
		//TypeName("coded");
		static const char* typeName_() { return "coded"; }
		static FoamFunctionObjects_EXPORT const ::tnbLib::word typeName;
		static FoamFunctionObjects_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from Time and dictionary
		FoamFunctionObjects_EXPORT codedFunctionObject
		(
			const word& name,
			const Time& time,
			const dictionary& dict
		);

		//- Disallow default bitwise copy construction
		FoamFunctionObjects_EXPORT codedFunctionObject(const codedFunctionObject&) = delete;


		//- Destructor
		FoamFunctionObjects_EXPORT virtual ~codedFunctionObject();


		// Member Functions

			//- Dynamically compiled functionObject
		FoamFunctionObjects_EXPORT functionObject& redirectFunctionObject() const;

		//- Called at each ++ or += of the time-loop.
		//  postProcess overrides the usual executeControl behaviour and
		//  forces execution (used in post-processing mode)
		FoamFunctionObjects_EXPORT virtual bool execute();

		//- Called at each ++ or += of the time-loop.
		//  postProcess overrides the usual writeControl behaviour and
		//  forces writing always (used in post-processing mode)
		FoamFunctionObjects_EXPORT virtual bool write();

		//- Called when Time::run() determines that the time-loop exits.
		//  By default it simply calls execute().
		FoamFunctionObjects_EXPORT virtual bool end();

		//- Read and set the function object if its data have changed
		FoamFunctionObjects_EXPORT virtual bool read(const dictionary&);


		// Member Operators

			//- Disallow default bitwise assignment
		FoamFunctionObjects_EXPORT void operator=(const codedFunctionObject&) = delete;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_codedFunctionObject_Header
