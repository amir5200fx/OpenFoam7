#pragma once
#ifndef _SaffmanMeiLiftForce_Header
#define _SaffmanMeiLiftForce_Header

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
	tnbLib::SaffmanMeiLiftForce

Description
	Saffman-Mei particle lift force model applicable to spherical particles.

SourceFiles
	SaffmanMeiLiftForce.C

\*---------------------------------------------------------------------------*/

#include <LiftForce.hxx>

#ifdef FoamLagrangian_EXPORT_DEFINE
#define FoamSaffmanMeiLiftForce_EXPORT __declspec(dllexport)
#else
#ifdef FoamSaffmanMeiLiftForce_EXPORT_DEFINE
#define FoamSaffmanMeiLiftForce_EXPORT __declspec(dllexport)
#else
#define FoamSaffmanMeiLiftForce_EXPORT __declspec(dllimport)
#endif
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
						 Class SaffmanMeiLiftForce Declaration
	\*---------------------------------------------------------------------------*/

	template<class CloudType>
	class SaffmanMeiLiftForce
		:
		public LiftForce<CloudType>
	{
	protected:

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
		//TypeName("SaffmanMeiLiftForce");
		static const char* typeName_() { return "SaffmanMeiLiftForce"; }
		static FoamSaffmanMeiLiftForce_EXPORT const ::tnbLib::word typeName;
		static FoamSaffmanMeiLiftForce_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from mesh
		SaffmanMeiLiftForce
		(
			CloudType& owner,
			const fvMesh& mesh,
			const dictionary& dict,
			const word& forceType = typeName
		);

		//- Construct copy
		SaffmanMeiLiftForce(const SaffmanMeiLiftForce& lf);

		//- Construct and return a clone
		virtual autoPtr<ParticleForce<CloudType>> clone() const
		{
			return autoPtr<ParticleForce<CloudType>>
				(
					new SaffmanMeiLiftForce<CloudType>(*this)
					);
		}


		//- Destructor
		virtual ~SaffmanMeiLiftForce();
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <SaffmanMeiLiftForceI.hxx>

//#ifdef NoRepository
//#include <SaffmanMeiLiftForce.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_SaffmanMeiLiftForce_Header
