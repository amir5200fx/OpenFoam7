#pragma once
#ifndef _BrownianMotionForce_Header
#define _BrownianMotionForce_Header

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
	tnbLib::BrownianMotionForce

Description
	Calculates particle Brownian motion force.

	Reference:
	\verbatim
		Li, A., & Ahmadi, G. (1992).
		Dispersion and deposition of spherical particles from point sources
		in a turbulent channel flow.
		Aerosol science and technology,
		16(4), 209-226.
	\endverbatim

SourceFiles
	BrownianMotionForceI.H
	BrownianMotionForce.C

\*---------------------------------------------------------------------------*/

#include <ParticleForce.hxx>
#include <Random.hxx>

#ifdef FoamLagrangian_EXPORT_DEFINE
#define FoamBrownianMotionForce_EXPORT __declspec(dllexport)
#else
#ifdef FoamBrownianMotionForce_EXPORT_DEFINE
#define FoamBrownianMotionForce_EXPORT __declspec(dllexport)
#else
#define FoamBrownianMotionForce_EXPORT __declspec(dllimport)
#endif
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
						Class BrownianMotionForce Declaration
	\*---------------------------------------------------------------------------*/

	template<class CloudType>
	class BrownianMotionForce
		:
		public ParticleForce<CloudType>
	{
		// Private Data

			//- Reference to the cloud random number generator
		Random& rndGen_;

		//- Molecular free path length [m]
		const scalar lambda_;

		//- Turbulence flag
		bool turbulence_;

		//- Pointer to the turbulence kinetic energy field
		const volScalarField* kPtr_;

		//- Flag that indicates ownership of turbulence k field
		bool ownK_;


		// Private Member Functions

			//- Inverse erf for Gaussian distribution
		scalar erfInv(const scalar y) const;

		//- Return the k field from the turbulence model
		tmp<volScalarField> kModel() const;


	public:

		//- Runtime type information
		//TypeName("BrownianMotion");
		static const char* typeName_() { return "BrownianMotion"; }
		static FoamBrownianMotionForce_EXPORT const ::tnbLib::word typeName;
		static FoamBrownianMotionForce_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from mesh
		BrownianMotionForce
		(
			CloudType& owner,
			const fvMesh& mesh,
			const dictionary& dict
		);

		//- Construct copy
		BrownianMotionForce(const BrownianMotionForce& bmf);

		//- Construct and return a clone
		virtual autoPtr<ParticleForce<CloudType>> clone() const
		{
			return autoPtr<ParticleForce<CloudType>>
				(
					new BrownianMotionForce<CloudType>(*this)
					);
		}


		//- Destructor
		virtual ~BrownianMotionForce();


		// Member Functions

			// Access

				//- Return const access to the molecular free path length [m]
		inline scalar lambda() const;

		//- Return const access to the turbulence flag
		inline bool turbulence() const;


		// Evaluation

			//- Cache fields
		virtual void cacheFields(const bool store);

		//- Calculate the coupled force
		virtual forceSuSp calcCoupled
		(
			const typename CloudType::parcelType& p,
			const typename CloudType::parcelType::trackingData& td,
			const scalar dt,
			const scalar mass,
			const scalar Re,
			const scalar muc
		) const;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <BrownianMotionForceI.hxx>
#include <BrownianMotionForce_Imp.hxx>

//#ifdef NoRepository
//#include <BrownianMotionForce.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_BrownianMotionForce_Header
