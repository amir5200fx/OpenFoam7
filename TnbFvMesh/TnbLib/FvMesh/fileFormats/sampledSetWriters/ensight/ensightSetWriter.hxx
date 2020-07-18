#pragma once
#ifndef _ensightSetWriter_Header
#define _ensightSetWriter_Header

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
	tnbLib::ensightSetWriter

Description

SourceFiles
	ensightSetWriter.C

\*---------------------------------------------------------------------------*/

#include <writer.hxx>
#include <PtrList.hxx>  // added by amir

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
						 Class ensightSetWriter Declaration
	\*---------------------------------------------------------------------------*/

	template<class Type>
	class ensightSetWriter
		:
		public writer<Type>
	{

	public:

		//- Runtime type information
		TypeName("ensight");


		// Constructors

			//- Construct null
		ensightSetWriter();


		//- Destructor
		virtual ~ensightSetWriter();


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
		) const;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#ifdef NoRepository
#include <ensightSetWriter.cxx>
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_ensightSetWriter_Header
