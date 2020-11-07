#pragma once
#ifndef _fixedFluxExtrapolatedPressureFvPatchScalarField_Header
#define _fixedFluxExtrapolatedPressureFvPatchScalarField_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2016-2019 OpenFOAM Foundation
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
	tnbLib::fixedFluxExtrapolatedPressureFvPatchScalarField

Description
	This boundary condition sets the pressure gradient to the provided value
	such that the flux on the boundary is that specified by the velocity
	boundary condition.

	Example of the boundary condition specification:
	\verbatim
	<patchName>
	{
		type            fixedFluxExtrapolatedPressure;
	}
	\endverbatim

See also
	tnbLib::fixedGradientFvPatchField

SourceFiles
	fixedFluxExtrapolatedPressureFvPatchScalarField.C

\*---------------------------------------------------------------------------*/

#include <fixedFluxPressureFvPatchScalarField.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
				 Class fixedFluxExtrapolatedPressureFvPatchScalarField Declaration
	\*---------------------------------------------------------------------------*/

	class fixedFluxExtrapolatedPressureFvPatchScalarField
		:
		public fixedFluxPressureFvPatchScalarField
	{

	public:

		//- Runtime type information
		//TypeName("fixedFluxExtrapolatedPressure");
		static const char* typeName_() { return "fixedFluxExtrapolatedPressure"; }
		static FoamFiniteVolume_EXPORT const ::tnbLib::word typeName;
		static FoamFiniteVolume_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from patch and internal field
		FoamFiniteVolume_EXPORT fixedFluxExtrapolatedPressureFvPatchScalarField
		(
			const fvPatch&,
			const DimensionedField<scalar, volMesh>&
		);

		//- Construct from patch, internal field and dictionary
		FoamFiniteVolume_EXPORT fixedFluxExtrapolatedPressureFvPatchScalarField
		(
			const fvPatch&,
			const DimensionedField<scalar, volMesh>&,
			const dictionary&
		);

		//- Construct by mapping given
		//  fixedFluxExtrapolatedPressureFvPatchScalarField onto a new patch
		FoamFiniteVolume_EXPORT fixedFluxExtrapolatedPressureFvPatchScalarField
		(
			const fixedFluxExtrapolatedPressureFvPatchScalarField&,
			const fvPatch&,
			const DimensionedField<scalar, volMesh>&,
			const fvPatchFieldMapper&
		);

		//- Copy constructor
		FoamFiniteVolume_EXPORT fixedFluxExtrapolatedPressureFvPatchScalarField
		(
			const fixedFluxExtrapolatedPressureFvPatchScalarField&
		);

		//- Construct and return a clone
		virtual tmp<fvPatchScalarField> clone() const
		{
			return tmp<fvPatchScalarField>
				(
					new fixedFluxExtrapolatedPressureFvPatchScalarField(*this)
					);
		}

		//- Copy constructor setting internal field reference
		FoamFiniteVolume_EXPORT fixedFluxExtrapolatedPressureFvPatchScalarField
		(
			const fixedFluxExtrapolatedPressureFvPatchScalarField&,
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
					new fixedFluxExtrapolatedPressureFvPatchScalarField(*this, iF)
					);
		}
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_fixedFluxExtrapolatedPressureFvPatchScalarField_Header
