#pragma once
#ifndef _exponentialParticleStressModel_Header
#define _exponentialParticleStressModel_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2013-2019 OpenFOAM Foundation
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
	tnbLib::ParticleStressModels::exponential

Description
	Exponential inter-particle stress model of the same form as used in
	twoPhaseEulerFoam

SourceFiles
	exponential.C

\*---------------------------------------------------------------------------*/

#include <ParticleStressModel.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace ParticleStressModels
	{

		/*---------------------------------------------------------------------------*\
								Class exponential Declaration
		\*---------------------------------------------------------------------------*/

		class exponential
			:
			public ParticleStressModel
		{
			// Private Data

				//- Pre-exponential factor
			scalar preExp_;

			//- Maximum limit of the exponential
			scalar expMax_;

			//- Front coefficient
			scalar g0_;


		public:

			//- Runtime type information
			//TypeName("exponential");
			static const char* typeName_() { return "exponential"; }
			static FoamLagrangian_EXPORT const ::tnbLib::word typeName;
			static FoamLagrangian_EXPORT int debug;
			virtual const word& type() const { return typeName; };


			//- Constructors

				//- Construct from components
			FoamLagrangian_EXPORT exponential(const dictionary& dict);

			//- Construct copy
			FoamLagrangian_EXPORT exponential(const exponential& hc);

			//- Clone
			virtual autoPtr<ParticleStressModel> clone() const
			{
				return autoPtr<ParticleStressModel>
					(
						new exponential(*this)
						);
			}


			//- Destructor
			FoamLagrangian_EXPORT virtual ~exponential();


			//- Member Functions

				//- Collision stress
			FoamLagrangian_EXPORT tmp<Field<scalar>> tau
			(
				const Field<scalar>& alpha,
				const Field<scalar>& rho,
				const Field<scalar>& uRms
			) const;

			//- Collision stress derivaive w.r.t. the volume fraction
			FoamLagrangian_EXPORT tmp<Field<scalar>> dTaudTheta
			(
				const Field<scalar>& alpha,
				const Field<scalar>& rho,
				const Field<scalar>& uRms
			) const;
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace ParticleStressModels
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_exponentialParticleStressModel_Header
