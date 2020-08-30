#pragma once
#ifndef _LarsenBorgnakkeVariableHardSphere_Header
#define _LarsenBorgnakkeVariableHardSphere_Header

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
	tnbLib::LarsenBorgnakkeVariableHardSphere

Description
	Variable Hard Sphere BinaryCollision Model with Larsen Borgnakke internal
	energy redistribution.  Based on the INELRS subroutine in Bird's DSMC0R.FOR

\*---------------------------------------------------------------------------*/

#include <BinaryCollisionModel.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	/*---------------------------------------------------------------------------*\
						  Class LarsenBorgnakkeVariableHardSphere Declaration
	\*---------------------------------------------------------------------------*/

	template<class CloudType>
	class LarsenBorgnakkeVariableHardSphere
		:
		public BinaryCollisionModel<CloudType>
	{
		// Private Data

			//- Reference temperature
		const scalar Tref_;

		//- Relaxation collision number
		const scalar relaxationCollisionNumber_;


		// Private Member Functions

			//- Calculate the energy ratio for distribution to internal degrees of
			// freedom
		scalar energyRatio
		(
			scalar ChiA,
			scalar ChiB
		);


	public:

		//- Runtime type information
		TypeName("LarsenBorgnakkeVariableHardSphere");


		// Constructors

			//- Construct from dictionary
		LarsenBorgnakkeVariableHardSphere
		(
			const dictionary& dict,
			CloudType& cloud
		);


		//- Destructor
		virtual ~LarsenBorgnakkeVariableHardSphere();


		// Member Functions

			//- Flag to indicate whether model activates collision model
		virtual bool active() const;

		//- Return the collision cross section * relative velocity product
		virtual scalar sigmaTcR
		(
			const typename CloudType::parcelType& pP,
			const typename CloudType::parcelType& pQ
		) const;

		//- Apply collision
		virtual void collide
		(
			typename CloudType::parcelType& pP,
			typename CloudType::parcelType& pQ
		);
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#ifdef NoRepository
#include <LarsenBorgnakkeVariableHardSphere.cxx>
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_LarsenBorgnakkeVariableHardSphere_Header
