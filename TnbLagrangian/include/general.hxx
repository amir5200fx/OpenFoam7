#pragma once
#ifndef _general_Header
#define _general_Header

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
	tnbLib::distributionModels::general

Description
	general distribution model

SourceFiles
	general.C

\*---------------------------------------------------------------------------*/

#include <distributionModel.hxx>
#include <VectorTemplate.hxx>
#include <VectorSpace.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace distributionModels
	{

		/*---------------------------------------------------------------------------*\
								   Class general Declaration
		\*---------------------------------------------------------------------------*/

		class general
			:
			public distributionModel
		{
			// Private Data

			typedef VectorSpace<Vector<scalar>, scalar, 2> pair;

			List<pair> xy_;

			label nEntries_;

			//- Min and max values of the distribution
			scalar minValue_;
			scalar maxValue_;

			scalar meanValue_;

			List<scalar> integral_;


		public:

			//- Runtime type information
			TypeName("general");


			// Constructors

				//- Construct from components
			general(const dictionary& dict, Random& rndGen);

			//- Construct copy
			general(const general& p);

			//- Construct and return a clone
			virtual autoPtr<distributionModel> clone() const
			{
				return autoPtr<distributionModel>(new general(*this));
			}


			//- Destructor
			virtual ~general();


			// Member Functions

				//- Sample the distributionModel
			virtual scalar sample() const;

			//- Return the minimum value
			virtual scalar minValue() const;

			//- Return the maximum value
			virtual scalar maxValue() const;

			//- Return the mean value
			virtual scalar meanValue() const;
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace distributionModels
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_general_Header
