#pragma once
#ifndef _kLowReWallFunctionFvPatchScalarField_Header
#define _kLowReWallFunctionFvPatchScalarField_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2012-2019 OpenFOAM Foundation
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
	tnbLib::kLowReWallFunctionFvPatchScalarField

Description
	This boundary condition provides a turbulence kinetic energy wall function
	condition for low- and high-Reynolds number turbulent flow cases.

	The model operates in two modes, based on the computed laminar-to-turbulent
	switch-over y+ value derived from kappa and E specified in the corresponding
	nutWallFunction.

Usage
	\table
		Property     | Description             | Required    | Default value
		Ceps2        | model coefficient       | no          | 1.9
	\endtable

	Example of the boundary condition specification:
	\verbatim
	<patchName>
	{
		type            kLowReWallFunction;
	}
	\endverbatim

See also
	tnbLib::fixedValueFvPatchField

SourceFiles
	kLowReWallFunctionFvPatchScalarField.C

\*---------------------------------------------------------------------------*/

#include <fixedValueFvPatchField.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
				Class kLowReWallFunctionFvPatchScalarField Declaration
	\*---------------------------------------------------------------------------*/

	class kLowReWallFunctionFvPatchScalarField
		:
		public fixedValueFvPatchField<scalar>
	{
	protected:

		// Protected data

			//- Ceps2 coefficient
		scalar Ceps2_;


	public:

		//- Runtime type information
		//TypeName("kLowReWallFunction");
		static const char* typeName_() { return "kLowReWallFunction"; }
		static FoamTurbulence_EXPORT const ::tnbLib::word typeName;
		static FoamTurbulence_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from patch and internal field
		FoamTurbulence_EXPORT kLowReWallFunctionFvPatchScalarField
		(
			const fvPatch&,
			const DimensionedField<scalar, volMesh>&
		);

		//- Construct from patch, internal field and dictionary
		FoamTurbulence_EXPORT kLowReWallFunctionFvPatchScalarField
		(
			const fvPatch&,
			const DimensionedField<scalar, volMesh>&,
			const dictionary&
		);

		//- Construct by mapping given kLowReWallFunctionFvPatchScalarField
		//  onto a new patch
		FoamTurbulence_EXPORT kLowReWallFunctionFvPatchScalarField
		(
			const kLowReWallFunctionFvPatchScalarField&,
			const fvPatch&,
			const DimensionedField<scalar, volMesh>&,
			const fvPatchFieldMapper&
		);

		//- Copy constructor
		FoamTurbulence_EXPORT kLowReWallFunctionFvPatchScalarField
		(
			const kLowReWallFunctionFvPatchScalarField&
		);

		//- Construct and return a clone
		virtual tmp<fvPatchScalarField> clone() const
		{
			return tmp<fvPatchScalarField>
				(
					new kLowReWallFunctionFvPatchScalarField(*this)
					);
		}

		//- Copy constructor setting internal field reference
		FoamTurbulence_EXPORT kLowReWallFunctionFvPatchScalarField
		(
			const kLowReWallFunctionFvPatchScalarField&,
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
					new kLowReWallFunctionFvPatchScalarField(*this, iF)
					);
		}


		// Member Functions

			// Evaluation functions

				//- Update the coefficients associated with the patch field
		FoamTurbulence_EXPORT virtual void updateCoeffs();


		// I-O

			//- Write
		FoamTurbulence_EXPORT virtual void write(Ostream&) const;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_kLowReWallFunctionFvPatchScalarField_Header
