#pragma once
#ifndef _freestreamPressureFvPatchScalarField_Header
#define _freestreamPressureFvPatchScalarField_Header

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
	tnbLib::freestreamPressureFvPatchScalarField

Description
	This boundary condition provides a free-stream condition for pressure.

	It is an outlet-inlet condition that uses the velocity orientation to
	continuously blend between zero gradient for normal inlet and fixed value
	for normal outlet flow.

Usage
	\table
		Property        | Description                | Required | Default value
		U               | velocity field name        | no       | U
		freestreamValue | freestream pressure        | yes      |
		supersonic      | Switch for supersonic flow | no       | false
	\endtable

	Example of the boundary condition specification:
	\verbatim
	<patchName>
	{
		type            freestreamPressure;
		freestreamValue uniform 1e5;
	}
	\endverbatim

Note
	This condition is designed to operate with a freestreamVelocity condition

See also
	tnbLib::mixedFvPatchField
	tnbLib::freestreamFvPatchField

SourceFiles
	freestreamPressureFvPatchScalarField.C

\*---------------------------------------------------------------------------*/

#include <fvPatchFields.hxx>
#include <mixedFvPatchFields.hxx>

#include <Switch.hxx>  // added by amir

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
				 Class freestreamPressureFvPatchScalarField Declaration
	\*---------------------------------------------------------------------------*/

	class freestreamPressureFvPatchScalarField
		:
		public mixedFvPatchScalarField
	{
		// Private Data

			//- Name of the velocity field
		word UName_;

		//- Set true for supersonic freestream
		Switch supersonic_;


	public:

		//- Runtime type information
		//TypeName("freestreamPressure");
		static const char* typeName_() { return "freestreamPressure"; }
		static FoamFiniteVolume_EXPORT const ::tnbLib::word typeName;
		static FoamFiniteVolume_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from patch and internal field
		FoamFiniteVolume_EXPORT freestreamPressureFvPatchScalarField
		(
			const fvPatch&,
			const DimensionedField<scalar, volMesh>&
		);

		//- Construct from patch, internal field and dictionary
		FoamFiniteVolume_EXPORT freestreamPressureFvPatchScalarField
		(
			const fvPatch&,
			const DimensionedField<scalar, volMesh>&,
			const dictionary&
		);

		//- Construct by mapping given freestreamPressureFvPatchScalarField onto
		//  a new patch
		FoamFiniteVolume_EXPORT freestreamPressureFvPatchScalarField
		(
			const freestreamPressureFvPatchScalarField&,
			const fvPatch&,
			const DimensionedField<scalar, volMesh>&,
			const fvPatchFieldMapper&
		);

		//- Copy constructor
		FoamFiniteVolume_EXPORT freestreamPressureFvPatchScalarField
		(
			const freestreamPressureFvPatchScalarField&
		);

		//- Construct and return a clone
		virtual tmp<fvPatchScalarField> clone() const
		{
			return tmp<fvPatchScalarField>
				(
					new freestreamPressureFvPatchScalarField(*this)
					);
		}

		//- Copy constructor setting internal field reference
		FoamFiniteVolume_EXPORT freestreamPressureFvPatchScalarField
		(
			const freestreamPressureFvPatchScalarField&,
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
					new freestreamPressureFvPatchScalarField(*this, iF)
					);
		}


		// Member Functions

		const scalarField& freestreamValue() const
		{
			return refValue();
		}

		scalarField& freestreamValue()
		{
			return refValue();
		}


		// Evaluation functions

			//- Update the coefficients associated with the patch field
		FoamFiniteVolume_EXPORT virtual void updateCoeffs();


		//- Write
		FoamFiniteVolume_EXPORT virtual void write(Ostream&) const;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_freestreamPressureFvPatchScalarField_Header
