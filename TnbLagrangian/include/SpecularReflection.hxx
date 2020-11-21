#pragma once
#ifndef _SpecularReflection_Header
#define _SpecularReflection_Header

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
	tnbLib::SpecularReflection

Description
	Reversing the wall-normal component of the particle velocity

\*---------------------------------------------------------------------------*/

#include <WallInteractionModel.hxx>

#ifdef FoamLagrangian_EXPORT_DEFINE
#define FoamSpecularReflection_EXPORT __declspec(dllexport)
#else
#ifdef FoamSpecularReflection_EXPORT_DEFINE
#define FoamSpecularReflection_EXPORT __declspec(dllexport)
#else
#define FoamSpecularReflection_EXPORT __declspec(dllimport)
#endif
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	/*---------------------------------------------------------------------------*\
						  Class SpecularReflection Declaration
	\*---------------------------------------------------------------------------*/

	template<class CloudType>
	class SpecularReflection
		:
		public WallInteractionModel<CloudType>
	{
	public:

		//- Runtime type information
		//TypeName("SpecularReflection");
		static const char* typeName_() { return "SpecularReflection"; }
		static FoamSpecularReflection_EXPORT const ::tnbLib::word typeName;
		static FoamSpecularReflection_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from dictionary
		SpecularReflection
		(
			const dictionary& dict,
			CloudType& cloud
		);


		//- Destructor
		virtual ~SpecularReflection();


		// Member Functions

			//- Apply wall correction
		virtual void correct(typename CloudType::parcelType& p);
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <SpecularReflectionI.hxx>

//#ifdef NoRepository
//#include <SpecularReflection.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_SpecularReflection_Header
