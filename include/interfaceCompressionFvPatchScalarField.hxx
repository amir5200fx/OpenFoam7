#pragma once
#ifndef _interfaceCompressionFvPatchScalarField_Header
#define _interfaceCompressionFvPatchScalarField_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2017-2019 OpenFOAM Foundation
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
	tnbLib::interfaceCompressionFvPatchScalarField

Description
	Applies interface-compression to the phase-fraction distribution at the
	patch by setting the phase-fraction to 0 if it is below 0.5, otherwise
	to 1.

	This approach is useful to avoid unphysical "bleed" of the lighter phase
	along the surface in regions of high shear adjacent to the surface which
	is at a shallow angle to the interface.

See also
	tnbLib::fixedValueFvPatchScalarField

SourceFiles
	interfaceCompressionFvPatchScalarField.C

\*---------------------------------------------------------------------------*/

#include <fixedValueFvPatchFields.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
			 Class interfaceCompressionFvPatchScalarField Declaration
	\*---------------------------------------------------------------------------*/

	class interfaceCompressionFvPatchScalarField
		:
		public fixedValueFvPatchScalarField
	{

	public:

		//- Runtime type information
		//TypeName("interfaceCompression");
		static const char* typeName_() { return "interfaceCompression"; }
		static FoamFiniteVolume_EXPORT const ::tnbLib::word typeName;
		static FoamFiniteVolume_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from patch and internal field
		FoamFiniteVolume_EXPORT interfaceCompressionFvPatchScalarField
		(
			const fvPatch&,
			const DimensionedField<scalar, volMesh>&
		);

		//- Construct from patch, internal field and dictionary
		FoamFiniteVolume_EXPORT interfaceCompressionFvPatchScalarField
		(
			const fvPatch&,
			const DimensionedField<scalar, volMesh>&,
			const dictionary&
		);

		//- Construct by mapping given
		//  interfaceCompressionFvPatchScalarField onto a new patch
		FoamFiniteVolume_EXPORT interfaceCompressionFvPatchScalarField
		(
			const interfaceCompressionFvPatchScalarField&,
			const fvPatch&,
			const DimensionedField<scalar, volMesh>&,
			const fvPatchFieldMapper&
		);

		//- Copy constructor
		FoamFiniteVolume_EXPORT interfaceCompressionFvPatchScalarField
		(
			const interfaceCompressionFvPatchScalarField&
		);

		//- Construct and return a clone
		virtual tmp<fvPatchScalarField> clone() const
		{
			return tmp<fvPatchScalarField >
				(
					new interfaceCompressionFvPatchScalarField(*this)
					);
		}

		//- Copy constructor setting internal field reference
		FoamFiniteVolume_EXPORT interfaceCompressionFvPatchScalarField
		(
			const interfaceCompressionFvPatchScalarField&,
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
					new interfaceCompressionFvPatchScalarField(*this, iF)
					);
		}


		// Member Functions

			// Evaluation functions

				//- Update the coefficients associated with the patch field
		FoamFiniteVolume_EXPORT virtual void updateCoeffs();


		//- Write
		FoamFiniteVolume_EXPORT virtual void write(Ostream&) const;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_interfaceCompressionFvPatchScalarField_Header
