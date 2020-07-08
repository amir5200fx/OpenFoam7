#pragma once
#ifndef _Table_Header
#define _Table_Header

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
	tnbLib::Function1Types::Table

Description
	Templated table container function.

	Items are stored in a list of Tuple2's. First column is always stored as
	scalar entries. Data is read in Tuple2 form.

	Usage:
	\verbatim
		<entryName>   table
		(
			(0.0 (1 2 3))
			(1.0 (4 5 6))
		);
	\endverbatim

SourceFiles
	Table.C

\*---------------------------------------------------------------------------*/

#include <Function1.hxx>
#include <Tuple2.hxx>
#include <TableBase.hxx> // added by amir

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace Function1Types
	{

		/*---------------------------------------------------------------------------*\
								   Class Table Declaration
		\*---------------------------------------------------------------------------*/

		template<class Type>
		class Table
			:
			public TableBase<Type>
		{

		public:

			//- Runtime type information
			TypeName("table");


			// Constructors

				//- Construct from entry name and Istream
			Table(const word& entryName, const dictionary& dict);

			//- Copy constructor
			Table(const Table<Type>& tbl);


			//- Destructor
			virtual ~Table();


			// Member Operators

				//- Disallow default bitwise assignment
			void operator=(const Table<Type>&) = delete;
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace Function1Types
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#ifdef NoRepository
#include <Table.cxx>
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
#endif // !_Table_Header
