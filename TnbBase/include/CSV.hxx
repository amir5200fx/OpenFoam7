#pragma once
#ifndef _CSV_Header
#define _CSV_Header

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
	tnbLib::Function1Types::Constant

Description
	Templated function that returns a constant value.

	Usage - for entry \<entryName\> returning the value <value>:
	\verbatim
		<entryName>    constant  <value>
	\endverbatim

SourceFiles
	Constant.C

\*---------------------------------------------------------------------------*/

#include <Function1.hxx>
#include <TableBase.hxx>
#include <Tuple2.hxx>
#include <labelList.hxx>
#include <ISstream.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace Function1Types
	{

		/*---------------------------------------------------------------------------*\
								   Class CSV Declaration
		\*---------------------------------------------------------------------------*/

		template<class Type>
		class CSV
			:
			public TableBase<Type>
		{
			// Private Data

				//- Number header lines
			label nHeaderLine_;

			//- Column of the time
			label refColumn_;

			//- Labels of the components
			labelList componentColumns_;

			//- Separator character
			char separator_;

			//- Merge separators flag, e.g. ',,,' becomes ','
			bool mergeSeparators_;

			//- File name for csv table
			fileName fName_;


			// Private Member Functions

				//- Read csv data table
			void read();

			//- Read the next value from the split string
			Type readValue(const List<string>&);


		public:

			//- Runtime type information
			//TypeName("csvFile");
			static const char* typeName_() { return "csvFile"; }
			static FoamBase_EXPORT const ::tnbLib::word typeName;
			static FoamBase_EXPORT int debug;
			virtual const word& type() const { return typeName; };


			// Constructors

				//- Construct from entry name and dictionary
			CSV
			(
				const word& entryName,
				const dictionary& dict
			);

			//- Copy constructor
			CSV(const CSV<Type>& tbl);


			//- Destructor
			virtual ~CSV();


			// Member Functions

				//- Return const access to the file name
			virtual const fileName& fName() const;

			//- Write in dictionary format
			virtual void writeData(Ostream& os) const;


			// Member Operators

				//- Disallow default bitwise assignment
			void operator=(const CSV<Type>&) = delete;
		};


		template<>
		FoamBase_EXPORT label CSV<label>::readValue(const List<string>& split);

		template<>
		FoamBase_EXPORT tnbLib::scalar CSV<scalar>::readValue(const List<string>& split);


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace Function1Types
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

//#ifdef NoRepository
//#include <CSV.cxx>
//#endif

#include <CSVI.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //


#endif // !_CSV_Header
