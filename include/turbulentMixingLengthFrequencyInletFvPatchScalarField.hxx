#pragma once
#ifndef _turbulentMixingLengthFrequencyInletFvPatchScalarField_Header
#define _turbulentMixingLengthFrequencyInletFvPatchScalarField_Header

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
	tnbLib::turbulentMixingLengthFrequencyInletFvPatchScalarField

Description
	This boundary condition provides a turbulence specific dissipation,
	\f$\omega\f$ (omega) inlet condition based on a specified mixing length.
	The patch values are calculated using:

		\f[
			\omega_p = \frac{k^{0.5}}{C_{\mu}^{0.25} L}
		\f]

	where

	\vartable
		\omega_p | patch omega values
		C_{\mu} | Model coefficient, set to 0.09
		k       | turbulence kinetic energy
		L       | length scale
	\endvartable

Usage
	\table
		Property     | Description             | Required    | Default value
		mixingLength | Length scale [m]        | yes         |
		phi          | flux field name         | no          | phi
		k            | turbulence kinetic energy field name | no | k
	\endtable

	Example of the boundary condition specification:
	\verbatim
	<patchName>
	{
		type            turbulentMixingLengthFrequencyInlet;
		mixingLength    0.005;
		value           uniform 200;   // placeholder
	}
	\endverbatim

Note
	In the event of reverse flow, a zero-gradient condition is applied

See also
	tnbLib::inletOutletFvPatchField


SourceFiles
	turbulentMixingLengthFrequencyInletFvPatchScalarField.C

\*---------------------------------------------------------------------------*/

#include <inletOutletFvPatchFields.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
		Class turbulentMixingLengthFrequencyInletFvPatchScalarField Declaration
	\*---------------------------------------------------------------------------*/

	class turbulentMixingLengthFrequencyInletFvPatchScalarField
		:
		public inletOutletFvPatchScalarField
	{
		// Private Data

			//- Turbulent length scale
		scalar mixingLength_;

		//- Name of the turbulent kinetic energy field
		word kName_;


	public:

		//- Runtime type information
		//TypeName("turbulentMixingLengthFrequencyInlet");
		static const char* typeName_() { return "turbulentMixingLengthFrequencyInlet"; }
		static FoamTurbulence_EXPORT const ::tnbLib::word typeName;
		static FoamTurbulence_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from patch and internal field
		FoamTurbulence_EXPORT turbulentMixingLengthFrequencyInletFvPatchScalarField
		(
			const fvPatch&,
			const DimensionedField<scalar, volMesh>&
		);

		//- Construct from patch, internal field and dictionary
		FoamTurbulence_EXPORT turbulentMixingLengthFrequencyInletFvPatchScalarField
		(
			const fvPatch&,
			const DimensionedField<scalar, volMesh>&,
			const dictionary&
		);

		//- Construct by mapping given
		//  turbulentMixingLengthFrequencyInletFvPatchScalarField
		//  onto a new patch
		FoamTurbulence_EXPORT turbulentMixingLengthFrequencyInletFvPatchScalarField
		(
			const turbulentMixingLengthFrequencyInletFvPatchScalarField&,
			const fvPatch&,
			const DimensionedField<scalar, volMesh>&,
			const fvPatchFieldMapper&
		);

		//- Copy constructor
		FoamTurbulence_EXPORT turbulentMixingLengthFrequencyInletFvPatchScalarField
		(
			const turbulentMixingLengthFrequencyInletFvPatchScalarField&
		);

		//- Construct and return a clone
		virtual tmp<fvPatchScalarField> clone() const
		{
			return tmp<fvPatchScalarField>
				(
					new turbulentMixingLengthFrequencyInletFvPatchScalarField
					(
						*this
					)
					);
		}

		//- Copy constructor setting internal field reference
		FoamTurbulence_EXPORT turbulentMixingLengthFrequencyInletFvPatchScalarField
		(
			const turbulentMixingLengthFrequencyInletFvPatchScalarField&,
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
					new turbulentMixingLengthFrequencyInletFvPatchScalarField
					(
						*this,
						iF
					)
					);
		}


		// Member Functions

			//- Update the coefficients associated with the patch field
		FoamTurbulence_EXPORT virtual void updateCoeffs();

		//- Write
		FoamTurbulence_EXPORT virtual void write(Ostream&) const;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_turbulentMixingLengthFrequencyInletFvPatchScalarField_Header
