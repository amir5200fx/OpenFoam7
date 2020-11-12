#pragma once
#ifndef _fixedValue_Header
#define _fixedValue_Header

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
	tnbLib::distributionModels::fixedValue

Description
	Returns a fixed value

SourceFiles
	fixedValue.C

\*---------------------------------------------------------------------------*/

#include <distributionModel.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace distributionModels
	{
		/*---------------------------------------------------------------------------*\
							   Class fixedValue Declaration
		\*---------------------------------------------------------------------------*/

		class fixedValue
			:
			public distributionModel
		{
			// Private Data

				//- Fixed value
			scalar value_;


		public:

			//- Runtime type information
			//TypeName("fixedValue");
			static const char* typeName_() { return "fixedValue"; }
			static FoamLagrangian_EXPORT const ::tnbLib::word typeName;
			static FoamLagrangian_EXPORT int debug;
			virtual const word& type() const { return typeName; };


			// Constructors

				//- Construct from components
			FoamLagrangian_EXPORT fixedValue(const dictionary& dict, Random& rndGen);

			//- Construct copy
			FoamLagrangian_EXPORT fixedValue(const fixedValue& p);

			//- Construct and return a clone
			virtual autoPtr<distributionModel> clone() const
			{
				return autoPtr<distributionModel>(new fixedValue(*this));
			}


			//- Destructor
			FoamLagrangian_EXPORT virtual ~fixedValue();


			// Member Functions

				//- Sample the distributionModel
			FoamLagrangian_EXPORT virtual scalar sample() const;

			//- Return the minimum value
			FoamLagrangian_EXPORT virtual scalar minValue() const;

			//- Return the maximum value
			FoamLagrangian_EXPORT virtual scalar maxValue() const;

			//- Return the mean value
			FoamLagrangian_EXPORT virtual scalar meanValue() const;
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace distributionModels
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_fixedValue_Header
