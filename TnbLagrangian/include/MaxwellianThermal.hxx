#pragma once
#ifndef _MaxwellianThermal_Header
#define _MaxwellianThermal_Header

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
	tnbLib::MaxwellianThermal

Description
	Wall interaction setting microscopic velocity to a random one
	drawn from a Maxwellian distribution corresponding to a specified
	temperature

\*---------------------------------------------------------------------------*/

#include <WallInteractionModel.hxx>

#ifdef FoamLagrangian_EXPORT_DEFINE
#define FoamMaxwellianThermal_EXPORT __declspec(dllexport)
#else
#ifdef FoamMaxwellianThermal_EXPORT_DEFINE
#define FoamMaxwellianThermal_EXPORT __declspec(dllexport)
#else
#define FoamMaxwellianThermal_EXPORT __declspec(dllimport)
#endif
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	/*---------------------------------------------------------------------------*\
						  Class MaxwellianThermal Declaration
	\*---------------------------------------------------------------------------*/

	template<class CloudType>
	class MaxwellianThermal
		:
		public WallInteractionModel<CloudType>
	{
	public:

		//- Runtime type information
		//TypeName("MaxwellianThermal");
		static const char* typeName_() { return "MaxwellianThermal"; }
		static FoamMaxwellianThermal_EXPORT const ::tnbLib::word typeName;
		static FoamMaxwellianThermal_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from dictionary
		MaxwellianThermal
		(
			const dictionary& dict,
			CloudType& cloud
		);


		//- Destructor
		virtual ~MaxwellianThermal();


		// Member Functions

			//- Apply wall correction
		virtual void correct(typename CloudType::parcelType& p);
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <MaxwellianThermalI.hxx>

//#ifdef NoRepository
//#include <MaxwellianThermal.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_MaxwellianThermal_Header
