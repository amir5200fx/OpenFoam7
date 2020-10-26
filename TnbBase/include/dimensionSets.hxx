#pragma once
#ifndef _dimensionSets_Header
#define _dimensionSets_Header

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

Global
	dimensionSets

Description
	Useful dimension sets

SourceFiles
	dimensionSets.C

\*---------------------------------------------------------------------------*/

#include <scalarMatrices.hxx>
#include <dimensionedScalarFwd.hxx>
#include <PtrList.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	FoamBase_EXPORT extern const dimensionSet dimless;

	FoamBase_EXPORT extern const dimensionSet dimMass;
	FoamBase_EXPORT extern const dimensionSet dimLength;
	FoamBase_EXPORT extern const dimensionSet dimTime;
	FoamBase_EXPORT extern const dimensionSet dimTemperature;
	FoamBase_EXPORT extern const dimensionSet dimMoles;
	FoamBase_EXPORT extern const dimensionSet dimCurrent;
	FoamBase_EXPORT extern const dimensionSet dimLuminousIntensity;

	FoamBase_EXPORT extern const dimensionSet dimArea;
	FoamBase_EXPORT extern const dimensionSet dimVolume;
	FoamBase_EXPORT extern const dimensionSet dimVol;

	FoamBase_EXPORT extern const dimensionSet dimDensity;
	FoamBase_EXPORT extern const dimensionSet dimForce;
	FoamBase_EXPORT extern const dimensionSet dimEnergy;
	FoamBase_EXPORT extern const dimensionSet dimPower;

	FoamBase_EXPORT extern const dimensionSet dimVelocity;
	FoamBase_EXPORT extern const dimensionSet dimAcceleration;
	FoamBase_EXPORT extern const dimensionSet dimPressure;
	FoamBase_EXPORT extern const dimensionSet dimCompressibility;
	FoamBase_EXPORT extern const dimensionSet dimGasConstant;
	FoamBase_EXPORT extern const dimensionSet dimSpecificHeatCapacity;
	FoamBase_EXPORT extern const dimensionSet dimViscosity;
	FoamBase_EXPORT extern const dimensionSet dimDynamicViscosity;


	class dimensionSets
	{
		// Private Data

			//- Set of dimensions
		PtrList<dimensionedScalar> units_;

		//- LU decomposition of dimensions
		scalarSquareMatrix conversion_;

		//- See above
		labelList conversionPivots_;

		//- Is LU decomposition valid
		bool valid_;

	public:

		// Constructors

			//- Construct from all units and set of units to use for inversion
			//  (writing)
		FoamBase_EXPORT dimensionSets
		(
			const HashTable<dimensionedScalar>&,
			const wordList& unitNames
		);

		// Member Functions

			//- Return the units
		const PtrList<dimensionedScalar>& units() const
		{
			return units_;
		}

		//- Is there a valid inverse of the selected unit
		bool valid() const
		{
			return valid_;
		}

		//- (if valid) obtain set of coefficients of unitNames
		FoamBase_EXPORT void coefficients(scalarField&) const;

	};


	//- Top level dictionary
	FoamBase_EXPORT dictionary& dimensionSystems();

	//- Set of all dimensions
	FoamBase_EXPORT const HashTable<dimensionedScalar>& unitSet();

	//- Set of units
	FoamBase_EXPORT const dimensionSets& writeUnitSet();


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_dimensionSets_Header
