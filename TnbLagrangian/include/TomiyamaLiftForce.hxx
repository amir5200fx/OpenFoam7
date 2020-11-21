#pragma once
#ifndef _TomiyamaLiftForce_Header
#define _TomiyamaLiftForce_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2012-2018 OpenFOAM Foundation
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
	tnbLib::TomiyamaLiftForce

Description
	Tomiyama particle lift force model applicable to deformable bubbles.

SourceFiles
	TomiyamaLiftForce.C

\*---------------------------------------------------------------------------*/

#include <LiftForce.hxx>

#ifdef FoamLagrangian_EXPORT_DEFINE
#define FoamTomiyamaLiftForce_EXPORT __declspec(dllexport)
#else
#ifdef FoamTomiyamaLiftForce_EXPORT_DEFINE
#define FoamTomiyamaLiftForce_EXPORT __declspec(dllexport)
#else
#define FoamTomiyamaLiftForce_EXPORT __declspec(dllimport)
#endif
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							Class TomiyamaLiftForce Declaration
	\*---------------------------------------------------------------------------*/

	template<class CloudType>
	class TomiyamaLiftForce
		:
		public LiftForce<CloudType>
	{
	protected:

		// Protected data

			//- Surface tension
		scalar sigma_;


		// Protected Member Functions

			//- Calculate the lift coefficient
		virtual scalar Cl
		(
			const typename CloudType::parcelType& p,
			const typename CloudType::parcelType::trackingData& td,
			const vector& curlUc,
			const scalar Re,
			const scalar muc
		) const;


	public:

		//- Runtime type information
		//TypeName("TomiyamaLift");
		static const char* typeName_() { return "TomiyamaLift"; }
		static FoamTomiyamaLiftForce_EXPORT const ::tnbLib::word typeName;
		static FoamTomiyamaLiftForce_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from mesh
		TomiyamaLiftForce
		(
			CloudType& owner,
			const fvMesh& mesh,
			const dictionary& dict,
			const word& forceType = typeName
		);

		//- Construct copy
		TomiyamaLiftForce(const TomiyamaLiftForce& lf);

		//- Construct and return a clone
		virtual autoPtr<ParticleForce<CloudType>> clone() const
		{
			return autoPtr<ParticleForce<CloudType>>
				(
					new TomiyamaLiftForce<CloudType>(*this)
					);
		}


		//- Destructor
		virtual ~TomiyamaLiftForce();
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <TomiyamaLiftForceI.hxx>

//#ifdef NoRepository
//#include <TomiyamaLiftForce.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_TomiyamaLiftForce_Header
