#pragma once
#ifndef _NonInertialFrameForce_Header
#define _NonInertialFrameForce_Header

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
	tnbLib::NonInertialFrameForce

Description
	Calculates particle non-inertial reference frame force.  Variable names as
	from Landau and Lifshitz, Mechanics, 3rd Ed, p126-129.

SourceFiles
	NonInertialFrameForce.C

\*---------------------------------------------------------------------------*/

#include <ParticleForce.hxx>

#ifdef FoamLagrangian_EXPORT_DEFINE
#define FoamNonInertialFrameForce_EXPORT __declspec(dllexport)
#else
#ifdef FoamNonInertialFrameForce_EXPORT_DEFINE
#define FoamNonInertialFrameForce_EXPORT __declspec(dllexport)
#else
#define FoamNonInertialFrameForce_EXPORT __declspec(dllimport)
#endif
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	class fvMesh;

	/*---------------------------------------------------------------------------*\
					  Class NonInertialFrameForce Declaration
	\*---------------------------------------------------------------------------*/

	template<class CloudType>
	class NonInertialFrameForce
		:
		public ParticleForce<CloudType>
	{
		// Private Data

			//- Name of the linear acceleration field
		word WName_;

		//- The linear acceleration of the reference frame
		vector W_;

		//- Name of the angular velocity field
		word omegaName_;

		//- The angular velocity of the reference frame
		vector omega_;

		//- Name of the angular acceleration field
		word omegaDotName_;

		//- The angular acceleration of the reference frame
		vector omegaDot_;

		//- Name of the centre of rotation field
		word centreOfRotationName_;

		//- The centre of rotation of the reference frame
		vector centreOfRotation_;


	public:

		//- Runtime type information
		//TypeName("nonInertialFrame");
		static const char* typeName_() { return "nonInertialFrame"; }
		static FoamNonInertialFrameForce_EXPORT const ::tnbLib::word typeName;
		static FoamNonInertialFrameForce_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from mesh
		NonInertialFrameForce
		(
			CloudType& owner,
			const fvMesh& mesh,
			const dictionary& dict
		);

		//- Construct copy
		NonInertialFrameForce(const NonInertialFrameForce& niff);

		//- Construct and return a clone
		virtual autoPtr<ParticleForce<CloudType>> clone() const
		{
			return autoPtr<ParticleForce<CloudType>>
				(
					new ParticleForce<CloudType>(*this)
					);
		}


		//- Destructor
		virtual ~NonInertialFrameForce();


		// Member Functions

			// Access

				//- Return the linear acceleration of the reference frame
		inline const vector& W() const;

		//- Return the angular velocity of the reference frame
		inline const vector& omega() const;

		//- Return the angular acceleration of the reference frame
		inline const vector& omegaDot() const;

		//- Return the centre of rotation of the reference frame
		inline const vector& centreOfRotation() const;


		// Evaluation

			//- Cache fields
		virtual void cacheFields(const bool store);

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
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <NonInertialFrameForceI.hxx>
#include <NonInertialFrameForce_Imp.hxx>

//#ifdef NoRepository
//#include <NonInertialFrameForce.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //


#endif // !_NonInertialFrameForce_Header
