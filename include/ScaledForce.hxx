#pragma once
#ifndef _ScaledForce_Header
#define _ScaledForce_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2018-2019 OpenFOAM Foundation
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
	tnbLib::ScaledForce

Description
	Particle force model scaled by a constant value

\*---------------------------------------------------------------------------*/

#include <ParticleForce.hxx>

#ifdef FoamLagrangian_EXPORT_DEFINE
#define FoamScaledForce_EXPORT __declspec(dllexport)
#else
#ifdef FoamScaledForce_EXPORT_DEFINE
#define FoamScaledForce_EXPORT __declspec(dllexport)
#else
#define FoamScaledForce_EXPORT __declspec(dllimport)
#endif
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	/*---------------------------------------------------------------------------*\
						   Class ScaledForce Declaration
	\*---------------------------------------------------------------------------*/

	template<class CloudType>
	class ScaledForce
		:
		public ParticleForce<CloudType>
	{
		// Private Data

			//- Model to scale
		autoPtr<ParticleForce<CloudType>> model_;

		//- Scale factor
		const scalar factor_;


		// Private Member Functions

			//- Create the dictionary for the sub-model
		dictionary modelDict(const dictionary& dict) const;


	public:

		//- Runtime type information
		//TypeName("scaled");
		static const char* typeName_() { return "scaled"; }
		static FoamScaledForce_EXPORT const ::tnbLib::word typeName;
		static FoamScaledForce_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from mesh
		ScaledForce
		(
			CloudType& owner,
			const fvMesh& mesh,
			const dictionary& dict
		);

		//- Construct copy
		ScaledForce(const ScaledForce<CloudType>& df);

		//- Construct and return a clone
		virtual autoPtr<ParticleForce<CloudType>> clone() const
		{
			return autoPtr<ParticleForce<CloudType>>
				(
					new ScaledForce<CloudType>(*this)
					);
		}


		//- Destructor
		virtual ~ScaledForce();


		// Member Functions

			// Evaluation

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

		//- Calculate the non-coupled force
		virtual forceSuSp calcNonCoupled
		(
			const typename CloudType::parcelType& p,
			const typename CloudType::parcelType::trackingData& td,
			const scalar dt,
			const scalar mass,
			const scalar Re,
			const scalar muc
		) const;

		//- Return the added mass
		virtual scalar massAdd
		(
			const typename CloudType::parcelType& p,
			const typename CloudType::parcelType::trackingData& td,
			const scalar mass
		) const;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <ScaledForceI.hxx>

//#ifdef NoRepository
//#include <ScaledForce.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_ScaledForce_Header
