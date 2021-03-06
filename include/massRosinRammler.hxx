#pragma once
#ifndef _massRosinRammler_Header
#define _massRosinRammler_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2016-2019 OpenFOAM Foundation
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
	tnbLib::distributionModels::massRosinRammler

Description
	Mass-based Rosin-Rammler distributionModel.

	Corrected form of the Rosin-Rammler distribution taking into account the
	varying number of particels per parces for for fixed-mass parcels.  This
	distribution should be used when
	\verbatim
		parcelBasisType mass;
	\endverbatim

	See equation 10 in reference:
	\verbatim
		Yoon, S. S., Hewson, J. C., DesJardin, P. E., Glaze, D. J.,
		Black, A. R., & Skaggs, R. R. (2004).
		Numerical modeling and experimental measurements of a high speed
		solid-cone water spray for use in fire suppression applications.
		International Journal of Multiphase Flow, 30(11), 1369-1388.
	\endverbatim

SourceFiles
	massRosinRammler.C

\*---------------------------------------------------------------------------*/

#include <distributionModel.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace distributionModels
	{

		/*---------------------------------------------------------------------------*\
							   Class massRosinRammler Declaration
		\*---------------------------------------------------------------------------*/

		class massRosinRammler
			:
			public distributionModel
		{
			// Private Data

				//- Distribution minimum
			scalar minValue_;

			//- Distribution maximum
			scalar maxValue_;

			//- Characteristic droplet size
			scalar d_;

			//- Empirical dimensionless constant to specify the distribution width,
			//  sometimes referred to as the dispersion coefficient
			scalar n_;


		public:

			//- Runtime type information
			//TypeName("massRosinRammler");
			static const char* typeName_() { return "massRosinRammler"; }
			static FoamLagrangian_EXPORT const ::tnbLib::word typeName;
			static FoamLagrangian_EXPORT int debug;
			virtual const word& type() const { return typeName; };


			// Constructors

				//- Construct from components
			FoamLagrangian_EXPORT massRosinRammler(const dictionary& dict, Random& rndGen);

			//- Construct copy
			FoamLagrangian_EXPORT massRosinRammler(const massRosinRammler& p);

			//- Construct and return a clone
			virtual autoPtr<distributionModel> clone() const
			{
				return autoPtr<distributionModel>(new massRosinRammler(*this));
			}


			//- Destructor
			FoamLagrangian_EXPORT virtual ~massRosinRammler();


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

#endif // !_massRosinRammler_Header
