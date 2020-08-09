#pragma once
#ifndef _uniformFixedGradientFvPatchField_Header
#define _uniformFixedGradientFvPatchField_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2013-2019 OpenFOAM Foundation
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
	tnbLib::uniformFixedGradientFvPatchField

Description
	This boundary condition provides a uniform fixed gradient condition.

Usage
	\table
		Property     | Description             | Required    | Default value
		uniformGradient | uniform gradient     | yes         |
	\endtable

	Example of the boundary condition specification:
	\verbatim
	<patchName>
	{
		type            uniformFixedGradient;
		uniformGradient constant 0.2;
	}
	\endverbatim

Note
	The uniformGradient entry is a Function1 type, able to describe time
	varying functions.  The example above gives the usage for supplying a
	constant value.

See also
	tnbLib::Function1Types
	tnbLib::fixedGradientFvPatchField

SourceFiles
	uniformFixedGradientFvPatchField.C

\*---------------------------------------------------------------------------*/

#include <fixedGradientFvPatchFields.hxx>
#include <Function1.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
				  Class uniformFixedGradientFvPatchField Declaration
	\*---------------------------------------------------------------------------*/

	template<class Type>
	class uniformFixedGradientFvPatchField
		:
		public fixedGradientFvPatchField<Type>
	{
		// Private Data

			//- Gradient
		autoPtr<Function1<Type>> uniformGradient_;


	public:

		//- Runtime type information
		TypeName("uniformFixedGradient");


		// Constructors

			//- Construct from patch and internal field
		uniformFixedGradientFvPatchField
		(
			const fvPatch&,
			const DimensionedField<Type, volMesh>&
		);

		//- Construct from patch and internal field and patch field
		uniformFixedGradientFvPatchField
		(
			const fvPatch&,
			const DimensionedField<Type, volMesh>&,
			const Field<Type>& fld
		);

		//- Construct from patch, internal field and dictionary
		uniformFixedGradientFvPatchField
		(
			const fvPatch&,
			const DimensionedField<Type, volMesh>&,
			const dictionary&
		);

		//- Construct by mapping given uniformFixedGradientFvPatchField
		//  onto a new patch
		uniformFixedGradientFvPatchField
		(
			const uniformFixedGradientFvPatchField<Type>&,
			const fvPatch&,
			const DimensionedField<Type, volMesh>&,
			const fvPatchFieldMapper&
		);

		//- Copy constructor
		uniformFixedGradientFvPatchField
		(
			const uniformFixedGradientFvPatchField<Type>&
		);

		//- Construct and return a clone
		virtual tmp<fvPatchField<Type>> clone() const
		{
			return tmp<fvPatchField<Type>>
				(
					new uniformFixedGradientFvPatchField<Type>(*this)
					);
		}

		//- Copy constructor setting internal field reference
		uniformFixedGradientFvPatchField
		(
			const uniformFixedGradientFvPatchField<Type>&,
			const DimensionedField<Type, volMesh>&
		);

		//- Construct and return a clone setting internal field reference
		virtual tmp<fvPatchField<Type>> clone
		(
			const DimensionedField<Type, volMesh>& iF
		) const
		{
			return tmp<fvPatchField<Type>>
				(
					new uniformFixedGradientFvPatchField<Type>(*this, iF)
					);
		}


		// Member Functions

			//- Update the coefficients associated with the patch field
		virtual void updateCoeffs();

		//- Write
		virtual void write(Ostream&) const;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#ifdef NoRepository
#include <uniformFixedGradientFvPatchField.cxx>
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_uniformFixedGradientFvPatchField_Header
