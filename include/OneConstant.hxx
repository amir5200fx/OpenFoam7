#pragma once
#ifndef _OneConstant_Header
#define _OneConstant_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2017-2019 OpenFOAM Foundation
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
	tnbLib::Function1Types::OneConstant

Description
	Templated function that returns the corresponding 1 (one).

	Usage:
	\verbatim
		<entryName> one;
	\endverbatim

SourceFiles
	OneConstant.C

\*---------------------------------------------------------------------------*/

#include <Function1.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace Function1Types
	{

		/*---------------------------------------------------------------------------*\
								   Class OneConstant Declaration
		\*---------------------------------------------------------------------------*/

		template<class Type>
		class OneConstant
			:
			public Function1<Type>
		{

		public:

			// Runtime type information
			TypeName("one");


			// Constructors

				//- Construct from entry name
			OneConstant(const word& entryName);

			//- Construct from entry name and dictionary
			OneConstant(const word& entryName, const dictionary& dict);

			//- Construct and return a clone
			virtual tmp<Function1<Type>> clone() const
			{
				return tmp<Function1<Type>>(new OneConstant<Type>(*this));
			}


			//- Destructor
			virtual ~OneConstant();


			// Member Functions

				//- Return constant value
			virtual inline Type value(const scalar) const;

			//- Integrate between two values
			virtual inline Type integrate(const scalar x1, const scalar x2) const;

			//- Return value as a function of (scalar) independent variable
			virtual tmp<Field<Type>> value(const scalarField& x) const;

			//- Integrate between two (scalar) values
			virtual tmp<Field<Type>> integrate
			(
				const scalarField& x1,
				const scalarField& x2
			) const;

			//- Write in dictionary format
			virtual void writeData(Ostream& os) const;


			// Member Operators

				//- Disallow default bitwise assignment
			void operator=(const OneConstant<Type>&) = delete;
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace Function1Types
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <OneConstantI.hxx>
#include <OneConstant_Imp.hxx>

//#ifdef NoRepository
//#include <OneConstant.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_OneConstant_Header
