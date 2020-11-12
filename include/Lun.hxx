#pragma once
#ifndef _Lun_Header
#define _Lun_Header

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
	tnbLib::ParticleStressModels::Lun

Description
	Inter-particle stress model of Lun et al

	The stress value takes the following form:
	\f[
		\left( \alpha \rho + \alpha^2 \rho (1 + e) \frac{3}{5}
		\left( 1 - \left( \frac{\alpha}{\alpha_{pack}} \right)^\frac{1}{3}
		\right) \right) \frac{1}{3} \sigma^2
	\f]
	Here, \f$\alpha\f$ is the volume fraction of the dispersed phase,
	\f$\rho\f$ is the density of the dispersed phase, \f$e\f$ is a coefficient
	of restitution, and \f$\sigma\f$ is the RMS velocity fluctuation.

	Reference:
	\verbatim
		"Kinetic theories for granular flow: inelastic particles in Couette
		flow and slightly inelastic particles in a general flowfield"
		C Lun, S Savage, G Jeffrey, N Chepurniy
		Journal of Fluid Mechanics
		Volume 140, Pages 223-256, 1984
	\endverbatim

SourceFiles
	Lun.C

\*---------------------------------------------------------------------------*/

#include <ParticleStressModel.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace ParticleStressModels
	{

		/*---------------------------------------------------------------------------*\
								Class Lun Declaration
		\*---------------------------------------------------------------------------*/

		class Lun
			:
			public ParticleStressModel
		{
			// Private Data

				//- Coefficient of restitution
			scalar e_;

			//- Smallest allowable difference from the packed volume fraction
			scalar eps_;


		public:

			//- Runtime type information
			//TypeName("Lun");
			static const char* typeName_() { return "Lun"; }
			static FoamLagrangian_EXPORT const ::tnbLib::word typeName;
			static FoamLagrangian_EXPORT int debug;
			virtual const word& type() const { return typeName; };


			//- Constructors

				//- Construct from components
			FoamLagrangian_EXPORT Lun(const dictionary& dict);

			//- Construct copy
			FoamLagrangian_EXPORT Lun(const Lun& hc);

			//- Clone
			virtual autoPtr<ParticleStressModel> clone() const
			{
				return autoPtr<ParticleStressModel>
					(
						new Lun(*this)
						);
			}


			//- Destructor
			FoamLagrangian_EXPORT virtual ~Lun();


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

#endif // !_Lun_Header
