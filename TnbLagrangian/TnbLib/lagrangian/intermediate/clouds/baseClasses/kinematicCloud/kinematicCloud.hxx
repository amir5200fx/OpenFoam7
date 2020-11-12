#pragma once
#ifndef _kinematicCloud_Header
#define _kinematicCloud_Header

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
	tnbLib::kinematicCloud

Description
	Virtual abstract base class for templated KinematicCloud

SourceFiles
	kinematicCloud.H

\*---------------------------------------------------------------------------*/

#include <typeInfo.hxx>
#include <volFieldsFwd.hxx>

#include <tmp.hxx>  // added by amir

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
						   Class kinematicCloud Declaration
	\*---------------------------------------------------------------------------*/

	class kinematicCloud
	{
	public:

		//- Runtime type information
		//TypeName("kinematicCloud");
		static const char* typeName_() { return "kinematicCloud"; }
		static FoamLagrangian_EXPORT const ::tnbLib::word typeName;
		static FoamLagrangian_EXPORT int debug;
		virtual const word& type() const { return typeName; };

		// Constructors

			//- Null constructor
		FoamLagrangian_EXPORT kinematicCloud();

		//- Disallow default bitwise copy construction
		kinematicCloud(const kinematicCloud&) = delete;


		//- Destructor
		FoamLagrangian_EXPORT virtual ~kinematicCloud();


		// Member Functions

			// Check

				//-  Number of parcels
		FoamLagrangian_EXPORT virtual label nParcels() const = 0;

		//- Total mass in system
		FoamLagrangian_EXPORT virtual scalar massInSystem() const = 0;

		//- Total linear momentum of the system
		FoamLagrangian_EXPORT virtual vector linearMomentumOfSystem() const = 0;

		//- Total linear kinetic energy in the system
		FoamLagrangian_EXPORT virtual scalar linearKineticEnergyOfSystem() const = 0;

		//- Mean diameter Dij
		FoamLagrangian_EXPORT virtual scalar Dij(const label i, const label j) const = 0;

		//- Max diameter
		FoamLagrangian_EXPORT virtual scalar Dmax() const = 0;


		// Fields

			//- Volume swept rate of parcels per cell
		FoamLagrangian_EXPORT virtual const tmp<volScalarField> vDotSweep() const = 0;

		//- Return the particle volume fraction field
		//  Note: for particles belonging to this cloud only
		FoamLagrangian_EXPORT virtual const tmp<volScalarField> theta() const = 0;

		//- Return the particle mass fraction field
		//  Note: for particles belonging to this cloud only
		FoamLagrangian_EXPORT virtual const tmp<volScalarField> alpha() const = 0;

		//- Return the particle effective density field
		//  Note: for particles belonging to this cloud only
		FoamLagrangian_EXPORT virtual const tmp<volScalarField> rhoEff() const = 0;


		// Member Operators

			//- Disallow default bitwise assignment
		FoamLagrangian_EXPORT void operator=(const kinematicCloud&) = delete;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_kinematicCloud_Header
