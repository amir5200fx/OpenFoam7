#pragma once
#ifndef _turbulentIntensityKineticEnergyInletFvPatchScalarField_Header
#define _turbulentIntensityKineticEnergyInletFvPatchScalarField_Header

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
	tnbLib::turbulentIntensityKineticEnergyInletFvPatchScalarField

Description
	This boundary condition provides a turbulent kinetic energy condition,
	based on user-supplied turbulence intensity, defined as a fraction of the
	mean velocity:

		\f[
			k_p = 1.5 (I |U|)^2
		\f]

	where

	\vartable
		k_p     | kinetic energy at the patch
		I       | turbulence intensity
		U       | velocity field
	\endvartable

	In the event of reverse flow, a zero-gradient condition is applied.

Usage
	\table
		Property     | Description             | Required    | Default value
		intensity    | fraction of mean field [0-1] | yes    |
		U            | velocity field name     | no          | U
		phi          | flux field name         | no          | phi
	\endtable

	Example of the boundary condition specification:
	\verbatim
	<patchName>
	{
		type        turbulentIntensityKineticEnergyInlet;
		intensity   0.05;           // 5% turbulence
		value       uniform 1;      // placeholder
	}
	\endverbatim

See also
	tnbLib::inletOutletFvPatchField

SourceFiles
	turbulentIntensityKineticEnergyInletFvPatchScalarField.C

\*---------------------------------------------------------------------------*/

#include <inletOutletFvPatchFields.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
	   Class turbulentIntensityKineticEnergyInletFvPatchScalarField Declaration
	\*---------------------------------------------------------------------------*/

	class turbulentIntensityKineticEnergyInletFvPatchScalarField
		:
		public inletOutletFvPatchScalarField
	{
		// Private Data

			//- Turbulent intensity as fraction of mean velocity
		scalar intensity_;

		//- Name of the velocity field
		word UName_;


	public:

		//- Runtime type information
		/*TypeName("turbulentIntensityKineticEnergyInlet");*/
		static const char* typeName_() { return "turbulentIntensityKineticEnergyInlet"; }
		static FoamFiniteVolume_EXPORT const ::tnbLib::word typeName;
		static FoamFiniteVolume_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from patch and internal field
		FoamFiniteVolume_EXPORT turbulentIntensityKineticEnergyInletFvPatchScalarField
		(
			const fvPatch&,
			const DimensionedField<scalar, volMesh>&
		);

		//- Construct from patch, internal field and dictionary
		FoamFiniteVolume_EXPORT turbulentIntensityKineticEnergyInletFvPatchScalarField
		(
			const fvPatch&,
			const DimensionedField<scalar, volMesh>&,
			const dictionary&
		);

		//- Construct by mapping given
		//  turbulentIntensityKineticEnergyInletFvPatchScalarField
		//  onto a new patch
		FoamFiniteVolume_EXPORT turbulentIntensityKineticEnergyInletFvPatchScalarField
		(
			const turbulentIntensityKineticEnergyInletFvPatchScalarField&,
			const fvPatch&,
			const DimensionedField<scalar, volMesh>&,
			const fvPatchFieldMapper&
		);

		//- Copy constructor
		FoamFiniteVolume_EXPORT turbulentIntensityKineticEnergyInletFvPatchScalarField
		(
			const turbulentIntensityKineticEnergyInletFvPatchScalarField&
		);

		//- Construct and return a clone
		virtual tmp<fvPatchScalarField> clone() const
		{
			return tmp<fvPatchScalarField>
				(
					new turbulentIntensityKineticEnergyInletFvPatchScalarField
					(
						*this
					)
					);
		}

		//- Copy constructor setting internal field reference
		FoamFiniteVolume_EXPORT turbulentIntensityKineticEnergyInletFvPatchScalarField
		(
			const turbulentIntensityKineticEnergyInletFvPatchScalarField&,
			const DimensionedField<scalar, volMesh>&
		);

		//- Construct and return a clone setting internal field reference
		virtual tmp<fvPatchScalarField> clone
		(
			const DimensionedField<scalar, volMesh>& iF
		) const
		{
			return tmp<fvPatchScalarField>
				(
					new turbulentIntensityKineticEnergyInletFvPatchScalarField
					(
						*this,
						iF
					)
					);
		}


		// Member Functions

		//- Update the coefficients associated with the patch field
		FoamFiniteVolume_EXPORT virtual void updateCoeffs();

		//- Write
		FoamFiniteVolume_EXPORT virtual void write(Ostream&) const;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_turbulentIntensityKineticEnergyInletFvPatchScalarField_Header
