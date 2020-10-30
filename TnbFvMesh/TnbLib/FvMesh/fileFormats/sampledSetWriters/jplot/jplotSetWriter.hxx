#pragma once
#ifndef _jplotSetWriter_Header
#define _jplotSetWriter_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2011-2018 OpenFOAM Foundation
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
	tnbLib::jplotSetWriter

SourceFiles
	jplotSetWriter.C

\*---------------------------------------------------------------------------*/

#include <writer.hxx>
#include <vector.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
						  Class jplotSetWriter Declaration
	\*---------------------------------------------------------------------------*/

	template<class Type>
	class jplotSetWriter
		:
		public writer<Type>
	{

		// Private Member Functions

			//- Write header
		Ostream& writeHeader(Ostream&) const;

	public:

		//- Runtime type information
		//TypeName("jplot");
		static const char* typeName_() { return "jplot"; }
		static FoamFvMesh_EXPORT const ::tnbLib::word typeName;
		static FoamFvMesh_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct null
		jplotSetWriter();


		//- Destructor
		virtual ~jplotSetWriter();


		// Member Functions

		virtual fileName getFileName
		(
			const coordSet&,
			const wordList&
		) const;

		virtual void write
		(
			const coordSet&,
			const wordList&,
			const List<const Field<Type>*>&,
			Ostream&
		) const;

		virtual void write
		(
			const bool writeTracks,
			const PtrList<coordSet>&,
			const wordList& valueSetNames,
			const List<List<Field<Type>>>&,
			Ostream&
		) const
		{
			NotImplemented;
		}
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <jplotSetWriterI.hxx>

//#ifdef NoRepository
//#include <jplotSetWriter.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_jplotSetWriter_Header
