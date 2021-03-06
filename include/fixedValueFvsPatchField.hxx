#pragma once
#ifndef _fixedValueFvsPatchField_Header
#define _fixedValueFvsPatchField_Header

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
	tnbLib::fixedValueFvsPatchField

Description
	tnbLib::fixedValueFvsPatchField

SourceFiles
	fixedValueFvsPatchField.C

\*---------------------------------------------------------------------------*/


#include <fvsPatchField.hxx>

#ifdef FoamFiniteVolume_EXPORT_DEFINE
#define FoamFixedValueFvsPatchField_EXPORT __declspec(dllexport)
#else
#ifdef FoamFixedValueFvsPatchField_EXPORT_DEFINE
#define FoamFixedValueFvsPatchField_EXPORT __declspec(dllexport)
#else
#define FoamFixedValueFvsPatchField_EXPORT __declspec(dllimport)
#endif
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							   Class fixedValueFvsPatch Declaration
	\*---------------------------------------------------------------------------*/

	template<class Type>
	class fixedValueFvsPatchField
		:
		public fvsPatchField<Type>
	{

	public:

		//- Runtime type information
		/*TypeName("fixedValue");*/
		static const char* typeName_() { return "fixedValue"; }
		static FoamFixedValueFvsPatchField_EXPORT const ::tnbLib::word typeName;
		static FoamFixedValueFvsPatchField_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from patch and internal field
		fixedValueFvsPatchField
		(
			const fvPatch&,
			const DimensionedField<Type, surfaceMesh>&
		);

		//- Construct from patch, internal field and dictionary
		fixedValueFvsPatchField
		(
			const fvPatch&,
			const DimensionedField<Type, surfaceMesh>&,
			const dictionary&
		);

		//- Construct by mapping the given fixedValueFvsPatchField<Type>
		//  onto a new patch
		fixedValueFvsPatchField
		(
			const fixedValueFvsPatchField<Type>&,
			const fvPatch&,
			const DimensionedField<Type, surfaceMesh>&,
			const fvPatchFieldMapper&
		);

		//- Copy constructor
		fixedValueFvsPatchField
		(
			const fixedValueFvsPatchField<Type>&
		);

		//- Construct and return a clone
		virtual tmp<fvsPatchField<Type>> clone() const
		{
			return tmp<fvsPatchField<Type>>
				(
					new fixedValueFvsPatchField<Type>(*this)
					);
		}

		//- Copy constructor setting internal field reference
		fixedValueFvsPatchField
		(
			const fixedValueFvsPatchField<Type>&,
			const DimensionedField<Type, surfaceMesh>&
		);

		//- Construct and return a clone setting internal field reference
		virtual tmp<fvsPatchField<Type>> clone
		(
			const DimensionedField<Type, surfaceMesh>& iF
		) const
		{
			return tmp<fvsPatchField<Type>>
				(
					new fixedValueFvsPatchField<Type>(*this, iF)
					);
		}


		// Member Functions

			// Access

				//- Return true if this patch field fixes a value.
				//  Needed to check if a level has to be specified while solving
				//  Poissons equations.
		virtual bool fixesValue() const
		{
			return true;
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


		// Member Operators

		virtual void operator=(const UList<Type>&) {}

		virtual void operator=(const fvsPatchField<Type>&) {}
		virtual void operator+=(const fvsPatchField<Type>&) {}
		virtual void operator-=(const fvsPatchField<Type>&) {}
		virtual void operator*=(const fvsPatchField<scalar>&) {}
		virtual void operator/=(const fvsPatchField<scalar>&) {}

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

#include <fixedValueFvsPatchFieldI.hxx>

//#ifdef NoRepository
//#include <fixedValueFvsPatchField.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_fixedValueFvsPatchField_Header
