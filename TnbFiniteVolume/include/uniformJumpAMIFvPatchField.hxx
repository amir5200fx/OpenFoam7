#pragma once
#ifndef _uniformJumpAMIFvPatchField_Header
#define _uniformJumpAMIFvPatchField_Header

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
	tnbLib::uniformJumpAMIFvPatchField

Description
	This boundary condition provides a jump condition, using the \c cyclicAMI
	condition as a base.  The jump is specified as a time-varying uniform
	value across the patch.

Usage
	\table
		Property     | Description             | Required    | Default value
		patchType    | underlying patch type should be \c cyclicAMI| yes |
		jumpTable    | jump value              | yes         |
	\endtable

	Example of the boundary condition specification:
	\verbatim
	<patchName>
	{
		type            uniformJumpAMI;
		patchType       cyclicAMI;
		jumpTable       constant 10;
	}
	\endverbatim

	The above example shows the use of a fixed jump of '10'.

Note
	The uniformValue entry is a Function1 type, able to describe time
	varying functions.  The example above gives the usage for supplying a
	constant value.

	The underlying \c patchType should be set to \c cyclic

See also
	tnbLib::jumpCyclicAMIFvPatchField
	tnbLib::Function1Types

SourceFiles
	uniformJumpAMIFvPatchField.C

\*---------------------------------------------------------------------------*/

#include <fixedJumpAMIFvPatchField.hxx>
#include <Function1.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
					 Class uniformJumpAMIFvPatchField Declaration
	\*---------------------------------------------------------------------------*/

	template<class Type>
	class uniformJumpAMIFvPatchField
		:
		public fixedJumpAMIFvPatchField<Type>
	{

	protected:

		// Protected data

			//- "jump" table
		autoPtr<Function1<Type>> jumpTable_;


	public:

		//- Runtime type information
		TypeName("uniformJumpAMI");

		// Constructors

			//- Construct from patch and internal field
		uniformJumpAMIFvPatchField
		(
			const fvPatch&,
			const DimensionedField<Type, volMesh>&
		);

		//- Construct from patch, internal field and dictionary
		uniformJumpAMIFvPatchField
		(
			const fvPatch&,
			const DimensionedField<Type, volMesh>&,
			const dictionary&
		);

		//- Construct by mapping given uniformJumpAMIFvPatchField onto a
		//  new patch
		uniformJumpAMIFvPatchField
		(
			const uniformJumpAMIFvPatchField<Type>&,
			const fvPatch&,
			const DimensionedField<Type, volMesh>&,
			const fvPatchFieldMapper&
		);

		//- Copy constructor
		uniformJumpAMIFvPatchField
		(
			const uniformJumpAMIFvPatchField<Type>&
		);

		//- Construct and return a clone
		virtual tmp<fvPatchField<Type>> clone() const
		{
			return tmp<fvPatchField<Type>>
				(
					new uniformJumpAMIFvPatchField<Type>(*this)
					);
		}

		//- Copy constructor setting internal field reference
		uniformJumpAMIFvPatchField
		(
			const uniformJumpAMIFvPatchField<Type>&,
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
					new uniformJumpAMIFvPatchField<Type>(*this, iF)
					);
		}


		// Member Functions

			//- Update the coefficients
		virtual void updateCoeffs();

		//- Write
		virtual void write(Ostream&) const;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#ifdef NoRepository
#include <uniformJumpAMIFvPatchField.cxx>
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_uniformJumpAMIFvPatchField_Header