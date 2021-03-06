#pragma once
#ifndef _MixedDiffuseSpecular_Header
#define _MixedDiffuseSpecular_Header

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
	tnbLib::MixedDiffuseSpecular

Description
	Wall interaction setting microscopic velocity to a random one
	drawn from a Maxwellian distribution corresponding to a specified
	temperature for a specified fraction of collisions, and reversing
	the wall-normal component of the particle velocity for the
	remainder.

\*---------------------------------------------------------------------------*/

#include <WallInteractionModel.hxx>

#ifdef FoamLagrangian_EXPORT_DEFINE
#define FoamMixedDiffuseSpecular_EXPORT __declspec(dllexport)
#else
#ifdef FoamMixedDiffuseSpecular_EXPORT_DEFINE
#define FoamMixedDiffuseSpecular_EXPORT __declspec(dllexport)
#else
#define FoamMixedDiffuseSpecular_EXPORT __declspec(dllimport)
#endif
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	/*---------------------------------------------------------------------------*\
						Class MixedDiffuseSpecular Declaration
	\*---------------------------------------------------------------------------*/

	template<class CloudType>
	class MixedDiffuseSpecular
		:
		public WallInteractionModel<CloudType>
	{
		// Private Data

			//- Fraction of wall interactions that are diffuse
		scalar diffuseFraction_;


	public:

		//- Runtime type information
		//TypeName("MixedDiffuseSpecular");
		static const char* typeName_() { return "MixedDiffuseSpecular"; }
		static FoamMixedDiffuseSpecular_EXPORT const ::tnbLib::word typeName;
		static FoamMixedDiffuseSpecular_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from dictionary
		MixedDiffuseSpecular
		(
			const dictionary& dict,
			CloudType& cloud
		);


		//- Destructor
		virtual ~MixedDiffuseSpecular();


		// Member Functions

			//- Apply wall correction
		virtual void correct(typename CloudType::parcelType& p);
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <MixedDiffuseSpecularI.hxx>

//#ifdef NoRepository
//#include <MixedDiffuseSpecular.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_MixedDiffuseSpecular_Header
