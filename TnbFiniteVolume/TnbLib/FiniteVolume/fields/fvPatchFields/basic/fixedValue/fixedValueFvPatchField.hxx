#pragma once
#ifndef _fixedValueFvPatchField_Header
#define _fixedValueFvPatchField_Header

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
	tnbLib::fixedValueFvPatchField

Description
	This boundary condition supplies a fixed value constraint, and is the base
	class for a number of other boundary conditions.

Usage
	\table
		Property     | Description             | Required    | Default value
		value        | Patch face values       | yes         |
	\endtable

	Example of the boundary condition specification:
	\verbatim
	<patchName>
	{
		type            fixedValue;
		value           uniform 0;  // Example for scalar field usage
	}
	\endverbatim

SourceFiles
	fixedValueFvPatchField.C

\*---------------------------------------------------------------------------*/

#include <fvPatchField.hxx>

#ifdef FoamFiniteVolume_EXPORT_DEFINE
#define FoamfixedValueFvPatchField_EXPORT __declspec(dllexport)
#else
#ifdef FoamfixedValueFvPatchField_EXPORT_DEFINE
#define FoamfixedValueFvPatchField_EXPORT __declspec(dllexport)
#else
#define FoamfixedValueFvPatchField_EXPORT __declspec(dllimport)
#endif
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
					   Class fixedValueFvPatchField Declaration
	\*---------------------------------------------------------------------------*/

	template<class Type>
	class fixedValueFvPatchField
		:
		public fvPatchField<Type>
	{

	public:

		//- Runtime type information
		//TypeName("fixedValue");
		static const char* typeName_() { return "fixedValue"; }
		static FoamfixedValueFvPatchField_EXPORT const ::tnbLib::word typeName;
		static FoamfixedValueFvPatchField_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from patch and internal field
		fixedValueFvPatchField
		(
			const fvPatch&,
			const DimensionedField<Type, volMesh>&
		);

		//- Construct from patch, internal field and dictionary
		fixedValueFvPatchField
		(
			const fvPatch&,
			const DimensionedField<Type, volMesh>&,
			const dictionary&,
			const bool valueRequired = true
		);

		//- Construct by mapping the given fixedValueFvPatchField<Type>
		//  onto a new patch
		fixedValueFvPatchField
		(
			const fixedValueFvPatchField<Type>&,
			const fvPatch&,
			const DimensionedField<Type, volMesh>&,
			const fvPatchFieldMapper&,
			const bool mappingRequired = true
		);

		//- Copy constructor
		fixedValueFvPatchField
		(
			const fixedValueFvPatchField<Type>&
		);

		//- Construct and return a clone
		virtual tmp<fvPatchField<Type>> clone() const
		{
			return tmp<fvPatchField<Type>>
				(
					new fixedValueFvPatchField<Type>(*this)
					);
		}

		//- Copy constructor setting internal field reference
		fixedValueFvPatchField
		(
			const fixedValueFvPatchField<Type>&,
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
					new fixedValueFvPatchField<Type>(*this, iF)
					);
		}


		// Member Functions

			// Attributes

				//- Return true if this patch field fixes a value.
				//  Needed to check if a level has to be specified while solving
				//  Poissons equations.
		virtual bool fixesValue() const
		{
			return true;
		}

		//- Return false: this patch field is not altered by assignment
		virtual bool assignable() const
		{
			return false;
		}


		// Evaluation functions

			//- Return the matrix diagonal coefficients corresponding to the
			//  evaluation of the value of this patchField with given weights
		virtual tmp<Field<Type>> valueInternalCoeffs
		(
			const tmp<scalarField>&
		) const;

		//- Return the matrix source coefficients corresponding to the
		//  evaluation of the value of this patchField with given weights
		virtual tmp<Field<Type>> valueBoundaryCoeffs
		(
			const tmp<scalarField>&
		) const;

		//- Return the matrix diagonal coefficients corresponding to the
		//  evaluation of the gradient of this patchField
		virtual tmp<Field<Type>> gradientInternalCoeffs() const;

		//- Return the matrix source coefficients corresponding to the
		//  evaluation of the gradient of this patchField
		virtual tmp<Field<Type>> gradientBoundaryCoeffs() const;


		//- Write
		virtual void write(Ostream&) const;


		// Member Operators

		virtual void operator=(const UList<Type>&) {}

		virtual void operator=(const fvPatchField<Type>&) {}
		virtual void operator+=(const fvPatchField<Type>&) {}
		virtual void operator-=(const fvPatchField<Type>&) {}
		virtual void operator*=(const fvPatchField<scalar>&) {}
		virtual void operator/=(const fvPatchField<scalar>&) {}

		virtual void operator+=(const Field<Type>&) {}
		virtual void operator-=(const Field<Type>&) {}

		virtual void operator*=(const Field<scalar>&) {}
		virtual void operator/=(const Field<scalar>&) {}

		virtual void operator=(const Type&) {}
		virtual void operator+=(const Type&) {}
		virtual void operator-=(const Type&) {}
		virtual void operator*=(const scalar) {}
		virtual void operator/=(const scalar) {}
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <fixedValueFvPatchFieldI.hxx>

//#ifdef NoRepository
//#include <fixedValueFvPatchField.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_fixedValueFvPatchField_Header
