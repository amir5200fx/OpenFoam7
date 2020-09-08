#pragma once
#ifndef _uniformInterpolationTable_Header
#define _uniformInterpolationTable_Header

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
	tnbLib::uniformInterpolationTable

Description
	Table with uniform interval in independent variable, with linear
	interpolation

	Example usage (scalar): values specified within a dictionary:

	\verbatim
	{
		x0          0;          // lower limit
		dx          0.2;        // fixed interval
		log10       true;       // take log(10) when interpolating?
		data                    // list of dependent data values
		(
			7870                // value at x0
			7870                // value at x0 + dx
			...
			7870                // value at x0 + n*dx
		);
	}
	\endverbatim

SourceFiles
	uniformInterpolationTable.C

\*---------------------------------------------------------------------------*/

#include <List.hxx>
#include <Switch.hxx>
#include <IOobject.hxx>
#include <objectRegistry.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
					 Class uniformInterpolationTable Declaration
	\*---------------------------------------------------------------------------*/

	template<class Type>
	class uniformInterpolationTable
		:
		public IOobject,
		public List<Type>
	{
		// Private Data

			// Control parameters

				//- Lower limit
		scalar x0_;

		//- Fixed interval
		scalar dx_;

		//- Flag to indicate that x data are given in log10(x) form
		Switch log10_;

		//- Bound x values
		Switch bound_;


		// Private Member Functions

			//- Check that the table is valid
		void checkTable() const;


	public:

		// Constructors

			//- Construct from IOobject and readFields flag.
			//  Creates a null object if readFields = false
		uniformInterpolationTable(const IOobject&, const bool readFields);

		//- Construct from name, objectRegistry and dictionary.
		//  If initialiseOnly flag is set, control parameters are read from
		//  the dictionary, but not the data table
		uniformInterpolationTable
		(
			const word& tableName,
			const objectRegistry&,
			const dictionary&,
			const bool initialiseOnly = false
		);

		//- Copy constructor
		uniformInterpolationTable(const uniformInterpolationTable&);


		//- Destructor
		~uniformInterpolationTable();


		// Member Functions

			// Access

				//- Return the lower limit
		inline scalar x0() const;

		//- Return the fixed interval
		inline scalar dx() const;

		//- Return the log10(x) flag
		inline const Switch& log10() const;

		//- Return the bound flag
		inline const Switch& bound() const;


		// Edit

			//- Return the lower limit
		inline scalar& x0();

		//- Return the fixed interval
		inline scalar& dx();

		//- Return the log10(x) flag
		inline Switch& log10();

		//- Return the bound flag
		inline Switch& bound();


		// Evaluation

			//- Return the minimum x value
		inline scalar xMin() const;

		//- Return the maximum x value
		inline scalar xMax() const;

		//- Interpolate
		Type interpolate(scalar x) const;

		//- Interpolate - takes log10 flag into account
		Type interpolateLog10(scalar x) const;


		// Override ancestor size() function and [] operator

			//- Return the size of the table
		using List<Type>::size;

		//- Use List[] operator for read/write access
		using List<Type>::operator[];


		// I-O

			//- Write
		void write() const;


		// Member Operators

			//- Disallow default bitwise assignment
		void operator=(const uniformInterpolationTable&) = delete;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <uniformInterpolationTableI.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <uniformInterpolationTable_Imp.hxx>

//#ifdef NoRepository
//#include <uniformInterpolationTable.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_uniformInterpolationTable_Header
