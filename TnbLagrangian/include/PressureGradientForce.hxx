#pragma once
#ifndef _PressureGradientForce_Header
#define _PressureGradientForce_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2011-2018 OpenFOAM Foundation
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
	tnbLib::PressureGradientForce

Description
	Calculates particle pressure gradient force

SourceFiles
	PressureGradientForceI.H
	PressureGradientForce.C

\*---------------------------------------------------------------------------*/

#include <ParticleForce.hxx>
#include <volFields.hxx>
#include <interpolation.hxx>

#ifdef FoamLagrangian_EXPORT_DEFINE
#define FoamPressureGradientForce_EXPORT __declspec(dllexport)
#else
#ifdef FoamPressureGradientForce_EXPORT_DEFINE
#define FoamPressureGradientForce_EXPORT __declspec(dllexport)
#else
#define FoamPressureGradientForce_EXPORT __declspec(dllimport)
#endif
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
						Class PressureGradientForce Declaration
	\*---------------------------------------------------------------------------*/

	template<class CloudType>
	class PressureGradientForce
		:
		public ParticleForce<CloudType>
	{
	protected:

		// Protected data

			//- Name of velocity field
		const word UName_;

		//- Rate of change of carrier phase velocity interpolator
		autoPtr<interpolation<vector>> DUcDtInterpPtr_;


	public:

		//- Runtime type information
		//TypeName("pressureGradient");
		static const char* typeName_() { return "pressureGradient"; }
		static FoamPressureGradientForce_EXPORT const ::tnbLib::word typeName;
		static FoamPressureGradientForce_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from mesh
		PressureGradientForce
		(
			CloudType& owner,
			const fvMesh& mesh,
			const dictionary& dict,
			const word& forceType = typeName
		);

		//- Construct copy
		PressureGradientForce(const PressureGradientForce& pgf);

		//- Construct and return a clone
		virtual autoPtr<ParticleForce<CloudType>> clone() const
		{
			return autoPtr<ParticleForce<CloudType>>
				(
					new PressureGradientForce<CloudType>(*this)
					);
		}


		//- Destructor
		virtual ~PressureGradientForce();


		// Member Functions

			// Access

				//- Return the rate of change of carrier phase velocity interpolator
		inline const interpolation<vector>& DUcDtInterp() const;


		// Evaluation

			//- Cache fields
		virtual void cacheFields(const bool store);

		//- Calculate the non-coupled force
		virtual forceSuSp calcCoupled
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

#include <PressureGradientForceI.hxx>
#include <PressureGradientForce_Imp.hxx>

//#ifdef NoRepository
//#include <PressureGradientForce.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_PressureGradientForce_Header
