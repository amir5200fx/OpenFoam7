#pragma once
#ifndef _openFoamTableReader_Header
#define _openFoamTableReader_Header

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
	tnbLib::openFoamTableReader

Description
	Reads an interpolation table from a file - OpenFOAM-format

SourceFiles
	openFoamTableReader.C

\*---------------------------------------------------------------------------*/

#include <tableReader.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
						 Class openFoamTableReader Declaration
	\*---------------------------------------------------------------------------*/

	template<class Type>
	class openFoamTableReader
		:
		public tableReader<Type>
	{

	public:

		//- Runtime type information
		TypeName("openFoam");


		// Constructors

			//- Construct from dictionary
		openFoamTableReader(const dictionary &dict);

		//- Construct and return a copy
		virtual autoPtr<tableReader<Type>> clone() const
		{
			return autoPtr<tableReader<Type>>
				(
					new openFoamTableReader<Type>
					(
						*this
						)
					);
		}


		//- Destructor
		virtual ~openFoamTableReader();


		// Member Functions

			//- Read the table
		virtual void operator()(const fileName&, List<Tuple2<scalar, Type>> &);

		//- Read 2D table
		virtual void operator()
			(
				const fileName&,
				List<Tuple2<scalar, List<Tuple2<scalar, Type>>>>&
				);
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <openFoamTableReaderI.hxx>

//#ifdef NoRepository
//#include <openFoamTableReader.cxx>
//#endif


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_openFoamTableReader_Header
