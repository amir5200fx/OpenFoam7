#pragma once
#ifndef _interfaceProperties_Header
#define _interfaceProperties_Header

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
	tnbLib::interfaceProperties

Description
	Contains the interface properties.

	Properties to aid interFoam:
	-# Correct the alpha boundary condition for dynamic contact angle.
	-# Calculate interface curvature.

SourceFiles
	interfaceProperties.C

\*---------------------------------------------------------------------------*/

#include <IOdictionary.hxx>
#include <surfaceTensionModel.hxx>
#include <volFields.hxx>
#include <surfaceFields.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							   Class interfaceProperties Declaration
	\*---------------------------------------------------------------------------*/

	class interfaceProperties
	{
		// Private Data

			//- Keep a reference to the transportProperties dictionary
		const dictionary& transportPropertiesDict_;

		//- Compression coefficient
		scalar cAlpha_;

		//- Surface tension
		autoPtr<surfaceTensionModel> sigmaPtr_;

		//- Stabilisation for normalisation of the interface normal
		const dimensionedScalar deltaN_;

		const volScalarField& alpha1_;
		const volVectorField& U_;
		surfaceScalarField nHatf_;
		volScalarField K_;


		// Private Member Functions

			//- Correction for the boundary condition on the unit normal nHat on
			//  walls to produce the correct contact dynamic angle
			//  calculated from the component of U parallel to the wall
		FoamTransportModels_EXPORT void correctContactAngle
		(
			surfaceVectorField::Boundary& nHat,
			const surfaceVectorField::Boundary& gradAlphaf
		) const;

		//- Re-calculate the interface curvature
		FoamTransportModels_EXPORT void calculateK();


	public:

		//- Conversion factor for degrees into radians
		static FoamTransportModels_EXPORT const scalar convertToRad;


		// Constructors

			//- Construct from volume fraction field gamma and IOdictionary
		FoamTransportModels_EXPORT interfaceProperties
		(
			const volScalarField& alpha1,
			const volVectorField& U,
			const IOdictionary&
		);

		//- Disallow default bitwise copy construction
		FoamTransportModels_EXPORT interfaceProperties(const interfaceProperties&) = delete;


		// Member Functions

		scalar cAlpha() const
		{
			return cAlpha_;
		}

		const dimensionedScalar& deltaN() const
		{
			return deltaN_;
		}

		const surfaceScalarField& nHatf() const
		{
			return nHatf_;
		}

		FoamTransportModels_EXPORT tmp<volScalarField> sigmaK() const;

		FoamTransportModels_EXPORT tmp<surfaceScalarField> surfaceTensionForce() const;

		//- Indicator of the proximity of the interface
		//  Field values are 1 near and 0 away for the interface.
		FoamTransportModels_EXPORT tmp<volScalarField> nearInterface() const;

		FoamTransportModels_EXPORT void correct();

		//- Read transportProperties dictionary
		FoamTransportModels_EXPORT bool read();


		// Member Operators

			//- Disallow default bitwise assignment
		FoamTransportModels_EXPORT void operator=(const interfaceProperties&) = delete;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_interfaceProperties_Header
