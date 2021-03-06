#pragma once
#ifndef _VirtualMassForce_Header
#define _VirtualMassForce_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2012-2019 OpenFOAM Foundation
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
	tnbLib::VirtualMassForce

Description
	Calculates particle virtual mass force

SourceFiles
	VirtualMassForce.C

\*---------------------------------------------------------------------------*/

#include <PressureGradientForce.hxx>

#ifdef FoamLagrangian_EXPORT_DEFINE
#define FoamVirtualMassForce_EXPORT __declspec(dllexport)
#else
#ifdef FoamVirtualMassForce_EXPORT_DEFINE
#define FoamVirtualMassForce_EXPORT __declspec(dllexport)
#else
#define FoamVirtualMassForce_EXPORT __declspec(dllimport)
#endif
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
						  Class VirtualMassForce Declaration
	\*---------------------------------------------------------------------------*/

	template<class CloudType>
	class VirtualMassForce
		:
		public PressureGradientForce<CloudType>
	{
		// Private Data

			//- Virtual mass coefficient - typically 0.5
		scalar Cvm_;


	public:

		//- Runtime type information
		//TypeName("virtualMass");
		static const char* typeName_() { return "virtualMass"; }
		static FoamVirtualMassForce_EXPORT const ::tnbLib::word typeName;
		static FoamVirtualMassForce_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from mesh
		VirtualMassForce
		(
			CloudType& owner,
			const fvMesh& mesh,
			const dictionary& dict,
			const word& forceType = typeName
		);

		//- Construct copy
		VirtualMassForce(const VirtualMassForce& pgf);

		//- Construct and return a clone
		virtual autoPtr<ParticleForce<CloudType>> clone() const
		{
			return autoPtr<ParticleForce<CloudType>>
				(
					new VirtualMassForce<CloudType>(*this)
					);
		}


		//- Destructor
		virtual ~VirtualMassForce();


		// Member Functions

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

#include <VirtualMassForceI.hxx>

//#ifdef NoRepository
//#include <VirtualMassForce.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_VirtualMassForce_Header
