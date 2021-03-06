#pragma once
#ifndef _NoBinaryCollision_Header
#define _NoBinaryCollision_Header

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
	tnbLib::NoBinaryCollision

Description
	No collison BinaryCollision Model

\*---------------------------------------------------------------------------*/

#include <BinaryCollisionModel.hxx>

#ifdef FoamLagrangian_EXPORT_DEFINE
#define FoamNoBinaryCollision_EXPORT __declspec(dllexport)
#else
#ifdef FoamNoBinaryCollision_EXPORT_DEFINE
#define FoamNoBinaryCollision_EXPORT __declspec(dllexport)
#else
#define FoamNoBinaryCollision_EXPORT __declspec(dllimport)
#endif
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	/*---------------------------------------------------------------------------*\
						  Class NoBinaryCollision Declaration
	\*---------------------------------------------------------------------------*/

	template<class CloudType>
	class NoBinaryCollision
		:
		public BinaryCollisionModel<CloudType>
	{
	public:

		//- Runtime type information
		//TypeName("none");
		static const char* typeName_() { return "none"; }
		static FoamNoBinaryCollision_EXPORT const ::tnbLib::word typeName;
		static FoamNoBinaryCollision_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from dictionary
		NoBinaryCollision
		(
			const dictionary& dict,
			CloudType& cloud
		);


		//- Destructor
		virtual ~NoBinaryCollision();


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

#include <NoBinaryCollisionI.hxx>

//#ifdef NoRepository
//#include <NoBinaryCollision.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_NoBinaryCollision_Header
