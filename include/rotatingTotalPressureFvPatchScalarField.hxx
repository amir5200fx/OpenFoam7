#pragma once
#ifndef _rotatingTotalPressureFvPatchScalarField_Header
#define _rotatingTotalPressureFvPatchScalarField_Header

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
	tnbLib::rotatingTotalPressureFvPatchScalarField

Description
	This boundary condition provides a total pressure condition for patches
	in a rotating frame.

Usage
	\table
		Property     | Description             | Required    | Default value
		U            | velocity field name     | no          | U
		phi          | flux field name         | no          | phi
		rho          | density field name      | no          | none
		psi          | compressibility field name | no       | none
		gamma        | ratio of specific heats (Cp/Cv) | yes |
		p0           | static pressure reference | yes       |
		omega        | angular velocty of the frame [rad/s] | yes    |
	\endtable

	Example of the boundary condition specification:
	\verbatim
	<patchName>
	{
		type            rotatingTotalPressure;
		U               U;
		phi             phi;
		rho             rho;
		psi             psi;
		gamma           1.4;
		p0              uniform 1e5;
		omega           100;
	}
	\endverbatim

	The \c omega entry is a Function1 type, able to describe time varying
	functions.

See also
	tnbLib::totalPressureFvPatchScalarField
	tnbLib::Function1Types

SourceFiles
	rotatingTotalPressureFvPatchScalarField.C

\*---------------------------------------------------------------------------*/

#include <totalPressureFvPatchScalarField.hxx>
#include <Function1.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
			   Class rotatingTotalPressureFvPatchScalarField Declaration
	\*---------------------------------------------------------------------------*/

	class rotatingTotalPressureFvPatchScalarField
		:
		public totalPressureFvPatchScalarField
	{
		// Private Data

			//- Angular velocity of the frame
		autoPtr<Function1<vector>> omega_;


	public:

		//- Runtime type information
		/*TypeName("rotatingTotalPressure");*/
		static const char* typeName_() { return "rotatingTotalPressure"; }
		static FoamFiniteVolume_EXPORT const ::tnbLib::word typeName;
		static FoamFiniteVolume_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from patch and internal field
		FoamFiniteVolume_EXPORT rotatingTotalPressureFvPatchScalarField
		(
			const fvPatch&,
			const DimensionedField<scalar, volMesh>&
		);

		//- Construct from patch, internal field and dictionary
		FoamFiniteVolume_EXPORT rotatingTotalPressureFvPatchScalarField
		(
			const fvPatch&,
			const DimensionedField<scalar, volMesh>&,
			const dictionary&
		);

		//- Construct by mapping given rotatingTotalPressureFvPatchScalarField
		//  onto a new patch
		FoamFiniteVolume_EXPORT rotatingTotalPressureFvPatchScalarField
		(
			const rotatingTotalPressureFvPatchScalarField&,
			const fvPatch&,
			const DimensionedField<scalar, volMesh>&,
			const fvPatchFieldMapper&
		);

		//- Copy constructor
		FoamFiniteVolume_EXPORT rotatingTotalPressureFvPatchScalarField
		(
			const rotatingTotalPressureFvPatchScalarField&
		);

		//- Construct and return a clone
		virtual tmp<fvPatchScalarField> clone() const
		{
			return tmp<fvPatchScalarField>
				(
					new rotatingTotalPressureFvPatchScalarField(*this)
					);
		}

		//- Copy constructor setting internal field reference
		FoamFiniteVolume_EXPORT rotatingTotalPressureFvPatchScalarField
		(
			const rotatingTotalPressureFvPatchScalarField&,
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
					new rotatingTotalPressureFvPatchScalarField(*this, iF)
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

#endif // !_rotatingTotalPressureFvPatchScalarField_Header
