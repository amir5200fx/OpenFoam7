#pragma once
#ifndef _Explicit_Header
#define _Explicit_Header

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
	tnbLib::PackingModels::Explicit

Description
	Explicit model for applying an inter-particle stress to the particles.

	The inter-particle stress is calculated using current particle locations.
	This force is then applied only to the particles that are moving towards
	regions of close pack. The resulting velocity change is limited using an
	abtracted correction velocity limiter.

	Reference:
	\verbatim
		"An Incompressible Three-Dimensional Multiphase Particle-in-Cell Model
		for Dense Particle Flows"
		D Snider
		Journal of Computational Physics
		Volume 170, Issue 2, Pages 523-549, July 2001
	\endverbatim

SourceFiles
	Explicit.C

\*---------------------------------------------------------------------------*/

#include <PackingModel.hxx>

#include <vector.hxx>  // added by amir

#ifdef FoamLagrangian_EXPORT_DEFINE
#define FoamExplicit_EXPORT __declspec(dllexport)
#else
#ifdef FoamExplicit_EXPORT_DEFINE
#define FoamExplicit_EXPORT __declspec(dllexport)
#else
#define FoamExplicit_EXPORT __declspec(dllimport)
#endif
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace PackingModels
	{

		/*---------------------------------------------------------------------------*\
								 Class Explicit Declaration
		\*---------------------------------------------------------------------------*/

		template<class CloudType>
		class Explicit
			:
			public PackingModel<CloudType>
		{
			// Private Data

				//- Volume fraction average
			const AveragingMethod<scalar>* volumeAverage_;

			//- Velocity average
			const AveragingMethod<vector>* uAverage_;

			//- Stress average field
			autoPtr<AveragingMethod<scalar>> stressAverage_;

			//- Correction limiter
			autoPtr<CorrectionLimitingMethod> correctionLimiting_;


		public:

			//- Runtime type information
			//TypeName("explicit");
			static const char* typeName_() { return "explicit"; }
			static FoamExplicit_EXPORT const ::tnbLib::word typeName;
			static FoamExplicit_EXPORT int debug;
			virtual const word& type() const { return typeName; };

			// Constructors

				//- Construct from components
			Explicit(const dictionary& dict, CloudType& owner);

			//- Construct copy
			Explicit(const Explicit<CloudType>& cm);

			//- Construct and return a clone
			virtual autoPtr<PackingModel<CloudType>> clone() const
			{
				return autoPtr<PackingModel<CloudType>>
					(
						new Explicit<CloudType>(*this)
						);
			}


			//- Destructor
			virtual ~Explicit();


			// Member Functions

				//- Calculate the inter particles stresses
			virtual void cacheFields(const bool store);

			//- Calculate the velocity correction
			virtual vector velocityCorrection
			(
				typename CloudType::parcelType& p,
				const scalar deltaT
			) const;
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace PackingModels
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <ExplicitI.hxx>

//#ifdef NoRepository
//#include <Explicit.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_Explicit_Header
