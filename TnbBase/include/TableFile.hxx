#pragma once
#ifndef _TableFile_Header
#define _TableFile_Header

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
	tnbLib::Function1Types::TableFile

Description
	Templated table container function where data is read from file.

	Usage:
	\verbatim
		<entryName> tableFile;
		<entryName>Coeffs
		{
			file                dataFile;    // name of data file
			outOfBounds         clamp;       // optional out-of-bounds handling
			interpolationScheme linear;      // optional interpolation method
		}
	\endverbatim

	Data is stored as a list of Tuple2's. First column is always stored as
	scalar entries.  Data is read in the form, e.g. for an entry \<entryName\>
	that is (scalar, vector):
	\verbatim
		(
			(0.0 (1 2 3))
			(1.0 (4 5 6))
		);
	\endverbatim

SourceFiles
	TableFile.C

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
								   Class TableFile Declaration
		\*---------------------------------------------------------------------------*/

		template<class Type>
		class TableFile
			:
			public TableBase<Type>
		{
			// Private Data

				//- File name for csv table (optional)
			fileName fName_;


		public:

			//- Runtime type information
			TypeName("tableFile");


			// Constructors

				//- Construct from entry name and Istream
			TableFile(const word& entryName, const dictionary& dict);

			//- Copy constructor
			TableFile(const TableFile<Type>& tbl);


			//- Destructor
			virtual ~TableFile();


			// I/O

				//- Write in dictionary format
			virtual void writeData(Ostream& os) const;


			// Member Operators

				//- Disallow default bitwise assignment
			void operator=(const TableFile<Type>&) = delete;
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace Function1Types
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <TableFileI.hxx>

//#ifdef NoRepository
//#include <TableFile.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_TableFile_Header
